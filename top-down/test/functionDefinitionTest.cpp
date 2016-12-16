
#include <catch.hpp>
#include <runner.hpp>

#include <ast/FunctionDefinition.hpp>

TEST_CASE( "simple FunctionDefinitions" , "[FunctionDefinition]" ) {
    SECTION("hello world") {
        run<ast::FunctionDefinition>(
            "func main() {"
            "    Println(\"Hello World\")"
            "}"
        );
    }

    SECTION("simple expressions") {
        SECTION("first") {
            run<ast::FunctionDefinition>(
                "func main() {"
                "    Println(5 + 5)"
                "}"
            );
        }
        SECTION("second") {
            run<ast::FunctionDefinition>(
                "func main() {"
                "    var x := 5"
                "}"
            );
        }
        SECTION("third") {
            run<ast::FunctionDefinition>(
                "func main() {"
                "    var x := 5"
                "    var y := 6 * x"
                "}"
            );
        }
    }
}

TEST_CASE("FunctionDefinition: recursion", "[FunctionDefinition]") {
    SECTION("fib") {
        run<ast::FunctionDefinition>(
            "func fib(n int) int {"
            "   if n < 2 {"
            "       return 1"
            "   }"
            "   return fib(n - 1) + fib(n -2)"
            "}"
        );
    }
}
