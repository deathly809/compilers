
#include "catch.hpp"

#include <ast/Expressions/Term.hpp>
#include <Lexer.hpp>

#include <sstream>

TEST_CASE( "Testing term parsing and verification" , "[Term]" ) {
    std::stringstream ss;
    ss << "5";
    lexer::Lexer lex(new Scanner(ss));
    lex.HasNext();
    symtable::SymbolTable table;
    ast::Term term(lex, &table);
}