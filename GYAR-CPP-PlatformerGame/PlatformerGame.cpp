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
					else {
						auto blockMask = mapp.mapp[worldX][worldY];						
						std::cout << "\033[" << y + 1 << ";" << x + 1 << "H\033[" << BlockManager::getColour(blockMask) << "m" << BlockManager::getTexture(blockMask);
					}
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

	// debug
	std::cout << "\033[25;20H                                                                              ";
	std::cout << "\033[25;20HC" << cameraPos.x << ";" << cameraPos.y << "\tP" << player.x << ";" << player.y;
}
// Aparently \033[H draws 0,0 and 1,1 on the same spot so I should fix up the rendering logic and bounds on player, camera and enemies so they start on 1 instead of 0
// current selution is just rendering on +1 XY

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
