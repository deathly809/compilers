
#include <test/catch.hpp>

#include <symtable/SymbolTable.hpp>
#include <symtable/Attribute.hpp>

#include <iostream>

#include <exception>
#include <memory>


TEST_CASE( "SymbolTable is tested" , "[SymbolTable]" ) {
    symtable::SymbolTable sym;

    // All pointers are here
    std::shared_ptr<symtable::Attribute> s_attr(new symtable::StringAttribute("first_name", "jeffrey"));
    std::shared_ptr<symtable::Attribute> b_attr(new symtable::BooleanAttribute("is_male", true));
    std::shared_ptr<symtable::Attribute> r_attr(new symtable::Attribute());

    sym.Insert(s_attr);

    r_attr = sym.Locate("first_name");
    REQUIRE(r_attr->GetType() == symtable::StringAttributeType);

    r_attr = sym.Locate("last_name");
    REQUIRE(r_attr->GetType() == symtable::NilAttributeType);

    sym.OpenScope();
    r_attr = sym.Locate("first_name");
    REQUIRE(r_attr->GetType() == symtable::StringAttributeType);

    sym.Insert(b_attr);
    r_attr = sym.Locate("is_male");
    REQUIRE(r_attr->GetType() == symtable::BooleanAttributeType);

    std::shared_ptr<symtable::BooleanAttribute> r_bool = std::static_pointer_cast<symtable::BooleanAttribute,symtable::Attribute>(r_attr);
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
    r_attr = nullptr;
}
