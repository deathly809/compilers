

#include <constants.h>

char* conversions[] = {
    "int",
    "string",
    "char",
    "bool",
    "real",
    "nil"
};

const char* TypeAsString(Type t) {

    switch(t) {
        case IntType:
            return conversions[0];
        case StringType:
            return conversions[1];
        case CharType:
            return conversions[2];
        case BoolType:
            return conversions[3];
        case RealType:
            return conversions[4];
        case NilType:
            return conversions[5];
    }
    return 0;
}