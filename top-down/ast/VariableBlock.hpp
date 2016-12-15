
#ifndef VARIABLEBLOCK_HPP_
#define VARIABLEBLOCK_HPP_

#include <ast/Ast.hpp>
#include <vector>

namespace ast {

    class Expression;
    class Identifier;
    
    class VariableBlock : public Ast {

        struct VarPair {
            Identifier* lhs;
            Expression* rhs;
        };

        private:
            std::vector<VarPair> vars;

        public:
            VariableBlock(lexer::Lexer & lex, symtable::SymbolTable * table);
            ~VariableBlock();

            virtual void Validate() const;
            virtual void GenerateCode(std::ostream & out) const;

    };
    
}

#endif