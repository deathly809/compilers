
#ifndef EXPRESSION_HPP_
#define EXPRESSION_HPP_

#include <ast/Ast.hpp>

#include <ast/Type.hpp>

namespace ast {

    class Factor;
    class Expression;
    class Operator;
    
    class Expression : public Ast {


        public:
            Expression(lexer::Lexer & lex, symtable::SymbolTable * table);
            ~Expression();

            virtual void Validate();
            virtual void GenerateCode(std::ostream & out);
            ValueType ResultType();

        private:
            Factor*     lhs;
            Expression* rhs;
            Operator*   op;
    };

}

#endif