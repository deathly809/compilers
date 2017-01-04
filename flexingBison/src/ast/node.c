
#include <ast/node.h>

#define STACK 1

#if STACK
    const unsigned int StackSize = 6;
#endif 

unsigned int offset = 0;

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#include <instructions.h>


void Exception(const char* format, ...)
{
    char dest[1024 * 16];
    va_list argptr;
    va_start(argptr, format);
    vsprintf(dest, format, argptr);
    va_end(argptr);
    printf("%s",dest);
    exit(1);
}

void AssertTrue(int test,const char* msg) {
    if(!test) {
        Exception(msg);
    }
}

#define UnimplementedFunction(NAME) do { printf("unimplemented function: %s\n", #NAME); exit(1); } while(0);

const int InitialCapacity = 32;

#define CONVERT(_TO_,_VAL_) ((struct _TO_)_VAL_)

#define allocate_name(_TYPE_,_NAME_,_MSG_)                      \
    struct _TYPE_* _NAME_ = malloc(sizeof(struct _TYPE_));      \
    memcheck(_NAME_,_MSG_);

#define allocate_struct(_TYPE_,_MSG_)   allocate_name(_TYPE_,result,_MSG_)
 

void printNodeType(NodeType t) {
    switch(t) {
        case ExpressionNode:
            printf("expression");
            break;
        case AssignmentNode:
            printf("assignment");
            break;
        case ProgramNode:
            printf("program");
            break;
        case TargetNode:
            printf("target");
            break;
        case BlockNode:
            printf("block");
            break;
        case FunctionDefinitionNode:
            printf("func_def");
            break;
        case ValueTypeNode:
            printf("value_type");
            break;
        case LoopNode:
            printf("loop");
            break;
        case ConditionalNode:
            printf("conditional");
            break;
        case VariableDefinitionNode:
            printf("var_def");            
            break;
        case IdentifierNode:
            printf("ident");            
            break;
        case FunctionCallNode:
            printf("func_call");            
            break;
        case ReturnNode:
            printf("return_stmt");            
            break;
        case BlockDefinitionNode:
            printf("block_def");            
            break;
    }
}

struct generic_node* CreateNode(NodeType t, void* ptr) {
    allocate_struct(generic_node,"create node");
    
    result->nodetype = t;
    result->ptr = ptr;

    return result;
}

void DestroyNode(struct generic_node** n) {
    if(*n == NULL) return;

    void** ptr = &(n[0]->ptr);
    NodeType type = n[0]->nodetype;

    switch(type) {
        case ExpressionNode:
            // &((struct expression*)n[0]->ptr)
            DestroyExpression( CONVERT(expression**,ptr) );
            break;
        case AssignmentNode:
            DestroyAssignment( CONVERT(assignment**,ptr));
            break;
        case ProgramNode:
            DestroyProgram( CONVERT(program**,ptr));
            break;
        case TargetNode:
            DestroyTarget( CONVERT(target**,ptr) );
            break;
        case BlockNode:
            DestroyBlock( CONVERT(block**,ptr));
            break;
        case FunctionDefinitionNode:
            DestroyFunctionDefinition( CONVERT(func_def**,ptr));
            break;
        case ValueTypeNode:
            DestroyValueType( CONVERT(value_type**,ptr));
            break;
        case LoopNode:
            DestroyLoop(CONVERT(loop**,ptr));
            break;
        case ConditionalNode:
            DestroyConditional(CONVERT(conditional**,ptr));
            break;
        case VariableDefinitionNode:
            DestroyVariableDefinition(CONVERT(var_def**, ptr));
            break;
        case IdentifierNode:
            DestroyIdent(CONVERT(ident**,ptr));
            break;
        case FunctionCallNode:
            DestroyFunctionCall(CONVERT(func_call**,ptr));
            break;
        case ReturnNode:
            DestroyReturnStatement(CONVERT(return_stmt**,ptr));
            break;
        case BlockDefinitionNode:
            DestroyBlockDefinition(CONVERT(block_def**,ptr));
            break;
    }
    free(*n);
    *n = NULL;
}

