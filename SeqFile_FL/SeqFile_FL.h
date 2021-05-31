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
    pair<bool,Billio> search(float key);
    pair<bool,Billio> searchaux(float key);
    vector<Billio> searchBetween (float left, float right);
    void add(Billio billionary);
    void eliminate(float key);
    void test();
    void midsearch();
};


pair<bool,Billio> SeqFile::search(float key) {
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
    char comp[7];
    int cont = 0;
    while (cont < sizeaux)
    {
        db.seekg(5 + 54 + (fileSize + (cont))*(regSize+1), ios::beg);
        db.read(comp,6);
        sscanf(comp, "%f", &fcomp);
        // cout<<fcomp<<" ";
        if(fcomp >= key)
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

vector<Billio> SeqFile::searchBetween(float left, float right) {
    vector<Billio> out {};
    float start = max(left, right);
    float end = min(left,right);
    Billio startIndex = search(start).second;

    do {
        ifstream stream(filename);
        stream.seekg(5 + (startIndex.getNext()-1)*(regSize+1), ios::beg);
        startIndex.readBillio(stream);
        if(startIndex.getBillions() >= end) out.push_back(startIndex);
    } while(startIndex.getBillions() >= end);
    
    return out;
}

void SeqFile::add(Billio add) {
    ofstream db(filename, ios::in);

    auto s_m = this->search(add.getBillions()); //search main

    pair<bool, Billio> s_a;   //search aux

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
           
        billion.toString2();

        if(billion.getId()==1  && billion.getBillions() < add.getBillions())
        {
            add.setId( fileSize + sizeaux + 1);
            add.setNext( 1 );
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

void SeqFile::eliminate(float key) {
    fstream stream(filename, ios::in | std::fstream::out);
    int header {};
    char temp[5];
    stream.seekg(0, ios::beg);
    stream.read(temp,4);
    sscanf(temp, "%d", &header);

    pair<bool,Billio> find_m = search(key);

    cout<<find_m.second.getBillions()<<endl;
    if(find_m.second.getBillions() == key)
    {
        int tempi = find_m.second.getId(); //poner en header
        find_m.second.setState(header);
        header = tempi;

        stream.seekp(0, ios::beg);

        memset(temp, 0, 5);
        snprintf(temp, sizeof(temp), "%d", header);
        std::replace(begin(temp), end(temp)-1, '\0', ' ');
        cout<<temp<<" ";
        cout<<find_m.second.state;

        stream<<temp;

        
        stream.seekp(120 + 5 + (find_m.second.getId()-1)*(regSize+1), ios::beg);

        stream<<find_m.second.state;

    }
    stream.close();
    
    // auto find_a = searchaux(key);

    // findm(key), -> -1,
    // seekg(key.id-1) leo    

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
  
    while(left <= rigth) {
        int mid = (left + rigth)/2;
        stream.seekg(5 + mid*(regSize+1), ios::beg);
        billionary.readBillio(stream);
        
        
        if(mid != 0 && mid == left && mid == rigth) { // get max near
            if(billionary.getBillions() >= key) mid++;
            stream.seekg(5 + (mid-1)*(regSize+1), ios::beg);
            billionary.readBillio(stream);

            if(billionary.getBillions() > key ) return false;
            else if (billionary.getBillions() == key ) return true;
        
        }
        else if(billionary.getBillions() > key) left = mid + 1;
        else if(billionary.getBillions() < key) rigth = mid - 1;
        else if(billionary.getBillions() == key) return true; 
    }

    return false;
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

#endif //BD2_P1_FL_SEQFILE_H.