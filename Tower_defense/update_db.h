#ifndef UPDATE_DB_H
#define UPDATE_DB_H
#include <iostream>
#include <vector>
#include "select_db.h"
#include "libsqlite.hpp"
#include "Towers/towerclass.h"
using namespace std;

class update_db
{
protected:

public:

    void makealive(int towernumber, int defendernumber, std::array<int, 2> defpos) {
        select_db update;
        std::vector<int> towernum = update.get_towernumber();
        std::vector<int> defendernum = update.get_defendernumber();
        std::vector<int> maxhealth = update.get_maxhealth();
        int dmaxhealth;
        int size = towernum.size();
        for (int i = 0; i < size; i++) {
            if (towernum[i] == towernumber) {
                for (int i1 = 0; i1 < defendernum.size(); i++) {
                    if (defendernum[i] == defendernumber) {
                        dmaxhealth = maxhealth[i];
                        goto endloop;
                    }
                }
            }
        }
    endloop:
        try
        {
            int PosX = defpos[0];
            int PosY = defpos[1];

            sqlite::sqlite db("defenderdata.db");

            auto cur = db.get_statement();

            cur->set_sql("UPDATE defenders SET alive = 1,health=?,PosX=?,PosY=? WHERE towernumber=? AND defendernumber=?;");
            cur->prepare();
            cur->bind(1, dmaxhealth);
            cur->bind(2, PosX);
            cur->bind(3, PosY);
            cur->bind(4, towernumber);
            cur->bind(5, defendernumber);

            cur->step();
        }
        catch (sqlite::exception e)
        {
            cerr << e.what() << endl;
        }
    }
    void changehealth(int towernumber, int defendernumber, int healthdif, std::array<int, 2> pos) {
        select_db update1;
        std::vector<int> towernum = update1.get_towernumber();
        std::vector<int> defendernum = update1.get_defendernumber();
        std::vector<int> maxhealth = update1.get_maxhealth();
        std::vector<int> health = update1.get_health();
        int dmaxhealth;
        int dhealth;
        int alive = 1;
        int size = towernum.size();
        for (int i = 0; i < size; i++) {
            if (towernum[i] == towernumber) {
                for (int i1 = 0; i1 < defendernum.size(); i++) {
                    if (defendernum[i] == defendernumber) {
                        dmaxhealth = maxhealth[i];
                        dhealth = health[i];
                        goto endloop;
                    }
                }
            }
        }
    endloop:
        if (healthdif + dhealth > dmaxhealth) {
            dhealth = dmaxhealth;
        }
        else if (healthdif + dhealth <= 0) {
            dhealth = 0;
            alive = 0;
            remove(pos);
        }
        else {
            dhealth += healthdif;
        }

        try
        {

            sqlite::sqlite db("defenderdata.db");

            auto cur = db.get_statement();

            cur->set_sql("UPDATE defenders SET alive = ?,health=? WHERE towernumber=? AND defendernumber=?;");
            cur->prepare();
            cur->bind(1, alive);
            cur->bind(2, dhealth);
            cur->bind(3, towernumber);
            cur->bind(4, defendernumber);
            cur->step();
        }
        catch (sqlite::exception e)
        {
            cerr << e.what() << endl;
        }
    }

    void upgrade(int towernumber) {
        select_db update1;
        std::vector<int> towernum = update1.get_towernumber();
        std::vector<int> maxhealth = update1.get_maxhealth();
        std::vector<int> attack = update1.get_attack();
        int dmaxhealth;
        int dattack;
        int size = towernum.size();
        for (int i = 0; i < size; i++) {
            if (towernum[i] == towernumber) {
                dmaxhealth = maxhealth[i];
                dattack = attack[i];
                goto endloop;
            }
        }
    endloop:
        dattack += 2;
        dmaxhealth += 5;

        try
        {

            sqlite::sqlite db("defenderdata.db");

            auto cur = db.get_statement();

            cur->set_sql("UPDATE defenders SET maxhealth = ?,attack=? WHERE towernumber=?;");
            cur->prepare();
            cur->bind(1, dmaxhealth);
            cur->bind(2, dattack);
            cur->bind(3, towernumber);
            cur->step();
        }
        catch (sqlite::exception e)
        {
            cerr << e.what() << endl;
        }
    }

    void change_pos(int towernumber, int defendernumber, int xchange, int ychange) {
        select_db update2;
        std::vector<int> coords;
        int PosX;
        int PosY;
        coords = update2.spec_defender(towernumber, defendernumber);
        PosX = coords[0] + xchange;
        PosY = coords[1] + ychange;

        try
        {

            sqlite::sqlite db("defenderdata.db");

            auto cur = db.get_statement();

            cur->set_sql("UPDATE defenders SET PosX=?,PosY=? WHERE towernumber=? AND defendernumber=?;");
            cur->prepare();
            cur->bind(1, PosX);
            cur->bind(2, PosY);
            cur->bind(3, towernumber);
            cur->bind(4, defendernumber);
            cur->step();
        }
        catch (sqlite::exception e)
        {
            cerr << e.what() << endl;
        }


    }
};
#endif
