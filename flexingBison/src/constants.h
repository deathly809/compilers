
#ifndef CONSTANTS_H_
#define CONSTANTS_H_

typedef enum {
    Variable, Constant, Function
} Modifier;


typedef enum {
    IntType = 0, StringType = 1, CharType = 2, BoolType = 4, RealType = 8, NilType = 16
} Type;

const char* TypeAsString(Type);

#endif
