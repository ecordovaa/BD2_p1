#include <iostream>
#include "SeqFile_FL/SeqFile_FL.h"
//#include "ISAM/ISAM.h"
int main () 
{

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
    
    // test.eliminate(90.6);
    // test.eliminate(50.4);
    // test.eliminate(188);
    // test.eliminate(60.1);
    // test.eliminate(170);
    // test.eliminate(62.8);
    // test.eliminate(155);
    // test.eliminate(144);
    // test.eliminate(44.5);

    // auto i = test.search(90.6);
    // auto i1 = test.search(50.4);
    // auto i3 = test.search(60.1);

    // if(i.first)
    //     i.second.toString();
    // if(i1.first)
    //     i1.second.toString();
    // if(i3.first)
    //     i3.second.toString();

    Billio a("1","200","caca", "peru");
    Billio b("2","300","caca", "peru");
    Billio c("3","21","caca", "peru");
    Billio d("4","100","caca", "peru"); //.
    Billio e("5","10","caca", "peru"); //.
    Billio f("6","9","caca", "peru");

    test.adding(a);
    test.adding(b);
    // test.adding(e);
    // test.adding(d);
    //
    // test.adding(f);
    

    
    
    
    


    // auto i = test.search(154);
    // i.second.toString();

    auto testSearchBetween = test.searchBetween(250 , 170);
    for(auto t: testSearchBetween) {
        t.toString();
    }

    // test.midsearch();
    
    return 0;
}

