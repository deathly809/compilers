

#include <ast/Expressions/BooleanLiteral.hpp>

#include <Lexeme.hpp>
#include <LexemeTypes.hpp>

namespace ast {

    BooleanLiteral::BooleanLiteral(lexer::Lexer & lex, symtable::SymbolTable * table) : Ast(table) {
        std::unique_ptr<lexer::Lexeme> l = lex.Next();
        lex.HasNext();
        
        std::string val = l->GetValue();
        
        consumeLexemeType(l,lexer::BOOL);

        if(val == "true") {
            value = true;
        } else if( val == "false") {
            value = false;
        } else {
            throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ", expected true or false but found " + val);
        }

    }

    void BooleanLiteral::Validate() const {
        /* Empty */
    }

    void BooleanLiteral::GenerateCode(std::ostream & out) const {
        /* Empty */
    }

    ValueType BooleanLiteral::ResultType() const {
        return BoolType;
    }

    bool  BooleanLiteral::GetValue() const {
        return value;
    }

    std::ostream& operator<<(std::ostream& os, const BooleanLiteral & bLit) {
        if(bLit.GetValue()) {
            return os << "true";
        }
        return os << "false";
    }

}
