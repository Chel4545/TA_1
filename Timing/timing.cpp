#include <iostream>
#include <chrono>
#include <fstream>
#include <string>
#include <memory>


#include "../IPars.h"
#include "../RegEx/RegEx.h"
#include "../Smc/SmcParser.h"
#include "../Flex/FlexParser.h"
#include "RelationStore.h"

static int SRED = 1000;


int main() {
    std::vector<int> x = {1000, 5000, 10000, 20000, 30000, 40000, 50000,
                          60000, 70000, 80000, 90000, 100000};
    std::ifstream fileInput;

    std::string line;

    for (int size : x) {
        std::string path = std::string(TIMING_CASES_DIR) + "/cases_" + std::to_string(size) + ".txt";

        // regex
        {

            RelationStore store;
            std::unique_ptr<IPars> ParsRegex = std::make_unique<RegExClass>(store);

            auto startRegex = std::chrono::steady_clock::now();

            for (int i = 0; i < SRED; ++i) {
                std::ifstream fileInput(path);
                if (!fileInput.is_open()) {
                    std::cout << "Cannot open fileInput\n";
                    return 1;
                }
                while (std::getline(fileInput, line)) {
                    //ParsRegex->pars(line);
                }
            }

            auto finishRegex = std::chrono::steady_clock::now();

            auto durationRegex = std::chrono::duration_cast<std::chrono::microseconds>((finishRegex - startRegex) / SRED);
            std::cout << "Regex y: " << durationRegex.count() << " x: " << size << std::endl;
        }

        // smc
        {

            RelationStore store;
            std::unique_ptr<IPars> ParsSmc = std::make_unique<SmcParser>(store);

            auto startSmc = std::chrono::steady_clock::now();

            for (int i = 0; i < SRED; ++i) {
                std::ifstream fileInput(path);
                if (!fileInput.is_open()) {
                    std::cout << "Cannot open fileInput\n";
                    return 1;
                }
                while (std::getline(fileInput, line)) {
                    ParsSmc->pars(line);
                }
            }
            auto finishSmc = std::chrono::steady_clock::now();

            auto durationSmc = std::chrono::duration_cast<std::chrono::microseconds>((finishSmc - startSmc) / SRED);
            std::cout << "Smc y: " << durationSmc.count() << " x: " << size << std::endl;
        }

        // flex
        {
            RelationStore store;
            std::unique_ptr<IPars> ParsFlex = std::make_unique<FlexParser>(store);

            auto startFlex = std::chrono::steady_clock::now();

            for (int i = 0; i < SRED; ++i) {
                std::ifstream fileInput(path);
                if (!fileInput.is_open()) {
                    std::cout << "Cannot open fileInput\n";
                    return 1;
                }
                while (std::getline(fileInput, line)) {
                    ParsFlex->pars(line);
                }
            }
            auto finishFlex = std::chrono::steady_clock::now();

            auto durationFlex = std::chrono::duration_cast<std::chrono::microseconds>((finishFlex - startFlex) / SRED);
            std::cout << "Flex y: " << durationFlex.count() << " x: " << size << std::endl;
        }

    }
    return 0;
}