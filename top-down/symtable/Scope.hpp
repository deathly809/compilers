
#ifndef SCOPE_HPP_
#define SCOPE_HPP_

#include <string>
#include <memory>
#include <vector>
#include <map>

namespace symtable {

    class FunctionAttribute;
    class VariableAttribute;

    class Scope {

        public:
            
            bool ContainsFunction(std::string) const;
            bool ContainsVariable(std::string) const;

            int  FunctionIndex(std::string) const;
            int  VariableIndex(std::string) const;

            void InsertFunction(std::shared_ptr<FunctionAttribute>);
            void InsertVariable(std::shared_ptr<VariableAttribute>);

            std::shared_ptr<FunctionAttribute> GetFunctionAttribute(std::string) const;
            std::shared_ptr<VariableAttribute> GetVariableAttribute(std::string) const;

            size_t FunctionCount() const;
            size_t VariableCount() const;

        private:
            // list of functions
            std::vector<std::shared_ptr<FunctionAttribute>> functions;

            // list of variables
            std::vector<std::shared_ptr<VariableAttribute>> variables;

            // quick way to look up where an attribute is located
            std::map<std::string,int> varLookup;
            std::map<std::string,int> funcLookup;

            friend std::ostream& operator<<(std::ostream & os, const Scope & scope);
    };

    std::ostream& operator<<(std::ostream & os, const Scope & scope);


}

#endif