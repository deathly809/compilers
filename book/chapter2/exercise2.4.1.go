package main

import "fmt"

func S1(in []rune) []rune {
	if len(in) == 0 {
		panic("reached end of file")
	}
	switch in[0] {
	case '+':
		in = S1(in[1:])
		return S1(in)
	case '-':
		in = S1(in[1:])
		return S1(in)
	case 'a':
		return in[1:]
	default:
		panic("oops")
	}
}

func S2(in []rune) []rune {
	if len(in) > 0 {
		switch in[0] {
		case '(':
			in = S2(in[1:])
			match(')', in[0])
			return S2(in[1:])
		}
	}
	return in
}

func match(expected, found rune) {
	if expected != found {
		panic(fmt.Sprintf("expected '%c' but found '%c'\n", expected, found))
	}
}

func S3(in []rune) []rune {
	if len(in) == 0 {
		panic("empty string not allowed")
	}
	switch in[0] {
	case '0':
		in = in[1:]

		if in[0] != '1' {
			in = S3(in)
		}

		match('1', in[0])

		return in[1:]
	default:
		panic("unknown value")
	}
}

func Assert(passed bool) {
	if !passed {
		panic("assertion failed")
	}
}

func accepts() {
	for _, test := range []string{"a", "+aa", "-aa", "+a-aa", "+a+aa", "++aa+aa"} {
		Assert(len(S1([]rune(test))) == 0)
	}

	for _, test := range []string{"()", "", "()()", "()()()", "(()())", "(()(()()))"} {
		Assert(len(S2([]rune(test))) == 0)
	}

	for _, test := range []string{"01", "0011", "000111"} {
		Assert(len(S3([]rune(test))) == 0)
	}
}

func rec(s string) {
	if r := recover(); r == nil {
		fmt.Println(s)
	}
}

func fails() {
	for _, test := range []string{"aa", "-", "+", "+aa+aa", "+aa+aa"} {
		func() {
			defer rec(fmt.Sprintf("S1 did not fail on: '%s'", test))
			Assert(len(S1([]rune(test))) == 0)
		}()
	}

	for _, test := range []string{"(", ")", "()(", ")(", "()())", "()(()"} {
		func() {
			defer rec(fmt.Sprintf("S2 did not fail on: '%s'", test))
			Assert(len(S2([]rune(test))) == 0)
		}()
	}

	for _, test := range []string{"", "0", "1", "10", "11", "00", "110"} {
		func() {
			defer rec(fmt.Sprintf("S3 did not fail on: '%s'", test))
			Assert(len(S3([]rune(test))) == 0)
		}()
	}
}

func main() {
	accepts()
	fails()
}
