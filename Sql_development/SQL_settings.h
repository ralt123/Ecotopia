#include "C:/sqlite3/sqlite3.h"
#include <stdio.h>
#include <iostream>
#include <vector>

/* 
References:
https://www.devdungeon.com/content/compiling-sqlite3-c
https://videlais.com/2018/12/14/c-with-sqlite3-part-5-encapsulating-database-objects/
https://stackoverflow.com/questions/14437433/proper-use-of-callback-function-of-sqlite3-in-c
https://www.w3schools.com/sql/default.asp
*/
// sqlite handling class:
class SQL {
    public:
        // pointer to sqlite3 type, needed for _exec commands
        sqlite3 *db;

        // rc used to see if command was successful with SQLITE_OK
        int rc;

        // pointer to char, SQLITE parses error message to this
        char *error;

        // 2D and normal vector, will be parsed to main Ecotopia program so all SQL handling is done here.
        static std::vector<std::vector<std::string>> inventory_vector;
        static std::vector<std::string> inventory_item;

        // item Count

        SQL() {
            // Connects to inventory database where the inventory table is stored  
            rc = sqlite3_open("inventory.db", &db);
            // Creates table on innitialisation of object
            create_inventory_table();
            return_table();
            
        }

        void create_inventory_table() {
            // Creates table if not already made
            //
             rc = sqlite3_exec(db, "CREATE TABLE IF NOT EXISTS inventory(" \
            "item_num  INT PRIMARY KEY NOT NULL, " \
            "item_name CHAR(50) NOT NULL," \
            "item_type CHAR(50) NOT NULL,"\
            "item_stat INT      NOT NULL );", NULL, NULL, &error);

            if (rc != SQLITE_OK) {
                std::cout <<"\nCreate error: "<< error;
            }
        }

        void insert_item(std::string item_num, std::string item_name, std::string item_type, std::string item_stat) {
            std::string query;
            query = "INSERT INTO inventory (item_num, item_name, item_type, item_stat)" \
            "VALUES("+item_num+",'"+item_name+"','"+item_type+"',"+item_stat+")";
            rc = sqlite3_exec(db,query.c_str(), NULL, NULL, &error);
            if (rc != SQLITE_OK) {
                    std::cout <<"\nInsert error:"<< *error;
                }
            return_table();
        }

        void return_table() {
            inventory_vector.clear();
            std::string query;
            query = "SELECT * FROM inventory";
            rc = sqlite3_exec(db, query.c_str(), callback, NULL, &error);
            if (rc != SQLITE_OK) {
                    std::cout <<"\nSelect error:"<<*error;
                }
        }

        static int callback(void *NotUsed, int argc, char **argv, char **azColName) {
            // argv is parsed each value from previously used SQL statement 
            // then added to 2d vector to be parsed to the main program
            // and for some reason call back needs to be static, so i had to work around this
            for(int i = 0; i < argc; i++) {
                inventory_item.push_back(argv[i]);  
            }
           
            inventory_vector.push_back(inventory_item);
            inventory_item.clear();
            return 0;
        }

        void remove_item(std::string item_name, std::string item_num) {
            // Very self explanitory:
            std::string query;
            query = "DELETE FROM inventory WHERE item_num = "+item_num+" AND item_name = '"+item_name+"'";
            rc = sqlite3_exec(db, query.c_str(),NULL ,NULL, &error);
            if (rc == SQLITE_OK) {
                update_table();
                return_table();
            }
            else {
                std::cout <<"\n" << "SQL Deletion error:" + *error;
            }
            

        }
        void update_table() {
            std::string query;
            std::stringstream row;
            std::stringstream value;
            for (int i = 0; i < inventory_vector.size(); i++) {
                row << i;
                query = "UPDATE inventory SET item_num = "+row.str()+" WHERE item_num != "+row.str()+" AND item_name = '"+inventory_vector[i][2]+"';";
                rc = sqlite3_exec(db, query.c_str(), NULL, NULL, &error);
                if (rc != SQLITE_OK) {
                    std::cout <<"\nupdate error:" << *error;
                }
            }
        }

};

//declare static attribute
std::vector<std::vector<std::string>> SQL::inventory_vector;
std::vector<std::string> SQL::inventory_item;

/*
//TEsting
int main() {
    SQL test;

    test.insert_item("0", "sword", "Weapon" , "20");
    test.return_table();
    std::cout << SQL::inventory_vector[0][0];
    
    

}
*/