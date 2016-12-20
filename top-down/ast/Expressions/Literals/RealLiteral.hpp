
#ifndef REALLITERAL_HPP_
#define REALLITERAL_HPP_

#include <ast/Ast.hpp>
#include <ast/Type.hpp>

namespace hardware {
    class InstructionGenerator;
}
namespace ast {

    class RealLiteral : public Ast {

        public:
            RealLiteral(lexer::Lexer & lex, symtable::SymbolTable * table);

            virtual void Validate() const;
            virtual std::unique_ptr<hardware::Register> GenerateCode(hardware::InstructionGenerator & codeGen) const;
            virtual std::ostream& Write(std::ostream & os) const;

            ValueType ResultType() const;
            double  GetValue() const;

        private:
            double value;

    };
    
}

#endif