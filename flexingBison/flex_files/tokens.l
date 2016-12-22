%{
    #include <string>
    #include <LexemeTypes.hpp>
    #define SAVE_TOKEN yylval.string = new std::string(yytext, yyleng);    
    #define TOKEN(t) (yylval.token = t)
    extern "C" int yywrap() { }
%}

DIGIT   [0-9]
ID      [a-zA-Z_][a-zA-Z0-9_]*

%%

[ \t\n]                          ;
"\""                            return TOKEN(D_QUOTE);
"'"                             return TOKEN(QUOTE);
"int"                           TOKEN(INT);
"bool"                          TOKEN(BOOL);
"string"                        TOKEN(STRING);
"for"                           TOKEN(LOOP);
"if"                            TOKEN(IF);
"else"                          TOKEN(ELSE);
"func"                          TOKEN(FUNC);
DIGIT+                          yylval.intval = atoi(yytext); TOKEN(INTEGER);
ID                              yylval.string = new std::string(yytext,yyleng) TOKEN(IDENT);
"="                             TOKEN(EQUAL);
"=="                            TOKEN(EQ);
"!="                            TOKEN(NE);
"<"                             TOKEN(LT);
"<="                            TOKEN(LTE);
">"                             TOKEN(GT);
">="                            TOKEN(GTE);
"+"                             TOKEN(PLUS);
"-"                             TOKEN(MINUS);
"*"                             TOKEN(MUL);
"/"                             TOKEN(DIV);
"%"                             TOKEN(MOD);
"|"                             TOKEN(OR);
"&"                             TOKEN(AND);
"["                             TOKEN(O_BRACKET);
"]"                             TOKEN(C_BRACKET);
"{"                             TOKEN(O_BRACE);
"}"                             TOKEN(C_BRACE);
"("                             TOKEN(O_PAREN);
")"                             TOKEN(C_PAREN);
","                             TOKEN(COMMA);
.                               printf("Unknown token!\n"); yyterminate();

%%
