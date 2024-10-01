#pragma once
class Text {
public:
    // Use enum class for text colors to avoid name clashes
    enum Formatting {
        // Basic text colours
        Black = 30,
        Red = 31,
        Green = 32,
        Yellow = 33,
        Blue = 34,
        Magenta = 35,
        Cyan = 36,
        White = 37,
        // Bright text colors
        Gray = 90,
        BrightRed = 91,
        BrightGreen = 92,
        BrightYellow = 93,
        BrightBlue = 94,
        BrightMagenta = 95,
        BrightCyan = 96,
        BrightWhite = 97,

        // Background colours
        backroundBlack = 40,
        backroundRed = 41,
        backroundGreen = 42,
        backroundYellow = 43,
        backroundBlue = 44,
        backroundMagenta = 45,
        backroundCyan = 46,
        backroundWhite = 47,

        // Bright background colours
        backroundGray = 100,
        backroundBrightRed = 101,
        backroundBrightGreen = 102,
        backroundBrightYellow = 103,
        backroundBrightBlue = 104,
        backroundBrightMagenta = 105,
        backroundBrightCyan = 106,
        backroundBrightWhite = 107,

        // Formats
        Bold = 1,
        Italic = 3, // May not be supported in all terminals
        Underline = 4,
        Blink = 5,
        Reverse = 7, // Invert colors
        Strikethrough = 9, // May not be supported in all terminals

        // Resets all, duh
        ResetAll = 0
    };    
    

    // Optional: Define a reset value globally if desired
    //static const int ResetAll = 0;    
};