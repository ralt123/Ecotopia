#include <stdio.h>
#include "../includes.h"


class Inventory: public SQL {
   public:
   std::vector<std::vector<std::string>> inventory;
   int item_counter; 
   std::ofstream inv_table;

      Inventory() {
         inventory = get_vector();
         item_counter = 0;
         
      }
   
      void add_item(std::string name, std::string type, std::string stat) {
         item_counter += 1;
         std::stringstream item_num;
         item_num << item_counter;
         insert_item(item_num.str(), name, type, stat);
         inventory = get_vector();
         ascii_table_update();
      }

      void delete_item(std::string name, std::string num) {
         remove_item(name, num);
         inventory = get_vector();
         ascii_table_update();
      }

      void ascii_table_update() {
         inv_table.open("inventory.txt");
         inv_table << "//=====[]===============[]=======[]======\\\\" \
         "\n|| no. ||     Name      || Type  || Stat ||" \
         "\n|]=====[]===============[]=======[]======[|";
         // ||     ||               ||       ||      ||
         for (int i = 0; i < inventory.size(); i++) {
            inv_table << "||"+inventory[i][0]+spaces_calc(5-inventory[i][0].size())+"||"+inventory[i][1]+spaces_calc(15-inventory[i][1].size())
            +"||"+inventory[i][2]+spaces_calc(7-inventory[i][2].size())+"||"+inventory[i][3]+spaces_calc(10-inventory[i][3].size())+"||";
         }
         inv_table << "\\\\=====[]===============[]=======[]======//";
      }

      std::string spaces_calc(int num) {
         std::string spaces_string;
         for (int i = 0; i < num; i++) {
            spaces_string += " ";
         }

         return spaces_string;
      }

      void ascii_table_remove(){
         ;
      }
};

int main() {
   Inventory test;
   test.insert_item("0", "sword", "Weapon" , "20");
   test.return_table();
   test.get_vector();
   std::cout << SQL::inventory_vector[0][0];
   if (test.inventory.empty()) {
      std::cout << "FUCK";
   }
}