#include "chunk.h"
#include "memory.h"
#include <stdlib.h>

void initChunk(Chunk *chunk) {
    chunk->capacity = 0;
    chunk->count = 0;
    chunk->code = NULL;
}

void writeChunk(Chunk *chunk, uint8_t byte) {
    if (chunk->count == chunk->capacity) {
        int newCapacity = GROW_CAPACITY(chunk->capacity);
        chunk->code = GROW_ARRAY(uint8_t, chunk->code, chunk->capacity, newCapacity);
        chunk->capacity = newCapacity;
    }
    chunk->code[chunk->count] = byte;
    chunk->count++;
}

void freeChunk(Chunk *chunk) {
    FREE_ARRAY(uint8_t, chunk->code, chunk->capacity);
    initChunk(chunk);
}
