
#include "../lib.h"

class Billio {
    public:
        char nombre[51];   //max 2147483647  6-digits
        char billions[7];    //3
        char country[31]; //4
        char industry[31]; //2
        char state[5]; //0: no eliminado, -1: fin de la cadena; >0: pos logica del nextDel (Eliminados)
        char next[5]; //Lista de ordenamiento

        Billio(){}
        
        Billio(char nombre[51], char billions [7],char country [31], 
        char industry[31], char state[5], char next[5])
        {
            strncpy(this->nombre, nombre, 51);
            strncpy(this->billions, billions, 7);
            strncpy(this->country, country, 31);
            strncpy(this->industry, industry, 31);
            strncpy(this->state, state, 5);
            strncpy(this->next, next, 5);

            std::replace(begin(this->nombre), end(this->nombre)-1, '\0', ' ');
            std::replace(begin(this->billions), end(this->billions)-1, '\0', ' ');
            std::replace(begin(this->country), end(this->country)-1, '\0', ' ');
            std::replace(begin(this->industry), end(this->industry)-1, '\0', ' ');
            std::replace(begin(this->state), end(this->state)-1, '\0', ' ');
            std::replace(begin(this->next), end(this->next)-1, '\0', ' ');
        }

        //Utility

        bool operator==(const Billio &billio) const {
            return nombre == billio.nombre &&
                billions == billio.billions &&
                country == billio.country &&
                industry == billio.industry;      
        }

        bool operator!=(const Billio &billio) const {
            return !(billio == *this);
        }

        void toString() {
            cout<<"nombre: "<<this->getNombre()<<endl;
            cout<<"billions: "<<this->getBillions()<<endl;
            cout<<"country: "<<this->getCountry()<<endl;
            cout<<"industry: "<<this->getIndustry()<<endl;
            cout<<"state: "<<this->getState()<<endl;
            cout<<"next: "<<this->getNext()<<endl<<endl;
        }
        void toString2() {
            cout<<"nombre: "<<this->nombre<<endl;
            cout<<"billions: "<<this->billions<<endl;
            cout<<"country: "<<this->country<<endl;
            cout<<"industry: "<<this->industry<<endl;
            cout<<"state: "<<this->state<<endl;
            cout<<"next: "<<this->next<<endl<<endl;
        }

        //Read from file

        bool readBillio(ifstream & stream) {
            string temp;
            getline(stream, temp);
            if(temp.empty()) return false;
            strcpy(this->nombre, (temp.substr(0,50)).c_str());
            strcpy(this->billions, (temp.substr(50,6)).c_str());
            strcpy(this->country, (temp.substr(56,30)).c_str());
            strcpy(this->industry, (temp.substr(86,30)).c_str());
            strcpy(this->state, (temp.substr(116,4)).c_str());
            strcpy(this->next, (temp.substr(120,4)).c_str());
            return true;

        }

        //Casting

        string getNombre() {
            string temp = nombre;
            return temp;
        }

        float getBillions() {
            float temp;
            sscanf(this->billions, "%f", &temp);
            return temp;
        }

        string getCountry() {
            string temp = country;
            return temp;
        }

        string getIndustry() {
            string temp = industry;
            return temp;
        }

        int getState() {
            int temp;
            sscanf(this->state, "%d", &temp);
            return temp;
        }

        int getNext() {
            int temp;
            sscanf(this->next, "%d", &temp);
            return temp;
        }
};