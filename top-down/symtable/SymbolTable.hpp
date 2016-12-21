
#ifndef SYMBOLTABLE_HPP_
#define SYMBOLTABLE_HPP_

#include <symtable/Attribute.hpp>

#include <iostream>

#include <map>
#include <vector>
#include <string>

#include <memory>

namespace symtable {

    class Scope;

    // SymbolTable holds information about symbols
    class SymbolTable {

        public:
            SymbolTable();
            ~SymbolTable();

            // Create a new scope
            void OpenScope();

            // Move to parent scope
            void CloseScope();

            // Locate an identifer
            std::shared_ptr<Attribute> Locate(std::string name) const;

            // Insert an attribute into the symbol table.  The symbol table takes ownership.
            void Insert(std::shared_ptr<Attribute> attr);

            // Given a name we find its numerical scope
            int GetScopeIndex(std::string name) const;

            // Given a name we find its position declaired among identical types
            int GetPositionIndex(std::string name) const;

            size_t CountType(AttributeType type) const;

            const std::shared_ptr<Scope> GetScope(size_t index) const;

            const std::shared_ptr<Scope> GetDeclaringScope(std::string name) const;

            size_t ScopeCount() const;

        private:
            std::vector<std::shared_ptr<Scope>> scopes;
            
            friend std::ostream& operator<<(std::ostream & os, const SymbolTable & table);

    };

    std::ostream& operator<<(std::ostream & os, const SymbolTable & table);

}

#endif