
#ifndef SYMBOLTABLE_HPP_
#define SYMBOLTABLE_HPP_

#include <map>
#include <vector>
#include <string>

namespace symtable {

    enum AttributeType {IntAttributeType, RealAttributeType, StringAttributeType, BooleanAttributeType, NilAttributeType, VariableAttributeType };
    enum IdentifierKind { Const, Var };
    enum IdentifierType { IntegerType, StringType, ArrayType, RealType, BooleanType, None };

    class Attribute {
        private:
            AttributeType type;
            std::string name;
        protected:
            Attribute(std::string name, AttributeType type) : type(type), name(name) {
                /* Empty */
            }
            
        public:
            virtual ~Attribute(){};
            std::string GetName() { return name; };
            AttributeType GetType() { return type; };

    };

    class IntAttribute : public Attribute {
        private:
            int value;
        public:
            IntAttribute(std::string name, int value) : Attribute(name,IntAttributeType), value(value) {
                /* Empty */
            }

            int GetValue() const {
                return value;
            }
    };

    class RealAttribute : public Attribute {
        private:
            double value;
        public:
            RealAttribute(std::string name, double value) : Attribute(name,RealAttributeType), value(value) {
                /* Empty */
            }

            double GetValue() const {
                return value;
            }
            
    };

    class StringAttribute : public Attribute {
        private: 
                std::string value;
        public:
            StringAttribute(std::string name, std::string value) : Attribute(name,StringAttributeType), value(value) {
                /* Empty */
            }

            std::string GetValue() const {
                return value;
            }
    };

    class BooleanAttribute : public Attribute {
        private:
            bool value;

        public:
            BooleanAttribute(std::string name, bool value) : Attribute(name,BooleanAttributeType), value(value) {
                /* Empty */
            }

            bool GetValue() const {
                return value;
            }
    };

    class NilAttribute : public Attribute {
        public:
            NilAttribute() : Attribute("nil",NilAttributeType) {
                /* Empty */
            }
    };

    /* Holds information about attributes */
    class VariableAttribute : public Attribute {
        private:
            IdentifierKind iKind;
            IdentifierType iType;
        public:
            VariableAttribute(std::string name, IdentifierKind kind, IdentifierType type) : Attribute(name,VariableAttributeType), iKind(kind), iType(type) {
                /* Empty */
            }

            IdentifierKind GetKind() {
                return iKind;
            }

            IdentifierType GetType() {
                return iType;
            }
    };


    // SymbolTable holds information about symbols
    class SymbolTable {
        // Really only needed inside the class
        typedef std::map<std::string,Attribute*> Scope;

        private:
            std::vector<Scope> scopes;
            Scope global;
            NilAttribute nil;

        public:
            SymbolTable() {
                scopes.push_back(global);
            }

            ~SymbolTable() {
                for(auto && s : scopes) {
                    for(auto && elems : s) {
                        delete elems.second;
                    }
                }
                scopes.clear();
            }

            // Create a new scope
            void OpenScope() {
                scopes.push_back(Scope());
            }

            // Move to parent scope
            void CloseScope() {
                if(scopes.size() == 1) {
                    throw std::runtime_error("Cannot remove global scope.");
                }
                scopes.pop_back();
            }

            // Locate an identifer
            Attribute* Locate(std::string name) {
                for( int pos = scopes.size() - 1; pos > -1; pos-- ) {
                    Scope& s = scopes[pos];
                    auto finger = s.find(name);
                    if(finger != s.end()) {
                        return (finger->second);
                    }
                }
                return &nil;
            }

            // Insert an attribute into the symbol table.  The symbol table takes ownership.
            void Insert(Attribute* attr) {
                scopes[scopes.size() - 1].insert({attr->GetName(),attr});
            }

    };

}

#endif