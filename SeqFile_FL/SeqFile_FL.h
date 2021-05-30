#ifndef BD2_P1_FL_SEQFILE_H
#define BD2_P1_FL_SEQFILE_H
#include "billionaries.h"

int regSize = sizeof(Billio)-6;

class SeqFile {
private:
    string filename {};
    string aux {};
    void buildFile();
    bool binarySearch(float key, ifstream &stream, Billio & billionary);
    
    size_t fileSize = 29;
    size_t maxaux = 10;
    size_t sizeaux = 0;
public:
    explicit SeqFile(string file): filename(std::move(file)){cout<<"Se guardo el archivo"<<endl;};
    pair<bool,Billio> search(float key);
    vector<Billio> searchBetween (float left, float right);
    void add(Billio billionary);
    void eliminate(Billio billionary);
    void test();
    void midsearch();
};


pair<bool,Billio> SeqFile::search(float key) {
    ifstream db("newdata/"+ filename + ".txt");
    Billio billionary;
    bool found = binarySearch(key, db, billionary);
    if(found) return make_pair(found, billionary) ;
    else {
        
        // db.seekg(6 + (regSize)*fileSize, ios::beg);
        // while(billionary.readBillio(db))
        //      if(billionary.getBillions() == key) return billionary;

        return make_pair(false, billionary);
    }
}

vector<Billio> SeqFile::searchBetween(float left, float right) {
    //Busqueda de left. Hacer next hasta llegar a right
    return vector<Billio>();
}

void SeqFile::add(Billio billio) {
    ofstream db("newdata/"+ filename + ".txt", ios::app);
    auto i = this->search(billio.getBillions());
    if(!i.first)
    {
        // if(maxaux==sizeaux) 
        // {
        //     heapify(); //mergeo
        //     this->sizeaux = 0; 
        //     this->add(billio);
        // }

        



        //stream.seekg(5 + mid*(regSize+1), ios::beg);
    }
    // db<<billio.nombre<<billio.billions<<billio.country;
    // db<<billio.industry<<billio.state<<billio.next;
    // db<<endl;
    
    //db.close();
}

void SeqFile::eliminate(Billio billionary) {
    
}

void SeqFile::test() {
    Billio temp;
    ifstream db("newdata/"+ filename + ".txt");
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
        if(billionary.getBillions() > key) left = mid + 1;
        else if(billionary.getBillions() < key) rigth = mid - 1;
        else if(billionary.getBillions()==key) return true;
    }

    return false;
}

//TODO: Eliminar esto
void SeqFile::midsearch() {
    ifstream stream("newdata/"+ filename + ".txt");
    int left = 0;
    int rigth = fileSize - 1;
  
    
    int mid = ((left + rigth)/2)-1;
    Billio billionary;
    
    stream.seekg(5 + mid*(regSize+1), ios::beg);

    billionary.readBillio(stream);
    billionary.toString();
    
}

#endif //BD2_P1_FL_SEQFILE_H.