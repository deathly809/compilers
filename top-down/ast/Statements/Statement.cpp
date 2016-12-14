

#include <ast/Statements/Statement.hpp>

namespace ast {

    Statement::Statement(symtable::SymbolTable * table) : Ast(table) {
        /* Empty */
    }

    Statement* Statement::Parse(lexer::Lexer & lex, symtable::SymbolTable * table) {
        throw std::runtime_error("uninitialized method");
    }

}