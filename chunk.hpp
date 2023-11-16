#ifndef clox_chunk_hpp
#define clox_chunk_hpp

#include <vector>
#include <string>

#include "common.hpp"
#include "value.hpp"

enum class OpCode : uint8_t { Constant, Return };

class Chunk {
   public:
    Chunk();
    void write(uint8_t byte, int line);
    void write(OpCode byte, int line);
    void disassemble(std::string name) const;
    size_t addConstant(Value value);

   private:
    std::vector<uint8_t> code;
    std::vector<Value> constants;
    std::vector<int> lines;
    size_t disassembleInstruction(size_t offset) const;
    size_t constantInstruction(std::string name, size_t offset) const;
};

#endif