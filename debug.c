#include "debug.h"
#include "value.h"

#include <stdio.h>

int simpleInstruction(const char* instruction, int offset) {
    printf("%s\n", instruction);
    return offset + 1;
}

int constantInstruction(const char* instruction, Chunk *chunk, int offset) {
    uint8_t constantOffset = chunk->code[offset + 1];
    Value value = chunk->constants.values[constantOffset];
    printf("%-16s %d '", instruction, constantOffset);
    printValue(value);
    printf("\n");
    return offset + 2;
}

void disassembleChunk(Chunk *chunk, const char *chunkName) {
    printf("== %s ==\n", chunkName);

    for (int offset = 0; offset < chunk->count;) {
        offset = disassembleInstruction(chunk, offset);
    }
}

int disassembleInstruction(Chunk *chunk, int offset) {
    printf("%04d ", offset);
    if ( offset > 0 && getLine(chunk, offset) == getLine(chunk, offset - 1)) {
        printf("%3s| ", " ");
    } else {
        printf("%4d ", getLine(chunk, offset));
    }
    uint8_t instr = chunk->code[offset];

    switch (instr) {
        case OP_CONSTANT:
            return constantInstruction("OP_CONSTANT", chunk, offset);
        case OP_RETURN:
            return simpleInstruction("OP_RETURN", offset);
        default:
            printf("Unknown instruction\n");
            return offset + 1;
    }
}
