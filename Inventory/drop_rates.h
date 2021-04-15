#include <random>
#include <ctime>
#include <string>
#include <iostream>
#include <vector>

class Drops {
    public:
        std::vector<std::vector<std::string>> stats 
        {{"Phaser", "weapon", "5"}, 
        {"Laser Rifle", "weapon", "10"},
        {"Plasma Blaster","weapon", "20"},
        {"Death-Ray", "weapon", "100"},
        {"Armoured Chest-Plate", "armour", "15"},
        {"Armoured Helmet", "armour", "20"},
        {"Praetor-Suit", "armour", "100"},
        {"Medical Syringe", "medical", "10"}};

        Drops() {
            srand(time(0));
        }

        std::string random_choice() {
            int num = rand() % 100;
            std::cout << num;

            if (num <= 20) {
                return "Phaser";
            } 
            else if(num > 20 && num <= 35) {
                return "Laser Rifle";
            }
            else if(num > 35 && num <= 45) {
                return "Plasma Blaster";
            }
            else if(num > 45 && num <= 60) {
                return "Armoured Chest-Plate";
            }
            else if(num > 60 && num <= 70) {
                return "Armoured Helmet";
            }
            else if (num > 70 && num <= 75 ) {
                return "Death-Ray";
            }
            else if (num > 75 && num <= 80 ) {
                return "Praetor-Suit";
            }
            else if (num > 80 && num <= 100) {
                return "medical syringe";
            }

        return "";
        }


};

