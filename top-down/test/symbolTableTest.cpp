
#include <catch.hpp>

#include <symtable/SymbolTable.hpp>

#include <exception>

#include <memory>

TEST_CASE( "SymbolTable is tested" , "[SymbolTable]" ) {
    symtable::SymbolTable sym;

    // All pointers are here
    std::unique_ptr<symtable::Attribute> s_attr = std::unique_ptr<symtable::StringAttribute>(new symtable::StringAttribute("first_name", "jeffrey"));
    std::unique_ptr<symtable::Attribute> b_attr = std::unique_ptr<symtable::BooleanAttribute>(new symtable::BooleanAttribute("is_male", true));
    std::shared_ptr<symtable::Attribute> r_attr = nullptr;

    sym.Insert(s_attr);

    r_attr = std::move(sym.Locate("first_name"));
    REQUIRE(r_attr->GetType() == symtable::StringAttributeType);

    r_attr = std::move(sym.Locate("last_name"));
    REQUIRE(r_attr->GetType() == symtable::NilAttributeType);

    sym.OpenScope();
    r_attr = std::move(sym.Locate("first_name"));
    REQUIRE(r_attr->GetType() == symtable::StringAttributeType);

    sym.Insert(b_attr);
    r_attr = std::move(sym.Locate("is_male"));
    REQUIRE(r_attr->GetType() == symtable::BooleanAttributeType);

    std::unique_ptr<symtable::BooleanAttribute> r_bool(dynamic_cast<symtable::BooleanAttribute*>(r_attr.get()));
    REQUIRE(r_bool->GetValue());

    r_attr = std::move(sym.Locate("first_name"));
    REQUIRE(r_attr->GetType() == symtable::StringAttributeType);


    sym.CloseScope();
    r_attr = std::move(sym.Locate("is_male"));
    REQUIRE(r_attr->GetType() == symtable::NilAttributeType);

    try {
        sym.CloseScope();
        REQUIRE(false);
    } catch(std::exception & e) {
        REQUIRE(true);
    }
    r_attr = nullptr;
}