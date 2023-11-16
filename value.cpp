#include <iostream>
#include <format>

#include "value.hpp"

void printValue(Value value) {
    std::cout << std::format("{:#g}", value);
}