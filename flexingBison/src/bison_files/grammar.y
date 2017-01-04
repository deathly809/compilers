
/* Declarations */

%{
    #include <symtable/symtable.h>

    #include <common.h>
    #include <constants.h>

    #include <stdio.h>
    #include <stdlib.h>

    extern int yylex();
    extern void yyerror(char*);

    void insertVariable(char*);
    void insertFunction(char*);

    extern void yyterminate();

    #if 0
        #define P(T) printf("%s\n", #T);
    #else
        #define P(T)
    #endif
%}

%union
{
    unsigned int            unsigned_integer;
    int                     integer;
    char*                   string;
    struct node_list*       n_list;
    struct value_type*      vt;
    struct generic_node*    nd;
    struct program*         prog;
    struct target*          targ;
    struct assignment*      assign;
    struct block_def*       b_def;
    struct ident*           id;
    struct block*           blk;
    struct formal_param*    f_param;
    struct var_def*         v_def;
    struct func_def*        f_def;
    struct loop*            loop;
    struct conditional*     cond;
    struct func_call*       f_call;
    struct expression*      expr;
    struct return_stmt*     ret;
    struct loop_cond*       l_cond;
    int                    t;
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
%token EOL

%type <string> IDENT
%type <integer> INTEGER
%type <unsigned_integer> var_attr
%type <b_def> decl_block
%type <n_list> decl_list_items opt_param_list opt_expr_list statement_list param_list expr_list opt_stmt_list
%type <nd>  param_item statement 
%type <f_def> func_def
%type <expr> target assignment expression logic_or_expr logic_and_expr cmp_expression linear_expression nonlinear_expression unary_expr primary_expr;
%type <blk> block
%type <t> type
%type <vt> opt_type param_type
%type <cond> conditional true_cond
%type <loop> loop
%type <ret> return
%type <assign> decl_item
%type <v_def> declaration
%type <l_cond> loop_conditional
%type <prog> top_level_list input

%%

/* Grammar */

/* need to consume all the new lines */
input:                      top_level_list          { P(input); root = $1;}
                        |   %empty                  { P(input); root = NULL; }

top_level_list:             top_level_list func_def         {
                                                                if( $1 == NULL) $1 = CreateProgram(CreateNodeList(), CreateNodeList());
                                                                P(top_level_list);
                                                                struct generic_node* t = CreateNode(FunctionDefinitionNode,$2);
                                                                Push($1->funcs, t);
                                                                $$ = $1;
                                                            }

                        |   top_level_list decl_block       {
                                                                if( $1 == NULL) $1 = CreateProgram(CreateNodeList(), CreateNodeList());
                                                                P(top_level_list); 
                                                                Push($1->vars,    CreateNode(BlockDefinitionNode,$2)); 
                                                                $$ = $1;
                                                            }

                        |   func_def                        {   
                                                                P(top_level_list);;
                                                                struct program* tmp = CreateProgram(CreateNodeList(),CreateNodeList());
                                                                struct generic_node* t = CreateNode(FunctionDefinitionNode, $1);
                                                                Push(tmp->funcs, t);
                                                                $$ = tmp;
                                                            }

                        |   decl_block                      {   
                                                                P(top_level_list); 
                                                                struct program* tmp = CreateProgram(CreateNodeList(),CreateNodeList()); 
                                                                Push(tmp->vars, CreateNode(BlockDefinitionNode, $1));
                                                                $$ = tmp;
                                                            }
                        |   top_level_list EOL              { P(top_level_list); $$ = $1; }
                        |   EOL                             { $$ = NULL; }
                        ;

decl_block:                 var_attr O_PAREN decl_list_items C_PAREN { P(decl_block); $$ = CreateBlockDefinition($3,$1); }
                        ;

var_attr:                   VAR                                 { P(var_attr); $$ = Variable; }
                        |   CONST                               { P(var_attr); $$ = Constant; }
                        ;

decl_list_items:            decl_item EOL decl_list_items       {
                                                                    P(decl_list_items); 
                                                                    Push($3,CreateNode(AssignmentNode,$1)); 
                                                                    $$ = $3; 
                                                                } 
                        |   decl_item EOL                       { 
                                                                    P(decl_list_items); 
                                                                    struct node_list* n_list = CreateNodeList(); 
                                                                    Push(n_list, CreateNode(AssignmentNode,$1)); 
                                                                    $$ = n_list; 
                                                                } 
                        ;

decl_item:                  IDENT EQUAL expression              { 
                                                                    P(decl_item);
                                                                    $$ = CreateAssignment( CreateTarget(CreateIdent($1,0,0),NULL), $3);
                                                                } 
                        ;


func_def:                   FUNC IDENT O_PAREN opt_param_list C_PAREN opt_type block    {
                                                                                            P(func_def); 
                                                                                            $$ = CreateFunctionDefinition( CreateIdent($2,0,0), $4, $6, $7); 
                                                                                        }
                        ;

opt_type:                   param_type                      { P(opt_type); $$ = $1; }
                        |   %empty                          { P(opt_type); $$ = NULL; }
                        ;

opt_param_list:             param_list      { P(opt_param_list); $$ = $1; }
                        |   %empty          { P(opt_param_list); $$ = NULL; }
                        ;

param_list:                 param_item COMMA param_list                 { P(param_list); Push($3, $1); $$ = $3; }
                        |   param_item                                  { P(param_list); struct node_list* tmp = CreateNodeList(); Push(tmp, $1); $$ = tmp;}
                        ;

param_item:                 IDENT param_type                                  { $$ = CreateNode(VariableDefinitionNode,CreateVariableDefinition(0,Variable,CreateIdent($1,0,0),NULL,$2));}
                        ;

param_type:                 O_BRACKET C_BRACKET type                                    { P(opt_type); $$ = CreateValueType($3,Variable, 0); }
                        |   type                                                        { P(opt_type); $$ = CreateValueType($1,Variable,-1); }

block:                      O_BRACE EOL opt_stmt_list C_BRACE                           { P(block); $$ = CreateBlock($3); }
                        ;

opt_stmt_list:              statement_list eols                 { P(opt_stmt_list); $$ = $1; }
                        |   %empty                              { P(opt_stmt_list); $$ = NULL; }
                        ;

eols:                       EOL eols
                        |   %empty

statement_list:             statement_list eols statement EOL    {
                                                                    P(statement_list); 
                                                                    Push($1, $3);
                                                                    if($3->nodetype == VariableDefinitionNode) {
                                                                        ((struct var_def*)$3->ptr)->pos = Count($1);
                                                                    }
                                                                    $$ = $1;
                                                                 }
                        |   statement EOL                        { P(statement_list); struct node_list* tmp = CreateNodeList(); Push(tmp,$1); $$ = tmp; }
                        ;

statement:                  loop                                { P(statement); $$ = CreateNode(LoopNode,$1);}
                        |   conditional                         { P(statement); $$ = CreateNode(ConditionalNode,$1);}
                        |   return                              { P(statement); $$ = CreateNode(ReturnNode,$1);}
                        |   declaration                         { P(statement); $$ = CreateNode(VariableDefinitionNode,$1);}
                        |   block                               { P(statement); $$ = CreateNode(BlockNode,$1); }
                        |   expression                          { P(statement); $$ = CreateNode(ExpressionNode,$1); }
                        ;

loop:                       LOOP loop_conditional block         { P(loop); $$ = CreateLoop($2,$3); }
                        ;

loop_conditional:           expression                                      { P(loop_conditional); $$ = CreateLoopCondition(NULL,$1,NULL); }
                        |   expression SEMI expression SEMI expression      { P(loop_conditional); $$ = CreateLoopCondition($1, $3, $5); }
                        |   %empty                                          { P(loop_conditional); $$ = CreateLoopCondition(NULL,NULL,NULL);}
                        ;

conditional:                true_cond                           { P(conditional); $$ = $1; }
                        |   true_cond ELSE block            { P(conditional); $1->alt = $3; $$ = $1; }
                        ;

true_cond:                  IF expression block { $$ = CreateConditional($2,$3,NULL);}
                        ;

return:                     RETURN expression               { P(return) $$ = CreateReturnStatement($2); }
                        |   RETURN                          { P(return) $$ = CreateReturnStatement(NULL);}
                        ;
                        ;
 
declaration:                var_attr IDENT type                                 { P(declaration) $$ = CreateVariableDefinition(0,$1,CreateIdent($2,0,0), NULL, CreateValueType($3,$1,-1)); }
                        |   var_attr IDENT O_BRACKET INTEGER C_BRACKET type     { P(declaration) $$ = CreateVariableDefinition(0,$1,CreateIdent($2,0,0), NULL, CreateValueType($6,$1,$4)); }
                        |   var_attr IDENT EQUAL logic_or_expr                  { P(declaration) $$ = CreateVariableDefinition(0,$1,CreateIdent($2,0,0), $4, NULL); }
                        ;

opt_expr_list:              expr_list           { P(opt_expr_list); $$ = $1; }
                        |   %empty              { P(opt_expr_list); $$ = NULL; }
                        ;

expr_list:                  expression COMMA expr_list      { P(expr_list); Push($3,CreateNode(ExpressionNode,$1)); $$ = $3; }
                        |   expression                      { P(expr_list); struct node_list* tmp = CreateNodeList(); Push(tmp,CreateNode(ExpressionNode,(void*)$1)); $$ = tmp; }
                        ;

expression:                 assignment                          { P(expression); $$ = $1; }
                        ;
                    
assignment:                 logic_or_expr                       { P(expression); $$ = $1; }
                        |   target EQUAL logic_or_expr           { P(assignment); $$ = CreateExpression(BinaryOperator,AssignmentOp,$1,$3);}


logic_or_expr:              logic_or_expr OR logic_and_expr { P(logic_or_expr) $$ = CreateExpression(BinaryOperator, OrOp, $1, $3); }
                        |   logic_and_expr                  { P(logic_or_expr) $$ = $1; }
                        ;

logic_and_expr:             logic_and_expr AND cmp_expression       { P(logic_and_expr); $$ = CreateExpression(BinaryOperator, AndOp ,$1, $3); }
                        |   cmp_expression                          { P(logica_and_expr); $$ = $1; }
                        ;

cmp_expression:             cmp_expression LT linear_expression     { P(cmp_expression); $$ = CreateExpression(BinaryOperator, LTOp,   $1, $3); }
                        |   cmp_expression LTE linear_expression    { P(cmp_expression); $$ = CreateExpression(BinaryOperator, LTEOp,  $1, $3); }
                        |   cmp_expression GT linear_expression     { P(cmp_expression); $$ = CreateExpression(BinaryOperator, GTOp,   $1, $3); }
                        |   cmp_expression GTE linear_expression    { P(cmp_expression); $$ = CreateExpression(BinaryOperator, GTEOp,  $1, $3); }
                        |   cmp_expression NE linear_expression     { P(cmp_expression); $$ = CreateExpression(BinaryOperator, NEOp,   $1, $3); }
                        |   cmp_expression EQ linear_expression     { P(cmp_expression); $$ = CreateExpression(BinaryOperator, EqOp,   $1, $3); }
                        |   linear_expression                       { P(cmp_expression); $$ = $1; }
                        ;

linear_expression:          linear_expression PLUS nonlinear_expression     { P(linear_expression) $$ = CreateExpression(BinaryOperator, PlusOp, $1, $3); }
                        |   linear_expression MINUS nonlinear_expression    { P(linear_expression) $$ = CreateExpression(BinaryOperator, MinusOp, $1, $3); }
                        |   nonlinear_expression                            { P(linear_expression) $$ = $1; }
                        ;

nonlinear_expression:       nonlinear_expression MUL unary_expr     { P(nonlinear_expression) $$ = CreateExpression(BinaryOperator, MulOp,$1,$3); }
                        |   nonlinear_expression DIV unary_expr     { P(nonlinear_expression) $$ = CreateExpression(BinaryOperator, DivOp,$1,$3); }
                        |   nonlinear_expression MOD unary_expr     { P(nonlinear_expression) $$ = CreateExpression(BinaryOperator, ModOp,$1,$3); }
                        |   unary_expr                              { P(nonlinear_expression) $$ = $1; }
                        ;

unary_expr:                 BANG primary_expr                          { P(unary_expr) $$ = CreateExpression(UnaryOperator, NotOp, $2, NULL); }
//                        |   PLUS primary_expr                          { P(unary_expr) $$ = $2; }
//                        |   MINUS primary_expr                         { P(unary_expr) $$ = CreateExpression(UnaryOperator, NegationOp, $2,NULL); }
                        |   primary_expr                               { P(unary_expr) $$ = $1; }
                        ;

primary_expr:               target
                        |   IDENT O_PAREN opt_expr_list C_PAREN         { P(primary_expr) $$ = CreateExpression(FunctionCall,NOP,CreateFunctionCall(CreateIdent($1,0,0),$3),NULL);}
                        |   INTEGER                                 { P(primary_expr) $$ = CreateExpression(IntegerValue, NOP, &($1), NULL);}
                        |   O_PAREN expression C_PAREN              { P(primary_expr) $$ = $2; }
                        ;

target:                     IDENT                                   { P(primary_expr) $$ = CreateExpression(VariableReference, NOP, CreateTarget(CreateIdent($1,0,0),NULL), NULL); }
                        |   IDENT O_BRACKET expression C_BRACKET        { P(primary_expr) $$ = CreateExpression(VariableReference, NOP, CreateTarget(CreateIdent($1,0,0),$3  ), NULL); }
                        ;
type:                       INT                                      { P(type); $$ = IntType;       }
                        |   STRING                                   { P(type); $$ = StringType;    }
                        |   BOOL                                     { P(type); $$ = BoolType;      }
                        |   REAL                                     { P(type); $$ = RealType;      }
                        |   CHAR                                     { P(type); $$ = CharType;      }
                        ;

%%

/* Epilogue */
