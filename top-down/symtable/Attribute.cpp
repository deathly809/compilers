
#include <symtable/Attribute.hpp>

#include <iostream>

namespace symtable {

    Attribute::Attribute(std::string name, AttributeType type) : type(type), name(name) {
        /* Empty */
    }
            
    Attribute::Attribute() : type(NilAttributeType), name("NIL") {}
    Attribute::~Attribute() {}
    std::string Attribute::GetName() { return name; }
    AttributeType Attribute::GetType() { return type; }


    IntAttribute::IntAttribute(std::string name, int value) : Attribute(name,IntAttributeType), value(value) {
        /* Empty */
    }

    int IntAttribute::GetValue() const {
        return value;
    }


    RealAttribute::RealAttribute(std::string name, double value) : Attribute(name,RealAttributeType), value(value) {
        /* Empty */
    }

    double RealAttribute::GetValue() const {
        return value;
    }
            
            
    StringAttribute::StringAttribute(std::string name, std::string value) : Attribute(name,StringAttributeType), value(value) {
        /* Empty */
    }

    std::string StringAttribute::GetValue() const {
        return value;
    }
    
    BooleanAttribute::BooleanAttribute(std::string name, bool value) : Attribute(name,BooleanAttributeType), value(value) {
        /* Empty */
    }

    bool BooleanAttribute::GetValue() const {
        return value;
    }

    NilAttribute::NilAttribute() : Attribute("nil",NilAttributeType) {
        /* Empty */
    }

    VariableAttribute::VariableAttribute(std::string name, IdentifierKind kind, IdentifierType type) : Attribute(name,VariableAttributeType), iKind(kind), iType(type) {
        /* Empty */
    }

    IdentifierKind VariableAttribute::GetKind() {
        return iKind;
    }

    IdentifierType VariableAttribute::GetVariableType() {
        return iType;
    }

}