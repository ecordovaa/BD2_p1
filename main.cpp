#include <iostream>
#include "SeqFile_FL/SeqFile_FL.h"
//#include "ISAM/ISAM.h"
int main () {

    SeqFile test("out2");
    // test.midsearch();

    // pair<bool,Billio> billionary = test.search(31.5);
    // if(billionary.first){billionary.second.toString();}
    // else{cout<<"NO HAY";}
    // 90.6 -> 50.4 -> 188 -> 60.10 ->50

    // auto i = test.searchmain(188);

    // cout<<i.first<<endl;
    // i.second.toString();


    // i.second.toString2();
    test.eliminate(90.6);
    test.eliminate(50.4);
    test.eliminate(188);
    test.eliminate(60.1);
    // auto i = test.search(90.6);
    // auto i1 = test.search(50.4);
    // auto i3 = test.search(60.1);
    Billio ee("Efrain C.","70","caca", "peru");
    Billio aa("Paul C.","200","caca", "peru");
    Billio bb("Diego C.","15","caca", "peru");
    test.add(ee);
    test.add(aa);
    test.add(bb);

    // i.second.toString();
    // i1.second.toString();
    // i3.second.toString();


    // auto i = test.search(154);
    // i.second.toString();

    // auto testSearchBetween = test.searchBetween(56.5, 144);
    // for(auto t: testSearchBetween) {
    //     t.toString();
    // }

    // test.midsearch();
    
    return 0;
}

