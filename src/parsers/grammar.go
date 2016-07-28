package parsers

import (
	"bufio"
	"bytes"
	"io"
	"strings"
)

type grammar struct {
	start       Symbol
	productions map[Symbol]Production
}

func (g *grammar) SetStart(start Symbol) {
	g.start = start
}

func (g *grammar) GetStart() Symbol {
	return g.start
}

func (g *grammar) GetProduction(label Symbol) Production {
	return g.productions[label]
}

func (g *grammar) AddProduction(prod Production) {
	if prod != nil {
		g.productions[prod.Label()] = prod
	}
}

func (g *grammar) String() string {
	writer := bytes.NewBuffer([]byte(nil))

	seen := make(map[Symbol]bool)
	Q := append([]Symbol(nil), g.start)
	for len(Q) > 0 {
		next := Q[len(Q)-1].GetProduction()

		writer.WriteString(next.String())

		Q = Q[:len(Q)-1]
		for _, alts := range next.Alternatives() {
			for _, sym := range alts {
				if _, ok := seen[sym]; !ok {
					seen[sym] = true
					Q = append(Q, sym)
				}
			}
		}
	}
	return writer.String()
}

func (g *grammar) Save(out io.Writer) {
	if g.start == nil {
		panic("Cannot write grammar, no start symbol")
	}
	out.Write([]byte(g.String()))
}

func (g *grammar) Load(in io.Reader) {
	reader := bufio.NewReader(in)
	start, err := reader.ReadString('\n')
	if err != nil {
		prod := strings.Split(start, "->")
		g.start = CreateSymbol(prod[0])
		if len(prod) == 1 {
			return
		}
	}
}

// CreateGrammar returns a new grammar data-structure
func CreateGrammar() Grammar {
	return &grammar{
		productions: make(map[Symbol]Production),
	}
}
