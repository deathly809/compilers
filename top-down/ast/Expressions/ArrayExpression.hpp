
#ifndef ARRAYEXPRESSION_HPP_
#define ARRAYEXPRESSION_HPP_

#include <ast/Ast.hpp>

#include <ast/Type.hpp>

namespace hardware {
    class InstructionGenerator;
}

namespace ast {

    class Identifier;
    class Expression;

    class ArrayExpression : public Ast {

        private:
            Identifier* name;
            Expression* index;

        public:
            ArrayExpression(lexer::Lexer & lex, symtable::SymbolTable * table);

            virtual void Validate() const;
            virtual std::unique_ptr<hardware::Register> GenerateCode(hardware::InstructionGenerator & codeGen) const;
            virtual std::ostream& Write(std::ostream & os) const;

            virtual ValueType ResultType() const;



    };
}

#endif