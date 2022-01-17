//
// Created by Carolina P. Nogueira 2016
//

#include <iostream>
#include <string>
#include "Manager.h"

using namespace ClassProject;

int main(int argc, char* argv[])
{
    Manager MyManager;
    MyManager.reset_table();
    BDD_ID a = MyManager.createVar("a");
    BDD_ID b = MyManager.createVar("b");
    BDD_ID c = MyManager.createVar("c");
    BDD_ID d = MyManager.createVar("d");
    BDD_ID f = MyManager.and2(MyManager.and2(c,d),MyManager.or2(a,b));
    MyManager.print_table();
}
