//Using SDL and all include statements
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <fstream> //https://www.cplusplus.com/reference/fstream/fstream/
#include <string> //http://www.cplusplus.com/reference/string/string/
#include <map> //https://www.cplusplus.com/reference/map/map/
#include <sstream> //used to convert strings to int, but may be better manually doing so.
#include <vector> //used to dynamically grow SurfaceSource memory. May remove if we can itterate through the map keys in a seperate function.
#include <cmath>
// our own defined header files
#include "SomeGlobals.h"
#include "Quality_Functions.h" // this contains functions that are not used for displaying information, but are used to make other functions less complicated
#include "FPSTimer.h" // class used to calculate fps
#include "Camera.h"
Camera *gCamera;
#include "Startup.h"
#include "Tile.h"
#include "SurfaceProperty.h"
//Map for traversing all Loaded images.
std::map<std::string, SurfaceProperty*> SurfacePropertyMap;
#include "FileFunctions.h"
#include "GenerateOffSetMap.h"
#include "SurfaceCreation.h"
#include "Layer.h"
#include "Sprite.h"
#include "Player.h"
#include "Text.h"
Text* fpsText;
Sprite* Object1; // we can create this sprite now so that it can be used in level/player/objectlayer
#include "Level+.h"
#include "CreatePlayer.h"
#include "TileCreation.h"
#include "CollisionCreation.h"
#include "Close.h"

//TO DO 
	//Json +Dummy files
	//Repo for multiple levels/maps
	//Memory management
	//CreateTransparancy Edit


//Initialize a HashTable for future use. 
TileHash* GlobalTileHash; //INSERT - we also need all globals that are not const to be written to a 'Save properties' folder/document. This would be later, so on load up, we'd read in those constants perhaps... but I'm unsure hwo exactly it works.
Player* Player1;
Level* gLevel1;

std::vector<Sprite*> AllSprites; // NEW




