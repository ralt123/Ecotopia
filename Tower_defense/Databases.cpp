#include <iostream>
#include <string>
#include <sqlite3.h>

using namespace std;


int create_db() {
    sqlite3 *db;
    char *column = 0;
    int load;
    string sql;
    load = sqlite3_open("enemydata.db", &db);
    
    if(load){
        cout << "DB Error: " << sqlite3_errmsg(db) << endl;
        sqlite3_close(db);
        return(1);
    }

    sql = "DROP TABLE Enemys;";
    
    load = sqlite3_exec(db, sql.c_str(), callback, 0, &column);

    sql = "CREATE TABLE Enemys ("  \
      "EnemyID INT NOT NULL," \
      "EnemyName        INT    NOT NULL,"\
      "EnemyHealth        INT    NOT NULL,"\
      "EnemyPositionX        INT    NOT NULL,"\
      "EnemyPositionY        INT    NOT NULL,"\
      "alive           BOOLEAN    NOT NULL);";
    
    load = sqlite3_exec(db, sql.c_str(), callback, 0, &column);
    sqlite3_close(db);
    
    return 0;
}

