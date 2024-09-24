#pragma once
class _Text {

	enum colour
	{
		// resets all \033 to deafult
		resetAll = 0,

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
	};

	enum backroundColour
	{
		// resets all \033 to deafult
		resetAll = 0,

		// Backround colours
		Black = 40,
		Red = 41,
		Green = 42,
		Yellow = 43,
		Blue = 44,
		Magenta = 45,
		Cyan = 46,
		White = 47,

		// Bright backround colours
		Gray = 100,
		BrightRed = 101,
		BrightGreen = 102,
		BrightYellow = 103,
		BrightBlue = 104,
		BrightMagenta = 105,
		BrightCyan = 106,
		BrightWhite = 107,
	};

	enum formatting
	{
		// resets all \033 to deafult
		resetAll = 0,

		// Formats
		Bold = 1,
		Italic = 3, // (May not be supported in all terminals)
		Underline = 4,
		Blink = 5,
		Reverse = 7, // Invert colors
		Strikethrough = 9, // May not be supported in all terminals)		
	};
};

