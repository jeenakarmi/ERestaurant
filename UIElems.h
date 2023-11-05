#include <iostream>
#include <vector>
#include <string>
#include <string_view>
#include <Windows.h>


#ifndef UIELEMS_H
#define UIELEMS_H

inline int centerX = 0;
inline int centerY = 0;


inline void gotoxy(int x, int y)
{
        COORD coord;
        coord.X = x;
        coord.Y = y;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

inline COORD GetWindowSize()
{
        HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
        PCONSOLE_SCREEN_BUFFER_INFO lpScreenInfo = new CONSOLE_SCREEN_BUFFER_INFO();
        GetConsoleScreenBufferInfo(consoleHandle, lpScreenInfo);
        COORD windowSize = lpScreenInfo->dwSize;

        return windowSize;
}

inline void SetWindowSizeAndCentre() {

        HWND console = GetConsoleWindow();
        RECT r;

        COORD consoleSize = GetWindowSize();
        int consoleWidth = consoleSize.X;
        int consoleHeight = consoleSize.Y;
        centerX = consoleWidth / 2;
        centerY = consoleHeight / 2;
}


inline void Title(const std::string& text, int paddingY)
{
        COORD consoleSize = GetWindowSize();
        int consoleWidth = consoleSize.X;
        int consoleHeight = consoleSize.Y;

        int textWidth = text.length();
        int paddingX = (consoleWidth - textWidth) / 2;

        gotoxy(paddingX, paddingY);
        std::cout << text << std::endl;
}

inline void MenuItems(std::vector<std::string_view> options)
{
        int longestStrLen = 0;
        for (std::string_view option : options)
        {
                if (option.length() > longestStrLen) longestStrLen = option.length();
        }

        COORD consoleSize = GetWindowSize();
        int consoleWidth = consoleSize.X;
        int consoleHeight = consoleSize.Y;

        int paddingX = (consoleWidth - longestStrLen) / 2;
        int startX = paddingX;

        int startY = centerY - options.size() / 2;

        for (std::string_view option : options)
        {
                gotoxy(startX, startY++);
                std::cout << option << '\n';
        }
}
#endif // !UIELEMS_H
