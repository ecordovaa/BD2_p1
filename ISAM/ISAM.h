#ifndef BD2_P1_ISAM_H
#define BD2_P1_ISAM_H
#include "index.h"

int regSize = sizeof(Billio) - 6;
int indexSize = sizeof(BillioIndex) - 2;

class ISAM {
private:
    int fileSize = 30;
    string filename {};
    string index {};
    bool binarySearch(float key, ifstream &stream, BillioIndex& billionary);

public:
    explicit ISAM(const string& file): filename("data/"+ file + ".txt"), index("data/index_"+ file + ".txt") {};
    pair<bool,Billio> search(float key);
    vector<Billio> searchBetween (int left, int right);
    void add(Billio billionary);
    void eliminate(float key);
    void test();
};

pair<bool,Billio> ISAM::search(float key) 
{
    ifstream mainStream(filename);
    ifstream indexStream(index);

    Billio billionary;
    BillioIndex billioIndex;

    bool found = binarySearch(key, indexStream, billioIndex); 

    mainStream.seekg(5 + billioIndex.getPos()*(regSize+1), ios::beg);
    billionary.readBillio(mainStream);

    bool isNotDeleted = billionary.getState() == 0;

    //Asegurar no trabajar sobre un registro eliminado.
    while(!isNotDeleted)
    {
        //false 115 -> eliminado
        int regpos = billioIndex.getPos();
        if(regpos == 0)
        {
            //No podemos buscar por arriba, ya que es el primer elemento.
            //Buscar, entonces, por abajo.
            while(billionary.getState() != 0)
            {
                indexStream.seekg((regpos++)*(indexSize+1), ios::beg);
                billioIndex.readBillioIndex(indexStream);
                mainStream.seekg(billioIndex.getPos()*(regSize+1), ios::beg);
                billionary.readBillio(mainStream);
            }
        }
        else
        {
            //Buscar por arriba el menor elemento mayor al que se pidio
            while(billionary.getState() != 0)
            {
                indexStream.seekg((regpos--)*(regSize+1), ios::beg);
                billioIndex.readBillioIndex(indexStream);
                mainStream.seekg(billioIndex.getPos()*(regSize+1), ios::beg);
                billionary.readBillio(mainStream);
            }
        }
    }
    mainStream.close();
    indexStream.close();
    return make_pair(found && isNotDeleted, billionary);
}

vector<Billio> ISAM::searchBetween(int left, int right) 
{
    vector<Billio> out {};
    float start = max(left, right);
    float end = min(left,right);
    Billio startIndex = search(start).second;

    ifstream mainStream(filename);
    ifstream indexStream(index);
    BillioIndex rangeDelim;
    binarySearch(startIndex.getBillions(),indexStream,rangeDelim); //Encontrar el menor y avanzar hasta el mayor

    //Mientras se mantenga en el rango
    while(rangeDelim.getBillions() >= end)
    {
        mainStream.seekg(9 + (rangeDelim.getPos())*(regSize+1), ios::beg);
        startIndex.readBillio(mainStream);
        if(startIndex.getState() == 0) out.push_back(startIndex);
        int regpos = 5 - (indexStream.tellg() / (regSize - 1));
        indexStream.seekg((regpos + 1)*(regSize + 1), ios::beg);
        rangeDelim.readBillioIndex(indexStream);
    }

    mainStream.close();
    indexStream.close();
    return out;
 }

