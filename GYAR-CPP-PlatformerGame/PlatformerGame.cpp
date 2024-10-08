#include "PlatformerGame.h"

PlatformerGame::PlatformerGame()
{
}

void PlatformerGame::Initzialize() {
	std::cout << "\033[?25l"; // hide cursor
	// std::cout << "\033[?25h"; // show cursor

	// set the mapp
	for (int x = 0; x < 64; x++) {
		this->mapp[x][16] = Block('=', Text::Green, x, 16);
	}
	for (int x = 8; x < 12; x++) {
		this->mapp[x][13] = Block('=', Text::Green, x, 13);
	}

	Render();
}

void PlatformerGame::Start()
{
	Initzialize();

	while (running)
	{
		Input();
		Update();
		Render();

		std::this_thread::sleep_for(std::chrono::milliseconds(500)); // tmp framerate limiter
	}
}

void PlatformerGame::Update()
{
	move(player); // move player
	std::cout << "Px:" << player.x << ":" << player.y << ";"; // debug player position
	// collition check with enemy
}

void PlatformerGame::Input() //make keys async? (this is now assync)
{ //might be problems with key presses not registered otherwhise	
	player.states &= ~0b00001111; // resets the movment state

	if (GetAsyncKeyState('W') & 0x8000) {
		player.states |= player.W;
	}
	if (GetAsyncKeyState('A') & 0x8000) {
		player.states |= player.A;
	}
	if (GetAsyncKeyState('S') & 0x8000) {
		player.states |= player.S;
	}
	if (GetAsyncKeyState('D') & 0x8000) {
		player.states |= player.D;
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
	for (int y = 0; y < 16; y++) {
		for (int x = 0; x < 64; x++) {
			Drawing::draw(mapp[x][y]);
		}
	}
}



void PlatformerGame::move(Entity& entity) { 
	// debug:
	std::cout << "JT:" << ((entity.states >> 6) & 0b11) << ";iG:" << (entity.states & entity.isGrounded)
		<< ";iJ:" << (entity.states & entity.isJump) << ";";
	// 

	// is grounded check
	if (mapp[entity.x][entity.y + 1].getTexture() == '=')
		entity.states |= entity.isGrounded;
	else entity.states &= ~entity.isGrounded;

	//Jump time needs to be more consistent

	// 1. stop jumping if W and jumping
	if (!(entity.states & entity.W) && (entity.states & entity.isJump)) {
		entity.states &= ~entity.isJump; // clears the isJump flag
		entity.states = (entity.states & ~entity.jumpTime); // clears bits 6 and 7
	}
	
	// 2. if not grounded and not jumping, fall down
	else if (!(entity.states & entity.isGrounded) && !(entity.states & entity.isJump)) {
		if (mapp[entity.x][entity.y + 1].getTexture() == '=') {
			entity.states |= entity.isGrounded; // sets the isGrounded flag
		}
		else {
			entity.y++; // fall
		}
	}	
	
	// 3. begin jumping if w is pressed and player is on ground and the sky is clear above
	else if (entity.states & entity.W && (entity.states & entity.isGrounded)) {
		if (mapp[entity.x][entity.y - 1].getTexture() != '=') {
			entity.states |= entity.isJump;          // sets the isJump flag
			entity.states &= ~entity.isGrounded;     // clear the isGrounded flag
			entity.y--;                    // move up
			entity.states = (entity.states & ~entity.jumpTime) | (1 << 6); // set jumpTime to 1
		}
		else entity.states &= ~entity.isJump;
	}

	// 4. continue jump if w is still pressed and jumpTime is less than 3
	else if (entity.states & entity.W && (entity.states & entity.isJump)) {
		// I really wanna remove this uint8_t initialisation cause it wastes a entire byte of memory << removed
		//uint8_t jumpTime = (entity.states >> 6) & 0b11; // extract jumpTime
		// ^^ that code above is a clear example of wasting resorses, using a whole byte for no reason. And additional overhead for the construction and deconstruction :<
		if (((entity.states >> 6) & 0b11) < 3 && mapp[entity.x][entity.y - 1].getTexture() != '=') {
			entity.y--; // Move up
			entity.states = (entity.states & ~entity.jumpTime) | (((entity.states >> 6) & 0b11) + 1) << 6; // increment jumpTime directly now like it allways should've been
		}
		else {
			entity.states &= ~entity.isJump; // Stop jumping if max height is reached or blocked
		}
	}

	// Left & Right
	if (entity.states & entity.A && !(entity.states & entity.D)) {
		if (mapp[entity.x - 1][entity.y].getTexture() != '=') // colition check
			entity.x--;
	}
	else if (!(entity.states & entity.A) && entity.states & entity.D) {
		if (mapp[entity.x + 1][entity.y].getTexture() != '=') // colition check
			entity.x++;
	}	
}

// need work
// a better way of doing the collition checks than checking textures...