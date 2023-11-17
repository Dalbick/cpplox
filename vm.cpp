#include <iostream>

#include "vm.hpp"
#include "compiler.hpp"

InterpretResult VM::interpret(const char *source) {
    compile(source);
    return InterpretResult::Ok;
}

InterpretResult VM::run() {
#define BINARY_OP(op)     \
    do {                  \
        double b = pop(); \
        double a = pop(); \
        push(a op b);     \
    } while (false)
    OpCode instruction;
    for (;;) {
#ifdef DEBUG_TRACE_EXECUTION
        std::cout << "          ";
        for (Value slot : stack) {
            std::cout << "[ ";
            printValue(slot);
            std::cout << " ]";
        }
        std::cout << "\n";
        chunk->disassembleInstruction(ip - chunk->getCode());
#endif
        switch (instruction = static_cast<OpCode>(readByte())) {
            case OpCode::Constant: {
                Value constant = readConstant();
                push(constant);
                break;
            }
            case OpCode::Add: BINARY_OP(+); break;
            case OpCode::Subtract: BINARY_OP(-); break;
            case OpCode::Multiply: BINARY_OP(*); break;
            case OpCode::Divide: BINARY_OP(/); break;
            case OpCode::Negate: push(-pop()); break;
            case OpCode::Return: {
                printValue(pop());
                std::cout << std::endl;
                return InterpretResult::Ok;
            }
        }
    }
#undef BINARY_OP
}

inline uint8_t VM::readByte() {
    return *ip++;
}

inline Value VM::readConstant() {
    return chunk->getConstants()[readByte()];
}

inline void VM::push(Value value) {
    stack.push_back(value);
}

inline Value VM::pop() {
    Value value = stack.back();
    stack.pop_back();
    return value;
}