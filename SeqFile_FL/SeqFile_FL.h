#ifndef BD2_P1_FL_SEQFILE_H
#define BD2_P1_FL_SEQFILE_H
#include "botella.h"

class SeqFile {
private:
    string filename {};
    string aux {};
    void buildFile();
    Botella binarySearch(int key);
    size_t fileSize = 50;
public:
    explicit SeqFile(string file): filename(std::move(file)){cout<<"Se guardo el archivo"<<endl;};
    Botella search(int key);
    vector<Botella> searchBetween (int left, int right);
    void add(Botella botella);
    void eliminate(Botella botella);
    void test();
};

/*
Botella SeqFile::search(int key) {
    if(++key > fileSize ) domain_error("\nERROR: search(key) | La key ingresada esta fuera de rango.");
    Botella botella = binarySearch(key);
    if(botella != Botella()) return botella;
    fstream auxFile(aux);
    auxFile.seekg(6, ios::beg);
    while(auxFile.read((char*) &botella, sizeof(Botella)))
        if(botella.id == key) return botella;
    cout<<"\nsearch(key) | No hay registros con key. Se retorna una instancia vacía.";    
    return Botella();
}*/

vector<Botella> SeqFile::searchBetween(int left, int right) {
    //Busqueda de left. Hacer next hasta llegar a right
    return vector<Botella>();
}

void SeqFile::add(Botella botella) {
    ofstream db("data/"+ filename + ".txt", ios::app);
    db<<botella.id<<botella.nivel<<botella.transparencia;
    db<<botella.faltante<<botella.turbidez<<botella.deficiente;
    db<<botella.impura<<botella.state<<botella.next;
    db<<endl;
    
    db.close();

}

void SeqFile::eliminate(Botella botella) {
    
}

void SeqFile::test() {
    // string temp1;
    Botella temp;
    ifstream db("data/"+ filename + ".txt");
    db.seekg(6,ios::beg);
    db.get();
    temp.readBotella(db);
    temp.toString();
    
    db.close();
}
/*
Botella SeqFile::binarySearch(int key){
    int left = 0;
    int right = fileSize - 1;
    while(left <= right) {
        int mid = (left + right) / 2;
        fstream midSearch(filename);
        Botella botella; 
        midSearch.seekg(mid * sizeof(Botella) + sizeof(int));
        midSearch.read((char*) &botella, sizeof(Botella));
        if(botella.id < key) left = mid + 1;
        if(botella.id > key) right = mid - 1;
        else {
            midSearch.seekg(mid * sizeof(Botella) + sizeof(int));
            midSearch.read((char*) &botella, sizeof(Botella));
            return botella;
        } 
    }
    return Botella();
}
*/
#endif //BD2_P1_FL_SEQFILE_H.