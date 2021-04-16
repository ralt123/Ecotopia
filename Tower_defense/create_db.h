#ifndef CREATE_DB_H
#define CREATE_DB_H
#include <iostream>
#include <string>
#include "sqlite3.h"

using namespace std;

int callback(void* NotUsed, int len, char** value, char** column) {

    for (int i = 0; i < len; i++) {
        cout << column[i] << ": " << value[i] << endl;

    }
    return 0;
}

int create_db() {
    sqlite3* db;
    char* column = 0;
    int load;
    string sql;
    load = sqlite3_open("defenderdata.db", &db);

    if (load) {
        cout << "DB Error: " << sqlite3_errmsg(db) << endl;
        sqlite3_close(db);
        return(1);
    }

    sql = "DROP TABLE defenders;";

    load = sqlite3_exec(db, sql.c_str(), callback, 0, &column);

    sql = "CREATE TABLE defenders ("  \
        "towernumber INT NOT NULL," \
        "defendernumber        INT    NOT NULL,"\
        "maxhealth        INT    NOT NULL,"\
        "health        INT    NOT NULL,"\
        "attack        INT    NOT NULL,"\
        "PosX        INT    NOT NULL,"\
        "PosY        INT    NOT NULL,"\
        "alive           BOOLEAN    NOT NULL);";


    load = sqlite3_exec(db, sql.c_str(), callback, 0, &column);
    sqlite3_close(db);

    return 0;
}
//https://videlais.com/2018/12/12/c-with-sqlite3-part-2-creating-tables/ (adapted code from here)
#endif
