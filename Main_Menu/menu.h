#ifndef MENU_H
#define MENU_H
#include <iostream>
#include <conio.h>
#include <fstream>
#include <string>
#include <array>
#include <vector>
#include <cstring> 
using namespace std;

class difficulty_data //difficulty from 1-7 , make object then call get_dif() for difficulty level
{
private:
    static int diff;
public:
    friend int menu_function();

    int get_dif() {
        return diff;
    }
    
    int get_multiplier() {
        switch (diff) {
        case 1:
            return 0.5;
        case 2:
            return 0.75;
        case 3:
            return 1;
        case 4:
            return 1.5;
        case 5:
            return 2;
        case 6:
            return 4;
        case 7:
            return 10;
        }
    }


};

int difficulty_data::diff;

class settings_data 
{
private:
    static string player_name;
    static string player_colour;
    static char player_character;
    static int animation_speed ;
    static std::vector<int> screen_size;
    static string save_directory;

public:
    friend void sortdata(int setting, string input,bool file);

    string get_player_name() {
        return player_name;
    }
    string get_player_colour() {
        return player_colour;
    }
    char get_player_character() {
        return player_character;
    }
    int get_animation_speed() {
        return animation_speed;
    }
    std::vector<int> get_screen_size() {
        return screen_size;
    }
    string get_save_directory() {
        return save_directory;
    }

};

string settings_data::player_name;
string settings_data::player_colour;
char settings_data::player_character;
int settings_data::animation_speed;
vector<int> settings_data::screen_size = {200,600};
string settings_data::save_directory;

void sortdata(int setting, string input, bool file) {//cleans the data
    settings_data d;
    char arr[3];
    char ch;
    string temp = "";
    string num = "";
    int num1;
    int num2;
    vector<int> size = { 0,1 };
    switch (setting) {
    case 0:
        if (file) {
            d.player_name = input;
        }
        else {
            for (int i = 0; i < input.length() - 1; i++) {
                temp += input[i];
            }
            d.player_name = temp;
        }

        break;
    case 1:
        if (file) {
            d.player_colour = input;
        }
        else {
            for (int i = 0; i < input.length() - 1; i++) {
                temp += input[i];
            }
            d.player_colour = temp;
        }
        break;
    case 2:
        strcpy_s(arr, input.c_str());
        ch = arr[0];
        d.player_character = ch;
        break;
    case 3:
        d.animation_speed = stoi(input);
        break;
    case 4:
        for (int i = 0; i < input.length(); i++) {
            try {
                temp = input[i];
                stoi(temp);
                num += temp;
            }
            catch (exception) {
                num1 = stoi(num);
                num = "";
            }
        }
        num2 = stoi(num);
        size[0] = num1;
        size[1] = num2;
        d.screen_size = size;
        break;
    case 5:
        d.save_directory = input;
        break;

    }

}

void default_settings() {
    settings_data d;
    ofstream myfile;
    myfile.open("settings.txt");
    myfile << "Degenerate Cabbage" << endl;
    myfile << "green" << endl;
    myfile << "@" << endl;
    myfile << "1" << endl;
    myfile << "200 600" << endl;
    myfile << "C:/User/" << endl;
    myfile.close();
}

void load_settings() {
    begin:
    int count = 0;
    string line;
    ifstream myfile("settings.txt");
    while (getline(myfile, line))
    {
        if (line == "") {
            myfile.close();
            default_settings();
            goto begin;
        }
        sortdata(count,line,true);
        count += 1;
    }
    myfile.close();
}

void store_settings() {
    settings_data d;
    ofstream myfile;
    myfile.open("settings.txt");
    myfile << d.get_player_name() << endl;
    myfile << d.get_player_colour() << endl;
    myfile << d.get_player_character() << endl;
    myfile << d.get_animation_speed() << endl;
    myfile << d.get_screen_size()[0]<< " " << d.get_screen_size()[1] << endl;
    myfile << d.get_save_directory() << endl;
    myfile.close();
 
}

void correct_settings(int setting,string value) {
    sortdata(setting, value,false);
    store_settings();
}

void header1() {
    string header[9] = {
                    "               8888888888 .d8888b.   .d88888b. 88888888888 .d88888b.  8888888b. 8888888        d8888 ",
                    "               888       d88P  Y88b d88P' 'Y88b    888    d88P' 'Y88b 888   Y88b  888         d88888 ",
                    "               888       888    888 888     888    888    888     888 888    888  888        d88P888 ",
                    "               8888888   888        888     888    888    888     888 888   d88P  888       d88P 888 ",
                    "               888       888        888     888    888    888     888 8888888P'   888      d88P  888 ",
                    "               888       888    888 888     888    888    888     888 888         888     d88P   888 ",
                    "               888       Y88b  d88P Y88b. .d88P    888    Y88b. .d88P 888         888    d8888888888 ",
                    "               8888888888 'Y8888P'   'Y88888P'     888     'Y88888P'  888       8888888 d88P     888",
                   };
    
    for (int i = 0; i < 5; i++) {
        cout << endl;

    }
    
    
    for (int i = 0; i < 9; i++) {
        cout << endl;
        cout << header[i];

    }
    cout << endl;
    cout << endl;
    cout << endl;
}

