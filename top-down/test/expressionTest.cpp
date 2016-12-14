
#include "catch.hpp"

#include <ast/Expressions/Expression.hpp>
#include <Lexer.hpp>

#include <sstream>

TEST_CASE( "Test single integer" , "[Expression]" ) {
    std::stringstream ss;
    ss << "5";
    lexer::Lexer lex(new Scanner(ss));
    lex.HasNext();
    symtable::SymbolTable table;
    ast::Expression expr(lex, &table);
}
TEST_CASE( "Test single boolean" , "[Expression]" ) {
    std::stringstream ss;
    ss << "true";
    lexer::Lexer lex(new Scanner(ss));
    lex.HasNext();
    symtable::SymbolTable table;
    ast::Expression expr(lex, &table);
}

TEST_CASE( "Test single real" , "[Expression]" ) {
    std::stringstream ss;
    ss << "5.0";
    lexer::Lexer lex(new Scanner(ss));
    lex.HasNext();
    symtable::SymbolTable table;
    ast::Expression expr(lex, &table);
}

TEST_CASE( "integer addition" , "[Expression]" ) {
    std::stringstream ss;
    ss << "5 + 6";
    lexer::Lexer lex(new Scanner(ss));
    lex.HasNext();
    symtable::SymbolTable table;
    ast::Expression expr(lex, &table);
}

TEST_CASE( "integer division" , "[Expression]" ) {
    std::stringstream ss;
    ss << "5 / 6";
    lexer::Lexer lex(new Scanner(ss));
    lex.HasNext();
    symtable::SymbolTable table;
    ast::Expression expr(lex, &table);
    expr.Validate();
}

TEST_CASE( "integer subtraction" , "[Expression]" ) {
    std::stringstream ss;
    ss << "5 - 6";
    lexer::Lexer lex(new Scanner(ss));
    lex.HasNext();
    symtable::SymbolTable table;
    ast::Expression expr(lex, &table);
    expr.Validate();
}

TEST_CASE( "integer mod" , "[Expression]" ) {
    std::stringstream ss;
    ss << "5 % 6";
    lexer::Lexer lex(new Scanner(ss));
    lex.HasNext();
    symtable::SymbolTable table;
    ast::Expression expr(lex, &table);
    expr.Validate();
}


TEST_CASE( "integer with multiplication and division" , "[Expression]" ) {
    std::stringstream ss;
    ss << "5 * 6 / 4";
    lexer::Lexer lex(new Scanner(ss));
    lex.HasNext();
    symtable::SymbolTable table;
    ast::Expression expr(lex, &table);
    expr.Validate();
}
