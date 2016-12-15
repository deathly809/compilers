
#ifndef BLOCK_HPP_
#define BLOCK_HPP_

#include <ast/Ast.hpp>

#include <vector>

namespace ast {

    class Statement;

    class Block : public Ast {
        std::vector<Statement*> stmts;
        public:
            Block(lexer::Lexer & lex, symtable::SymbolTable * table);
            ~Block();
            
            virtual void Validate() const;
            virtual void GenerateCode(std::ostream & out) const;
    };
}

#endif