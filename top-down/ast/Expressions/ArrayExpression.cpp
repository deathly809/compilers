
#include <ast/Expressions/ArrayExpression.hpp>

#include <ast/Identifier.hpp>
#include <ast/Expressions/Expression.hpp>

namespace ast {

    ArrayExpression::ArrayExpression(lexer::Lexer & lex, symtable::SymbolTable * table) : Ast(table) {
        name = new Identifier(lex, table);
        consumeLexemeType(lex,lexer::O_BRACKET);
        index = new Expression(lex, table);
        consumeLexemeType(lex,lexer::C_BRACKET);
    }

    void ArrayExpression::Validate() const {
        name->Validate();
        index->Validate();
    }

    void ArrayExpression::GenerateCode(std::ostream & out) const {

    }

    std::ostream& ArrayExpression::Write(std::ostream & os) const {
        return os << *name << "[" << *index << "]";
    }

    ValueType ArrayExpression::ResultType() const {
        return NilType;
    }

}