void header2() {
    cout << endl;
    string header[3] = {"                                              /////////////////////",
                        "                                              //// DIFFICULTY /////",
                        "                                              /////////////////////" };
    for (int i = 0; i < 3; i++) {
        cout << endl;
        cout << header[i];
         
    }
    
    cout << endl;
    cout << endl;
}

void settings_header() {
    string options[6][3] = { {"                                                  ","player name ","<"},
                          {"                                                 ","player colour  "," "},
                          {"                                               ","player character "," "},
                          {"                                                ","animation speed  "," "},
                          {"                                                  ","screen size "," "},
                          {"                                                 ","save directory  "," "} };
    settings_data d;
    for (int i = 0; i < 6; i++) {
        cout << endl;
        cout << options[i][1];
        cout << " : ";
        switch(i) {
        case 0:
            cout << d.get_player_name();
            break;
        case 1:
            cout << d.get_player_colour();
            break;
        case 2:
            cout << d.get_player_character();
            break;
        case 3:
            cout << d.get_animation_speed();
            break;
        case 4:
            cout<<d.get_screen_size()[0] << " X " << d.get_screen_size()[1];
            break;
        case 5:
            cout << d.get_save_directory();
            break;
        }

    }
}

std::array<int, 2> navigation(string fields[][3],int rows,int header_num) {
    int in = 0;
    char letter = 'o';
    std::array<int, 2> cursor = { 0,2 };
    for (int i = 0; i < rows; i++) {
        if (fields[i][2] == "<") {
            cursor = {i,2};
        }
    }
    while (in != 13) {//13 is enter key
        switch(header_num) {
        case 1:
            header1();
            break;
        case 2:
            header2();
            break;
        case 3:
            settings_header();
            break;
        }
        for (int i = 0; i < rows; i++) {
            cout << endl;
            for (int ii = 0; ii < sizeof(fields[0]) / sizeof(fields[0][0]); ii++) {
                cout << fields[i][ii];
            }
        }
        if (in == 8) {
            cout << "back" << endl;
        }
        //cout<<cursor[0]<<cursor[1] << endl;
        cout << endl;
        letter = _getch();
        in = letter; 
        cout << letter;
        if (letter == 's' && cursor[0] + 1 < rows)
        {
            fields[cursor[0]][cursor[1]] = " ";
            cursor[0] += 1;
            fields[cursor[0]][cursor[1]] = "<";
        }
        else if (letter == 'a' && cursor[1] - 2 > 0)
        {
            fields[cursor[0]][cursor[1]] = " ";
            cursor[1] -= 2;
            fields[cursor[0]][cursor[1]] = "<";
        }
        else if (letter == 'w' && cursor[0] - 1 > -1)
        {
            fields[cursor[0]][cursor[1]] = " ";
            cursor[0] -= 1;
            fields[cursor[0]][cursor[1]] = "<";
        }
        else if (letter == 'd' && cursor[1] + 2 < sizeof(fields[0]) / sizeof(fields[0][0]))
        {
            fields[cursor[0]][cursor[1]] = " ";
            cursor[1] += 2;
            fields[cursor[0]][cursor[1]] = "<";
        }
        system("CLS");
        if (in == 8) {
            return { -1,-1 };
        }
    }
    return cursor;
}


