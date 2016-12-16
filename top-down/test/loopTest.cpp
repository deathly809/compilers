

#include <catch.hpp>
#include <runner.hpp>

#include <ast/Statements/Loop.hpp>

TEST_CASE( "Loop: boolean w/ empty block" , "[Loop]" ) {
    run<ast::Loop>("for true { }");
    run<ast::Loop>("for false { }");
}

TEST_CASE( "Loop: boolean w/ non-empty block" , "[Loop]" ) {
    SECTION("first")  { run<ast::Loop>("for true  {var x := 5 + 5 var y := 6}"); }
    SECTION("second") { run<ast::Loop>("for false {var x := 5 + 5 var y := 6}"); }
    SECTION("third")  { run<ast::Loop>("for false {var x int x = x + 3}"); }
}

TEST_CASE( "Loop: conditionals w/ empty block" , "[Loop]" ) {
    run<ast::Loop>("for i < 3  {}");
    run<ast::Loop>("for 5 > (2 + 3) {}");
}

TEST_CASE( "Loop: conditionals w/ non-empty block" , "[Loop]" ) {
    run<ast::Loop>("for i < 3  { var x int x = 5 + 3}");
    run<ast::Loop>("for 5 > (2 + 3) { var x int x =  5 + 3}");
}

TEST_CASE( "Loop: init, test, incr w/ empty block" , "[Loop]" ) {
    run<ast::Loop>("for i = 1 ; i < 3; i = i + 1  { }");
    run<ast::Loop>("for var i := 1; i < 3; i = i + 1  {}");
    run<ast::Loop>("for i = f() ; i < 3; i = i + 1  { }");
    run<ast::Loop>("for var i := g(); i < 3; i = i + 1 { }" );
    run<ast::Loop>("for var i := g(); i < 3; i = i + 1 { }" );
    run<ast::Loop>("for var i := g(); i < 3 & i != 3 | i > 100; i = i + 1 {\n}", true);
}

TEST_CASE("Loop: nested", "[Loop]") {
    run<ast::Loop>("for i = 1 ; i < 3; i = i + 1  { for j = 2; j < i; j = j + 2 {} }", true);
    run<ast::Loop>("for i = 1 ; i < 3; i = i + 1  { if j < i {j = j + 2 } }", true);
}





