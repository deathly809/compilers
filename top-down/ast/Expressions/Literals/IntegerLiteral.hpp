
#ifndef INTEGERLITERAL_HPP_
#define INTEGERLITERAL_HPP_

#include <ast/Ast.hpp>
#include <ast/Type.hpp>

namespace hardware {
    class InstructionGenerator;
}

namespace ast {

    class IntegerLiteral : public Ast {
        
        public:
            IntegerLiteral(int);
            IntegerLiteral(lexer::Lexer & lex, symtable::SymbolTable * table);

            virtual void Validate() const;
            virtual std::unique_ptr<hardware::Register> GenerateCode(hardware::InstructionGenerator & codeGen) const;
            virtual std::ostream& Write(std::ostream & os) const;

            ValueType ResultType() const;
            int  GetValue() const;

        private:
            int value;

    };
    
}

#endif