#ifndef BD2_P1_FL_SEQFILE_H
#define BD2_P1_FL_SEQFILE_H
#include "billionaries.h"

int regSize = sizeof(Billio)-7;

class SeqFile {
private:
    string filename {};
    string aux {};
    void buildFile();
    bool binarySearch(float key, ifstream &stream, Billio & billionary);
    
    size_t fileSize = 30;
    size_t maxaux = 10;
    size_t sizeaux = 0;
public:
    explicit SeqFile(string file): filename("data/"+ file + ".txt") {cout<<"Se guardo el archivo"<<endl;};
    pair<bool,Billio> searchmain(float key);
    pair<bool,Billio> searchaux(float key);
    pair<bool,Billio> search(float key);
    vector<Billio> searchBetween (float left, float right);
    void add(Billio billionary);
    void eliminate(float key);
    void test();
    void midsearch();
    Billio firstB();
};


pair<bool,Billio> SeqFile::searchmain(float key) {
    ifstream db(filename);
    Billio billionary;
    if(binarySearch(key, db, billionary)) return make_pair(true, billionary) ;
    else {
        // db.seekg(6 + (regSize)*fileSize, ios::beg);
        // while(billionary.readBillio(db))
        //      if(billionary.getBillions() == key) return billionary;
        return make_pair(false, billionary);
    }
}

pair<bool,Billio> SeqFile::searchaux(float key) {
    ifstream db(filename);
    Billio temp;

    float fcomp;
    int  fstate;

    char comp[7];
    char state[5];//
    int cont = 0;

    while (cont < sizeaux)
    {
        db.seekg(5 + 54 + (fileSize + (cont))*(regSize+1), ios::beg);
        db.read(comp,6);
        sscanf(comp, "%f", &fcomp);

        db.seekg(5 + 120 + (fileSize + (cont))*(regSize+1), ios::beg);
        db.read(state,4);
        sscanf(state, "%d", &fstate);

        // cout<<fstate<<endl;

        if(fcomp >= key && fstate == 0)
        {
            db.seekg(5 + (fileSize + (cont))*(regSize+1), ios::beg);
            temp.readBillio(db);
            if(fcomp==key)
            {
                return make_pair(true,temp);
            }
        }
        cont++;
        
    }return make_pair(false, temp);
}

