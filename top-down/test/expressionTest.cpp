
#include "catch.hpp"

#include <ast/Expressions/Expression.hpp>
#include <Lexer.hpp>

#include <sstream>

TEST_CASE( "Testing math expression parsing and verification" , "[Expression]" ) {
    std::stringstream ss;
    ss << "5 + 6";
    lexer::Lexer lex(new Scanner(ss));
    lex.HasNext();
    symtable::SymbolTable table;
    ast::Expression expr(lex, &table);
}