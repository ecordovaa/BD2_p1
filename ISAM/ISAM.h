#ifndef BD2_P1_ISAM_H
#define BD2_P1_ISAM_H
#include "players.h"

class ISAM {
private:
    string filename {};
public:
    explicit ISAM(const string& file): filename(file) {};
    Profile search(int key);
    vector<Profile> searchBetween (int left, int right);
    void add(Profile profile);
    void eliminate(Profile profile);
    void test();
};

Profile ISAM::search(int key) {
    return Profile();
}

vector<Profile> ISAM::searchBetween(int left, int right) {
    return vector<Profile>();
}

void ISAM::add(Profile profile) {

}

void ISAM::eliminate(Profile profile) {

}

void ISAM::test() {

}

#endif //BD2_P1_ISAM_H
