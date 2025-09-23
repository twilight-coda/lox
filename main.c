#include "common.h"
#include "chunk.h"
#include "debug.h"
#include "vm.h"

int main (int argc, const char* argv[]) {
    initVM();
    Chunk chunk;
    initChunk(&chunk);
    int offset = addConstant(&chunk, 2.2);
    writeChunk(&chunk, OP_CONSTANT, 1);
    writeChunk(&chunk, offset, 1);
    // offset = addConstant(&chunk, 43.0);
    // writeChunk(&chunk, OP_CONSTANT, 1);
    // writeChunk(&chunk, offset, 1);
    // writeChunk(&chunk, OP_MULTIPLY, 1);
    for (int i = 0; i < 1000000; i++) {
        writeChunk(&chunk, OP_NEGATE, 2);
    }
    writeChunk(&chunk, OP_RETURN, 2);
    // disassembleChunk(&chunk, "test chunk");
    interpret(&chunk);
    freeVM();
    freeChunk(&chunk);

    return 0;
}
