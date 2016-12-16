
#include <test/catch.hpp>
#include <test/runner.hpp>

#include <ast/Statements/Assignment.hpp>

TEST_CASE( "single value assignment" , "[Assignment]" ) {
    SECTION("integer") {
        run<ast::Assignment>("x = 5");
    }
    SECTION("bool") {
        run<ast::Assignment>("x = true");
        run<ast::Assignment>("x = false");
    }
    SECTION("string") {
        run<ast::Assignment>("x = \"this is a string which I hope is saved\"");
    }
}

TEST_CASE( "complex expression assignment" , "[Assignment]" ) {
    SECTION("integer") {
        run<ast::Assignment>("x = 5 + 5");
    }
    SECTION("bool") {
        run<ast::Assignment>("x = true | false");
        run<ast::Assignment>("x = false & true");
    }
    SECTION("string") {
        run<ast::Assignment>("x = \"this is a string which I hope is saved\" + \"concat hopefully\"");
    }
    SECTION("functions") {
        run<ast::Assignment>("x = fib(5) + fib(4)");
    }
}
