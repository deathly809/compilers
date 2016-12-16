
#ifndef CONSTANTBLOCK_HPP_
#define CONSTANTBLOCK_HPP_

#include <ast/Ast.hpp>

#include <vector>

namespace ast {

    class Expression;
    class Identifier;

    class ConstantBlock : public Ast {
        
        struct VarPair {
            Identifier* lhs;
            Expression* rhs;
        };
        
        std::vector<VarPair> vars;

        public:
            ConstantBlock(lexer::Lexer & lex, symtable::SymbolTable* table);
            ~ConstantBlock();

            virtual void Validate() const;
            virtual void GenerateCode(std::ostream & out) const;
            virtual std::ostream& Write(std::ostream& os) const;

    };

}

#endif