void ISAM::add(Billio newBillionary)
{
    pair<bool,Billio> found = search(newBillionary.getBillions());
    if(found.first) return; //No hacer nada si ya se encuentra en el archivo

    char temp[5];
    int header {};

    //Obtener header
    ifstream mainStream(filename);
    ifstream indexStream(index);
    BillioIndex newIndex;
    mainStream.seekg(0, ios::beg); 
    mainStream.read(temp,4);
    sscanf(temp, "%d", &header);

    //2 - 6 - 8 - 9 - 12 eliminado:6 anadimos: 5 | 2-6(X)-8 write-> 2-5-8

    //Escribir en heap (main). Adicionalmente, intentará buscar un registro eliminado apropiado para insertar
    if(header == -1) mainStream.seekg(0, ios::beg);
    else {
        mainStream.seekg(5 + (header - 1)*(regSize - 1));
        Billio aux;
        BillioIndex billioIndex;
        aux.readBillio(mainStream);

        //Buscar un registro eliminado tal que su mayor y menor consecutivos sean tambien los del nuevo registro. (Podria no encontrarse)
        binarySearch(aux.getBillions(),indexStream,billioIndex);
        int regpos = 5 + (indexStream.tellg() /(regSize-1));
        bool downCondition = true;
        bool upCondition = true;
        do 
        {
            if(regpos != 5) 
            {
                BillioIndex downAux;
                indexStream.seekg(regpos - (regSize-1));
                downAux.readBillioIndex(indexStream);
                downCondition = downAux.getBillions() >= aux.getBillions();
            }
            if(regpos != 5 + (fileSize + 1) /(regSize-1))
            {
                BillioIndex upAux;
                indexStream.seekg(regpos + (regSize-1));
                upAux.readBillioIndex(indexStream);
                upCondition = upAux.getBillions() <= aux.getBillions();
            }
            if(!(downCondition && upCondition))
            {
                if(aux.getState() == -1)
                { 
                    mainStream.seekg(0, ios::end);
                    indexStream.seekg(0, ios::end);
                    break;
                }
                else
                {
                    mainStream.seekg(5 + aux.getState()*(regSize - 1));
                    aux.readBillio(mainStream);
                }
            }
        } while(downCondition && upCondition || aux.getState() == -1);
        if(downCondition && upCondition)
        { 
            indexStream.seekg(regpos);
            header = aux.getState();
            mainStream.seekg(5 + (header - 1)*(regSize - 1));
            ofstream writeHeader(filename);
            writeHeader.seekp(0, ios::beg);
            std::stringstream newHeader;
            newHeader << header;
            writeHeader<<newHeader.str().c_str()<<endl;
        }
    }

    newBillionary.readBillio(mainStream);
    newBillionary.setId(++fileSize);
    newBillionary.setState(0);
    mainStream.close();

    newIndex.readBillioIndex(indexStream);
    indexStream.close();
}

void ISAM::eliminate(float key) 
{
    ifstream indexStream(index);
    BillioIndex billioIndex;

    //Si no encuentra el registro o ya esta eliminado, no se hace nada
    if(!binarySearch(key, indexStream, billioIndex)) return;

    Billio billionary;
    ifstream mainStream(filename);
    char temp[5];
    int header {};

    //Obtener header
    mainStream.seekg(0, ios::beg);
    mainStream.read(temp,4);
    sscanf(temp, "%d", &header);

    //Ir al registro a eliminar
    mainStream.seekg((billioIndex.getPos()*(regSize+1), ios::beg));
    billionary.readBillio(mainStream);

    //Eliminación LIFO
    int aux = header;
    header = billionary.getId();   
    billionary.setState(aux);

    //Escritura del header modificado
    mainStream.seekg(0, ios::beg);
    memset(temp, 0, 5);
    snprintf(temp, sizeof(temp), "%d", header);
    std::replace(begin(temp), end(temp)-1, '\0', ' ');

    mainStream.close();
    indexStream.close();
}

