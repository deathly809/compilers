
#include <test/catch.hpp>
#include <test/runner.hpp>

#include <ast/Expressions/Term.hpp>

TEST_CASE( "Test integer" , "[Term]" ) {
    run<ast::Term>("5");
}

TEST_CASE( "Test bool" , "[Term]" ) {
    run<ast::Term>("false");
}

TEST_CASE( "Test string" , "[Term]" ) {
    run<ast::Term>("\"test string\"");
}

TEST_CASE( "Test integer sub-expression" , "[Term]" ) {
    SECTION("singled nested") {
        run<ast::Term>("(5)");
    }
    SECTION("double nested") {
        run<ast::Term>("((5))");
    }
    SECTION("triple nested") {
        run<ast::Term>("(((5)))");
    }

}

TEST_CASE( "Test string sub-expression" , "[Term]" ) {
    SECTION("single nested") {
        run<ast::Term>("(\"parens everywhere\")");
    }
    SECTION("double nested") {
        run<ast::Term>("((\"parens everywhere\"))");
    }
    SECTION("triple nested") {
        run<ast::Term>("(((\"parens everywhere\")))");
    }
}

TEST_CASE( "Test bool sub-expression" , "[Term]" ) {
    SECTION("single nested") {
        run<ast::Term>("(true)");
    }
    SECTION("double nested") {
        run<ast::Term>("((true))");
    }
    SECTION("triple nested") {
        run<ast::Term>("(((true)))");
    }
}

TEST_CASE("dumb number nested parens" , "[Term]") {
    SECTION("integer") {
        run<ast::Term>("(((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((5)))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))");
    }
    SECTION("bool") {
        run<ast::Term>("(((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((false)))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))");
    }
    SECTION("string") {
        run<ast::Term>("(((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((\"this is the string\")))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))");
    }
    SECTION("function") {
        run<ast::Term>("(((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((f())))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))");
    }
}

TEST_CASE("Term: less than", "[Term]") {
    SECTION("integer") {
        run<ast::Term>("5 < 3");
        run<ast::Term>("50 < 3");
        run<ast::Term>("5 < 30");
        run<ast::Term>("-100 < 3");
    }
    SECTION("string") {
        run<ast::Term>("\"asdf\" < \"asdf\"");
        run<ast::Term>("\"a\" < \"a\"");
        run<ast::Term>("\"b\" < \"a\"");
        run<ast::Term>("\"\" < \"asdf\"");
    }
    SECTION("bool") {
        run<ast::Term>("true < true");
        run<ast::Term>("true < false");
        run<ast::Term>("false < true");
        run<ast::Term>("false < false");
    }
    SECTION("identifiers") {
        run<ast::Term>("a < b");
        run<ast::Term>("b < a");
        run<ast::Term>("_asdf < name");
        run<ast::Term>("star69 < number_of_stars");
    }
    SECTION("mixed") {
        run<ast::Term>("true < asdf");
        run<ast::Term>("true < 5");
        run<ast::Term>("5 < false");
        run<ast::Term>("5 < true");
        run<ast::Term>("5 < true");
        run<ast::Term>("false < 5");
    }
}

TEST_CASE("Term: less than or equal", "[Term]") {
    SECTION("integer") {
        run<ast::Term>("5 <= 3");
        run<ast::Term>("50 <= 3");
        run<ast::Term>("5 <= 30");
        run<ast::Term>("-100 <= 3");
    }
    SECTION("string") {
        run<ast::Term>("\"asdf\" <= \"asdf\"");
        run<ast::Term>("\"a\" <= \"a\"");
        run<ast::Term>("\"b\" <= \"a\"");
        run<ast::Term>("\"\" <= \"asdf\"");
    }
    SECTION("bool") {
        run<ast::Term>("true <= true");
        run<ast::Term>("true <= false");
        run<ast::Term>("false <= true");
        run<ast::Term>("false <= false");
    }
    SECTION("identifiers") {
        run<ast::Term>("a <= b");
        run<ast::Term>("b <= a");
        run<ast::Term>("_asdf <= name");
        run<ast::Term>("star69 <= number_of_stars");
    }
    SECTION("mixed") {
        run<ast::Term>("true <= asdf");
        run<ast::Term>("true <= 5");
        run<ast::Term>("5 <= false");
        run<ast::Term>("5 <= true");
        run<ast::Term>("5 <= true");
        run<ast::Term>("false <= 5");
    }
}

