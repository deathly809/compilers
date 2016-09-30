package parsers

import (
	"fmt"
	"io"
	"io/ioutil"
	"strings"
	"unicode"
)

func getRuneAtIndex(s string, idx int) rune {
	return []rune(s)[idx]
}

func substring(s string, first, last int) string {
	return string([]rune(s)[first:last])
}

func readDecimal(s string) string {
	for i, r := range s {
		if !unicode.IsDigit(r) {
			return s[i:]
		}
	}
	return ""
}

func removeFirst(s string) string {
	return string([]rune(s)[1:])
}

func period(s string) string {
	f := getRuneAtIndex(s, 0)
	if f == '.' {
		s = removeFirst(s)
	}
	return s
}

func decimal(s string) string {
	for i, r := range s {
		if !unicode.IsDigit(r) {
			t := substring(s, i, len(s))
			return t
		}
	}
	return ""
}

func sign(s string) string {
	if strings.HasPrefix(s, "+") || strings.HasPrefix(s, "-") {
		return removeFirst(s)
	}
	return s
}

func exponent(s string) string {

	if strings.HasPrefix(s, "e") || strings.HasPrefix(s, "E") {

		// Must remove e/E
		t := removeFirst(s)
		if t == "" {
			return s
		}

		// Optional +/-
		t = sign(t)
		if t == "" {
			return s
		}

		// Required decimals
		r := decimal(t)
		if r == t {
			return s
		}
		return r
	}
	return s
}

func decimalOrLetter(s string) string {
	for i, r := range s {
		if !(unicode.IsLetter(r) || unicode.IsDigit(r) || r == '_') {
			return substring(s, i, len(s))
		}
	}
	return ""
}

func isHexDigit(r rune) bool {
	return unicode.IsNumber(r) || (r <= 'F' && r >= 'A') || (r <= 'f' && r >= 'a')
}

func isOctDigit(r rune) bool {
	return r < '8' && r >= '0'
}

func checkNumber(s string, f func(rune) bool) string {
	for i, r := range s {
		if !f(r) {
			return substring(s, i, len(s))
		}
	}
	return ""
}

func hexNumber(s string) string {
	return checkNumber(s, isHexDigit)
}
func octNumber(s string) string {
	return checkNumber(s, isOctDigit)
}
func decNumber(s string) string {
	return checkNumber(s, unicode.IsNumber)
}

func readOptional(f func(string) string, s string) string {
	return f(s)
}

func readRequired(f func(string) string, s string) (string, bool) {
	r := f(s)
	return r, r != s
}

// ParseToken takes in a string, as much as it can
// The return value is (string, string, error)
//
//  The first string is how much was read
//  The second string is the remaining string
//  error is non-nil if could not parse
type ParseToken func(string) (string, string, error)

/*
 *  List of built-in functions to determine lexeme types
 */
