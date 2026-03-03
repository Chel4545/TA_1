#include <algorithm>
#include <stdexcept>
#include <iostream>
#include "RelationStore.h"

    std::vector<std::string>& RelationStore::getAttrs(const std::string& name) {
        auto res = rels.find(name);
        if (res == rels.end()) {
            throw std::runtime_error("Relation not found");
        }
        return res->second;
    }

    bool RelationStore::isConsist(const std::string& name) {
        return (rels.find(name) != rels.end());
    }

    bool RelationStore::addRel(const std::string& name, const std::vector<std::string>& attr) {
        if (isConsist(name)) {
            return false;
        }
        rels.emplace(name, attr);
        return true;
    }

    bool RelationStore::delRel(const std::string& name) {
        if (!isConsist(name)) {
            return false;
        }
        rels.erase(name);
        return true;
    }

    void RelationStore::printAllRels() {
        auto itMap = rels.begin();
        while (itMap != rels.end()) {
            std::cout << itMap->first.c_str() << ":" << std::endl;
            auto itVector = itMap->second.begin();
            while (itVector != itMap->second.end()) {
                std::cout << itVector->c_str() << std::endl;
                itVector++;
            }
            itMap++;
        }
    }

    bool RelationStore::makeJoin(
            const std::string& name0,
            const std::string& name1,
            const std::string& name2) {

        if ( isConsist(name0) ||
            !isConsist(name1) ||
            !isConsist(name2)) {
            return false;
        }

        std::vector<std::string> allAttr, addAttr;
        allAttr = this->getAttrs(name1);
        addAttr = this->getAttrs(name2);


        for (auto it1 : addAttr) {
            auto it2 = std::find(allAttr.begin(), allAttr.end(), it1);
            if (it2 != allAttr.end()) {
                *it2 = name1 + "." + *it2;
                allAttr.emplace_back(name2 + "." + it1);
            } else {
                allAttr.emplace_back(it1);
            }
        }

        this->addRel(name0, allAttr);
        return true;

    }