#ifndef TowerDefense_h
#define TowerDefense_h
#include <iostream>
#include <conio.h>
#include <fstream>
#include <string>
#include <array>
#include <vector>
#include <cstring> 
#include <tchar.h>
#include <stdlib.h>   
#include <chrono> 
#include <thread>
#include "towerclass.h"
using namespace std;



struct base
{
    int positionX;
    int positionY;
    char main_tower_symbol;
    int hp;
}main_tower;

struct enemy1
{
    int positionX;
    int positionY;
    char enemy_soldier_symbol;
    int enemy_hp;
}enemy_soldier;


struct enemy2
{
    int positionX;
    int positionY;
    char enemy_tank_symbol;
    int enemy_hp;
}enemy_Tank;


struct enemy3
{
    int positionX;
    int positionY;
    char enemy_carry_symbol;
    int enemy_hp;
}enemy_Carry;

struct towers
{
    int positionX;
    int positionY;
    char tower1_symbol;
    int enemy_hp;
}tower1, tower2, tower3, tower4, tower5, tower6, tower7, tower8, tower9, tower10;

void tower_hit()// function for when the main_tower hits an enemy
{
    main_tower.hp--;
}

void enemysoldierhit() {
    enemy_soldier.enemy_hp--;
}
void enemyTankhit() {
    enemy_Tank.enemy_hp--;
}
void enemyCarryhit() {
    enemy_Carry.enemy_hp--;
}

void pathing() {
    int tankpathX[10] = { 2 };
    int tankpathY[10] = { 14 };

    for (int i = 0; i < 10; ++i) {
        enemy_Tank.positionX = tankpathX[i];
        enemy_Tank.positionY = tankpathY[i];
    }

}

int hex_decimal(char in) {
    switch (in) {
    case '1':
        return 2;
        break;
    case '2':
        return 3;
        break;
    case '3':
        return 4;
        break;
    case '4':
        return 5;
        break;
    case '5':
        return 6;
        break;
    case '6':
        return 7;
        break;
    case '7':
        return 8;
        break;
    case '8':
        return 9;
        break;
    case '9':
        return 10;
        break;
    case 'a':
        return 11;
        break;
    case 'b':
        return 12;
        break;
    case 'c':
        return 13;
        break;
    case 'd':
        return 14;
        break;
    case 'e':
        return 15;
        break;
    case 'f':
        return 16;
        break;
    case 'g':
        return 17;
        break;
    case 'h':
        return 18;
        break;
    case 'i':
        return 19;
        break;

    }
}


std::vector<int> buy_tower(std::vector<char> tower_coords,int numtowers) {
    int money = 2000;//to be added
    int x = hex_decimal(tower_coords[0]);
    
    int y = hex_decimal(tower_coords[1]);
    int numberoftowers= numtowers;

    if (money < 1000) {
        cout << "your broke" << endl;
        return {0,0};
    }
    else {
        money -= 1000;
    }


    //cout << "----------------------------" << 1;
    if (numberoftowers == 0) {
        tower1 = { x,y,'s',10 };
        //cout << "----------------------------" << 2;
        return { 1,0 }; 
    }
    else if (numberoftowers == 1) {
        tower2 = { x,y,'s',10 };
        //cout << "----------------------------" << 3;
        return { 1,1 };
        
    }
    else if (numberoftowers == 2) {
        tower3 = { x,y,'s',10 };
        //cout << "----------------------------" << 4;
        return { 1,2 };
    }
    else if (numberoftowers == 3) {
        tower4 = { x,y,'s',10 };
        return { 1,3 };
    }
    else if (numberoftowers == 4) {
        tower5 = { x,y,'s',10 };
        return { 1,4 };
    }
    else if (numberoftowers == 5) {
        tower6 = { x,y,'s',10 };
        return { 1,5 };
    }
    else if (numberoftowers == 6) {
        tower7 = { x,y,'s',10 };
        return { 1,6 };
    }
    else if (numberoftowers == 7) {
        tower8 = { x,y,'s',10 };
        return { 1,7 };
    }
    else if (numberoftowers == 8) {
        tower9 = { x,y,'s',10 };
        return { 1,8 };
    }
    else if (numberoftowers == 9) {
        tower10 = { x,y,'s',10 };

        return { 1,9 };
    }else {
        cout << "cant place more towers" << endl;
        return { 0,0 };
    }
   
    return { 0,0 };

}



