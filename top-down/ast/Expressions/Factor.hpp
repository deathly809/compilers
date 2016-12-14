
#ifndef FACTOR_HPP_
#define FACTOR_HPP_

#include <ast/Ast.hpp>
#include <ast/Type.hpp>

namespace ast {

    class Term;
    class Factor;
    class Operator;

    class Factor : public Ast {

        public:
            Factor(lexer::Lexer & lex,symtable::SymbolTable * table);
            ~Factor();

            virtual void Validate();
            virtual void GenerateCode(std::ostream & out);
            ValueType ResultType();

        private:
            Term*           lhs;
            Factor*         rhs;
            Operator*       op;
    };

}

#endif