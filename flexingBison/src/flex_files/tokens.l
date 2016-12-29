%{

    #define YY_DECL extern "C" int yylex()
    extern "C" int yywrap() { }

    #include <string.h>
    #include <bison_files/grammar.tab.h>
    #define SAVE_TOKEN yylval.string = strdup(yytext);    
%}

%%

[ \t\n]                          ;
"\""                            { return D_QUOTE;}
"'"                             { return QUOTE;}
"int"                           { return INT;}
"bool"                          { return BOOL;}
"string"                        { return STRING;}
"for"                           { return LOOP;}
"if"                            { return IF;}
"else"                          { return ELSE;}
"func"                          { return FUNC;}
"var"                           { return VAR;}
"const"                         { return CONST;}
"return"                        { return RETURN; }
[0-9]+                          { yylval.integer = atoi(yytext); return INTEGER;}
[[:alpha:]_][[:alnum:]_]*       { SAVE_TOKEN return IDENT;}
"="                             { return EQUAL;}
"=="                            { return EQ;}
"!="                            { return NE;}
"<"                             { return LT;}
"<="                            { return LTE;}
">"                             { return GT;}
">="                            { return GTE;}
"+"                             { return PLUS;}
"++"                            { return D_PLUS;}
"-"                             { return MINUS;}
"--"                            { return D_MINUS;}
"*"                             { return MUL;}
"/"                             { return DIV;}
"%"                             { return MOD;}
"|"                             { return OR;}
"&"                             { return AND;}
"["                             { return O_BRACKET;}
"]"                             { return C_BRACKET;}
"{"                             { return O_BRACE;}
"}"                             { return C_BRACE;}
"("                             { return O_PAREN;}
")"                             { return C_PAREN;}
","                             { return COMMA;}
";"                             { return SEMI;}
.                               { printf("Unknown token: %s\n",yytext); yyterminate(); }

%%
