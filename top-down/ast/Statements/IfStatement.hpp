
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
            
            virtual void Validate() const;
            virtual std::unique_ptr<hardware::Register> GenerateCode(std::ostream & out) const;
            virtual std::ostream& Write(std::ostream & os) const;

        private:
            Expression* cond        = nullptr;
            Block*      trueBlock   = nullptr;
            Block*      falseBlock  = nullptr;

    };

}

#endif