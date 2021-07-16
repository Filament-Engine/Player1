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

	Level();
	~Level();
	void CombineUltraLayer();
	void CombineTextures();
	void RenderThis(Player* PlayerName);
	void MapAllCollision();
	void CreateObjectLayer(std::vector<Sprite*> AllSprites);
	void CreateObjectLayer();
};
// constructor for the level
Level::Level() {
	printf("LEVEL CREATED!!!!!\n");

	CollisionOverride = new int* [LEVEL_HEIGHT];
	for (int i = 0; i < LEVEL_HEIGHT; i++) {
		CollisionOverride[i] = new int[LEVEL_WIDTH];
	}
	CombinedHigher = NULL;
	CombinedLower = NULL;

	CombinedTexture = SDL_CreateTexture(gRenderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, LEVEL_WIDTH, LEVEL_HEIGHT);
	NumLayers = 0;
	SpriteLayer = NULL; 

	//TextureBuffer= SDL_CreateTexture(gRenderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, LEVEL_WIDTH, LEVEL_HEIGHT);
	//may want to make it only the window but for now who cares.
}
// destructor for the level
Level::~Level() {
	printf("Deconstructor called for level\n");
}
void Level::CombineUltraLayer() {
	//should just be three or less for now, so for now if the texture is not null we will go forth.
	printf("CombineUltraLayer Called\n");
	//render Lower - OBject/Player - Higher -check for nulls and don't render if there is a null there instead!
	SDL_SetRenderTarget(gRenderer, CombinedTexture);
	if (CombinedLower != NULL) {
		printf("Okay place into CombinedTexture the Lower\n");
		SDL_RenderCopy(gRenderer, CombinedLower, NULL, NULL);
	}
	if (SpriteLayer->CombinedObjects != NULL) {
		printf("Okay place into CombinedTexture the Player\n");
		SDL_RenderCopy(gRenderer, SpriteLayer->CombinedObjects, NULL, NULL);
	}
	if (CombinedHigher != NULL) {
		printf("Okay place into CombinedTexture the Higher\n");
		SDL_RenderCopy(gRenderer, CombinedHigher, NULL, NULL);
	}
	printf("Return the Target to the Window\n");
	SDL_SetRenderTarget(gRenderer, NULL);


}
// combines all the textures
void Level::CombineTextures() { //trigger each time a layer is 'hidden' later as a boolean.
	//make new combined texture
	printf("going through combine textures()\n");
	if (LayerSplit <= RenderOrder.size()) {
		printf("Layers are able to split - %d = size of RenderOrder \n", RenderOrder.size());
	}
	else {
		printf("Layers are able UNABLE to split - %d = size of RenderOrder \n", RenderOrder.size());
	}
	//Add another layer in doc to test the blit sandwitching.

	SDL_SetRenderTarget(gRenderer, CombinedLower); //Will have to set the target back to window after the function finishes.
														//https://wiki.libsdl.org/SDL_SetRenderTarget
															//https://stackoverflow.com/questions/40886350/how-to-connect-multiple-textures-in-the-one-in-sdl2
	for (int i = 0; i < LayerSplit; i++) {
		//INSERT - boolean in each Layer for if we want it rendered. 
		//CHANGE - Also only go up to the player, then from above the player to the last layer.
		//CHANGE - bring this check outside, when we declare how many layers total the level will have eventually. Then compare the forloops to the player layer or some thing like that
		CombinedLower = SDL_CreateTexture(gRenderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, LEVEL_WIDTH, LEVEL_HEIGHT);
		if (i <= RenderOrder.size()) {
			SDL_RenderCopy(gRenderer, RenderOrder[i]->SelfHiddenTexture, NULL, NULL);
			printf("Rendering layer %d\n", i);
		}
		else {
			SDL_DestroyTexture(CombinedLower);
			CombinedLower = NULL;
			printf("Theres not enough info, so destroy the lower texture.\n");
			break;
		}
	}
	SDL_SetRenderTarget(gRenderer, NULL); //This resets the render target to the Render window (see the wiki)
	//At this point, the texture has all previous textures.


	SDL_SetRenderTarget(gRenderer, CombinedHigher); //Will have to set the target back to window after the function finishes.
														//https://wiki.libsdl.org/SDL_SetRenderTarget
															//https://stackoverflow.com/questions/40886350/how-to-connect-multiple-textures-in-the-one-in-sdl2
	for (int i = LayerSplit; i < RenderOrder.size(); i++) {
		//INSERT - boolean in each Layer for if we want it rendered. 
		//CHANGE - Also only go up to the player, then from above the player to the last layer.
		CombinedHigher = SDL_CreateTexture(gRenderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, LEVEL_WIDTH, LEVEL_HEIGHT);
		if (i <= RenderOrder.size()) {
			SDL_RenderCopy(gRenderer, RenderOrder[i]->SelfHiddenTexture, NULL, NULL);
		}
		else {
			SDL_DestroyTexture(CombinedLower);
			CombinedHigher = NULL;
			printf("Theres not enough info, so destroy the higher texture.\n");
			break;
		}
	}


	SDL_SetRenderTarget(gRenderer, NULL); //This resets the render target to the Render window (see the wiki)

	//set it as render target
	//grab pointers to textures
	//render copy each poitner the netire thing to the entire thing
	//set render target to null
	//render present
	//then clear the renderer
	//copy the renderer, target textures (the combined one) 
	//render the texture/  
	//perhaps set as this things texture?

}
// renders the level to the window
void Level::RenderThis(Player* PlayerName) {
	
	// printf(".1.");
	// printf("number of layers is %d\n", NumLayers);
	for (int i = 0; i < NumLayers; i++) { // instead of comparing it to NumLayers, we may want to compare it to the bottom layers -- the layers below the player
		SDL_RenderCopy(gRenderer, RenderOrder[i]->SelfHiddenTexture, gCamera->Cam, gFullWindowRect);
	}
	PlayerName->RenderThis(); // renders the player here
	
	SpriteLayer->BlitObjects(); // this is so we can rerender the objects -- allows them to be movable!
	// SpriteLayer->MakeSelfTexture();
	SDL_RenderCopy(gRenderer, SpriteLayer->CombinedObjects, gCamera->Cam, gFullWindowRect); // this renders the texture of the objectLayer

	// rendering text
	text->Display();
	if (displayFPS && fpsText != NULL) {
		fpsText->Display((SCREEN_WIDTH * TILE_WIDTH) - fpsText->text_rect->w, 0);
	}

	// for layers above the player, we will want to do another for loop here
	SDL_RenderPresent(gRenderer);
	SDL_RenderClear(gRenderer);
}
// maps all the collision into one array, collisionoverride
void Level::MapAllCollision() { // NEW
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

	printf("testing with collision override...\n");
	for (int i = 0; i < LEVEL_HEIGHT; i++) {
		for (int j = 0; j < LEVEL_WIDTH; j++) {
			if (CollisionOverride[i][j] != -1) {
				CombinedCollision[i][j] = CollisionOverride[i][j];
			}
		}
	}

	// now we will go through the collision override and override any collision points in CombinedCollision
}
void Level::CreateObjectLayer(std::vector<Sprite*> AllSprites) {
	SpriteLayer = new ObjectLayer(AllSprites);
}
void Level::CreateObjectLayer() {
	SpriteLayer = new ObjectLayer;
}