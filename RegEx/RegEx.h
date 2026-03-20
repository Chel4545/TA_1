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
    inline static const std::regex createRegex{
            R"(^\s*create)"
    };

    inline static const std::regex nameRegex{
            R"(^\s+([a-zA-Z_.][a-zA-Z0-9_.]*))"
    };

    inline static const std::regex lparenRegex{
            R"(^\s*\()"
    };

    inline static const std::regex attrRegex{
            R"(^\s*([a-zA-Z_.][a-zA-Z0-9_.]*))"
    };

    inline static const std::regex commaRegex{
            R"(^\s*,)"
    };

    inline static const std::regex rparenRegex{
            R"(^\s*\))"
    };

    inline static const std::regex asRegex{
            R"(^\s+as)"
    };

    inline static const std::regex joinRegex{
            R"(^\s+join)"
    };

    inline static const std::regex endRegex{
            R"(^\s*$)"
    };

    std::string str = "";
    size_t      pos =  0;

    RelationStore& store;

    bool eat(const std::regex& re);

    std::pair<bool, std::string> eatName();

public:
    explicit RegExClass(RelationStore& relStore);

    std::pair<bool, std::string> pars(std::string_view line) override;
};


#endif
