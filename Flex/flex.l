%{
#include <iostream>
#include "../Store/RelationStore.h"

#ifdef __cplusplus
#define YY_DECL extern "C" int yylex(void)
#else
#define YY_DECL int yylex(void)
#endif

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

%}

%%
create                  { return static_cast<int>(Token::COMMAND_CREATE); }
as                      { return static_cast<int>(Token::COMMAND_AS);     }
join                    { return static_cast<int>(Token::COMMAND_JOIN);   }

[a-zA-Z_][a-zA-Z0-9_.]* { return static_cast<int>(Token::ID_NAME);        }

","                     { return static_cast<int>(Token::SYMBOL_COMMA);  }
"("                     { return static_cast<int>(Token::SYMBOL_LPAREN); }
")"                     { return static_cast<int>(Token::SYMBOL_RPAREN); }

[ \t]+              ;

.                       { return static_cast<int>(Token::ERROR);         }
%%


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

    bool pars(std::string_view line) {
        state = State::START;
        attributes.clear();
        currentCommand = CommandType::NONE;

        YY_BUFFER_STATE buf = yy_scan_bytes(line.data(), (int)line.size());

        int raw = 0;
        while ((raw = yylex()) != 0) {

            Token token = static_cast<Token>(raw);

            switch (state) {
                //1 команда
                case State::START:
                    if (token == Token::COMMAND_CREATE) {
                        state = State::GOT_CREATE;
                    } else {
                        state = State::ERROR_STATE;
                    }
                    break;
                case State::GOT_CREATE:
                    if (token == Token::ID_NAME) {
                        name0 = yytext;
                        state = State::GOT_NAME;
                    } else {
                        state = State::ERROR_STATE;
                    }
                    break;
                case State::GOT_NAME:
                    if (token == Token::SYMBOL_LPAREN) {
                        state = State::IN_LIST;
                    } else if (token == Token::COMMAND_AS) {
                        state = State::GOT_AS;
                    } else {
                        state = State::ERROR_STATE;
                    }
                    break;
                case State::IN_LIST:
                    if (token == Token::ID_NAME) {
                        attributes.emplace_back(yytext);
                        state = State::AFTER_ID;
                    } else {
                        state = State::ERROR_STATE;
                    }
                    break;
                case State::AFTER_ID:
                    if (token == Token::SYMBOL_COMMA) {
                        state = State::IN_LIST;
                    } else if (token == Token::SYMBOL_RPAREN) {
                        currentCommand = CommandType::CREATE_LIST;
                        state = State::END;
                    } else {
                        state = State::ERROR_STATE;
                    }
                    break;

                    //2 команда
                case State::GOT_AS:
                    if (token == Token::ID_NAME) {
                        name1 = yytext;
                        state = State::GOT_NAME_AS;
                    } else {
                        state = State::ERROR_STATE;
                    }
                    break;
                case State::GOT_NAME_AS:
                    if (token == Token::COMMAND_JOIN) {
                        state = State::GOT_JOIN;
                    } else {
                        state = State::ERROR_STATE;
                    }
                    break;
                case State::GOT_JOIN:
                    if (token == Token::ID_NAME) {
                        name2 = yytext;
                        currentCommand = CommandType::CREATE_JOIN;
                        state = State::END;
                    } else {
                        state = State::ERROR_STATE;
                    }
                    break;
                case State::ERROR_STATE:
                    break;
                case State::END:
                    if (currentCommand == CommandType::CREATE_LIST) {
                        store.addRel(name0, attributes);
                    } else if (currentCommand == CommandType::CREATE_JOIN) {
                        store.makeJoin(name0, name1, name2);
                    }
                    break;
            }

            if (state == State::ERROR_STATE) {
                break;
            }

            if (state == State::END) {
                if (currentCommand == CommandType::CREATE_LIST) {
                    store.addRel(name0, attributes);
                } else if (currentCommand == CommandType::CREATE_JOIN) {
                    store.makeJoin(name0, name1, name2);
                }
                state = State::START;
                attributes.clear();
                currentCommand = CommandType::NONE;
                break;
            }
        }

        yy_delete_buffer(buf);

        if (state == State::END) {
            std::cout << "Commands is correct\n";
        } else {
            std::cout << "Syntax error\n";
        }

        return state != State::ERROR_STATE;
    }
};