//Grabs everything from the file. Maps paths to letter names, creates tiles, and finds screen dimensions
void FileHandler(std::string MapRepo, long int& TotalTilesOfSurface) {
	//CHANGE All variable declarations must be declared at the start of this function, before anything else, as much as applicable, after making sub functions.

	//Object to hold our Saved Map File
	std::ifstream sourceIMG;

	//Open our Map File from our Repository - Repository should be known through the Saving of the program.
	sourceIMG.open(MapRepo); //Insert a check to see if it exists, or it opened properly.



	if (sourceIMG.is_open()) { //Insert a check to see if the map was openable, if not throw error should be thrown, so I guess make this bool?
		std::string line;
		int FoundTileSetHeader = false; //controls if getline() is to look for "TileSet" header. Tileset is equivalent to the Surfaces we are opening.
		int FoundTileHeader = false; //controls if getline() is to look for "Tiles" header. Tiles is equivlanet to all the SDL_Rect's we will want to blit.
		int FoundCollisionHeader = false;
		int FoundCollisionOverrideHeader = false;

		FoundTileSetHeader = ScreenTileDimension(sourceIMG, line);
		//NEW - temporary, declared here since we are only working with one level, and might as well, although ideally we'd only do so right when we need to
		//placed here since we need the screen width and height at minimum. -although we could wait to declare override array..
		gCamera = new Camera(0, 0); // TEMP
		gLevel1 = new Level();

		//create the window/screen surface
		if (!init()) // gWindow, gScreenSurface, gRenderer, SCREEN_WIDTH * TILE_WIDTH, SCREEN_HEIGHT * TILE_HEIGHT))
		{
			printf("Failed to initialize!\n");
		}

		//While we are not at the end of the file. 
		while (!sourceIMG.eof()) {
			getline(sourceIMG, line);

			if (FoundTileSetHeader && IsSameString(line.c_str(), "Tilesets")) { //Insert a check, if Header not found, throw.
				FoundCollisionHeader = SurfaceCreation(sourceIMG, line, TotalTilesOfSurface, &SurfacePropertyMap, &GlobalTileHash);
			}

			if (FoundCollisionHeader && IsSameString(line.c_str(), "Collision")) { //Insert - This check may be redudant, but if "Tiles" is not found, throw.
				FoundTileHeader = CollisionCreation(sourceIMG, line, SurfacePropertyMap);
			}
			if (SurfacePropertyMap.size() > 0) {
				GenerateTiles(SurfacePropertyMap, GlobalTileHash);
			}


			if (FoundTileHeader && IsSameString(line.c_str(), "Tiles")) { //Insert - This check may be redudant, but if "Tiles" is not found, throw.
				FoundCollisionOverrideHeader = DrawSavedTiles(sourceIMG, line, SurfacePropertyMap, gLevel1, GlobalTileHash);
			}

			if (FoundCollisionOverrideHeader && IsSameString(line.c_str(), "Collision Override")) {
				OverrideCollision(sourceIMG, line, gLevel1);
				// printf("collision override is...\n");
				for (int i = 0; i < LEVEL_HEIGHT; i++) {
					for (int j = 0; j < LEVEL_WIDTH; j++) {
						// printf("%d ", gLevel1->CollisionOverride[i][j]);
					}
					// printf("\n");
				}
				// printf("map collision has been called...\n");
				gLevel1->MapAllCollision(); // NEW
				// printf("Combined Collision is...\n");
				for (int i = 0; i < LEVEL_HEIGHT; i++) {
					for (int j = 0; j < LEVEL_WIDTH; j++) {
						// printf("%d ", gLevel1->CombinedCollision[i][j]);
					}
					// printf("\n");
				}
			}

			//If everything was read as it should be by eof
			if (FoundTileSetHeader && FoundCollisionHeader && FoundTileHeader && FoundCollisionOverrideHeader) {
				printf("COMBINE TEXTURES\n");
				CreatePlayer(&Player1, SurfacePropertyMap); // Creates the player



				//summary
				// Object -> Print -> Map, repeat
				// This allows the first object created to be 0, and when maping it it then increases the vector in object layer
				// which allows the next object to be 1, rinser repeat
				gLevel1->CreateObjectLayer();
				//NEW - the order of creation gives them an 'int name' which shoudl be unchanged for the rest of the program .might make it static later.
				//ALSO this distance function just returns its position in the que, so if it's the ifrst object then it would be begin-(past the end itter), =   0-1=|-1|=1, etc.
				//grabs the order. Might make global later, but for now this'll do. It should also leave the player alone for now, since I can insert it to the start as creation order '0'
				
				Object1 = new Sprite(64, 64, "AA229", SurfacePropertyMap, std::distance(gLevel1->SpriteLayer->AllSprites.begin(), gLevel1->SpriteLayer->AllSprites.end())); // TEMP
				//check to see if distance is working as expected.
				printf("Object%d, created order = %d\n", 1, Object1->OrderCreation);
				gLevel1->SpriteLayer->MapSprite(Object1); //NEW 


				//lets just see if it works again
				Sprite* Object2 = new Sprite(16, 16, "AA259", SurfacePropertyMap, std::distance(gLevel1->SpriteLayer->AllSprites.begin(), gLevel1->SpriteLayer->AllSprites.end()), 1, 16, 80, "AxisX"); // TEMP
				//check to see if distance is working as expected.
				printf("Object%d, created order = %d\n", 2, Object2->OrderCreation);
				gLevel1->SpriteLayer->MapSprite(Object2); //NEW 
				

				Sprite* Object3 = new Sprite(80, 80, "AA249", SurfacePropertyMap, std::distance(gLevel1->SpriteLayer->AllSprites.begin(), gLevel1->SpriteLayer->AllSprites.end()), 0, 80, 80, "AxisX"); // TEMP
				//check to see if distance is working as expected.
				printf("Object%d, created order = %d\n", 3, Object3->OrderCreation);
				gLevel1->SpriteLayer->MapSprite(Object3); //NEW 

				Sprite* Object4 = new Sprite(120, 120, "AA219", SurfacePropertyMap, std::distance(gLevel1->SpriteLayer->AllSprites.begin(), gLevel1->SpriteLayer->AllSprites.end()), 0, 120, 120, "AxisX"); // TEMP
				//check to see if distance is working as expected.
				printf("Object%d, created order = %d\n", 4, Object4->OrderCreation);
				gLevel1->SpriteLayer->MapSprite(Object4); //NEW 


				//After pushing back all the objects -DONE ONCE
				gLevel1->SpriteLayer->AllocateQue2(); //New - so it is now ready for taking on the order of which to mvoe the sprites.



				//Where are they relative to the tiles on the map when they firest spawn (shoudl be on top of each other)
				//position should be (x, y) = (48=3, 2) thus we have position 
				// 0, 16, 23, 48 64
				// 0, 16, 23, 48 64 
				// 0, 16, 23, OB OB [r2, c3, c4] 
				// 0, 16, 23, OB OB [r3, c3, c4]

				//okay we got both objects in to R2, c3, c4.

				// gLevel1->SpriteLayer->DisplayTileBasedArray();






				//I'm adding directly to object so this is redundant.
				AllSprites.clear(); // this is removing the AllSprites data because we have this data transfered into gLevel1->SpriteLayer instead

				gLevel1->CombineTextures();


			}
			else {
				printf("Dim Throw\n");
			}
		}
		//Close the File
		sourceIMG.close();
	}
}

