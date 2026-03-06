#include <vector>
#include <sstream>

#include "RegEx.h"

RegExClass::RegExClass(RelationStore &relStore) : store(relStore) {}

bool RegExClass::pars(std::string_view line) {

    std::smatch match;
    bool operationStatus = true;

    const std::string s(line);

    if(std::regex_match(s, match, createListRegex)) {

        std::vector<std::string> tokens;
        std::stringstream ss(match[2].str());

        std::string token;
        while (std::getline(ss, token, ',')) {
            token.erase(0, token.find_first_not_of(" \t"));
            token.erase(token.find_last_not_of(" \t") + 1);
            tokens.push_back(token);
        }
        store.addRel(match[1].str(), tokens);
    }
    else if (std::regex_match(s, match, joinListRegex)) {
        store.makeJoin(match[1].str(), match[2].str(), match[3].str());
    } else {
        operationStatus = false;
    }
    return operationStatus;
}
