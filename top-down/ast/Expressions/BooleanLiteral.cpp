

#include <ast/Expressions/BooleanLiteral.hpp>

#include <lexer/Lexeme.hpp>
#include <lexer/LexemeTypes.hpp>

namespace ast {

    BooleanLiteral::BooleanLiteral(lexer::Lexer & lex, symtable::SymbolTable * table) : Ast(table) {
        auto l = lex.Next();
        lex.HasNext();
        
        std::string val = l->GetValue();
        
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

    std::ostream& BooleanLiteral::Write(std::ostream& os) const {
        if(GetValue()) {
            return os << "true";
        }
        return os << "false";
    }

}
