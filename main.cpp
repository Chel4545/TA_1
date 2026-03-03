#include <iostream>
#include "RelationStore.h"
#include "RegEx.h"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << "No input file\n";
        return 1;
    }

    RelationStore store;

    checkComandRegex(std::string(argv[1]), store);
    store.printAllRels();

    return 0;
}