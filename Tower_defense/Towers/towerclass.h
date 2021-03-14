#ifndef TOWERCLASS_H
#define TOWERCLASS_H
#include <iostream>
#include <vector>
#include <array>
#include "characters.h"
#include "create_db.h"
#include "insert_db.h"
#include "select_db.h"
#include "update_db.h"
using namespace std;

class tower
{
protected:
    std::array<int,2> position;
    int towernumber;
    
    
public:
    static int towercounter;
    tower(std::array<int,2> _position){
        Character player({1,2});//use this as defenders are based on the players stats
        position=_position;
        towercounter+=1;
        towernumber=towercounter;
        if(towercounter==1){
            create_db();
        }   
        for(int i=1;i<6;i++)
        {//need to get player max health get health only gets current
            insert_db(towernumber,i,player.get_health(),player.get_health(),position[0],position[1],false);
        }    
    }
    
    std::array<int,2> get_position(){
        return position;
    }
    
    void show_db(){
        select_db s;
        s.showall();
    }
    
    void game_tick(){//updates shit, to be ran every time screen updates(i think)
        select_db s;
        int defendernumber;
        int towernumber;
        std::array<int,2> coords;
        std::vector<int> defalive=s.get_alive();
        std::vector<int> Xcoord=s.get_Xcoord();
        std::vector<int> Ycoord=s.get_Ycoord();
        for(int i=0;i<defalive.size();i++){
            if(defalive[i]==1){
                  defendernumber=(i%5)+1;
                  towernumber=(i/5)+1;
                  coords[0]=Xcoord[i];
                  coords[1]=Ycoord[i];
                  walk(coords,defendernumber);
                  
            }
        }
    }
    
    std::array<int,2> walk(std::array<int,2> pos,int defendernumber){
        bool enemy = false;
        int xchange=1;
        int ychange=0;
        update_db u;
        if(true){//check surrounding tiles
            enemy=true;
            xchange=1;
            ychange=0;
        }
        if(enemy){//check if next tile has enemy
            fight(defendernumber);
        }else{//walk
            u.change_pos(towernumber,defendernumber,xchange,ychange);
        }
    }
    
    void fight(int defendernumber){
        update_db u;
        u.changehealth(towernumber,defendernumber,-1);
        //when dead remove from map
    }
    
    bool spawndefender(){
        select_db s;
        for(int i=1;i<6;i++){
            if(s.if_alive(towernumber,i)==false){
                update_db u;
                u.makealive(towernumber,i);
                return true;
            }
        }
        return false;
    }
};
int tower::towercounter = 0;
#endif
