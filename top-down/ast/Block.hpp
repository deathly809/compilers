
#ifndef BLOCK_HPP_
#define BLOCK_HPP_

#include <ast/Ast.hpp>

#include <vector>

namespace hardware {
    class InstructionGenerator;
}

namespace ast {

    class Block : public Ast {

        std::vector<Ast*> stmts;
        
        public:
            Block(lexer::Lexer & lex, symtable::SymbolTable * table);
            ~Block();
            
            virtual void Validate() const;
            virtual std::unique_ptr<hardware::Register> GenerateCode(hardware::InstructionGenerator & codeGen) const;
            virtual std::ostream& Write(std::ostream& os) const;
    };
}

#endif