void PrintNode(struct generic_node* n) {
    if(n == NULL) return;

    void* ptr = n->ptr;
    NodeType type = n->nodetype;

    switch(type) {
        case ExpressionNode:
            // &((struct expression*)n[0]->ptr)
            PrintExpression( CONVERT(expression*,ptr) );
            break;
        case AssignmentNode:
            PrintAssignment( CONVERT(assignment*,ptr));
            break;
        case ProgramNode:
            PrintProgram( CONVERT(program*,ptr));
            break;
        case TargetNode:
            PrintTarget( CONVERT(target*,ptr) );
            break;
        case BlockNode:
            PrintBlock( CONVERT(block*,ptr));
            break;
        case FunctionDefinitionNode:
            PrintFunctionDefinition( CONVERT(func_def*,ptr));
            break;
        case ValueTypeNode:
            PrintValueType( CONVERT(value_type*,ptr));
            break;
        case LoopNode:
            PrintLoop(CONVERT(loop*,ptr));
            break;
        case ConditionalNode:
            PrintConditional(CONVERT(conditional*,ptr));
            break;
        case VariableDefinitionNode:
            PrintVariableDefinition(CONVERT(var_def*, ptr));
            break;
        case BlockDefinitionNode:
            PrintBlockDefinition(CONVERT(block_def*,ptr));
            break;
        case IdentifierNode:
            PrintIdent(CONVERT(ident*,ptr));
            break;
        case FunctionCallNode:
            PrintFunctionCall(CONVERT(func_call*,ptr));
            break;
        case ReturnNode:
            PrintReturnStatement(CONVERT(return_stmt*,ptr));
            break;
    }
}

void PrintNodeCode(struct generic_node* n, struct symtable* table) {
    if(n == NULL) return;

    void* ptr = n->ptr;
    NodeType type = n->nodetype;

    switch(type) {
        case ExpressionNode:
            // &((struct expression*)n[0]->ptr)
            PrintExpressionCode( CONVERT(expression*,ptr), table );
            break;
        case AssignmentNode:
            PrintAssignmentCode( CONVERT(assignment*,ptr), table);
            break;
        case ProgramNode:
            PrintProgramCode( CONVERT(program*,ptr), table);
            break;
        case TargetNode:
            PrintTargetCode( CONVERT(target*,ptr), table);
            break;
        case BlockNode:
            PrintBlockCode( CONVERT(block*,ptr), table);
            break;
        case FunctionDefinitionNode:
            PrintFunctionDefinitionCode( CONVERT(func_def*,ptr), table);
            break;
        case ValueTypeNode:
            PrintValueTypeCode( CONVERT(value_type*,ptr), table);
            break;
        case LoopNode:
            PrintLoopCode(CONVERT(loop*,ptr), table);
            break;
        case ConditionalNode:
            PrintConditionalCode(CONVERT(conditional*,ptr), table);
            break;
        case VariableDefinitionNode:
            PrintVariableDefinitionCode(CONVERT(var_def*, ptr), table);
            break;
        case BlockDefinitionNode:
            PrintBlockDefinitionCode(CONVERT(block_def*,ptr), table);
            break;
        case IdentifierNode:
            PrintIdentCode(CONVERT(ident*,ptr), table);
            break;
        case FunctionCallNode:
            PrintFunctionCallCode(CONVERT(func_call*,ptr), table);
            break;
        case ReturnNode:
            PrintReturnStatementCode(CONVERT(return_stmt*,ptr), table);
            break;
    }
}







void freeNodeList(struct node_list** n_list) {
    while(Count(*n_list) > 0) {
        struct generic_node* n = Pop(*n_list);
        DestroyNode(&n);
    }

    DestroyNodeList(n_list);
}

// create a new empty stack with capacity 32.
struct node_list* CreateNodeList() {

    allocate_struct(node_list,"create node list");

    result->count = 0;
    result->capacity = InitialCapacity;

    result->list = malloc(sizeof(struct generic_node*) * result->capacity);
    memcheck(result->list,"node list");
    memset(result->list,0,sizeof(struct generic_node*) * result->capacity);

    return result;
}

void DestroyNodeList(struct node_list** n_list) {
    if(*n_list == NULL) return;
    free(n_list[0]->list);
    free(*n_list);
    *n_list = NULL;
}

