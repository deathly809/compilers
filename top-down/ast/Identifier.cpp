
#include <ast/Identifier.hpp>

#include <Lexeme.hpp>
#include <LexemeTypes.hpp>

#include <iostream>

namespace ast {

        Identifier::Identifier(lexer::Lexer& lex, symtable::SymbolTable * table) : Ast(table) {
            lexeme = lex.Next();
            checkLexemeType(lexeme,lexer::ID);
            std::cout << *lexeme << std::endl;
            lex.HasNext();
        }

        Identifier::~Identifier() {
            delete lexeme;
        }

        void Identifier::Validate() {
            /* Nothing to validate */
        }

        void Identifier::GenerateCode(std::ostream & out) {
            // Should be nothing to do
        }

        ValueType Identifier::ResultType() {
            return IntType;
        }

        std::string Identifier::GetName() {
            return lexeme->GetValue();
        }

}