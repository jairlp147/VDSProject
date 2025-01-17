#include "Manager.h"

ClassProject::Manager::Manager() {  //contructor
    reset_table();
}

void ClassProject::Manager::reset_table() {

    unique_table.clear(); //remove all elements from vector (storage not released)

    table vectable;
    vectable.node = "False";
    vectable.iID = 0;
    vectable.iHigh = 0;
    vectable.iLow = 0;
    vectable.iTopVar = 0;
    unique_table.push_back(vectable);

    vectable.node = "True";
    vectable.iID = 1;
    vectable.iHigh = 1;
    vectable.iLow = 1;
    vectable.iTopVar = 1;
    unique_table.push_back(vectable);
}

vector<table> &ClassProject::Manager::popVector(vector<table> &unique_table, BDD_ID bdd_id, BDD_ID high, BDD_ID low,
                                               BDD_ID topVar, string nodeName) {
    //create structure, fill in info passed as argument and pop (add) new vector into existing vectors.
    //table vectable;
    //vectable.iID = bdd_id;   //bdd_id of new node being added = vector.size -1;
    //vectable.node = nodeName;
    //vectable.iTopVar = topVar;
    //vectable.iHigh = high;
    //vectable.iLow = low;
    //unique_table.push_back(vectable);
    unique_table.push_back({nodeName,bdd_id,high,low,topVar});
    return unique_table;
}

void::ClassProject::Manager::print_table(){

    cout << endl << left << setw(15) << "Node"<< left << setw(10) << "BDD_ID" << left << setw(10) << "High" << left << setw(10) <<"Low"<< left << setw(10) <<"TopVar";
    for (size_t i=0; i<uniqueTableSize(); i++){
        cout << endl << left << setw(15) << unique_table[i].node << left << setw(10) << unique_table[i].iID << left << setw(10) << unique_table[i].iHigh << left << setw(10) << unique_table[i].iLow << left << setw(10) << unique_table[i].iTopVar;
    }
}

BDD_ID ClassProject::Manager::table_element(BDD_ID ID,string attribute){
    if (attribute=="iID"){return unique_table[ID].iID;}
    else if (attribute=="iTopVar") {return unique_table[ID].iTopVar;}
    else if (attribute=="iHigh") {return unique_table[ID].iHigh;}
    else if (attribute=="iLow") {return unique_table[ID].iLow;}
    else {return 0;}
}

BDD_ID ClassProject::Manager::TopVariable_3(const BDD_ID a, const BDD_ID b, const BDD_ID c) {
    BDD_ID Mytop;
    Mytop=unique_table[a].iTopVar; // a is never a constant
    if (!isConstant(b)){
        Mytop=std::min({Mytop, unique_table[b].iTopVar});
    }
    if (!isConstant(c)){
        Mytop=std::min({Mytop, unique_table[c].iTopVar});
    }
    return Mytop;
}

BDD_ID ClassProject::Manager::find_or_add_unique_table(const BDD_ID TopVariable, const BDD_ID r_high,
                                                       const BDD_ID r_low) {
    //auto found = inverse_table.find({r_high,r_low,TopVariable});
    std::unordered_map<Key, BDD_ID , KeyHash, KeyEqual>::const_iterator found = inverse_table.find({r_high,r_low,TopVariable});
    if ( found == inverse_table.end()){
        //for(size_t i=0;i<uniqueTableSize();i++){
        //    if((unique_table[i].iTopVar==TopVariable)&&(unique_table[i].iHigh==r_high)&&(unique_table[i].iLow==r_low)){
        //        inverse_table.insert({{r_high,r_low,TopVariable},unique_table[i].iID});
        //        return unique_table[i].iID;
        //    }
        //}
        //highest CURRENT ID is = size-1, therefore new node will have id = size
        unique_table= popVector(unique_table, uniqueTableSize(), r_high, r_low, TopVariable, "");
        inverse_table.insert({{r_high,r_low,TopVariable},unique_table[uniqueTableSize()-1].iID});
        return unique_table[uniqueTableSize()-1].iID; //return ID new node created. ID last node is size -1
    }
    else{
        return found->second;
    }
    // HASH Table: -> VarTop,High,LOW-> ID //reverse unique table
}

BDD_ID ClassProject::Manager::createVar(const std::string &label) {

    unique_table = popVector(unique_table, uniqueTableSize(), 1, 0, uniqueTableSize(), label); //ID new node is current size (as ID last node in table is size-1 )
    inverse_table.insert({{1,0,unique_table[uniqueTableSize()-1].iID},unique_table[uniqueTableSize()-1].iID});
    return unique_table[uniqueTableSize()-1].iID; //return ID new node created. ID last node is size -1
}

const BDD_ID & ClassProject::Manager::True() {
    return unique_table[1].iID;
}

const BDD_ID & ClassProject::Manager::False() {
    return unique_table[0].iID;
}

bool ClassProject::Manager::isConstant(const BDD_ID f) {
    if ((unique_table[f].iID == unique_table[f].iHigh) && (unique_table[f].iHigh == unique_table[f].iLow) ){
        return true;
    }
    else{
        return false;
    }
}

bool ClassProject::Manager::isVariable(const BDD_ID x) {
    if (unique_table[x].iHigh==1 && unique_table[x].iLow==0){ //Variable: High=1 & Low =0
        return true;
    }
    else{
        return false;
    }
}

