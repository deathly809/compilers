
#include <test/catch.hpp>
#include <test/runner.hpp>

#include <ast/Expressions/Expression.hpp>

TEST_CASE( "Test single integer" , "[Expression]" ) {
    run<ast::Expression>("5");
    run<ast::Expression>("50");
    run<ast::Expression>("2342652423");
    run<ast::Expression>("1023");
    run<ast::Expression>("-1");
}
TEST_CASE( "Test single boolean" , "[Expression]" ) {
    run<ast::Expression>("true");
    run<ast::Expression>("false");
}

TEST_CASE( "integer addition" , "[Expression]" ) {
    run<ast::Expression>("5 + 6");
}

TEST_CASE( "integer division" , "[Expression]" ) {
    run<ast::Expression>("5 / 6");
}

TEST_CASE( "integer subtraction" , "[Expression]" ) {
    run<ast::Expression>("5 - 6");
}

TEST_CASE( "integer mod" , "[Expression]" ) {
    run<ast::Expression>("5 % 6");
}

TEST_CASE( "integer with multiplication and division" , "[Expression]" ) {
    run<ast::Expression>("5 * 6 / 4");
}

TEST_CASE( "parenthesis around integer" , "[Expression]" ) {
    run<ast::Expression>("(1123123)");
}

TEST_CASE( "parenthesis around string" , "[Expression]" ) {
    run<ast::Expression>("(\"hello world how are you?\")");
}

TEST_CASE( "parenthesis around bool" , "[Expression]" ) {
    run<ast::Expression>("(true)");
}

TEST_CASE( "function call" , "[Expression]" ) {
    SECTION("single letter function") {
        run<ast::Expression>("f()");
    }

    SECTION("underscore function") {
        run<ast::Expression>("_()");
    }

    SECTION("multiple letter function") {
        run<ast::Expression>("fibo()");
    }
}

TEST_CASE( "function with arguments" , "[Expression]" ) {
    run<ast::Expression>("f(5)");
}

TEST_CASE( "function call with multiple arguments" , "[Expression]" ) {
    run<ast::Expression>("f(\"test\",false,5)");
}

TEST_CASE("very very long identifiers" , "[Expression]") {
    SECTION("function") {
        run<ast::Expression>("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa(\"test\",false,5)");
    }

    SECTION("identifier") {
        run<ast::Expression>("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
    }
}

TEST_CASE("Expression: arrays") {
    SECTION("simple") {
        run<ast::Expression>("asd[5]", true);
        run<ast::Expression>("asd[a]", true);
    }
}
