#pragma once
// includes level, player, and objectlayer
class Level;

class Level {
public:
	std::vector<Layer*> RenderOrder;
	SDL_Texture* CombinedLower;
	SDL_Texture* CombinedHigher;
	SDL_Texture* CombinedTexture;
	int** CollisionOverride;
	int** CombinedCollision;
	//make use of swap to exchange orders dynamically perhaps.
	int LayerSplit = 1;
	ObjectLayer* SpriteLayer;
	SDL_Texture* TextureBuffer;
	int NumLayers; // this is the number of layers

	// constructor for the level
	Level() {
		
		CollisionOverride = new int* [LEVEL_HEIGHT];
		for (int i = 0; i < LEVEL_HEIGHT; i++) {
			CollisionOverride[i] = new int[LEVEL_WIDTH];
		}
		CombinedHigher = NULL;
		CombinedLower = NULL;

		CombinedTexture = SDL_CreateTexture(gRenderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, LEVEL_WIDTH, LEVEL_HEIGHT);
		NumLayers = 0;
		SpriteLayer = NULL;
	}

	// destructor for the level
	~Level() {
		printf("Deconstructor called for level\n");
	}
	
	// renders the level to the window
	void RenderThis(Player* PlayerName) {

		for (int i = 0; i < NumLayers; i++) { // instead of comparing it to NumLayers, we may want to compare it to the bottom layers -- the layers below the player
			SDL_RenderCopy(gRenderer, RenderOrder[i]->SelfHiddenTexture, gCamera->Cam, gFullWindowRect);
		}
		PlayerName->RenderThis(); // renders the player here -- still needs to be improved a bit

		SpriteLayer->BlitObjects(); // this is so we can rerender the objects -- allows them to be movable!
		SDL_RenderCopy(gRenderer, SpriteLayer->CombinedObjects, gCamera->Cam, gFullWindowRect); // this renders the texture of the objectLayer


		// rendering fpsText
		if (displayFPS && fpsText != NULL) {
			fpsText->Display((SCREEN_WIDTH * TILE_WIDTH) - fpsText->text_rect->w, 0);
		}


		// for layers above the player, we will want to do another for loop here
		SDL_RenderPresent(gRenderer);
		SDL_RenderClear(gRenderer);
	}

	// maps all the collision into one array, collisionoverride
	void MapAllCollision() {
		// this sets up the size of combined collision based on the level width and height
		CombinedCollision = new int* [LEVEL_HEIGHT];
		for (int i = 0; i < LEVEL_HEIGHT; i++) {
			CombinedCollision[i] = new int[LEVEL_WIDTH];
		}


		// this goes through every layers collision and puts it all together in CombinedCollision
		for (int counter = 0; counter < NumLayers; counter++) { // NUM LAYERS WILL HAVE TO CHANGE
			for (int i = 0; i < LEVEL_HEIGHT; i++) {
				for (int j = 0; j < LEVEL_WIDTH; j++) {
					if (counter == 0) {
						CombinedCollision[i][j] = RenderOrder[counter]->Arr[i][j];
					}
					else if (RenderOrder[counter]->Arr[i][j] != 0 && counter > 0) {
						CombinedCollision[i][j] = RenderOrder[counter]->Arr[i][j];
					}
				}
			}
		}

		// collision override
		for (int i = 0; i < LEVEL_HEIGHT; i++) {
			for (int j = 0; j < LEVEL_WIDTH; j++) {
				if (CollisionOverride[i][j] != -1) {
					CombinedCollision[i][j] = CollisionOverride[i][j];
				}
			}
		}

	}

	// creates the object layer
	void CreateObjectLayer(std::vector<Sprite*> AllSprites) {
		SpriteLayer = new ObjectLayer(AllSprites);
	}

	// a second way to create the object layer
	void CreateObjectLayer() {
		SpriteLayer = new ObjectLayer;
	}
};