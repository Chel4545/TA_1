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

void SmcClass::executeCommand() {

    if (currentCommand == Command::CREATE_LIST) {
        if (!store.addRel(name0, attributes)) {
            lineOkCreate = false;
        }
    }
    else if (currentCommand == Command::CREATE_JOIN) {
        if(!store.makeJoin(name0, name1, name2)) {
            lineOkJoin = false;
        }
    }
}

void SmcClass::resetLine() {
    attributes.clear();
    currentCommand = Command::NONE;
    lineOkCreate = true;
    lineOkJoin   = true;
}

bool SmcClass::isLineOkCreate() const {
    return lineOkCreate;
}

bool SmcClass::isLineOkJoin() const {
    return lineOkJoin;
}

void SmcClass::syntaxError() {
    lineOkCreate = false;
    lineOkJoin   = false;
    currentCommand = Command::NONE;
}

Command SmcClass::getCommand() const {
    return currentCommand;
}
