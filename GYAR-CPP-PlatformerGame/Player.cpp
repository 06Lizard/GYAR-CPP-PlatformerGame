#include "Player.h" 
// Might need work

short Player::getHealth() const
{
    return health;
}

void Player::Update() {	
	Input();
	Move();	
	Collision();
}

void Player::Input() //make keys async? (this is now assync)
{ //might be problems with key presses not registered otherwhise	
	states &= ~0b00001111; // resets the movment state

	if ((GetAsyncKeyState('W') & 0x8000) || (GetAsyncKeyState(VK_UP) & 0x8000)) {
		states |= Up;
	}
	if ((GetAsyncKeyState('A') & 0x8000) || (GetAsyncKeyState(VK_LEFT) & 0x8000)) {
		states |= Left;
	}
	if ((GetAsyncKeyState('S') & 0x8000) || (GetAsyncKeyState(VK_DOWN) & 0x8000)) {
		states |= Down;
	}
	if ((GetAsyncKeyState('D') & 0x8000) || (GetAsyncKeyState(VK_RIGHT) & 0x8000)) {
		states |= Right;
	}
	// Why 0x8000 and why &
	//* the reason for 0x8000 is becuse it's a hexadecimal representation of a binary number, as we know eatch part of information is a bit and every bit is organized in a group of 4 or nible as it's called, 8 bits or 2 nibles creates a byte
	//* for every nible we can have 16 difrent values, this can be representated by a single digit of hex, therefore we use one hexa decimal per nible, and define it's hex code with the 0x first, hence 0x folowed by four zeroes is a group of 4 nibles, 16 bit or one byte, or 0x0000
	//* 
	//* the reason for & however.
	//* & is a bitwise and and is used for comparing two bits against eatchother, one from eatch variable
	//* a number like 0101 compared to something like 1100 would become 0100
	//* if both numbers are 1 it's 1 else it's a zero
	//* we use this in the if statment cause anything that isn't zero isn't false
	//* so we enter the statment
}

//some way to move this into entity or player / enemy itself would be good so we can remove the const uints from entity when typing player, would look nicer
void Player::Move() {
	// debug:
	//std::cout << "JT:" << ((entity.states >> 6) & 0b11) << ";iG:" << (entity.states & entity.isGrounded) << ";iJ:" << (entity.states & entity.isJump) << ";";
	// 
	
	// is grounded check
	if (BlockManager::getCollision(mapp->mapp[x][y + 1]))
		states |= isGrounded;
	else states &= ~isGrounded;

	//Jump time needs to be more consistent

	// 1. stop jumping if W and jumping
	if (!(states & Up) && (states & isJump)) {
		states &= ~isJump; // clears the isJump flag
		states = (states & ~jumpTime); // clears bits 6 and 7
	}

	// 2. if not grounded and not jumping, fall down
	else if (!(states & isGrounded) && !(states & isJump)) {
		if (BlockManager::getCollision(mapp->mapp[x][y + 1])) {
			states |= isGrounded; // sets the isGrounded flag
		}
		else {
			y++; // fall
		}
	}

	// 3. begin jumping if w is pressed and player is on ground and the sky is clear above
	else if (states & Up && (states & isGrounded)) {
		if (!BlockManager::getCollision(mapp->mapp[x][y - 1])) {
			states |= isJump;          // sets the isJump flag
			states &= ~isGrounded;     // clear the isGrounded flag
			y--;                    // move up
			states = (states & ~jumpTime) | (1 << 6); // set jumpTime to 1
		}
		else states &= ~isJump;
	}

	// 4. continue jump if w is still pressed and jumpTime is less than 3
	else if (states & Up && (states & isJump)) {
		// I really wanna remove this uint8_t initialisation cause it wastes a entire byte of memory << removed
		//uint8_t jumpTime = (entity.states >> 6) & 0b11; // extract jumpTime
		// ^^ that code above is a clear example of wasting resorses, using a whole byte for no reason. And additional overhead for the construction and deconstruction :<
		if (((states >> 6) & 0b11) < 3 && !BlockManager::getCollision(mapp->mapp[x][y - 1])) {
			y--; // Move up
			states = (states & ~jumpTime) | (((states >> 6) & 0b11) + 1) << 6; // increment jumpTime directly now like it allways should've been
		}
		else {
			states &= ~isJump; // Stop jumping if max height is reached or blocked
		}
	}

	// Left & Right
	if (states & Left && !(states & Right)) {
		if (x > 0 && !BlockManager::getCollision(mapp->mapp[x - 1][y])) // colition check & border
			x--;
	}
	else if (!(states & Left) && states & Right) {
		if (x < mapp->width-1 && !BlockManager::getCollision(mapp->mapp[x + 1][y])) // colition check & border
			x++;
	}
}
// need work
// a better way of doing the collition checks than checking textures...

void Player::Collision() 
{
	char block = mapp->mapp[x][y];
	if (block && (BlockManager::getType(block) == BlockManager::flag || BlockManager::getType(block) == BlockManager::flagPole)) // if player is on flag
	{
		//while (dynamic_cast<FlagPole*>(mapp->mapp[x][y-1])) {
		//	y--;
		//	//score ++;
		//	//lower flag
		//	//render
		//}
		mapp->LvLFinished();
	}
	
	///*tmp*/mapp->mapp[x][y]->Update();
}