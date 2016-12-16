
#include <catch.hpp>
#include <runner.hpp>

#include <ast/Statements/VariableDeclaration.hpp>

TEST_CASE( "empty declaration" , "[VariableDeclaration]" ) {
    SECTION("integer") {
        run<ast::VariableDeclaration>("var x int");
    }
    SECTION("bool") {
        run<ast::VariableDeclaration>("var x bool");
    }
    SECTION("string") {
        run<ast::VariableDeclaration>("var x string");
    }
}