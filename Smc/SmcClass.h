#ifndef LAB1_CMSCLASS_H
#define LAB1_CMSCLASS_H

#include <string>
#include <vector>
#include <utility>
#include "../Store/RelationStore.h"

enum class CommandType
{
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

    CommandType currentCommand = CommandType::NONE;

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
};

#endif