void PrintNodeList(struct node_list* list, char sep) {

    if(list == NULL) return;
    if(list->count == 0) return;

    PrintNode(list->list[0]);
    for(int i = 1 ; i < list->count; ++i) {
        printf("%c ", sep);
        PrintNode(list->list[i]);
    }

}

void PrintNodeListCode(struct node_list* list, struct symtable* table) {
    if(list == NULL) return;
    for(int i = 0; i < list->count; ++i) {
        PrintNodeCode(list->list[i], table);
    }
}

void Push(struct node_list* n_list, struct generic_node* node) {

    if(n_list == NULL) return;
    if(node == NULL) return;

    if(4 * n_list->count > 3 * n_list->capacity) {
        fprintf(stdout,"resize\n");
        fflush(stdout);
        int old_capacity = n_list->capacity;
        int new_capacity = old_capacity * 2;
        
        struct generic_node** resized = malloc(sizeof(struct generic_node*) * new_capacity);
        memcheck(resized, "resize node list");

        // copy over old stuff
        memset(resized, 0, new_capacity * sizeof(struct generic_node*));
        memcpy(resized,n_list->list,old_capacity);

        struct generic_node** old_list = n_list->list;

        // save
        n_list->list = resized;
        n_list->capacity = new_capacity;

        // free
        free(old_list);
    }

    n_list->list[n_list->count] = node;
    n_list->count++;
}

struct generic_node* Pop(struct node_list* n_list) {
    if(n_list == NULL || n_list->count == 0) return NULL;

    if(4 * n_list->count < n_list->capacity && n_list->capacity > InitialCapacity ) {

    }

    return n_list->list[--n_list->count];
}

