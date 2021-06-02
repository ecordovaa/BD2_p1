#include <iostream>
#include "SeqFile_FL.h"
//#include "ISAM/ISAM.h"
void testseq () 
{
    SeqFile test("test");
    
    // test.midsearch();

    float search = 188;
    sleep(2);
    cout<<"<------Probando-------->"<<endl;
    sleep(1);
    cout<<"search() without eliminates"<<endl<<endl;
    sleep(1);
    cout<<"buscando = "<<search<<endl<<endl;
    getchar();
    pair<bool,Billio> temp = test.search(search);

    if(temp.first)
    {
        temp.second.toString();
    }
    else
    {
        cout<<"No existe la key "<<search<<endl<<endl;
    }


    // 90.6 -> 50.4 -> 188 -> 60.10 ->50
    getchar();
    search = 44.4;
    cout<<"buscando = "<<search<<endl<<endl;
    getchar();
    temp = test.searchmain(search);

    if(temp.first)
    {
        temp.second.toString();
    }
    else
    {
        cout<<"No existe la key "<<search<<endl<<endl;
    }

    getchar();
    search = 63.8;
    cout<<"buscando = "<<search<<endl<<endl;
    getchar();
    temp = test.searchmain(search);

    if(temp.first)
    {
        temp.second.toString();
    }
    else
    {
        cout<<"No existe la key "<<search<<endl<<endl;
    }
    getchar();



    cout<<"<------Fin search without eliminates-------->"<<endl<<endl;

    sleep(2);
    cout<<"<------Probando-------->"<<endl;
    sleep(1);
    cout<<"eliminates()"<<endl<<endl;
    float eliminate = 90.6; 
    getchar();
    cout<<"Eliminando: "<<eliminate<<endl;
    test.eliminate(eliminate);
    getchar();
    eliminate = 50.4;
    cout<<"Eliminando: "<<eliminate<<endl; 
    test.eliminate(eliminate);
    getchar();
    eliminate = 188;
    cout<<"Eliminando: "<<eliminate<<endl; 
    test.eliminate(eliminate);
    getchar();
    eliminate = 170; 
    cout<<"Eliminando: "<<eliminate<<endl;
    test.eliminate(eliminate);
    getchar();
    eliminate = 60.1;  
    cout<<"Eliminando: "<<eliminate<<endl;
    test.eliminate(eliminate);
    getchar();
    eliminate = 44.5; 
    cout<<"Eliminando: "<<eliminate<<endl;
    test.eliminate(eliminate);
    getchar(); 
    eliminate = 170; 
    cout<<"Eliminando: "<<eliminate<<endl;
    test.eliminate(eliminate);
    getchar();
    eliminate = 62.8; 
    cout<<"Eliminando: "<<eliminate<<endl;
    test.eliminate(eliminate);
    getchar();

    cout<<"<------Fin eliminates-------->"<<endl<<endl;



    search = 188;
    sleep(2);
    cout<<"<------Probando-------->"<<endl;
    sleep(1);
    cout<<"search() with eliminates"<<endl<<endl;
    sleep(1);
    cout<<"buscando = "<<search<<endl<<endl;
    getchar();
    temp = test.search(search);

    if(temp.first)
    {
        temp.second.toString();
    }
    else
    {
        cout<<"No existe la key "<<search<<endl<<endl;
    }


    // 90.6 -> 50.4 -> 188 -> 60.10 ->50
    getchar();
    search = 44.5;
    cout<<"buscando = "<<search<<endl<<endl;
    getchar();
    temp = test.searchmain(search);

    if(temp.first)
    {
        temp.second.toString();
    }
    else
    {
        cout<<"No existe la key "<<search<<endl<<endl;
    }

    getchar();
    search = 155;
    cout<<"buscando = "<<search<<endl<<endl;
    getchar();
    temp = test.searchmain(search);

    if(temp.first)
    {
        temp.second.toString();
    }
    else
    {
        cout<<"No existe la key "<<search<<endl<<endl;
    }
    getchar();



    cout<<"<------Fin search with eliminates-------->"<<endl<<endl;

    sleep(2);
    cout<<"<------Probando-------->"<<endl;
    sleep(1);
    cout<<"add() + eliminate() in aux"<<endl<<endl;
    sleep(1);

    Billio a("1","200.22","Peru", "Industria");
    Billio b("2","300.21","Canada", "Industria");
    Billio c("3","21.31","Mexico", "Industria");
    Billio d("4","100.21","Uruguay", "Industria");
    Billio e("5","10.12","Venezuela", "Industria"); 
    Billio f("6","9.42","Bolivia", "Industria");
    Billio g("7","9.48","Peru", "Industria");
    Billio h("8","123.42","Finlandia", "Industria");
    Billio i("9","300.42","China", "Industria");
    Billio j("10","22.42","Paises Bajos", "Industria");
    Billio k("11","98.42","Brasil", "Industria");
    Billio l("12","100.42","Espania", "Industria");
    Billio m("13","109.21","Arequipa","Mina");

    cout<<"añadiendo un registro con key: "<<a.getBillions()<<endl;  
    test.adding(a);
    getchar();
    cout<<"añadiendo un registro con key: "<<b.getBillions()<<endl;
    test.adding(b);
    getchar();
    cout<<"añadiendo un registro con key: "<<c.getBillions()<<endl;
    test.adding(c);
    getchar();
    cout<<"añadiendo un registro con key: "<<d.getBillions()<<endl;
    test.adding(d);
    getchar();
    cout<<"añadiendo un registro con key: "<<e.getBillions()<<endl;
    test.adding(e);
    getchar();
    cout<<"añadiendo un registro con key: "<<f.getBillions()<<endl;
    test.adding(f);
    getchar();
    cout<<"añadiendo un registro con key: "<<g.getBillions()<<endl;
    test.adding(g);
    getchar();
    cout<<"añadiendo un registro con key: "<<h.getBillions()<<endl;
    test.adding(h);
    getchar();
    cout<<"añadiendo un registro con key: "<<i.getBillions()<<endl;
    test.adding(i);
    getchar();
    cout<<"añadiendo un registro con key: "<<j.getBillions()<<endl;
    test.adding(j);
    getchar();

    eliminate = 300.21;
    cout<<"Eliminando: "<<eliminate<<endl;
    test.eliminate(eliminate);
    getchar();
        
    eliminate = 10.12;
    cout<<"Eliminando: "<<eliminate<<endl;
    test.eliminate(eliminate);
    getchar();

    cout<<"<------Fin add plus eliminates in aux-------->"<<endl<<endl;

    sleep(2);
    cout<<"<------Probando-------->"<<endl;
    sleep(1);
    cout<<"sortd()"<<endl<<endl;

    getchar();

    cout<<"añadiendo un registro con key: "<<k.getBillions()<<endl;  
    test.adding(k);
    getchar();

    cout<<"añadiendo un registro con key: "<<l.getBillions()<<endl;  
    test.adding(l);
    getchar();

    cout<<"añadiendo un registro con key: "<<m.getBillions()<<endl;  
    test.adding(m);
    getchar();

    cout<<"<------Fin desbordamiento-------->"<<endl<<endl;

    sleep(2);
    cout<<"<------Probando-------->"<<endl;
    sleep(1);
    cout<<"search_between()"<<endl<<endl;
    sleep(1);
    float from,to;
    from = 200;
    to = 41;
    cout<<"searching from "<<from<<" to "<<to<<endl;
    getchar();
    auto myv = test.searchBetween(from,to);

    for(auto i :myv) { i.toString(); getchar();}

    cout<<"<------Fin de search_between-------->"<<endl<<endl;
}

