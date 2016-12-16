
#ifndef TERM_HPP_
#define TERM_HPP_

#include <ast/Ast.hpp>

#include <ast/Type.hpp>

namespace ast {

    class Operator;
    class VName;

    class Term : public Ast {

        public:
            Term(lexer::Lexer & lex,symtable::SymbolTable * table);
            ~Term();

            virtual void Validate() const;
            virtual void GenerateCode(std::ostream & out) const;
            virtual std::ostream& Write(std::ostream & os) const;

            ValueType ResultType() const;

        private:
            VName*      lhs = nullptr;
            Operator*   op  = nullptr;
            Term*       rhs = nullptr;
            
    };

}

#endif