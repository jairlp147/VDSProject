#include "Manager.h"


struct table{
    std::string node;
    BDD_ID iID, iHigh, iLow, iTopVar;
}BDD_table[100];

BDD_ID GL_Top;
bool flag = 0;





void ClassProject::Manager::reset_table() {
    for (int i=0;i<uniqueTableSize();i++){
        BDD_table[i].iID=0;
        BDD_table[i].iHigh=0;
        BDD_table[i].iLow=0;
        BDD_table[i].iTopVar=0;
        BDD_table[GL_Top].node="";
    }

    BDD_table[0].node = "False";
    BDD_table[0].iID = 0;
    BDD_table[0].iHigh = 0;
    BDD_table[0].iLow = 0;
    BDD_table[0].iTopVar = 0;

    BDD_table[1].node = "True";
    BDD_table[1].iID = 1;
    BDD_table[1].iHigh = 1;
    BDD_table[1].iLow = 1;
    BDD_table[1].iTopVar = 1;

    GL_Top=1;
}

void::ClassProject::Manager::print_table(){
    cout<<"Node"<<"     "<<"ID"<<"     "<<"High"<<"     "<<"Low"<<"     "<<"TopVar"<<endl;
    for(int i=0;i<uniqueTableSize();i++){
        cout<<BDD_table[i].node<<"     "<<BDD_table[i].iID<<"     "<<BDD_table[i].iHigh<<"     "<<BDD_table[i].iLow<<"     "<<BDD_table[i].iTopVar<<endl;
    }
}

BDD_ID ClassProject::Manager::TopVariable_3(const BDD_ID a, const BDD_ID b, const BDD_ID c) {
    BDD_ID Mytop=50000;
    if (!isConstant(a)){
        Mytop=BDD_table[a].iTopVar;
    }
    if (!isConstant(b)){
        Mytop=std::min({Mytop, BDD_table[b].iTopVar});
    }
    if (!isConstant(c)){
        Mytop=std::min({Mytop, BDD_table[c].iTopVar});
    }
    return Mytop;
}

BDD_ID ClassProject::Manager::find_or_add_unique_table(const BDD_ID TopVariable, const BDD_ID r_high,
                                                       const BDD_ID r_low) {
    for(int i=0;i<uniqueTableSize();i++){
        if((BDD_table[i].iTopVar==TopVariable)&&(BDD_table[i].iHigh==r_high)&&(BDD_table[i].iLow==r_low)){
            return BDD_table[i].iID;
        }
    }
    GL_Top++;
    BDD_table[GL_Top].node = "Unknown";
    BDD_table[GL_Top].iID = GL_Top;
    BDD_table[GL_Top].iHigh = r_high;
    BDD_table[GL_Top].iLow = r_low;
    BDD_table[GL_Top].iTopVar = TopVariable;
    return BDD_table[GL_Top].iID;
}

BDD_ID ClassProject::Manager::createVar(const std::string &label) {
    GL_Top++;
    BDD_table[GL_Top].node = label;
    BDD_table[GL_Top].iID = GL_Top;
    BDD_table[GL_Top].iHigh = 1;
    BDD_table[GL_Top].iLow = 0;
    BDD_table[GL_Top].iTopVar = BDD_table[GL_Top].iID;

    return BDD_table[GL_Top].iID;
}

const BDD_ID & ClassProject::Manager::True() {
    return BDD_table[1].iID;
}

const BDD_ID & ClassProject::Manager::False() {
    return BDD_table[0].iID;
}

bool ClassProject::Manager::isConstant(const BDD_ID f) {
    if ((BDD_table[f].iID == BDD_table[f].iHigh) && (BDD_table[f].iHigh == BDD_table[f].iLow) ){
        return true;
    }
    else{
        return false;
    }
}

bool ClassProject::Manager::isVariable(const BDD_ID x) {
    if ((BDD_table[x].iID == BDD_table[x].iHigh) && (BDD_table[x].iHigh == BDD_table[x].iLow) ){
        return false;
    }
    else{
        return true;
    }
}

BDD_ID ClassProject::Manager::topVar(const BDD_ID f) {
    return BDD_table[f].iTopVar;
}

size_t ClassProject::Manager::uniqueTableSize() {
    BDD_ID x;
    x = GL_Top + 1;
    return x;
}

BDD_ID ClassProject::Manager::ite(const BDD_ID i, const BDD_ID t, const BDD_ID e) {
    BDD_ID MyTopVariable,r_high,r_low,r;
    if(isConstant(i)){//Terminal case
        if(BDD_table[i].iID==True()){return t;}
        else{return e;}
    }
    else{//apply the ite algorithm
        MyTopVariable=TopVariable_3(i,t,e);//Determinate the top variable
        r_high=ite(coFactorTrue(i,MyTopVariable),coFactorTrue(t,MyTopVariable),coFactorTrue(e,MyTopVariable));
        r_low=ite(coFactorFalse(i,MyTopVariable),coFactorFalse(t,MyTopVariable),coFactorFalse(e,MyTopVariable));
        if(r_high==r_low){ // is reduction possible?
            return r_high;
        }
        r=find_or_add_unique_table(MyTopVariable,r_high,r_low);
        return r;
    }
}

