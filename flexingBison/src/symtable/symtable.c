
#include <symtable/symtable.h>
#include <util.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/*
 *  CreateItem - Creates a new scope item
 *
 *      name        - The identifer value for this item
 *      modifier    - What type of item is this
 *      type        - What value type this item managess
 *
 *      @result     - Returns a pointer to a new item
 *
 */
struct item* CreateItem(const char *name, unsigned int modifier, unsigned int type) {
    struct item* result = malloc(sizeof(struct item));

    memcheck(result,"create item");

    result->ident = strdup(name);
    result->modifier = modifier;
    result->type = type;

    return result;
}

/*
 *  DestroyItem - Frees up any memory associated with this item
 */
void DestroyItem(struct item** it) {
    if(*it == NULL) return;
    free((*it)->ident);
    free(*it);
    *it = NULL;
}

/*
 *  CreateScope - creates a new scope in the symbol table
 *
 *      @result - returns a new scope if no error
 *
 */
struct scope* CreateScope() {
    struct scope* result = malloc(sizeof(struct scope));

    memcheck(result,"create scope");

    result->max_items = 128;
    result->num_items = 0;
    result->items = malloc(sizeof(struct item*) * result->max_items);

    memcheck(result->items,"create scope items");

    memset(result->items,0,sizeof(struct item*) * result->max_items);

    return result;
}

/*
 *  DestroyScope - Frees up memory associated with a scope.
 */
void DestroyScope(struct scope** scope) {
    if(*scope == NULL) {
        return;
    }

    for(unsigned int pos = 0; pos < (*scope)->num_items; ++pos) {
        DestroyItem( (*scope)->items + pos);
    }

    free((*scope)->items);
    free(*scope);
    
    *scope = NULL;
}

/*
 *  locate - locates a variable in a scope
 *
 *      @result - Returns NULL if item not found, otherwise returns item
 *
 */
struct item* locate(struct scope* scope, const char* name) {
    if(scope == NULL) {
        return NULL;
    }

    for(int i = 0 ; i < scope->num_items; ++i) {
        if(strcmp(scope->items[i]->ident,name) == 0) {
            return scope->items[i];
        }
    }
    return NULL;
}

/*
 *  insert - insert a new item into a scope
 *
 *
 */
int insert(struct scope* scope, struct item* it) {
    
    if(locate(scope,it->ident) != NULL) { 
        return 0;
    }

    if(scope->num_items == scope->max_items) {
        return 0;
    }

    scope->items[scope->num_items] = it;
    scope->num_items++; 

    return 1;
}

/*
 *  CreateTable - create a new symbol table
 *
 *      @result     - return a pointer to a new symbol table
 */
struct symtable* CreateTable() {
    struct symtable* result = malloc(sizeof(struct symtable));

    memcheck(result, "create symbol table");

    result->max_scopes = 32;
    result->num_scopes = 1;

    result->scopes = malloc(result->max_scopes * sizeof(struct item*));
    memcheck(result->scopes, "create scopes" );
    memset(result->scopes,0,result->max_scopes * sizeof(struct item*));

    // Global Scope
    result->scopes[0] = CreateScope();

    return result;
}

/*
 *  DestroyTable - free up memory allocated by symbol table
 */
void DestroyTable(struct symtable** table) {
    if(*table == NULL) {
        return;
    }

    for(int i = 0 ; i < (*table)->max_scopes; ++i) {
        DestroyScope( (*table)->scopes + i);
    }

    free((*table)->scopes);
    free(*table);
    *table = NULL;

}

/*
 *  PushScope - push a new scope on the stack
 */
void PushScope(struct symtable* table) {
    table->scopes[table->num_scopes] = CreateScope();
    table->num_scopes++;
}

/*
 *  PopScope - remove the top scope from the stack
 */
void PopScope(struct symtable* table) {
    if(table->max_scopes > 1) {
        table->num_scopes--;
        DestroyScope( table->scopes + table->num_scopes);
    }
}

/*
 *  Insert - create a new item and insert it into the top most scope
 *
 *      table       - table to insert our item into
 *      name        - name of the identifier
 *      modifier    - item attributes
 *      type        - value type we result in
 *
 */
int Insert(struct symtable *table, const char* name, int modifier, int type) {
    int result = 0;

    if(table) {
        result = insert(table->scopes[table->num_scopes - 1], CreateItem(name, modifier, type));
    }

    return result;    
}

/*
 *  Lookup - locate an identifier in all visible scopes
 *
 *      table   - symbol table we are searching through
 *      name    - identifier name
 *
 *      @result - return NULL of identifier does not exist, else returns item.
 *
 */
struct item* Lookup(struct symtable* table, const char* name) {
    struct item* result = NULL;

    if(table) {
        for(int i = table->num_scopes - 1 ; i >= 0; --i) {
            result = locate(table->scopes[i], name);
            if(result) {
                break;
            }
        }
    }

    return result;
}
