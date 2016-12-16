
#ifndef VARIABLEDECLARATION_HPP_
#define VARIABLEDECLARATION_HPP_

#include <ast/Statements/Statement.hpp>


namespace ast {

    class Expression;
    class Identifier;
    class Type;

    class VariableDeclaration : public Statement {
        public:
            VariableDeclaration(lexer::Lexer &lex, symtable::SymbolTable * table);
            ~VariableDeclaration();
            
            virtual void Validate() const;
            virtual void GenerateCode(std::ostream & out) const;

        private:
            bool        variable    = true;
            Type*       type        = nullptr;
            Identifier* name        = nullptr;
            Expression* value       = nullptr; 

            friend std::ostream& operator<<(std::ostream & os, const VariableDeclaration & varDef);

    };

    std::ostream& operator<<(std::ostream & os, const VariableDeclaration & varDef);
}

#endif