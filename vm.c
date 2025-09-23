#include <stdio.h>

#include "vm.h"

VM vm;

void resetStack() {
    vm.stackTop = vm.stack;
}

void initVM() {
    resetStack();
}

void freeVM() {}

InterpretResult run() {
    #define READ_BYTE() (*(vm.ip)++)
    #define READ_CONSTANT() ( (vm.chunk)->constants.values[READ_BYTE()] )
    #define BINARY_OP(op)\
    do {\
        Value right = pop();\
        Value left = pop();\
        Value value = left op right;\
        push(value);\
    } while(false)

    while (true) {
        #ifdef DEBUG_TRACE_EXECUTION
            printf("    ");
            for (Value *it = vm.stack; it < vm.stackTop; it++) {
                printf("[");
                printValue(*it);
                printf("]");
            }
            printf("\n");
            disassembleInstruction(vm.chunk, (int)(vm.ip - vm.chunk->code));
        #endif
        uint8_t instr = READ_BYTE();
        switch (instr) {
            case OP_RETURN: {
                printValue(pop());
                printf("\n");
                return INTERPRET_OK;
            }
            case OP_CONSTANT: {
                Value constant = READ_CONSTANT();
                push(constant);
                printf("\n");
                break;
            }
            case OP_NEGATE: {
                Value *top = vm.stackTop - 1;
                *top = -(*top);
                break;
            }
            case OP_ADD: {
                BINARY_OP(+);
                break;
            }
            case OP_SUBTRACT: {
                BINARY_OP(-);
                break;
            }
            case OP_MULTIPLY: {
                BINARY_OP(*);
                break;
            }
            case OP_DIVIDE: {
                BINARY_OP(/);
                break;
            }
            default:
                break;
        }
    }
    #undef READ_BYTE
    #undef READ_CONSTANT
    #undef BINARY_OP
}

InterpretResult interpret(Chunk *chunk) {
    vm.chunk = chunk;
    vm.ip = chunk->code;
    return run();
}

void push(Value value) {
    *vm.stackTop = value;
    vm.stackTop++;
}

Value pop() {
    vm.stackTop--;
    return *vm.stackTop;
}
