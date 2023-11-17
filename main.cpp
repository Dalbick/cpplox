#include <iostream>
#include <fstream>
#include <format>

#include "common.hpp"
#include "chunk.hpp"
#include "vm.hpp"

namespace {
void repl(VM &vm) {
    std::string line;
    for (;;) {
        std::cout << "> " << std::flush;
        std::getline(std::cin, line);
        vm.interpret(line.data());
    }
}
std::string readFile(const char *path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        std::cerr << std::format("Could not open file\"{}\".\n", path);
        exit(74);
    }
    return std::string(std::istreambuf_iterator<char>(file),
                       std::istreambuf_iterator<char>());
}

void runFile(const char *path, VM &vm) {
    std::string source = readFile(path);
    InterpretResult result = vm.interpret(source.data());

    if (result == InterpretResult::CompileError) exit(65);
    if (result == InterpretResult::RuntimeError) exit(70);
}
}

int main(int argc, const char *argv[]) {
    VM vm;

    if (argc == 1) {
        repl(vm);
    } else if (argc == 2) {
        runFile(argv[1], vm);
    } else {
        std::cerr << "Usage: clox [path]\n";
        exit(64);
    }

    return 0;
}