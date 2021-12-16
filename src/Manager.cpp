#include "Manager.h"

/*
struct table{
    string node;
    int iID, iHigh, iLow, iTopVar;
}obj[5];
*/

ClassProject::BDD_ID ClassProject::Manager::createVar(const std::string &label) {
    return 0;
}

const ClassProject::BDD_ID &ClassProject::Manager::True() {
    /*
    obj[1].node = "True";
    obj[1].iID = 1;
    obj[1].iHigh = 1;
    obj[1].iLow = 1;
    obj[1].iTopVar = 1;

    //GL_Top = obj[1].iID;
    return obj[1].iID;
     */
    return 0;
}

const ClassProject::BDD_ID &ClassProject::Manager::False() {
    /*
    obj[0].node = "False";
    obj[0].iID = 0;
    obj[0].iHigh = 0;
    obj[0].iLow = 0;
    obj[0].iTopVar = 0;

    //GL_Top = obj[0].iID;
    return obj[0].iID;
     */
    return 0;
}

bool ClassProject::Manager::isConstant(ClassProject::BDD_ID f) {
    return false;
}

bool ClassProject::Manager::isVariable(ClassProject::BDD_ID x) {
    return false;
}

ClassProject::BDD_ID ClassProject::Manager::topVar(ClassProject::BDD_ID f) {
    return 0;
}

ClassProject::BDD_ID
ClassProject::Manager::ite(ClassProject::BDD_ID i, ClassProject::BDD_ID t, ClassProject::BDD_ID e) {
    return 0;
}

ClassProject::BDD_ID ClassProject::Manager::coFactorTrue(ClassProject::BDD_ID f, ClassProject::BDD_ID x) {
    return 0;
}

ClassProject::BDD_ID ClassProject::Manager::coFactorFalse(ClassProject::BDD_ID f, ClassProject::BDD_ID x) {
    return 0;
}

ClassProject::BDD_ID ClassProject::Manager::coFactorTrue(ClassProject::BDD_ID f) {
    return 0;
}

ClassProject::BDD_ID ClassProject::Manager::coFactorFalse(ClassProject::BDD_ID f) {
    return 0;
}

ClassProject::BDD_ID ClassProject::Manager::neg(ClassProject::BDD_ID a) {
    return 0;
}

ClassProject::BDD_ID ClassProject::Manager::and2(ClassProject::BDD_ID a, ClassProject::BDD_ID b) {
    return 0;
}

ClassProject::BDD_ID ClassProject::Manager::or2(ClassProject::BDD_ID a, ClassProject::BDD_ID b) {
    return 0;
}

ClassProject::BDD_ID ClassProject::Manager::xor2(ClassProject::BDD_ID a, ClassProject::BDD_ID b) {
    return 0;
}

ClassProject::BDD_ID ClassProject::Manager::nand2(ClassProject::BDD_ID a, ClassProject::BDD_ID b) {
    return 0;
}

ClassProject::BDD_ID ClassProject::Manager::nor2(ClassProject::BDD_ID a, ClassProject::BDD_ID b) {
    return 0;
}

ClassProject::BDD_ID ClassProject::Manager::xnor2(ClassProject::BDD_ID a, ClassProject::BDD_ID b) {
    return 0;
}

std::string ClassProject::Manager::getTopVarName(const ClassProject::BDD_ID &root) {
    return std::__cxx11::string();
}

void ClassProject::Manager::findNodes(const ClassProject::BDD_ID &root, std::set<BDD_ID> &nodes_of_root) {

}

void ClassProject::Manager::findVars(const ClassProject::BDD_ID &root, std::set<BDD_ID> &vars_of_root) {

}

size_t ClassProject::Manager::uniqueTableSize() {
    return 0;
}
