#include "PlatformerGame.h"
#include "DeltaTimeCounter.h"
#include "string"

void PlatformerGame::Run() {
	std::cout << "\033[0m\033[?25l"; // reset formating & hide cursor
	// std::cout << "\033[?25h"; // show cursor
	Menue(); // making menue a return would probably make this looks mother
	std::cout << "\033[2J\033[0m\033[3;5H Thanks for playing" << std::endl; // escape call 2J clears screen
}

void PlatformerGame::Menue() {
	bool menueLoop = true;
	while (menueLoop) {
		bool optionLoop = true;
		bool menuOption = true;
		std::cout << "\033[2J\033[3;6HPlatformerGame\033[4;6H StartGame \033[5;6H Quit ";
		_getch(); // await key press
		while (optionLoop) {
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
			if (menuOption) 	std::cout << "\033[2J\033[3;6HPlatformerGame\033[4;6H<StartGame>\033[5;6H Quit ";
			else std::cout << "\033[2J\033[3;6HPlatformerGame\033[4;6H StartGame \033[5;6H<Quit>";

			// also posible but ads flickering
			//std::cout << "\033[2J\033[3;6HPlatformerGame\033[4;6H"
			//	<< (menuOption ? "<StartGame>" : " StartGame ")
			//	<< "\033[5;6H"
			//	<< (!menuOption ? "<Quit>" : " Quit ");

			std::this_thread::sleep_for(std::chrono::milliseconds(100));
			if ((GetAsyncKeyState('W') & 0x8000) || (GetAsyncKeyState('S') & 0x8000) || (GetAsyncKeyState(VK_UP) & 0x8000) || (GetAsyncKeyState(VK_DOWN) & 0x8000))
				menuOption = !menuOption;
			if (GetAsyncKeyState(VK_RETURN) & 0x8000 || (GetAsyncKeyState(VK_SPACE) & 0x8000)) // VK_Return dosn't seem to work
				optionLoop = false;
		}

		if (menuOption)
			GameLoop(); // starts the actual game
		else menueLoop = false; //leaves the menue and exits game
	}
}

void PlatformerGame::Initzialize() {
	running = true;
	
	// reset player
	player.Reset();

	// set camera pos
	cameraPos.x = player.x;
	cameraPos.y = player.y;
	UpdateCamera();
	
	// set the mapp
	_LvLManager.Initzialize();
}	

void PlatformerGame::GameLoop()
{
	Initzialize();
	DeltaTimeCounter deltaFrameCounter;

	while (running)
	{		
		/*depricated*/ //Render(); // 54.5 ms
		OptimizedRender(); // 0.33 ms
		Update(); // 0.05 ms
		deltaFrameCounter.Count();
		deltaFrameCounter.Display(1, 1, "Frame"); // change the second number to 17 if trying the depricated update
		// the counter takes about 0.19 ms

		std::this_thread::sleep_for(std::chrono::milliseconds(50)); // tmp framerate limiter
		// remember that it blocks the game for more then the time specified (5-10 ms)
	}
}

void PlatformerGame::Update()
{ // problem can arise later if mapp is acsesed after player finishes LvL
	_LvLManager.Update();
	
	player.Update(); // potentially put update camera and entity rendering in a if statment running on a player.update return steming from collition check, here by we can also swap player texture to a backround colour alowing render to show what player died from	

	UpdateCamera();
}

// depricated
// renders the mapp, avrage time of 54.5 ms
void PlatformerGame::Render() {
		short worldX;
		short worldY;
		for (short y = 0; y < LvLManager::screenHight; y++) {
			for (short x = 0; x < LvLManager::screenWidth; x++) {
				// move out for efichency !?
				worldX = x + cameraPos.x;
				worldY = y + cameraPos.y;

				if (player.x != worldX || player.y != worldY) {
					auto blockMask = _LvLManager.mapp[worldX][worldY];
					std::cout << "\033[" << y + 1 << ";" << x + 1 << "H\033[" << BlockManager::getColour(blockMask) << "m" << BlockManager::getTexture(blockMask);
				}
				else {
					std::cout << "\033[" << y + 1 << ";" << x + 1 << "H\033[" << player.getColour() << "m" << player.getTexture();
				}

				// Temporary area for entity rendering
				for (auto& enemy : _LvLManager.entitiesList->enemies)
				{
					if (enemy->x == worldX && enemy->y == worldY)
						std::cout << "\033[" << y + 1 << ";" << x + 1 << "H\033[" << enemy->getColour() << "m" << enemy->getTexture();
				} // and the same thing for the projectile rendering (unnececary as this is depricated anyways)
			}
		}
	}
