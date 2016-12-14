
#include <ast/Util.hpp>

#include <Lexeme.hpp>

namespace ast {

    void checkEOF(bool value) {
        if(!value) {
            throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ", unexpected EOF");
        }
    }
    
}