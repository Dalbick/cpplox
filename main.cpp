#include "common.hpp"
#include "chunk.hpp"

int main(int, const char *[]) {
    Chunk chunk;

    size_t constant = chunk.addConstant(1.2);
    chunk.write(OpCode::Constant, 123);
    chunk.write(constant, 123);

    chunk.write(OpCode::Return, 123);
    chunk.disassemble("test chunk");

    return 0;
}