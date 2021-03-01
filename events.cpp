#include <iostream>//-------------------------------------this is a placeholder until we I know how to implement the random events------------------
#include "characters.h"
using namespace std;

int stat1(Character player){
    cout << "you have found a suspicous mushroom growing " << endl;
    cout << "you eat the mushroom (you have increased strength)(doing health for now) " << endl;
    player.heal(2);
    cout << player.get_health() << endl;
    cout << "do drugs kids" << endl;
    return 0;
}
int stat2(Character player){
    cout << "you fell into stinging nettles" << endl;
    cout << "you have recieved damage" << endl;
    player.directReduceHealth(1);
    cout << player.get_health() << endl;
    return 0;
}
int resource1(Character player){
    cout << "you have encountered a lonely orphan" << endl;
    cout << "you have kidnapped a lonely orphan" << endl;
    cout << "resource increase" << endl;
    return 0;
}
int resource2(Character player){
    cout << "fucking monkey steals some food" << endl;
    cout << "resource decrease" << endl;
    return 0;
}
int combat1(Character player){
    cout << "hostile mob appeared" << endl;
    cout << "fight the hostile mob" << endl;
    engageCombat(Player &User, Alien &Foe);
    return 0;
}
int combat2(Character player){
    cout << "very raw beef appeared" << endl;
    cout << "fight the cow" << endl;
    engageCombat(Player &User, Alien &Foe);
    return 0;
}
