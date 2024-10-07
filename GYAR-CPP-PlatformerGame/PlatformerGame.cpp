#include "PlatformerGame.h"

PlatformerGame::PlatformerGame()
{
}

void PlatformerGame::Initzialize() {
	std::cout << "\033[?25l"; // hide cursor
	// std::cout << "\033[?25h"; // show cursor
	Render();
}

void PlatformerGame::Start()
{
	Initzialize();

	// headFrame = now (last frame we drew)	
	// if (curTime - headFrame < timeFPS) wait(curTime-headFrame)
	// head + timeFPS


	while (true)
	{
		Input();
		Update();
		Render();
	}
}

void PlatformerGame::Update()
{
}

void PlatformerGame::Input() //make keys async?
{ //might be problems with key presses not registered otherwhise
	if (GetAsyncKeyState('W') & 0x8000) {
		std::cout << 'W';
	}
	if (GetAsyncKeyState('A') & 0x8000) {
		std::cout << 'A';
	}
	if (GetAsyncKeyState('S') & 0x8000) {
		std::cout << 'S';
	}
	if (GetAsyncKeyState('D') & 0x8000) {
		std::cout << 'D';
	}
	/* Why 0x8000 and why &
	* the reason for 0x8000 is becuse it's a hexadecimal representation of a binary number, as we know eatch part of information is a bit and every bit is organized in a group of 4 or nible as it's called, 8 bits or 2 nibles creates a byte
	* for every nible we can have 16 difrent values, this can be representated by a single digit of hex, therefore we use one hexa decimal per nible, and define it's hex code with the 0x first, hence 0x folowed by four zeroes is a group of 4 nibles, 16 bit or one byte, or 0x0000
	* 
	* the reason for & however.
	* & is a bitwise and and is used for comparing two bits against eatchother, one from eatch variable
	* a number like 0101 compared to something like 1100 would become 0100
	* if both numbers are 1 it's 1 else it's a zero
	* we use this in the if statment cause anything that isn't zero isn't false
	* so we enter the statment
	*/
}

void PlatformerGame::Render()
{
	Drawing::draw(player);
}

// need work