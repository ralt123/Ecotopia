#include <fstream>
#include <iostream>
#include <chrono>
#include <thread>

class Animation {
    public:
        std::ifstream frame;

        void output(std::string frame_num) {
            std::string lines;
            frame.open(frame_num);
            if (frame.is_open()) {
                while (std::getline(frame, lines)) {
                std::cout << lines << "\n";
                }
                
            }
            else {
                std::cout << "Not Found";
            }
        }

        void wait_timer() {
            std::chrono::milliseconds time(500);
            std::this_thread::sleep_for(time);
        }

};
