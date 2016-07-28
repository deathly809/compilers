package parsers

import "bytes"

// Symbol represents a terminal or non-terminal symbol
type Symbol interface {
	Value() string
	GetProduction() Production
	SetProduction(Production)
	String() string
}

// Production defines the functions and methods of a grammar
//
//      A production consistes of two parts, a left hand side and right hand side,
//      denoted as P -> R_1 | R_2 | ...
//      where R_1 is a string of terminals and non-terminals
//
type Production interface {
	Label() Symbol
	Alternatives() []Alternative
	AddAlternative(Alternative)
	String() string
}

// Grammar defines the functions and methods of a grammar
type Grammar interface {
	GetStart() Symbol
	SetStart(Symbol)
	GetProduction(Symbol) Production
	AddProduction(Production)
	String() string
}

// Alternative is just an array of symbols
type Alternative []Symbol

func (a Alternative) String() string {
	buffer := bytes.NewBuffer([]byte(nil))
	if len(a) > 0 {
		buffer.WriteString(a[0].Value())
		for _, s := range a[1:] {
			buffer.WriteString(" ")
			buffer.WriteString(s.Value())
		}
	}
	return buffer.String()
}
