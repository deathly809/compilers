
/* Declarations */

%{
    #include <symtable/symtable.h>
    #include <ast/node.h>

    #include <stdio.h>

    extern int yylex();
    extern void yyerror(char*);

    void insertVariable(char*);
    void insertFunction(char*);


    struct program* entry;

%}

%union
{
    unsigned int        unsigned_integer;
    int                 integer;
    char*               string;
    struct node_list*   n_list;
    struct node*        n;
    struct block_def*   b_def;
}

%token D_MINUS
%token D_PLUS
%token  BANG
%token  COMMA
%token  QUOTE
%token  D_QUOTE
%token  O_BRACE
%token  O_PAREN
%token  O_BRACKET
%token  C_BRACE
%token  C_PAREN
%token  C_BRACKET
%token  FUNC
%token  IF
%token  ELSE
%token  LOOP
%token  LT
%token  LTE
%token  GT
%token  GTE
%token  NE
%token  EQ
%token  EQUAL
%token  PLUS
%token  MINUS
%token  MUL
%token  DIV
%token  MOD
%token  EXP
%token  OR
%token  AND
%token  CHAR
%token  INT
%token  REAL
%token  STRING
%token  BOOL
%token  IDENT
%token  INTEGER
%token  RETURN
%token  VAR
%token  CONST
%token  SEMI

%type <string> IDENT target
%type <integer> INTEGER
%type <unsigned_integer> var_attr
%type <n> decl_item 
%type <b_def> decl_block decl_list_items
%%

/* Grammar */

input:                      { entry = malloc(sizeof(struct program)); }top_level_list                      { }
                        ;

top_level_list:             top_level_item top_level_list       { }
                        |   %empty                              { }
                        ;

top_level_item:             func_def                            { }
                        |   decl_block                          { } 
                        ;

decl_block:                 var_attr O_PAREN decl_list_items C_PAREN { $$ = $3; }
                        ;

var_attr:                   VAR                                 { $$ = Variable; }
                        |   CONST                               { $$ = Constant; }
                        ;

decl_list_items:            decl_item decl_list_items           { } 
                        |   decl_item                           { struct node_list* n_list = CreateNodeList(); Push(n_list, $1); $$ = tmp; } 
                        ;

decl_item:                  IDENT EQUAL expression              { struct assignment* tmp = CreateAssignement(CreateTarget($1,NULL), $3); $$ = tmp; } 
                        ;


func_def:                   FUNC IDENT { insertFunction($2);} O_PAREN opt_param_list C_PAREN opt_type block   
                        ;

opt_type:                   type
                        |   %empty
                        ;

opt_param_list:             param_list
                        |   %empty
                        ;

param_list:                 param_item COMMA param_list
                        |   param_item
                        ;

param_item:                 IDENT type
                        ;

block:                      {printf("block:before\n"); } O_BRACE statement_list C_BRACE { printf("block:after\n");}
                        ;

statement_list:             statement statement_list
                        |   %empty
                        ;

statement:                  loop
                        |   conditional
                        |   return
                        |   assignment
                        |   declaration
                        |   func_call
                        ;

loop:                       {printf("for\n");}LOOP loop_conditional block             {printf("loop_end:  NOP\n");}
                        ;

loop_conditional:           expression opt_rem_loop_cond { printf("JMP label_test\n"); }
                        |   init rem_loop_cond
                        |   %empty
                        ;

opt_rem_loop_cond:          rem_loop_cond
                        |   %empty
                        ;

rem_loop_cond:              SEMI expression SEMI update 
                        ;
init:                       assignment
                        |   declaration
                        ;

conditional:                IF expression block opt_else            { printf("if\n");}
                        ;

update:                     assignment
                        |   expression
                        ;

opt_else:                   ELSE block
                        |   %empty
                        ;

return:                     RETURN opt_expr                 { printf("JMP ret_lbl\n"); }
                        ;

opt_expr:                   expression
                        |   %empty
                        ;

assignment:                 target EQUAL expression         { printf("assign to %s\n", $1 );}
                        ;

target:                     IDENT opt_arr                   { $$ = $1; }
                        ;

opt_arr:                    opt_arr O_BRACKET expression C_BRACKET
                        |   %empty
                        ;

declaration:              var_attr IDENT decl_rem
                        ;

decl_rem:                  type
                        |   EQUAL expression
                        ;

func_call:                  IDENT O_PAREN opt_expr_list C_PAREN         { printf("%s(...)\n", $1);}
                        ;

opt_expr_list:              expr_list
                        |   %empty
                        ;

expr_list:                  expression COMMA expr_list
                        |   expression    
                        ;

expression:                 logic_or_expr
                        ;

logic_or_expr:              logic_or_expr OR logic_and_expr
                        |   logic_and_expr
                        ;

logic_and_expr:             logic_and_expr AND cmp_expression
                        |   cmp_expression
                        ;

cmp_expression:             cmp_expression LT linear_expression     { printf("LT\n"); }
                        |   cmp_expression LTE linear_expression    { printf("LTE\n"); }
                        |   cmp_expression GT linear_expression     { printf("GT\n"); }
                        |   cmp_expression GTE linear_expression    { printf("GTE\n"); }
                        |   cmp_expression NE linear_expression     { printf("NE\n"); }
                        |   cmp_expression EQ linear_expression     { printf("EQ\n"); }
                        |   linear_expression
                        ;

linear_expression:          linear_expression PLUS nonlinear_expression     { printf("ADD\n"); }
                        |   linear_expression MINUS nonlinear_expression    { printf("SUB\n"); }
                        |   nonlinear_expression
                        ;

nonlinear_expression:       nonlinear_expression MUL unary_exp      { printf("MUL\n");}
                        |   nonlinear_expression DIV unary_exp      { printf("DIV\n");}
                        |   nonlinear_expression MOD unary_exp      { printf("MOD\n");}
                        |   unary_exp
                        ;

unary_exp:                  BANG post_expr                          { printf("NOT"); }
                        |   PLUS post_expr
                        |   MINUS post_expr                         { printf("NEG"); }
                        |   post_expr
                        ;

post_expr:                  primary_expr
                        |   func_call
                        |   post_expr O_BRACKET expression C_BRACKET    { printf("array stuff\n"); }
                        |   post_expr D_PLUS                            { printf("++\n");}
                        |   post_expr D_MINUS                           { printf("--\n");}
                        ;

primary_expr:               IDENT                               { printf("load from %s\n", $1); }
                        |   INTEGER                             { printf("LD %d\n", $1);}
                        |   O_PAREN expression C_PAREN
                        ;

type:                       opt_array INT
                        |   opt_array STRING
                        |   opt_array BOOL
                        |   opt_array REAL
                        |   opt_array CHAR
                        ;

opt_array:                  O_BRACKET INTEGER C_BRACKET
                        |   O_BRACKET C_BRACKET
                        |   %empty
                        ;

%%

/* Epilogue */


void insertFunction(char* name) {
    printf("%s\n", name);
}

void insertVariable(char* name) {
    printf("%s\n", name);
}

