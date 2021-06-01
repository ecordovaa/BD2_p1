#ifndef BD2_P1_INDEX_H
#define BD2_P1_INDEX_H

class BillioIndex {
    char id[5];
    Billio* address;

    BillioIndex(){}

    bool createIndex(Billio billionary) {
        id = billionary.id;
        address = *billionary;
    }

    //Utility
    bool operator==(const BillioIndex &billioIndex) const {
        return id == billioIndex.id &&
               address == *billioIndex;     
    }

    bool operator!=(const BillioIndex &billioIndex) const {
        return !(billioIndex == *this);
    }

    void toString(){
        cout<<"id: "<<this->getId()<<endl;
        cout<<"address: "<<this->
    }

    //Casting
    int getId() {
        int temp;
        sscanf(this->id, "%d", &temp);
        return temp;
    }

    float getBillions() {
        float temp;
        sscanf(this->billions, "%f", &temp);
        return temp;
    }

    void setId(int i) {
        memset(this->id, 0, 5);
        snprintf(this->id, sizeof(this->id), "%d", i);
        std::replace(begin(this->id), end(this->id)-1, '\0', ' ');
    }

    void setAddress(Billio billionary){
        address = *billionary;
    }
}

#endif //BD2_P1_INDEX_H