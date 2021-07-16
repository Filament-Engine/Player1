#pragma once
#include "Tile.h"
#include "SurfaceProperty.h"
#include "Quality_Functions.h"
#include <map>
#include <string>

// I CANT ENTER? WHAT - Okay I had to manually save it, I guess thats what hte lock does.
//TEST 1 for branch making. -ended up making a local branch but not one on git... interesting?


class Layer {
public:
	SDL_Surface* SelfHiddenSurface;
	SDL_Texture* SelfHiddenTexture;
	int* CollisionData;
	std::string** DrawnTiles;
	int** Arr;

	Layer(std::string* DrawnTilesRead[], TileHash* GlobalTileHash, std::map<std::string, SurfaceProperty*> SurfacePropertyMap) {
		//if they end up being stored on seperate files, just assign a null to ensure all variables have something and not garbage.
		AddTiles(DrawnTilesRead);
		CollisionData = new int[LEVEL_HEIGHT * LEVEL_WIDTH]; //Every layer should have data for every position 
		AddCollision(GlobalTileHash);
		SelfHiddenSurface = SDL_CreateRGBSurface(0, LEVEL_WIDTH * TILE_WIDTH, LEVEL_HEIGHT * TILE_HEIGHT, 32, 0xff000000, 0x00ff0000, 0x0000ff00, 0x000000ff); // creates a transparent background for the layer
		SelfHiddenTexture = NULL;
		BlitMatrixLayer(GlobalTileHash, SurfacePropertyMap);
		MakeSelfTexture();
	}


	~Layer() {
		printf("deconstructor for layer called\n");
	}

	// Makes a pixel transparent based on the hex transpcolor you pass into it.
	void CreateTransparency(std::string TranspColor) {
		int r = HexToInt(TranspColor, 2); // instead of str, we will have transparent pixel
		int g = HexToInt(TranspColor, 4);
		int b = HexToInt(TranspColor, 6);
		SDL_SetColorKey(SelfHiddenSurface, SDL_TRUE, SDL_MapRGB(SelfHiddenSurface->format, r, g, b)); // taking the black background (0x000000) and making it transparent
	}

	void AddCollision(TileHash* GlobalTileHash) {

		//Use the drawnTilesRead to find the pointers to the proper tile through TileHash (THIS REQUIRES A NEW MEMBER std::string*** DrawnTiles Matrix
		//two arrays one with just collision data, the other copy constructed tiles 
		//make sure the array looks like int ** = new int [height] //requires new member int ** CollisionDataMatrix
		//each pointer in that pointer pointer array has =new int [width]


		for (int i = 0; i < LEVEL_WIDTH * LEVEL_HEIGHT; i++) {
			if (0 == DrawnTiles[i]->compare("")) { //AA##, or "" empty string (\0)
				CollisionData[i] = 0; //2 is reserved for the 'no tile' information. This could then be dynamicallys tated to be collision or none in the override stage.
			}
			else {
				//If there exists a tile at that position, grab the default collision for that tile.
				CollisionData[i] = GlobalTileHash->find(*DrawnTiles[i])->CollisionType;
			}

		}
		// printf("Collision properly read for the Layer\n");
	}

	void AddTiles(std::string* DrawnTilesRead[]) {
		DrawnTiles = new std::string * [(LEVEL_WIDTH * LEVEL_HEIGHT)];
		for (int i = 0; i < (LEVEL_WIDTH * LEVEL_HEIGHT); i++) {
			if (0 == DrawnTilesRead[i]->compare("")) {
				// printf("Empty Tile Read? You Sure?\n");
			}
			DrawnTiles[i] = DrawnTilesRead[i];
		}
	}

	void BlitMatrixLayer(TileHash* GlobalTileHash, std::map<std::string, SurfaceProperty*> SurfacePropertyMap) {
		Arr = new int* [LEVEL_HEIGHT];
		int pos = 0;
		for (int p = 0; p < LEVEL_HEIGHT; p++) {
			Arr[p] = new int[LEVEL_WIDTH];
			for (int i = 0; i < LEVEL_WIDTH; i++) {

				if (0 == DrawnTiles[pos]->compare("\0")) {
					Arr[p][i] = CollisionData[pos];
				}
				else {
					Arr[p][i] = CollisionData[pos];
					GlobalTileHash->find(*DrawnTiles[pos])->BlitThis(i, p, SelfHiddenSurface, SurfacePropertyMap); //Theres actually a tile to blit
				}
				pos += 1;
			}
		}
	}

	void MakeSelfTexture() {
		SelfHiddenTexture = SDL_CreateTextureFromSurface(gRenderer, SelfHiddenSurface);
	}

	void MapThis() {
		//This isn't really a 'map' this, but it should take a global amt of it's layer #, and then add it to a level class
		//this level class then at the end of gathering all collision data and graphic data should handle rendering the textures on screen in proper order
		//As well as handling the scrolling/collision for that level.
		//add to level

		//NOTE Layer is added to the level upon reading. This function still might be used in some capacity but otherwise an artifact to be kept until file management is finished.
		//Insert is usually reserved for when you want more control over the position of objects. LEAVE HERE - for reading multiple files may want to use this.
			//gLevel1->RenderOrder.insert(gLevel1->RenderOrder.end(), new Layer(savedTiles));
	}
};