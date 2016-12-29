
#include <stdio.h>
#include <stdlib.h>

extern int yyparse();

void yyerror (char const *s) {
   fprintf (stderr, "%s\n", s);
 }

int main(int argc, char* argv[]) {
    int result = yyparse();
    if(result == 0) {
        printf("success\n");
    } else {
        printf("failure\n");
    }
    return EXIT_SUCCESS;
}
