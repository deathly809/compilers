
#include <test/catch.hpp>
#include <test/runner.hpp>

#include <ast/Expressions/Factor.hpp>

TEST_CASE( "Testing int" , "[FactorTest]" ) {
    SECTION("single integer") {
    }
    SECTION("single multiplication") {
        run<ast::Factor>("5 * 1000");
    }
    SECTION("single division") {
        run<ast::Factor>("100 / 2");
    }
    SECTION("single mod") {
        run<ast::Factor>("5 % 1000");
    }
}

TEST_CASE( "Testing single bool" , "[FactorTest]" ) {
    run<ast::Factor>("true");
}

TEST_CASE( "Testing string" , "[FactorTest]" ) {
    run<ast::Factor>("\"hi\"");
}

TEST_CASE( "Testing multiplication" , "[FactorTest]" ) {
    run<ast::Factor>("5 * 3");
}

TEST_CASE( "Testing division" , "[FactorTest]" ) {
    run<ast::Factor>("5 / 3");
}

TEST_CASE( "Testing mod" , "[FactorTest]" ) {
    run<ast::Factor>("5 % 3");
}
