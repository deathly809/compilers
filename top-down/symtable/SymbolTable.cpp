
#include <symtable/SymbolTable.hpp>
#include <symtable/Attribute.hpp>
#include <symtable/Scope.hpp>

#include <symtable/VariableRedefinition.hpp>

#include <iostream>

#include <map>
#include <vector>
#include <string>
#include <string>

#include <memory>

namespace symtable {

    SymbolTable::SymbolTable() {
        OpenScope();
    }

    SymbolTable::~SymbolTable() {
        scopes.clear();
    }

    // Create a new scope
    void SymbolTable::OpenScope() {
        scopes.push_back(std::shared_ptr<Scope>(new Scope(scopes.size())));
    }

    // Move to parent scope
    void SymbolTable::CloseScope() {
        if(scopes.size() == 1) {
            throw std::runtime_error("Cannot remove global scope.");
        }
        scopes.pop_back();
    }

    // Locate an identifer
    std::shared_ptr<Attribute> SymbolTable::Locate(std::string name) const {
        for( int pos = scopes.size() - 1; pos >= 0; --pos ) {

            std::shared_ptr<Scope> s = scopes[pos];

            auto ptr1 = s->GetFunctionAttribute(name);
            if(ptr1) {
                return ptr1;
            }

            auto ptr2 = s->GetVariableAttribute(name);
            if(ptr2) {
                return ptr2;
            }

        }
        return nullptr;
    }

    template<class After>
    std::shared_ptr<After> ConvertAttribute(std::shared_ptr<Attribute> b) {
        return std::static_pointer_cast<After,Attribute>(b);
    }

    // Insert an attribute into the symbol table.  The symbol table takes ownership.
    void SymbolTable::Insert(std::shared_ptr<Attribute> attr) {
        std::shared_ptr<Scope> scope = scopes[scopes.size() - 1];
        switch(attr->GetType()) {
            case FunctionAttributeType:
                scope->InsertFunction(ConvertAttribute<FunctionAttribute>(attr));
                break;
            case VariableAttributeType:
                scope->InsertVariable(ConvertAttribute<VariableAttribute>(attr));
                break;
            default:
                throw std::runtime_error("SymbolTable: unsupported type.  Function and Variable attributes supported.");
                break;
        }
    }

    size_t SymbolTable::CountType(AttributeType type) const {
        std::shared_ptr<Scope> scope = scopes.back();
        switch(type) {
            case FunctionAttributeType:
                return scope->FunctionCount();
            case VariableAttributeType:
                return scope->VariableCount();
            default:
                break;
        }
        return 0;
    }


    int SymbolTable::GetScopeIndex(std::string name) const {
        for(int i = scopes.size() - 1; i >= 0; --i) {

            if(scopes[i]->ContainsFunction(name)) {
                return i;
            }

            if(scopes[i]->ContainsVariable(name)) {
                return i;
            }

        }
        return -1;
    }

    // Given a name we find its position declaired among identical types
    int SymbolTable::GetPositionIndex(std::string name) const {
        int scopeId = GetScopeIndex(name);
        
        if(scopeId == -1) {
            return -1;
        }

        
        int index = scopes[scopeId]->FunctionIndex(name);
        if(index != -1) return index;

        return scopes[scopeId]->VariableIndex(name);

    }

    size_t SymbolTable::ScopeCount() const {
        return scopes.size();
    }

    const std::shared_ptr<Scope> SymbolTable::GetScope(size_t index) const {
        return scopes[index];
    }

    const std::shared_ptr<Scope> SymbolTable::GetDeclaringScope(std::string name) const {
        int idx = GetScopeIndex(name);
        if(idx == -1) {
            return nullptr;
        }

        return scopes[idx];
    }

    std::ostream& operator<<(std::ostream & os, const SymbolTable & table) {
        for(auto & s : table.scopes) {
            os << *s << std::endl;
        }
        return os;
    }

}
