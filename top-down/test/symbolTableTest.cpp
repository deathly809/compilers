
#include <catch.hpp>

#include <symtable/SymbolTable.hpp>

#include <exception>

TEST_CASE( "SymbolTable is tested" , "[SymbolTable]" ) {
    symtable::SymbolTable sym;

    // All pointers are here
    symtable::StringAttribute* s_attr = new symtable::StringAttribute("first_name", "jeffrey");
    symtable::BooleanAttribute* b_attr = new symtable::BooleanAttribute("is_male", true);

    sym.Insert(s_attr);
    symtable::Attribute* r_attr = sym.Locate("first_name");
    REQUIRE(r_attr->GetType() == symtable::StringAttributeType);

    r_attr = sym.Locate("last_name");
    REQUIRE(r_attr->GetType() == symtable::NilAttributeType);

    sym.OpenScope();
    r_attr = sym.Locate("first_name");
    REQUIRE(r_attr->GetType() == symtable::StringAttributeType);

    sym.Insert(b_attr);
    r_attr = sym.Locate("is_male");
    REQUIRE(r_attr->GetType() == symtable::BooleanAttributeType);
    symtable::BooleanAttribute* r_bool = dynamic_cast<symtable::BooleanAttribute*>(r_attr);
    REQUIRE(r_bool->GetValue());

    r_attr = sym.Locate("first_name");
    REQUIRE(r_attr->GetType() == symtable::StringAttributeType);


    sym.CloseScope();
    r_attr = sym.Locate("is_male");
    REQUIRE(r_attr->GetType() == symtable::NilAttributeType);

    try {
        sym.CloseScope();
        REQUIRE(false);
    } catch(std::exception & e) {
        REQUIRE(true);
    }
    
}