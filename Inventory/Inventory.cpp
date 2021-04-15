#include <stdio.h>
#include "../includes.h"


class Inventory: public SQL {
   public:
   int item_counter; 
   std::ofstream inv_table;

      Inventory() {
         item_counter = SQL::inventory_vector.size();
         
      }
   
      void add_item(std::string name, std::string type, std::string stat) {
         item_counter += 1;
         std::stringstream item_num;
         item_num << item_counter;
         insert_item(item_num.str(), name, type, stat);
         ascii_table_update();
      }

      void delete_item(std::string name, std::string num) {
         remove_item(name, num);
         ascii_table_update();
      }

      void ascii_table_update() {
         if (SQL::inventory_vector.empty()) {
            std::cout << "REEEE";
            inv_table.open("inventory.txt");
            if (inv_table.is_open()) {
               inv_table << "//=====[]===============[]=======[]======\\\\" \
            "\n|| no. ||     Name      || Type  || Stat ||" \
            "\n|]=====[]===============[]=======[]======[|" \
            "\n\\\\=====[]===============[]=======[]======//";
            
            }
         }
         inv_table.open("test.txt");
         if (inv_table.is_open()) {
            std::cout << "\nWriting:";
            inv_table << "//=====[]===============[]=======[]======\\\\" \
            "\n|| no. ||     Name      || Type  || Stat ||" \
            "\n|]=====[]===============[]=======[]======[|";
            // ||     ||               ||       ||      ||
            for (int i = 0; i < SQL::inventory_vector.size(); i++) {
               inv_table << 
               "\n||"+SQL::inventory_vector[i][0]+spaces_calc(5-SQL::inventory_vector[i][0].size()) \
               +"||"+SQL::inventory_vector[i][1]+spaces_calc(15-SQL::inventory_vector[i][1].size()) \
               +"||"+SQL::inventory_vector[i][2]+spaces_calc(7-SQL::inventory_vector[i][2].size()) \
               +"||"+SQL::inventory_vector[i][3]+spaces_calc(6-SQL::inventory_vector[i][3].size()) \
               +"||";
            }
            inv_table << "\n\\\\=====[]===============[]=======[]======//";
         }
         

         else {
            std::cout << "\nWrite error!";
         }

         inv_table.close();
      }

      std::string spaces_calc(int num) {
         std::string spaces_string;
         for (int i = 0; i < num; i++) {
            spaces_string += " ";
         }

         return spaces_string;
      }

      void ascii_table_output(){
         ;
      }
};

int main() {
   Inventory test;
   test.return_table();
   test.add_item("sword", "weapon", "20");




}