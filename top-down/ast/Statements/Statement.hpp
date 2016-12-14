
#ifndef STATEMENT_HPP_
#define STATEMENT_HPP_

#include <ast/Ast.hpp>

namespace ast {
    class Statement : public Ast {
        public:
            Statement(symtable::SymbolTable * table);
            ~Statement() {}
            static Statement* Parse(lexer::Lexer & lex, symtable::SymbolTable * table);
    };

}

#endif