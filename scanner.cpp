#include <cstring>

#include "scanner.hpp"

inline bool isDigit(char c) {
    return c >= '0' && c <= '9';
}

inline bool isAlpha(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_';
}

Scanner::Scanner(const char *source)
    : start(source), current(source), line(1) {}

Token Scanner::scanToken() {
    skipWhitespace();
    start = current;
    if (isAtEnd()) return makeToken(TokenType::Eof);

    char c = advance();
    if (isDigit(c)) return number();
    if (isAlpha(c)) return identifier();

    switch (c) {
        case '(': return makeToken(TokenType::LeftParen);
        case ')': return makeToken(TokenType::RightParen);
        case '{': return makeToken(TokenType::LeftBrace);
        case '}': return makeToken(TokenType::RightBrace);
        case ';': return makeToken(TokenType::Semicolon);
        case ',': return makeToken(TokenType::Comma);
        case '.': return makeToken(TokenType::Dot);
        case '-': return makeToken(TokenType::Minus);
        case '+': return makeToken(TokenType::Plus);
        case '/': return makeToken(TokenType::Slash);
        case '*': return makeToken(TokenType::Star);
        case '!':
            return makeToken(match('=') ? TokenType::BangEqual
                                        : TokenType::Bang);
        case '=':
            return makeToken(match('=') ? TokenType::EqualEqual
                                        : TokenType::Equal);
        case '<':
            return makeToken(match('=') ? TokenType::LessEqual
                                        : TokenType::Less);
        case '>':
            return makeToken(match('=') ? TokenType::GreaterEqual
                                        : TokenType::Greater);
        case '"': return string();
    }

    return errorToken("Unexpected character.");
}

Token Scanner::string() {
    while (peek() != '"' && !isAtEnd()) {
        if (peek() == '\n') line++;
        advance();
    }
    if (isAtEnd()) return errorToken("Unterminated string.");

    advance();
    return makeToken(TokenType::String);
}

Token Scanner::number() {
    while (isDigit(peek())) advance();

    if (peek() == '.' && isDigit(peekNext())) {
        advance();
        while (isDigit(peek())) advance();
    }

    return makeToken(TokenType::Number);
}

Token Scanner::identifier() {
    while (isAlpha(peek()) || isDigit(peek())) advance();
    return makeToken(identifierType());
}

TokenType Scanner::identifierType() const {
    switch (start[0]) {
        case 'a': return checkKeyword(1, "nd", TokenType::And);
        case 'c': return checkKeyword(1, "lass", TokenType::Class);
        case 'e': return checkKeyword(1, "lse", TokenType::Else);
        case 'i': return checkKeyword(1, "f", TokenType::If);
        case 'n': return checkKeyword(1, "il", TokenType::Nil);
        case 'o': return checkKeyword(1, "r", TokenType::Or);
        case 'p': return checkKeyword(1, "rint", TokenType::Print);
        case 'r': return checkKeyword(1, "eturn", TokenType::Return);
        case 's': return checkKeyword(1, "uper", TokenType::Super);
        case 'v': return checkKeyword(1, "ar", TokenType::Var);
        case 'w': return checkKeyword(1, "hile", TokenType::While);
        case 'f':
            if (current - start > 1) {
                switch (start[1]) {
                    case 'a': return checkKeyword(2, "lse", TokenType::False);
                    case 'o': return checkKeyword(2, "r", TokenType::For);
                    case 'u': return checkKeyword(2, "n", TokenType::Fun);
                }
            }
            break;
        case 't':
            if (current - start > 1) {
                switch (start[1]) {
                    case 'h': return checkKeyword(2, "is", TokenType::This);
                    case 'r': return checkKeyword(2, "ue", TokenType::True);
                }
            }
            break;
    }
    return TokenType::Identifier;
}

TokenType Scanner::checkKeyword(int start, std::string rest,
                                TokenType type) const {
    if ((size_t)(current - this->start) == start + rest.size() &&
        memcmp(this->start + start, rest.data(), rest.size()) == 0) {
        return type;
    }
    return TokenType::Identifier;
}

inline bool Scanner::isAtEnd() const {
    return *current == '\0';
}

inline Token Scanner::makeToken(TokenType type) const {
    return {type, start, (size_t)(current - start), line};
}

inline Token Scanner::errorToken(const char *message) const {
    return {TokenType::Error, message, strlen(message), line};
}

inline char Scanner::advance() {
    return *(current++);
}

bool Scanner::match(char expected) {
    if (isAtEnd()) return false;
    if (*current != expected) return false;
    current++;
    return true;
}

void Scanner::skipWhitespace() {
    for (;;) {
        switch (peek()) {
            case ' ':
            case '\r':
            case '\t': advance(); break;
            case '/':
                if (peekNext() == '/') {
                    while (peek() != '\n' && !isAtEnd()) advance();
                } else {
                    return;
                }
                break;
            default: return;
        }
    }
}

inline char Scanner::peek() const {
    return *current;
}

inline char Scanner::peekNext() const {
    if (isAtEnd()) return '\0';
    return current[1];
}