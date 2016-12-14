
#ifndef INTEGERLITERAL_HPP_
#define INTEGERLITERAL_HPP_

#include <ast/Ast.hpp>

#include <Lexeme.hpp>
#include <LexemeTypes.hpp>

namespace ast {

    class IntegerLiteral : public Ast {
        public:
            IntegerLiteral(lexer::Lexer & lex, symtable::SymbolTable * table) : Ast(table) {
                lexer::Lexeme * l = lex.Next();
                lex.HasNext();
                std::string val = l->GetValue();
                consumeLexemeType(l,lexer::INT);
                value = Convert<int>(val);
            }

            virtual void Validate() {
                /* Empty */
            }

            virtual void GenerateCode(std::ostream & out) {
                /* Empty */
            }

            ValueType ResultType() {
                return IntType;
            }

            int  GetValue() {
                return value;
            }

        private:
            int value;

    };
}

#endif