#include <iostream>
using namespace std;
void draw(int,int);
int main()
{
cout<<"Tower defense\n";
int x; 
cout << "Type your x cordinate for tower: "; 
cin >> x;
int y; 
cout << "Type your y cordinate for tower: "; 
cin >> y;
draw(x,y);
system("pause");
}

void draw(int x, int y)
{
for(int i = 1; i < 13; i++)
  if (i < 0)
      cout<<" "<<i;
  else
      cout<<"  "<<i;
cout<<endl;

for(int i = 0; i < 9; i++)
{
cout<<(char)(i + 49);
for(int j = -6; j < 7; j++)
if(i == y - 1 && j == x)
  cout<<" x ";
else
  cout<<" . ";

cout<<(char)(i + 49)<<endl;
}
}
