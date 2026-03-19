#include <vector>
#include <sstream>

#include "RegEx.h"

RegExClass::RegExClass(RelationStore &relStore) : store(relStore) {}

std::pair<bool, std::string> RegExClass::pars(std::string_view line) {

    std::smatch match;
    const std::string s(line);

    if(std::regex_match(s, match, createListRegex)) {

        std::vector<std::string> tokens;
        /*std::stringstream ss(match[2].str());

        std::string token;
        while (std::getline(ss, token, ',')) {
            token.erase(0, token.find_first_not_of(" \t"));
            token.erase(token.find_last_not_of(" \t") + 1);
            tokens.push_back(token);
        }*/
        bool ok = store.addRel(match[1].str(), tokens);
        return ok
               ? std::make_pair(true, "Make create: " + s)
               : std::make_pair(false, "Create failed");
    }
    else if (std::regex_match(s, match, joinListRegex)) {
        bool ok = store.makeJoin(match[1].str(), match[2].str(), match[3].str());
        return ok
               ? std::make_pair(true, "Make join: " + s)
               : std::make_pair(false, "Join failed");
    }
    return {false, "Unknown command"};
}
