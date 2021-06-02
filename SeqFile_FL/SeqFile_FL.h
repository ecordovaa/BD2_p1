#ifndef BD2_P1_FL_SEQFILE_H
#define BD2_P1_FL_SEQFILE_H
#include "billionaries.h"

int regSize = sizeof(Billio)-7;


class SeqFile {
private:
    int filesizemain = 30;
    string filename {};
    string aux {};
    void buildFile();
    bool binarySearch(float key, ifstream &stream, Billio & billionary);
    
    
    size_t maxaux = 10;
    
public:
    size_t sizeaux = 0;
    size_t fileSize = filesizemain;
    explicit SeqFile(string file): filename("data/"+ file + ".txt") {cout<<"Se guardo el archivo"<<endl;};
    pair<bool,Billio> searchmain(float key);
    pair<bool,Billio> searchaux(float key);
    pair<bool,Billio> search(float key);
    vector<Billio> searchBetween (float left, float right);
    void adding(Billio billionary);
    void eliminate(float key);
    void test();
    void midsearch();
    void sortd();
    Billio firstB();

};


pair<bool,Billio> SeqFile::searchmain(float key) {

    ifstream db(filename);
    Billio billionary;
    // binarysearch en el main;
    // 
    bool i = binarySearch(key, db, billionary);
    db.close();
    return make_pair(i,billionary);  //

}

pair<bool,Billio> SeqFile::searchaux(float key) {

    ifstream db(filename);
    Billio temp;
    bool btemp;

    vector<int> vtemp;
    Billio billion;

    float keymin = 1000, keymax = 0;
    int idmin, idmax;


    int cont = 0;
    
    while (cont < sizeaux)
    {
        db.seekg(9  + (this->filesizemain + (cont))*(regSize+1), ios::beg);

        billion.readBillio(db);

        if(billion.getState()==0)
        {
            vtemp.push_back(billion.getId());
        }
        cont++;
        
    }
    
    if(vtemp.size()==1) 
    {
        db.seekg(9  + (vtemp[0]-1)*(regSize+1), ios::beg);
        billion.readBillio(db);
        btemp = ( key == billion.getBillions()) ? true:false;
        db.close();
        return make_pair(btemp,billion);
    }
    else
    {
        for(cont = 0; cont < vtemp.size();cont++)
        {
            db.seekg(9  + (vtemp[cont]-1)*(regSize+1), ios::beg);
            billion.readBillio(db);

            if( key < billion.getBillions() && keymin > billion.getBillions() ){ 
                idmin = billion.getId();
                keymin = billion.getBillions(); 
            }
            if(keymax < billion.getBillions() ){ 
                idmax = billion.getId();
                keymax =  billion.getBillions(); 
            }
            if(key == billion.getBillions())
            {
                db.close();
                return make_pair(true, billion);
            }

        }
        if ( keymax < key)
        {
            db.seekg(9  + (idmax-1)*(regSize+1), ios::beg);
            billion.readBillio(db);
            db.close();
            return make_pair(false, billion);
        }
        else
        {
            db.seekg(9  + (idmin-1)*(regSize+1), ios::beg);
            billion.readBillio(db);
            db.close();
            return make_pair(false, billion);
        } 
    }
}


pair<bool,Billio> SeqFile::search(float key)
{
    // primero busco en el main
    auto s_m = searchmain(key);


    pair<bool, Billio> s_a;   //searchaux

    Billio billion;

    if(sizeaux != 0)  
    {
        // cout<<endl<<" ola "<<endl;
        // cout<<sizeaux<<endl;

        s_a = this->searchaux(key);
        // s_m.second.toString();
        //-
        if( s_m.second.getBillions() < key || s_a.second.getBillions() < key)  // 500
        {
            return (s_m.second.getBillions() > s_a.second.getBillions()) ? 
                        s_m : s_a;
        }
        
        // if(s_m.second.getBillions()>s_a.second.getBillions())

        //-
        return (s_m.second.getBillions() > s_a.second.getBillions()) ? 
                        s_a : s_m;

    }
    else
    {
        return s_m;
    }

}

vector<Billio> SeqFile::searchBetween(float left, float right) {
    vector<Billio> out {};
    ifstream stream(filename);
    float temp, start;
    temp = start  = max(left, right);
    float end = min(left,right);
    Billio startIndex = search(start).second;

    while(start >= end )
    {
        if(startIndex.getBillions() <= temp) out.push_back(startIndex);
        
        stream.seekg(9 + (startIndex.getNext()-1)*(regSize+1), ios::beg);
        startIndex.readBillio(stream);
        start = startIndex.getBillions();
        if(startIndex.getNext() == 0)
        {
            out.push_back(startIndex);
            break;
        }
    }
    stream.close();
    return out;
}


