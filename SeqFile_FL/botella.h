
#include "../lib.h"

//La base de datos guarda datos sobre mediciones de liquidos en botellas
class Botella {
    public:
        char id[6];   //max 2147483647  6-digits
        char nivel[3];    //3
        char transparencia[4]; //4
        char faltante[2]; //2
        char turbidez[2]; //2
        char deficiente [1]; //0 false 1 true
        char impura [1]; //1

        char state[6]; //0: no eliminado, -1: fin de la cadena; >0: pos logica del nextDel (Eliminados)
        //6
        char next[6]; //Lista de ordenamiento
        //6
        bool operator==(const Botella &botella) const {
            return id == botella.id &&
                nivel == botella.nivel &&
                transparencia == botella.transparencia &&
                faltante == botella.faltante &&
                turbidez == botella.turbidez &&
                deficiente == botella.deficiente &&
                impura == botella.impura;
        }

        bool operator!=(const Botella &botella) const {
            return !(botella == *this);
        }

        void toString() {
            cout<<"id: "<<id<<endl;
            cout<<"nivel: "<<nivel<<endl;
            cout<<"transparencia: "<<transparencia<<endl;
            cout<<"faltante: "<<faltante<<endl;
            cout<<"turbidez: "<<turbidez<<endl;
            cout<<"deficiente: "<<deficiente<<endl;
            cout<<"impura: "<<impura<<endl;
            cout<<"state: "<<state<<endl;
            cout<<"next: "<<next<<endl<<endl;
        }
        
        void readBotella(ifstream & stream) {
            stream.getline(this->id, 6);
            stream.getline(this->nivel, 3);
            stream.getline(this->transparencia, 4);
            stream.getline(this->faltante, 2);
            stream.getline(this->turbidez, 2);
            stream.getline(this->deficiente, 1);
            stream.getline(this->impura, 2);
        }

};

ifstream &operator>> (ifstream & stream, Botella & record) {
    string uwu; //temp
    getline(stream,uwu);
    
    return stream;
}