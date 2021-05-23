#ifndef BD2_P1_PLAYERS_H
#define BD2_P1_PLAYERS_H
#include "lib.h"
#include "index.h"
class DartPlayer {
private:
    int rank; //key
    char name [25];
    char country [18];
    char earnings [10];
    char address [3]; //linked by index. From R1 to R99
    int next;

public:
    //Utility methods
    void showPlayerInfo(){
        cout<<"\nRanking: "<<rank;
        cout<<"\nNombre: "<<name;
        cout<<"\nPais: "<<country;
        cout<<"\nGanancia: "<<earnings << endl;
    }

    bool operator==(const DartPlayer &dartPlayer) const {
        return rank == dartPlayer.rank &&
               name == dartPlayer.name &&
               country == dartPlayer.country &&
               earnings == dartPlayer.earnings &&
               address == dartPlayer.address;
    }

    bool operator!=(const DartPlayer &dartPlayer) const {
        return !(dartPlayer == *this);
    }
};

#endif //BD2_P1_PLAYERS_H