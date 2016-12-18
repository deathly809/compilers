
#include <symtable/VariableRedefinition.hpp>

#include <sstream>
#include <string>

namespace symtable {

    VariableRedefinition::VariableRedefinition(std::string vname, std::string file, int line, int column) : std::runtime_error("variable redefined"), name(vname), file(file), line(line), column(column) {
        /* Empty */
    }


    const char* VariableRedefinition::what() const throw() {
        std::ostringstream cnvt( "" );
        
        cnvt << runtime_error::what() << ": " << name << " file: " << file << " line: " << line << " column: " << column;

        std::string s = cnvt.str();
        s.copy(buffer,s.size());
        buffer[s.size()] = '\0';
        return buffer;
    }
}