struct generic_node* Get(struct node_list* n_list, int pos) {
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
struct value_type* CreateValueType(Type type, int modifier, int size) {
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

void printType(Type type) {
    switch(type){
        case IntType:
            printf("int");
            break;
        case StringType:
            printf("string");
            break;
        case CharType:
            printf("char");
            break;
        case BoolType:
            printf("bool");
            break;
        case RealType:
            printf("real");
            break;
        case NilType:
            printf("nil");
            break;
    }
}

void PrintValueType(struct value_type* type) {
    if(type == NULL) return;

    if(type->size == 0) {
        printf("[]");  
    } else if(type->size > 0) {
        printf("[%d]", type->size);
    }
    printType(type->type);
}

void PrintValueTypeCode(struct value_type* type, struct symtable* table) {
    if(type == NULL) return;
    UnimplementedFunction(PrintValueTypeCode);
}

// array

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


void PrintProgram(struct program* p) {
    if(p == NULL) return;

    PrintNodeList(p->vars,'\n');
    PrintNodeList(p->funcs,'\n');

}

void PrintProgramCode(struct program* p, struct symtable* table) {
    if(p == NULL) return;

    unsigned int global_size = 0;
    for(int i = 0; i < Count(p->vars);++i) {
        struct block_def* bd = (struct block_def*)p->vars->list[i]->ptr;
        global_size += Count(bd->defs);
    }

    INIT();
    #if STACK
        global_size += StackSize + 1;
    #endif

    if(global_size > 0) {
        ALLOC(global_size);
    }

    #if STACK
        LDC(1)
        ST(0,1)
    #endif

    offset = StackSize + 1;
    PrintNodeListCode(p->vars, table);
    offset = 0;

    JMP(1);
    PrintNodeListCode(p->funcs, table);

    struct item* main_ptr = Lookup(table,"main");

    if(main_ptr == NULL) {
        printf("missing main method\n");
        exit(1);
    } else {
        struct func_def_meta* meta = (struct func_def_meta*)(main_ptr->data);
        LABEL(1);
        CALL(meta->label);
        ALLOC(-global_size);
        HALT();
    }
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

void PrintTarget(struct target* t) {
    if(t == NULL) return;
    PrintIdent(t->name);
    PrintExpression(t->index);
}

void PrintTargetCode(struct target* t, struct symtable* table) {
    if(t == NULL) return;
    UnimplementedFunction(PrintTargetCode);
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

void PrintAssignment(struct assignment* a) {
    if(a == NULL) return;
    PrintTarget(a->lhs);
    printf(" = ");
    PrintExpression(a->rhs);
}


void PrintStore(struct target* l, struct expression* r, struct symtable* table) {
    if(l == NULL) Exception("null pointer: PrintStore\n");
    char* name = l->name->name;
    struct item* it = Lookup(table,name);
    if(it == NULL) {
        Exception("undefined variable: %s\n", name);
    }
    struct var_def_meta* meta = (struct var_def_meta*)it->data;
    if(l->index) {
        // Compute index
        PrintExpressionCode(l->index,table);       // compute index
        LDA(meta->scope,meta->position);                // load address
        ADD();                                          // compute address
        PrintExpressionCode(r,table);
        STL();                                          // store
    } else {
        PrintExpressionCode(r,table);
        ST(meta->scope,meta->position);
    }
}

Type PrintLoad(struct target* l, struct symtable* table) {
    if(l == NULL) Exception("null pointer: PrintLoad\n");
    char* name = l->name->name;
    struct item* it = Lookup(table,name);
    if(it == NULL) {
        Exception("undefined variable: %s\n", name);
    }
    struct var_def_meta* meta = (struct var_def_meta*)it->data;

    Type t1 = meta->node->type->type;
    if(l->index) {
        PrintExpressionCode(l->index,table);       // x[]
        LDA(meta->scope,meta->position);
        ADD();
        IND();
    } else {
        LDV(meta->scope,meta->position);
    }

    return t1;
}

void PrintAssignmentCode(struct assignment* a, struct symtable* table) {
    if(a == NULL) return;
    //PrintExpressionCode(a->rhs,table);
    PrintStore(a->lhs, a->rhs, table);

    UnimplementedFunction(PrintAssignmentCode);
}

// block_def
struct block_def* CreateBlockDefinition(struct node_list* defs, Modifier mod) {
    allocate_struct(block_def,"create block def");

    result->defs = defs;
    result->modifier = mod;

    return result;
}

void DestroyBlockDefinition(struct block_def** bf) {
    if(*bf == NULL) return;
    freeNodeList(&bf[0]->defs);
    free(*bf);
    *bf = NULL;
}

void printModifier(Modifier mod) {
    switch(mod){
        case Variable:
            printf("var ");
            break;
        case Constant:
            printf("const ");
            break;
        case Function:
            break; 
    }
}

void PrintBlockDefinition(struct block_def* b) {
    if(b == NULL) return;
    printModifier(b->modifier);
    printf(" (\n");
    PrintNodeList(b->defs, '\n');
    printf(")\n");
}

void PrintBlockDefinitionCode(struct block_def* b, struct symtable* table) {
    if(b == NULL) return;
    PrintNodeListCode(b->defs, table);
}

// ident
struct ident* CreateIdent(char* name, int line, int col) {
    allocate_struct(ident,"create ident");

    result->name = strdup(name);
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

void PrintIdent(struct ident* i) {
    if( i == NULL) return;
    printf("%s", i->name);
}

void PrintIdentCode(struct ident* i, struct symtable* table) {
    if( i == NULL) return;
    UnimplementedFunction(PrintIdentCode);
}

// Block
struct block* CreateBlock(struct node_list* list) {
    allocate_struct(block,"create block");

    result->num_var_def = 0;
    result->pos = 0;
    result->stmts = list;

    return result;
}
void DestroyBlock(struct block** b) {
    if(*b == NULL) return;

    freeNodeList(&b[0]->stmts);

    free(*b);
    *b = NULL;
}

void PrintBlock(struct block* b) {
    if( b == NULL) return;
    printf("{\n");
    PrintNodeList(b->stmts, '\n');
    printf("}\n");
}

void PrintBlockCode(struct block* b, struct symtable* table) {
    if( b == NULL) return;

    int pos = 0;
    for(int i = 0 ; i < Count(b->stmts); i++) {
        if(b->stmts->list[i]->nodetype == VariableDefinitionNode) {
            struct var_def* vd = (struct var_def*)(b->stmts->list[i]->ptr);
            vd->pos = pos + offset;
            if(vd->type != NULL && vd->type->size > 0) {
                pos += vd->type->size;
            } else {
                pos++;
            }
        }
    }

    if(pos > 0) {
        ALLOC(pos);
    }
    
    PrintNodeListCode(b->stmts, table);
    
    if(pos > 0) {
        ALLOC(-pos);
    }
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

void PrintFormalParamater(struct formal_param* f) {
    if( f == NULL) return;
    PrintIdent(f->name);
    printf(" ");
    PrintValueType(f->type);
}

void PrintFormalParamaterCode(struct formal_param* f, struct symtable* table) {
    UnimplementedFunction(PrintFormalParamater);
    if( f == NULL) return;
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

void PrintFunctionDefinition(struct func_def* f) {
    if( f == NULL) return;

    printf("func ");
    PrintIdent(f->name);
    printf("(");
    PrintNodeList(f->params, ',');
    printf(") ");
    PrintValueType(f->ret);
    PrintBlock(f->body);
}


void PrintFunctionDefinitionCode(struct func_def* f, struct symtable* table) {

    if( f == NULL) return;

    allocate_struct(func_def_meta,"create function definition meta");

    result->def_scope = TopScope(table);
    result->node = f;
    result->label = GenerateLabel(table);

    LABEL(result->label);

    int n_params = Count(f->params);

    Insert(table, f->name->name, Function, result);

    PushScope(table);
    
    PROC(1);
    if(n_params > 0) {
        ALLOC(n_params);
        for(int i = 0 ; i < n_params; ++i) {
            ((struct var_def*)f->params->list[i]->ptr)->pos = i;
        }
        
        PrintNodeListCode(f->params,table);

        for(int i = 0 ; i < n_params; ++i) {
            
            // Get address
            LDV(0,1)
            LDC(i - n_params + 1)
            ADD();
            IND();
            
            struct var_def* v_def = (struct var_def*)f->params->list[i]->ptr;
            struct target* tar = CreateTarget(v_def->name,NULL);
            PrintStore(tar,NULL, table);
        }
    }

    PrintBlockCode(f->body, table);

    if(n_params > 0) {
        ALLOC(-n_params);
    }

    RET(1);

    PopScope(table);

}

// loop condtiion
struct loop_cond* CreateLoopCondition(struct expression* init, struct expression* cond, struct expression* update) {
    allocate_struct(loop_cond,"create loop");

    result->init = init;
    result->test = cond;
    result->update = update;

    return result;
}

void DestroyLoopCondition(struct loop_cond** l) {
    if(*l == NULL) return;

    DestroyExpression(&l[0]->init);
    DestroyExpression(&l[0]->test);
    DestroyExpression(&l[0]->update);

    free(*l);
    *l = NULL;
}

void PrintLoopCondition(struct loop_cond* l) {
    if(l == NULL) return;
    
    if(l->init != NULL) {
        printf(" ");
        PrintExpression(l->init);
        printf("; ");
        PrintExpression(l->test);
        printf("; ");
        PrintExpression(l->update);
        printf(" ");
    } else if(l->update != NULL) {
        printf(" ");
        PrintExpression(l->test);
        printf(" ");
    }
}

void PrintLoopConditionCode(struct loop_cond* l, struct symtable* table) {
    UnimplementedFunction(PrintLoopConditionCode);
    if(l == NULL) return;
}


// loop
struct loop* CreateLoop(struct loop_cond* cond, struct block* body) {
    allocate_struct(loop,"create loop");

    result->cond = cond;
    result->body = body;

    return result;
}

void DestroyLoop(struct loop** l) {
    if(*l == NULL) return;

    DestroyLoopCondition(&l[0]->cond);
    DestroyBlock(&l[0]->body);

    free(*l);
    *l = NULL;
}

void PrintLoop(struct loop* l) {
    if(l == NULL) return;
    printf("for");
    PrintLoopCondition(l->cond);
    PrintBlock(l->body);
}

void PrintLoopCode(struct loop* l, struct symtable* table) {
    //UnimplementedFunction(PrintLoopCode);
    if(l == NULL) return;

    unsigned int test_label = GenerateLabel(table);

    if(l->cond) {
        unsigned int after_loop = GenerateLabel(table);
        if(l->cond->init) {
            PrintExpressionCode(l->cond->init, table);
        } 

        LABEL(test_label);
        if(l->cond->test) {
            PrintExpressionCode(l->cond->test, table);
            JMPF(after_loop);
        }

        PrintBlockCode(l->body, table);

        if(l->cond->update) {
            PrintExpressionCode(l->cond->update, table);
            
        }

        JMP(test_label);
        LABEL(after_loop);
    } else {
        LABEL(test_label);
        PrintBlockCode(l->body, table);
        JMP(test_label);
    }

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

void PrintConditional(struct conditional* c) {
    if(c == NULL) return;
    printf("if ");
    PrintExpression(c->test);
    PrintBlock(c->con);
    if(c->alt != NULL) {
        printf("else ");
        PrintBlock(c->alt);
    }
}

void PrintConditionalCode(struct conditional* c, struct symtable* table) {
//    UnimplementedFunction(PrintConditionalCode);
    if(c == NULL) return;

    unsigned int after_true = GenerateLabel(table);
    Type t = PrintExpressionCode(c->test, table);
    if( t != BoolType) {
        PrintExpression(c->test);
        printf("\n");
        Exception("expected boolean for condition arguments, found %s\n", TypeAsString(t));
    }
    JMPF(after_true);
    PrintBlockCode(c->con, table);
    if(c->alt) {
        unsigned int after_if = GenerateLabel(table);
        JMP(after_if);
        LABEL(after_true);
        after_true = after_if;
        PrintBlockCode(c->alt, table);
    }
    LABEL(after_true);

}

// Function call
struct func_call* CreateFunctionCall(struct ident* name, struct node_list *n_list) {
    allocate_struct(func_call,"create function call");

    result->name = name;
    result->params = n_list;

    return result;
}

void DestroyFunctionCall(struct func_call** fc) {
    if(*fc == NULL) return;

    DestroyIdent(&fc[0]->name);
    freeNodeList(&fc[0]->params);

    free(*fc);
    *fc = NULL;
}

void PrintFunctionCall(struct func_call* f) {
    if( f == NULL) return;
    PrintIdent(f->name);
    printf("(");
    PrintNodeList(f->params, ',');
    printf(")");
}

Type PrintFunctionCallCode(struct func_call* f, struct symtable* table) {
//    UnimplementedFunction(PrintFunctionCallCode);
    if( f == NULL) return NilType;

    Type t1 = NilType;

    const char* n = f->name->name;
    const int num_params = Count(f->params);

    struct item* f_call = Lookup(table, n);

    if(f_call == NULL) {
        Exception("unknown function: %s\n", f->name->name);
    } else {
        struct func_def_meta* meta = (struct func_def_meta*)f_call->data;
        struct func_def* f_def = meta->node;
        const int num_arguments = Count(f_def->params);

        if(num_params != num_arguments) {
            Exception("number of params does not equal number of arguments for %s: %d and %d\n", n, num_params, num_arguments);
        } else if( meta->node->body == NULL) {
            // built in
            if(strcmp(n,"printInt") == 0) {
                PrintNodeCode(Pop(f->params),table);
                OUT();
            } else if(strcmp(n,"newline") == 0) {
                LDC(10);
                OUTCH();
            } else {
                IN();
                t1 = IntType;
            }
        }else {
            for(unsigned int i = 0 ; i < num_params;++i) {
                // Get address
                LDV(0,1)
                LDA(0,1)
                ADD()
                DUP()
                PrintNodeCode(f->params->list[i],table);
                STL()
                ST(0,1)
            }
            CALL(meta->label);
            if(num_params > 0) {
                LDV(0,1)
                LDC(num_params)
                SUB()
                ST(0,1)
            }
        }
    }
    return t1;
}

// Expression
struct expression* CreateExpression(ExpressionType type, Operator op, void* lhs, void* rhs) {
    allocate_struct(expression,"create expression");

    result->type = type;
    result->op = op;

    switch(type) {
        case BinaryOperator:
            result->lhs = (struct expression*)lhs;
            result->rhs = (struct expression*)rhs;
        break;
        case UnaryOperator:
            result->lhs = (struct expression*)lhs;
        break;
        case FunctionCall:
            result->fc = (struct func_call*)lhs;
        break;
        case VariableReference:
            result->tar = (struct target*)lhs;
        break;
        case BooleanValue:
        case IntegerValue:
            result->integer = *(int*)lhs;
        break;
    }

    return result;
}

void DestroyExpression(struct expression** e) {
    if(*e == NULL) return;

    switch(e[0]->type) {
        case BinaryOperator:
            DestroyExpression(&e[0]->lhs);
            DestroyExpression(&e[0]->rhs);
            break;
        case UnaryOperator:
            DestroyExpression(&e[0]->lhs);
            break;
        case FunctionCall:
            DestroyFunctionCall(&e[0]->fc);
            break;
        case VariableReference:
            DestroyTarget(&e[0]->tar);
            break;
        case IntegerValue:
        case BooleanValue:
            break;
    }

    free(*e);
    *e = NULL;
}

void PrintExpression(struct expression* e) {
    if( e == NULL ) return;
    switch(e->type) {
        case BinaryOperator:
            PrintExpression(e->lhs);
            switch(e->op){
                case AssignmentOp:
                    printf("=");
                    break;
                case PlusOp:
                    printf("+");
                    break;
                case MinusOp:
                    printf("-");
                    break;
                case MulOp:
                    printf("*");
                    break;
                case DivOp:
                    printf("/");
                    break;
                case ModOp:
                    printf("%%");
                    break;
                case LTOp:
                    printf("<");
                    break;
                case LTEOp:
                    printf("<=");
                    break;
                case GTOp:
                    printf(">");
                    break;
                case GTEOp:
                    printf(">=");
                    break;
                case EqOp:
                    printf("==");
                    break;
                case NEOp:
                    printf("!=");
                    break;
                default:
                    printf("Invalid operator: %d\n", e->op);
                    exit(1);
                    break;
            }
            PrintExpression(e->rhs);
            break;
        case UnaryOperator:
            switch(e->op){
                case NegationOp:
                    printf("-");
                    PrintExpression(e->lhs);
                    break;
                case IncOp:
                    PrintExpression(e->lhs);
                    printf("++");
                    break;
                case DecOp:
                    PrintExpression(e->lhs);
                    printf("--");
                    break;
                case NotOp:
                    printf("!");
                    PrintExpression(e->lhs);
                    break;
                default:
                    printf("Invalid operator: %d\n", e->op);
                    exit(1);
                    break;
            }
            break;
        case IntegerValue:
        case BooleanValue:
            printf("%d",e->integer);
            break;
        case FunctionCall:
            PrintFunctionCall(e->fc);
            break;
        case VariableReference:
            PrintTarget(e->tar);
            break;
    }
}



Type PrintExpressionCode(struct expression* e, struct symtable* table) {
    if( e == NULL ) return NilType;

    Type t1 = NilType, t2 = NilType;

    switch(e->type) {
        case BinaryOperator:
            if(e->op == AssignmentOp) {
                //t1 = PrintExpressionCode(e->rhs,table);
                PrintStore(e->lhs->tar,e->rhs,table);
            } else {
                t1 = PrintExpressionCode(e->lhs, table);
                t2 = PrintExpressionCode(e->rhs, table);

                if(t1 != t2) {
                    PrintExpression(e);
                    printf("\n");
                    Exception("binary operator types don't match: %s and %s\n", TypeAsString(t1), TypeAsString(t2));
                }
            }

            switch(e->op){
                case AssignmentOp:
                    break;
                case PlusOp:
                    AssertTrue(t1==IntType,"+ only supports integers\n");
                    ADD();
                    break;
                case MinusOp:
                    AssertTrue(t1==IntType,"- only supports integers\n");
                    SUB();
                    break;
                case MulOp:
                    AssertTrue(t1==IntType,"* only supports integers\n");
                    MULT();
                    break;
                case DivOp:
                    AssertTrue(t1==IntType,"/ only supports integers\n");
                    DIV();
                    break;
                case ModOp:
                    AssertTrue(t1==IntType,"% only supports integers\n");
                    MOD();
                    break;
                case LTOp:
                    AssertTrue(t1==IntType,"< only supports integers\n");
                    t1 = BoolType;
                    LT();
                    break;
                case LTEOp:
                    AssertTrue(t1==IntType,"<= only supports integers\n");
                    LE();
                    t1 = BoolType;
                    break;
                case GTOp:
                    AssertTrue(t1==IntType,">= only supports integers\n");
                    t1 = BoolType;
                    GT();
                    break;
                case GTEOp:
                    AssertTrue(t1==IntType,">= only supports integers\n");
                    t1 = BoolType;
                    GE();
                    break;
                case EqOp:
                    EQ();
                    t1 = BoolType;
                    break;
                case NEOp:
                    NE();
                    t1 = BoolType;
                    break;
                case OrOp:
                    AssertTrue(t1==BoolType,"| only supports booleans\n");
                    OR();
                    break;
                case AndOp:
                    AssertTrue(t1==BoolType,"& only supports booleans\n");
                    AND();
                    break;
                default:
                    printf("Invalid operator: %d\n", e->op);
                    exit(1);
                    break;
            }
            break;
        case UnaryOperator:
            t1 = PrintExpressionCode(e->lhs, table);

            switch(e->op){
                case NegationOp:
                    if( t1 != IntType) Exception("integer negate can only be applied to integer values");
                    NEG();
                    break;
                case IncOp:
                    UnimplementedFunction("post-increment\n");
                    break;
                case DecOp:
                    UnimplementedFunction("post-decrement\n");
                    break;
                case NotOp:
                    if( t1 != BoolType) Exception("boolean not can only be applied to booleans");
                    NOT();
                    break;
                default:
                    printf("Invalid operator: %d\n", e->op);
                    exit(1);
                    break;
            }
            break;
        case BooleanValue:
            t1 = BoolType;
            LDC(e->integer);
            break;
        case IntegerValue:
            t1 = IntType;
            LDC(e->integer);
            break;
        case FunctionCall:
            t1 = PrintFunctionCallCode(e->fc, table);
            break;
        case VariableReference:
            t1 = PrintLoad(e->tar, table);
            break;
    }
    return t1;
}

// return statements
struct return_stmt* CreateReturnStatement(struct expression* e) {
    allocate_struct(return_stmt,"create return statement");
    result->result = e;
    return result;
}

void DestroyReturnStatement(struct return_stmt** r) {
    if(*r  == NULL) return;
    DestroyExpression(&r[0]->result);
    free(*r);
    *r = NULL;
}

void PrintReturnStatement(struct return_stmt* r) {
    if(r == NULL) return;

    printf("return");
    if(r->result) {
        printf(" ");
        PrintExpression(r->result);
    }
}

void PrintReturnStatementCode(struct return_stmt* r, struct symtable* table) {
    UnimplementedFunction(PrintReturnStatementCode);
    if(r == NULL) return;
}

// Variable definitions 
struct var_def* CreateVariableDefinition(unsigned int pos, int modifier, struct ident* name, struct expression* value, struct value_type* type) {
    allocate_struct(var_def,"create variable definition");
    result->pos = pos;
    result->modifier = modifier;
    result->name = name;
    result->value = value;
    result->type = type;
    return result;
}
void DestroyVariableDefinition(struct var_def** vd) {
    if(*vd == NULL) return;

    DestroyIdent(&vd[0]->name);
    DestroyExpression(&vd[0]->value);
    DestroyValueType(&vd[0]->type);

    free(*vd);
    *vd = NULL;
}

void PrintVariableDefinition(struct var_def* v) {
    if( v == NULL ) return;

    switch(v->modifier) {
        case Variable:
            printf("var ");
            break;
        case Constant:
            printf("const ");
            break;
    }

    PrintIdent(v->name);
    if(v->value) {
        printf(" = ");
        PrintExpression(v->value);
    } else {
        printf(" ");
        PrintValueType(v->type);
    }
    printf("\n");
}

void PrintVariableDefinitionCode(struct var_def* v, struct symtable* table) {
    if( v == NULL ) return;

    allocate_name(var_def_meta,meta,"create variable meta data");
    struct scope* s = TopScope(table);

    meta->scope = s->id;
    meta->position = v->pos + offset + 1;
    meta->node = v;

    Insert(table,v->name->name, v->modifier,meta);

    if(v->value) {
        v->type = CreateValueType(PrintExpressionCode(v->value, table), Variable,-1);
        ST(s->id,meta->position);
    } else {
        /* initialize to "0" */
        int pos = 1;
        if(v->type->size > 0) {
            pos = v->type->size;
        }
        for(int i = 0; i < pos; ++i) {
            LDC(0);
            ST(s->id,meta->position + i);
        }
    }
}