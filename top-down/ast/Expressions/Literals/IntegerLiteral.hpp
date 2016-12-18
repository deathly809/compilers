
#ifndef INTEGERLITERAL_HPP_
#define INTEGERLITERAL_HPP_

#include <ast/Ast.hpp>
#include <ast/Type.hpp>

namespace ast {

    class IntegerLiteral : public Ast {
        
        public:
            IntegerLiteral(lexer::Lexer & lex, symtable::SymbolTable * table);

            virtual void Validate() const;
            virtual std::unique_ptr<hardware::Register> GenerateCode(std::ostream & out) const;
            virtual std::ostream& Write(std::ostream & os) const;

            ValueType ResultType() const;
            int  GetValue() const;

        private:
            int value;

    };
    
}

#endif