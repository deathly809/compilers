
#ifndef REALLITERAL_HPP_
#define REALLITERAL_HPP_

#include <ast/Ast.hpp>

#include <Lexeme.hpp>
#include <LexemeTypes.hpp>

namespace ast {

    class RealLiteral : public Ast {

        public:
            RealLiteral(lexer::Lexer & lex, symtable::SymbolTable * table) : Ast(table) {
                lexer::Lexeme* l = lex.Next();
                lex.HasNext();

                std::string val = l->GetValue();
                value = Convert<double>(val);

                consumeLexemeType(l,lexer::REAL);

            }

            virtual void Validate() {
                /* Empty */
            }

            virtual void GenerateCode(std::ostream & out) {
                /* Empty */
            }

            ValueType ResultType() {
                return RealType;
            }

            double  GetValue() {
                return value;
            }

        private:
            double value;

    };
}

#endif