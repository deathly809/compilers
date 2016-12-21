
#ifndef LOOPCONDITION_HPP_
#define LOOPCONDITION_HPP_

#include <ast/Ast.hpp>

namespace hardware {
    class InstructionGenerator;
}

namespace ast {

    class InitStatement;
    class Expression;
    class Assignment;

    class LoopCondition : public Ast {
        public:
            LoopCondition(lexer::Lexer& lex, symtable::SymbolTable * table);
            ~LoopCondition();
            
            virtual void Validate() const;
            virtual std::unique_ptr<hardware::Register> GenerateCode(hardware::InstructionGenerator & codeGen) const;
            virtual std::ostream& Write(std::ostream & os) const;

            InitStatement*  GetInit() const;
            Expression*     GetCondition() const;
            Assignment*     GetUpdate() const;
            
        private:
            InitStatement*  init = nullptr;
            Expression*     cond = nullptr;
            Assignment*     incr = nullptr;
        
    };

}

#endif