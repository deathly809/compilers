
#ifndef IFSTATEMENT_HPP_
#define IFSTATEMENT_HPP_

#include <ast/Statements/Statement.hpp>

namespace ast {

    class Expression;
    class Block;

    class IfStatement : public Statement {
        public:
            IfStatement(lexer::Lexer & lex, symtable::SymbolTable * table);
            ~IfStatement();
            
            virtual void Validate();
            virtual void GenerateCode(std::ostream & out);

        private:
            Expression* cond        = nullptr;
            Block*      trueBlock   = nullptr;
            Block*      falseBlock  = nullptr;
    };

}

#endif