#include "../../includes.h"
int main() {
    Console console;
    // key press dictates if x or y goes up or down.
    console.console_mode("echo");
    int kp = std::cin.get();
    system("CLS");
    console.console_mode("standard");
    std::cout <<  kp;
    std::cin.ignore();
        }