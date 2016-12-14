

#ifndef UTIL_HPP_
#define UTIL_HPP_

#include <Lexeme.hpp>
#include <LexemeTypes.hpp>

#include <string>
#include <sstream>

namespace lexer {
    class Lexeme;
}

namespace ast {

    // handles EOF checks
    void checkEOF(bool more);

    // validate the lexeme 
    #define checkLexemeType(l,expectedType) do {            \
        if(l == nullptr) {                                  \
            throw std::runtime_error(std::string(__FILE__)  \
                        + ":" + std::to_string(__LINE__)    \
                        + ", unexpected EOF");              \
        }                                                   \
                                                            \
        if(l->GetType() != expectedType) {                  \
            throw std::runtime_error(                       \
                std::string(__FILE__)                       \
                + ":" + std::to_string(__LINE__)            \
                + ", expected "                             \
                + LexemeTypeToString(expectedType)          \
                + " but found "                             \
                + LexemeTypeToString(l->GetType()));        \
        }                                                   \
    } while(0);

    // Validate the lexeme type and then free it
    #define consumeLexemeType(l,expectedType) do {          \
        checkLexemeType(l,expectedType);                    \
        delete l;                                           \
    } while(0);
    
    // convert from string to expected type
    template<class T>
    T Convert(std::string val ) {
        T result;
        std::stringstream ss;
        ss << val;
        ss >> result;
        return result;
    }
}

#endif