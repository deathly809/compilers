
#include <ast/node.h>

#include <constants.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CONVERT(_TO_,_VAL_) ((struct _TO_**)_VAL_)

#define allocate_struct(_TYPE_,_MSG_)                        \
    struct _TYPE_* result = malloc(sizeof(struct _TYPE_));    \
    memcheck(result,_MSG_);

void DestroyNode(struct node** n) {
    if(*n == NULL) return;

    void** ptr = &(n[0]->ptr);
    int const type = n[0]->nodetype;

    switch(type) {
        case EXPRESSION:
            // &((struct expression*)n[0]->ptr)
            DestroyExpression( CONVERT(expression,ptr) );
            break;
        case ASSIGNMENT:
            DestroyAssignment( CONVERT(assignment,ptr));
            break;
        case PROGRAM:
            DestroyProgram( CONVERT(program,ptr));
            break;
        case TARGET:
            DestroyTarget( CONVERT(target,ptr) );
            break;
        case BLOCK:
            DestroyBlock( CONVERT(block,ptr));
            break;
        case FUNC_DEF:
            DestroyFunctionDefinition( CONVERT(func_def,ptr));
            break;
        case NUMBER:
            break;
        case VAL_TYPE:
            DestroyValueType( CONVERT(value_type,ptr));
            break;
        default:
            fprintf(stderr, "error: unknown node type (%d)\n",(*n)->nodetype);
            exit(1);
    }
    free(*n);
    *n = NULL;
}

void freeNodeList(struct node_list** n_list) {
    while(Count(*n_list) > 0) {
        struct node* n = Pop(*n_list);
        DestroyNode(&n);
    }

    DestroyNodeList(n_list);
}

// create a new empty stack with capacity 32.
struct node_list* CreateNodeList() {

    struct node_list* result = malloc(sizeof(struct node_list));

    memcheck(result, "create node list");

    result->count = 0;
    result->capacity = 32;
    result->list = malloc(sizeof(struct node) * result->capacity);

    memcheck(result->list,"node list");

    memset(result->list,0,sizeof(struct node) * result->capacity);

    return result;
}

void DestroyNodeList(struct node_list** n_list) {
    if(*n_list == NULL) return;
    free(n_list[0]->list);
    free(*n_list);
    *n_list = NULL;
}


void Push(struct node_list* n_list, struct node* node) {
    if(n_list == NULL) return;

    if(4 * n_list->count > 3 * n_list->capacity) {

        int old_capacity = n_list->capacity;
        int new_capacity = old_capacity * 2;
        
        struct node** resized = malloc(sizeof(struct node) * new_capacity);
        memcheck(resized, "resize node list");

        // copy over old stuff
        memcpy(resized,n_list->list,old_capacity);

        struct node** old_list = n_list->list;

        // save
        n_list->list = resized;
        n_list->capacity = new_capacity;

        // free
        free(old_list);
    }

    n_list->list[n_list->count++] = node;
}

struct node* Pop(struct node_list* n_list) {
    if(n_list == NULL || n_list->count == 0) return NULL;
    return n_list->list[--n_list->count];
}

struct node* Get(struct node_list* n_list, int pos) {
    if(n_list == NULL || (pos < 0 && pos >= n_list->count)) return NULL;
    return n_list->list[pos];
}

int Count(struct node_list* n_list) {
    if(n_list == NULL) return 0;
    return n_list->count;
}

int Capacity(struct node_list* n_list) {
    if(n_list == NULL) return 0;
    return n_list->capacity;
}


/* value type stuff */
struct value_type* CreateValueType(int type, int modifier, int size) {
    allocate_struct(value_type,"create value type");

    result->type = type;
    result->modifier = modifier;
    result->size = size;

    return result;
}
void DestroyValueType(struct value_type ** vt) {
    if(*vt == NULL) return;
    free(*vt);
    *vt = NULL;
}


// Programs
struct program* CreateProgram(struct node_list* vars, struct node_list* funcs) {
    allocate_struct(program,"create program");

    result->vars = vars;
    result->funcs = funcs;

    return result;

}
void DestroyProgram(struct program** p) {
    if(*p == NULL) return;

    freeNodeList(&p[0]->vars);
    freeNodeList(&p[0]->funcs);

    free(*p);
    *p = NULL;
}


// Target
struct target* CreateTarget(struct ident* name, struct expression* index) {
    allocate_struct(target,"create target");

    result->name = name;
    result->index = index;

