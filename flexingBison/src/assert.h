
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

