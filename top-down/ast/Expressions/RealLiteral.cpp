
#include <ast/Expressions/RealLiteral.hpp>

#include <Lexeme.hpp>
#include <LexemeTypes.hpp>

namespace ast {

    RealLiteral::RealLiteral(lexer::Lexer & lex, symtable::SymbolTable * table) : Ast(table) {
        std::unique_ptr<lexer::Lexeme> l = lex.Next();
        lex.HasNext();

        std::string val = l->GetValue();
        value = Convert<double>(val);

        consumeLexemeType(l,lexer::REAL);

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
