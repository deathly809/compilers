
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

TEST_CASE( "single value declaration" , "[VariableDeclaration]" ) {
    SECTION("integer") {
        run<ast::VariableDeclaration>("var x := 5");
    }
    SECTION("bool") {
        run<ast::VariableDeclaration>("var x := true");
        run<ast::VariableDeclaration>("var x := false");
    }
    SECTION("string") {
        run<ast::VariableDeclaration>("var x := \"this is a string which I hope is saved\"");
    }
}

TEST_CASE( "complex expression declaration" , "[VariableDeclaration]" ) {
    SECTION("integer") {
        run<ast::VariableDeclaration>("var x := 5 + 5");
    }
    SECTION("bool") {
        run<ast::VariableDeclaration>("var x := true | false");
        run<ast::VariableDeclaration>("var x := false & true");
    }
    SECTION("string") {
        run<ast::VariableDeclaration>("var x := \"this is a string which I hope is saved\" + \"concat hopefully\"");
    }
    SECTION("functions") {
        run<ast::VariableDeclaration>("var x := fib(5) + fib(4)");
    }
}