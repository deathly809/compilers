#include <ast/Statements/Assignment.hpp>

#include <ast/Expressions/Expression.hpp>
#include <ast/Identifier.hpp>

#include <Lexeme.hpp>
#include <LexemeTypes.hpp>

namespace ast {

    Assignment::Assignment(lexer::Lexer & lex, symtable::SymbolTable* table) : Statement(table) {
        lhs = new Identifier(lex, table);
        consumeLexemeType(lex.Next(),lexer::EQUAL);
        lex.HasNext();
        rhs = new Expression(lex, table);
    }

    Assignment::~Assignment() {
        delete lhs;
        delete rhs;
    }

    void Assignment::Validate() const {
        lhs->Validate();
        rhs->Validate();
    }

    void Assignment::GenerateCode(std::ostream & out) const {

    }

    std::ostream& Assignment::Write(std::ostream & os) const {
        return os << *lhs << " = " << *rhs;
    }

}