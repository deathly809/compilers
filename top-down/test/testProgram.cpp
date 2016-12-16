
#include <catch.hpp>
#include <runner.hpp>

#include <ast/Program.hpp>

TEST_CASE( "simple programs" , "[Program]" ) {
    SECTION("hello world") {
        run<ast::Program>("                 \
            func main() {                   \
                Println(\"Hello World\")    \
            }                               \
        ", true);
    }

    SECTION("simple expressions") {
        SECTION("first") {
            run<ast::Program>("                 \
                func main() {                   \
                    Println(5 + 6)              \
                }                               \
            ", true);
        }
        SECTION("second") {
            run<ast::Program>("                 \
                func main() {                   \
                    var x := 5 + 6              \
                }                               \
            ", true);
        }
        SECTION("third") {
            run<ast::Program>("                 \
                func main() {                   \
                    var x := 5 + 6              \
                    var y := x + 3              \
                }                               \
            ", true);
        }
    }
}

TEST_CASE("Program: conditionals", "[Program]") {
    SECTION("first") {
        run<ast::Program>(
            "func main() {"
            "    if x < 3 {"
            "    } else {"
            "    }"
            "}"
        );
    }
    SECTION("second") {
        run<ast::Program>(
            "func main() {"
            "    var x := readInt()"
            "    if x < 3 {"
            "    } else {"
            "    }"
            "}"
        );
    }
    SECTION("third") {
        run<ast::Program>(
            "func main() {"
            "    var x := readInt()"
            "    if x < 3 {"
            "        Println(\"less than 3\")"
            "    } else {"
            "        Println(\"greater than or equal to 3\")"
            "    }"
            "}"
        );
    }
    SECTION("fourth") {
        run<ast::Program>(
            "func main() {"
            "    var x := readInt()"
            "    if x < 3 {"
            "        if x == 2 {"
            "            Println(\"x is 2\")"
            "        } else {"
            "            Println(\"less than 2\")"
            "        }"
            "    } else {"
            "        Println(\"greater than or equal to 3\")"
            "    }"
            "}"
        );
    }
}


TEST_CASE("Program: fibonacci" , "[Program]") {
    run<ast::Program>(
        "func fib(n int) int {"
        "   if n < 2 {"
        "       return 1"
        "   } else {"
        "       return fib(n - 1) + fib(n - 2)"
        "   }"
        "}"
        "func main() {"
        "}"
    );
}

// */