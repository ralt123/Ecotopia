#include <iostream>
#include <fstream>
#include "console_settings.h"
#include "chunk_generation.h"

Console console;

class Map: public Chunk{
    public:
        int chunk_x;
        int chunk_y;
        int coords_x;
        int coords_y;
        
        Map() {
            chunk_x = 0;
            chunk_y = 0;
            coords_x = 0;
            coords_y = 0;


            game();
        }

        std::string current_chunk() {
            std::stringstream cc;
            cc << "map," << chunk_x << "-" << chunk_y << ".txt";
            return cc.str();
        }

        std::vector<std::vector<std::string>> map_vect_generation(){

        std::vector<std::vector<std::string>> mapvect;
        std::vector<std::string> row;
        
        std::string line, chars;

        
        std::ifstream map(current_chunk());
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

        void new_chunk() {
            // if player goes out of chunk range new chunk is generated and player is placed in new position
            if (coords_x < 0) {
                chunk_x--;
                coords_x = Chunk::chunk_sizex-1;
            }

            else if (coords_x >= Chunk::chunk_sizex) {
                chunk_x++;
                coords_x = 0;
            }

            else if (coords_y < 0) {
                chunk_y--;
                coords_y = Chunk::chunk_sizey-1;
            }

            else if (coords_y >= Chunk::chunk_sizey) {
                chunk_y++;
                coords_y = 0;
            }


            std::string chunk_names;
            std::stringstream new_chunk_name;
            new_chunk_name << "map," << chunk_x << "-" << chunk_y << ".txt";

            std::ifstream check_chunk("chunk_coords.txt");
            while(getline(check_chunk, chunk_names)) {
                if (chunk_names == new_chunk_name.str()) map_output();
            }

            chunk_generator(chunk_x, chunk_y);
            map_output();
        }

        void map_output() {
        // validates that coords are in range, if not new chunk is made
        if (coords_x >= Chunk::chunk_sizex || coords_y >= Chunk::chunk_sizey) new_chunk();
        if (coords_x == -1||coords_y == -1) new_chunk();


        std::vector<std::vector<std::string>> map;
        map = map_vect_generation();
        std::string player = "O";
        std::string full_map;
        std::string temp_map;
        int position;

        map[coords_y][coords_x] = player;




        // loops through each row in 2D map 
        for (int i = 0; i < map.size(); i++) {
            
            // loops through each charatcer in the current cycles row and adds to a string of the full row
            for (int j = 0; j < map[i].size(); j++) {
                full_map +=  map[i][j];
            }
            // if the player is not on the row it prints the row in green fully 
            if (full_map.find(player) == std::string::npos) {
                std::cout << full_map << "\n";
                full_map.clear();
                continue;


            }
            // if the player is on the row is splits the row in two, changing the colour of the player to red, then back to green
            else if (full_map.find(player) != std::string::npos) {

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

                std::cout << temp_map << "\n";
                full_map.clear();

                }
            }
    
        }

        int input() {
            // key press dictates if x or y goes up or down.
            console.console_mode("echo");
            int kp = std::cin.get();
            system("CLS");
            console.console_mode("standard");
            return kp;
        }

        void game() {
            int w = -1;
            int a = -1;
            int s =  1;
            int d = 1;
            

            map_output();
            while (true) {
                int key_press = input();
                switch (key_press) {
                    case 119:
                        coords_y += w;
                        break;
                    case 97:
                        coords_x += a;
                        break;
                    case 115:
                        coords_y += s;
                        break;
                    case 100:
                        coords_x += d;
                        break;
                    default:
                        break;
                } 
                map_output();
            }

        
    }

};



int main() {
    Map map;
    std::cin.ignore();
}