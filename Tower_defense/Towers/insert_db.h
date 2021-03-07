//------------------------------------------------used to add new data to the defenders database (not change, add)------------------------
#ifndef INSERT_DB_H
#define INSERT_DB_H
#include <iostream>
#include "select_db.h"
#include "libsqlite.hpp"
using namespace std;


int insert_db(int towernum,int defendernum,int maxhealth,int health,int PosX,int PosY,bool alive)
{
    try
    {
        std::vector<int> towernumber;
        int size;
        int defendercount;
        select_db view;
        towernumber=view.get_towernumber();
        size=towernumber.size();
        for(int i=0;i<size;i++){
          if(towernumber[i]==towernum){
            defendercount+=1;
          }
        }
        if(defendercount>=5){
          cout<<"error: tower already has 5 defenders"<<endl;
          return 1;
        }
        sqlite::sqlite db("defenderdata.db");

        auto cur = db.get_statement();
      
        cur->set_sql( "INSERT INTO defenders VALUES(?,?,?,?,?,?,?);" );
        cur->prepare();
        cur->bind( 1, towernum );
        cur->bind( 2, defendernum );
        cur->bind( 3, maxhealth );
        cur->bind( 4, health );
        cur->bind( 5, PosX );
        cur->bind( 6, PosY );
        cur->bind( 7, alive );
        cur->step();


    }
    catch( sqlite::exception e )
    {
        cerr << e.what() << endl;
        return 1;
    }
  

  return 0;
}
#endif
