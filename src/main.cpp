//
// Created by Carolina P. Nogueira 2016
//

#include <iostream>
#include <string>
#include "Manager.h"

using namespace ClassProject;

int main(int argc, char* argv[])
{

    BDD_ID x,y,z,b,p,q,r,s;
    MyManager MyManager;

    x = MyManager.False1();
    y = MyManager.True1();
    z = MyManager.createVar("a");
    b = MyManager.createVar("b");
    x = MyManager.createVar("c");
    x = MyManager.createVar("d");

    p = MyManager.or2(2,3);
    q = MyManager.and2(4,5);
    r = MyManager.and2(6,7);

    for(int i=0;i<MyManager.uniqueTableSize();i++){
        cout<<BDD_table[i].node<<"     "<<BDD_table[i].iID<<"     "<<BDD_table[i].iHigh<<"     "<<BDD_table[i].iLow<<"     "<<BDD_table[i].iTopVar<<endl;
    }

    return 0;
}