void SeqFile::sortd()
{
    // cont filesize
    ifstream stream(filename);

    vector<Billio> sorted = {};
    
    Billio first = this->firstB();

    while(true)
    {
        if(first.getNext() == 0)
        {
            sorted.push_back(first);
            break;
        }
        else { sorted.push_back(first); }
        stream.seekg(9 + (first.getNext()-1)*(regSize+1), ios::beg);
        first.readBillio(stream);

    }
    stream.close();

    ofstream overdb(filename, ios::trunc);

    char temp[] = "-1     1\n";
    overdb<<temp;

    
    for(int i = 0; i < sorted.size(); ++i)
    {
        if(i!=sorted.size()-1)
        {
            sorted[i].setId(i+1);
            sorted[i].setNext(i+2);
        }
        else 
        {
            sorted[i].setId(i+1);
            sorted[i].setNext(0);
        }
        
        overdb<<sorted[i].id;            
        overdb<<sorted[i].nombre<<sorted[i].billions<<sorted[i].country;
        overdb<<sorted[i].industry<<sorted[i].state<<sorted[i].next;
        overdb<<endl;
    }

    filesizemain = this->fileSize = sorted.size();
    this->sizeaux = 0; 
    cout<<endl<<"Se llego a un maximo de records en el auxiliar"<<endl;
    cout<<"New Data have " << fileSize<< " records in main and " <<sizeaux+1 <<" records in aux."<<endl<<endl;
    overdb.close();
}


void SeqFile::adding(Billio add) {
    fstream db(filename, ios::in | std::fstream::out);

    //auto s_m = this->searchmain(add.getBillions()); //searchmain main

    auto search_a = this->search(add.getBillions());   //search 

    int header {};
    char temp[5];
    db.seekg(0, ios::beg);
    db.read(temp,4);
    sscanf(temp, "%d", &header);
   
   
    if(!search_a.first)
    {
        if(maxaux==sizeaux) 
        {
            this->sortd(); //mergeo
            db.close();
            this->adding(add);
            return;
        }
        Billio billion = search_a.second;

        /*

        

        if(header!=-1)
        {
            if(billion.getId()==firstB().getId()  && billion.getBillions() < add.getBillions())
            {
                
                db.seekg(9 + (header-1)*(regSize+1), ios::beg);
                Billio temp_e;
                temp_e.readBillio(db);
                
                add.setId(header);
                add.setNext(billion.getId());
                add.setState(0);
                billion.toString();
                temp_e.toString();
                add.toString();

                db.seekp(0,ios::beg);

                db<<temp_e.state;

                db.seekp(4,ios::beg);

                db<<add.id;

                db.seekp(9 + (header-1)*(regSize+1), ios::beg);
                db<<add.id;
                db<<add.nombre<<add.billions<<add.country;
                db<<add.industry<<add.state<<add.next;
                db<<endl;
                fileSize++;

                
                return;

                
            }

            db.seekg(9 + (header-1)*(regSize+1), ios::beg);
            Billio temp_e;
            
            temp_e.readBillio(db);
            
            
            add.setId(header);
            add.setNext(billion.getNext());
            add.setState(0);

            billion.setNext(header);

            db.seekp(0,ios::beg);

            db<<temp_e.state;
            db.seekp(124 + 9 + (billion.getId()-1)*(regSize+1), ios::beg);
            db<<billion.next;

            
            db.seekp( 9 + (add.getId()-1)*(regSize+1), ios::beg);

            db<<add.id;
            db<<add.nombre<<add.billions<<add.country;
            db<<add.industry<<add.state<<add.next;
            db<<endl;

            fileSize++;
            
            return;
        }
           
        billion.toString();

        */
        // billion.toString();
        if(billion.getId()==firstB().getId()  && billion.getBillions() < add.getBillions())
        {
            cout<<" cambiando el primero"<<endl;
            add.setId( filesizemain + sizeaux + 1);
            add.setNext(firstB().getId());
            add.setState(0);

            
            db.seekp(4,ios::beg);
            db<<add.id;

            db.seekp(0, ios::end);
            db<<add.id;
            
            db<<add.nombre<<add.billions<<add.country;
            db<<add.industry<<add.state<<add.next;
            db<<endl;
            db.close();
            // fileSize++;
            sizeaux++;
            return;
        }
        else
        {
            add.setId(filesizemain + sizeaux + 1);
            add.setNext(billion.getNext());
            add.setState(0);
            billion.setNext(filesizemain + sizeaux + 1);
            db.seekp(124 + 9 + (billion.getId()-1)*(regSize+1), ios::beg);
            db<<billion.next;
            db.seekp(0, ios::end);
            db<<add.id<<add.nombre<<add.billions<<add.country;
            db<<add.industry<<add.state<<add.next;
            db<<endl;
            db.close();
            // fileSize++;
            sizeaux++;
            return;
        }
    }
    else 
    {
        cout<<"ya existe"<<endl;
    }
    // db<<billio.nombre<<billio.billions<<billio.country;
    // db<<billio.industry<<billio.state<<billio.next;
    // db<<endl;
    
    db.close();
}

