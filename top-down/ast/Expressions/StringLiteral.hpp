
#ifndef STRINGLITERAL_HPP_
#define STRINGLITERAL_HPP_

#include <ast/Ast.hpp>

#include <Lexeme.hpp>
#include <LexemeTypes.hpp>

namespace ast {

    class StringLiteral : public Ast {

        public:
            StringLiteral(lexer::Lexer & lex, symtable::SymbolTable * table) : Ast(table) {
                lexer::Lexeme * l = lex.Next();
                lex.HasNext();
                
                value = l->GetValue();

                consumeLexemeType(l,lexer::STRING);
            }

            virtual void Validate() {
                /* Empty */
            }

            virtual void GenerateCode(std::ostream & out) {
                /* Empty */
            }

            virtual ValueType ResultType() {
                return StringType;
            }

            std::string GetValue() {
                return value;
            }

        private:
            std::string value;
    };

}

#endif