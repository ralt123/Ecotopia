#ifndef SELECT_DB_H
#define SELECT_DB_H
#include <iostream>
#include <string>
#include <vector>
#include "libsqlite.hpp"
using namespace std;

class select_db
{
protected:
    std::vector<int> towernum;
    std::vector<int> defendernum;//each tower has 5 defenders
    std::vector<int> maxhealth;
    std::vector<int> health;
    std::vector<int> attack;
    std::vector<int> PosX;
    std::vector<int> PosY;
    std::vector<int> alive;
    int size;
public:
    select_db() {
        try
        {
            sqlite::sqlite db("defenderdata.db");

            auto cur = db.get_statement();
            cur->set_sql("SELECT * FROM defenders;");
            cur->prepare();

            while (cur->step()) {
                towernum.push_back(cur->get_int(0));
                defendernum.push_back(cur->get_int(1));
                maxhealth.push_back(cur->get_int(2));
                health.push_back(cur->get_int(3));
                attack.push_back(cur->get_int(4));
                PosX.push_back(cur->get_int(5));
                PosY.push_back(cur->get_int(6));
                alive.push_back(cur->get_int(7));

            }
        }
        catch (sqlite::exception e)
        {
            cerr << e.what() << endl;
        }
    }

    std::vector<int> get_towernumber() {
        select_db();
        return towernum;
    }
    std::vector<int> get_defendernumber() {
        select_db();
        return defendernum;
    }
    std::vector<int> get_maxhealth() {
        select_db();
        return maxhealth;
    }
    std::vector<int> get_health() {
        select_db();
        return health;
    }
    std::vector<int> get_attack() {
        select_db();
        return attack;
    }
    std::vector<int> get_Xcoord() {//x coordinate
        select_db();
        return PosX;
    }
    std::vector<int> get_Ycoord() {//y coordinate
        select_db();
        return PosY;
    }
    std::vector<int> get_alive() {//boolean alive or not (alive=1, dead=0)
        select_db();
        return alive;
    }
    /*
    void ressurect(int towernumber,int defendernumber){
      select_db();
      size=towernum.size();
      for(int i=0;i<size;i++){
        if(towernum[i]==1){
          if(alive[i]==0){
            update_db u;
            u.makealive(towernumber,defendernumber)
            break;
          }
        }
      }
    }*/

    bool if_alive(int towernum, int defendernum) {
        bool alive;
        try
        {
            sqlite::sqlite db("defenderdata.db");

            auto cur = db.get_statement();
            cur->set_sql("SELECT alive FROM defenders WHERE towernumber=? AND defendernumber=?;");
            cur->prepare();
            cur->bind(1, towernum);
            cur->bind(2, defendernum);

            while (cur->step()) {
                if (cur->get_int(0) == 1) {
                    alive = true;
                }
                else {
                    alive = false;
                }

            }
            return alive;
        }
        catch (sqlite::exception e)
        {
            cerr << e.what() << endl;
        }

        return true;
    }

    void showall() {
        try
        {
            sqlite::sqlite db("defenderdata.db");

            auto cur = db.get_statement();
            cur->set_sql("SELECT * FROM defenders;");
            cur->prepare();

            while (cur->step()) {
                cout << cur->get_int(0) << " " << cur->get_int(1) << " " << cur->get_int(2) << " " << cur->get_int(3) << " " << cur->get_int(4) << " " << cur->get_int(5) << " " << cur->get_int(6) << " " << cur->get_int(7) << endl;
            }
        }
        catch (sqlite::exception e)
        {
            cerr << e.what() << endl;
        }
    }
    std::vector<int> spec_defender(int towernum, int defendernum) {
        std::vector<int> coords;
        try
        {
            sqlite::sqlite db("defenderdata.db");

            auto cur = db.get_statement();
            cur->set_sql("SELECT PosX,PosY FROM defenders WHERE towernumber=? AND defendernumber=?;");
            cur->prepare();
            cur->bind(1, towernum);
            cur->bind(2, defendernum);

            while (cur->step()) {
                coords.push_back(cur->get_int(0));
                coords.push_back(cur->get_int(1));
            }
            return coords;
        }
        catch (sqlite::exception e)
        {
            cerr << e.what() << endl;
        }
        return {0,0};

    }



};
#endif
