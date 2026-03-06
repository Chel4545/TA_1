#include "SmcClass.h"

SmcClass::SmcClass(RelationStore& relStore)
        : store(relStore)
{}

void SmcClass::setName0(const std::string& name) {
    name0 = name;
}

void SmcClass::setName1(const std::string& name) {
    name1 = name;
}

void SmcClass::setName2(const std::string& name) {
    name2 = name;
}

void SmcClass::setAttribute(const std::string &attr) {
    attributes.push_back(attr);
}

void SmcClass::setCreateList() {
    currentCommand = Command::CREATE_LIST;
}

void SmcClass::setCreateJoin() {
    currentCommand = Command::CREATE_JOIN;
}

void SmcClass::executeCommand() const{
    if (!lineOk) return;

    if (currentCommand == Command::CREATE_LIST) {
        store.addRel(name0, attributes);
    }
    else if (currentCommand == Command::CREATE_JOIN) {
        store.makeJoin(name0, name1, name2);
    }
}

void SmcClass::resetLine() {
    attributes.clear();
    currentCommand = Command::NONE;
    lineOk = true;
}

bool SmcClass::isLineOk() const {
    return lineOk;
}

void SmcClass::syntaxError() {
    lineOk = false;
    currentCommand = Command::NONE;
}