class maze
{
private:
    static vector<vector<unsigned char>> maze_s;

public:
    friend int main();
    friend void initialiser();
    friend void mazechange(std::array<int, 2> oldpos, std::array<int, 2> newpos, char character);
    friend void remove(std::array<int, 2> pos);
    //friend bool buy_tower(std::vector<char> tower_coords);

    void move_piece(std::array<int, 2> oldpos, std::array<int, 2> newpos) {
        maze_s[newpos[0]][newpos[1]] = maze_s[oldpos[0]][oldpos[1]];
        maze_s[oldpos[0]][oldpos[1]] = ' ';
    }

    void remove_piece(std::array<int, 2> pos) {
        maze_s[pos[0]][pos[1]] = ' ';
    }
    bool movement() {
        bool update = true;
        if (main_tower.hp == 0)// when the maintower rund out of hp the ganmes stops and print out you have lost the game.
        {
            cout << " you have lost the game \n";
            return false;//false means dead
        }

        while (maze_s[enemy_Tank.positionX][enemy_Tank.positionY] == maze_s[main_tower.positionX][main_tower.positionY])
        {
            if (main_tower.hp > 0) {
                tower_hit();
            }
            if (main_tower.hp == 0) {
                cout << " you have lost the game \n";
                break;
            }
            if (enemy_Tank.enemy_hp > 0) {
                enemyTankhit();
            }
            if (enemy_Tank.enemy_hp <= 0)
            {
                maze_s[enemy_Tank.positionX][enemy_Tank.positionY] = 'O';
                enemy_Tank = { 14 , 1, 'Y',8 };
                maze_s[enemy_Tank.positionX][enemy_Tank.positionY] = 'Y';

            }
        }
        if (enemy_Tank.enemy_hp <= 0)
        {
            maze_s[enemy_Tank.positionX][enemy_Tank.positionY] = ' ';
            enemy_Tank = { 14 , 1, 'Y',8 };
            maze_s[enemy_Tank.positionX][enemy_Tank.positionY] = 'Y';

        }

        while (maze_s[enemy_soldier.positionX][enemy_soldier.positionY] == maze_s[main_tower.positionX][main_tower.positionY])
        {
            if (main_tower.hp > 0) {
                tower_hit();
            }
            if (main_tower.hp == 0) {
                cout << " you have lost the game \n";
                break;
            }
            if (enemy_soldier.enemy_hp > 0) {
                enemysoldierhit();
            }
            if (enemy_soldier.enemy_hp <= 0)
            {
                maze_s[enemy_soldier.positionX][enemy_soldier.positionY] = 'O';
                enemy_soldier = { 18, 4, 'X',5 };
                maze_s[enemy_soldier.positionX][enemy_soldier.positionY] = 'X';

            }
        }
        if (enemy_soldier.enemy_hp <= 0)
        {
            maze_s[enemy_soldier.positionX][enemy_soldier.positionY] = ' ';
            enemy_soldier = { 18, 4, 'X',5 };
            maze_s[enemy_soldier.positionX][enemy_soldier.positionY] = 'X';

        }

        while (maze_s[enemy_Carry.positionX][enemy_Carry.positionY] == maze_s[main_tower.positionX][main_tower.positionY])
        {
            if (main_tower.hp > 0) {
                tower_hit();
            }
            if (main_tower.hp == 0) {
                cout << " you have lost the game \n";
                break;
            }
            if (enemy_Carry.enemy_hp > 0) {
                enemyCarryhit();
            }
            if (enemy_Carry.enemy_hp <= 0)
            {

                maze_s[enemy_Carry.positionX][enemy_Carry.positionY] = 'O';
                enemy_Carry = { 16, 18, 'Z',3 };
                maze_s[enemy_Carry.positionX][enemy_Carry.positionY] = 'Z';
            }
        }
        if (enemy_Carry.enemy_hp <= 0)
        {

            maze_s[enemy_Carry.positionX][enemy_Carry.positionY] = ' ';
            enemy_Carry = { 16, 18, 'Z',3 };
            maze_s[enemy_Carry.positionX][enemy_Carry.positionY] = 'Z';
        }
        if (maze_s[enemy_Tank.positionX - 1][enemy_Tank.positionY] != '^' && maze_s[enemy_Tank.positionX][enemy_Tank.positionY - 1] != '^') {
        if (enemy_Tank.positionX < 11) {
            if (maze_s[enemy_Tank.positionX - 1][enemy_Tank.positionY] == ' ' || maze_s[enemy_Tank.positionX - 1][enemy_Tank.positionY] == 'O')
            {
                update = true;
                maze_s[enemy_Tank.positionX][enemy_Tank.positionY] = ' ';
                enemy_Tank.positionX--;
                maze_s[enemy_Tank.positionX][enemy_Tank.positionY] = 'Y';
            }
            if (maze_s[enemy_Tank.positionX][enemy_Tank.positionY - 1] == ' ' || maze_s[enemy_Tank.positionX][enemy_Tank.positionY - 1] == 'O')
            {
                update = true;
                maze_s[enemy_Tank.positionX][enemy_Tank.positionY] = ' ';
                enemy_Tank.positionY--;
                maze_s[enemy_Tank.positionX][enemy_Tank.positionY] = 'Y';

            }
        }
        else {
            if (maze_s[enemy_Tank.positionX - 1][enemy_Tank.positionY] == ' '|| maze_s[enemy_Tank.positionX - 1][enemy_Tank.positionY] == 'O')
            {
                update = true;
                maze_s[enemy_Tank.positionX][enemy_Tank.positionY] = ' ';
                enemy_Tank.positionX--;
                maze_s[enemy_Tank.positionX][enemy_Tank.positionY] = 'Y';
            }

            if (maze_s[enemy_Tank.positionX][enemy_Tank.positionY + 1] == ' '|| maze_s[enemy_Tank.positionX][enemy_Tank.positionY + 1] == 'O')
            {
                update = true;
                maze_s[enemy_Tank.positionX][enemy_Tank.positionY] = ' ';
                enemy_Tank.positionY++;
                maze_s[enemy_Tank.positionX][enemy_Tank.positionY] = 'Y';

            }
        }
        
        }
        if (maze_s[enemy_Tank.positionX - 1][enemy_Tank.positionY] == '*' && maze_s[enemy_Tank.positionX + 1][enemy_Tank.positionY] == '*' && maze_s[enemy_Tank.positionX][enemy_Tank.positionY - 1] == '*' && maze_s[enemy_Tank.positionX][enemy_Tank.positionY] != maze_s[main_tower.positionX][main_tower.positionY])
        {
            update = true;
            maze_s[enemy_Tank.positionX][enemy_Tank.positionY] = 'O';
            enemy_Tank.positionX = enemy_Tank.positionX + 10;
            maze_s[enemy_Tank.positionX][enemy_Tank.positionY] = 'Y';
        }
        if (maze_s[enemy_Carry.positionX - 1][enemy_Carry.positionY] != '^' && maze_s[enemy_Carry.positionX][enemy_Carry.positionY - 1] != '^') {
            if (maze_s[enemy_Carry.positionX - 1][enemy_Carry.positionY] == ' '|| maze_s[enemy_Carry.positionX - 1][enemy_Carry.positionY] == 'O')
            {
                update = true;
                maze_s[enemy_Carry.positionX][enemy_Carry.positionY] = ' ';
                enemy_Carry.positionX--;
                maze_s[enemy_Carry.positionX][enemy_Carry.positionY] = 'Z';
            }

            if (maze_s[enemy_Carry.positionX][enemy_Carry.positionY - 1] == ' '|| maze_s[enemy_Carry.positionX][enemy_Carry.positionY - 1] == 'O')
            {
                update = true;
                maze_s[enemy_Carry.positionX][enemy_Carry.positionY] = ' ';
                enemy_Carry.positionY--;
                maze_s[enemy_Carry.positionX][enemy_Carry.positionY] = 'Z';
            }
        }
        if (maze_s[enemy_soldier.positionX - 1][enemy_soldier.positionY] != '^' && maze_s[enemy_soldier.positionX][enemy_soldier.positionY - 1] != '^') {
            if (enemy_soldier.positionX < 15) {
                if (maze_s[enemy_soldier.positionX - 1][enemy_soldier.positionY] == ' '|| maze_s[enemy_soldier.positionX - 1][enemy_soldier.positionY] == 'O')
                {
                    update = true;
                    maze_s[enemy_soldier.positionX][enemy_soldier.positionY] = ' ';
                    enemy_soldier.positionX--;
                    maze_s[enemy_soldier.positionX][enemy_soldier.positionY] = 'X';
                }

                if (maze_s[enemy_soldier.positionX][enemy_soldier.positionY - 1] == ' '|| maze_s[enemy_soldier.positionX][enemy_soldier.positionY - 1] == 'O')
                {
                    update = true;
                    maze_s[enemy_soldier.positionX][enemy_soldier.positionY] = ' ';
                    enemy_soldier.positionY--;
                    maze_s[enemy_soldier.positionX][enemy_soldier.positionY] = 'X';

                }
            }
            else {
                if (maze_s[enemy_soldier.positionX - 1][enemy_soldier.positionY] == ' '|| maze_s[enemy_soldier.positionX - 1][enemy_soldier.positionY] == 'O')
                {
                    update = true;
                    maze_s[enemy_soldier.positionX][enemy_soldier.positionY] = ' ';
                    enemy_soldier.positionX--;
                    maze_s[enemy_soldier.positionX][enemy_soldier.positionY] = 'X';
                }

                if (maze_s[enemy_soldier.positionX][enemy_soldier.positionY + 1] == ' '|| maze_s[enemy_soldier.positionX][enemy_soldier.positionY + 1] == 'O')
                {
                    update = true;
                    maze_s[enemy_soldier.positionX][enemy_soldier.positionY] = ' ';
                    enemy_soldier.positionY++;
                    maze_s[enemy_soldier.positionX][enemy_soldier.positionY] = 'X';

                }
            }
        }
        if (maze_s[enemy_soldier.positionX - 1][enemy_soldier.positionY] == '*' && maze_s[enemy_soldier.positionX + 1][enemy_soldier.positionY] == '*' && maze_s[enemy_soldier.positionX][enemy_soldier.positionY - 1] == '*' && maze_s[enemy_soldier.positionX][enemy_soldier.positionY] != maze_s[main_tower.positionX][main_tower.positionY])
        {
            update = true;
            maze_s[enemy_soldier.positionX][enemy_soldier.positionY] = 'O';
            enemy_soldier.positionX = enemy_soldier.positionX + 15;
            maze_s[enemy_soldier.positionX][enemy_soldier.positionY] = 'X';
        }
        


    }

