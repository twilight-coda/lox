#include "common.h"
#include "chunk.h"
#include "debug.h"

int main (int argc, const char* argv[]) {
    Chunk chunk;
    initChunk(&chunk);
    int offset = addConstant(&chunk, 1.2);
    writeChunk(&chunk, OP_CONSTANT, 1);
    writeChunk(&chunk, offset, 1);
    offset = addConstant(&chunk, 42.0);
    writeChunk(&chunk, OP_CONSTANT, 1);
    writeChunk(&chunk, offset, 1);
    writeChunk(&chunk, OP_RETURN, 2);
    disassembleChunk(&chunk, "test chunk");
    freeChunk(&chunk);

    return 0;
}
