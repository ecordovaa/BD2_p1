
#include "../lib.h"

//La base de datos guarda datos sobre mediciones de liquidos en botellas
class Botella {
    public:
    
        char id[7];   //max 2147483647  6-digits
        char nivel[4];    //3
        char transparencia[5]; //4
        char faltante[3]; //2
        char turbidez[3]; //2
        char deficiente [2]; //0 false 1 true
        char impura [2]; //1

        char state[7]; //0: no eliminado, -1: fin de la cadena; >0: pos logica del nextDel (Eliminados)
        //6
        char next[7]; //Lista de ordenamiento
        //6

/*
        int id;   //max 2147483647  6-digits
        int nivel;    //3
        float transparencia; //4
        int faltante; //2
        int turbidez; //2
        bool deficiente; //0 false 1 true
        bool impura; //1

        int state; //0: no eliminado, -1: fin de la cadena; >0: pos logica del nextDel (Eliminados)
        //6
        int next;*/

        Botella(){}
        Botella(char id[7], char nivel [4],char transparencia [5], 
        char faltante[3] , char turbidez[3] , char deficiente [2], 
        char impura [2], char state[7], char next[7])
        {
            strncpy(this->id, id, 7);
            strncpy(this->nivel, nivel, 4);
            strncpy(this->transparencia, transparencia, 5);
            strncpy(this->faltante, faltante, 3);
            strncpy(this->turbidez, turbidez, 3);
            strncpy(this->deficiente, deficiente, 2);
            strncpy(this->impura, impura, 2);
            strncpy(this->state, state, 7);
            strncpy(this->next, next, 7);
            std::replace(begin(this->id), end(this->id)-1, '\0', ' ');
            std::replace(begin(this->nivel), end(this->nivel)-1, '\0', ' ');
            std::replace(begin(this->transparencia), end(this->transparencia)-1, '\0', ' ');
            std::replace(begin(this->faltante), end(this->faltante)-1, '\0', ' ');
            std::replace(begin(this->turbidez), end(this->turbidez)-1, '\0', ' ');
            std::replace(begin(this->deficiente), end(this->deficiente)-1, '\0', ' ');
            std::replace(begin(this->impura), end(this->impura)-1, '\0', ' ');
            std::replace(begin(this->state), end(this->state)-1, '\0', ' ');
            std::replace(begin(this->next), end(this->next)-1, '\0', ' ');
        }


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
            cout<<"id: "<<this->getId()<<endl;
            cout<<"nivel: "<<this->getNivel()<<endl;
            cout<<"transparencia: "<<this->getTransparencia()<<endl;
            cout<<"faltante: "<<this->getFaltante()<<endl;
            cout<<"turbidez: "<<this->getTurbidez()<<endl;
            cout<<"deficiente: "<<this->getDeficiente()<<endl;
            cout<<"impura: "<<this->getImpura()<<endl;
            cout<<"state: "<<this->getState()<<endl;
            cout<<"next: "<<this->getNext()<<endl<<endl;
        }

        void toString2() {
            cout<<"id: "<<this->id<<endl;
            cout<<"nivel: "<<this->nivel<<endl;
            cout<<"transparencia: "<<this->transparencia<<endl;
            cout<<"faltante: "<<this->faltante<<endl;
            cout<<"turbidez: "<<this->turbidez<<endl;
            cout<<"deficiente: "<<this->deficiente<<endl;
            cout<<"impura: "<<this->impura<<endl;
            cout<<"state: "<<this->state<<endl;
            cout<<"next: "<<this->next<<endl<<endl;
        }
        
        bool readBotella(ifstream & stream) {
            string uwu2;
            getline(stream, uwu2);

            if(uwu2.empty()) return false;



            //cout<<uwu2<<endl;
            strcpy(this->id, (uwu2.substr(0,6)).c_str());
            strcpy(this->nivel, (uwu2.substr(6,3)).c_str());
            strcpy(this->transparencia, (uwu2.substr(9,4)).c_str());
            strcpy(this->faltante, (uwu2.substr(13,2)).c_str());
            strcpy(this->turbidez, (uwu2.substr(15,2)).c_str());
            strcpy(this->deficiente, (uwu2.substr(17,1)).c_str());
            strcpy(this->impura, (uwu2.substr(18,1)).c_str());
            strcpy(this->state, (uwu2.substr(19,6)).c_str());
            strcpy(this->next, (uwu2.substr(25,6)).c_str());
            return true;
        
        
        
        
        
        }



        int getId()
        {
            int temp;
            sscanf(this->id, "%d", &temp);
            return temp;
        }
        int getNivel()
        {
            int temp;
            sscanf(this->nivel, "%d", &temp);
            return temp;
        }
        int getTransparencia()
        {
            int temp;
            sscanf(this->transparencia, "%d", &temp);
            return temp;
        }
        int getFaltante()
        {
            int temp;
            sscanf(this->faltante, "%d", &temp);
            return temp;
        }
        int getTurbidez()
        {
            int temp;
            sscanf(this->turbidez, "%d", &temp);
            return temp;
        }
        int getDeficiente()
        {
            int temp;
            sscanf(this->deficiente, "%d", &temp);
            return temp;
        }
        int getImpura()
        {
            int temp;
            sscanf(this->turbidez, "%d", &temp);
            return temp;
        }
        int getState()
        {
            int temp;
            sscanf(this->state, "%d", &temp);
            return temp;
        }
        int getNext()
        {
            int temp;
            sscanf(this->next, "%d", &temp);
            return temp;
        }
};