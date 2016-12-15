
#include <ast/Identifier.hpp>

#include <Lexeme.hpp>
#include <LexemeTypes.hpp>

#include <iostream>

namespace ast {

        Identifier::Identifier(lexer::Lexer& lex, symtable::SymbolTable * table) : Ast(table) {
            lexeme = lex.Next();
            checkLexemeType(lexeme,lexer::ID);
            lex.HasNext();
        }

        Identifier::~Identifier() {
            delete lexeme;
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

        std::ostream& operator<<(std::ostream & os, const Identifier & id) {
            return os << id.GetName();
        }

}