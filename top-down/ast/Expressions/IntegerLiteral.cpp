

#include <ast/Expressions/IntegerLiteral.hpp>

#include <Lexeme.hpp>
#include <LexemeTypes.hpp>

namespace ast {

    IntegerLiteral::IntegerLiteral(lexer::Lexer & lex, symtable::SymbolTable * table) : Ast(table) {
        auto l = lex.Next();
        lex.HasNext();
        
        value = Convert<int>(l->GetValue());
        
    }

    void IntegerLiteral::Validate() const {
        /* Empty */
    }

    void IntegerLiteral::GenerateCode(std::ostream & out) const {
        /* Empty */
    }

    ValueType IntegerLiteral::ResultType() const {
        return IntType;
    }

    int  IntegerLiteral::GetValue() const {
        return value;
    }

    std::ostream& IntegerLiteral::Write(std::ostream & os) const {
        return os << GetValue();
    }
}