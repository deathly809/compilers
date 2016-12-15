
#ifndef INTEGERLITERAL_HPP_
#define INTEGERLITERAL_HPP_

#include <ast/Ast.hpp>
#include <ast/Type.hpp>

namespace ast {

    class IntegerLiteral : public Ast {
        public:
            IntegerLiteral(lexer::Lexer & lex, symtable::SymbolTable * table);

            virtual void Validate() const;
            virtual void GenerateCode(std::ostream & out) const;

            ValueType ResultType() const;
            int  GetValue() const;

        private:
            int value;

    };

    std::ostream& operator<<(std::ostream & os, const IntegerLiteral & iLit);
    
}

#endif