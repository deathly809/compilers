
#include <ast/Expressions/StringLiteral.hpp>

#include <Lexeme.hpp>
#include <LexemeTypes.hpp>

namespace ast {

    StringLiteral::StringLiteral(lexer::Lexer & lex, symtable::SymbolTable * table) : Ast(table) {
        std::unique_ptr<lexer::Lexeme>  l = lex.Next();
        lex.HasNext();
        
        value = l->GetValue();

        consumeLexemeType(l,lexer::STRING);
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

    std::ostream& operator<<(std::ostream & os, const StringLiteral & sLit) {
        return os << sLit.GetValue();
    }

}
