package main

import (
	"bytes"
	"fmt"
	"io"
	"io/ioutil"
	"os"
	"unicode"
)

type LexemeType byte

// Dumb
const (
	Terminal    = LexemeType(iota)
	NonTerminal = LexemeType(iota)
	Assignment  = LexemeType(iota)

	LeftParen  = LexemeType(iota)
	RightParen = LexemeType(iota)

	LeftBrace  = LexemeType(iota)
	RightBrace = LexemeType(iota)

	LeftBracket  = LexemeType(iota)
	RightBracket = LexemeType(iota)

	Alternative = LexemeType(iota)

	NewLine = LexemeType(iota)
)

func TypeToString(t LexemeType) string {
	switch t {
	case Terminal:
		return "Terminal"
	case NonTerminal:
		return "NonTerminal"
	case Assignment:
		return "Assignment"
	case LeftParen:
		return "LeftParen"
	case RightParen:
		return "RightParen"
	case LeftBrace:
		return "LeftBrace"
	case RightBrace:
		return "RightBrace"
	case LeftBracket:
		return "LeftBracket"
	case RightBracket:
		return "RightBracket"
	case Alternative:
		return "Alternative"
	case NewLine:
		return "NewLine"
	default:
		return "Unknown"
	}
}

type Lexeme struct {
	t         LexemeType
	value     string
	line, col int
}

func (l *Lexeme) String() string {
	if l.t != NewLine {
		return fmt.Sprintf("<%s,%s>", TypeToString(l.t), l.value)
	}
	return "<NewLine>"
}

type Lexer struct {
	pos, col, line int
	buffer         []rune
}

func (l *Lexer) char() rune {
	if l.hasMore() {
		return l.buffer[l.pos]
	}
	return 0
}

func (l *Lexer) hasMore() bool {
	return l.pos < len(l.buffer)
}

func (l *Lexer) next() {
	l.col++
	if l.char() == '\n' {
		l.line++
		l.col = 0
	}
	l.pos++
}

func (l *Lexer) readLine() {
	for l.hasMore() && l.char() != '\n' {
		l.next()
	}
	l.next()
}

func (l *Lexer) consumeWhitespace() {
	for {
		// read white space (stop at newlines)
		for l.hasMore() && l.char() != '\n' && unicode.IsSpace(l.char()) {
			l.next()
		}

		if l.char() == '#' {
			for l.hasMore() && l.char() != '\n' {
				l.next()
			}
			l.next()
		} else {
			break
		}
	}
}

func (l *Lexer) acceptIt() {
	l.next()
}

func (l *Lexer) accept(r rune) {
	if r != l.char() {
		fmt.Fprintf(os.Stderr, "line: %d, column: %d expected %c but found %c", l.line, l.col, r, l.char())
		os.Exit(1)
	}
	l.acceptIt()
}

func (l *Lexer) newLineLexeme() *Lexeme {
	l.acceptIt()
	return &Lexeme{NewLine, "\n", l.line, l.col}
}

func (l *Lexer) nonTerminalLexeme() *Lexeme {
	line := l.line
	col := l.col

	buffer := bytes.NewBuffer(nil)
	l.acceptIt()
	for (unicode.IsLetter(l.char()) || l.char() == '_') && l.char() != '>' {
		buffer.WriteRune(l.char())
		l.next()
	}
	l.accept('>')
	return &Lexeme{NonTerminal, buffer.String(), line, col}
}

func (l *Lexer) terminalLexeme() *Lexeme {
	line := l.line
	col := l.col
	buffer := bytes.NewBuffer(nil)
	l.acceptIt()
	dontExit := false
	for dontExit || l.char() != '"' {
		if !dontExit && l.char() == '\\' {
			dontExit = true
		} else {
			buffer.WriteRune(l.char())
			dontExit = false
		}
		l.next()
	}
	l.accept('"')
	return &Lexeme{Terminal, buffer.String(), line, col}
}

func (l *Lexer) leftBracketLexeme() *Lexeme {
	l.acceptIt()
	return &Lexeme{LeftBracket, "[", l.line, l.col}
}

func (l *Lexer) rightBracketLexeme() *Lexeme {
	l.acceptIt()
	return &Lexeme{RightBracket, "]", l.line, l.col}
}

func (l *Lexer) leftBraceLexeme() *Lexeme {
	l.acceptIt()
	return &Lexeme{LeftBrace, "{", l.line, l.col}
}

func (l *Lexer) rightBraceLexeme() *Lexeme {
	l.acceptIt()
	return &Lexeme{RightBrace, "}", l.line, l.col}
}

func (l *Lexer) leftParenLexeme() *Lexeme {
	l.acceptIt()
	return &Lexeme{LeftParen, "(", l.line, l.col}
}

func (l *Lexer) rightParenLexeme() *Lexeme {
	l.acceptIt()
	return &Lexeme{RightParen, ")", l.line, l.col}
}

func (l *Lexer) optionalLexeme() *Lexeme {
	l.acceptIt()
	return &Lexeme{Alternative, "|", l.line, l.col}
}

func (l *Lexer) assignmentLexeme() *Lexeme {
	l.acceptIt()
	l.accept(':')
	l.accept('=')
	return &Lexeme{Assignment, "::=", l.line, l.col}
}

func (l *Lexer) Next() *Lexeme {
	switch l.char() {
	case ':':
		return l.assignmentLexeme()
	case '\n':
		return l.newLineLexeme()
	case '<':
		return l.nonTerminalLexeme()
	case '"':
		return l.terminalLexeme()
	case '[':
		return l.leftBracketLexeme()
	case ']':
		return l.rightBracketLexeme()
	case '{':
		return l.leftBraceLexeme()
	case '}':
		return l.rightBraceLexeme()
	case '(':
		return l.leftParenLexeme()
	case ')':
		return l.rightParenLexeme()
	case '|':
		return l.optionalLexeme()
	default:
		fmt.Fprintf(os.Stderr, "line: %d, column: %d unexpected character '%c'\n", l.line, l.col, l.char())
		os.Exit(1)
	}
	return nil
}

func (l *Lexer) HasNext() bool {
	l.consumeWhitespace()
	return l.pos < len(l.buffer)
}

func NewLexer(input io.Reader) *Lexer {
	contents, err := ioutil.ReadAll(input)
	if err != nil {
		panic(err)
	}

	return &Lexer{0, 0, 0, []rune(string(contents))}
}
