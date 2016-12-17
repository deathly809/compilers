
#ifndef BLOCKDEFINITION_HPP_
#define BLOCKDEFINITION_HPP_

#include <ast/Ast.hpp>
#include <vector>

namespace ast {

    class Identifier;
    class Expression;
    
    class BlockDefinition : public Ast {

        struct BlockDecl {
            Identifier* id;
            Expression* expr;
        };

        private:
            bool variable;
            std::vector<BlockDecl> vars;

        public:
            BlockDefinition(lexer::Lexer & lex, symtable::SymbolTable * table);
            ~BlockDefinition();

            virtual void Validate() const;
            virtual void GenerateCode(std::ostream & out) const;
            virtual std::ostream& Write(std::ostream& os) const;

    };
    
}

#endif