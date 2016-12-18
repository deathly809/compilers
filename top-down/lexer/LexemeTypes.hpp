
#ifndef LEXEMETYPES_HPP_
#define LEXEMETYPES_HPP_

#include <string>

namespace lexer {

    enum LexemeType { ID, CHAR, INT, REAL, STRING, BOOL,
                CHARTYPE, INTTYPE, REALTYPE, STRINGTYPE, BOOLTYPE,
                O_PAREN, C_PAREN, O_BRACE, C_BRACE, O_BRACKET, C_BRACKET, LOOP, IF,
                ELSE, VAR, CONST, C_EQUAL , EQUAL , D_EQUAL,
                LT , LTE, GT, GTE, BANG , OR, 
                AND, MUL, DIV, PLUS, MINUS, MOD, 
                PERIOD, FUNC, RETURN, COMMA, NE,
                SEMI, UNDEF, PACKAGE, IMPORT,COLON , TYPE, ENDFILE
    };

    std::string& LexemeTypeToString(LexemeType t);
    
}

std::ostream& operator<<(std::ostream & os, const lexer::LexemeType & type);

#endif