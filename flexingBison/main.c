
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    int i;
    printf("running program %s with arguments:\n", argv[0]);
    for(i = 1 ; i < argc ; ++i ) {
        printf("\t%s\n", argv[i]);
    }
    return EXIT_SUCCESS;
}
