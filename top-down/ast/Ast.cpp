
#include <ast/Ast.hpp>

namespace ast {

    Ast::Ast(symtable::SymbolTable * table) : table(table) {
        /* Nothing to see */
    }

    Ast::~Ast() {
        /* Empty */
    }
}