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
    // test.eliminate(170);
    // test.eliminate(60.1);
    // test.eliminate(44.5);
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

    Billio a("1","200.22","caca", "peru");

    Billio b("2","300.21","caca", "peru");
    Billio c("3","21.31","caca", "peru");
    Billio d("4","100.21","caca", "peru");
    Billio e("5","10.12","caca", "peru"); 
    Billio f("6","9.42","caca", "peru");
    Billio g("7","9.48","caca", "peru");
    Billio h("8","123.42","caca", "peru");
    Billio i("9","300.42","caca", "peru");
    Billio j("10","22.42","caca", "peru");
    Billio k("11","98.42","caca", "peru");
    Billio l("12","100.42","caca", "peru");

    
    // b.toString2();
    // c.toString2();
    // d.toString2();
    // e.toString2();
    // f.toString2();
    // cout<<test.sizeaux<<endl;
    test.adding(a);
    test.adding(b);
    test.adding(c);
    cout<<test.sizeaux<<endl;
    test.adding(d);
    cout<<test.sizeaux<<endl;
    test.adding(e);
    cout<<test.sizeaux<<endl;
    test.adding(f);
    cout<<test.sizeaux<<endl;
    test.adding(g);
    cout<<test.sizeaux<<endl;
    test.adding(h);
    cout<<test.sizeaux<<endl;
    test.adding(i);
    cout<<test.sizeaux<<endl;
    test.adding(j);
    cout<<test.sizeaux<<endl;
    // test.adding(k);
    test.eliminate(300.21);
    test.eliminate(10.12);
    sleep(10);
    test.adding(l);
    // cout<<test.sizeaux<<endl;
    // test.adding(l);
    // cout<<test.sizeaux<<endl;
    // test.adding(a);
    // cout<<test.sizeaux<<endl;
    // test.adding(b);
    // cout<<test.sizeaux<<endl;
    // test.adding(b);
    // test.adding(b);
    // test.adding(b);
    // test.adding(c);
    // test.adding(d);
    // test.adding(e);
    // test.adding(f);
    // test.adding(g);
    // test.adding(h);
    // test.adding(i);
    // test.adding(j);
    // test.adding(k);
    // test.adding(l);
    

    // test.eliminate(9);
    // test.eliminate(300);
    // test.eliminate(188);
    // test.eliminate(10);
    // test.eliminate(89.1);
    // test.eliminate(57);
    // test.eliminate(50.4);
    // test.adding(b);

    // test.sortd();
    
    
    


    // auto i = test.search(200);
    // i.second.toString();

    // auto testSearchBetween = test.searchBetween(250 , 170);
    // for(auto t: testSearchBetween) {
    //     t.toString();
    // }

    // test.midsearch();
    
    return 0;
}