void SeqFile::eliminate(float key) 
{
    fstream stream(filename, ios::in | std::fstream::out);

    int header {};
    char temp[5];
    stream.seekg(0, ios::beg);
    stream.read(temp,4);
    sscanf(temp, "%d", &header);



    auto find = this->search(key);


    if(find.second.getBillions() == key)
    {
        int tempi = find.second.getId(); //poner en header
        find.second.setState(header);
        header = tempi;

        stream.seekp(0, ios::beg);

        memset(temp, 0, 5);
        snprintf(temp, sizeof(temp), "%d", header);
        std::replace(begin(temp), end(temp)-1, '\0', ' ');

        stream<<temp;

        
        stream.seekp(120 + 9 + (find.second.getId()-1)*(regSize+1), ios::beg);

        stream<<find.second.state;

        stream.close();

        fstream stream(filename, ios::in | std::fstream::out);

        auto prev = this->search(key);
        
        if(find.second.getId() != firstB().getId())
        {
            stream.seekp(124 + 9 + (prev.second.getId()-1)*(regSize+1), ios::beg);
            stream<<find.second.next;
        }
        else
        {
            stream.seekp(4,ios::beg);

            stream<<prev.second.id;
        }
        // fileSize--;
        //if(find.second.getId() > filesizemain) { sizeaux--;}
    }

    else { cout<<"No existe el Registro con la key: "<< key<<endl;}
    stream.close();
    //sizeaux--
    //filesize--
}

void SeqFile::test() {
    Billio temp;
    ifstream db(filename);
    db.seekg(4,ios::beg);
    db.get();
    
    while(temp.readBillio(db)){
        temp.toString();
    }
    
    db.close();
}

bool SeqFile::binarySearch(float key, ifstream &stream, Billio & billionary) {
    int left = 0;
    int rigth = filesizemain - 1 ;
    
    while(left <= rigth) 
    {
        int mid = (left + rigth)/2;
        stream.seekg(9 + mid*(regSize+1), ios::beg);
        billionary.readBillio(stream);
        

        if(billionary.getBillions() < key) rigth = mid - 1;

        else if(billionary.getBillions() > key) left = mid + 1;
        
        //existe
        else if (billionary.getBillions() == key)
        {
            //existe y no eliminado
            if(billionary.getState() == 0)

            {
                // true && registro
                return true;
            }
            //exista y esta eliminado
            else
            {
                int temp = mid;
                while(billionary.getState()!=0)
                {
                    if (mid==0) 
                    {
                        temp++;
    
                        while(billionary.getState()!=0)
                        {
                            stream.seekg(9 + (temp-1)*(regSize+1), ios::beg);
                            billionary.readBillio(stream);
                            temp++;
                        }
                        return false;
                    }

                    stream.seekg(9 + (mid-1)*(regSize+1), ios::beg);
                    billionary.readBillio(stream);
                    mid--;

                }
                return false;
            }
        }
        
        // no exista y no sea el primero

        if(mid != 0 && mid == left || mid == rigth) { 

            stream.seekg(9 + (left-1)*(regSize+1), ios::beg);
            billionary.readBillio(stream);

            // no eliminado
            if(billionary.getState() == 0)
            {
                return false;
            }

            //esta eliminado
            else
            {
                int temp = mid;
                while(billionary.getState()!=0)
                {
                    temp++;
                    if (mid==0) 
                    {
                        //mid++;
                        while(billionary.getState()!=0)
                        {
                            stream.seekg(9 + (temp-1)*(regSize+1), ios::beg);
                            billionary.readBillio(stream);
                            temp++;
                        }
                        return false;
                    }

                    stream.seekg(9 + (mid-1)*(regSize+1), ios::beg);
                    billionary.readBillio(stream);
                    mid--;

                }
                return false;
            }
        }

    }


    //no exista y sea el primero
    // y no este eliminado
   if(billionary.getState() == 0)
    {
        return false;
    }

    //esta eliminado
    else
    {
        int mid=1;

        // cout<<"asex1";
                        //mid++;
        while(billionary.getState()!=0)
        {
            stream.seekg(9 + (mid-1)*(regSize+1), ios::beg);
            billionary.readBillio(stream);
            mid++;
        }
        return false;
    }
}

//TODO: Eliminar esto
void SeqFile::midsearch() {
    ifstream stream(filename);
    int left = 0;
    int rigth = filesizemain - 1;
  
    
    int mid = ((left + rigth)/2)-1;
    Billio billionary;
    
    stream.seekg(9 + mid*(regSize+1), ios::beg);

    billionary.readBillio(stream);
    billionary.toString();
    stream.close();
    
}
Billio SeqFile::firstB()
{

    fstream db(filename, ios::in | std::fstream::out);
    int first {};
    char temp[5];
    db.seekg(4, ios::beg);
    db.read(temp,4);
    sscanf(temp, "%d", &first);
    Billio tempb;
    db.seekg(9 + (first-1)*(regSize+1), ios::beg);
    tempb.readBillio(db);
    db.close();
    return tempb;


    // auto i = search(999);
    // return i.second;
}

#endif //BD2_P1_FL_SEQFILE_H.