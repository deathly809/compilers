
#ifndef EXPRESSION_HPP_
#define EXPRESSION_HPP_

#include <ast/Ast.hpp>

#include <ast/Type.hpp>

namespace hardware {
    class InstructionGenerator;
}

namespace ast {

    class Factor;
    class Expression;
    class Operator;
    
    class Expression : public Ast {


        public:
            Expression(lexer::Lexer & lex, symtable::SymbolTable * table);
            ~Expression();

            virtual void Validate() const;
            virtual std::unique_ptr<hardware::Register> GenerateCode(hardware::InstructionGenerator & codeGen) const;
            virtual std::ostream& Write(std::ostream & os) const;

            ValueType ResultType() const;

        private:
            Factor*     lhs = nullptr;
            Expression* rhs = nullptr;
            Operator*   op  = nullptr;

    };

}

#endif