#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <windows.h>
#include <stdlib.h> 

using namespace std;

int input(){
    HANDLE hstdin;
    DWORD  mode;

    hstdin = GetStdHandle( STD_INPUT_HANDLE );
    GetConsoleMode( hstdin, &mode );
    SetConsoleMode( hstdin, ENABLE_ECHO_INPUT | ENABLE_PROCESSED_INPUT );  
    
    int ch = cin.get();
    system("CLS");

    SetConsoleMode( hstdin, mode ); 
    return ch;
}

std::vector<std::vector<std::string>> map_vect_generation(){
    std::vector<std::vector<std::string>> mapvect;
    std::vector<std::string> row;
    
    std::string line, chars;
    
    std::ifstream map("mapingfile.txt");
    while(std::getline(map, line)) {
        row.clear();
        chars.clear();
        for (int i = 0; i <= line.size(); i++) {
            chars.clear();
            chars.push_back(line[i]);
            row.push_back(chars);

        }
        mapvect.push_back(row);
    }

    return mapvect;
}


void map_output(int x = 0, int y = 0) {
    std::vector<std::vector<std::string>> map = map_vect_generation();
    std::string player = "O";
    map[y][x] = player;
    for (int i = 0; i < map.size(); i++) {
        for (int j = 0; j < map[i].size(); j++) {
            if (map[i][j] != "\n") {
                 cout << map[i][j];
            }

            else cout << endl;
        }
        std::cout << endl;    
    }
 
}

int main() {
    int w = -1;
    int a = -1;
    int s =  1;
    int d = 1;
    int x = 0;
    int y = 0;

    map_output();
    while (true) {
        int key_press = input();
        switch (key_press) {
            case 119:
                y += w;
                break;
            case 97:
                x += a;
                break;
            case 115:
                y += s;
                break;
            case 100:
                x += d;
                break;
            default:
                break;
        } 
        map_output(x,y);

    }
}