#include "chunk.h"
#include "memory.h"
#include <stdlib.h>

void initChunk(Chunk *chunk) {
    chunk->capacity = 0;
    chunk->count = 0;
    chunk->code = NULL;
    initSourceInstructionMap(&(chunk->sourceInstructionMap));
    initValueArray(&chunk->constants);
}

void initSourceInstructionMap(SourceInstructionMap *sourceMap) {
    sourceMap->offset = -1;
    sourceMap->count = 0;
    sourceMap->capacity = 0;
    sourceMap->instructionBlockIndices = NULL;
}

void writeChunk(Chunk *chunk, uint8_t byte, int line) {
    if (chunk->count == chunk->capacity) {
        int newCapacity = GROW_CAPACITY(chunk->capacity);
        chunk->code = GROW_ARRAY(
            uint8_t, chunk->code, chunk->capacity, newCapacity
        );
        chunk->capacity = newCapacity;
    }
    chunk->code[chunk->count] = byte;
    SourceInstructionMap *map = &chunk->sourceInstructionMap;
    if (map->offset == -1) map->offset = line;
    if (map->count == map->capacity) {
        int newCapacity = GROW_CAPACITY(map->capacity);
        map->instructionBlockIndices = GROW_ARRAY(
            int, map->instructionBlockIndices, map->capacity, newCapacity
        );
        map->capacity = newCapacity;
    }
    map->instructionBlockIndices[line - map->offset] = chunk->count;
    map->count = line - map->offset + 1;
    chunk->count++;
}

void freeChunk(Chunk *chunk) {
    FREE_ARRAY(uint8_t, chunk->code, chunk->capacity);
    FREE_ARRAY(
        int,
        chunk->sourceInstructionMap.instructionBlockIndices,
        chunk->sourceInstructionMap.capacity
    );
    freeValueArray(&chunk->constants);
    initChunk(chunk);
}

int addConstant(Chunk *chunk, Value value) {
    ValueArray *constants = &chunk->constants;
    writeValueArray(constants, value);
    return constants->count - 1;
}

int searchIndex(int *instructionBlockIndices, int len, int instructionIndex) {
    int l = 0, r = len - 1;
    while (l <= r) {
        int mid = (l + r) / 2;
        if (
            (mid > 0
                && instructionBlockIndices[mid] >= instructionIndex
                && instructionBlockIndices[mid - 1] < instructionIndex)
            ||
            (mid == 0
                && instructionBlockIndices[mid] >= instructionIndex)) {
            return mid;
        }
        if (instructionIndex < instructionBlockIndices[mid]) {
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    return -1;
}

int getLine(Chunk *chunk, int instructionIndex) {
    SourceInstructionMap *map = &(chunk->sourceInstructionMap);
    int line = searchIndex(map->instructionBlockIndices, map->count, instructionIndex);
    return line + map->offset;
}
