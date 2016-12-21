
#include <symtable/Scope.hpp>

#include <symtable/Attribute.hpp>

namespace symtable {

    bool Scope::ContainsFunction(std::string name) const {
        return FunctionIndex(name) != -1;
    }

    bool Scope::ContainsVariable(std::string name) const {
        return VariableIndex(name) != -1;
    }

    int  Scope::FunctionIndex(std::string name) const {
        const auto & ptr = funcLookup.find(name);

        if(ptr == funcLookup.end()) {
            return -1;
        }

        return ptr->second;
    }

    int  Scope::VariableIndex(std::string name) const {
        const auto & ptr = varLookup.find(name);

        if(ptr == varLookup.end()) {
            return -1;
        }
        return ptr->second;
    }

    void Scope::InsertFunction(std::shared_ptr<FunctionAttribute> attr) {
        
        if(ContainsFunction(attr->GetName())) {
            throw std::runtime_error("Cannot redefine function: " + attr->GetName());
        }

        funcLookup.insert({attr->GetName(),functions.size()});
        functions.push_back(attr);

    }

    void Scope::InsertVariable(std::shared_ptr<VariableAttribute> attr) {

        if(ContainsVariable(attr->GetName())) {
            throw std::runtime_error("Cannot redefine variable: " + attr->GetName());
        }

        varLookup.insert({attr->GetName(),functions.size()});
        variables.push_back(attr);
    }

    std::shared_ptr<FunctionAttribute> Scope::GetFunctionAttribute(std::string name) const {
        int idx = FunctionIndex(name);
        if(idx == -1) {
            return nullptr;
        }
        return functions[idx];
    }

    std::shared_ptr<VariableAttribute> Scope::GetVariableAttribute(std::string name) const {
        int idx = VariableIndex(name);
        if(idx == -1) {
            return nullptr;
        }
        return variables[idx];
    }

    size_t Scope::FunctionCount() const {
        return functions.size();
    }

    size_t Scope::VariableCount() const {
        return variables.size();
    }

    std::ostream& operator<<(std::ostream & os, const Scope & scope) {
        for( auto & v : scope.variables) {
            os << *v << " ";
        }
        for( auto & f : scope.functions) {
            os << *f << " ";
        }
        return os;
    }

}