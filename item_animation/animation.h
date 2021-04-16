#include <fstream>
#include <iostream>
#include <chrono>
#include <thread>

class Animation {
    public:
        std::ifstream frame;

        void output1() {
            std::ifstream frame2;
            std::string lines;
            frame2.open("C:/Users/peter/Documents/GitHub/Ecotopia/item_animation/frame1.txt");
            if (frame2.is_open()) {
                while (std::getline(frame2, lines)) {
                std::cout << lines << "\n";
                }
            }
        }

        void output2() {
            std::ifstream frame2;
            std::string lines;
            frame2.open("C:/Users/peter/Documents/GitHub/Ecotopia/item_animation/frame2.txt");
            if (frame2.is_open()) {
                while (std::getline(frame2, lines)) {
                std::cout << lines << "\n";
                }
            }
        }

        void output3() {
            std::ifstream frame2;
            std::string lines;
            frame2.open("C:/Users/peter/Documents/GitHub/Ecotopia/item_animation/frame3.txt");
            if (frame2.is_open()) {
                while (std::getline(frame2, lines)) {
                std::cout << lines << "\n";
                }
            }
        }

        void wait_timer() {
            std::chrono::milliseconds time(500);
            std::this_thread::sleep_for(time);

            
        }

        void full_animation() {
            output1();
            wait_timer();
            system("CLS");
            output2();
            wait_timer();
            system("CLS");
            output3();
            wait_timer();
            system("CLS");

        }

};



