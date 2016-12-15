
#include <catch.hpp>

#include <ast/Statements/VariableDeclaration.hpp>
#include <Lexer.hpp>

#include <sstream>

TEST_CASE( "Testing variable declaration parsing and verification" , "[VariableDeclaration]" ) {
    std::stringstream ss;
    ss << "var x := 5 + 6";
    lexer::Lexer lex(new Scanner(ss));
    lex.HasNext();
    symtable::SymbolTable table;
    ast::VariableDeclaration var(lex, &table);
}