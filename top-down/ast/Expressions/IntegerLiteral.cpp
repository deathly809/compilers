

#include <ast/Expressions/IntegerLiteral.hpp>

#include <Lexeme.hpp>
#include <LexemeTypes.hpp>

namespace ast {

    IntegerLiteral::IntegerLiteral(lexer::Lexer & lex, symtable::SymbolTable * table) : Ast(table) {
        lexer::Lexeme * l = lex.Next();
        std::string val = l->GetValue();
        consumeLexemeType(l,lexer::INT);
        value = Convert<int>(val);
        lex.HasNext();
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

    std::ostream& operator<<(std::ostream & os, const IntegerLiteral & iLit) {
        return os << iLit.GetValue();
    }
}