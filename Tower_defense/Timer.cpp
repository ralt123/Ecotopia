#include <iostream>
#include <iomanip>
#include <unistd.h>
using namespace std;
//libraries

int M = 0;
int S = 0;
//variables minute and second

void Exhibit()
{
  system("clear");//clear board after every second
  cout << setfill(' ') << setw(32) << "COUNT DOWN TIMER\n";
  cout << setfill(' ') << setw(37) << " -------------------------\n";
  cout << setfill(' ') << setw(12);
  cout << "| " << setfill('0') << setw(2) << M << " minutes | ";
  cout << setfill('0') << setw(2) << S << " seconds |\n" ;
  cout << setfill(' ') << setw(37) << " -------------------------\n";
}//poisituoning the timer
  
void Time()
{
  while (true) {//time loop till 10 mins

    Exhibit();//every repeat call on this function

    sleep(1);//pauses every secong

    S++;//start of time increases by second
    if (S == 60) {
      M++;
    //after secong reches 60, causes the minute to increase
    if (M == 10) {//stops at this minute call on the tower defense event
    //towerdefense()
    }
  S = 0;
}
}
}


