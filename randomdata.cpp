#include <iostream>//-----------to store a variable to ake the function work-------------------------------
using namespace std;

int sinceevent=1;

int lastevent(){
    return sinceevent;
}
int lasteventadd(){
    sinceevent+=1;
    return sinceevent;
}
int lasteventreset(){
    sinceevent=1;
    return sinceevent;
}