std::array<int, 2> settings(string fields[][3], int rows, int setting) {
    int in = 0;
    char letter = 'o';
    int lim = 5;
    int count = 0;
    int out1 ;  //for handling output
    string out2 ;
    int out3 ;
    string input="";
    string placeholder = "";
    vector<string> screensize;
    std::array<string, 6> colours = {"white","red","blue","grey","green","aqua"};
    bool valid_input = true;
    std::array<int, 2> cursor = { 0,2 };
    while (in != 13) {//13 is enter key
        settings_header();
        for (int i = 0; i < rows; i++) {
            cout << endl;
            for (int ii = 0; ii < sizeof(fields[0]) / sizeof(fields[0][0]); ii++) {
                cout << fields[i][ii];
                if (i == setting && ii == 2) {
                    if (setting == 4) {
                        if (screensize.end() - screensize.begin() == 1) {
                            cout << " : " << screensize[0] << " X " << input;
                            
                        }
                        else {
                            cout << " : " << input;
                        } 
                    }
                    else {
                        cout << " : " << input;
                        count += 1;
                    }
                    
                    
                }

                out:
                {}
            }
        }

        cout << endl;
        letter = _getch();        
        input = input + letter;
        in = letter;
        if (in == 13 && setting == 4) {
            if (screensize.end()-screensize.begin()!=2) {
                for (int i = 0; i < input.length() - 1; i++) {
                    placeholder += input[i];
                }
                screensize.push_back(placeholder);
                placeholder = "";
                input = ""; 
                in = 0;
            }
            if (screensize.end() - screensize.begin() == 2) {
                in = 13;//exits
                out1 = stoi(screensize[0]);
                out2 = " X ";
                out3 = stoi(screensize[1]);

            }
        }
        if (in == 32 && setting == 4) {
            if (screensize.end() - screensize.begin() != 2) {
                for (int i = 0; i < input.length() - 1; i++) {
                    placeholder += input[i];
                }
                screensize.push_back(placeholder);
                placeholder = "";
                input = "";
                in = 0;
            }
            if(screensize.end() - screensize.begin() == 2) {
                in = 13;//exits
                out1 = stoi(screensize[0]);
                out2 = " X ";
                out3 = stoi(screensize[1]);
            }
        }
        
        if (in == 8) {//8 is backspace
            system("CLS");
            return {-1,-1};
        }
        cout << letter;
        system("CLS");
    }
    switch (setting) {
    case 0:
        valid_input = true;
        break;
    case 1:
        valid_input = false;
        placeholder = "";
        for (int i = 0; i < input.length() - 1; i++) {
            placeholder += input[i];
        }
        for (int i = 0; i < colours.end() - colours.begin(); i++) {
            if (placeholder == colours[i]) {
                valid_input = true;
            }
        }
        if (valid_input==false) {
            cout << "colour not available";
        }
        break;
    case 2:
        if (input.length() != 2) {//includes the enter key so 2
            valid_input = false;
            cout << "Invalid" << endl;
        }
        break;
    case 3:
        try {
            stoi(input);
        }
        catch (exception) {
            cout << "Invalid";
            valid_input = false;
        }
        break;
    case 4:
        try {
            stoi(screensize[0]);
            stoi(screensize[1]);
        }
        catch (exception) {
            cout << "Invalid";
            valid_input = false;
        }
        break;
    case 5:
        valid_input = true;
        break;

    }
    if (valid_input) {       
        if (setting == 4) {
            cout << "changed " << fields[setting][1] << "to :" << out1 << out2 << out3;
            input = screensize[0] + " " + screensize[1];
        }
        else {
            cout << "changed " << fields[setting][1] << "to :" << input;
        }
        sortdata(setting, input,false);
    }
    return cursor;
}





int menu_function()
{
    load_settings();
    int in=0;
    char letter='o';
    int difficulty_level = 1;
    int rows;
    std::array<int, 2> cursor = {1,1};
    



    menu:
    store_settings();

    string main_menu[3][3] = { {"                                                   ","Start ","<"},
                              {"                                                 ","difficulty "," "},
                            {"                                                  ","options "," "} };

    string difficulty[7][3] ={{"                                                  ","baby mode ","<"},
                              {"                                                     ","easy "," "},
                              {"                                                    ","normal "," "},
                              {"                                                     ","hard "," "},
                              {"                                                  ","very hard "," "},
                              {"                                                   ","big oof "," "},
                              {"                                          ","intense pscological torture "," "}};

    string options[6][3] = {  {"                                                  ","player name ","<"},
                              {"                                                 ","player colour  "," "},
                              {"                                               ","player character "," "},
                              {"                                                ","animation speed  "," "},
                              {"                                                  ","screen size "," "},
                              {"                                                 ","save directory  "," "}};


    
    cursor = navigation(main_menu, size(main_menu),1);
    if (cursor[0] == -1) {
        goto menu;
    }


    switch (cursor[0]) {
    case 0 :
        cout << "buckle up shit nugget" << endl;
        //start game
        break;
    case 1:
        cursor = navigation(difficulty, size(difficulty),2);
        if (cursor[0] == -1) {
            goto menu;
        }
        difficulty_level = cursor[0];
        cout << "changed to difficulty level : " << difficulty[difficulty_level][1] ;
        difficulty_data d;
        d.diff = difficulty_level + 1;
        goto menu;
        break;
    case 2:
        nav:
        cursor = { 0,2 };
        cursor = navigation(options, size(options), 3);
        if (cursor[0] == -1) {
            goto menu;
        }
        settings(options, size(options),cursor[0]);
        goto nav;
        
        break;
    }
    
    cout << cursor[0]<<cursor[1]<<endl;

    return 0;
}
#endif
