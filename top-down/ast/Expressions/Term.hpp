
#ifndef TERM_HPP_
#define TERM_HPP_

#include <ast/Ast.hpp>

#include <ast/Type.hpp>

namespace hardware {
    class InstructionGenerator;
}

namespace ast {

    class Operator;
    class VName;

    class Term : public Ast {

        public:
            Term(lexer::Lexer & lex,symtable::SymbolTable * table);
            ~Term();

            virtual void Validate() const;
            virtual std::unique_ptr<hardware::Register> GenerateCode(hardware::InstructionGenerator & codeGen) const;
            virtual std::ostream& Write(std::ostream & os) const;

            ValueType ResultType() const;

        private:
            VName*      lhs = nullptr;
            Operator*   op  = nullptr;
            Term*       rhs = nullptr;
            bool        isnot;
            
    };

}

#endif