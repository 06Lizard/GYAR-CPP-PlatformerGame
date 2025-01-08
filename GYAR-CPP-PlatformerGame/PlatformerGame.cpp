#include "PlatformerGame.h"

// forward declared from LvL manager
//struct LvLManager::ForwardDeclaredLists {
//public:
//	std::vector<std::unique_ptr<Enemy>> enemies;
//	std::vector<std::unique_ptr<Projectile>> projectiles;
//
//	ForwardDeclaredLists() = default;
//	~ForwardDeclaredLists() = default;
//};
#include "ForwardDeclaredLists.h"

void PlatformerGame::Run() {
	std::cout << "\033[0m"; // reset formating;
	std::cout << "\033[?25l"; // hide cursor
	// std::cout << "\033[?25h"; // show cursor
	Menue(); // making menue a return would probably make this looks mother
	std::cout << "\033[2J\033[0m\033[3;5H Thanks for playing" << std::endl; // escape call 2J clears screen
}

void PlatformerGame::Menue() {
	bool menuOption = true;
	std::cout << "\033[2J\033[3;6HPlatformerGame\033[4;6H StartGame \033[5;6H Quit ";
	_getch(); // await key press
	while (true) {
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
		if (menuOption) 	std::cout << "\033[2J\033[3;6HPlatformerGame\033[4;6H<StartGame>\033[5;6H Quit ";
		else std::cout << "\033[2J\033[3;6HPlatformerGame\033[4;6H StartGame \033[5;6H<Quit>";
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
		if ((GetAsyncKeyState('W') & 0x8000) || (GetAsyncKeyState('S') & 0x8000) || (GetAsyncKeyState(VK_UP) & 0x8000) || (GetAsyncKeyState(VK_DOWN) & 0x8000))
			menuOption = !menuOption;
		if (GetAsyncKeyState(VK_RETURN) & 0x8000 || (GetAsyncKeyState(VK_SPACE) & 0x8000)) // VK_Return dosn't seem to work
			if (menuOption)
				GameLoop();
			else return;		
	}	
}

void PlatformerGame::Initzialize() {
	score = 0; // reset score

	// reset player
	player.Reset();

	// set camera pos
	cameraPos.x = player.x;
	cameraPos.y = 1;
	UpdateCamera();
	
	// set the mapp
	_LvLManager.Initzialize();
}	

void PlatformerGame::GameLoop()
{
	Initzialize();

	while (running)
	{		
		Render();
		Update();
				
		std::this_thread::sleep_for(std::chrono::milliseconds(25)); // tmp framerate limiter
	}

	GameOver();
}

void PlatformerGame::GameOver() {
	std::cout << "\033[2J\033[0m\033[3;5H Game Over\033[4;5H Score: " << score << "\033[5;5H Level: " << _LvLManager.getLvL() << std::endl;
	Beep(1000, 100);
	std::this_thread::sleep_for(std::chrono::milliseconds(500));
	_getch();
	// we'll go back to the menue loop, be nice if we wen't back to the start of the menue function but eh
}

void PlatformerGame::Update()
{ // problem can arise later if mapp is acsesed after player finishes LvL
	_LvLManager.Update();
	
	player.Update(); // potentially put update camera and entity rendering in a if statment running on a player.update return steming from collition check, here by we can also swap player texture to a backround colour alowing render to show what player died from	

	UpdateCamera();
}

void PlatformerGame::Render() {
	short worldX;
	short worldY;
	for (short y = 0; y < LvLManager::screenHight; y++) {
		for (short x = 0; x < LvLManager::screenWidth; x++) {
			// move out for efichency !?
			worldX = x + cameraPos.x;
			worldY = y + cameraPos.y;

			if (player.x != worldX || player.y != worldY) {
				//for (Entity* entity : entities) /*test3*/
				//{
				//	if (entity->x == worldX && entity->y == worldY)
				//		std::cout << "\033[" << y + 1 << ";" << x + 1 << "H\033[" << entity->getColour() << "m" << entity->getTexture();
				//	else {
				//		auto blockMask = mapp.mapp[worldX][worldY];						
				//		std::cout << "\033[" << y + 1 << ";" << x + 1 << "H\033[" << BlockManager::getColour(blockMask) << "m" << BlockManager::getTexture(blockMask);
				//	}
				//}
				auto blockMask = _LvLManager.mapp[worldX][worldY];
				std::cout << "\033[" << y + 1 << ";" << x + 1 << "H\033[" << BlockManager::getColour(blockMask) << "m" << BlockManager::getTexture(blockMask);
				/*debug camera pos*/
				//std::cout << "\033[" << cameraPos.y+1 << ";" << cameraPos.x+1 << "H\033[" << Text::backroundBlue << "mC\033[0m";
				/*test3->cmented*///std::cout << "\033[" << y+1 << ";" << x+1 << "H\033[" << mapp.mapp[worldX][worldY].getColour() << "m" << mapp.mapp[worldX][worldY].getTexture();
			}
			else {
				std::cout << "\033[" << y + 1 << ";" << x + 1 << "H\033[" << player.getColour() << "m" << player.getTexture();
				//std::cout << "\033[25;10HXY" << x << ";" << y;
			}

			// Temporary area for entity rendering
			for (auto& enemy : _LvLManager.entitiesList->enemies)
			{
				if (enemy->x == worldX && enemy->y == worldY)
					std::cout << "\033[" << y + 1 << ";" << x + 1 << "H\033[" << enemy->getColour() << "m" << enemy->getTexture();
			}
		}
		// abstract enemy and projectile rendering to the LvLManager instead
		//_LvLManager.Render();
	}// some weird bug where y 0 dosnt get drawn, it starts drawing y1 to the left edge, prop same for x top

	// debug
	//std::cout << "\033[25;20H                                                                              ";
	//std::cout << "\033[25;20HC" << cameraPos.x << ";" << cameraPos.y << "\tP" << player.x << ";" << player.y;
}
// Aparently \033[H draws 0,0 and 1,1 on the same spot so I should fix up the rendering logic and bounds on player, camera and enemies so they start on 1 instead of 0
// current selution is just rendering on +1 XY

void PlatformerGame::UpdateCamera() {
	// Adjusted camera bounds
	static const short cameraLeftBound = 10;
	static const short cameraRightBound = LvLManager::screenWidth - 10;

	// Lower the camera's focus to bring the ground closer to the bottom
	//const short cameraTopBound = 2;
	//const short cameraBottomBound = screenHight-2;

	// Horizontal camera movement
	if (player.x < cameraPos.x + cameraLeftBound) {
		cameraPos.x = player.x - cameraLeftBound;
	}
	else if (player.x > cameraPos.x + cameraRightBound) {
		cameraPos.x = player.x - cameraRightBound;
	}

	/*// Vertical camera movement
	if (player.y < cameraPos.y + cameraTopBound) {
		cameraPos.y = player.y - cameraTopBound;
	}
	else if (player.y > cameraPos.y + cameraBottomBound) {
		cameraPos.y = player.y - cameraBottomBound;
	}*/

	// Ensure the camera doesn't go out of map bounds
	cameraPos.x = (cameraPos.x < 0) ? 0 : (cameraPos.x > _LvLManager.width - LvLManager::screenWidth ? _LvLManager.width - LvLManager::screenWidth : cameraPos.x);
	//cameraPos.y = (cameraPos.y < 0) ? 0 : (cameraPos.y > mappHight - screenHight ? mappHight - screenHight : cameraPos.y);
}
