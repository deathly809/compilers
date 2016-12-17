
#include <symtable/VariableRedefinition.hpp>
#include <sstream>

namespace symtable {

        VariableRedefinition::VariableRedefinition(std::string vname) : std::runtime_error("variable redefined"), name(vname) {
            /* Empty */
        }


    const char* VariableRedefinition::what() const throw() {
        std::ostringstream cnvt( "" );
        
        cnvt << runtime_error::what() << ": " << name << std::endl;
        return cnvt.str().c_str();
    }
}
