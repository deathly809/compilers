
#ifndef REALLITERAL_HPP_
#define REALLITERAL_HPP_

#include <ast/Ast.hpp>
#include <ast/Type.hpp>

namespace ast {

    class RealLiteral : public Ast {

        public:
            RealLiteral(lexer::Lexer & lex, symtable::SymbolTable * table);

            virtual void Validate() const;
            virtual void GenerateCode(std::ostream & out) const;
            virtual std::ostream& Write(std::ostream & os) const;

            ValueType ResultType() const;
            double  GetValue() const;

        private:
            double value;

    };
    
}

#endif