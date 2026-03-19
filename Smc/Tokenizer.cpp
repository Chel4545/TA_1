#include "Tokenizer.h"
#include "SmcClass.h"
#include "../Store/RelationStore.h"

#include <cctype>
#include <string_view>
#include <utility>

std::vector<TokenStruct> Tokenizer::getTokens(std::string_view line) {
    input = std::string(line);
    pos = 0;
    tokens.clear();

    return tokenize();
}

std::vector<TokenStruct> Tokenizer::tokenize() {

    while (pos < input.size()) {
        skipOptSpace();

        if (pos >= input.size()) {
            break;
        }

        if (getCreate()) {
            skipNecSpace();
            continue;
        }
        if (getAs()) {
            skipNecSpace();
            continue;
        }
        if (getJoin()) {
            skipNecSpace();
            continue;
        }
        if (getName()) {
            skipNecSpace();
            continue;
        }
        if (getLeftBracket()) {
            continue;
        }
        if (getRightBracket()) {
            continue;
        }
        if (getComma()) {
            continue;
        }

        tokens.push_back({TokenType::INVALID, std::string(1, input[pos])});
        ++pos;
    }

    tokens.push_back({TokenType::EOL, ""});
    return tokens;
}

bool Tokenizer::getCreate() {
    if (input.compare(pos, CREATE_KW.size(), CREATE_KW) != 0) {
        return false;
    }

    if (pos + CREATE_KW.size() < input.size()) {
        char next = input[pos + CREATE_KW.size()];
        if (!std::isspace(static_cast<unsigned char>(next))) {
            return false;
        }
    }

    tokens.push_back({TokenType::CREATE, CREATE_KW});
    pos += CREATE_KW.size();
    return true;
}

bool Tokenizer::getAs() {
    if (input.compare(pos, AS_KW.size(), AS_KW) != 0) {
        return false;
    }

    if (pos + AS_KW.size() < input.size()) {
        char next = input[pos + AS_KW.size()];
        if (!std::isspace(static_cast<unsigned char>(next))) {
            return false;
        }
    }

    tokens.push_back({TokenType::AS, AS_KW});
    pos += AS_KW.size();
    return true;
}

bool Tokenizer::getJoin() {
    if (input.compare(pos, JOIN_KW.size(), JOIN_KW) != 0) {
        return false;
    }

    if (pos + JOIN_KW.size() < input.size()) {
        char next = input[pos + JOIN_KW.size()];
        if (!std::isspace(static_cast<unsigned char>(next))) {
            return false;
        }
    }

    tokens.push_back({TokenType::JOIN, JOIN_KW});
    pos += JOIN_KW.size();
    return true;
}

bool Tokenizer::skipNecSpace() {
    if (pos >= input.size() ||
        !std::isspace(static_cast<unsigned char>(input[pos]))) {
        return false;
    }

    while (pos < input.size() &&
           std::isspace(static_cast<unsigned char>(input[pos]))) {
        ++pos;
    }

    return true;
}

bool Tokenizer::skipOptSpace() {
    while (pos < input.size() &&
           std::isspace(static_cast<unsigned char>(input[pos]))) {
        ++pos;
    }

    return true;
}

bool Tokenizer::getName() {
    if (pos >= input.size()) return false;

    char c = input[pos];
    if (!(std::isalpha(static_cast<unsigned char>(c)) || c == '_' || c == '.')) {
        return false;
    }

    std::string name;
    while (pos < input.size()) {
        char ch = input[pos];
        if (std::isalnum(static_cast<unsigned char>(ch)) || ch == '_' || ch == '.') {
            name += ch;
            ++pos;
        } else {
            break;
        }
    }

    tokens.push_back({TokenType::ID, name});
    return true;
}

bool Tokenizer::getRightBracket() {

    if (pos >= input.size() || input[pos] != RPAREN_CH) {
        return false;
    }

    tokens.push_back({TokenType::RPAREN, std::string(1, RPAREN_CH)});
    pos++;
    return true;
}

bool Tokenizer::getLeftBracket() {

    if (pos >= input.size() || input[pos] != LPAREN_CH) {
        return false;
    }

    tokens.push_back({TokenType::LPAREN, std::string(1, LPAREN_CH)});
    pos++;
    return true;
}

bool Tokenizer::getComma() {

    if (pos >= input.size() || input[pos] != COMMA_CH) {
        return false;
    }

    tokens.push_back({TokenType::COMMA, std::string(1, COMMA_CH)});
    pos++;
    return true;
}