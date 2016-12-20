
#ifndef BLOCKDEFINITION_HPP_
#define BLOCKDEFINITION_HPP_

#include <ast/Ast.hpp>
#include <vector>

namespace hardware {
    class InstructionGenerator;
}

namespace ast {

    class Identifier;
    class Expression;
    
    class BlockDefinition : public Ast {

        struct BlockDecl {
            Identifier* id;
            Expression* expr;
        };

        private:
            bool variable;
            std::vector<BlockDecl> vars;

        public:
            BlockDefinition(lexer::Lexer & lex, symtable::SymbolTable * table);
            ~BlockDefinition();

            virtual void Validate() const;
            virtual std::unique_ptr<hardware::Register> GenerateCode(hardware::InstructionGenerator & codeGen) const;
            virtual std::ostream& Write(std::ostream& os) const;
            size_t VariablesDeclared() const;

    };
    
}

#endif