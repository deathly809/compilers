package main

//
//	Here is the issue: How can I tell when one production ends and another begins?
//
//
//	<S> 		::= <P> <S> | EMPTY
//	<P> 		::= <N_TERM> "::=" <P_LIST> [NewLine] {  "|" <P_LIST> [NewLine] }
//	<P_LIST> 	::= <P_TERM> <P_LIST> | EMPTY
//  <P_TERM> 	::=	<O_GROUP> | <R_GROUP> | <G_GROUP> | <N_TERM> | <TERM>
//	<O_GROUP>	::= "[" <P_LIST> "]"
//	<R_GROUP>	::= "{" <P_LIST> "}"
//	<G_GROUP>	::= "(" <P_LIST> ")"
//
//	<N_TERM>	::= "<" <N_IDENT> ">"
//	<TERM>		::= "\""" <T_IDENT> "\"""
//
//	<N_IDENT>	::= U_LETTER <N_IDENT> | U_LETTER
//	<T_IDENT>	::= LETTER <T_IDENT> | LETTER
//
//
//
//

import (
	"bufio"
	"flag"
	"fmt"
	"os"
	"strings"
)

var (
	input = flag.String("input", "", "input file to read")
)

var productions = make(map[string][][]string)

func validateArgs() {
	flag.Parse()
	if !flag.Parsed() {
		flag.PrintDefaults()
		os.Exit(1)
	}

	if *input == "" {
		fmt.Println("missing input flag")
		flag.PrintDefaults()
		os.Exit(1)
	}
}

func parseProduction(input *bufio.Scanner) {

	prev := ""
	currProd := ""

	var terms [][]string
	var term []string

	// Productions
	for input.Scan() {

		str := input.Text()

		switch str {
		case "(":

		case "[":
		case "{":
		default: // Production
		}

		if str == "::=" {
			if prev == "" {
				panic("error... no previous value")
			}

			if currProd == "" {
				currProd = prev
				continue
			}

			if !strings.HasPrefix(prev, "<") {
				panic(fmt.Sprintf("production names must begin with <: %s", prev))
			}

			if !strings.HasSuffix(prev, ">") {
				panic(fmt.Sprintf("production names must end with >: %s", prev))
			}

			if _, ok := productions[currProd]; ok {
				panic(fmt.Sprintf("key already exists: %s", currProd))
			}

			terms = append(terms, term)
			productions[currProd] = terms

			currProd = prev
			prev = ""

			terms = nil
			term = nil

		} else if str == "|" {
			term = append(term, prev)
			terms = append(terms, term)

			term = nil
			prev = ""
		} else {
			term = append(term, prev)
			prev = str
		}
	}

	if prev == "::=" {
		panic("final term was ::=")
	}

	term = append(term, prev)
	terms = append(terms, term)

	productions[currProd] = terms
}

func main() {
	validateArgs()

	f, err := os.Open(*input)
	if err != nil {
		panic(err)
	}
	defer f.Close()

	lexer := NewLexer(f)
	for lexer.HasNext() {
		fmt.Println(lexer.Next())
	}

	/*
		input := bufio.NewScanner(f)
		buffer := bytes.NewBuffer(nil)
		for input.Scan() {
			str := input.Text()
			if !strings.HasPrefix(str, "%") {
				buffer.WriteString(str)
				buffer.WriteRune('\n')
			}
		}

		input = bufio.NewScanner(buffer)
		input.Split(bufio.ScanWords)
		for input.Scan() {
			parseProduction(input)
		}
	*/
}
