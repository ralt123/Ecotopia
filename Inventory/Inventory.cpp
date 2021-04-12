#include "../includes.h"

int main() {
    sqlite3* db; 
    int exit = 0;
    exit = sqlite3_open("example.db", &db);

    if (exit) {
        std::cout << "Error!";
    }
}
