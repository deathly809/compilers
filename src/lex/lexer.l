
%option main

%%

\"([^\\\"]|\\.)*\"               printf("<%s>", yytext);

[a-zA-Z_][a-zA-Z0-9]+ printf("<%s>", yytext);

0x[a-fA-F0-9]   printf("<%s>", yytext);

0[0-7]+         printf("<%s>", yytext);

[0-9]+          printf("<%s>", yytext);

"("             printf("<O_PAREN>");

")"             printf("<C_PAREN>");

"{"             printf("<O_BRACE>");

"}"             printf("<C_BRACE>");

"["             printf("<O_BRACKET>");

"]"             printf("<O_BRACKET>");

";"             printf("<SEMICOLON>");

"&"             printf("<AND>");

"|"             printf("<OR>");

"."             printf("<DOT>");

[ \t\n\r]+          ;

