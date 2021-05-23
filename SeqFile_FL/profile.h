#ifndef BD2_P1_PROFILE_H
#define BD2_P1_PROFILE_H
#include "../lib.h"

class Profile {
private:
    //Data
    char name [20] {};
    char country [18] {};
    int age {};
    char dob [10] {};
    char nickname [20] {};
    int PDCRank {}; //key
    char tourCard [6] {};
    char careerEarnings [15] {};
    int next {};
    int nextDel {};

public:
    int getNext() const {
        return next;
    }

    void setNext(int n) {
        next = n;
    }

    int getNextDel() const {
        return nextDel;
    }

    void setNextDel(int n) {
        nextDel = n;
    }

    //Utility methods
    void showProfileInfo(){
        cout<<"\nNombre: "<<name;
        cout<<"\nPais: "<<country:
        cout<<"\nEdad: "<<age;
        cout<<"\nFecha de Nacimiento: "<<dob;
        cout<<"\nNickname: "<<nickname;
        cout<<"\nPDC Ranking: "<<PDCRank;
        cout<<"\nTour Card: "<<tourCard;
        cout<<"\nGanancia: "<<careerEarnings << endl;
    }

    bool operator==(const Profile &profile) const {
        return name == profile.name &&
               country == profile.country &&
               age == profile.age &&
               dob == profile.dob &&
               nickname == profile.nickname &&
               PDCRank == profile.PDCRank &&
               tourCard == profile.tourCard &&
               careerEarnings == profile.careerEarnings &&
               next == profile.next &&
               nextDel == profile.nextDel;
    }

    bool operator!=(const Profile &profile) const {
        return !(profile == *this);
    }
};

#endif //BD2_P1_PROFILE_H