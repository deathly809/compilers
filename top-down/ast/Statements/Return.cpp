
#include <ast/Statements/Return.hpp>

#include <ast/Expressions/Expression.hpp>

#include <Lexer.hpp>
#include <Lexeme.hpp>
#include <LexemeTypes.hpp>


namespace ast {
    Return::Return(lexer::Lexer& lex, symtable::SymbolTable * table) : Statement(table) {
        consumeLexemeType(lex.Next(),lexer::RETURN)
        lex.HasNext();
        if(NextType(lex) != lexer::C_BRACE && NextType(lex) != lexer::ENDFILE) {
            result = new Expression(lex,table);
        }
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