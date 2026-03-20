#ifndef LAB1_REGEX_H
#define LAB1_REGEX_H

#include <string>
#include <string_view>
#include <regex>
#include "RelationStore.h"
#include "../IPars.h"

class RegExClass : public IPars {
private:
    //мб поделить
    inline static const std::regex createListRegex{
            R"(^\s*create\s+([a-zA-Z_.][a-zA-Z0-9_.]*)\s*\((\s*[a-zA-Z_.][a-zA-Z0-9_.]*(\s*,\s*[a-zA-Z_.][a-zA-Z0-9_.]*)*\s*)\)\s*$)",
            std::regex::optimize
    };

    inline static const std::regex joinListRegex{
            R"(^\s*create\s+([a-zA-Z_.][a-zA-Z0-9_.]*)\s+as\s+([a-zA-Z_.][a-zA-Z0-9_.]*)\s+join\s+([a-zA-Z_.][a-zA-Z0-9_.]*)\s*$)",
            std::regex::optimize
    };

    RelationStore& store;

public:
    explicit RegExClass(RelationStore& relStore);

    std::pair<bool, std::string> pars(std::string_view line);
};


#endif