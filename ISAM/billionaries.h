#include "../lib.h"

class Billio {
    public:
        char id[5];
        char nombre[51];   //max 2147483647  6-digits
        char billions[7];    //3
        char country[31]; //4
        char industry[31]; //2
        char state[5]; //0: no eliminado, -1: fin de la cadena; >0: pos logica del nextDel (Eliminados)

        Billio(){}
        
        Billio(string nombre, string billions,string country, 
        string industry){

            // this->setBillions(billions);

            strncpy(this->nombre, nombre.c_str(), 51); 
            strncpy(this->billions, billions.c_str(), 7);     
            strncpy(this->country, country.c_str(), 31);
            strncpy(this->industry, industry.c_str(), 31);

            std::replace(begin(this->nombre), end(this->nombre)-1, '\0', ' ');
            std::replace(begin(this->billions), end(this->billions)-1, '\0', ' ');
            std::replace(begin(this->country), end(this->country)-1, '\0', ' ');
            std::replace(begin(this->industry), end(this->industry)-1, '\0', ' ');

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
            cout<<"id: "<<this->getId()<<endl;
            cout<<"nombre: "<<this->getNombre()<<endl;
            cout<<"billions: "<<this->getBillions()<<endl;
            cout<<"country: "<<this->getCountry()<<endl;
            cout<<"industry: "<<this->getIndustry()<<endl;
            cout<<"state: "<<this->getState()<<endl;
        }

        //Read from file
        bool readBillio(ifstream & stream) {
            string temp;
            getline(stream, temp);
            if(temp.empty()) return false;
            strcpy(this->id, (temp.substr(0,4)).c_str());
            strcpy(this->nombre, (temp.substr(4,50)).c_str());
            strcpy(this->billions, (temp.substr(54,6)).c_str());
            strcpy(this->country, (temp.substr(60,30)).c_str());
            strcpy(this->industry, (temp.substr(90,30)).c_str());
            strcpy(this->state, (temp.substr(120,4)).c_str());
            return true;
        }

        bool readBillio(fstream & stream) {
            string temp;
            getline(stream, temp);
            if(temp.empty()) return false;
            strcpy(this->id, (temp.substr(0,4)).c_str());
            strcpy(this->nombre, (temp.substr(4,50)).c_str());
            strcpy(this->billions, (temp.substr(54,6)).c_str());
            strcpy(this->country, (temp.substr(60,30)).c_str());
            strcpy(this->industry, (temp.substr(90,30)).c_str());
            strcpy(this->state, (temp.substr(120,4)).c_str());
            return true;
        }


        void setId(int i)
        {
            memset(this->id, 0, 5);
            snprintf(this->id, sizeof(this->id), "%d", i);
            std::replace(begin(this->id), end(this->id)-1, '\0', ' ');
        }

        void setState(int i)
        {
            memset(this->state, 0, 5);
            snprintf(this->state, sizeof(this->state), "%d", i);
            std::replace(begin(this->state), end(this->state)-1, '\0', ' ');
        }

        //Casting
        int getId() {
            int temp;
            sscanf(this->id, "%d", &temp);
            return temp;
        }

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

};