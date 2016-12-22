
/* Declarations */


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

%left   PLUS MINUS
%left   MUL DIV
%left   MOD
%right  EXP
%left   OR
%right  AND

%%

/* Grammar */

input:              top_level_list

top_level_list:     func_def top_level_list | decl_block top_level_list |  %empty

decl_block:          decl_list_type O_PAREN decl_list_items C_PAREN

decl_list_type:     VAR 
                |   CONST

decl_list_items:    IDENT EQUAL expression decl_list_items
                |   IDENT EQUAL expression
func_def: FUNC IDENT O_PAREN opt_param_list C_PAREN opt_type block

opt_type:           %empty
                |   type

opt_param_list: %empty
                |   param_list
                
param_list:     IDENT type COMMA param_list
                |IDENT type

block:  O_BRACE statement_list C_BRACE

statement_list: %empty
                | statement statement_list

statement:      loop
            |   conditional
            |   return
            |   assignment
            |   declaration
            |   func_call

loop:           LOOP loop_conditional block

loop_conditional:   init COMMA expression COMMA expression

init:               assignment | declaration | func_call

conditional:    IF expression block opt_else

opt_else:       %empty
            |   ELSE block

return:         RETURN opt_expr

opt_expr:       %empty
            |   expression

assignment:     target EQUAL expression
            
target:         IDENT opt_arr

opt_arr:        %empty
            |   arr_list
            
arr_list:        O_BRACKET expression C_BRACKET arr_list
            |   O_BRACKET expression C_BRACKET

declaration:    VAR IDENT type
            |   VAR IDENT EQUAL expression

func_call:      IDENT O_PAREN opt_expr_list C_PAREN

opt_expr_list:  %empty
            |   expr_list

expr_list:      expression COMMA expr_list
            |   expression    

expression:     PLUS expression
            |   MINUS expression
            |   BANG expression
            |   expression op expression
            |   IDENT
            |   INTEGER
            |   O_PAREN expression C_PAREN
            ;
op:             PLUS
            |   MINUS
            |   MUL
            |   DIV
            |   MOD
            |   AND
            |   OR
            |   LT
            |   LTE
            |   GT
            |   GTE
            |   EQ
            |   NE
            ;

type:           opt_array INT
            |   opt_array STRING
            |   opt_array BOOL
            |   opt_array REAL
            |   opt_array CHAR

opt_array:      %empty
            |   O_BRACKET INTEGER C_BRACKET

%%

/* Epilogue */