BDD_ID ClassProject::Manager::coFactorTrue(const BDD_ID f, BDD_ID x) {

    BDD_ID T,F;
    if(x==-1){x = BDD_table[f].iTopVar;}

    if (isConstant(f) || isConstant(x) || BDD_table[f].iTopVar > x){
        return f;
    }

    if(BDD_table[f].iTopVar == x){
        return BDD_table[f].iHigh;
    }
    else{
        T = coFactorTrue ( BDD_table[f].iHigh , x ) ;
        F = coFactorTrue ( BDD_table[f].iLow , x ) ;
        return ite(BDD_table[f].iTopVar , T, F);
    }
}

BDD_ID ClassProject::Manager::coFactorFalse(const BDD_ID f, BDD_ID x) {
    BDD_ID T,F;
    if(x==-1){x = BDD_table[f].iTopVar;}

    if (isConstant(f) || isConstant(x) || BDD_table[f].iTopVar > x){
        return f;
    }

    if(BDD_table[f].iTopVar == x){
        return BDD_table[f].iLow;
    }
    else{
        T = coFactorFalse ( BDD_table[f].iHigh , x ) ;
        F = coFactorFalse ( BDD_table[f].iLow , x ) ;
        return ite(BDD_table[f].iTopVar , T, F);
    }
}

BDD_ID ClassProject::Manager::neg(const BDD_ID a) {
    BDD_ID temp = ite(a, 0, 1);
    BDD_table[temp].node = "!" + BDD_table[a].node;
    return temp;
}

BDD_ID ClassProject::Manager::and2(const BDD_ID a, const BDD_ID b) {
    BDD_ID temp = ite(a, b, 0);
    BDD_table[temp].node = BDD_table[a].node + "*" + BDD_table[b].node;
    return temp;
}

BDD_ID ClassProject::Manager::or2(const BDD_ID a, const BDD_ID b) {
    BDD_ID temp = ite(a, 1, b);
    BDD_table[temp].node = BDD_table[a].node + "+" + BDD_table[b].node;
    return temp;
}

BDD_ID ClassProject::Manager::xor2(const BDD_ID a, const BDD_ID b) {
    BDD_ID temp = ite(a, neg(b), b);
    BDD_table[temp].node = BDD_table[a].node + "⊕" + BDD_table[b].node;
    return temp;
}

BDD_ID ClassProject::Manager::nand2(const BDD_ID a, const BDD_ID b) {
    BDD_ID temp = ite(neg(a), 1, neg(b));
    BDD_table[temp].node = BDD_table[a].node + " nand " + BDD_table[b].node;
    return temp;
}

BDD_ID ClassProject::Manager::nor2(const BDD_ID a, const BDD_ID b) {
    BDD_ID temp = ite(neg(a), neg(b), 0);
    BDD_table[temp].node = BDD_table[a].node + " nor " + BDD_table[b].node;
    return temp;
}

BDD_ID ClassProject::Manager::xnor2(const BDD_ID a, const BDD_ID b) {
    BDD_ID temp = ite(a, b, neg(b));
    BDD_table[temp].node = BDD_table[a].node + "⊙" + BDD_table[b].node;
    return temp;
}

std::string ClassProject::Manager::getTopVarName(const BDD_ID &root) {
    BDD_ID temp = BDD_table[root].iTopVar;
    return BDD_table[temp].node;
}

void ClassProject::Manager::findNodes(const BDD_ID &root, std::set<BDD_ID> &nodes_of_root) {
    nodes_of_root.insert(root);
    nodes_of_root.insert(BDD_table[root].iHigh);
    nodes_of_root.insert(BDD_table[root].iLow);
    if(!isConstant(BDD_table[root].iHigh)){
        findNodes(BDD_table[root].iHigh, nodes_of_root);
    }
    if(!isConstant(BDD_table[root].iLow)){
        findNodes(BDD_table[root].iLow, nodes_of_root);
    }
}

void ClassProject::Manager::findVars(const BDD_ID &root, std::set<BDD_ID> &vars_of_root) {
    vars_of_root.insert(BDD_table[root].iTopVar);
    if(!isConstant(BDD_table[root].iHigh)){
        findVars(BDD_table[root].iHigh, vars_of_root);
    }
    if(!isConstant(BDD_table[root].iLow)){
        findVars(BDD_table[root].iLow, vars_of_root);
    }
}


