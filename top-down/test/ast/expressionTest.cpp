
#include <test/catch.hpp>
#include <test/runner.hpp>

#include <ast/Expressions/Expression.hpp>

TEST_CASE( "Expression: Test single integer" , "[Expression]" ) {
    run<ast::Expression>("5");
    run<ast::Expression>("50");
    run<ast::Expression>("2342652423");
    run<ast::Expression>("1023");
    run<ast::Expression>("-1");
}

TEST_CASE( "Expression: Test single character" , "[Expression]" ) {
    run<ast::Expression>("'5'");
    run<ast::Expression>("'a'");
    run<ast::Expression>("'b'");
    run<ast::Expression>("'c'");
    run<ast::Expression>("'%'");
    run<ast::Expression>("':'");
}

TEST_CASE( "Expression: Test single boolean" , "[Expression]" ) {
    run<ast::Expression>("true");
    run<ast::Expression>("false");
}

TEST_CASE( "Expression: integer addition" , "[Expression]" ) {
    run<ast::Expression>("5 + 6");
}

TEST_CASE( "Expression: integer division" , "[Expression]" ) {
    run<ast::Expression>("5 / 6");
}

TEST_CASE( "Expression: integer subtraction" , "[Expression]" ) {
    run<ast::Expression>("5 - 6");
}

TEST_CASE( "Expression: integer mod" , "[Expression]" ) {
    run<ast::Expression>("5 % 6");
}

TEST_CASE( "Expression: integer with multiplication and division" , "[Expression]" ) {
    run<ast::Expression>("5 * 6 / 4");
}

TEST_CASE( "Expression: parenthesis around integer" , "[Expression]" ) {
    run<ast::Expression>("(1123123)");
}

TEST_CASE( "Expression: parenthesis around string" , "[Expression]" ) {
    run<ast::Expression>("(\"hello world how are you?\")");
}

TEST_CASE( "Expression: parenthesis around bool" , "[Expression]" ) {
    run<ast::Expression>("(true)");
}

TEST_CASE( "Expression: function call with no arguments" , "[Expression]" ) {
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

TEST_CASE( "Expression: function with single argument" , "[Expression]" ) {
    SECTION("integer") {
        run<ast::Expression>("f(5)");
        run<ast::Expression>("f(-5242)");
        run<ast::Expression>("f(5222)");
        run<ast::Expression>("f(5424)");
    }
    SECTION("bool") {
        run<ast::Expression>("f(true)");
        run<ast::Expression>("f(false)");
    }
    SECTION("string") {
        run<ast::Expression>("f(\"\")");
        run<ast::Expression>("f(\"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa\")");
        run<ast::Expression>("f(\"12312312\")");
        run<ast::Expression>("f(\"f()\")", true);
        run<ast::Expression>("f(\"This is a string with an escaped string within: '\\\"escaped\\\"'  \")");
    }
    SECTION("character") {
        run<ast::Expression>("f('a')");
        run<ast::Expression>("f('&')");
        run<ast::Expression>("f('f')");
        run<ast::Expression>("f('(')");
        run<ast::Expression>("f('\\n')");
        run<ast::Expression>("f('\\t')");
    }
}

TEST_CASE( "Expression: function call with multiple arguments" , "[Expression]" ) {
    run<ast::Expression>("f(\"test\",false,5)");
}

TEST_CASE("Expression: very long identifiers" , "[Expression]") {
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
