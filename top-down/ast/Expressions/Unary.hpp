
#ifndef UNARY_HPP_
#define UNARY_HPP_

#include <ast/Ast.hpp>

#include <ast/Type.hpp>

namespace hardware {
    class InstructionGenerator;
}

namespace ast {

    class Operator;
    class VName;

    class Unary : public Ast {

        public:
            Unary(lexer::Lexer & lex,symtable::SymbolTable * table);
            ~Unary();

            virtual void Validate() const;
            virtual std::unique_ptr<hardware::Register> GenerateCode(hardware::InstructionGenerator & codeGen) const;
            virtual std::ostream& Write(std::ostream & os) const;

            ValueType ResultType() const;

        private:
            union {
                VName*      vname;
                Unary*      unary;
            } value;
            Operator*   op  = nullptr;            
    };

}

#endif