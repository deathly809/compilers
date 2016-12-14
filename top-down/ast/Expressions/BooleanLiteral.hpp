
#ifndef BOOLEANLITERAL_HPP_
#define BOOLEANLITERAL_HPP_

#include <ast/Ast.hpp>

#include <Lexeme.hpp>
#include <LexemeTypes.hpp>

namespace ast {

    class BooleanLiteral : public Ast {

        public:
            BooleanLiteral(lexer::Lexer & lex, symtable::SymbolTable * table) : Ast(table) {
                lexer::Lexeme* l = lex.Next();
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

                consumeLexemeType(l, lexer::BOOL);
            }

            virtual void Validate() {
                /* Empty */
            }

            virtual void GenerateCode(std::ostream & out) {
                /* Empty */
            }

            ValueType ResultType() {
                return BoolType;
            }

            bool  GetValue() {
                return value;
            }

        private:
            bool value;

    };
}

#endif