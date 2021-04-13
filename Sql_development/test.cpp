#include "C:/sqlite3/sqlite3.h"
#include <stdio.h>
#include <iostream>
#include <vector>


class SQL {
    public:
        sqlite3 *db;
        int rc;
        char *error;
        static std::vector<std::vector<std::string>> inventory_vector;
        static std::vector<std::string> inventory_item;

        SQL() {
            rc = sqlite3_open("inventory.db", &db);
            create_table();
        }

        void create_table() {
             rc = sqlite3_exec(db, "CREATE TABLE IF NOT EXISTS inventory(" \
            "item_num  INT PRIMARY KEY NOT NULL, " \
            "item_name CHAR(50) NOT NULL," \
            "item_type CHAR(50) NOT NULL,"\
            "item_stat INT      NOT NULL );", NULL, NULL, &error);

            if (rc != SQLITE_OK) {
                std::cout << error;
            }
        }

        void insert_table(std::string item_num, std::string item_name, std::string item_type, std::string item_stat) {
            std::string query;
            query = "INSERT INTO inventory (item_num, item_name, item_type, item_stat)" \
            "VALUES("+item_num+",'"+item_name+"','"+item_type+"',"+item_stat+")";
            rc = sqlite3_exec(db,query.c_str(), NULL, NULL, &error);
        }

        void return_table() {
            std::string query;
            query = "SELECT * FROM inventory";
            rc = sqlite3_exec(db, query.c_str(), callback, NULL, &error);
        }

        static int callback(void *NotUsed, int argc, char **argv, char **azColName) {

            // int argc: holds the number of results
            // (array) azColName: holds each column returned
            // (array) argv: holds each value
            int item_counter = 0;
            for(int i = 0; i < argc; i++) {
                // inventory_item.push_back(argv[i]);  
                std::cout << argv[i];
                
                
            }
            //item_counter += 1;
            //inventory_vector.push_back(inventory_item);
            //inventory_item.clear();
            return 0;
        }
        void insert_vector(std::string value) {

        }
};

int main() {
    SQL test;

    test.insert_table("0", "sword", "Weapon" , "20");
    test.return_table();
    std::vector<int> test_vect;
    
    

}