// handles the loop in main. this determines fps and user inputted events
void handleLoop() {
	// fps timers
	Timer fpsTimer; // calculates the fps
	Timer capTimer; // limits the max possible fps

	// begin counting fps
	int countedFrames = 0;
	fpsTimer.start();

	// movement variables

	//Player movements
	int xVel = 0; // velocity of x
	int yVel = 0; // velocity of y position
	int xVec = 1; //how many pixels x movement is on x axis
	int yVec = 1; //how many pixels y movement is on y axis

	//Limits of the level
	//0 is implicit
	int yBuff = LEVEL_HEIGHT * TILE_HEIGHT - SCREEN_HEIGHT * TILE_HEIGHT; //the 'limit' space for the 'box' around the player to move.
	int xBuff = LEVEL_WIDTH * TILE_WIDTH - SCREEN_WIDTH * TILE_WIDTH; //the 'limit' space for the camera tracking player to move.
	int yPlayerBuff = SCREEN_HEIGHT * TILE_HEIGHT;
	int xPlayerBuff = SCREEN_WIDTH * TILE_WIDTH;

	// loop variables
	bool quit = false; // handles the loop; whether we want to quit, or continue
	SDL_Event e; // event handler


	// begin loop
	while (!quit) {
		capTimer.start(); // starts the max fps timer 
		while (SDL_PollEvent(&e) != 0) {	// this is checking to see if there is an event or not 
			if (e.type == SDL_QUIT) {	// if the user event is "QUIT" then...
				quit = true;	// this will end the loop
			}
			// if the user does not want to quit, continue with the loop
			if (e.type == SDL_KEYDOWN && e.key.repeat == 0) // if the user presses down a key
			{
				switch (e.key.keysym.sym) // Select surfaces based on key press
				{
				case SDLK_w: // if the user presses 'w'
					yVel -= yVec;
					break;
				case SDLK_s: // if the user presses 's'
					yVel += yVec;
					break;
				case SDLK_a: // if the user presses 'a'
					xVel -= xVec;
					break;
				case SDLK_d: // if the user presses 'd'
					xVel += xVec;
					break;
				case SDLK_RIGHT: // if the user presses right arrow key
					Object1->xVec += xVec;
					break;
				case SDLK_DOWN: // if the user presses up arrow key
					Object1->yVec += yVec;
					break;
				case SDLK_LEFT: // if the user presses right arrow key
					Object1->xVec += -xVec;
					break;
				case SDLK_UP: // if the user presses up arrow key
					Object1->yVec += -yVec;
					break;
				case SDLK_u: // if the user presses 'u' -- this will be utility for now, and will change if fps is displayed or not
					if (displayFPS) {
						displayFPS = false;
					}
					else {
						displayFPS = true;
					}
					break;
				}
			}
			else if (e.type == SDL_KEYUP && e.key.repeat == 0) // if the user releases a key, go through this statement
			{
				switch (e.key.keysym.sym) // Select surfaces based on key press
				{
				case SDLK_w: // if the user releases 'w'
					yVel += yVec;
					break;
				case SDLK_s: // if the user releases 's'
					yVel -= yVec;
					break;
				case SDLK_a: // if the user releases 'a'
					xVel += xVec;
					break;
				case SDLK_d: // if the user releases 'd'
					xVel -= xVec;
					break;

				case SDLK_RIGHT: // if the user presses right arrow key
					Object1->xVec += -xVec;
					break;
				case SDLK_DOWN: // if the user presses up arrow key
					Object1->yVec += -yVec;
					break;
				case SDLK_LEFT: // if the user presses right arrow key
					Object1->xVec += xVec;
					break;
				case SDLK_UP: // if the user presses up arrow key
					Object1->yVec += yVec;
					break;

				}
			}
		}

		if (displayFPS && fpsText == NULL) { // this creates the fps text -- we want it to only be made once, so we make sure it only does this if fpsText == NULL
			fpsText = new Text("Fonts/arial.ttf", "FPS", 18, { 255, 255, 255 }, 0, 0, false);
		}


		// at some point, this will need to be put into gLevel1->SpriteLayer->MoveAllSprites2, but we will likely need to pass in the combined collision / yVel / xVel -- or make the velocities based on something else
		if (Player1->MoveY(yVel, gLevel1->CombinedCollision)) {
			Player1->MoveTargetTileY();
		}
		if (Player1->MoveX(xVel, gLevel1->CombinedCollision)) {
			Player1->MoveTargetTileX();
		}

		//test to see if auto movement works 
		gLevel1->SpriteLayer->MoveAllSprites2();	
		// printf("%d %d -- %d %d\n", Player1->xPos, Player1->yPos, gCamera->x, gCamera->y);// gLevel1->Camera->x, gLevel1->Camera->y); // camera x and y are not going back to 0. they need to when moving back up tho... awk.


		gLevel1->RenderThis(Player1);
		TIME++;
		if (TIME >= MAX_FPS) {
			TIME = 0;
		}

		// calculating fps
		float avgFPS = countedFrames / (fpsTimer.getTicks() / 1000.f); // calculates fps
		if (avgFPS > 2000000) { // this is an extremely large fps that may occur at startup; this is not correct, though, so we are putting the avgFPS as 0, instead
			avgFPS = 0;
		}
		++countedFrames; // adds 1 to the countedFrames
		// used to display FPS on screen
		if (displayFPS && fpsText != NULL) {
			std::string fpsMessage = "FPS: " + std::to_string(int(avgFPS));
			fpsText->UpdateMessage(fpsMessage.c_str());
		}
		//If frame finished early
		int frameTicks = capTimer.getTicks();
		if (frameTicks < SCREEN_TICKS_PER_FRAME)
		{
			//Wait remaining time
			SDL_Delay(SCREEN_TICKS_PER_FRAME - frameTicks);
		}

	}
}

int wmain(int argc, char* args[]) {
	// gCamera = new Camera(0, 0);
	long int TotalTilesOfSurface;
	//FileHandler assumed ot be 'load file'
	std::string MapRepo = UserDirectory() + "72,000.txt"; //CHANGE ME - Requires knowing Repo from Save Files


		//Load media
	if (!loadMedia())
	{
		printf("Failed to load media!\n");
	}
	else
	{
		FileHandler(MapRepo, TotalTilesOfSurface);

		
		handleLoop();
	}

	close(gLevel1, Player1, &SurfacePropertyMap); //Free resources and close SDL - INSERT call deconstructor of every tile. 

	return 0;
}