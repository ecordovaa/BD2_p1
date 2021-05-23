#ifndef BD2_P1_FL_SEQFILE_H
#define BD2_P1_FL_SEQFILE_H
#include "profile.h"

class SeqFile {
private:
    string filename {};
public:
    explicit SeqFile(string  file): filename(std::move(file)) {};
    Profile search(int key);
    vector<Profile> searchBetween (int left, int right);
    void add(Profile profile);
    void eliminate(Profile profile);
    void test();
};

Profile SeqFile::search(int key) {
    return Profile();
}

vector<Profile> SeqFile::searchBetween(int left, int right) {
    return vector<Profile>();
}

void SeqFile::add(Profile profile) {

}

void SeqFile::eliminate(Profile profile) {

}

void SeqFile::test() {

}

#endif //BD2_P1_FL_SEQFILE_H