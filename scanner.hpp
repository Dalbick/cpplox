#ifndef clox_scanner_hpp
#define clox_scanner_hpp

#include <string>

#include "common.hpp"

enum class TokenType {
    // Single-character tokens.
    LeftParen,
    RightParen,
    LeftBrace,
    RightBrace,
    Comma,
    Dot,
    Minus,
    Plus,
    Semicolon,
    Slash,
    Star,
    // One or two character tokens.
    Bang,
    BangEqual,
    Equal,
    EqualEqual,
    Greater,
    GreaterEqual,
    Less,
    LessEqual,
    // Literals.
    Identifier,
    String,
    Number,
    // Keywords.
    And,
    Class,
    Else,
    False,
    For,
    Fun,
    If,
    Nil,
    Or,
    Print,
    Return,
    Super,
    This,
    True,
    Var,
    While,

    Error,
    Eof
};

struct Token {
    TokenType type;
    const char *start;
    size_t length;
    int line;
};

class Scanner {
   public:
    Scanner(const char *source);
    Token scanToken();

   private:
    const char *start;
    const char *current;
    int line;

    Token string();
    Token number();
    Token identifier();
    TokenType identifierType() const;
    TokenType checkKeyword(int start, std::string rest, TokenType type) const;
    bool isAtEnd() const;
    Token makeToken(TokenType type) const;
    Token errorToken(const char *message) const;
    char advance();
    bool match(char expected);
    void skipWhitespace();
    char peek() const;
    char peekNext() const;
};

#endif