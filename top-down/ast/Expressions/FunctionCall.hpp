
#ifndef FUNCTIONCALL_HPP_
#define FUNCTIONCALL_HPP_

#include <ast/Ast.hpp>
#include <ast/Type.hpp>

#include <vector>

namespace hardware {
    class InstructionGenerator;
}

namespace ast {

    class Expression;
    class Identifier;
    
    class FunctionCall : public Ast {

        public:
            FunctionCall(lexer::Lexer& lex, symtable::SymbolTable * table);
            ~FunctionCall();

            virtual void Validate() const;
            virtual std::unique_ptr<hardware::Register> GenerateCode(hardware::InstructionGenerator & codeGen) const;
            virtual std::ostream& Write(std::ostream & os) const;

            ValueType ResultType() const;

        private:
            Identifier*                 functionName;
            std::vector<Expression*>    arguments;
            ValueType                   returnType;

    };
}

#endif
