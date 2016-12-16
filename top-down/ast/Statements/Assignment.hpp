
#ifndef ASSIGNMENT_HPP_
#define ASSIGNMENT_HPP_

#include <ast/Statements/Statement.hpp>

namespace ast {

    class Identifier;
    class Expression;

    class Assignment : public Statement {
            
        public:
            Assignment(lexer::Lexer & lex, symtable::SymbolTable* table);
            ~Assignment();

            virtual void Validate() const;
            virtual void GenerateCode(std::ostream & out) const;
            virtual std::ostream& Write(std::ostream & os) const;

        private:
            Identifier*     lhs = nullptr;
            Expression*     rhs = nullptr;
            Expression*     index = nullptr;
    };


}

#endif