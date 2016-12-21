
#ifndef VARIABLEDECLARATION_HPP_
#define VARIABLEDECLARATION_HPP_

#include <ast/Statements/Statement.hpp>

#include <symtable/Attribute.hpp>

namespace hardware {
    class InstructionGenerator;
}

namespace ast {

    class Expression;
    class Identifier;
    class Type;

    class VariableDeclaration : public Statement {
        public:
            VariableDeclaration(lexer::Lexer &lex, symtable::SymbolTable * table);
            ~VariableDeclaration();
            
            virtual void Validate() const;
            virtual std::unique_ptr<hardware::Register> GenerateCode(hardware::InstructionGenerator & codeGen) const;
            virtual std::ostream& Write(std::ostream&) const;

        private:
            bool                        variable    = true;
            Type*                       type        = nullptr;
            Identifier*                 name        = nullptr;
            Expression*                 value       = nullptr;
            symtable::IdentifierKind    kind;

    };
}

#endif