

#include <catch.hpp>
#include <runner.hpp>

#include <ast/Identifier.hpp>

TEST_CASE( "single character" , "[Identifier]" ) {
    SECTION("alphabet") {
        run<ast::Identifier>("a");
        run<ast::Identifier>("b");
        run<ast::Identifier>("c");
        run<ast::Identifier>("d");
    }
}
TEST_CASE( "multiple characters" , "[Identifier]" ) {
    run<ast::Identifier>("aa");
    run<ast::Identifier>("asdfasdf");
    run<ast::Identifier>("_asdfafas141434" , true );
    run<ast::Identifier>("___25lskjg_23243KjlJIJkL" , true );
}

