// A minimalistic BDD library, following Wolfgang Kunz lecture slides
//
// Created by Markus Wedler 2014

#ifndef VDSPROJECT_MANAGER_H
#define VDSPROJECT_MANAGER_H

#include "ManagerInterface.h"
#include <string>
#include <iostream>
#include <iomanip>
#include <vector>
using namespace std;  //for string nodename?
typedef int BDD_ID;

//-------------VECTORS
struct unique_table{
    BDD_ID bdd_id,high,low,topVar;
    string nodeName;
};
vector<unique_table> utable_vec;  //create vector of dataype structure
vector<unique_table> popVector(vector<unique_table> utable_vec, BDD_ID bdd_id, BDD_ID high, BDD_ID low, BDD_ID topVar, string nodeName);  //declare function
bool checkTable(vector<unique_table> utable_vec, BDD_ID high, BDD_ID low, BDD_ID topVar);
size_t  uniqueTableSize(); //return number of nodes in the unqiue table of Manager class
void printuniquetable();
void createtable();

//---------------------definition of Vector Talbe functions


void createtable(){
    unique_table vectable;
    vectable.bdd_id = 0;
    vectable.nodeName = "False";
    vectable.topVar = 0;
    vectable.high = 0;
    vectable.low = 0;
    utable_vec.push_back(vectable);

    vectable.bdd_id = 1;
    vectable.nodeName = "True";
    vectable.topVar = 1;
    vectable.high = 1;
    vectable.low = 1;
    utable_vec.push_back(vectable);
}

vector<unique_table> popVector(vector<unique_table> utable_vec, BDD_ID bdd_id, BDD_ID high, BDD_ID low, BDD_ID topVar, string nodeName){
    //create structure, fill in info passed as argument and pop new vector into existing vectors.
    unique_table vectable;
    vectable.bdd_id = bdd_id;   //bdd_id of new node being added = vector.size -1;
    vectable.nodeName = nodeName;
    vectable.topVar = topVar;
    vectable.high = high;
    vectable.low = low;
    utable_vec.push_back(vectable);
    return utable_vec;
}

bool checkTable(vector<unique_table> utable_vec, BDD_ID high, BDD_ID low, BDD_ID topVar){  //return true if node exists in table
    int size = uniqueTableSize();
    for (int i=0; i<size; i++){
        if (utable_vec[i].topVar==topVar){
            if (utable_vec[i].high==high){
                if(utable_vec[i].low==low){
                    return true;  //
                    break;
                }
            }
        }
    }
}


size_t uniqueTableSize(){
    return utable_vec.size();
}

void printuniquetable(){
    int size = uniqueTableSize();
    cout << endl << left << setw(15) << "Node"<< left << setw(10) << "BDD_ID" << left << setw(10) << "High" << left << setw(10) <<"Low"<< left << setw(10) <<"TopVar";
    for (int i=0; i<size; i++){
        cout << endl << left << setw(15) << utable_vec[i].nodeName << left << setw(10) << utable_vec[i].bdd_id << left << setw(10) << utable_vec[i].high << left << setw(10) << utable_vec[i].low << left << setw(10) << utable_vec[i].topVar;
    }
}






namespace ClassProject {

}

#endif
