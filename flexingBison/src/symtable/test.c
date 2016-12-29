
#include <symtable/symtable.h>
#include <constants.h>

#include <stdio.h>
#include <stdlib.h>

#define AssertFalse(_TEST_) do {                                        \
    if(_TEST_) {                                                        \
        fprintf(stderr,                                                 \
            "expected false but found true\n\t%s:%d: %s\n",             \
            __FILE__,                                                   \
            __LINE__,                                                   \
            #_TEST_                                                     \
        );                                                              \
        exit(1);                                                        \
    }                                                                   \
} while(0);

#define AssertTrue(_TEST_) do {                                         \
    if(!(_TEST_)) {                                                     \
        fprintf(stderr,                                                 \
            "expected true but found false\n\t%s:%d: %s\n",             \
            __FILE__,                                                   \
            __LINE__,                                                   \
            #_TEST_                                                     \
        );                                                              \
        exit(1);                                                        \
    }                                                                   \
} while(0);

void memcheck(void* ptr, const char* msg) {
    if(!ptr) {
        printf("malloc failed: %s\n", msg);
        exit(1);
    }
}

int main() {

    printf("testng the symbol table\n");

    struct symtable* table = CreateTable();

    printf("table:\n\tmax_scopes: %d\n\tnum_scopes: %d\n", table->max_scopes, table->num_scopes);

    Insert(table, "jeff", Variable, IntType);

    AssertFalse(Insert(table, "jeff", Array, IntType));

    AssertTrue(Lookup(table, "jeff"))    

    PushScope(table);

    AssertTrue(Lookup(table, "jeff"));

    AssertTrue(Insert(table, "jeff", Array, IntType));
    AssertFalse(Insert(table, "jeff", Function, IntType));

    AssertTrue(Lookup(table, "jeff"));

    PopScope(table);

    return 0;
}
