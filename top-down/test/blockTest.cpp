
#include <catch.hpp>
#include <runner.hpp>

#include <ast/Block.hpp>

TEST_CASE("Block: assignment", "[Block]") {
    run<ast::Block>(
        "{"
        "   x = 5"
        "}"
    );
}

TEST_CASE("Block: var def", "[Block]") {
    SECTION("int") {
        run<ast::Block>(
            "{"
            "   var x = 5"
            "}"
        );
    }
    SECTION("bool") {
        run<ast::Block>(
            "{"
            "   var x = true"
            "}"
        );
    }
    SECTION("string") {
        run<ast::Block>(
            "{"
            "   var x = \"hi\""
            "}"
        );
    }
    SECTION("array index") {
        run<ast::Block>(
            "{"
            "   var x = y[5]"
            "}"
        );
    }
    SECTION("function") {
        run<ast::Block>(
            "{"
            "   var x = f(2)"
            "}"
        );
    }
}

TEST_CASE("Block: Binary Search", "[Block]") {
    SECTION("middle") {
        run<ast::Block>(
            "{"
            "   return (a + b) / 2"
            "}"
        );    
    }

    SECTION("bSearch 1") {
        run<ast::Block>(
            "{"
            "   if right < left {"
            "       return -1"
            "   }"
            "}"
        );
    }
    

    SECTION("bSearch 2") {
        run<ast::Block>(
            "{"
            "   if right < left {"
            "       return -1"
            "   }"
            "   var mid = middle(left,right)"
            "}"
        );
    }
    

    SECTION("bSearch 3") {
        run<ast::Block>(
            "{"
            "   if right < left {"
            "       return -1"
            "   }"
            "   var mid = middle(left,right)"
            "   if val == list[mid] {"
            "       return mid"
            "   }"
            "}"
        );
    }
    
    SECTION("bSearch 4") {
        run<ast::Block>(
            "{"
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
            "}"
        );
    }
    SECTION("bSearch all") {
        run<ast::Block>(
            "{"
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