BDD_ID ClassProject::Manager::topVar(const BDD_ID f) {
    return unique_table[f].iTopVar;
}

size_t ClassProject::Manager::uniqueTableSize() {
    return unique_table.size();
}

BDD_ID ClassProject::Manager::ite(const BDD_ID i, const BDD_ID t, const BDD_ID e) {
    BDD_ID MyTopVariable,r_high,r_low,r;
    std::unordered_map<Key, BDD_ID , KeyHash, KeyEqual>::const_iterator found;
    if(isConstant(i)){//Terminal case (i==1, i==0)
        if(unique_table[i].iID==True()){return t;}
        else{return e;}
    }
    else if (t == e){//Terminal case
        return t;
    }
    else if (t == 1 && e == 0){//Terminal case
        return i;
    }
    else if ((found=computed_table.find({i,t,e})) != computed_table.end()){
        return found->second;
    }
    else{//apply the ite algorithm
        MyTopVariable=TopVariable_3(i,t,e);//Determinate the top variable
        r_high=ite(coFactorTrue(i,MyTopVariable),coFactorTrue(t,MyTopVariable),coFactorTrue(e,MyTopVariable));
        r_low=ite(coFactorFalse(i,MyTopVariable),coFactorFalse(t,MyTopVariable),coFactorFalse(e,MyTopVariable));
        if(r_high==r_low){ // is reduction possible?
            return r_high;
        }
        r=find_or_add_unique_table(MyTopVariable,r_high,r_low);
        computed_table.insert({{i,t,e},r});
        return r;
    }
}

BDD_ID ClassProject::Manager::coFactorTrue(const BDD_ID f, BDD_ID x) {

    BDD_ID T,F;

    if (isConstant(f) || isConstant(x) || unique_table[f].iTopVar > x){
        return f;
    }

    if(unique_table[f].iTopVar == x){
        return unique_table[f].iHigh;
    }
    else{
        T = coFactorTrue ( unique_table[f].iHigh , x ) ;
        F = coFactorTrue ( unique_table[f].iLow , x ) ;
        return ite(unique_table[f].iTopVar , T, F);
    }
}

BDD_ID ClassProject::Manager::coFactorTrue(const BDD_ID f) {
    return unique_table[f].iHigh;
}

BDD_ID ClassProject::Manager::coFactorFalse(const BDD_ID f, BDD_ID x) {
    BDD_ID T,F;

    if (isConstant(f) || isConstant(x) || unique_table[f].iTopVar > x){
        return f;
    }

    if(unique_table[f].iTopVar == x){
        return unique_table[f].iLow;
    }
    else{
        T = coFactorFalse ( unique_table[f].iHigh , x ) ;
        F = coFactorFalse ( unique_table[f].iLow , x ) ;
        return ite(unique_table[f].iTopVar , T, F);
    }
}

BDD_ID ClassProject::Manager::coFactorFalse(const BDD_ID f) {
    return unique_table[f].iLow;
}

BDD_ID ClassProject::Manager::neg(const BDD_ID a) {
    return ite(a, 0, 1);
}

BDD_ID ClassProject::Manager::and2(const BDD_ID a, const BDD_ID b) {
   return ite(a, b, 0); //removed label propagation
}

BDD_ID ClassProject::Manager::or2(const BDD_ID a, const BDD_ID b) {
    return ite(a, 1, b);
}

BDD_ID ClassProject::Manager::xor2(const BDD_ID a, const BDD_ID b) {
     return ite(a, neg(b), b);
}

BDD_ID ClassProject::Manager::nand2(const BDD_ID a, const BDD_ID b) {
    return ite(neg(a), 1, neg(b));
}

BDD_ID ClassProject::Manager::nor2(const BDD_ID a, const BDD_ID b) {
      return ite(neg(a), neg(b), 0);
}

BDD_ID ClassProject::Manager::xnor2(const BDD_ID a, const BDD_ID b) {
       return ite(a, b, neg(b));
}

std::string ClassProject::Manager::getTopVarName(const BDD_ID &root) {
    BDD_ID temp = unique_table[root].iTopVar;
    return unique_table[temp].node;
}

void ClassProject::Manager::findNodes(const BDD_ID &root, std::set<BDD_ID> &nodes_of_root) {
    nodes_of_root.insert(root);
    nodes_of_root.insert(unique_table[root].iHigh);
    nodes_of_root.insert(unique_table[root].iLow);
    if(!isConstant(unique_table[root].iHigh)){
        findNodes(unique_table[root].iHigh, nodes_of_root);
    }
    if(!isConstant(unique_table[root].iLow)){
        findNodes(unique_table[root].iLow, nodes_of_root);
    }
}

void ClassProject::Manager::findVars(const BDD_ID &root, std::set<BDD_ID> &vars_of_root) {
    if (isConstant(unique_table[root].iID)){
        return;
    }
    vars_of_root.insert(unique_table[root].iTopVar);
    if(!isConstant(unique_table[root].iHigh)){
        findVars(unique_table[root].iHigh, vars_of_root);
    }
    if(!isConstant(unique_table[root].iLow)){
        findVars(unique_table[root].iLow, vars_of_root);
    }

}


