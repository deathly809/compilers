
#ifndef NODE_H_
#define NODE_H_

#include <util.h>
#include <constants.h>

#include <symtable/symtable.h>


struct func_def_meta {
    struct scope* def_scope;
    struct func_def* node;
    unsigned int label;
};

struct var_def_meta {
    unsigned int scope;
    unsigned int position;
    struct var_def* node;
};


typedef enum {
    BinaryOperator, UnaryOperator, IntegerValue, VariableReference, FunctionCall, BooleanValue
} ExpressionType;

typedef enum {
    ExpressionNode , AssignmentNode, ProgramNode,
    TargetNode, BlockNode, FunctionDefinitionNode, 
    ValueTypeNode, LoopNode, ConditionalNode,
    VariableDefinitionNode, BlockDefinitionNode, IdentifierNode, 
    FunctionCallNode, ReturnNode,
} NodeType;

typedef enum {
    PlusOp, MinusOp, NegationOp,
    PositiveOp, OrOp, AndOp,
    MulOp, DivOp, ModOp,
    LTOp, GTOp, LTEOp,
    GTEOp, EqOp, NEOp,
    NotOp, DecOp, IncOp,
    AssignmentOp, NOP
} Operator;

struct generic_node {
    NodeType nodetype;
    void* ptr;
};

struct generic_node* CreateNode(NodeType type, void* ptr);
void DestroyNode(struct generic_node**);
void PrintNode(struct generic_node*);
void PrintNodeCode(struct generic_node*, struct symtable*);

extern const int InitialCapacity;

struct node_list {
    int count;
    int capacity;
    struct generic_node** list;
};

struct node_list* CreateNodeList();
void DestroyNodeList(struct node_list** n_list);
void PrintNodeList(struct node_list*,char sep);
void PrintNodeListCode(struct node_list*, struct symtable*);

void Push(struct node_list* n_list, struct generic_node* node);
struct generic_node* Pop(struct node_list* n_list);
struct generic_node* Get(struct node_list* n_list, int pos);

int Count(struct node_list* n_list);
int Capacity(struct node_list* n_list);

struct value_type {
    Type type;
    int modifier;
    int size;
};

struct value_type* CreateValueType(Type type, int modifier, int size);
void DestroyValueType(struct value_type ** vt);
void PrintValueType(struct value_type*);
void PrintValueTypeCode(struct value_type*, struct symtable*);

struct program {
    struct node_list* vars;
    struct node_list* funcs;
};

struct program* CreateProgram(struct node_list* vars, struct node_list* funcs);
void DestroyProgram(struct program**);
void PrintProgram(struct program*);
void PrintProgramCode(struct program*, struct symtable*);

struct target {
    Type type;
    struct ident* name;
    struct expression* index;
};

struct target* CreateTarget(struct ident*, struct expression*);
void DestroyTarget(struct target** tar);
void PrintTarget(struct target*);
void PrintTargetCode(struct target*, struct symtable*);

struct assignment {
    struct target*      lhs;
    struct expression*  rhs;
};

struct assignment* CreateAssignment(struct target* l, struct expression* r);
void DestroyAssignment(struct assignment ** a);
void PrintAssignment(struct assignment*);
void PrintAssignmentCode(struct assignment*, struct symtable*);

struct block_def {
    struct node_list* defs;
    Modifier modifier;
};

struct block_def* CreateBlockDefinition(struct node_list* defs, Modifier mod);
void DestroyBlockDefinition(struct block_def**);
void PrintBlockDefinition(struct block_def*);
void PrintBlockDefinitionCode(struct block_def*, struct symtable*);

struct ident {
    char* name;
    int line;
    int col;
};

struct ident* CreateIdent(char* name, int line, int col);
void DestroyIdent(struct ident**);
void PrintIdent(struct ident*);
void PrintIdentCode(struct ident*, struct symtable*);

struct block {
    unsigned int num_var_def;
    unsigned int pos;
    struct node_list* stmts;
};

struct block* CreateBlock();
void DestroyBlock(struct block**);
void PrintBlock(struct block*);
void PrintBlockCode(struct block*, struct symtable*);

struct formal_param {
    struct ident* name;
    struct value_type* type;
};

struct formal_param* CreateFormalParamater(struct ident* name, struct value_type* type);
void DestroyFormalParameter(struct formal_param**);
void PrintFormalParamater(struct formal_param*);
void PrintFormalParamaterCode(struct formal_param*, struct symtable*);

struct func_def {
    struct ident* name;
    struct node_list* params;
    struct value_type* ret;
    struct block* body;
};

struct func_def* CreateFunctionDefinition(struct ident* name, struct node_list* params, struct value_type* ret, struct block* body);
void DestroyFunctionDefinition(struct func_def**);
void PrintFunctionDefinition(struct func_def*);
void PrintFunctionDefinitionCode(struct func_def*, struct symtable*);

struct loop_cond {
    struct expression* init; 
    struct expression* test;
    struct expression* update;
};

struct loop_cond* CreateLoopCondition(struct expression* init, struct expression* cond, struct expression* update);
void DestroyLoopCondition(struct loop_cond** c);
void PrintLoopCondition(struct loop_cond* c);
void PrintLoopConditionCode(struct loop_cond* c, struct symtable*);


struct loop {
    struct loop_cond* cond;
    struct block* body;
};

struct loop* CreateLoop(struct loop_cond* c, struct block* body);
void DestroyLoop(struct loop**);
void PrintLoop(struct loop*);
void PrintLoopCode(struct loop*, struct symtable*);

struct conditional {
    struct expression* test;
    struct block* con;
    struct block* alt;
};

struct conditional* CreateConditional(struct expression* t, struct block* con, struct block* alt);
void DestroyConditional(struct conditional**);
void PrintConditional(struct conditional*);
void PrintConditionalCode(struct conditional*, struct symtable*);

struct func_call {
    Type type;
    struct ident* name;
    struct node_list* params;
};

struct func_call* CreateFunctionCall(struct ident* id, struct node_list* n_list);
void DestroyFunctionCall(struct func_call**);
void PrintFunctionCall(struct func_call*);
Type PrintFunctionCallCode(struct func_call*, struct symtable*);

struct expression {
    ExpressionType type;
    Type v_type;
    union {
        struct expression*        lhs;
        struct func_call*   fc;
        struct target*      tar;
        int integer;
    };
    struct expression* rhs;
    Operator op;
};

struct expression* CreateExpression(ExpressionType, Operator op, void* lhs, void* rhs);
void DestroyExpression(struct expression** e);
void PrintExpression(struct expression*);
Type PrintExpressionCode(struct expression*, struct symtable*);

struct return_stmt {
    struct expression* result;
};

struct return_stmt* CreateReturnStatement(struct expression* e);
void DestroyReturnStatement(struct return_stmt** r);
void PrintReturnStatement(struct return_stmt*);
void PrintReturnStatementCode(struct return_stmt*, struct symtable*);

struct var_def {
    unsigned int pos;
    int modifier;
    struct ident* name;
    struct expression* value;
    struct value_type* type;
};

struct var_def* CreateVariableDefinition(unsigned int pos, int modifier, struct ident* name, struct expression* value, struct value_type* type);
void DestroyVariableDefinition(struct var_def** vd);
void PrintVariableDefinition(struct var_def*);
void PrintVariableDefinitionCode(struct var_def*, struct symtable*);


#endif
