
#include <ast/Statements/Return.hpp>

#include <ast/Expressions/Expression.hpp>

namespace ast {
    Return::Return(lexer::Lexer& lex, symtable::SymbolTable * table) : Statement(table) {

    }

    Return::~Return() {
        delete result;
    }

    void Return::Validate() {
        if( result != nullptr) {
            result->Validate();
        }
    }

    void Return::GenerateCode(std::ostream & out) {

    }
}