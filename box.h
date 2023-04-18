#ifndef ERESTAURANT_HEADER_H
#define ERESTAURANT_HEADER_H

#include <iostream>
#include <windows.h>

inline void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

inline void box(const std::string& text) {

    char boxTopLeft = 201;
    char boxTopRight = 187;
    char boxBottomLeft = 200;
    char boxBottomRight = 188;
    char horizontalLine = 205;
    char verticalLine = 186;

    // Define the width and height of the box
    int boxWidth = 100;
    int boxHeight = 10;

    // Draw the top of the box
    std::cout << boxTopLeft;
    for (int i = 0; i < boxWidth - 2; i++) {
        std::cout << horizontalLine;
    }
    std::cout << boxTopRight << std::endl;

    // Draw the sides of the box
    for (int i = 0; i < boxHeight - 2; i++) {
        std::cout << verticalLine;
        for (int j = 0; j < boxWidth - 2; j++) {
            // Print empty space inside the box
            std::cout << " ";
        }
        std::cout << verticalLine << std::endl;
    }

    // Draw the bottom of the box
    std::cout << boxBottomLeft;
    for (int i = 0; i < boxWidth - 2; i++) {
        std::cout << horizontalLine;
    }
    std::cout << boxBottomRight << std::endl;

    // Write text inside the box
    gotoxy(36, 12); // Position cursor at (2, 2) inside the box
    std::cout << text << std::endl;
}

#endif
