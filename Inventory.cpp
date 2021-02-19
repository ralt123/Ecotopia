#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <ostream>
#include <Windows.h>
#include <string>
#include <cctype>
using namespace std;

  struct Item {
    string name; //Item name.
    int slot; //Head, Torso, Hands
    int hp;
    int attack;
    int defense;
    
  };

std::ostream &operator<<(std::ostream &os, const Item& item) {
    os << item.name;
    return os;
}

int main()
{

    //Variables, Strings, etc.
    int itemcounter = 0, counter = 0;


    //"Empty" Item
    Item Empty{ "<Empty>", 0, 0, 0 };

    vector<Item> Equipment = { 100, Empty }; //Current Equipment, 10 empty slots.
    vector<Item> Inventory = { }; //Players Inventory.
    string InventorySlots[] = { "Head" "Torso", "Hands" }; //Player parts where items can be equiped.

    cout << "You check your manned maneuvering unit," << " you have:" << endl;

    for (int i = 0; i < itemcounter; i++)
    {
        cout << InventorySlots[i];
        if (Equipment[i].name == "Empty ")
        {
        cout << " " << Equipment[i] << endl << endl;
      }
    }

}
