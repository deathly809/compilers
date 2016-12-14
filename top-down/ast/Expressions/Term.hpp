
#ifndef TERM_HPP_
#define TERM_HPP_

#include <ast/Ast.hpp>

#include <ast/Type.hpp>

namespace ast {

    class Expression;
    class BooleanLiteral;
    class IntegerLiteral;
    class RealLiteral;
    class StringLiteral;
    class FunctionCall;

    class Term : public Ast {

        public:
            Term(lexer::Lexer & lex,symtable::SymbolTable * table);
            ~Term();

            virtual void Validate();
            virtual void GenerateCode(std::ostream & out);
            ValueType ResultType();

        private:
            Expression*     expr = nullptr;

            BooleanLiteral* bLit = nullptr;
            IntegerLiteral* iLit = nullptr;
            RealLiteral*    rLit = nullptr;
            StringLiteral*  sLit = nullptr;

            FunctionCall*   fCall = nullptr;

    };

}

#endif