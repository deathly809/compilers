package parsers

import "bytes"

type production struct {
	label Symbol
	rhs   []Alternative
}

func (p *production) Label() Symbol {
	return p.label
}

func (p *production) Alternatives() []Alternative {
	return p.rhs
}

func (p *production) AddAlternative(r Alternative) {
	p.rhs = append(p.rhs, r)
}

func (p *production) String() string {
	buffer := bytes.NewBuffer([]byte(nil))
	buffer.WriteString(p.label.Value())
	if p.rhs != nil {
		buffer.WriteString("->")
		buffer.WriteString(p.rhs[0].String())
		for _, a := range p.rhs[1:] {
			buffer.WriteRune('|')
			buffer.WriteString(a.String())
		}
	}
	return buffer.String()
}

// CreateProduction creates a new production with a symbol
func CreateProduction(s Symbol) Production {
	return &production{
		label: s,
	}
}
