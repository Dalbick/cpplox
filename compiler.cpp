#include <iostream>
#include <format>

#include "compiler.hpp"
#include "scanner.hpp"

void compile(const char *source) {
    Scanner scanner(source);
    int line = -1;
    for (;;) {
        Token token = scanner.scanToken();
        if (token.line != line) {
            std::cout << std::format("{:4} ", token.line);
            line = token.line;
        } else {
            std::cout << "   | ";
        }
        std::cout << std::format("{:2} '{:.{}}'\n",
                                 static_cast<uint8_t>(token.type), token.start,
                                 token.length);

        if (token.type == TokenType::Eof) break;
    }
}