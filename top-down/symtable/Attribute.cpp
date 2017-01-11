
#include <symtable/Attribute.hpp>

#include <iostream>
#include <map>
#include <string>

namespace symtable {

    std::map<AttributeType,std::string> attrKindMapping = {
        {IntAttributeType,"IntAttr"},
        {RealAttributeType,"RealAttr"},
        {StringAttributeType,"StringAttr"},
        {BooleanAttributeType,"BoolAttr"},
        {NilAttributeType,"NilAttr"},
        {VariableAttributeType,"VarAttr"},
        {FunctionAttributeType,"FuncAttr"}
    };

    std::map<IdentifierKind,std::string> identKindMappings = {
        {Var,"Var"},
        {Const,"Const"}
    };


    std::string& IdentifierKindToString(IdentifierKind idk) {
        auto ptr = identKindMappings.find(idk);
        return ptr->second;
    }

    std::string& AttributeTypeToString(AttributeType idk) {
        auto ptr = attrKindMapping.find(idk);
        return ptr->second;
    }

    Attribute::Attribute(std::string name, AttributeType type) : type(type), name(name), filename("nil"), line(-1), column(-1) {
        /* Empty */
    }

    Attribute::Attribute(std::string name, std::string filename, int line, int column, AttributeType type) : type(type), name(name), filename(filename), line(line), column(column) {
        /* Empty */
    }
            
    Attribute::Attribute() : type(NilAttributeType), name("NIL") {}
    Attribute::~Attribute() {}
    std::string Attribute::GetName() const { return name; }
    AttributeType Attribute::GetType() const { return type; }

    void Attribute::Write(std::ostream & os) const  {
        os << "[" << GetName() << ", " << AttributeTypeToString(GetType())  << "]"<<  std::endl;
    }
// Int

    IntAttribute::IntAttribute(std::string name, int value) : Attribute(name,IntAttributeType), value(value) {
        /* Empty */
    }

    int IntAttribute::GetValue() const {
        return value;
    }

    void IntAttribute::Write(std::ostream & os) const  {
        os << GetValue() << std::endl;
    }

// REAL

    RealAttribute::RealAttribute(std::string name, double value) : Attribute(name,RealAttributeType), value(value) {
        /* Empty */
    }

    double RealAttribute::GetValue() const {
        return value;
    }

    void RealAttribute::Write(std::ostream & os) const  {
        os << "[" << GetName() << ", " << GetValue() << "]" << std::endl;
    }


// STRING
            
    StringAttribute::StringAttribute(std::string name, std::string value) : Attribute(name,StringAttributeType), value(value) {
        /* Empty */
    }

    std::string StringAttribute::GetValue() const {
        return value;
    }

    void StringAttribute::Write(std::ostream & os) const  {
        os << "[" << GetName() << ", " << GetValue() << "]" << std::endl;
    }
    
    BooleanAttribute::BooleanAttribute(std::string name, bool value) : Attribute(name,BooleanAttributeType), value(value) {
        /* Empty */
    }

    bool BooleanAttribute::GetValue() const {
        return value;
    }

    void BooleanAttribute::Write(std::ostream & os) const  {
        if(GetValue()) {
            os << "[" << GetName() << ", true]" << std::endl;
        } else {
            os << "[" << GetName() << ", false]" << std::endl;
        }
    }

    NilAttribute::NilAttribute() : Attribute("nil",NilAttributeType) {
        /* Empty */
    }

    void NilAttribute::Write(std::ostream & os) const  {
        os << "[" << GetName() << ", Nil]" << std::endl;
    }


// VAR

    VariableAttribute::VariableAttribute(std::string name, std::string filename, int line, int column, IdentifierKind kind, ast::ValueType type, int size) : Attribute(name,filename, line, column, VariableAttributeType), size(size), iKind(kind), iType(type) {
        /* Empty */
    }

    IdentifierKind VariableAttribute::GetKind() const {
        return iKind;
    }

    ast::ValueType VariableAttribute::GetVariableType() const {
        return iType;
    }

    void VariableAttribute::SetVariableType(ast::ValueType type) {
        iType = type;
    }

    int VariableAttribute::GetSize() const {
        return size;
    }

    void VariableAttribute::SetSize(int n_size) {
        size = n_size;
    }

    void VariableAttribute::Write(std::ostream & os) const  {
        os << "[" << GetName() << ", " << IdentifierKindToString(iKind) << ", " << ast::ValueTypeToString(iType) << "," << size << "]";
        if(reg) {
            os << "@REG(" << reg->GetID() << ")";
        } else {
            os << "@REG(nullptr)";            
        }
    }

    void VariableAttribute::SetRegister(std::unique_ptr<hardware::Register> reg) {
        this->reg = std::move(reg);
    }

// FunctionAttribute

    FunctionAttribute::FunctionAttribute(std::string name, std::string filename, int line, int column, ast::ValueType type) : Attribute(name, filename, line, column, FunctionAttributeType), iType(type), label("NONE"), builtin(false) {
        /* Empty */
    }

    FunctionAttribute::FunctionAttribute(std::function<void(hardware::InstructionGenerator&)> gen, std::string name, ast::ValueType type) : Attribute(name, "builtin", -1, -1, FunctionAttributeType), iType(type), label("NONE") , builtin(true), gen(gen) {
        /* Empty */
    }

    ast::ValueType FunctionAttribute::GetReturnType() const {
        return iType;
    }
    void FunctionAttribute::SetReturnType(ast::ValueType type) {
        iType = type;
    }

    void FunctionAttribute::Write(std::ostream & os) const  {
        os << AttributeTypeToString(GetType()) << "[" << GetName() << ", " << ast::ValueTypeToString(iType) << "]@" << label;
    }

    void FunctionAttribute::SetLabel(std::string lbl) {
        label = lbl;
    }

    std::string FunctionAttribute::GetLabel() const {
        return label;
    }

    bool FunctionAttribute::IsBuiltIn() {
        return builtin;
    }
    void FunctionAttribute::GenerateCode(hardware::InstructionGenerator & codeGen) const {
        gen(codeGen);
    }



// OStream
    std::ostream& operator<<(std::ostream & os, const Attribute & attr) {
        attr.Write(os);
        return os;
    }

}