// Aparently \033[H draws 0,0 and 1,1 on the same spot so I should fix up the rendering logic and bounds on player, camera and enemies so they start on 1 instead of 0
// current selution is just rendering on +1 XY

// new
// renders the mapp, avrage time of 0.33 ms
void PlatformerGame::OptimizedRender() {
	// 1: populate/prepare the screenBuffer
	struct DisplayElement { char texture; short colour; };
	DisplayElement screenBuffer[LvLManager::screenWidth][LvLManager::screenHight];

	for (short y = 0; y < LvLManager::screenHight; y++) {
		for (short x = 0; x < LvLManager::screenWidth; x++) {
			short worldX = x + cameraPos.x;
			short worldY = y + cameraPos.y;

			DisplayElement element;

			// if not player's pos amend mapp
			if (player.x != worldX || player.y != worldY) {
				auto blockMask = _LvLManager.mapp[worldX][worldY];
				if (blockMask) {
					element.texture = BlockManager::getTexture(blockMask);
					element.colour = BlockManager::getColour(blockMask);
				}
				else {
					element.texture = ' ';
					element.colour = 0;
				}
			}
			else { // player
				element.texture = player.getTexture();
				element.colour = player.getColour();
			}

			// entity handling
			for (auto& enemy : _LvLManager.entitiesList->enemies) {
				if (enemy->x == worldX && enemy->y == worldY) {
					element.texture = enemy->getTexture();
					element.colour = enemy->getColour();
					break;
				}
			}

			// projectile handling
			for (auto& projectile : _LvLManager.entitiesList->projectiles) {
				if (projectile->x == worldX && projectile->y == worldY) {
					element.texture = projectile->getTexture();
					element.colour = projectile->getColour();
					break;
				}
			}

			// update screenBuffer
			screenBuffer[x][y] = element;
		}
	}

	// 2: construct the screenOutput string from screenBuffer
	std::string screenOutput;
	screenOutput.reserve(LvLManager::screenWidth * LvLManager::screenHight * 7); // preallocate space with a slight overestimation to prevent further prealocation
	//screenOutput.reserve(7 + LvLManager::screenHight + LvLManager::screenHight * LvLManager::screenWidth * 6); // perfectly preallocated space
	// why:
	/*
		"\033[" + std::to_string(element.colour) + "m"

		The escape sequence \033[ is 2 bytes.
		The color value (element.colour) could go up to 2 digits (so we assume 2 bytes on average).
		The m adds 1 more byte.
		Total per element for the control code: 5 bytes.

		Each texture is represented by a single character (1 byte).
		Subtotal per element:
			5 + 1 = 6 bytes.

		For each row, we append \n (1 byte)

		The command \033[1;1H sets the cursor position, and it's 7 bytes in total (including the H).

		Row contribution: each row contributes
			LvLManager::screenWidth × 6 + 1 bytes.

		Header contribution: the initial cursor reset string contributes 7 bytes.
		Total:			
			7 + LvLManager::screenHight + LvLManager::screenHight × LvLManager::screenWidth × 6
		Or:
			"\033[1;1H" + ("\n" * screenHight) + screenHight * screenWidth * 6
	*/

	// sets the initial cursor pos
	screenOutput += "\033[2;2H";

	// the screenBuffer amender (that can't be a real word)
	for (short y = 0; y < LvLManager::screenHight; y++) {
		for (short x = 0; x < LvLManager::screenWidth; x++) {
			const auto& element = screenBuffer[x][y];
			//screenOutput += "\033[" + std::to_string(y + 1) + ";" + std::to_string(x + 1) + "H";
			screenOutput += "\033[" + std::to_string(element.colour) + "m";
			screenOutput += element.texture;
		}
		screenOutput += '\n'; // end of row
	}

	// 3: renders the screen in a singular cout instead of (screenHight * screenWidth + entities) times
	std::cout << screenOutput << std::flush;
}

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
	/*TMP*/ cameraPos.y = 1;

	// Ensure the camera doesn't go out of map bounds
	cameraPos.x = (cameraPos.x < 0) ? 0 : (cameraPos.x > _LvLManager.width - LvLManager::screenWidth ? _LvLManager.width - LvLManager::screenWidth : cameraPos.x);
	//cameraPos.y = (cameraPos.y < 0) ? 0 : (cameraPos.y > mappHight - screenHight ? mappHight - screenHight : cameraPos.y);
}