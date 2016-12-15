
#ifndef LOOP_HPP_
#define LOOP_HPP_

#include <ast/Statements/Statement.hpp>

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
            virtual void GenerateCode(std::ostream & out) const;
    };

}

#endif