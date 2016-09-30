package parsers

type symbol struct {
	value string
	prod  Production
}

func (s *symbol) Value() string {
	return s.value
}

func (s *symbol) GetProduction() Production {
	return s.prod
}

func (s *symbol) SetProduction(production Production) {
	s.prod = production
}

func (s *symbol) String() string {
	return s.value
}

// CreateSymbol teakes in a symbol name and boolean value which determines
// if the new symbol is a terminal or not
func CreateSymbol(name string) Symbol {
	return &symbol{
		value: name,
	}
}
