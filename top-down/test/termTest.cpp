

#include <catch.hpp>

#include <ast/Expressions/Term.hpp>
#include <Lexer.hpp>

#include <sstream>

TEST_CASE( "Test integer" , "[Term]" ) {
    std::stringstream ss;
    ss << "5";
    lexer::Lexer lex(new Scanner(ss));
    lex.HasNext();
    symtable::SymbolTable table;
    ast::Term term(lex, &table);
}

TEST_CASE( "Test bool" , "[Term]" ) {
    std::stringstream ss;
    ss << "false";
    lexer::Lexer lex(new Scanner(ss));
    lex.HasNext();
    symtable::SymbolTable table;
    ast::Term term(lex, &table);
}

TEST_CASE( "Test string" , "[Term]" ) {
    std::stringstream ss;
    ss << "\"test string\"";
    lexer::Lexer lex(new Scanner(ss));
    lex.HasNext();
    symtable::SymbolTable table;
    ast::Term term(lex, &table);
}

TEST_CASE( "Test integer sub-expression" , "[Term]" ) {
    std::stringstream ss;
    ss << "(5)";
    lexer::Lexer lex(new Scanner(ss));
    lex.HasNext();
    symtable::SymbolTable table;
    ast::Term term(lex, &table);
}
/*

TEST_CASE( "Test string sub-expression" , "[Term]" ) {
    std::stringstream ss;
    ss << "(\"parens everywhere\")";
    lexer::Lexer lex(new Scanner(ss));
    lex.HasNext();
    symtable::SymbolTable table;
    ast::Term term(lex, &table);
}

TEST_CASE( "Test bool sub-expression" , "[Term]" ) {
    std::stringstream ss;
    ss << "(true)";
    lexer::Lexer lex(new Scanner(ss));
    lex.HasNext();
    symtable::SymbolTable table;
    ast::Term term(lex, &table);
}

*/