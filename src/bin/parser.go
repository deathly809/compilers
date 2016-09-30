package main

import (
	"fmt"
	"io"
	"os"

	"github.com/deathly809/compilers/src/bin/main"
)

type NodeType byte

type Grammar struct {
	prods []*Production
}

type Production struct {
	value string
	alts  []*Alt
}

type Alt struct {
}

type Parser struct {
	l          *Lexer
	prev, curr *main.Lexeme
}

func (p *Parser) requiresType(t LexemeType) {
	if p.curr.t != t {
		fmt.Fprintf(os.Stderr, "ERROR: line: %d, column: %d, expected type %s, found type %s\n", p.curr.line, p.curr.col, TypeToString(t), TypeToString(p.curr.t))
		os.Exit(1)
	}
}
func (p *Parser) acceptIt() {
	if p.l.HasNext() {
		p.curr = p.l.Next()
	} else {
		p.curr = nil
	}
}

func (p *Parser) acceptType(t LexemeType) {
	p.requiresType(t)
	p.acceptIt()
}

func (p *Parser) Parse() *Grammar {
	result := &Grammar{}
	result.prods = p.parseProductions()
	return result
}

func (p *Parser) parseProductions() []*Production {
	result := []*Production(nil)
	if p.curr != nil {
		p.requiresType(NonTerminal)
		result = append(result, p.parseProduction())
	}
	return result
}

func (p *Parser) parseProduction() *Production {
	result := &Production{}
	result.value = p.curr.value
	p.acceptIt()
	p.acceptType(Assignment)
	result.alts = p.parseAlternatives()
	return result
}

func (p *Parser) parseAlternatives() []*Alt {
	result := []*Alt(nil)
	for {
		switch p.curr.t {
		case NewLine:
			goto end
		case Alternative:
			p.acceptIt()
			fallthrough
		default:
			result = append(result, p.parseAlternative())
		}
	}
end:
	return result
}

func (p *Parser) parseRepeat() *Alt {
	p.acceptIt()
	result := p.parseAlternative()
	p.acceptType(RightBrace)
	return result
}
func (p *Parser) parseOptional() *Alt {
	p.acceptIt()
	result := p.parseAlternative()
	p.acceptType(RightBracket)
	return result
}
func (p *Parser) parseGroup() *Alt {
	p.acceptIt()
	result := p.parseAlternative()
	p.acceptType(RightParen)
	return result
}

func (p *Parser) parseAlternative() *Alt {
	result := &Alt{}
	for {
		switch p.curr.t {
		case LeftBrace:
			result = append(result, p.parseRepeat())
		case LeftBracket:
			result = append(result, p.parseOptional())
		case LeftParen:
			result = append(result, p.parseGroup())
		case NewLine:
			p.acceptIt()
			break
		}
	}
	return result
}

func NewParser(input io.Reader) *Parser {
	return &Parser{NewLexer(input), nil, nil}
}