    return result;
}

void DestroyTarget(struct target** tar) {
    if(*tar == NULL) return;
    
    DestroyIdent( &tar[0]->name);
    DestroyExpression( &tar[0]->index);
    free(*tar);
    *tar = NULL;
}

// assignment
struct assignment* CreateAssignment(struct target* l, struct expression* r) {
    allocate_struct(assignment,"create assignment node");

    result->lhs = l;
    result->rhs = r;

    return result;
}

void DestroyAssignment(struct assignment ** a) {
    if(*a == NULL) return;

    DestroyTarget(&a[0]->lhs);
    DestroyExpression(&a[0]->rhs);

    free(*a);
    *a = NULL;
}

// ident
struct ident* CreateIdent(char* name, int line, int col) {
    allocate_struct(ident,"create ident");

    result->name = strdup(name);
    memcheck(result->name,"name in create ident");
    result->line = line;
    result->col = col;

    return result;
}

void DestroyIdent(struct ident** id) {
    if(*id == NULL) return;

    free(id[0]->name);

    free(*id);
    *id = NULL;
}


// Block
struct block* CreateBlock(struct node_list* list) {
    allocate_struct(block,"create block");

    result->stmts = list;

    return result;
}
void DestroyBlock(struct block** b) {
    if(*b == NULL) return;

    freeNodeList(&b[0]->stmts);

    free(*b);
    *b = NULL;
}


// formal parameter
struct formal_param* CreateFormalParamater(struct ident* name, struct value_type* type) {
    allocate_struct(formal_param,"create formal parameter");
    result->name = name;
    result->type = type;

    return result;
}

void DestroyFormalParameter(struct formal_param** fp) {
    if(*fp == NULL) return;

    DestroyIdent(&fp[0]->name);
    DestroyValueType(&fp[0]->type);
    free(*fp);
    *fp = NULL;
}

// function definition
struct func_def* CreateFunctionDefinition(struct ident* name, struct node_list* params, struct value_type* ret, struct block* body) {
    allocate_struct(func_def,"create function definition");

    result->name = name;
    result->params = params;
    result->ret = ret;
    result->body = body;

    return result;
}
void DestroyFunctionDefinition(struct func_def** fd) {
    if(*fd == NULL) return;

    DestroyIdent(&fd[0]->name);
    freeNodeList(&fd[0]->params);
    DestroyValueType(&fd[0]->ret);
    DestroyBlock(&fd[0]->body);

    free(*fd);
    *fd = NULL;
}



// loop
struct loop* CreateLoop(struct node* init, struct expression* cond, struct node* update, struct block* body) {
    allocate_struct(loop,"create loop");
    result->init = init;
    result->test = cond;
    result->update = update;
    result->body = body;

    return result;
}

void DestroyLoop(struct loop** l) {
    if(*l == NULL) return;

    DestroyNode(&l[0]->init);
    DestroyExpression(&l[0]->test);
    DestroyNode(&l[0]->update);
    DestroyBlock(&l[0]->body);

    free(*l);
    *l = NULL;
}



// Conditional
struct conditional* CreateConditional(struct expression* t, struct block* con, struct block* alt) {
    allocate_struct(conditional,"create conditional");

    result->test = t;
    result->con = con;
    result->alt = alt;

    return result;
}
void DestroyConditional(struct conditional** cond) {
    if(cond[0] == NULL) return;

    DestroyExpression(&cond[0]->test);
    DestroyBlock(&cond[0]->con);
    DestroyBlock(&cond[0]->alt);

    free(*cond);
    *cond = NULL;
}

// Function call
struct func_call* CreateFunctionCall(struct ident* name) {
    allocate_struct(func_call,"create function call");
    result->name = name;
    result->params = CreateNodeList();

    return result;
}

void DestroyFunctionCall(struct func_call** fc) {
    if(*fc == NULL) return;

    DestroyIdent(&fc[0]->name);
    freeNodeList(&fc[0]->params);
    free(*fc);
    *fc = NULL;
}


// Expression
struct expression* CreateExpression(int op, struct node* lhs, struct node* rhs) {
    allocate_struct(expression,"create expression");

    result->lhs = lhs;
    result->rhs = rhs;
    result->op = op;

    return result;
}

void DestroyExpression(struct expression** e) {
    if(*e == NULL) return;

    DestroyNode(&e[0]->lhs);
    DestroyNode(&e[0]->rhs);

    free(*e);
    *e = NULL;
}
