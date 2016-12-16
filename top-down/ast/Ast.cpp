
#include <ast/Ast.hpp>

namespace ast {

    Ast::Ast(symtable::SymbolTable * table) : table(table) {
        /* Nothing to see */
    }

    Ast::~Ast() {
        /* Empty */
    }

    std::ostream& operator<<(std::ostream & os, const Ast & ast) {
        return ast.Write(os);
    }

}