#include <iostream>
#include "SeqFile_FL/SeqFile_FL.h"
//#include "ISAM/ISAM.h"
int main () {

    SeqFile test("out2");
    // test.midsearch();
    Billio b1("Efrain C.","90.6","Peru","Utec");

    // pair<bool,Billio> billionary = test.search(31.5);
    // if(billionary.first){billionary.second.toString();}
    // else{cout<<"NO HAY";}

    test.eliminate(44.5);
    // auto i = test.search(154);
    // i.second.toString();

    // auto testSearchBetween = test.searchBetween(56.5, 144);
    // for(auto t: testSearchBetween) {
    //     t.toString();
    // }

    // test.midsearch();
    
    return 0;
}

