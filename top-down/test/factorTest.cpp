

#include <catch.hpp>

#include <ast/Expressions/Factor.hpp>
#include <Lexer.hpp>

#include <sstream>

TEST_CASE( "Testing single int" , "[FactorTest]" ) {
    std::stringstream ss;
    ss << "5";
    lexer::Lexer lex(new Scanner(ss));
    lex.HasNext();
    symtable::SymbolTable table;
    ast::Factor fact(lex, &table);
}

TEST_CASE( "Testing single bool" , "[FactorTest]" ) {
    std::stringstream ss;
    ss << "true";
    lexer::Lexer lex(new Scanner(ss));
    lex.HasNext();
    symtable::SymbolTable table;
    ast::Factor fact(lex, &table);
}

TEST_CASE( "Testing string" , "[FactorTest]" ) {
    std::stringstream ss;
    ss << "\"hi\"";
    lexer::Lexer lex(new Scanner(ss));
    lex.HasNext();
    symtable::SymbolTable table;
    ast::Factor fact(lex, &table);
}

TEST_CASE( "Testing multiplication" , "[FactorTest]" ) {
    std::stringstream ss;
    ss << "5 * 3";
    lexer::Lexer lex(new Scanner(ss));
    lex.HasNext();
    symtable::SymbolTable table;
    ast::Factor fact(lex, &table);
}

TEST_CASE( "Testing division" , "[FactorTest]" ) {
    std::stringstream ss;
    ss << "5 / 3";
    lexer::Lexer lex(new Scanner(ss));
    lex.HasNext();
    symtable::SymbolTable table;
    ast::Factor fact(lex, &table);
}

TEST_CASE( "Testing mod" , "[FactorTest]" ) {
    std::stringstream ss;
    ss << "5 % 3";
    lexer::Lexer lex(new Scanner(ss));
    lex.HasNext();
    symtable::SymbolTable table;
    ast::Factor fact(lex, &table);
}