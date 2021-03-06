
#ifndef VARIABLEREDEFINITION_HPP_
#define VARIABLEREDEFINITION_HPP_

#include <exception>
#include <stdexcept>


namespace symtable {

    class VariableRedefinition : public std::runtime_error {

        private:
            VariableRedefinition() = delete;

        public:
            VariableRedefinition(std::string vname, std::string file, int line, int column);
            virtual const char* what() const throw();

        private:
            std::string name;
            std::string file;
            int line;
            int column;
            mutable char buffer[512];
    };
}

#endif