#ifndef clox_chunk_h
#define clox_chunk_h

#include "common.h"
#include "value.h"

typedef enum {
    OP_CONSTANT,
    OP_RETURN,
} OpCode;

typedef struct SourceInstructionMap {
    int offset;
    int count;
    int capacity;
    int *instructionBlockIndices;
} SourceInstructionMap;

typedef struct Chunk {
    int count;
    int capacity;
    uint8_t *code;
    SourceInstructionMap sourceInstructionMap;
    ValueArray constants;
} Chunk;

void initChunk(Chunk *chunk);
void writeChunk(Chunk *chunk, uint8_t byte, int line);
void freeChunk(Chunk *chunk);
int addConstant(Chunk *chunk, Value value);
void initSourceInstructionMap(SourceInstructionMap *sourceMap);
int getLine(Chunk *chunk, int instructionIndex);

#endif
