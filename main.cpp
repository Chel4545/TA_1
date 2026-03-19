#include <iostream>
#include <fstream>
#include <string>
#include <memory>


#include "IPars.h"

#ifdef PARSER_REGEX
#include "RegEx.h"
#endif

#ifdef PARSER_SMC
#include "SmcParser.h"
#endif

#ifdef PARSER_FLEX
#include "FlexParser.h"
#endif

#include "RelationStore.h"


int main(int argc, char* argv[]) {
    std::ifstream fileInput;
    std::istream* input = &std::cin;

    std::ofstream fileOutput;
    std::ostream* output = &std::cout;

    if (argc >= 2) {
        fileInput.open(argv[1]);
        if (!fileInput.is_open()) {
            std::cout << "Cannot open fileInput\n";
            return 1;
        }
        input = &fileInput;
    }
    if (argc >= 3) {
        fileOutput.open(argv[2]);
        if (!fileOutput.is_open()) {
            std::cout << "Cannot open fileInput\n";
            return 1;
        }
        output = &fileOutput;
    }
    if (argc > 3) {
        return 1;
    }

    std::string line;
    RelationStore store;
    std::unique_ptr<IPars> Pars;

    #ifdef PARSER_REGEX
        Pars = std::make_unique<RegExClass>(store);
    #elif defined(PARSER_SMC)
        Pars = std::make_unique<SmcParser>(store);
    #elif defined(PARSER_FLEX)
        Pars = std::make_unique<FlexParser>(store);
    #else
        std::cout << "Parser is not selected\n";
        return 1;
    #endif

    while (std::getline(*input, line)) {
        std::pair<bool, std::string> res = Pars->pars(line);
        *output << res.first << " " << res.second << "\n";
    }

    return 0;
}