#include <fstream>
#include <regex>
#include "RegEx.h"

static std::regex createListRegex(
        R"(^\s*create\s+([a-zA-Z_.][a-zA-Z0-9_.]*)\s*\((\s*[a-zA-Z_.][a-zA-Z0-9_.]*(\s*,\s*[a-zA-Z_.][a-zA-Z0-9_.]*)*\s*)\)\s*$)"
);

static std::regex joinListRegex(
        R"(^\s*create\s+([a-zA-Z_.][a-zA-Z0-9_.]*)\s+as\s+([a-zA-Z_.][a-zA-Z0-9_.]*)\s+join\s+([a-zA-Z_.][a-zA-Z0-9_.]*)\s*$)"
);

bool checkComandRegex(const std::string& fileName, RelationStore& relStor) {
    std::ifstream file(fileName);
    if (!file.is_open()) return false;

    std::string line;
    std::smatch match;
    bool operationStatus = true;

    while (std::getline(file, line)) {
        if(std::regex_match(line, match, createListRegex)) {

            std::vector<std::string> tokens;
            std::stringstream ss(match[2]);
            std::string token;
            while (std::getline(ss, token, ',')) {
                token.erase(0, token.find_first_not_of(" \t"));
                token.erase(token.find_last_not_of(" \t") + 1);
                tokens.push_back(token);
            }
            relStor.addRel(match[1], tokens);
        }
        else if (std::regex_match(line, match, joinListRegex)) {
            relStor.makeJoin(match[1], match[2], match[3]);
        } else {
            operationStatus = false;
            continue;
        }
    }
    return operationStatus;
}