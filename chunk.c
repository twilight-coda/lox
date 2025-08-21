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
        growChunk(chunk);
    }
    chunk->code[chunk->count] = byte;
    chunk->count++;
}

void freeChunk(Chunk *chunk) {
    reallocateChunk(chunk, 0);
    initChunk(chunk);
}

void growChunk(Chunk *chunk) {
    size_t newCapacity = chunk->capacity == 0 ? 8 : chunk->capacity * 2;
    reallocateChunk(chunk, newCapacity*sizeof(uint8_t));
}

void reallocateChunk(Chunk *chunk, int newSize) {
    chunk->code = reallocate(
        chunk->code, chunk->capacity * sizeof(uint8_t), newSize
    );
    chunk->capacity = newSize;
}
