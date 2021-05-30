#include <iostream>
#include "SeqFile_FL/SeqFile_FL.h"
//#include "ISAM/ISAM.h"
int main () {

    SeqFile test("uwu");
    //test.test();
    Billio b1("Efrain C.","20","SI","ola","1","1");

    // pair<bool,Billio> billionary = test.search(101);
    // if(billionary.first){billionary.second.toString();}
    // else{cout<<"NO HAY";}

    test.add(b1);

    // test.midsearch();
    
    return 0;
}

