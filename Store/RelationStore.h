#ifndef RELATIONSTORE_H
#define RELATIONSTORE_H

#include <map>
#include <vector>
#include <string>

class RelationStore {
private:
    std::map<std::string, std::vector<std::string>> rels;

public:
    std::vector<std::string>& getAttrs(const std::string& name);

    bool isConsist(const std::string& name);

    bool addRel(const std::string& name, const std::vector<std::string>& attr);

    bool delRel(const std::string& name);

    void printAllRels();

    bool makeJoin(
            const std::string& name0,
            const std::string& name1,
            const std::string& name2);
};

#endif
