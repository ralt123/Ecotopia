#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "console_settings.h" 

using namespace std;
Console console;

int input(){
    console.console_mode("echo");
    int ch = cin.get();
    system("CLS");
    console.console_mode("standard");
    return ch;
}

std::vector<std::vector<std::string>> map_vect_generation(){
    std::vector<std::vector<std::string>> mapvect;
    std::vector<std::string> row;
    
    std::string line, chars;
    
    std::ifstream map("map,0-0.txt");
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
    std::vector<std::vector<std::string>> map;
    map = map_vect_generation();
    std::string player = "O";
    std::string full_map;
    std::string temp_map;
    int position;
    if (!map.empty()) map[y][x] = player;
    else std::cout << "EMPTY!!!!";

    // loops through each row in 2D map 
    for (int i = 0; i < map.size(); i++) {
        
        // loops through each charatcer in the current cycles row and adds to a string of the full row
        for (int j = 0; j < map[i].size(); j++) {
            full_map +=  map[i][j];
        }
         // if the player is not on the row it prints the row in green fully 
        if (full_map.find(player) == string::npos) {
            std::cout << full_map <<endl;
            full_map.clear();
            continue;


        }
        // if the player is on the row is splits the row in two, changing the colour of the player to red, then back to green
        else if (full_map.find(player) != string::npos) {
            position = full_map.find(player);

            for (int l = 0; l < position; l++) {
                temp_map.push_back(full_map[l]);
            }
            std::cout << temp_map;
            console.text_colour("red");
            std::cout << player;
            console.text_colour("green");
            temp_map.clear();

            for (int t = position+1; t < full_map.length(); t++) {
                temp_map.push_back(full_map[t]);
            }

            std::cout << temp_map << endl;
            full_map.clear();

        }
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