
#include <symtable/SymbolTable.hpp>
#include <symtable/Attribute.hpp>

#include <symtable/VariableRedefinition.hpp>

#include <iostream>

#include <map>
#include <vector>
#include <string>
#include <string>

#include <memory>

namespace symtable {


    SymbolTable::SymbolTable() {
        scopes.push_back(global);
    }

    SymbolTable::~SymbolTable() {
        for(auto && s : scopes) {
            s.clear();
        }
        scopes.clear();
    }

    // Create a new scope
    void SymbolTable::OpenScope() {
        scopes.push_back(Scope());
    }

    // Move to parent scope
    void SymbolTable::CloseScope() {
        if(scopes.size() == 1) {
            throw std::runtime_error("Cannot remove global scope.");
        }

        auto back = scopes.back();
        back.clear();
        scopes.pop_back();
    }

    // Locate an identifer
    std::shared_ptr<Attribute> SymbolTable::Locate(std::string name) {
        for( int pos = scopes.size() - 1; pos > -1; pos-- ) {
            Scope& s = scopes[pos];
            auto finger = s.find(name);
            if(finger != s.end()) {
                return finger->second;
            }
        }
        return std::shared_ptr<Attribute>(new Attribute());
    }

    // Insert an attribute into the symbol table.  The symbol table takes ownership.
    void SymbolTable::Insert(std::shared_ptr<Attribute> attr) {
        auto & scope = scopes[scopes.size() - 1];
        auto ptr = scope.find(attr->GetName());
        if(ptr != scope.end()) {
            throw VariableRedefinition(attr->GetName(), attr->GetFilename(), attr->GetLine(), attr->GetColumn());
        }
        scope.insert({ attr->GetName(),std::move(attr)});
    }


    void SymbolTable::PrintScope() const {
        std::cout << scopes.size() << ": [";
        
        if(scopes.size() > 0) std::cout << std::endl;

        for( auto & v : scopes.back()) {
            auto s = v.second;
            std::cout << "\t" << *s << std::endl;
        }
        std::cout << "]" << std::endl;
    }
}
