#ifndef LAB1_TOCKENS_H
#define LAB1_TOCKENS_H

#include <string>

enum class TokenType {
    CREATE,
    AS,
    JOIN,
    ID,
    LPAREN,
    RPAREN,
    COMMA,
    EOL,
    INVALID
};

struct TokenStruct {
    TokenType type;
    std::string text;
};

#endif
