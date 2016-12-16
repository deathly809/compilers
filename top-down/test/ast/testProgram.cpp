
#include <test/catch.hpp>
#include <test/runner.hpp>

#include <ast/Program.hpp>

TEST_CASE( "simple programs" , "[Program]" ) {
    SECTION("hello world") {
        run<ast::Program>(
            "func main() {"
            "   Println(\"Hello World\")"
            "}"
        );
    }

    SECTION("simple expressions") {
        SECTION("first") {
            run<ast::Program>(
                "func main() {"
                "   Println(5 + 6)"
                "}"
            );
        }
        SECTION("second") {
            run<ast::Program>(
                "func main() {"
                "    var x = 5 + 6"
                "}"
            );
        }
        SECTION("third") {
            run<ast::Program>(
                "func main() {"
                "   var x = 5 + 6"
                "   var y = x + 3"
                "}"
            );
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
            "    var x = readInt()"
            "    if x < 3 {"
            "    } else {"
            "    }"
            "}"
        );
    }
    SECTION("third") {
        run<ast::Program>(
            "func main() {"
            "    var x = readInt()"
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
            "    var x = readInt()"
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
        "   Println(fib(5))"
        "}"
    );
}

TEST_CASE("Program: constant blocks" , "[Program]") {
    run<ast::Program>(
        "const ("
        "   x = 10"
        "   y = 10"
        "   z = f(1)"
        ")"
    );
}

TEST_CASE("Program: variable blocks" , "[Program]") {
    run<ast::Program>(
        "var ("
        "   x = 10"
        "   y = 10"
        "   z = f(1)"
        ")"
    );
}

TEST_CASE("Program: Binary Search", "[Program]") {
    SECTION("middle") {
        run<ast::Program>(
            "func middle(a int, b int) int {"
            "   return (a + b) / 2"
            "}"
        );    
    }

    SECTION("bSearch") {
        run<ast::Program>(
            "func bSearch(val int, list []int, left int, right int) int {"
            "   if right < left {"
            "       return -1"
            "   }"
            "   var mid = middle(left,right)"
            "   if val == list[mid] {"
            "       return mid"
            "   }"
            "   if val < list[mid] {"
            "       return bSearch(val,list,left,mid)"
            "   }"
            "   return bSearch(val,list,mid + 1,right)"
            "}"
        );
    }

    SECTION("entire program") {
        run<ast::Program>(
            "func middle(a int, b int) int {"
            "   return (a + b) / 2"
            "}"
            "func bSearch(val int, list []int, left int, right int) int {"
            "   if right < left {"
            "       return -1"
            "   }"
            "   var mid = middle(left,right)"
            "   if val == list[mid] {"
            "       return mid"
            "   }"
            "   if val < list[mid] {"
            "       return bSearch(val,list,left,mid)"
            "   }"
            "   return bSearch(val,list,mid + 1,right)"
            "}"
        );
    }
}

TEST_CASE("Program: array assignment", "[Program]") {
    run<ast::Program>(
        "func main() {"
        "   var x [100]int"
        "   x[10] = x[6]"
        "}"
    );    
}
