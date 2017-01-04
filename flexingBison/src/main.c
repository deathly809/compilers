
#include <stdio.h>
#include <stdlib.h>

#include <common.h>
#include <symtable/symtable.h>

extern int yydebug;
extern int yylex();
extern int yyparse();
extern FILE* yyin;

void yyerror (char const *s) {
   fprintf (stderr, "%s\n", s);
 }

void parse() {
        int result = yyparse();
        switch(result) {
        case 0:
//            printf("successully parsed\n");
            break;
        case 1:
            printf("parse failed with invalid input\n");
            return;
        case 2:
            printf("parsing failed due to memory exhaustion\n");
            return;
        default:
            printf("yyparse returned invalid value: '%d'\n", result);
            return;
    }
    
    if(root == NULL) {
        printf("root is null, idk why\n");
    } else {


        struct node_list* printIntN_List = CreateNodeList();
        Push(printIntN_List,(void*)345);

        struct func_def* printInt = CreateFunctionDefinition(CreateIdent("printInt",0,0),printIntN_List,NULL,NULL);
        struct func_def* readInt = CreateFunctionDefinition(CreateIdent("readInt",0,0),NULL,CreateValueType(IntType,Function,-1),NULL);
        struct func_def* newline = CreateFunctionDefinition(CreateIdent("newline",0,0),NULL,NULL,NULL);

        struct func_def_meta printInt_meta = {
            NULL,
            printInt,
            0
        };

        struct func_def_meta readInt_meta = {
            NULL,
            readInt,
            0
        };

        struct func_def_meta newline_meta = {
            NULL,
            newline,
            0
        };

//        PrintProgram(root);
        struct symtable* table = CreateTable();
        Insert(table,"printInt",Function,&printInt_meta);
        Insert(table,"readInt",Function,&readInt_meta);
        Insert(table,"newline",Function,&newline_meta);
        PrintProgramCode(root, table);
//        printf("worked\n");
    }

    fflush(stdout);
}

void lex() {
    while(yylex());
}
int main(int argc, char* argv[]) {
    if(argc > 1) {
        yyin = fopen(argv[1],"r");
    }
    root = NULL;

    if(argc > 2) {
        yydebug = 1;
        parse();
    } else {
        yydebug = 0;
        parse();
    }

    return EXIT_SUCCESS;
}
