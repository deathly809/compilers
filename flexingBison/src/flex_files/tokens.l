%{

    #define YY_DECL extern "C" int yylex()
    extern "C" int yywrap() { }

    #include <bison_files/grammar.tab.h>
    #include <string.h>

    #if 0
        #define DISP fprintf(stderr,"%s\n",yytext); fflush(stdout);
    #else
        #define DISP
    #endif
%}


tmp     [\n](" "|"\t")*

%%

[ \t]                           ;
"#".*                           ;
{tmp}                           { yylineno++; return EOL; }
"\""                            { DISP; return D_QUOTE;}
"'"                             { DISP; return QUOTE;}
"true"                          { DISP; return TRUE; }
"false"                         { DISP; return FALSE; }
"int"                           { DISP; return INT;}
"bool"                          { DISP; return BOOL;}
"string"                        { DISP; return STRING;}
"for"                           { DISP; return LOOP;}
"if"                            { DISP; return IF;}
"else"                          { DISP; return ELSE;}
"func"                          { DISP; return FUNC;}
"var"                           { DISP; return VAR;}
"const"                         { DISP; return CONST;}
"return"                        { DISP; return RETURN; }
[0-9]+                          { DISP; yylval.integer = atoi(yytext); return INTEGER;}
[[:alpha:]_][[:alnum:]_]*       { DISP; yylval.string = strdup(yytext); return IDENT;}
"="                             { DISP; return EQUAL;}
"=="                            { DISP; return EQ;}
"!"                             { DISP; return BANG; }
"!="                            { DISP; return NE;}
"<"                             { DISP; return LT;}
"<="                            { DISP; return LTE;}
">"                             { DISP; return GT;}
">="                            { DISP; return GTE;}
"+"                             { DISP; return PLUS;}
"-"                             { DISP; return MINUS;}
"*"                             { DISP; return MUL;}
"/"                             { DISP; return DIV;}
"%"                             { DISP; return MOD;}
"|"                             { DISP; return OR;}
"&"                             { DISP; return AND;}
"["                             { DISP; return O_BRACKET;}
"]"                             { DISP; return C_BRACKET;}
"{"                             { DISP; return O_BRACE;}
"}"                             { DISP; return C_BRACE;}
"("                             { DISP; return O_PAREN;}
")"                             { DISP; return C_PAREN;}
","                             { DISP; return COMMA;}
";"                             { DISP; return SEMI;}
.                               { fprintf(stdout,"Unknown token: %s\n",yytext); fflush(stdout); yyterminate(); }

%%
