#include <string>
#include <iostream>
#include "defenderclass.h"
#include "characters.h"
#include "towerclass.h"
using namespace std;


int towerfunction(){
    int i=0;
    bool spawn = true;
    time_t current;
    tower tower1({1,2});
    tower tower2({1,2});
    while(spawn){
        current=time(NULL);
        while(time(NULL)-current!=1){
          i=0;
        }
        spawn=tower1.spawndefender();
        cout<<"spawn"<<endl;
    }
    //tower1.walk({1,2},1);
    tower1.game_tick();
    tower1.show_db();
    return 0;
}
