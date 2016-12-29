
#include <util.h>

#include <stdio.h>
#include <stdlib.h>

/*
 *  memcheck - Validates malloc worked.  If not prints message and exits
 *
 *      ptr     - The ptr to test
 *      message - The message to display
 *
 */
void memcheck(void* ptr, const char* message) {
    if(!ptr) {
        fprintf(stderr,"could not allocate memory: %s\n", message);
        exit(1);
    }
}
