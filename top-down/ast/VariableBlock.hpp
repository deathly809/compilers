
#ifndef VARIABLEBLOCK_HPP_
#define VARIABLEBLOCK_HPP_

#include <ast/Ast.hpp>
#include <vector>

namespace ast {

    class Assignment;
    
    class VariableBlock : public Ast {

        private:
            std::vector<Assignment*> vars;

        public:
            VariableBlock(lexer::Lexer & lex, symtable::SymbolTable * table);
            ~VariableBlock();

            virtual void Validate() const;
            virtual void GenerateCode(std::ostream & out) const;
            virtual std::ostream& Write(std::ostream& os) const;

    };
    
}

#endif