    void show_maze() {
        int currency = 3000;
        int animation_speed = 1;
        int rows = 19;
        int in = 0;
        int numberoftowers = 0;
        bool alive = true;
        bool buying_tower=false;
        char placeholder;
        std::vector<char> tower_coords;
        std::vector<int> ret;
        std::vector<int> coords;
        tower towerc1({ 0,0 });
        tower towerc2({ 0,0 });
        tower towerc3({ 0,0 });
        tower towerc4({ 0,0 });
        tower towerc5({ 0,0 });
        tower towerc6({ 0,0 });
        tower towerc7({ 0,0 });
        tower towerc8({ 0,0 });
        tower towerc9({ 0,0 });
        tower towerc10({ 0,0 });
        while (in != 13) {//13 is enter key
            //cout << alive;
            cout << "currency = "<<currency << endl;
            cout << "\n 1 - Buy Towers\n 2 - Upgrade Tower\n 3 - Sell Towers " << endl;

            for (int i = 0; i < rows; i++) {
                cout << endl;
                for (int ii = 0; ii < 19 ; ii++) {
                    cout << maze_s[i][ii];
                }
            }
            cout << endl << endl << "    health: " << main_tower.hp << endl << "____________________\n \n";
            alive = movement();
            if (buying_tower) {
                if (tower_coords.size() == 0) {
                    cout << "X coordinate for tower : " << endl;
                }
                else if (tower_coords.size() == 1) {
                    cout << "X coordinate for tower : " << tower_coords[0] << endl;
                    cout << "Y coordinate for tower : " << endl;
                }
            }
 
            //cout << alive;
            if (_kbhit())
            {
                char ch =_getch();
                if (buying_tower) {

                    
                    tower_coords.push_back(ch);
                    if (tower_coords.size() == 2) {
                        placeholder = tower_coords[0];
                        tower_coords[0] = tower_coords[1];
                        tower_coords[1] = placeholder;
                        buying_tower = false;
                        //ch = 'r';
                        numberoftowers += 1;
                        currency -= 1000;
                        if (buy_tower(tower_coords, numberoftowers)[0]==1) {
                            ret=buy_tower(tower_coords, numberoftowers);
                            coords = { hex_decimal(tower_coords[0]) - 1,hex_decimal(tower_coords[1]) - 1 };
                            if (ret[1] == 1) {
                                towerc1.change_position({ coords[0],coords[1] });
                                maze_s[coords[0]][coords[1]] = 's';
                            }else if (ret[1] == 2){
                                towerc2.change_position({ coords[0],coords[1] });
                                maze_s[coords[0]][coords[1]] = 's';
                            }else if (ret[1] == 3) {
                                towerc3.change_position({ coords[0],coords[1] });
                                maze_s[coords[0]][coords[1]] = 's';
                            }
                            else if (ret[1] == 4) {
                                towerc4.change_position({ coords[0],coords[1] });
                                maze_s[coords[0]][coords[1]] = 's';
                            }
                            else if (ret[1] == 5) {
                                towerc5.change_position({ coords[0],coords[1] });
                                maze_s[coords[0]][coords[1]] = 's';
                            }
                            else if (ret[1] == 6) {
                                towerc6.change_position({ coords[0],coords[1] });
                                maze_s[tower6.positionX][tower6.positionY] = tower6.tower1_symbol;
                            }
                            else if (ret[1] == 7) {
                                towerc7.change_position({ coords[0],coords[1] });
                                maze_s[tower7.positionX][tower7.positionY] = tower7.tower1_symbol;
                            }
                            else if (ret[1] == 8) {
                                towerc8.change_position({ coords[0],coords[1] });
                                maze_s[tower8.positionX][tower8.positionY] = tower8.tower1_symbol;
                            }
                            else if (ret[1] == 9) {
                                towerc9.change_position({ coords[0],coords[1] });
                                maze_s[tower9.positionX][tower9.positionY] = tower9.tower1_symbol;
                            }
                            else if (ret[1] == 10) {
                                towerc10.change_position({ coords[0],coords[1] });
                                maze_s[tower10.positionX][tower10.positionY] = tower10.tower1_symbol;
                            }


                        }

                        tower_coords.pop_back();
                        tower_coords.pop_back();
                    }
                    
                }
                else {
                    switch (ch)
                    {
                    case '1':
                        buying_tower = true;
                        break;
                    }
                }
            }
            
            switch(numberoftowers) {
            case 0:
                break;
            case 1:
                towerc1.game_tick(maze_s);
                break;
            case 2:
                towerc2.game_tick(maze_s);
                break;
            case 3:
                towerc3.game_tick(maze_s);
                break;
            case 4:
                towerc4.game_tick(maze_s);
                break;
            case 5:
                towerc5.game_tick(maze_s);
                break;
            case 6:
                towerc6.game_tick(maze_s);
                break;
            case 7:
                towerc7.game_tick(maze_s);
                break;
            case 8:
                towerc8.game_tick(maze_s);
                break;
            case 9:
                towerc9.game_tick(maze_s);
                break;
            case 10:
                towerc10.game_tick(maze_s);
                break;

            }



            std::this_thread::sleep_for(std::chrono::milliseconds{ 100 * (10 - animation_speed) });
            cout << endl;
            system("CLS");
        }
    }
};

