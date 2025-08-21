#include "memory.h"
#include <stdlib.h>

void *reallocate(void *pointer, size_t oldSize, size_t newSize) {
    if (newSize == 0) {
        free(pointer);
        return NULL;
    }
    void* tmp = realloc(pointer, newSize);
    if (tmp == NULL) {
        free(pointer);
        exit(1);
    }
    return tmp;
}