void ISAM::test() 
{
    /*
    Antes de cada corrida del test posterior al primer llamado, por favor, restaure los archivos
    "index_data_isam" y  "data_isam" con los archivos "cache_index_isam" y "cache_data_isam" 
    respectivamente. El test no correrá apropiadamente sin ese cambio.
    cout<<endl<<" =========[TESTS DE ISAM]========="<<endl;
    */
    ISAM isam ("data_isam");

    cout<<endl<<"<--[ISAM] TEST DE SEARCH (no eliminados) -->"<<endl;
    Billio testSearch1("Carlos Slim", "56.50", "Mexico", "Diversified");
    pair<bool,Billio> billionary = isam.search(56.50);
    if(!(billionary.first && billionary.second == testSearch1))
        cout<<"\n[ISAM] ERROR: Test1. Falla en search(key) sin eliminaciones";
    billionary.second.toString();    
    Billio testSearch2("Jeff Bezos", "188.00", "United States", "Technology");
    billionary = isam.search(188.00);
    if(!(billionary.first && billionary.second == testSearch2))
        cout<<"\n[ISAM] ERROR: Test2. Falla en search(key) sin eliminaciones";
    billionary.second.toString();      
    Billio testSearch3("Zhang Yiming", "44.50", "United States", "Technology");
    billionary = isam.search(44.500);
    if(!(billionary.first && billionary.second == testSearch2))
        cout<<"\n[ISAM] ERROR: Test3. Falla en search(key) sin eliminaciones";
    billionary.second.toString();  

    cout<<endl<<"<--[ISAM] TEST DE SERCH-BETWEEN-->"<<endl;
    vector<Billio> billionaries = searchBetween(188.00, 44.50);
    for(auto billio: billionaries) billio.toString();

    cout<<endl<<"<--[ISAM] TEST DE ADD (no eliminados)-->"<<endl;
    Billio testAdd1("Peter Castle", "100.00", "Peru", "Teacher");
    isam.add(testAdd1);
    if(isam.search(100.00).second != testAdd1) 
        cout<<"\n[ISAM] ERROR: Test1. Falla en add(newBillionary) sin eliminaciones";
    Billio testAdd2("Fransisco Sagasti", "360.50", "Peru", "Industrial");
    isam.add(testAdd2);
    if(isam.search(360.50).second != testAdd2);
        cout<<"\n[ISAM] ERROR: Test2. Falla en add(newBillionary) sin eliminaciones";
    Billio testAdd3("Elmgam Wemsem", "40.80", "Germany", "Technology");
    if(isam.search(40.80).second != testAdd3);
        cout<<"\n[ISAM] ERROR: Test3. Falla en add(newBillionary) sin eliminaciones";    

    cout<<endl<<"<--[ISAM] ELIMINACIONES -->"<<endl;
    cout<<"Eliminando: Peter Castle (key = 100.00)"<<endl;     
    isam.eliminate(100.00);
    cout<<"Eliminando: Fransisco Sagasti (key = 360.50)"<<endl;     
    isam.eliminate(360.50);
    cout<<"Eliminando: Elmgam Wemsem (key = 40.80)"<<endl;     
    isam.eliminate(40.80);

    cout<<endl<<"<--[ISAM] TEST DE ADD Y SEARCH (con eliminados)-->"<<endl;
    Billio testAddE1("Castle Peter", "110.00", "Peru", "Politician");
    isam.add(testAddE1);
    if(isam.search(110.00).second != testAddE1) 
        cout<<"\n[ISAM] ERROR: Test1. Falla en add(newBillionary) sin eliminaciones";
    Billio testAddE2("Vimzcarra", "360.50", "Peru", "Industrial");
    isam.add(testAddE2);
    if(isam.search(360.50).second != testAddE2);
        cout<<"\n[ISAM] ERROR: Test2. Falla en add(newBillionary) sin eliminaciones";
    Billio testAddE3("Lamgam Wemsem", "26.7", "Germany", "Technology");
    isam.add(testAddE3);
    if(isam.search(26.7).second != testAddE3);
        cout<<"\n[ISAM] ERROR: Test3. Falla en add(newBillionary) sin eliminaciones";    
}

//Utilities

bool ISAM::binarySearch(float key, ifstream& stream, BillioIndex& billioIndex) 
{
    int left = 0;
    int rigth = fileSize - 1;

    while(left <= rigth)
    {
        int mid = (left + rigth) / 2;
        stream.seekg(mid*(indexSize+1), ios::beg);
        billioIndex.readBillioIndex(stream);

        if(billioIndex.getBillions() < key) rigth = mid - 1;
        else if(billioIndex.getBillions() > key) left = mid + 1;
        else return true;
    }
    if(fileSize != 1) 
    {
        stream.seekg(5 + (rigth-1)*(indexSize+1), ios::beg);
        billioIndex.readBillioIndex(stream);
    }
    return false;
}

#endif //BD2_P1_ISAM_H.