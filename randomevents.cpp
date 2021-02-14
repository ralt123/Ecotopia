#include <stdio.h>     //---------------------this is the main random events file-----------------------------------
#include <stdlib.h>     
#include <time.h>       
#include <ctime>
#include <iostream>
#include "events.h"
#include "randomdata.h"
using namespace std;


int randomchance(time_t current_time, bool movement)
{
  int randomnum;
  int upperlimit;
  time_t current_time1;
  int timepassed;
  int movementbonus=1;
  int rand1;
  current_time1 = time(NULL);
  timepassed= current_time1- current_time1;
  srand (time(NULL));
  if(movement==true){
    movementbonus=2;
  }
  upperlimit=(((100)-10*timepassed)/lastevent())/movementbonus;
  cout << "upperlimit is : " << upperlimit << endl;
  rand1=rand()*lastevent();
  if(rand1<1){
      rand1=rand1*-1;
  }
  randomnum = rand1 % upperlimit + 1;
  if(randomnum==2){
      stat1();
  }else if(randomnum==3){
      stat2();
  }else if(randomnum==4){
      resource1();
  }else if(randomnum==5){
      resource2();
  }else if(randomnum==6){
      combat1();
  }else if(randomnum==7){
      combat2();
  }else{
      lasteventadd();
  }
  return randomnum ;
}
