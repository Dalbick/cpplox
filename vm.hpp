#ifndef clox_vm_hpp
#define clox_vm_hpp

#include "chunk.hpp"

enum class InterpretResult { Ok, CompileError, RuntimeError };

class VM {
   public:
    VM() = default;
    InterpretResult interpret(const char* source);

   private:
    const Chunk *chunk;
    const uint8_t *ip;
    std::vector<Value> stack;

    InterpretResult run();
    uint8_t readByte();
    Value readConstant();
    
    void push(Value value);
    Value pop();
};

#endif