var (
	StringFunc = func(s string) (string, string, error) {
		orig := s
		if strings.HasPrefix(s, "\"") {
			s = removeFirst(s)
			skip := false
			for i, r := range s {
				if skip {
					skip = false
				} else if r == '\\' {
					skip = true
				} else if r == '"' {
					s = substring(s, i+1, len(s))
					break
				}
			}
		} else {
			return "", orig, fmt.Errorf("strings start with \": %s", orig)
		}
		return orig[:len(orig)-len(s)], s, nil
	}
	// <number>     ::= <int> | <float>
	//
	//  <number>    ::= <decimal> [ . <decimal> ] [ <exponent> ]
	//              |   <decimal> [. <exponent>     ]
	//              |   . <decimal> [ <exponent> ]
	NumberFunc = func(s string) (string, string, error) {
		orig := s
		var ok bool
		if strings.HasPrefix(s, ".") {
			s = removeFirst(s)

			if s, ok = readRequired(decimal, s); !ok {
				return "", orig, fmt.Errorf("could not read number: %s", orig)
			}

			s = readOptional(exponent, s)
		} else {

			if s, ok = readRequired(decimal, s); !ok {
				return "", orig, fmt.Errorf("could not read number: %s", orig)
			}

			if strings.HasPrefix(s, ".") {
				return "", orig, fmt.Errorf("could not read number: %s", orig)
			}

			s = removeFirst(s)

			s = readOptional(decimal, s)
			s = readOptional(exponent, s)

		}
		return orig[:len(orig)-len(s)], s, nil
	}
	IDFunc = func(s string) (string, string, error) {
		first := getRuneAtIndex(s, 0)
		orig := s
		if unicode.IsLetter(first) || first == '_' {
			s = readOptional(decimalOrLetter, s)
		} else {
			return "", orig, fmt.Errorf("idenfifiers begin with a letter or underscore: %s", orig)
		}
		return orig[:len(orig)-len(s)], s, nil
	}
	// <decimals> . [ <decimals> ] [ <exponent> ]
	// <decimals> <exponent>
	// . <decimals> [ <exponent> ]

	// float    ::=     . <decimals> [ <exponent> ]
	//          |       <decimals> (  . [ <decimals> ] [ <exponent> ]  | <exponent>  )
	Real = func(s string) (string, string, error) {
		var ok bool
		orig := s
		if strings.HasPrefix(s, ".") {
			s = readOptional(period, s)

			if s, ok = readRequired(decimal, s); !ok {
				return "", orig, fmt.Errorf("could not parse decimal portion: %s", orig)
			}

			s = readOptional(exponent, s)
		} else {

			if s, ok = readRequired(decimal, s); !ok {
				return "", orig, fmt.Errorf("coult not parse decimal portion: %s", orig)
			}

			if strings.HasPrefix(s, ".") {
				s = readOptional(period, s)
				s = readOptional(decimal, s)
				s = readOptional(exponent, s)
			} else {
				if s, ok = readRequired(exponent, s); !ok {
					return "", orig, fmt.Errorf("could not read exponent: %s", orig)
				}
			}
		}
		return orig[:len(orig)-len(s)], s, nil
	}

	// <int>    ::= <hex> | <oct> | <dec>
	//
	//  <hex>       ::= '0' ( 'x' | 'X' ) <hex_digit> { <hex_digit> }
	//  <oct>       ::= '0' <oct_digit> { <oct_digit> }
	//  <dec>       ::= ( '1' | ... | '9' ) { <dec_digit> }
	//
	//  <hex_digit> ::= <dec_digit> | 'A' | 'B' | 'C' | 'D' | 'E' | 'F' | 'a' | 'b' | 'c' | 'd' | 'e' | 'g'
	//  <dec_digit> ::= <oct_digit> | '8' | '9'
	//  <oct_digit> ::= '0' | ... | '7'
	//
	//  Converted:
	//
	//  <int>       ::= ( '0' ( ( 'x' | 'X' ) <hex_num> | <oct_num> ) ) | <dec>
	//  <hex_num>   ::= <hex_digit> { <hex_digit> }
	//  <oct_num>   ::= <oct_digit> { <oct_digit> }
	Integer = func(s string) (string, string, error) {
		var ok bool
		orig := s
		if strings.HasPrefix(s, "0") {
			s = removeFirst(s)
			if strings.HasPrefix(s, "x") || strings.HasPrefix(s, "X") {
				s = removeFirst(s)
				if s, ok = readRequired(hexNumber, s); !ok {
					return "", orig, fmt.Errorf("could not parse hexidecimal number: %s", orig)
				}
			} else {
				if s, ok = readRequired(octNumber, s); !ok {
					return "", orig, fmt.Errorf("could not parse octal number: %s", orig)
				}
			}
		} else {
			if s, ok = readRequired(decNumber, s); !ok {
				return "", orig, fmt.Errorf("could not parse decimal number: %s", orig)
			}
		}
		return orig[:len(orig)-len(s)], s, nil
	}

	// isNext functions
	IDIsNext = func(s string) bool {
		first := getRuneAtIndex(s, 0)
		return unicode.IsLetter(first) || first == '_'
	}

	// isNext functions
	NumberIsNext = func(s string) bool {
		first := getRuneAtIndex(s, 0)
		return isHexDigit(first)
	}
)

type lexer struct {
	contents []string
	pos      int
	keywords []string
	prev     Lexeme
}

type lexeme struct {
	typ   LexemeType
	value string
}

func (l *lexeme) Type() LexemeType {
	return l.typ
}

func (l *lexeme) Value() string {
	return l.value
}

func (l *lexer) Scan() bool {
	return l.pos < len(l.contents)
}

func (l *lexer) Next() Lexeme {
	return nil
	//return l.contents[l.pos]
}

// NewLexer creates a new lexer from the input stream
func NewLexer(input io.Reader, keywords []string) Lexer {
	contents, err := ioutil.ReadAll(input)
	if err != nil {
		panic(err)
	}

	result := &lexer{
		strings.Fields(string(contents)),
		0,
		keywords,
		nil,
	}
	return result
}
