package main

import (
	"flag"
	"fmt"

	"github.com/deathly809/compilers/src/common"
	"github.com/deathly809/research/ranking/src/go/util"
)

var (
	input = flag.String("in", "", "inpuot file to lex")
)

var (
	flags = []string{"in"}
)

func init() {
	util.ValidateFlags(flags)
}

func main() {
	contents := common.readEntireFile(*input)
	r := NewReader(contents)

	for r.Next() {
		fmt.Printf("%c", r.Current())
	}
	fmt.Println()
	l := NewLexer(NewReader(contents))

	for l.HasNext() {
		fmt.Println(l.Next())
	}
}
