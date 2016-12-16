
#include <catch.hpp>
#include <runner.hpp>

#include <ast/Statements/Return.hpp>

TEST_CASE("Return: empty","[Return]") {
    run<ast::Return>("return");
}

TEST_CASE("Return: expression","[Return]") {
    run<ast::Return>("return 5 + 2 / 2", true);
}