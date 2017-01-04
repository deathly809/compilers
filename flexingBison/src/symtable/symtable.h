
#ifndef SYMTABLE_H_
#define SYMTABLE_H_
#include <constants.h>

/* Identifier */
struct item {
    char* ident;                /* variable name    */
    Modifier mod;               /* type of data     */
    void *data;                 /* pointer to data  */
};

/* Scope */
struct scope {
    unsigned int id;
    unsigned int num_items;     /* how many items in this scope */
    unsigned int max_items;     /* max number of items allowed  */
    struct item** items;        /* array of items               */
};

/* Symbol Table */
struct symtable {
    unsigned int num_scopes;    /* how many scopes in the table */
    unsigned int max_scopes;    /* max number of scopes allowed */
    struct scope** scopes;      /* ordered list of scopes       */
    unsigned int label;
};

// Create a symbol table
struct symtable* CreateTable();

// Cleanup a symbol table
void DestroyTable(struct symtable** table);

// Insert a new item in the top-most scope
int Insert(struct symtable* table, const char* name, Modifier mod, void* data);

// Search all scopes, starting from top, for identifier definition
struct item* Lookup(struct symtable* table, const char* name);

// Entering new scope
void PushScope(struct symtable*);

// Leaving scope
void PopScope(struct symtable*);

struct scope* TopScope(struct symtable*);

unsigned int GenerateLabel(struct symtable* table);

#endif