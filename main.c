#include "common.h"
#include "chunk.h"
#include "debug.h"

int main (int argc, const char* argv[]) {
    Chunk chunk;
    initChunk(&chunk);
    int offset = addConstant(&chunk, 1.2);
    writeChunk(&chunk, OP_CONSTANT, 1);
    writeChunk(&chunk, offset, 1);
    offset = addConstant(&chunk, 43.0);
    writeChunk(&chunk, OP_CONSTANT, 1);
    writeChunk(&chunk, offset, 1);
    offset = addConstant(&chunk, 44.0);
    writeChunk(&chunk, OP_CONSTANT, 1);
    writeChunk(&chunk, offset, 1);
    offset = addConstant(&chunk, 45.0);
    writeChunk(&chunk, OP_CONSTANT, 2);
    writeChunk(&chunk, offset, 2);
    offset = addConstant(&chunk, 45.0);
    writeChunk(&chunk, OP_CONSTANT, 3);
    writeChunk(&chunk, offset, 3);
    offset = addConstant(&chunk, 45.0);
    writeChunk(&chunk, OP_CONSTANT, 4);
    writeChunk(&chunk, offset, 4);
    offset = addConstant(&chunk, 45.0);
    writeChunk(&chunk, OP_CONSTANT, 5);
    writeChunk(&chunk, offset, 5);
    offset = addConstant(&chunk, 45.0);
    writeChunk(&chunk, OP_CONSTANT, 6);
    writeChunk(&chunk, offset, 6);
    offset = addConstant(&chunk, 42.0);
    writeChunk(&chunk, OP_CONSTANT, 7);
    writeChunk(&chunk, offset, 7);
    writeChunk(&chunk, OP_RETURN, 8);
    disassembleChunk(&chunk, "test chunk");
    freeChunk(&chunk);

    return 0;
}
