
#ifndef LOOPCONDITION_HPP_
#define LOOPCONDITION_HPP_

#include <ast/Ast.hpp>

namespace ast {

    class Expression;

    class LoopCondition : public Ast {
        public:
            LoopCondition(lexer::Lexer& lex, symtable::SymbolTable * table);
            ~LoopCondition();
            
            virtual void Validate();
            virtual void GenerateCode(std::ostream & out);
            
        private:
            std::vector<Expression*> exp;
        
    };

}

#endif