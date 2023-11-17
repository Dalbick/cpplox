#include <filesystem>
#include <iostream>
#include <fstream>

#include "vm.hpp"

namespace {
std::string readFile(const char *path) {
    std::ifstream file(path);
    return std::string(std::istreambuf_iterator<char>(file),
                       std::istreambuf_iterator<char>());
}
}
namespace fs = std::filesystem;

int main() {
    std::string path = "../test";
    VM vm;

    for (const auto &entry : fs::directory_iterator(path)) {
        if (entry.is_directory()) {
            for (const auto &subentry : fs::directory_iterator(entry)) {
                vm.interpret(readFile(subentry.path().c_str()).data());
            }
        } else {
            vm.interpret(readFile(entry.path().c_str()).data());
        }
    }

    return 0;
}