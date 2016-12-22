
#ifndef LEXEMETYPEs_HPP_
#define LEXEMETYPEs_HPP_

enum LexemeTypes {
    COMMA, 
    QUOTE, D_QUOTE,
    O_BRACE, O_PAREN, O_BRACKET, 
    C_BRACE, C_PAREN, C_BRACKET, 
    FUNC, IF, ELSE, LOOP,
    LT, LTE, GT, GTE, NE, EQ,
    EQUAL,
    PLUS, MINUS, MUL, DIV, MOD, OR, AND,
    INT, STRING, BOOL,
    IDENT, INTEGER
};

#endif
