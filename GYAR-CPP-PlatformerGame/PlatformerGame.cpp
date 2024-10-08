#include "PlatformerGame.h"

PlatformerGame::PlatformerGame()
{
}

void PlatformerGame::Initzialize() {
	std::cout << "\033[?25l"; // hide cursor
	// std::cout << "\033[?25h"; // show cursor

	// set the mapp
	for (int i = 0; i < 64; i++) {
		this->mapp[i][16] = Block('=', Text::Green, i, 16);
	}
	
	
	//if (mapp[player.x][player.y - 1].getTexture() == '=') { // some better way of finding if it's ground or not would be great...
	//	player.isGrounded;
	//}
	//else !player.isGrounded;
	//if (mapp[player.x][player.y + 1].getTexture() == '=') { // some better way of finding if it's ground or not would be great...
	//	!player.isSkyClear;
	//}
	//else player.isSkyClear;

	// lastly
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

		//std::this_thread::sleep_for(std::chrono::milliseconds(100)); // tmp framerate limiter
	}
}

void PlatformerGame::Update()
{
	move(player, movementState); // move player
	std::cout << "Px:" << player.x << ":" << player.y << ";"; // debug player position
	// collition check with enemy
}

void PlatformerGame::Input() //make keys async? (this is now assync)
{ //might be problems with key presses not registered otherwhise	
	movementState = 0; // resets the movment state

	if (GetAsyncKeyState('W') & 0x8000) {
		movementState |= W;
	}
	if (GetAsyncKeyState('A') & 0x8000) {
		movementState |= A;
	}
	if (GetAsyncKeyState('S') & 0x8000) {
		movementState |= S;
	}
	if (GetAsyncKeyState('D') & 0x8000) {
		movementState |= D;
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
	for (int i = 0; i < 64; i++) {
		Drawing::draw(mapp[i][0]);
	}
}



void PlatformerGame::move(Entity& entity, uint8_t& movementState) {
	// is sky clear check
	if (mapp[entity.x][entity.y - 1].getTexture() == '=')
		entity.isSkyClear = false;
	else entity.isSkyClear = true;

	// is grounded check
	if (mapp[entity.x][entity.y + 1].getTexture() == '=')
		entity.isGrounded = true;
	else entity.isGrounded = false;

	//Jump time needs to be more consistent

	// 1. stop jumping if W and jumping
	if (!(movementState & W) && entity.isJump) {
		entity.jumpTime = 0;           // Reset jump time
		entity.isJump = false;         // Stop jump
	}
	
	// 2. if not grounded and not jumping, fall down
	else if (!entity.isGrounded && !entity.isJump) {
		if (mapp[entity.x][entity.y + 1].getTexture() == '=') { // checked if on ground
			entity.isGrounded = true;  
		}
		else {
			entity.y++; // fall
		}
	}
	
	// 3. begin jumping if w is pressed and player is on ground and the sky is clear above
	else if (movementState & W && entity.isGrounded && entity.isSkyClear) {
		entity.isJump = true;
		entity.isGrounded = false;
		entity.y--;
		entity.jumpTime++;
	}

	// 4. continue jump if w is still pressed and jumpTime is less than 3
	else if (movementState & W && entity.isJump) {
		if (entity.jumpTime < 3) {
			if (entity.isSkyClear) {
				entity.y--;
				entity.jumpTime++;
			}
			else {
				entity.isJump = false; // sky blocked
			}
		}
		else {
			entity.isJump = false; // jumpTime to large
		}
	}

	// Left & Right
	if (movementState & A && !(movementState & D)) {
		if (mapp[entity.x - 1][entity.y].getTexture() != '=') // colition check
			entity.x--;
	}
	else if (!(movementState & A) && movementState & D) {
		if (mapp[entity.x + 1][entity.y].getTexture() != '=') // colition check
			entity.x++;
	}	
}

// need work
// a better was of doing the collition checks then checking textures...