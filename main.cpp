#include <iostream>
#include <fstream>
#include <string>


#include "RelationStore.h"
#include "RegEx.h"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << "No input file\n";
        return 1;
    }

    std::ifstream file(argv[1]);

    if (!file.is_open()) {
        std::cout << "Cannot open file\n";
        return 1;
    }

    std::string line;

    while (std::getline(file, line)) {
        bool res = pars(line);
        std::cout << res << "\n";
    }

    return 0;
}