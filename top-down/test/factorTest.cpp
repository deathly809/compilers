
#include "catch.hpp"

#include <ast/Expressions/Factor.hpp>
#include <Lexer.hpp>

#include <sstream>

TEST_CASE( "Testing factor parsing and verification" , "[FactorTest]" ) {
    std::stringstream ss;
    ss << "5 * 3";
    lexer::Lexer lex(new Scanner(ss));
    lex.HasNext();
    symtable::SymbolTable table;
    ast::Factor fact(lex, &table);
}