#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Item
{
public:
  string name;
  int weight;
  int value;

  Item(string n, int w, int v) : name(n), value(v), weight(w) {}

  virtual void print(void) {}
};

class Weapon : public Item
{
public:
  int damage;

  Weapon(int d, string n, int w, int v) :damage(d), Item(n, w, v) {}

  void print(void) {std::cout << "\t" "\e[1m" "---" <<  name << "---" "\n" << "\e[0m" "Weight: "  << weight << "\n" << "Value: " << value << "\n" << "Damge: " << damage << "\n" << "\n" << endl; }
};

class Weapon1 : public Item
{
public:
  int damage;

  Weapon1(int d, string n, int w, int v) :damage(d), Item(n, w, v) {}

  void print(void) {std::cout << "\t" "\e[1m" "---" <<  name << "---" "\n" << "\e[0m" "Weight: "  << weight << "\n" << "Value: " << value << "\n" << "Damge: " << damage << "\n" << "\n" << endl; }
};

class Weapon2 : public Item
{
public:
  int damage;

  Weapon2(int d, string n, int w, int v) :damage(d), Item(n, w, v) {}

  void print(void) {std::cout << "\t" "\e[1m" "---" <<  name << "---" "\n" << "\e[0m" "Weight: "  << weight << "\n" << "Value: " << value << "\n" << "Damge: " << damage << "\n" << "\n" << endl; }
};

class Weapon3 : public Item
{
public:
  int damage;

  Weapon3(int d, string n, int w, int v) :damage(d), Item(n, w, v) {}

  void print(void) {std::cout << "\t" "\e[1m" "---" <<  name << "---" "\n" << "\e[0m" "Weight: "  << weight << "\n" << "Value: " << value << "\n" << "Damge: " << damage << "\n" << "\n" << endl; }
};


class Armor : public Item
{

public:
  int armour;
  
  Armor(int p, string n, int w, int v) :armour(p), Item(n,w,v) {};
  
  void print(void) { std::cout << "\t" "\e[1m" "---" <<  name << "---"  "\n" << "\e[0m" "Weight: "  << weight << "\n" << "Value: " << value << "\n" << "Protection: " << armour << "\n" << "\n" << endl; }
 };


class Armor1 : public Item
{

public:
  int armour;
  
  Armor1(int p, string n, int w, int v) :armour(p), Item(n,w,v) {};
  
  void print(void) { std::cout << "\t" "\e[1m" "---" <<  name << "---"  "\n" << "\e[0m" "Weight: "  << weight << "\n" << "Value: " << value << "\n" << "Protection: " << armour << "\n" << "\n" << endl; }
 };


class Armor2 : public Item
{

public:
  int armour;
  
  Armor2(int p, string n, int w, int v) :armour(p), Item(n,w,v) {};
  
  void print(void) { std::cout << "\t" "\e[1m" "---" <<  name << "---"  "\n" << "\e[0m" "Weight: "  << weight << "\n" << "Value: " << value << "\n" << "Protection: " << armour << "\n" << "\n" << endl; }
 };


class Heals : public Item
{

public:
  int heals;
  
  Heals(int p, string n, int w, int v) :heals(p), Item(n,w,v) {};
  
  void print(void) { std::cout << "\t" "\e[1m" "---" <<  name << "---"  "\n" << "\e[0m" "Weight: "  << weight << "\n" << "Value: " << value << "\n" << "Health Gain: " << heals << "\n" << "\n" << endl; }
 };


class Inventory
{
public:
  vector<Item*> items;
};

int main(void)
{
  Inventory myInventory;
  Item *myWeapon = new Weapon(25, "Phaser",  2, 1);
  Item *myWeapon1 = new Weapon(50, "Laser Rifle",  2, 30);
  Item *myWeapon2 = new Weapon(100, "Plasma Blaster",  5, 100);
  Item *myWeapon3 = new Weapon(300, "xX-Death Ray-Xx",  10, 500);
  Item *myArmor = new Armor(50, "ARMOUR PLATE",  0, 10);
  Item *myArmor1 = new Armor(50, "HELMET",  0, 10);
  Item *myArmor2 = new Armor(250, "Praetor Suit",  0, 200);
  Item *myHeals = new Heals(50, "Medical Syringe",  1, 10);
  myInventory.items.push_back(myWeapon);
  myInventory.items.push_back(myWeapon1);
  myInventory.items.push_back(myWeapon2);
  myInventory.items.push_back(myWeapon3);
  myInventory.items.push_back(myArmor);
  myInventory.items.push_back(myArmor1);
  myInventory.items.push_back(myArmor2);
  myInventory.items.push_back(myHeals);
  

  for (int i = 0; i < myInventory.items.size(); i++)
     myInventory.items[i]->print();

  for (int i = 0; i < myInventory.items.size(); i++)
    delete myInventory.items[i];

  return 0;
}