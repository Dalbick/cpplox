#ifndef clox_chunk_hpp
#define clox_chunk_hpp

#include <vector>

#include "common.hpp"
#include "value.hpp"

enum class OpCode : uint8_t {
    Constant,
    Add,
    Subtract,
    Multiply,
    Divide,
    Negate,
    Return
};

class Chunk {
   public:
    Chunk();
    void write(uint8_t byte, int line);
    void write(OpCode byte, int line);
    void disassemble(const char *name) const;
    size_t disassembleInstruction(size_t offset) const;
    size_t addConstant(Value value);
    inline const uint8_t *getCode() const {
        return code.data();
    }
    inline const Value *getConstants() const {
        return constants.data();
    }

   private:
    std::vector<uint8_t> code;
    std::vector<Value> constants;
    std::vector<int> lines;
    size_t constantInstruction(const char *name, size_t offset) const;
};

#endif