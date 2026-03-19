#ifndef LAB1_FLEXPARSER_H
#define LAB1_FLEXPARSER_H

#include <string>
#include <string_view>
#include <string_view>
#include <utility>

#include "../IPars.h"
#include "../Store/RelationStore.h"

enum class Token {
    START = 1,
    COMMAND_CREATE,
    COMMAND_AS,
    COMMAND_JOIN,
    ID_NAME,
    SYMBOL_COMMA,
    SYMBOL_LPAREN,
    SYMBOL_RPAREN,
    ERROR
};

enum class State {
    START = 1,
    GOT_CREATE,
    GOT_NAME,
    GOT_NAME_AS,
    IN_LIST,
    GOT_AS,
    GOT_JOIN,
    AFTER_ID,
    END,
    ERROR_STATE
};

enum class CommandType {
    NONE,
    CREATE_LIST,
    CREATE_JOIN
};

class FlexParser : public IPars {
private:
    State state = State::START;

    std::string name0;
    std::string name1;
    std::string name2;

    std::vector<std::string> attributes;

    RelationStore& store;
    CommandType currentCommand = CommandType::NONE;

public:
    explicit FlexParser(RelationStore& s) : store(s) {};

    std::pair<bool, std::string> pars(std::string_view line) override;
};

#endif
