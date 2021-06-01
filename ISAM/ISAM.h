#ifndef BD2_P1_ISAM_H
#define BD2_P1_ISAM_H
#include "index.h"

int regSize = sizeof(Billio) - 6;
int indexSize = sizeof(BillioIndex) - 2;

class ISAM {
private:
    int fileSize = 30;
    string filename {};
    string index = "data/index.txt";
    bool binarySearch(float key, ifstream &stream, BillioIndex& billionary);

public:
    explicit ISAM(const string& file): filename("data/"+ file + ".txt"){};
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
        int regpos = billioIndex.getPos();
        if(regpos == 0)
        {
            //No podemos buscar por arriba, ya que es el primer elemento.
            //Buscar, entonces, por abajo.
            while(billionary.getState() != 0)
            {
                indexStream.seekg((regpos++)*(indexSize+1), ios::beg);
                billioIndex.readBillioIndex(indexStream);
                mainStream.seekg(5 + (billioIndex.getPos())*(regSize+1), ios::beg);
                billionary.readBillio(mainStream);
            }
        }
        else
        {
            //Buscar por arriba el menor elemento mayor al que se pidio
            indexStream.seekg((regpos--)*(regSize+1), ios::beg);
            billioIndex.readBillioIndex(indexStream);
            mainStream.seekg(5 + (billioIndex.getPos())*(regSize+1), ios::beg);
            billionary.readBillio(mainStream);
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
    binarySearch(startIndex.getBillions(),indexStream,rangeDelim);

    //Mientras se mantenga en el rango
    while(rangeDelim.getBillions() >= end)
    {
        mainStream.seekg(9 + (rangeDelim.getPos())*(regSize+1), ios::beg);
        startIndex.readBillio(mainStream);
        if(startIndex.getState() == 0) out.push_back(startIndex);
        int regpos = (indexStream.tellg() / (5 + regSize - 1));
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

    //Escribir en heap (main). Adicionalmente, intentará buscar un registro eliminado apropiado para insertar
    if(header == -1) mainStream.seekg(0, ios::beg);
    else {
        mainStream.seekg(5 + (header - 1)*(regSize - 1));
        Billio aux;
        BillioIndex billioIndex;
        aux.readBillio(mainStream);

        //Buscar un registro eliminado tal que su mayor y menor consecutivos sean tambien los del nuevo registro. (Podria no encontrarse)
        binarySearch(aux.getBillions(),indexStream,billioIndex);
        int regpos = ((int) indexStream.tellg() /(5 + regSize-1));
        bool downCondition = true;
        bool upConditon = true;
        do 
        {
            if(regpos != 5) 
            {
                BillioIndex downAux;
                indexStream.seekg(regpos - (regSize-1) - 5 );
                downAux.readBillioIndex(indexStream);
                downCondition = downAux.getBillions() >= aux.getBillions();
            }
            if(regpos != 5 + (fileSize + 1) /(regSize-1)))
            {
                BillioIndex upAux;
                indexStream.seekg(regpos + (regSize-1) + 5 );
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
                    mainStream.seekg(5 + aux.getState()*(regSize -));
                    aux.readBillio(mainStream);
                }
            }
        } while(downCondition && upCondition || aux.getState() == -1);
        if(downCondition && upConditon)
        { 
            indexStream.seekg(regpos);
            header = aux.getState();
            mainStream.seekg(5 + (header - 1)*(regSize - 1));
            ofstream writeHeader(filename);
            char newHeader[] = header +  "     \n";
            writeHeader<<newHeader;
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
    mainStream.seekg(5 + (billioIndex.getPos())*(regSize+1), ios::beg);
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
    stream.seekg((rigth-1)*(indexSize+1), ios::beg);
    billioIndex.readBillioIndex(stream);
    return false;
}

#endif //BD2_P1_ISAM_H.