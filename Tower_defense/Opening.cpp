#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;
void print( std::vector<std::string> &stringVec ) {
cout << std::setfill( '_' ) << setw( 60 ) << '_' <<  endl;
for( int i=0; i< stringVec.size(); i++ ) {
cout << '|' << std::left << setfill(' ')<< setw( 60 - 2 ) << stringVec[i] << '|'<< endl;}
cout << std::setfill( '_' ) << setw( 60 ) << '_' <<  endl;
}
int main( )
{
  std::vector<std::string> vec = { "Tower Defense", 
  "Main event",
  "User please stop the invasion from the monsters.",
  "Do you accept? Please answer y/n"};
  print( vec );
  char option;
  cout << "Type your option: "; // Type a number and press enter
  cin >> option;
  if(option == 'y'){
  std::vector<std::string> vec = { "You better move fast, The monsters are attacking the city."};
  print( vec );
  } else{
    std::vector<std::string> vec = { "Warrior we have lost the battle, please find a new world."};
    print( vec );
    
  }
  
}
