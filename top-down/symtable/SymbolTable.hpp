
#ifndef SYMBOLTABLE_HPP_
#define SYMBOLTABLE_HPP_

#include <iostream>

#include <map>
#include <vector>
#include <string>

#include <memory>

namespace symtable {

    class Attribute;

    // SymbolTable holds information about symbols
    class SymbolTable {
        // Really only needed inside the class
        typedef std::map<std::string, std::shared_ptr<Attribute> > Scope;

        private:
            std::vector<Scope> scopes;
            Scope global;
            
        public:
            SymbolTable();
            ~SymbolTable();

            // Create a new scope
            void OpenScope();

            // Move to parent scope
            void CloseScope();

            // Locate an identifer
            std::shared_ptr<Attribute> Locate(std::string name);

            // Insert an attribute into the symbol table.  The symbol table takes ownership.
            void Insert(std::shared_ptr<Attribute> attr);

    };

}

#endif