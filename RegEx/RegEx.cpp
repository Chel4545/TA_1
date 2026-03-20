#include <vector>
#include <sstream>

#include "RegEx.h"

RegExClass::RegExClass(RelationStore &relStore) : store(relStore) {}

bool RegExClass::eat(const std::regex& re) {
    std::smatch match;
    std::string tail = str.substr(pos);

    if (std::regex_search(tail, match, re)) {
        pos += match.length();
        return true;
    }

    return false;
}

std::pair<bool, std::string> RegExClass::eatName() {
    std::smatch match;
    std::string tail = str.substr(pos);

    if (std::regex_search(tail, match, nameRegex)) {
        pos += match.length();
        return {true, match[1].str()};
    }

    return {false, ""};
}

std::pair<bool, std::string> RegExClass::pars(std::string_view line) {

    str = std::string(line);
    pos = 0;

    //create
    if (!eat(createRegex)) {
        return {false, "Unknown command"};
    }
    //name
    auto [okName0, name0] = eatName();
    if (!okName0) {
        return {false, "Unknown command"};
    }

    {
        std::size_t savePos = pos;
        std::vector<std::string> attrs;

        if (eat(lparenRegex)) {
            auto [okAttr, attr] = eatName();
            if (!okAttr) {
                return {false, "Unknown command"};
            }
            attrs.push_back(attr);

            while (true) {
                std::size_t commaPos = pos;

                if (!eat(commaRegex)) {
                    pos = commaPos;
                    break;
                }

                auto [okNextAttr, nextAttr] = eatName();
                if (!okNextAttr) {
                    return {false, "Unknown command"};
                }
                attrs.push_back(nextAttr);
            }

            if (!eat(rparenRegex)) {
                return {false, "Unknown command"};
            }

            if (!eat(endRegex)) {
                return {false, "Unknown command"};
            }

            bool ok = store.addRel(name0, attrs);
            return ok
                   ? std::make_pair(true, "Make create: " + str)
                   : std::make_pair(false, "Create failed");
        }

        pos = savePos;
    }


    if (!eat(asRegex)) {
        return {false, "Unknown command"};
    }

    auto [okName1, name1] = eatName();
    if (!okName1) {
        return {false, "Unknown command"};
    }

    if (!eat(joinRegex)) {
        return {false, "Unknown command"};
    }

    auto [okName2, name2] = eatName();
    if (!okName2) {
        return {false, "Unknown command"};
    }

    if (!eat(endRegex)) {
        return {false, "Unknown command"};
    }

    bool ok = store.makeJoin(name0, name1, name2);
    return ok
           ? std::make_pair(true, "Make join: " + str)
           : std::make_pair(false, "Join failed");
}
