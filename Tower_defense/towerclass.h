#ifndef TOWERCLASS_H
#define TOWERCLASS_H
#include <iostream>
#include <vector>
#include <array>
#include <cstdlib>
//#include "characters.h"
#include "create_db.h"
#include "insert_db.h"
#include "select_db.h"
#include "update_db.h"
#include "TowerDefense.h"
using namespace std;

class tower
{
protected:
    std::array<int, 2> position;
    int towernumber;
    bool defender_direction;//chooses which direction the defender takes


public:
    static int towercounter;
    tower(std::array<int, 2> _position) {
        defender_direction = true;
        //Character player({ 1,2 });//use this as defenders are based on the players stats
        position = _position;
        towercounter += 1;
        towernumber = towercounter;
        if (towercounter == 1) {
            create_db();
        }
        for (int i = 1; i < 6; i++)
        {//need to get player max health get health only gets current
            insert_db(towernumber, i,6,6,2, position[0], position[1], false);// player.get_health(), player.get_health(), player.get_attack(), position[0], position[1], false);
        }
    }

    std::array<int, 2> get_position() {
        return position;
    }

    void change_position(std::array<int, 2> pos) {
        position = pos;
    }

    void show_db() {
        select_db s;
        s.showall();
    }

    void upgrade_tower() {
        update_db u;
        u.upgrade(towernumber);



    }

    void game_tick(vector<vector<unsigned char>> maze) {//updates shit, to be ran every time screen updates(i think)
        select_db s;
        int defendernumber;
        int towernumber;
        spawndefender(maze);
        std::array<int, 2> coords;
        std::vector<int> defalive = s.get_alive();
        std::vector<int> Xcoord = s.get_Xcoord();
        std::vector<int> Ycoord = s.get_Ycoord();
        for (int i = 0; i < defalive.size(); i++) {
            if (defalive[i] == 1) {
                defendernumber = (i % 5) + 1;
                towernumber = (i / 5) + 1;
                coords[0] = Xcoord[i];
                coords[1] = Ycoord[i];
                walk(coords, defendernumber, maze);

            }
        }
    }

    void walk(std::array<int, 2> pos, int defendernumber, vector<vector<unsigned char>> maze) { //maze[WIDTH][HEIGHT]
        bool enemy = false;
        char enemy_type;
        bool can_move = true; //there is space to move
        std::array<int, 2> defpos; //defender position
        int xchange = 0;
        int ychange = 0;
        int looped = 0;//ensures the defender has had a chance to move
        update_db u;
        if (maze[pos[0]][pos[1] + 1] == 'X' || maze[pos[0]][pos[1] + 1] == 'Y' || maze[pos[0]][pos[1] + 1] == 'Z') {
            //cout << "enemy ^" << endl;
            enemy_type = maze[pos[0]][pos[1] + 1];
            enemy = true;
        }
        else if (maze[pos[0] + 1][pos[1]] == 'X' || maze[pos[0] + 1][pos[1]] == 'Y' || maze[pos[0] + 1][pos[1]] == 'Z') {
            //cout << "enemy >" << endl;
            enemy_type = maze[pos[0] + 1][pos[1]];
            enemy = true;
        }
        else if (maze[pos[0]][pos[1] - 1] == 'X' || maze[pos[0]][pos[1] - 1] == 'Y' || maze[pos[0]][pos[1] - 1] == 'Z') {
            //cout << "enemy V" << endl;
            enemy_type = maze[pos[0]][pos[1] - 1];
            enemy = true;
        }
        else if (maze[pos[0] - 1][pos[1]] == 'X' || maze[pos[0] - 1][pos[1]] == 'Y' || maze[pos[0] - 1][pos[1]] == 'Z') {
            //cout << "enemy <" << endl;
            enemy_type = maze[pos[0] - 1][pos[1]];
            enemy = true;
        }
        if (enemy == false) {
            looped = 0;
            while (looped < 2) {
                if (defender_direction == true) {
                    if (maze[pos[0]][pos[1] + 1] == ' ' && abs((position[1] + 1) - pos[1]) <= 3) {
                        //cout << "wspace okay ^" << endl;
                        defpos = { pos[0],pos[1] + 1 };
                        ychange = 1;
                        looped += 2;
                    }
                    else if (maze[pos[0] + 1][pos[1]] == ' ' && abs((position[0] + 1) - pos[0]) <= 3) {
                        //cout << "wspace okay >" << endl;
                        defpos = { pos[0] + 1,pos[1] };
                        xchange = 1;
                        looped += 2;
                    }
                    else {
                        defender_direction = false;
                        looped += 1;
                    }
                }if (defender_direction == false && looped < 2) {}
                if (maze[pos[0]][pos[1] - 1] == ' ' && abs((position[1] - 1) - pos[1]) <= 3) {
                    //cout << "wspace okay V" << endl;
                    defpos = { pos[0],pos[1] - 1 };
                    ychange = -1;
                    looped += 2;
                }
                else if (maze[pos[0] - 1][pos[1]] == ' ' && abs((position[0] - 1) - pos[0]) <= 3) {
                    //cout << "wspace okay <" << endl;
                    defpos = { pos[0] - 1,pos[1] };
                    xchange = -1;
                    looped += 2;
                }
                else {
                    defender_direction = true;
                    looped += 1;
                }
            }
            if (xchange == 0 && ychange == 0) {
                can_move = false;
            }
        }
        if (enemy) {
            fight(defendernumber, pos, enemy_type);
        }
        else if (can_move) {//walk
            mazechange(pos, defpos, '^');
            u.change_pos(towernumber, defendernumber, xchange, ychange);
        }
    }

    void fight(int defendernumber, std::array<int, 2> pos, char enemy_type) {
        if (enemy_type == 'X') {
            enemysoldierhit();
        }
        else if (enemy_type == 'Y') {
            enemyTankhit();
        }
        else if (enemy_type == 'Z') {
            enemyCarryhit();
        }
        else {
            cout << "unknown enemy type" << endl;
        }
        update_db u;
        u.changehealth(towernumber, defendernumber, -1, pos);
    }



    bool spawndefender(vector<vector<unsigned char>> maze) {
        std::array<int, 2> defpos;
        bool spawnable = true;
        if (maze[position[0]][position[1] + 1] == ' ') {
            //cout << "dspace okay ^" << endl;
            defpos = { position[0],position[1] + 1 };
        }
        else if (maze[position[0] + 1][position[1]] == ' ') {
            //cout << "dspace okay >" << endl;
            defpos = { position[0] + 1,position[1] };
        }
        else if (maze[position[0]][position[1] - 1] == ' ') {
            //cout << "dspace okay V" << endl;
            defpos = { position[0],position[1] - 1 };
        }
        else if (maze[position[0] - 1][position[1]] == ' ') {
            //cout << "dspace okay <" << endl;
            defpos = { position[0] - 1,position[1] };
        }
        else {
            spawnable = false;
        }
        select_db s;
        if (spawnable == true) {
            for (int i = 1; i < 6; i++) {
                if (s.if_alive(towernumber, i) == false) {
                    update_db u;
                    u.makealive(towernumber, i, defpos);//position
                    return true;
                }
            }
        }
        return false;
    }
};
int tower::towercounter = 0;
#endif
