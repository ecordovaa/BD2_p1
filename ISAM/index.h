#ifndef BD2_P1_INDEX_H
#define BD2_P1_INDEX_H

class Index {
    int rank;
    int address;

    Profile getProfileByAddress();
};

Profile Index::getProfileByAddress() {
    //link address with the record that holds that address
    return Profile();
}

#endif //BD2_P1_INDEX_H