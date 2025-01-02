#include "PlatformerGame.h"

void PlatformerGame::Initzialize() {
	std::cout << "\033[?25l"; // hide cursor
	// std::cout << "\033[?25h"; // show cursor

	// Clean up
	for (Entity* entity : entities)
	{
		delete entity;
	}

	// set player pos
	player.x = 10;
	player.y = 10;

	// set camera pos
	cameraPos.x = player.x;
	cameraPos.y = 1;
	UpdateCamera();
	
	// set the mapp
	mapp.Start();
	//for (int x = 0; x < mapp.width; x++) {
	//	mapp.mapp[x][screenHight] = Block('=', Text::Green, true);
	//}
	//for (int x = 8; x < 12; x++) {
	//	mapp.mapp[x][13] = Block('=', Text::Green, true);
	//}
	//mapp.mapp[3][screenHight-1] = Block('=', Text::Green, true);
	///*flag*/for (short y = screenHight - 5; y < screenHight; y++) {
	//	mapp.mapp[mapp.width - 1][y] = FlagPole();
	//}
	//mapp.mapp[mapp.width-1][screenHight-5] = Flag();
	
	//entities.push_back(new Enemy1(5, 5, &mapp));
	entities.push_back(&enemy1);
}

void PlatformerGame::Start()
{
	Initzialize();

	std::cout << "enemy stats:\tcolour " << enemy1.getColour() << "\ttexture: " << enemy1.getTexture() << "\tHP:" << enemy1.getHealth();
	while (running)
	{		
		//std::cout << "\033[" << enemy1.y << ";" << enemy1.x << "H\033[" << enemy1.getColour() << "m" << enemy1.getTexture();
		//Input();
		Render();
		Update();
		//std::cout << "\033[" << 15 << ";" << 0 << "H\033[" << player.getColour() << "m" << player.getTexture();
				
		std::this_thread::sleep_for(std::chrono::milliseconds(10)); // tmp framerate limiter
	}
}

void PlatformerGame::Update()
{
	//move(player);
	player.Update();

	UpdateCamera();

	for (Entity* entity : entities)
	{
		entity->Update();  // polymorphic call
	}

	//std::cout << "Px:" << player.x << ":" << player.y << ";"; // debug player position
	// collition check with enemy
}

/*void PlatformerGame::Input() //make keys async? (this is now assync)
{ //might be problems with key presses not registered otherwhise	
	player.states &= ~0b00001111; // resets the movment state

	if ((GetAsyncKeyState('W') & 0x8000) || (GetAsyncKeyState(VK_UP) & 0x8000)) {
		player.states |= player.Up;
	}
	if ((GetAsyncKeyState('A') & 0x8000) || (GetAsyncKeyState(VK_LEFT) & 0x8000)) {
		player.states |= player.Left;
	}
	if ((GetAsyncKeyState('S') & 0x8000) || (GetAsyncKeyState(VK_DOWN) & 0x8000)) {
		player.states |= player.Down;
	}
	if ((GetAsyncKeyState('D') & 0x8000) || (GetAsyncKeyState(VK_RIGHT) & 0x8000)) {
		player.states |= player.Right;
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
}*/

void PlatformerGame::Render() {
	short worldX;
	short worldY;
	for (short y = 0; y < screenHight; y++) {
		for (short x = 0; x < screenWidth; x++) {
			// move out for efichency !?
			worldX = x + cameraPos.x;
			worldY = y + cameraPos.y;

			if (player.x != worldX || player.y != worldY) {
				for (Entity* entity : entities) /*test3*/
				{
					if (entity->x == worldX && entity->y == worldY)
						std::cout << "\033[" << y + 1 << ";" << x + 1 << "H\033[" << entity->getColour() << "m" << entity->getTexture();
					else 
						std::cout << "\033[" << y + 1 << ";" << x + 1 << "H\033[" << mapp.mapp[worldX][worldY]->getColour() << "m" << mapp.mapp[worldX][worldY]->getTexture();
				}
				/*debug camera pos*/
				//std::cout << "\033[" << cameraPos.y+1 << ";" << cameraPos.x+1 << "H\033[" << Text::backroundBlue << "mC\033[0m";
				/*test3->cmented*///std::cout << "\033[" << y+1 << ";" << x+1 << "H\033[" << mapp.mapp[worldX][worldY].getColour() << "m" << mapp.mapp[worldX][worldY].getTexture();
			}
			else {			
				std::cout << "\033[" << y+1 << ";" << x+1 << "H\033[" << player.getColour() << "m" << player.getTexture();			
				//std::cout << "\033[25;10HXY" << x << ";" << y;
			}
		}
	}// some weird bug where y 0 dosnt get drawn, it starts drawing y1 to the left edge, prop same for x top

	// Render entitities
	//Entity entity = entities.front();
	//std::cout << "\033[" << entity.y << ";" << entity.x << "H\033[" << entity.getColour() << "m" << entity.getTexture();
	///*test*/std::cout << "\033[" << enemy1.y << ";" << enemy1.x << "H\033[" << enemy1.getColour() << "m" << enemy1.getTexture();
	/*test2*//*for (Entity* entity : entities)
	{
		std::cout << "\033[" << entity->y + 1 << ";" << entity->x + 1 << "H\033[" << entity->getColour() << "m" << entity->getTexture();
	}*/

	// debug
	std::cout << "\033[25;20H                                                                              ";
	std::cout << "\033[25;20HC" << cameraPos.x << ";" << cameraPos.y << "\tP" << player.x << ";" << player.y;
}
// Aparently \033[H draws 0,0 and 1,1 on the same spot so I should fix up the rendering logic and bounds on player, camera and enemies so they start on 1 instead of 0
// current selution is just rendering on +1 XY


