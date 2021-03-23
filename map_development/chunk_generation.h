#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h> 
#include <fstream>
#include <random>
#include <ctime>
#include <sstream>


class Chunk {
    public:
        int chunk_sizex;
        int chunk_sizey;

        Chunk() {
        srand(time(0));
        chunk_sizex = 100;
        chunk_sizey = 28;
        if (!does_file_exist("chunk_coords.txt")) {
            chunk_generator(0,0);
        }

        }

        bool does_file_exist(const char *filename) {
            std::ifstream infile(filename);
            return infile.good();
        }

        std::string rand_character(int x) {
            std::vector<std::string> characters = {"A","B","T","o",".", ".", " " , " " , " " , " "};
            int rand_num_1 = rand() % 500;
            int rand_num_2 = rand() % 6;
            int rand_num_3 = rand() % 4;
            int choice;
            
            // Interactive character choice 25% chance
            if ( rand_num_1 == 0) {
                    return characters[rand_num_3];
            }

            // Scenery character choice 75% chance
            else {
                return characters[rand_num_2+4];
            }   
        }

        void chunk_generator(int x, int y) {
            std::ofstream mapchunk;
            std::stringstream map_ss;
            map_ss << "map" << "," << x << "-" << y << ".txt";
            std::string map_name = map_ss.str();
            add_chunk_coords(map_name);
            mapchunk.open(map_name);

            for (int i = 0; i < chunk_sizey ; i++){
                std::string char2 = "";
                for (int x = 0; x < chunk_sizex; x++) {
                    char2 += rand_character(x);  
                }
            
            mapchunk << char2 << "\n";
            }
        } 

        void add_chunk_coords(std::string map_name) {
            std::ofstream chunk_coords;
            chunk_coords.open("chunk_coords.txt");
            chunk_coords << map_name << "\n";
            chunk_coords.close();
        }

};



