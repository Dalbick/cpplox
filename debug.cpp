#include <iostream>
#include <format>

#include "common.hpp"
#include "chunk.hpp"

namespace {
size_t simpleInstruction(std::string name, size_t offset) {
    std::cout << std::format("{}\n", name);
    return offset + 1;
}
}

void Chunk::disassemble(std::string name) const {
    std::cout << std::format("== {} ==\n", name);

    for (size_t offset = 0; offset < code.size();) {
        offset = this->disassembleInstruction(offset);
    }

    std::cout << std::flush;
}

size_t Chunk::disassembleInstruction(size_t offset) const {
    std::cout << std::format("{:04} ", offset);

    if (offset > 0 && lines[offset] == lines[offset - 1]) {
        std::cout << "   | ";
    } else {
        std::cout << std::format("{:4} ", lines[offset]);
    }

    uint8_t instruction = code[offset];
    switch (static_cast<OpCode>(instruction)) {
        case OpCode::Constant:
            return constantInstruction("OP_CONSTANT", offset);
        case OpCode::Return:
            return simpleInstruction("OP_RETURN", offset);
        default:
            std::cout << std::format("Unknown opcode {}\n", instruction);
            return offset + 1;
    }
}

size_t Chunk::constantInstruction(std::string name, size_t offset) const {
    uint8_t constant = code[offset + 1];
    std::cout << std::format("{:16} {:4} '", name, constant);
    printValue(constants[constant]);
    std::cout << "'\n";
    return offset + 2;
}