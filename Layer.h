#pragma once
#include "Tile.h"
#include "SurfaceProperty.h"
#include "Quality_Functions.h"
#include <map>
#include <string>



// layers are used to display tiles. additionally, layers can stack up on top of each other
class Layer {
public:
	SDL_Surface* SelfHiddenSurface;
	SDL_Texture* SelfHiddenTexture;
	int* CollisionData;
	std::string** DrawnTiles;
	int** Arr;

	// constructor for the layer
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

	// adds collision to the layer
	void AddCollision(TileHash* GlobalTileHash) {
		for (int i = 0; i < LEVEL_WIDTH * LEVEL_HEIGHT; i++) {
			if (0 == DrawnTiles[i]->compare("")) { //AA##, or "" empty string (\0)
				CollisionData[i] = 0; //2 is reserved for the 'no tile' information. This could then be dynamicallys tated to be collision or none in the override stage.
			}
			else {
				//If there exists a tile at that position, grab the default collision for that tile.
				CollisionData[i] = GlobalTileHash->find(*DrawnTiles[i])->CollisionType;
			}

		}
	}

	// adds the tiles to the layer
	void AddTiles(std::string* DrawnTilesRead[]) {
		DrawnTiles = new std::string * [(LEVEL_WIDTH * LEVEL_HEIGHT)];
		for (int i = 0; i < (LEVEL_WIDTH * LEVEL_HEIGHT); i++) {
			DrawnTiles[i] = DrawnTilesRead[i];
		}
	}

	// writes all the tiles to the layer
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

	// makes the texture for the layer -- this way we can actually render it
	void MakeSelfTexture() {
		SelfHiddenTexture = SDL_CreateTextureFromSurface(gRenderer, SelfHiddenSurface);
	}
};