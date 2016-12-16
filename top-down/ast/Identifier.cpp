
#include <ast/Identifier.hpp>

#include <lexer/Lexeme.hpp>
#include <lexer/LexemeTypes.hpp>

#include <iostream>

namespace ast {

        Identifier::Identifier(lexer::Lexer& lex, symtable::SymbolTable * table) : Ast(table) {
            lexeme = lex.Next();
            checkLexemeType(lexeme,lexer::ID);
            lex.HasNext();
        }

        Identifier::~Identifier() {
        }

        void Identifier::Validate() const {
            /* Nothing to validate */
        }

        void Identifier::GenerateCode(std::ostream & out) const {
            // Should be nothing to do
        }

        ValueType Identifier::ResultType() const {
            return IntType;
        }

        std::string Identifier::GetName() const {
            return lexeme->GetValue();
        }

        std::ostream& Identifier::Write(std::ostream & os) const {
            return os << GetName();
        }

}