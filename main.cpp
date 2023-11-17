#include "common.hpp"
#include "chunk.hpp"
#include "vm.hpp"

int main(int, const char *[]) {
    VM vm;

    Chunk chunk;
    size_t constant = chunk.addConstant(1.2);
    chunk.write(OpCode::Constant, 123);
    chunk.write(constant, 123);

    constant = chunk.addConstant(3.4);
    chunk.write(OpCode::Constant, 123);
    chunk.write(constant, 123);

    chunk.write(OpCode::Add, 123);

    constant = chunk.addConstant(5.6);
    chunk.write(OpCode::Constant, 123);
    chunk.write(constant, 123);

    chunk.write(OpCode::Divide, 123);
    chunk.write(OpCode::Negate, 123);

    chunk.write(OpCode::Return, 123);
    chunk.disassemble("test chunk");

    vm.interpret(&chunk);

    return 0;
}