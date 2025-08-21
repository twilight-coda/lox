#include "debug.h"

#include <stdio.h>

int simpleInstruction(const char* instruction, int offset) {
    printf("%s\n", instruction);
    return offset + 1;
}

void disassembleChunk(Chunk *chunk, const char *chunkName) {
    printf("== %s ==\n", chunkName);

    for (int offset = 0; offset < chunk->count;) {
        offset = disassembleInstruction(chunk, offset);
    }
}

int disassembleInstruction(Chunk *chunk, int offset) {
    printf("%04d ", offset);
    uint8_t instr = chunk->code[offset];

    switch (instr) {
        case OP_RETURN:
            return simpleInstruction("OP_RETURN", offset);
        default:
            printf("Unknown instruction\n");
            return offset + 1;
    }
}
