#include <windows.h>
#include <stdlib.h>
#include <string>
#include <iostream>



/*
Console Class:
    - Used to set Console settings like console size, mode, etc. ALl using the windows console API
    Refrences:
    https://docs.microsoft.com/en-us/windows/console

    *Methods:
        - Text_colour
        - Window_Size
*/


class Console {
    public:
        // Class Attributes: various windows.h structure types and variables:
        //Console HANDLEs (Input and Output Handle), DWORD used to change modes, Coordinates for console size
        HANDLE hstdin;
        HANDLE hstdout;
        DWORD  mode;
        COORD console_size;

        Console() {
            hstdin = GetStdHandle( STD_INPUT_HANDLE );
            hstdout = GetStdHandle( STD_OUTPUT_HANDLE );
            GetConsoleMode( hstdin, &mode );
            window_size(240,200);
            text_colour("green");
            console_title();
        }

        void console_title() {
            SetConsoleTitle(TEXT("Ecotopia"));
        }

        void console_mode(std::string mode_type) {
            if (mode_type == "echo") {
                SetConsoleMode( hstdin, ENABLE_ECHO_INPUT | ENABLE_PROCESSED_INPUT );
            }
            else if (mode_type == "standard") {
                SetConsoleMode( hstdin, mode ); 
            }
        }

        void text_colour(std::string colour) {
            if (colour == "green") {
                SetConsoleTextAttribute(hstdout, FOREGROUND_GREEN);
            }
            if (colour == "blue") {
                SetConsoleTextAttribute(hstdout, 0xb);
            }
        }

        void window_size(int x, int y) {
            _SMALL_RECT windowsize;
        windowsize.Top = 0; 
        windowsize.Left = 0; 
        windowsize.Bottom = y - 1; 
        windowsize.Right = x - 1;
        console_size.X = x;
        console_size.Y = y;

        SetConsoleScreenBufferSize(hstdin, console_size);
        SetConsoleWindowInfo(hstdout, TRUE, &windowsize);
        }
};




