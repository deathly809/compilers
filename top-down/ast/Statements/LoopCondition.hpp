
#ifndef LOOPCONDITION_HPP_
#define LOOPCONDITION_HPP_

#include <ast/Ast.hpp>

namespace ast {

    class Expression;

    class LoopCondition : public Ast {
        public:
            LoopCondition(lexer::Lexer& lex, symtable::SymbolTable * table);
            ~LoopCondition();
            
            virtual void Validate() const;
            virtual void GenerateCode(std::ostream & out) const;
            virtual std::ostream& Write(std::ostream & os) const;
            
        private:
            std::vector<Expression*> exp;
        
    };

}

#endif