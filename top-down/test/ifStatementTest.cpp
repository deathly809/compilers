

#include <catch.hpp>
#include <runner.hpp>

#include <ast/Statements/IfStatement.hpp>

TEST_CASE( "IfStatement: boolean w/ empty block" , "[IfStatement]" ) {
    run<ast::IfStatement>("if true { }");
    run<ast::IfStatement>("if false { }");
}

TEST_CASE( "IfStatement: boolean w/ non-empty block" , "[IfStatement]" ) {
    run<ast::IfStatement>("if true  {var x := 5 + 5 var y := 6}");
    run<ast::IfStatement>("if false {var x := 5 + 5 var y := 6}");
    run<ast::IfStatement>("if false {var x int x = x + 3}");
}

TEST_CASE( "IfStatement: conditionals w/ empty block" , "[IfStatement]" ) {
    run<ast::IfStatement>("if i < 3  {}");
    run<ast::IfStatement>("if 5 > (2 + 3) {}");
}

TEST_CASE( "IfStatement: conditionals w/ non-empty block" , "[IfStatement]" ) {
    run<ast::IfStatement>("if i < 3  { var x int x = 5 + 3}");
    run<ast::IfStatement>("if 5 > (2 + 3) { var x int x =  5 + 3}");
}

TEST_CASE( "IfStatement: boolean w/ empty true and false block" , "[IfStatement]" ) {
    run<ast::IfStatement>("if true { } else { }");
    run<ast::IfStatement>("if false { } else { }");
}

TEST_CASE( "IfStatement: boolean w/ non-empty blocks" , "[IfStatement]" ) {
    run<ast::IfStatement>("if true  {var x := 5 + 5 var y := 6} else { }");
    run<ast::IfStatement>("if true  {var x := 5 + 5 var y := 6} else { var x := 2 x = 7 }");
    run<ast::IfStatement>("if false {var x int x = x + 3} else { y = 7}");
    run<ast::IfStatement>("if false {var x int x = x + 3} else { y = f(y) }");
}

TEST_CASE( "IfStatement: conditionals w/ empty blocks" , "[IfStatement]" ) {
    run<ast::IfStatement>("if i < 3  {} else { }");
    run<ast::IfStatement>("if 5 > (2 + 3) {} else { }");
}

TEST_CASE( "IfStatement: conditionals w/ non-empty blocks" , "[IfStatement]" ) {
    run<ast::IfStatement>("if i < 3  { var x int x = 5 + 3} else { }");
    run<ast::IfStatement>("if 5 > (2 + 3) { var x int x =  5 + 3} else { }");
    run<ast::IfStatement>("if i < 3  { var x int x = 5 + 3} else {y = x }");
    run<ast::IfStatement>("if 5 > (2 + 3) { var x int x =  5 + 3} else { y = 5 + 5 }");
}


