
#include <ast/Expressions/StringLiteral.hpp>

#include <lexer/Lexeme.hpp>
#include <lexer/LexemeTypes.hpp>

namespace ast {

    StringLiteral::StringLiteral(lexer::Lexer & lex, symtable::SymbolTable * table) : Ast(table) {
        auto l = lex.Next();
        lex.HasNext();
        
        value = l->GetValue();
    }

    void StringLiteral::Validate() const {
        /* Empty */
    }

    void StringLiteral::GenerateCode(std::ostream & out) const {
        /* Empty */
    }

    ValueType StringLiteral::ResultType() const {
        return StringType;
    }

    std::string StringLiteral::GetValue() const {
        return value;
    }

    std::ostream& StringLiteral::Write(std::ostream & os) const {
        return os << "\"" << GetValue() << "\"";
    }

}
