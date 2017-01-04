
#include <ast/node.h>

#include <assert.h>

#include <util.c>


void testProgram() {

    struct node_list* vars = CreateNodeList();
    struct node_list* funcs = CreateNodeList();

    struct program* p = CreateProgram(vars,funcs);

    DestroyProgram(&p);
}

void testNodeList() {
    struct node_list* n_list = CreateNodeList();

    Push(n_list, malloc(sizeof(struct node)));

    AssertTrue(Count(n_list) == 1);
    AssertTrue(Capacity(n_list) == 32);


    struct generic_node* tmp = Pop(n_list);

    AssertTrue(tmp);

    AssertTrue(Count(n_list) == 0);
    AssertTrue(Capacity(n_list) == 32);
    

    DestroyNodeList(&n_list);
}

int main(int argc, char* argv[]) {
    testNodeList();
    testProgram();
    return 0;
}
