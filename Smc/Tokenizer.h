#ifndef LAB1_TOKENIZER_H
#define LAB1_TOKENIZER_H

#include <string>
#include <string_view>
#include <utility>
#include <vector>
#include "SmcClass.h"

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

struct Token {
    TokenType type;
    std::string text;
};

class Tokenizer {
public:
    std::pair<bool, std::string> parse(std::string_view line);

private:
    std::string input;
    std::size_t pos = 0;
    std::vector<Token> tokens;
    SmcClass& ctxt;

    inline static const std::string CREATE_KW = "create";
    inline static const std::string AS_KW     = "as";
    inline static const std::string JOIN_KW   = "join";

    inline static constexpr char LPAREN_CH = '(';
    inline static constexpr char RPAREN_CH = ')';
    inline static constexpr char COMMA_CH  = ',';

private:
    explicit Tokenizer(SmcClass& newSmcCalss) : ctxt(newSmcCalss) {}

    std::vector<Token> tokenize(const std::string& line);
    bool getCreate();
    bool skipNecSpace();
    bool skipOptSpace();
    bool getName();
    bool getRightBracket();
    bool getLeftBracket();
    bool getComma();
    bool getAs();
    bool getJoin();
};

#endif
