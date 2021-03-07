//-------------------------------used to update the defenders database------------------------------
#ifndef UPDATE_DB_H
#define UPDATE_DB_H
#include <iostream>
#include <vector>
#include "select_db.h"
#include "libsqlite.hpp"
using namespace std;

class update_db
{
protected:

public:
  
  void makealive(int towernumber,int defendernumber){
    select_db update;
    std::vector<int> towernum=update.get_towernumber();
    std::vector<int> defendernum=update.get_defendernumber();
    std::vector<int> maxhealth=update.get_maxhealth();
    int dmaxhealth;
    int size=towernum.size();    
    for(int i=0;i<size;i++){
      if(towernum[i]==towernumber){
        for(int i1=0;i1<defendernum.size();i++){
          if(defendernum[i]==defendernumber){
              dmaxhealth=maxhealth[i];
              goto endloop;
          }
        }
      }
    }
    endloop:
    try
    {
        
        sqlite::sqlite db("defenderdata.db");

        auto cur = db.get_statement();
      
        cur->set_sql( "UPDATE defenders SET alive = 1,health=? WHERE towernumber=? AND defendernumber=?;");
        cur->prepare();
        cur->bind( 1, dmaxhealth );
        cur->bind( 2, towernumber );
        cur->bind( 3, defendernumber );
        cur->step();
    }
    catch( sqlite::exception e )
    {
        cerr << e.what() << endl;
    }
  }  
  void changehealth(int towernumber,int defendernumber,int healthdif){
    select_db update1;
    std::vector<int> towernum=update1.get_towernumber();
    std::vector<int> defendernum=update1.get_defendernumber();
    std::vector<int> maxhealth=update1.get_maxhealth();
    std::vector<int> health=update1.get_health();
    int dmaxhealth;
    int dhealth;
    int alive = 1;
    int size=towernum.size();    
    for(int i=0;i<size;i++){
      if(towernum[i]==towernumber){
        for(int i1=0;i1<defendernum.size();i++){
          if(defendernum[i]==defendernumber){
              dmaxhealth=maxhealth[i];
              dhealth=health[i];
              goto endloop;
          }
        }
      }
    }
    endloop:
    if(healthdif+dhealth>dmaxhealth){
      dhealth=dmaxhealth;
    }else if(healthdif+dhealth<0){
      dhealth=0;
      alive=0;
      cout << "dead"<<endl;
    }else{
      dhealth+=healthdif;
    }
    
    try
    {
        
        sqlite::sqlite db("defenderdata.db");

        auto cur = db.get_statement();
      
        cur->set_sql( "UPDATE defenders SET alive = ?,health=? WHERE towernumber=? AND defendernumber=?;");
        cur->prepare();
        cur->bind( 1, alive );
        cur->bind( 2, dhealth );
        cur->bind( 3, towernumber );
        cur->bind( 4, defendernumber );
        cur->step();
    }
    catch( sqlite::exception e )
    {
        cerr << e.what() << endl;
    }
  }
  void change_pos(int towernumber,int defendernumber,int xchange,int ychange){
    select_db update2;
    std::vector<int> coords;
    int PosX;
    int PosY;
    coords=update2.spec_defender(towernumber,defendernumber);
    PosX=coords[0]+xchange;
    PosY=coords[1]+ychange;
    
        try
    {
        
        sqlite::sqlite db("defenderdata.db");

        auto cur = db.get_statement();
      
        cur->set_sql( "UPDATE defenders SET PosX=?,PosY=? WHERE towernumber=? AND defendernumber=?;");
        cur->prepare();
        cur->bind( 1, PosX );
        cur->bind( 2, PosY );
        cur->bind( 3, towernumber );
        cur->bind( 4, defendernumber );
        cur->step();
    }
    catch( sqlite::exception e )
    {
        cerr << e.what() << endl;
    }
    
 
  }
  

};
#endif
