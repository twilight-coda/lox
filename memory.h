#ifndef clox_memory_h
#define clox_memory_h

#include "common.h"

#define GROW_CAPACITY(capacity) ((capacity) < 8 ? 8 : (capacity) * 2)
#define GROW_ARRAY(type, pointer, oldCapacity, newCapacity) \
    (type*) reallocate(pointer, (oldCapacity) * sizeof(type), (newCapacity) * sizeof(type))

void* reallocate(void* pointer, size_t oldSize, size_t newSize);

#endif
