
#ifndef FUNCTIONDEFINITION_HPP_
#define FUNCTIONDEFINITION_HPP_

#include <ast/Ast.hpp>

#include <symtable/SymbolTable.hpp>

namespace hardware {
    class InstructionGenerator;
}

namespace ast {

    class Block;
    class Identifier;
    class Type;

    // FUNC ID ( OPT_PARAMS ) OPT_RET BLOCK
    class FunctionDefinition : public Ast {
        protected:
            
            struct Param {
                Identifier* ident;
                Type*       type;
            };

        private:
        
            Identifier*         functionName    = nullptr;
            std::vector<Param>  optParams;
            Type*               optRetType      = nullptr;
            Block*              block           = nullptr;

        public:
            FunctionDefinition(lexer::Lexer & lex, symtable::SymbolTable* table);
            ~FunctionDefinition();
            
            virtual void Validate() const;
            virtual std::unique_ptr<hardware::Register> GenerateCode(hardware::InstructionGenerator & codeGen) const;
            virtual std::ostream& Write(std::ostream & os) const;

    };

}

#endif