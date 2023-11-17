#include "chunk.hpp"

Chunk::Chunk() {}

void Chunk::write(uint8_t byte, int line) {
    code.push_back(byte);
    lines.push_back(line);
}

void Chunk::write(OpCode byte, int line) {
    write(static_cast<uint8_t>(byte), line);
}

size_t Chunk::addConstant(Value value) {
    constants.push_back(value);
    return constants.size() - 1;
}
