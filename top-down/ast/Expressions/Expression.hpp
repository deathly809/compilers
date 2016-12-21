
#ifndef EXPRESSION_HPP_
#define EXPRESSION_HPP_

#include <ast/Ast.hpp>

#include <ast/Type.hpp>

#include <vector>

namespace hardware {
    class InstructionGenerator;
}

namespace ast {

    class Factor;
    class Expression;
    class Operator;
    
    class Expression : public Ast {

        struct Pair {
            Factor* lhs;
            Operator* op;
        };

        public:
            Expression(lexer::Lexer & lex, symtable::SymbolTable * table);
            ~Expression();

            virtual void Validate() const;
            virtual std::unique_ptr<hardware::Register> GenerateCode(hardware::InstructionGenerator & codeGen) const;
            virtual std::ostream& Write(std::ostream & os) const;

            ValueType ResultType() const;

        private:
            std::vector<Pair> list;
            Factor*     rhs = nullptr;
            //Expression* rhs = nullptr;
            //Operator*   op  = nullptr;

    };

}

#endif