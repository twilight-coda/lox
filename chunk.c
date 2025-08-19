#include "chunk.h"
#include <stdlib.h>

void initChunk(Chunk *chunk) {
    chunk->capacity = 0;
    chunk->count = 0;
    chunk->code = NULL;
}

void writeChunk(Chunk *chunk, uint8_t byte) {
    if (chunk->count == chunk->capacity) {
        growChunk(chunk);
    }
    chunk->code[chunk->count] = byte;
    chunk->count++;
}

void growChunk(Chunk *chunk) {
    reallocateChunk(chunk, chunk->capacity * 2);
}

void reallocateChunk(Chunk *chunk, int newCapacity) {
    if (newCapacity == 0) {
        free(chunk->code);
        initChunk(chunk);
    } else {
        uint8_t tmp = realloc(chunk->code, newCapacity);
        if (tmp == NULL) exit(1);
        chunk->code = tmp;
        chunk->capacity = newCapacity;
    }
}
