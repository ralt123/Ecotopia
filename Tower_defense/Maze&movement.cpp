#include <iostream> 
#include <cmath>
#include <stdio.h>

using namespace std;

struct base
{
 int positionX ; 
 int positionY ; 
 char main_tower_symbol;
 int hp;
}main_tower;
 
struct enemy1
{
 int positionX;
 int positionY;
 char enemy_soldier_symbol;
 int enemy_hp;
}enemy_soldier;


struct enemy2
{
 int positionX;
 int positionY;
 char enemy_tank_symbol;
 int enemy_hp;
}enemy_Tank;


struct enemy3
{
 int positionX;
 int positionY;
 char enemy_carry_symbol;
 int enemy_hp;
}enemy_Carry;

struct towers
{
 int positionX;
 int positionY;
 char tower1_symbol;
 int enemy_hp;
}tower1;
 
void tower_hit()// function for when the main_tower hits an enemy
{
 main_tower.hp --;
}

void enemysoldierhit(){
 enemy_soldier.enemy_hp --;
}
void enemyTankhit(){
 enemy_Tank.enemy_hp --;
}
void enemyCarryhit(){
 enemy_Carry.enemy_hp --;
}

int pathing(){
  int tankpathX[10]= {2};
  int tankpathY[10]= {14};

  for (int i=0; i<10; ++i)
    enemy_Tank.positionX = tankpathX[i];
    

}

