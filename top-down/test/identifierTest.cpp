

#include <catch.hpp>

#include <ast/Identifier.hpp>
#include <Lexer.hpp>

#include <sstream>

TEST_CASE( "single alphabet character" , "[Identifier]" ) {
    std::stringstream ss;
    ss << "a";
    lexer::Lexer lex(new Scanner(ss));
    lex.HasNext();
    symtable::SymbolTable table;
    ast::Identifier id(lex, &table);
}

