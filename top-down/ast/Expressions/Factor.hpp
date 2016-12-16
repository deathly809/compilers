
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

            virtual void Validate() const;
            virtual void GenerateCode(std::ostream & out) const;
            virtual std::ostream& Write(std::ostream & os) const;

            ValueType ResultType() const;

        private:
            Term*           lhs = nullptr;
            Factor*         rhs = nullptr;
            Operator*       op  = nullptr;

    };

}

#endif