int main()
{
 const char HEIGHT = 19, WIDTH = 19; // the maze width and height 
 main_tower = {2,2,'O',10};
 enemy_soldier = {4, 18, 'X',5};
 enemy_Tank = { 1 , 14, 'Y',8};
 enemy_Carry = {18, 16, 'Z',3};

//placements for all the things

 unsigned char maze[WIDTH][HEIGHT] = 
{
' ','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F','G','H','I',  
'1','*','*','*','*','*','*','*','*','*','*','*','*','*',' ','*','*','*','*',
'2','*',' ',' ',' ',' ',' ',' ',' ','*',' ',' ','*','*',' ','*',' ','*','*',
'3','*','*','*','*','*','*','*',' ','*',' ','*','*',' ',' ','*',' ','*','*', 
'4','*',' ',' ',' ',' ',' ','*',' ','*',' ','*','*',' ','*','*',' ',' ',' ',
'5','*',' ',' ',' ',' ','*',' ',' ',' ',' ',' ',' ',' ','*','*','*',' ','*',
'6','*',' ','*','*',' ','*',' ','*','*',' ','*','*',' ',' ','*',' ',' ','*',
'7','*',' ','*',' ',' ','*',' ','*','*',' ',' ',' ',' ','*','*',' ','*','*',
'8','*',' ',' ',' ','*','*','*','*','*',' ','*',' ',' ','*','*',' ','*','*',
'9','*',' ','*',' ','*','*','*','*','*',' ','*',' ','*','*','*',' ','*','*',
'A','*',' ','*',' ',' ',' ','*','*','*',' ',' ',' ',' ',' ','*',' ','*','*',
'B','*',' ','*','*',' ','*','*',' ','*',' ','*','*',' ',' ','*',' ','*','*', 
'C','*',' ','*','*','*',' ',' ',' ',' ',' ','*','*',' ',' ',' ',' ',' ','*',
'D','*',' ',' ',' ','*','*','*','*','*','*','*','*',' ','*',' ','*',' ','*',
'E','*',' ','*','*','*','*',' ','*','*',' ','*','*',' ',' ',' ',' ',' ','*',
'F','*',' ','*',' ',' ',' ',' ','*','*',' ',' ','*',' ','*','*',' ','*','*',
'G','*',' ','*','*',' ','*','*','*','*',' ','*',' ',' ','*','*',' ','*','*',
'H','*',' ',' ','*','*',' ',' ',' ',' ',' ',' ',' ','*','*','*',' ','*','*',
'I','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*',' ','*','*',
};
 cout << "Choose your Option: \n 1 - Buy Towers\n 2 - Place Tower\n 3 - Upgrade Tower\n 4 - Sell Towers\n q - Start the round."<<endl;


 int i=0;
 bool spawn = true;
  
 char option = 's';

 bool update = false;

 while (option !='q') 
 {


 
  if (update == true) 
  {
   system("CLS");
   maze[enemy_soldier.positionX][enemy_soldier.positionY] = enemy_soldier.enemy_soldier_symbol;
   maze[enemy_Tank.positionX][enemy_Tank.positionY] = enemy_Tank.enemy_tank_symbol;
   maze[enemy_Carry.positionX][enemy_Carry.positionY] = enemy_Carry.enemy_carry_symbol;
   maze[main_tower.positionX][main_tower.positionY] = main_tower.main_tower_symbol; 
        
 
   for(int y=0;y<HEIGHT;y++)
   {
    cout << endl;
     for(int x=0;x<WIDTH;x++)
      {
       cout << maze[x][y];
      }
    }
    cout << endl << endl << "    health: " << main_tower.hp << endl << "____________________\n \n";
    update = false;
}
int numberoftowers=0;
cin >> option; 
update = true;      

switch (option) 
{
 case '1':{
  int currency=1000;
  if(currency<1000){
  cout << "your broke"<<endl;
  break;
}
int x; 
cout << "Type your x cordinate for tower: "; 
cin >> x;
int y; 
cout << "Type your y cordinate for tower: "; 
cin >> y;

if(x <= 10 && y <=10){
 tower1 = {x,y,'s',10};
 maze[tower1.positionX][tower1.positionY] = tower1.tower1_symbol; 
 }
else if (x<= 10 && y > 10){
  tower1 = {x,y-87,'s',10};
}
else if (x> 10 && y <= 10){
  tower1 = {x-87,y,'s',10};
}
else{
  tower1 = {x-87,y-87,'s',10};
}

 
}
}


option = 'q';

update = false;

while (option =='q') 
{

 cin >> option; 
 update = true;  
 
 if (update == true) 
 {
  system("CLS");
  maze[enemy_soldier.positionX][enemy_soldier.positionY] = enemy_soldier.enemy_soldier_symbol;
  maze[enemy_Tank.positionX][enemy_Tank.positionY] = enemy_Tank.enemy_tank_symbol;
  maze[enemy_Carry.positionX][enemy_Carry.positionY] = enemy_Carry.enemy_carry_symbol;
  maze[main_tower.positionX][main_tower.positionY] = main_tower.main_tower_symbol; 
        
 
  for(int y=0;y<HEIGHT;y++)
  {
   cout << endl;
   for(int x=0;x<WIDTH;x++)
   {
    cout << maze[x][y];
   }
  }
 cout << endl << endl << "    health: " << main_tower.hp << endl << "____________________\n \n";
 update = false;
 }
 
  
 if (main_tower.hp == 0)// when the maintower rund out of hp the ganmes stops and print out you have lost the game.
 {
  cout <<" you have lost the game \n";                    
  break;
 }

 while (maze[enemy_Tank.positionX][enemy_Tank.positionY] == maze[main_tower.positionX][main_tower.positionY])
 {
  if(main_tower.hp > 0){
   tower_hit();}
  if(main_tower.hp == 0){
   cout <<" you have lost the game \n";
   break;}
  if(enemy_Tank.enemy_hp > 0){
   enemyTankhit();
   cout << enemy_Tank.enemy_hp << endl;}
  if(enemy_Tank.enemy_hp == 0)
   {enemy_Tank = { 1 , 14, 'Y',8};}
 }

 while (maze[enemy_soldier.positionX][enemy_soldier.positionY] == maze[main_tower.positionX][main_tower.positionY])
 {
  if(main_tower.hp > 0){
   tower_hit();}
  if(main_tower.hp == 0){
   cout <<" you have lost the game \n";
   break;}
  if(enemy_soldier.enemy_hp > 0){
   enemysoldierhit();
   cout << enemy_soldier.enemy_hp << endl;}
  if(enemy_soldier.enemy_hp == 0)
   {enemy_soldier = {4, 18, 'X',5};}
 }

 while (maze[enemy_Carry.positionX][enemy_Carry.positionY] == maze[main_tower.positionX][main_tower.positionY])
 {
  if(main_tower.hp > 0){
   tower_hit();}
  if(main_tower.hp == 0){
   cout <<" you have lost the game \n";
   break;}
  if(enemy_Carry.enemy_hp > 0){
   enemyCarryhit();
   cout << enemy_Carry.enemy_hp << endl;}
  if(enemy_Carry.enemy_hp == 0)
   {enemy_Carry = {18, 16, 'Z',3};}
 }

 if (maze[enemy_Tank.positionX+1][enemy_Tank.positionY] != '*' )
 {
  update = true;
  maze[enemy_Tank.positionX][enemy_Tank.positionY] = ' ';
  enemy_Tank.positionX ++;
}

 if(maze[enemy_Tank.positionX][enemy_Tank.positionY -1] != '*')
 {
  update = true;
  maze[enemy_Tank.positionX][enemy_Tank.positionY] = ' ';
  enemy_Tank.positionY --;
}

 if (maze[enemy_Tank.positionX-1][enemy_Tank.positionY] == '*' && maze[enemy_Tank.positionX+1][enemy_Tank.positionY] == '*' && maze[enemy_Tank.positionX][enemy_Tank.positionY -1] == '*' && maze[enemy_Tank.positionX][enemy_Tank.positionY] != maze[main_tower.positionX][main_tower.positionY])
 {
  update = true;
  maze[enemy_Tank.positionX][enemy_Tank.positionY] = ' ';
  enemy_Tank.positionX = enemy_Tank.positionX - 10;
}

 if (maze[enemy_Carry.positionX-1][enemy_Carry.positionY] != '*' )
 {
  update = true;
  maze[enemy_Carry.positionX][enemy_Carry.positionY] = ' ';
  enemy_Carry.positionX --;
}

 if(maze[enemy_Carry.positionX][enemy_Carry.positionY -1] != '*')
 {
  update = true;
  maze[enemy_Carry.positionX][enemy_Carry.positionY] = ' ';
  enemy_Carry.positionY --;
}

 if (maze[enemy_soldier.positionX+1][enemy_soldier.positionY] != '*' )
 {
  update = true;
  maze[enemy_soldier.positionX][enemy_soldier.positionY] = ' ';
  enemy_soldier.positionX ++;
 }

 if(maze[enemy_soldier.positionX][enemy_soldier.positionY -1] != '*')
{
 update = true;
 maze[enemy_soldier.positionX][enemy_soldier.positionY] = ' ';
 enemy_soldier.positionY --;

 }
 if (maze[enemy_soldier.positionX-1][enemy_soldier.positionY] == '*' && maze[enemy_soldier.positionX+1][enemy_soldier.positionY] == '*' && maze[enemy_soldier.positionX][enemy_soldier.positionY -1] == '*' && maze[enemy_soldier.positionX][enemy_soldier.positionY] != maze[main_tower.positionX][main_tower.positionY])
 {
 update = true;
 maze[enemy_soldier.positionX][enemy_soldier.positionY] = ' ';
 enemy_soldier.positionX = enemy_soldier.positionX - 15;
 }

}



return 0;

}
}

