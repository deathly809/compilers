
#include <ast/Expressions/RealLiteral.hpp>

#include <Lexeme.hpp>
#include <LexemeTypes.hpp>

namespace ast {

    RealLiteral::RealLiteral(lexer::Lexer & lex, symtable::SymbolTable * table) : Ast(table) {
        auto l = lex.Next();
        lex.HasNext();

        value = Convert<double>(l->GetValue());
    }

    void RealLiteral::Validate() const {
        /* Empty */
    }

    void RealLiteral::GenerateCode(std::ostream & out) const {
        /* Empty */
    }

    ValueType RealLiteral::ResultType() const {
        return RealType;
    }

    double  RealLiteral::GetValue() const {
        return value;
    }

    std::ostream& RealLiteral::Write(std::ostream & os) const {
        return os << GetValue();
    }
    

}
