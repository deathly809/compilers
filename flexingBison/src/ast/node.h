
#ifndef NODE_H_
#define NODE_H_

#include <util.h>

typedef enum { EXPRESSION , ASSIGNMENT, PROGRAM, TARGET, BLOCK, FUNC_DEF, NUMBER, VAL_TYPE } NodeType;

struct node {
    NodeType nodetype;
    void* ptr;
};

struct node_list {
    int count;
    int capacity;
    struct node** list;
};

struct node_list* CreateNodeList();
void DestroyNodeList(struct node_list** n_list);

void Push(struct node_list* n_list, struct node* node);
struct node* Pop(struct node_list* n_list);
struct node* Get(struct node_list* n_list, int pos);

int Count(struct node_list* n_list);
int Capacity(struct node_list* n_list);


struct value_type {
    int type;
    int modifier;
    int size;
};

struct value_type* CreateValueType(int type, int modifier, int size);
void DestroyValueType(struct value_type ** vt);

struct program {
    struct node_list* vars;
    struct node_list* funcs;
};

struct program* CreateProgram(struct node_list* vars, struct node_list* funcs);
void DestroyProgram(struct program**);


struct target {
    struct ident* name;
    struct expression* index;
};

struct target* CreateTarget(struct ident*, struct expression*);
void DestroyTarget(struct target** tar);

struct assignment {
    struct target*      lhs;
    struct expression*  rhs;
};

struct assignment* CreateAssignment(struct target* l, struct expression* r);
void DestroyAssignment(struct assignment ** a);

struct block_def {
    int modifier;
    struct node_list* defs;
};

struct ident {
    char* name;
    int line;
    int col;
};

struct ident* CreateIdent(char* name, int line, int col);
void DestroyIdent(struct ident**);

struct block {
    struct node_list* stmts;
};

struct block* CreateBlock();
void DestroyBlock(struct block**);

struct formal_param {
    struct ident* name;
    struct value_type* type;
};

struct formal_param* CreateFormalParamater(struct ident* name, struct value_type* type);
void DestroyFormalParameter(struct formal_param**);

struct func_def {
    struct ident* name;
    struct node_list* params;
    struct value_type* ret;
    struct block* body;
};

struct func_def* CreateFunctionDefinition(struct ident* name, struct node_list* params, struct value_type* ret, struct block* body);
void DestroyFunctionDefinition(struct func_def**);

struct loop {
    struct node* init; 
    struct expression* test;
    struct node* update;
    struct block* body;
};

struct loop* CreateLoop(struct node* init, struct expression* cond, struct node* update, struct block* body);
void DestroyLoop(struct loop**);

struct conditional {
    struct expression* test;
    struct block* con;
    struct block* alt;
};

struct conditional* CreateConditional(struct expression* t, struct block* con, struct block* alt);
void DestroyConditional(struct conditional**);

struct func_call {
    struct ident* name;
    struct node_list* params;
};

struct func_call* CreateFunctionCall();
void DestroyFunctionCall(struct func_call**);

struct expression {
    struct node* lhs;
    struct node* rhs;
    int op;
};

struct expression* CreateExpression(int op, struct node* lhs, struct node* rhs);
void DestroyExpression(struct expression** e);

#endif