//Using SDL and all include statements
bool pause = false;
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
//two more for testing
Sprite* Object2;
Sprite* Object3;
Sprite* Object4;

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
		int FoundTileHeader = false; //controls if getline() is to look for "Tiles" header. Tiles is equivalent to all the SDL_Rect's we will want to blit.
		int FoundCollisionHeader = false;
		int FoundCollisionOverrideHeader = false;

		FoundTileSetHeader = ScreenTileDimension(sourceIMG, line);
		//NEW - temporary, declared here since we are only working with one level, and might as well, although ideally we'd only do so right when we need to
		//placed here since we need the screen width and height at minimum. -although we could wait to declare override array..
		gCamera = new Camera(0, 0); // TEMPORARILY HERE -- WILL NEED TO CHANGE FOR PLAYER POSITION
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
				gLevel1->MapAllCollision();
			}

			//If everything was read as it should be by eof
			if (FoundTileSetHeader && FoundCollisionHeader && FoundTileHeader && FoundCollisionOverrideHeader) {
				CreatePlayer(&Player1, SurfacePropertyMap); // Creates the player



				//summary
				// Object -> Print -> Map, repeat
				// This allows the first object created to be 0, and when maping it it then increases the vector in object layer
				// which allows the next object to be 1, rinser repeat
				gLevel1->CreateObjectLayer();
				//NEW - the order of creation gives them an 'int name' which shoudl be unchanged for the rest of the program .might make it static later.
				//ALSO this distance function just returns its position in the que, so if it's the ifrst object then it would be begin-(past the end itter), =   0-1=|-1|=1, etc.
				//grabs the order. Might make global later, but for now this'll do. It should also leave the player alone for now, since I can insert it to the start as creation order '0'
			

				 
				//TEST TELEPORT OBJECTS BEGIN
				Object1 = new Sprite(64, 64, "AA229", SurfacePropertyMap, std::distance(gLevel1->SpriteLayer->AllSprites.begin(), gLevel1->SpriteLayer->AllSprites.end())); // TEMP
				printf("Object%d, created order = %d\n", 1, Object1->OrderCreation);
				gLevel1->SpriteLayer->MapSprite(Object1);
				Object3 = new Sprite(48, 96, "AA259", SurfacePropertyMap, std::distance(gLevel1->SpriteLayer->AllSprites.begin(), gLevel1->SpriteLayer->AllSprites.end())); // TEMP
				printf("Object%d, created order = %d\n", 3, Object3->OrderCreation);
				gLevel1->SpriteLayer->MapSprite(Object3); 
				Object2 = new Sprite(80, 96, "AA259", SurfacePropertyMap, std::distance(gLevel1->SpriteLayer->AllSprites.begin(), gLevel1->SpriteLayer->AllSprites.end())); // TEMP
				printf("Object%d, created order = %d\n", 2, Object2->OrderCreation);
				gLevel1->SpriteLayer->MapSprite(Object2);  
				Object4 = new Sprite(16, 16, "AA150", SurfacePropertyMap, std::distance(gLevel1->SpriteLayer->AllSprites.begin(), gLevel1->SpriteLayer->AllSprites.end())); // TEMP
				printf("Object%d, created order = %d\n", 4, Object4->OrderCreation);
				gLevel1->SpriteLayer->MapSprite(Object4);
				//NOTE YOU MUST MAP SPRITE BEFORE DECLARING THE REST, OTHERWISE THE ORDER IS THE SAME!!! (may be useful but might not be, who knows....)
				  
				 

				/* 
				//RANDOM SPRITES BEGIN
				//kept Object1 because it's global, don't want to mess anything up.
				Object1 = new Sprite(16, 16, "AA229", SurfacePropertyMap, std::distance(gLevel1->SpriteLayer->AllSprites.begin(), gLevel1->SpriteLayer->AllSprites.end())); // TEMP
				//check to see if distance is working as expected.
				printf("Object%d, created order = %d\n", 1, Object1->OrderCreation);
				gLevel1->SpriteLayer->MapSprite(Object1); //NEW
				std::vector<Sprite*> RandomMoveSprites;
				//0-20 (width wise, don't have gaurd for going over edge of spawn area).
				RandomMoveSprites.resize(10); //now it has space for 20 objects given to it, I choose 20 because it's roughly 1/3rd of the width of level using concentric
				int xPosTemp = 0;
				int yPosTemp = 0;
				for (int j = 0; j < RandomMoveSprites.size(); j++) {
					//they will all start on the first row, but three colomns apart (each occupying the 'third' column.
					RandomMoveSprites[j] = new Sprite(xPosTemp, yPosTemp, "AA259", SurfacePropertyMap, std::distance(gLevel1->SpriteLayer->AllSprites.begin(), gLevel1->SpriteLayer->AllSprites.end()), "RandomMove");
					printf("Object%d, created order = %d, Position={%d, %d}\n", j + 2, Object1->OrderCreation, xPosTemp, yPosTemp);
					gLevel1->SpriteLayer->MapSprite(RandomMoveSprites[j]); //NEW
					if (xPosTemp > (LEVEL_WIDTH - 3) * TILE_WIDTH) {
						xPosTemp = 0;
						yPosTemp += 32;
					}
					else {
						xPosTemp += 32;
					}
				}
				//RANDOM SPRITES END
				 
				 */












				 
				//TEST TELEPORT OBJECTS END
				
				//After pushing back all the objects -DONE ONCE
				gLevel1->SpriteLayer->AllocateQue2(); //New - so it is now ready for taking on the order of which to mvoe the sprites.
				


				//Where are they relative to the tiles on the map when they firest spawn (shoudl be on top of each other)
				//position should be (x, y) = (48=3, 2) thus we have position 
				// 0, 16, 23, 48 64
				// 0, 16, 23, 48 64 
				// 0, 16, 23, OB OB [r2, c3, c4] 
				// 0, 16, 23, OB OB [r3, c3, c4]

				//okay we got both objects in to R2, c3, c4.

				//I'm adding directly to object so this is redundant.
				AllSprites.clear(); // this is removing the AllSprites data because we have this data transfered into gLevel1->SpriteLayer instead
				 
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
	Timer capTimer; // limits the max possible fps -- we have it capped at 60 fps

	// begin counting fps
	int countedFrames = 0;
	fpsTimer.start();

	// movement variables

	//Player movements
	int xVel = 0; // velocity of x
	int yVel = 0; // velocity of y position
	int xVec = 1; //how many pixels x movement is on x axis
	int yVec = 1; //how many pixels y movement is on y axis

	// loop variables
	bool quit = false; // handles the loop; whether we want to quit, or continue
	SDL_Event e; // event handler

	bool Object2or3Moved = false;

	// begin loop
	while (!quit) {
		TOTALFRAMECOUNT++;
		capTimer.start(); // starts the max fps timer 
		while (SDL_PollEvent(&e) != 0) {	// this is checking to see if there is an event or not 
			if (e.type == SDL_QUIT) {	// if the user event is "QUIT" then...
				quit = true;	// this will end the loop
			}
			// if the user does not want to quit, continue with the loop
			if (e.type == SDL_KEYDOWN && e.key.repeat == 0) // if the user holds down a key
			{
				switch (e.key.keysym.sym) // this is just checking to see what key was pressed
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


				//Test Object 2
				case SDLK_l: // if the user presses right arrow key
					Object2->xVec += xVec;
					Object2or3Moved = true;
					break;
				case SDLK_k: // if the user presses up arrow key
					Object2->yVec += yVec;
					Object2or3Moved = true;
					break;
				case SDLK_j: // if the user presses right arrow key
					Object2->xVec += -xVec;
					Object2or3Moved = true;
					break;
				case SDLK_i: // if the user presses up arrow key
					Object2->yVec += -yVec;
					Object2or3Moved = true;
					break;

				//Test Object 3
				case SDLK_h: // if the user presses right arrow key
					Object3->xVec += xVec;
					Object2or3Moved = true;
					break;
				case SDLK_g: // if the user presses up arrow key
					Object3->yVec += yVec;
					Object2or3Moved = true;
					break;
				case SDLK_f: // if the user presses right arrow key
					Object3->xVec += -xVec;
					Object2or3Moved = true;
					break;
				case SDLK_t: // if the user presses up arrow key
					Object3->yVec += -yVec;
					Object2or3Moved = true;
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
					if (yVel < 0) {//NEW statements, because velocities can change at a moment, and the buttom presses shouldn't be dependent on it.
						yVel += yVec;
					}
					break;
				case SDLK_s: // if the user releases 's'
					if (yVel > 0) {
						yVel -= yVec;
					}
					break;
				case SDLK_a: // if the user releases 'a'
					if (xVel < 0) {
						xVel += xVec;
					}
					break;
				case SDLK_d: // if the user releases 'd'
					if (yVel > 0) {
						xVel -= xVec;
					}
					break;

				case SDLK_RIGHT: // if the user presses right arrow key
					if (Object1->xVec > 0) {
						Object1->xVec += -xVec;
					}
					break;
				case SDLK_DOWN: // if the user presses up arrow key
					if (Object1->yVec > 0) {
						Object1->yVec += -yVec;
					}
					break;
				case SDLK_LEFT: // if the user presses right arrow key
					if (Object1->xVec < 0) {
						Object1->xVec += xVec;
					}
					break;
				case SDLK_UP: // if the user presses up arrow key
					if (Object1->yVec < 0) {
						Object1->yVec += yVec;
					}
					break;


					//Test Object 2
				case SDLK_l: // if the user presses right arrow key
					if (Object2->yVec < 0) {
						Object2->xVec += -xVec;
					}
					break;
				case SDLK_k: // if the user presses up arrow key
					if (Object2->yVec > 0) {
						Object2->yVec += -yVec;
					}
					break;
					
				case SDLK_j: // if the user presses right arrow key
					if (Object2->xVec < 0) {
						Object2->xVec += xVec;
					}
					break;
				case SDLK_i: // if the user presses up arrow key
					if (Object2->yVec < 0) {
						Object2->yVec += yVec;
					}
					break;

					//Test Object 3
				case SDLK_h: // if the user presses right arrow key
					if (Object3->yVec < 0) {
						Object3->xVec += -xVec;
					}
					break;
				case SDLK_g: // if the user presses up arrow key
					if (Object3->yVec > 0) {
						Object3->yVec += -yVec;
					}
					break;
				case SDLK_f: // if the user presses right arrow key
					if (Object3->xVec < 0) {
						Object3->xVec += xVec;
					}
					break;
				case SDLK_t: // if the user presses up arrow key
					if (Object3->yVec < 0) {
						Object3->yVec += yVec;
					}
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
		

		gLevel1->RenderThis(Player1);
		TIME++;
		//if (TIME >= MAX_FPS) {
		if (TIME >= 30) {
			TIME = 0;
		}


		//FOR MANUAL TESTS
		/* 
		if (Object2or3Moved) {
			printf("Adjusted positions - OB1 OB2 OB3 = {%d, %d}, {%d, %d}, {%d, %d}\n", Object1->xPos, Object1->yPos, Object2->xPos, Object2->yPos, Object3->xPos, Object3->yPos);
			printf("Giving you time to lift the key up\n");
			SDL_Delay(500);
			Object2or3Moved = false;
		}
		if (pause) {
			SDL_Delay(0);
			pause = false;
		}
		*/


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
	//std::string MapRepo = UserDirectory() + "72,000.txt"; //CHANGE ME - Requires knowing Repo from Save Files
	std::string MapRepo = UserDirectory() + "Checkers2.txt"; //CHANGE ME - Requires knowing Repo from Save Files


		//Load media
	
	FileHandler(MapRepo, TotalTilesOfSurface);

	// handles the game loop
	handleLoop();
	
	// when handleloop is over (when the user quits), we close everything
	close(gLevel1, Player1, &SurfacePropertyMap); //Free resources and close SDL - INSERT call deconstructor of every tile. 

	return 0;
}