#include <iostream>
#include <string>
#include <stdlib.h> 
#include <fstream>


int main() {
    std::string char1 = "X";
    std::string char2;

    std::ofstream map;
    map.open("mapingfile.txt");
    
    if (map.is_open()) std::cout << "open\n";
    else std::cout << "Unsuccessful";

    for (int i = 0; i <= 10; i++){
        char2 = "";
        for (int x = 0; x <= 50; x++) {
            char2 += char1;  
        }

        map << char2 << "\n";
        std::cout << "Success\n";
 
    }
}
  