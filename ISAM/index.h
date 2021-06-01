#ifndef BD2_P1_INDEX_H
#define BD2_P1_INDEX_H
#include "billionaries.h"

class BillioIndex {
public:
    char billions [5];
    int pos {};
    BillioIndex(){};

    bool operator==(const BillioIndex &billioIndex) const 
    {
        return billions == billioIndex.billions && pos == billioIndex.pos;     
    }

    bool operator!=(const BillioIndex &billioIndex) const 
    {
        return !(billioIndex == *this);
    }

    bool BillioIndex::readBillioIndex(ifstream& stream) 
    {
        string temp {};
        getline(stream, temp);
        if(temp.empty()) return false;
        strcpy(this->billions, (temp.substr(54,6)).c_str());
        pos = stream.tellg()/sizeof(Billio);
        return true;
    }

    void toString()
    {
        cout<<"billions: "<<getBillions()<<endl;
        cout<<"pos: "<<getPos()<<endl;
    }

    //Casting
    float BillioIndex::getBillions() 
    {
        float temp;
        sscanf(this->billions, "%f", &temp);
        return temp;
    }

    int BillioIndex::getPos() 
    {
        return this->pos;   
    }

    void BillioIndex::setBillions(float billions) 
    {
        memset(this->billions, 0, 5);
        snprintf(this->billions, sizeof(this->billions), "%d", billions);
        std::replace(begin(this->billions), end(this->billions)-1, '\0', ' ');  
    }

    void setPos(int regpos)
    {
        this->pos = regpos;
    }
};

#endif //BD2_P1_INDEX_H.