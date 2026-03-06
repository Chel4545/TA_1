#include <iostream>
#include <fstream>
#include <string>
#include <memory>


#include "IPars.h"
#include "RegEx.h"
#include "SmcClass.h"
//#include "lex.yy.c"
#include "RelationStore.h"


int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << "No input file\n";
        return 1;
    }

    std::ifstream file(argv[2]);

    if (!file.is_open()) {
        std::cout << "Cannot open file\n";
        return 1;
    }

    std::string line;
    RelationStore store;
    std::unique_ptr<IPars> Pars = std::make_unique<RegExClass>(store);
    //std::unique_ptr<IPars> Pars = std::make_unique<FlexParser>(store);

    while (std::getline(file, line)) {
        bool res = Pars->pars(line);
        std::cout << res << "\n";
    }

    return 0;
}