/*void PlatformerGame::_Render()
{
	for (short y = cameraPos.y; y < screenHight + cameraPos.y; y++) {
		for (short x = cameraPos.x; x < screenWidth + cameraPos.x; x++) {
			if (player.x != x || player.y != y) {
				//debug camera pos
				std::cout << "\033[" << cameraPos.y << ";" << cameraPos.x << "H\033[" << Text::backroundBlue << "mC\033[0m";
				std::cout << "\033[" << y << ";" << x << "H\033[" << mapp.mapp[x][y].getColour() << "m" << mapp.mapp[x][y].getTexture();
			}			
			else
				std::cout << "\033[" << player.y << ";" << player.x << "H\033[" << player.getColour() << "m" << player.getTexture();
		}
	}
	// debug
	std::cout << "\033[25;20H                                                                      ";
	std::cout << "\033[25;20HC" << cameraPos.x << ";" << cameraPos.y << "\tP" << player.x << ";" << player.y;
}*/

//some way to move this into entity or player / enemy itself would be good so we can remove the const uints from entity when typing player, would look nicer
/*void PlatformerGame::move(Entity& entity) {
	// debug:
	//std::cout << "JT:" << ((entity.states >> 6) & 0b11) << ";iG:" << (entity.states & entity.isGrounded) << ";iJ:" << (entity.states & entity.isJump) << ";";
	// 

	// is grounded check
	if (mapp.mapp[entity.x][entity.y + 1].getTexture() != ' ')
		entity.states |= entity.isGrounded;
	else entity.states &= ~entity.isGrounded;

	//Jump time needs to be more consistent

	// 1. stop jumping if W and jumping
	if (!(entity.states & entity.Up) && (entity.states & entity.isJump)) {
		entity.states &= ~entity.isJump; // clears the isJump flag
		entity.states = (entity.states & ~entity.jumpTime); // clears bits 6 and 7
	}
	
	// 2. if not grounded and not jumping, fall down
	else if (!(entity.states & entity.isGrounded) && !(entity.states & entity.isJump)) {
		if (mapp.mapp[entity.x][entity.y + 1].getTexture() != ' ') {
			entity.states |= entity.isGrounded; // sets the isGrounded flag
		}
		else {
			entity.y++; // fall
		}
	}	
	
	// 3. begin jumping if w is pressed and player is on ground and the sky is clear above
	else if (entity.states & entity.Up && (entity.states & entity.isGrounded)) {
		if (mapp.mapp[entity.x][entity.y - 1].getTexture() == ' ') {
			entity.states |= entity.isJump;          // sets the isJump flag
			entity.states &= ~entity.isGrounded;     // clear the isGrounded flag
			entity.y--;                    // move up
			entity.states = (entity.states & ~entity.jumpTime) | (1 << 6); // set jumpTime to 1
		}
		else entity.states &= ~entity.isJump;
	}

	// 4. continue jump if w is still pressed and jumpTime is less than 3
	else if (entity.states & entity.Up && (entity.states & entity.isJump)) {
		// I really wanna remove this uint8_t initialisation cause it wastes a entire byte of memory << removed
		//uint8_t jumpTime = (entity.states >> 6) & 0b11; // extract jumpTime
		// ^^ that code above is a clear example of wasting resorses, using a whole byte for no reason. And additional overhead for the construction and deconstruction :<
		if (((entity.states >> 6) & 0b11) < 3 && mapp.mapp[entity.x][entity.y - 1].getTexture() == ' ') {
			entity.y--; // Move up
			entity.states = (entity.states & ~entity.jumpTime) | (((entity.states >> 6) & 0b11) + 1) << 6; // increment jumpTime directly now like it allways should've been
		}
		else {
			entity.states &= ~entity.isJump; // Stop jumping if max height is reached or blocked
		}
	}

	// Left & Right
	if (entity.states & entity.Left && !(entity.states & entity.Right)) {
		if (mapp.mapp[entity.x - 1][entity.y].getTexture() == ' ') // colition check
			entity.x--;
	}
	else if (!(entity.states & entity.Left) && entity.states & entity.Right) {
		if (mapp.mapp[entity.x + 1][entity.y].getTexture() == ' ') // colition check
			entity.x++;
	}	
}*/ // moved to player
// need work
// a better way of doing the collition checks than checking textures...

void PlatformerGame::UpdateCamera() {
	// Adjusted camera bounds
	static const short cameraLeftBound = 5;
	static const short cameraRightBound = screenWidth - 5;

	// Lower the camera's focus to bring the ground closer to the bottom
	//const short cameraTopBound = 2;
	//const short cameraBottomBound = screenHight-2;

	// Horizontal camera movement
	std::cout << "\033[26;5H" << player.x;
	if (player.x < cameraPos.x + cameraLeftBound) {
		cameraPos.x = player.x - cameraLeftBound;
	}
	else if (player.x > cameraPos.x + cameraRightBound) {
		cameraPos.x = player.x - cameraRightBound;
	}
	std::cout << "\033[27;5H" << player.x;
	/*// Vertical camera movement
	if (player.y < cameraPos.y + cameraTopBound) {
		cameraPos.y = player.y - cameraTopBound;
	}
	else if (player.y > cameraPos.y + cameraBottomBound) {
		cameraPos.y = player.y - cameraBottomBound;
	}*/

	// Ensure the camera doesn't go out of map bounds
	cameraPos.x = (cameraPos.x < 0) ? 0 : (cameraPos.x > mapp.width - screenWidth ? mapp.width - screenWidth : cameraPos.x);
	//cameraPos.y = (cameraPos.y < 0) ? 0 : (cameraPos.y > mappHight - screenHight ? mappHight - screenHight : cameraPos.y);
}