TEST_CASE("Term: greater than", "[Term]") {
    SECTION("integer") {
        run<ast::Term>("5 > 3");
        run<ast::Term>("50 > 3");
        run<ast::Term>("5 > 30");
        run<ast::Term>("-100 > 3");
    }
    SECTION("string") {
        run<ast::Term>("\"asdf\" > \"asdf\"");
        run<ast::Term>("\"a\" > \"a\"");
        run<ast::Term>("\"b\" > \"a\"");
        run<ast::Term>("\"\" > \"asdf\"");
    }
    SECTION("bool") {
        run<ast::Term>("true > true");
        run<ast::Term>("true > false");
        run<ast::Term>("false > true");
        run<ast::Term>("false > false");
    }
    SECTION("identifiers") {
        run<ast::Term>("a > b");
        run<ast::Term>("b > a");
        run<ast::Term>("_asdf > name");
        run<ast::Term>("star69 > number_of_stars");
    }
    SECTION("mixed") {
        run<ast::Term>("true > asdf");
        run<ast::Term>("true > 5");
        run<ast::Term>("5 > false");
        run<ast::Term>("5 > true");
        run<ast::Term>("5 > true");
        run<ast::Term>("false > 5");
    }
}

TEST_CASE("Term: greater than or equal", "[Term]") {
    SECTION("integer") {
        run<ast::Term>("5 >= 3");
        run<ast::Term>("50 >= 3");
        run<ast::Term>("5 >= 30");
        run<ast::Term>("-100 >= 3");
    }
    SECTION("string") {
        run<ast::Term>("\"asdf\" >= \"asdf\"");
        run<ast::Term>("\"a\" >= \"a\"");
        run<ast::Term>("\"b\" >= \"a\"");
        run<ast::Term>("\"\" >= \"asdf\"");
    }
    SECTION("bool") {
        run<ast::Term>("true >= true");
        run<ast::Term>("true >= false");
        run<ast::Term>("false >= true");
        run<ast::Term>("false >= false");
    }
    SECTION("identifiers") {
        run<ast::Term>("a >= b");
        run<ast::Term>("b >= a");
        run<ast::Term>("_asdf >= name");
        run<ast::Term>("star69 >= number_of_stars");
    }
    SECTION("mixed") {
        run<ast::Term>("true >= asdf");
        run<ast::Term>("true >= 5");
        run<ast::Term>("5 >= false");
        run<ast::Term>("5 >= true");
        run<ast::Term>("5 >= true");
        run<ast::Term>("false >= 5");
    }
}

TEST_CASE("Term: equal to", "[Term]") {
    SECTION("integer") {
        run<ast::Term>("5 == 3");
        run<ast::Term>("50 == 3");
        run<ast::Term>("5 == 30");
        run<ast::Term>("-100 == 3");
    }
    SECTION("string") {
        run<ast::Term>("\"asdf\" == \"asdf\"");
        run<ast::Term>("\"a\" == \"a\"");
        run<ast::Term>("\"b\" == \"a\"");
        run<ast::Term>("\"\" == \"asdf\"");
    }
    SECTION("bool") {
        run<ast::Term>("true == true");
        run<ast::Term>("true == false");
        run<ast::Term>("false == true");
        run<ast::Term>("false == false");
    }
    SECTION("identifiers") {
        run<ast::Term>("a == b");
        run<ast::Term>("b == a");
        run<ast::Term>("_asdf == name");
        run<ast::Term>("star69 == number_of_stars");
    }
    SECTION("mixed") {
        run<ast::Term>("true == asdf");
        run<ast::Term>("true == 5");
        run<ast::Term>("5 == false");
        run<ast::Term>("5 == true");
        run<ast::Term>("5 == true");
        run<ast::Term>("false == 5");
    }
}

TEST_CASE("Term: not equal to", "[Term]") {
    SECTION("integer") {
        run<ast::Term>("5 != 3");
        run<ast::Term>("50 != 3");
        run<ast::Term>("5 != 30");
        run<ast::Term>("-100 != 3");
    }
    SECTION("string") {
        run<ast::Term>("\"asdf\" != \"asdf\"");
        run<ast::Term>("\"a\" != \"a\"");
        run<ast::Term>("\"b\" != \"a\"");
        run<ast::Term>("\"\" != \"asdf\"");
    }
    SECTION("bool") {
        run<ast::Term>("true != true");
        run<ast::Term>("true != false");
        run<ast::Term>("false != true");
        run<ast::Term>("false != false");
    }
    SECTION("identifiers") {
        run<ast::Term>("a != b");
        run<ast::Term>("b != a");
        run<ast::Term>("_asdf != name");
        run<ast::Term>("star69 != number_of_stars");
    }
    SECTION("mixed") {
        run<ast::Term>("true != asdf");
        run<ast::Term>("true != 5");
        run<ast::Term>("5 != false");
        run<ast::Term>("5 != true");
        run<ast::Term>("5 != true");
        run<ast::Term>("false != 5");
    }
}
