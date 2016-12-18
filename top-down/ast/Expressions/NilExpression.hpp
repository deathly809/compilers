
#ifndef NILEXPRESSION_HPP_
#define NILEXPRESSION_HPP_ 

#include <exception>
#include <stdexcept>
#include <sstream>

namespace ast {

    class NilExpression : public std::runtime_error {

        public:
            NilExpression(const char* file, int line) : std::runtime_error("expression has no return type"), file(std::string(file)), line(line) {
                /* Empty */
            }

            virtual const char* what() const throw() {
                std::ostringstream cnvt( "" );
                cnvt << runtime_error::what() << ": " << file << "(" << line << ")";

                auto str = cnvt.str();
                std::copy(str.begin(),str.end(),buffer);
                buffer[str.size()] = '\0';
                
                return buffer;
            }

        private:
        
            const std::string file;
            const int line;
            mutable char buffer[512];

    };

}

#endif