vector<vector<unsigned char>> maze::maze_s;








std::array<int, 2> output(unsigned char fields[][19], int rows) {
    
    
    char letter = 'o';
    std::array<int, 2> cursor = { 0,2 };
    return cursor;
}

void initialiser() {

    maze e;
    e.maze_s = {
    {' ','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F','G','H','I'},
    {'1','*','*','*','*','*','*','*','*','*','*','*','*','*',' ','*','*','*','*'},
    {'2','*',' ','*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
    {'3','*',' ','*',' ',' ','*','*',' ','*','*','*','*',' ','*','*','*',' ','*'},
    {'4','*',' ','*',' ',' ','*',' ',' ',' ',' ','*','*',' ','*',' ','*','*','*'},
    {'5','*',' ','*',' ',' ',' ',' ','*','*',' ',' ','*','*','*',' ',' ','*','*'},
    {'6','*',' ','*',' ','*','*','*','*','*',' ','*',' ','*','*',' ','*',' ','*'},
    {'7','*',' ','*','*',' ',' ',' ','*','*','*','*',' ','*',' ',' ','*',' ','*'},
    {'8','*',' ',' ',' ',' ','*','*','*','*','*',' ',' ','*','*','*','*',' ','*'},
    {'9','*','*','*','*',' ','*','*','*','*','*','*',' ','*','*','*','*',' ','*'},
    {'A','*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*',' ',' ',' ',' ','*'},
    {'B','*',' ','*','*',' ','*',' ','*','*',' ','*','*','*','*',' ','*',' ','*'},
    {'C','*','*','*','*',' ','*',' ',' ',' ',' ','*','*','*','*','*',' ',' ','*'},
    {'D','*','*',' ',' ',' ',' ',' ',' ','*',' ',' ',' ',' ',' ',' ',' ','*','*'},
    {'E',' ',' ',' ','*','*',' ',' ','*','*','*',' ',' ','*',' ','*','*','*','*'},
    {'F','*','*','*','*','*','*','*','*','*','*','*',' ',' ',' ','*','*','*','*'},
    {'G','*',' ',' ',' ','*',' ',' ',' ',' ',' ',' ',' ','*',' ',' ',' ',' ',' '},
    {'H','*','*','*',' ',' ',' ','*','*','*','*','*',' ',' ',' ','*','*','*','*'},
    {'I','*','*','*',' ','*','*','*','*','*','*','*','*','*','*','*',' ','*','*'}
    };

    main_tower = { 2,2,'O',100 };
    enemy_soldier = { 18,4, 'X',5 };
    enemy_Tank = { 14 , 1, 'Y',8 };
    enemy_Carry = { 16, 18, 'Z',3 };
    e.maze_s[enemy_soldier.positionX][enemy_soldier.positionY] = enemy_soldier.enemy_soldier_symbol;
    e.maze_s[enemy_Tank.positionX][enemy_Tank.positionY] = enemy_Tank.enemy_tank_symbol;
    e.maze_s[enemy_Carry.positionX][enemy_Carry.positionY] = enemy_Carry.enemy_carry_symbol;
    e.maze_s[main_tower.positionX][main_tower.positionY] = main_tower.main_tower_symbol;

}

int TowerDefensemain()
{
    initialiser();
    cout << "currency = 3000"<<endl;
    cout << "Choose your Option: \n 1 - Buy Towers\n 2 - Upgrade Tower\n 3 - Sell Towers\n q - Start the round." << endl;
    char ch = _getch();

    maze d;
    d.show_maze();

}

void remove(std::array<int, 2> pos) {
    maze m;
    m.maze_s[pos[0]][pos[1]] = ' ';
}


void mazechange(std::array<int, 2> oldpos, std::array<int, 2> newpos, char character) {
    maze m;
    m.maze_s[newpos[0]][newpos[1]] = character;
    m.maze_s[oldpos[0]][oldpos[1]] = ' ';
}
#endif
