%option noyywrap
%type Token
%{
#include <iostream>
#include <string>
#include "FlexParser.h"

#define YY_DECL int yylex(void)

%}

%%
create                  { return static_cast<int>(Token::COMMAND_CREATE); }
as                      { return static_cast<int>(Token::COMMAND_AS);     }
join                    { return static_cast<int>(Token::COMMAND_JOIN);   }

[a-zA-Z_][a-zA-Z0-9_.]* { return static_cast<int>(Token::ID_NAME);        }

","                     { return static_cast<int>(Token::SYMBOL_COMMA);  }
"("                     { return static_cast<int>(Token::SYMBOL_LPAREN); }
")"                     { return static_cast<int>(Token::SYMBOL_RPAREN); }

[ \t\r]+              ;

.                       { return static_cast<int>(Token::ERROR);         }
%%



std::pair<bool, std::string> FlexParser::pars(std::string_view line) {
    state = State::START;
    attributes.clear();
    currentCommand = CommandType::NONE;

    std::string s(line);
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
                    state = State::ERROR_STATE;
                    break;
            }

            if (state == State::ERROR_STATE) {
                yy_delete_buffer(buf);
                return {false, "Unknown command"};
            }
        }

        yy_delete_buffer(buf);

        if (state != State::END) {
            return {false, "Unknown command"};
        }

        if (currentCommand == CommandType::CREATE_LIST) {
            bool ok = store.addRel(name0, attributes);
            return ok
                ? std::make_pair(true, "Make create: " + s)
                : std::make_pair(false, "Create failed");
        }

        if (currentCommand == CommandType::CREATE_JOIN) {
            bool ok = store.makeJoin(name0, name1, name2);
            return ok
                ? std::make_pair(true, "Make join: " + s)
                : std::make_pair(false, "Join failed");
        }

        return {false, "Unknown command"};
}
