
#ifndef CHARLITERAL_HPP_
#define CHARLITERAL_HPP_

#include <ast/Ast.hpp>
#include <ast/Type.hpp>

namespace hardware {
    class InstructionGenerator;
}

namespace ast {

    class CharLiteral : public Ast {
        public:
            CharLiteral(lexer::Lexer & lex, symtable::SymbolTable * table);

            virtual void Validate() const;
            virtual std::unique_ptr<hardware::Register> GenerateCode(hardware::InstructionGenerator & codeGen) const;
            virtual std::ostream& Write(std::ostream & os) const;

            ValueType ResultType() const;
            char  GetValue() const;

        private:
            char value;

    };
    
}

#endif