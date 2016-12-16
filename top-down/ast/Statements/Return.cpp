
#include <ast/Statements/Return.hpp>

#include <ast/Expressions/Expression.hpp>

namespace ast {
    Return::Return(lexer::Lexer& lex, symtable::SymbolTable * table) : Statement(table) {

    }

    Return::~Return() {
        delete result;
    }

    void Return::Validate() const {
        if( result != nullptr) {
            result->Validate();
        }
    }

    void Return::GenerateCode(std::ostream & out) const {

    }

    std::ostream& Return::Write(std::ostream & os) const {
        os << "return";
        if(result != nullptr) {
            os << " " << *result;
        }
        return os;
    }

}