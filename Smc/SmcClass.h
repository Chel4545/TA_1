//удалить

#ifndef LAB1_CMSCLASS_H
#define LAB1_CMSCLASS_H

#include <string>
#include <vector>
#include <utility>
#include "../Store/RelationStore.h"
#include "Tokenizer.h"

enum class Command {
    NONE,
    CREATE_LIST,
    CREATE_JOIN
};

class SmcClass {
private:
    RelationStore& store;

    std::string name0;
    std::string name1;
    std::string name2;
    std::vector<std::string> attributes;

    Command currentCommand = Command::NONE;

    bool lineOk = true;

public:
    explicit SmcClass(RelationStore& relStore);

    void setName0(const std::string& name);
    void setName1(const std::string& name);
    void setName2(const std::string& name);

    void setAttribute(const std::string& attr);

    void setCreateList();
    void setCreateJoin();

    void executeCommand() const;

    void syntaxError();
    void resetLine();

    bool isLineOk() const;

    bool IsCreate(const Token& token) const { return token.type == TokenType::CREATE; }
    bool IsAs(const Token& token) const { return token.type == TokenType::AS; }
    bool IsJoin(const Token& token) const { return token.type == TokenType::JOIN; }
    bool IsId(const Token& token) const { return token.type == TokenType::ID; }
    bool IsLParen(const Token& token) const { return token.type == TokenType::LPAREN; }
    bool IsRParen(const Token& token) const { return token.type == TokenType::RPAREN; }
    bool IsComma(const Token& token) const { return token.type == TokenType::COMMA; }
    bool IsEol(const Token& token) const { return token.type == TokenType::EOL; }
    bool IsInvalid(const Token& token) const { return token.type == TokenType::INVALID; }
};

#endif