pair<bool,Billio> SeqFile::search(float key)
{
    auto s_m = searchmain(key);
    // auto s_a = searchaux(key);
    pair<bool, Billio> s_a;   //searchmain aux

    Billio billion;
    if(sizeaux != 0)  
    {
        s_a = this->searchaux(key);
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
    float start = max(left, right);
    float end = min(left,right);
    Billio startIndex = searchmain(start).second;

    do {
        ifstream stream(filename);
        stream.seekg(5 + (startIndex.getNext()-1)*(regSize+1), ios::beg);
        startIndex.readBillio(stream);
        if(startIndex.getBillions() >= end) out.push_back(startIndex);
    } while(startIndex.getBillions() >= end);
    
    return out;
}

void SeqFile::add(Billio add) {
    fstream db(filename, ios::in | std::fstream::out);

    auto s_m = this->searchmain(add.getBillions()); //searchmain main

    pair<bool, Billio> s_a;   //searchmain aux

    int header {};
    char temp[5];
    db.seekg(0, ios::beg);
    db.read(temp,4);
    sscanf(temp, "%d", &header);
    //cout<<header<<" ";

    // if(header != -1)
    // {

    // }

    if(sizeaux != 0)  s_a = this->searchaux(add.getBillions());
    
    else s_a = make_pair(false, Billio());
    
    if(!s_m.first && !s_a.first)
     {
        // if(maxaux==sizeaux) 
        // {
        //     heapify(); //mergeo
        //     this->sizeaux = 0; 
        //     this->add(billio);
        // }
        Billio billion;
        if(sizeaux != 0)
        {
            billion = (s_m.second.getBillions() > s_a.second.getBillions()) ? 
                        s_a.second : s_m.second;
        }
        else
        {
            billion = s_m.second;
        }

        if(header!=-1)
        {
            if(billion.getId()==firstB().getId()  && billion.getBillions() < add.getBillions())
            {
                db.seekg(5 + (header-1)*(regSize+1), ios::beg);
                Billio temp_e;
                temp_e.readBillio(db);
                temp_e.toString();

                add.setId(header);
                add.setNext(billion.getId());
                add.setState(0);

                add.toString();

                db.seekp(0,ios::beg);

                db<<temp_e.state;

                db.seekp(5 + (header-1)*(regSize+1), ios::beg);
                db<<add.id;
                db<<add.nombre<<add.billions<<add.country;
                db<<add.industry<<add.state<<add.next;
                db<<endl;
                fileSize++;
                sizeaux++;
                return;

                
            }

            db.seekg(5 + (header-1)*(regSize+1), ios::beg);
            Billio temp_e;
            
            temp_e.readBillio(db);
            
            
            add.setId(header);
            add.setNext(billion.getNext());
            add.setState(0);

            billion.setNext(header);

            db.seekp(0,ios::beg);

            db<<temp_e.state;
            db.seekp(124 + 5 + (billion.getId()-1)*(regSize+1), ios::beg);
            db<<billion.next;

            
            db.seekp( 5 + (add.getId()-1)*(regSize+1), ios::beg);

            db<<add.id;
            db<<add.nombre<<add.billions<<add.country;
            db<<add.industry<<add.state<<add.next;
            db<<endl;

            fileSize++;
            sizeaux++;
            
            return;
        }
           
        // billion.toString2();

        if(billion.getId()==firstB().getId()  && billion.getBillions() < add.getBillions())
        {
            add.setId( fileSize + sizeaux + 1);
            add.setNext(firstB().getId());
            add.setState(0);

            // add.toString2();
            db.seekp(0, ios::end);
            db<<add.id;
            db<<add.nombre<<add.billions<<add.country;
            db<<add.industry<<add.state<<add.next;
            db<<endl;
            fileSize++;
            sizeaux++;
        }
        else
        {
            add.setId(fileSize + sizeaux + 1);
            add.setNext(billion.getNext());
            add.setState(0);
            billion.setNext(fileSize + sizeaux + 1);
            db.seekp(124 + 5 + (billion.getId()-1)*(regSize+1), ios::beg);
            db<<billion.next;
            db.seekp(0, ios::end);
            db<<add.id<<add.nombre<<add.billions<<add.country;
            db<<add.industry<<add.state<<add.next;
            db<<endl;
            fileSize++;
            sizeaux++;
        }
        
        



        //stream.seekg(5 + mid*(regSize+1), ios::beg);
    }
    else cout<<"ya existe";
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


    // pair<bool,Billio> find_m = searchmain(key);
    // pair<bool,Billio> find_a = searchaux(key);
    // cout<<find_m.second.getBillions()<<endl;
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

        
        stream.seekp(120 + 5 + (find.second.getId()-1)*(regSize+1), ios::beg);

        stream<<find.second.state;

        stream.close();

        fstream stream(filename, ios::in | std::fstream::out);

        auto prev = this->search(key);
        prev.second.toString();
        if(prev.second.getId() != firstB().getId())
        {
            stream.seekp(124 + 5 + (prev.second.getId()-1)*(regSize+1), ios::beg);
            stream<<find.second.next;
        }
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
    int rigth = fileSize - 1;
    
    while(left <= rigth) 
    {
        int mid = (left + rigth)/2;
        stream.seekg(5 + mid*(regSize+1), ios::beg);
        billionary.readBillio(stream);
        

        if(billionary.getBillions() < key) rigth = mid - 1;

        else if(billionary.getBillions() > key) left = mid + 1;
        
        //exista
        else if (billionary.getBillions() == key)
        {
            //existe y no eliminado
            if(billionary.getState() == 0)
            {
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
                            stream.seekg(5 + (temp-1)*(regSize+1), ios::beg);
                            billionary.readBillio(stream);
                            temp++;
                        }
                        return false;
                    }

                    stream.seekg(5 + (mid-1)*(regSize+1), ios::beg);
                    billionary.readBillio(stream);
                    mid--;

                }
                return false;
            }
        }
        
        // no exista y no sea el primero

        if(mid != 0 && mid == left || mid == rigth) { 

            stream.seekg(5 + (left-1)*(regSize+1), ios::beg);
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
                        cout<<"asex1";
                        //mid++;
                        while(billionary.getState()!=0)
                        {
                            stream.seekg(5 + (temp-1)*(regSize+1), ios::beg);
                            billionary.readBillio(stream);
                            temp++;
                        }
                        return false;
                    }

                    stream.seekg(5 + (mid-1)*(regSize+1), ios::beg);
                    billionary.readBillio(stream);
                    mid--;

                }
                return false;
            }
        }
        

    }
   if(billionary.getState() == 0)
    {
        return false;
    }

    //esta eliminado
    else
    {
        int mid=1;

        cout<<"asex1";
                        //mid++;
        while(billionary.getState()!=0)
        {
            stream.seekg(5 + (mid-1)*(regSize+1), ios::beg);
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
    int rigth = fileSize - 1;
  
    
    int mid = ((left + rigth)/2)-1;
    Billio billionary;
    
    stream.seekg(5 + mid*(regSize+1), ios::beg);

    billionary.readBillio(stream);
    billionary.toString();
    
}
Billio SeqFile::firstB()
{
    auto i = this->search(999999);
    return i.second;
}

#endif //BD2_P1_FL_SEQFILE_H.