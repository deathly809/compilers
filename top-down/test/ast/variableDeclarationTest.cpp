
#include <test/catch.hpp>
#include <test/runner.hpp>

#include <ast/Statements/VariableDeclaration.hpp>

TEST_CASE( "empty declaration" , "[VariableDeclaration]" ) {
    SECTION("integer") {
        run<ast::VariableDeclaration>("var x int");
    }
    SECTION("bool") {
        run<ast::VariableDeclaration>("var x bool");
    }
    SECTION("string") {
        run<ast::VariableDeclaration>("var x string");
    }
}

TEST_CASE( "single value declaration" , "[VariableDeclaration]" ) {
    SECTION("integer") {
        run<ast::VariableDeclaration>("var x = 5");
    }
    SECTION("bool") {
        run<ast::VariableDeclaration>("var x = true");
        run<ast::VariableDeclaration>("var x = false");
    }
    SECTION("string") {
        run<ast::VariableDeclaration>("var x = \"this is a string which I hope is saved\"");
    }
}

TEST_CASE( "complex expression declaration" , "[VariableDeclaration]" ) {
    SECTION("integer") {
        run<ast::VariableDeclaration>("var x = 5 + 5");
    }
    SECTION("bool") {
		SECTION("or") {
				run<ast::VariableDeclaration>("var x = true | false");
		}
		SECTION("and") {
				run<ast::VariableDeclaration>("var x = false & true");
		}
    }
    SECTION("string") {
        run<ast::VariableDeclaration>("var x = \"this is a string which I hope is saved\" + \"concat hopefully\"");
    }
    SECTION("functions") {
        run<ast::VariableDeclaration>("var x = fib(5) + fib(4)");
    }
}

TEST_CASE("VariableDeclaration: Arrays", "[VariableDeclaration]") {
    SECTION("int") {
        run<ast::VariableDeclaration>("var x [10]int");
    }
    SECTION("bool") {
        run<ast::VariableDeclaration>("var x [10]bool");
    }
    SECTION("string") {
        run<ast::VariableDeclaration>("var x [10]string");
    }
}
