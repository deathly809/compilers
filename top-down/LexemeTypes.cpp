
#include <LexemeTypes.hpp>

#include <map>

namespace lexer {
    std::map<LexemeType,std::string> typeMappings = {
        {ID,"ID"}, 
        {INT, "INT"},
        {REAL, "REAL"},
        {STRING, "STRING"},
        {O_PAREN, "O_PAREN"},
        {C_PAREN,"C_PAREN"},
        {O_BRACE, "O_BRACE"},
        {C_BRACE, "C_BRACE"},
        {O_BRACKET, "O_BRACKET"},
        {C_BRACKET,"C_BRACKET"}, 
        {LOOP,"LOOP"}, 
        {IF,"IF"},
        {ELSE, "ELSE"},
        {VAR, "VAR"},
        {CONST, "CONST"},
        {C_EQUAL , "C_EQUAL"},
        {EQUAL ,"EQUAL" },
        {D_EQUAL,"D_EQUAL"},
        {LT , "LT"},
        {LTE, "LTE"},
        {GT, "GT"},
        {GTE, "GTE"},
        {BANG ,"BANG"}, 
        {OR, "OR"},
        {AND, "AND"},
        {MUL, "MUL"},
        {DIV, "DIV"},
        {PLUS, "PLUS"},
        {MINUS, "MINUS"},
        {MOD, "MOD"},
        {PERIOD,"PERIOD" },
        {FUNC, "FUNC"},
        {RETURN, "RETURN"},
        {COMMA,"COMMA"}, 
        {NE,"NE"},
        {SEMI,"SEMI"}, 
        {UNDEF,"UNDEF"},
        {IMPORT,"IMPORT"},
        {PACKAGE,"PACKAGE"},
        {COLON,"COLON"},
        {ENDFILE,"EOF"}
    };

    std::string& LexemeTypeToString(lexer::LexemeType t) {
        return typeMappings.find(t)->second;
    }
    

}

std::ostream& operator<<(std::ostream & os, const lexer::LexemeType & type) {
    return os << LexemeTypeToString(type);
}