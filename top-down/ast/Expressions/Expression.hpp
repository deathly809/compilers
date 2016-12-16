
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

            virtual void Validate() const;
            virtual void GenerateCode(std::ostream & out) const;
            virtual std::ostream& Write(std::ostream & os) const;

            ValueType ResultType() const;

        private:
            Factor*     lhs = nullptr;
            Expression* rhs = nullptr;
            Operator*   op  = nullptr;

    };

}

#endif