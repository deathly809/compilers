
#ifndef CONSTANTBLOCK_HPP_
#define CONSTANTBLOCK_HPP_

#include <ast/Ast.hpp>
#include <vector>

namespace ast {

    class Assignment;

    class ConstantBlock : public Ast {
        
        private:
            std::vector<Assignment*> vars;

        public:
            ConstantBlock(lexer::Lexer & lex, symtable::SymbolTable* table);
            ~ConstantBlock();

            virtual void Validate() const;
            virtual void GenerateCode(std::ostream & out) const;
            virtual std::ostream& Write(std::ostream& os) const;

    };

}

#endif