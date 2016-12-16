
#include <test/catch.hpp>
#include <test/runner.hpp>

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
                "    var x = 5"
                "}"
            );
        }
        SECTION("third") {
            run<ast::FunctionDefinition>(
                "func main() {"
                "    var x = 5"
                "    var y = 6 * x"
                "}"
            );
        }
    }
}

TEST_CASE("FunctionDefinition: multiple params", "[FunctionDefinition]") {
    SECTION("first") {
        run<ast::FunctionDefinition>(
            "func max(a int, b int) int{"
            "   if a < b {"
            "       return b"
            "   }"
            "   return a"
            "}"
        );
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

TEST_CASE("FunctionDefinition: array parameters", "[FunctionDefinition]") {
    SECTION("int") {
        run<ast::FunctionDefinition>(
            "func test(a []int) {}"
        );
    }
    SECTION("bool") {
        run<ast::FunctionDefinition>(
            "func test(a []bool) {}"
        );
    }
    SECTION("string") {
        run<ast::FunctionDefinition>(
            "func test(a []string) {}"
        );
    }
    SECTION("int as second") {
        run<ast::FunctionDefinition>(
            "func test(a int, b[]int) {}"
        );
    }
    SECTION("bool as second") {
        run<ast::FunctionDefinition>(
            "func test(a int, b[]bool) {}"
        );
    }
    SECTION("string as second") {
        run<ast::FunctionDefinition>(
            "func test(a int, b[]string) {}"
        );
    }
    SECTION("bSearch") {
        run<ast::FunctionDefinition>(
            "func bSearch(val int, list []int, left int, right int) int {}"
        );
    }   
}
