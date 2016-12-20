
#ifndef LOOP_HPP_
#define LOOP_HPP_

#include <ast/Statements/Statement.hpp>

namespace hardware {
    class InstructionGenerator;
}

namespace ast {
    
    class Block;
    class LoopCondition;
    
    class Loop : public Statement {
        private:
            LoopCondition*  cond;
            Block*          block;
        public:
            Loop(lexer::Lexer& lex, symtable::SymbolTable * table);
            ~Loop();
            
            virtual void Validate() const;
            virtual std::unique_ptr<hardware::Register> GenerateCode(hardware::InstructionGenerator & codeGen) const;
            virtual std::ostream& Write(std::ostream & os) const;

    };

}

#endif