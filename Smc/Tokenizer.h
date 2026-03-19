#ifndef LAB1_TOKENIZER_H
#define LAB1_TOKENIZER_H

#include <string>
#include <string_view>
#include <utility>
#include <vector>
#include "SmcClass.h"
#include "Tokens.h"

class Tokenizer {
public:
    std::vector<TokenStruct> getTokens(std::string_view line);

private:
    std::string input;
    std::size_t pos = 0;
    std::vector<TokenStruct> tokens;

    inline static const std::string CREATE_KW = "create";
    inline static const std::string AS_KW     = "as";
    inline static const std::string JOIN_KW   = "join";

    inline static constexpr char LPAREN_CH = '(';
    inline static constexpr char RPAREN_CH = ')';
    inline static constexpr char COMMA_CH  = ',';

private:

    std::vector<TokenStruct> tokenize();
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
