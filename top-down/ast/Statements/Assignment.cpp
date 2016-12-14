#include <ast/Statements/Assignment.hpp>

#include <ast/Expressions/Expression.hpp>
#include <ast/Identifier.hpp>

#include <Lexeme.hpp>
#include <LexemeTypes.hpp>

namespace ast {

    Assignment::Assignment(lexer::Lexer & lex, symtable::SymbolTable* table) : Statement(table) {
        lhs = new Identifier(lex, table);
        consumeLexemeType(lex.Next(),lexer::C_EQUAL);
        rhs = new Expression(lex, table);
    }

    Assignment::~Assignment() {
        delete lhs;
        delete rhs;
    }

    void Assignment::Validate() {
        lhs->Validate();
        rhs->Validate();
    }

    void Assignment::GenerateCode(std::ostream & out) {

    }

}