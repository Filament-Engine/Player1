#pragma once
// includes level, player, and objectlayer

class Player;
class Level;

class Level {
public:
	SDL_Rect* Camera;
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
	void CreateCamera(int x, int y);
	void MapAllCollision();
	void CreateObjectLayer(std::vector<Sprite*> AllSprites);
	void Level::CreateObjectLayer();
};
class Player {
	//QUESTION - should we prepare the class to handle multiple different tiles to be a 'object' or should we just assume it is one rectangle and the animations are swapping between those?
private:
	SDL_Rect* SourceTile;
public:
	int xPos;
	int yPos;
	SDL_Rect* SelfTile;
	SDL_Rect* TargetTile; //this needs to be edited by the programmer for specific instances/screen transitions.
	std::string SourceName;
	SDL_Texture* SelfImg;
	SDL_Surface* TempOrigin;
	//source img
	//width of player
	//height of palyer
	//target x
	//target y
	int xVel;
	int yVel;
	//movement speed (vel x, vel y) - movmeent vector not c vectors :P
	//animations?
	//default spawn location
	//'redraw' position x y
	//'reference' position (to compare to colision space. perhaps the 0,0 of the target tile vs movement tile.

	Player(int DefaultSpawnX, int DefaultSpawnY, int DefaultPixelH, int DefaultPixelW, std::string SourceKey, int SourceCoordx, int SourceCoordy, int SourcePixelH, int SourcePixelW, int xVelocity, int yVelocity, std::map<std::string, SurfaceProperty*> SurfacePropertyMap, Level* level) {

		//SurfaceProperty* DefaultSourceSurface = SurfacePropertyMap["SourceName"]->texture;
		 //this is either atexture or a surface. 

		xPos = DefaultSpawnX;
		yPos = DefaultSpawnY;

		SourceName = SourceKey; //AA

		printf("Init Player\n");
		SourceTile = new SDL_Rect();
		SelfTile = new SDL_Rect();
		TargetTile = new SDL_Rect();
		SourceTile->x = SourceCoordx * TILE_WIDTH;
		SourceTile->y = SourceCoordy * TILE_HEIGHT;
		SourceTile->h = SourcePixelH;
		SourceTile->w = SourcePixelW;

		SelfTile->x = 0;
		SelfTile->y = 0;
		SelfTile->h = SourcePixelH;
		SelfTile->w = SourcePixelW;
		//grab a portion of a texture, and make a texture.

		TargetTile->x = DefaultSpawnX;
		TargetTile->y = DefaultSpawnY;
		TargetTile->w = DefaultPixelH;
		TargetTile->h = DefaultPixelW;
		//Surface -> Texture
		TempOrigin = SDL_CreateRGBSurface(0, SourceTile->w, SourceTile->h, 32, 0, 0, 0, 0);
		printf("checking\n");
		SDL_BlitSurface(SurfacePropertyMap[SourceName]->GetSelfSurface(), SourceTile, TempOrigin, SelfTile);

		printf("checking2\n");
		//case Temp Origin to a texture
		SelfImg = SDL_CreateTextureFromSurface(gRenderer, TempOrigin);
		xVel = xVelocity;
		yVel = yVelocity;

		// level->SpriteLayer->PlayerObject = this;

	}
	~Player() {
		printf("Destruct Player\n");
	}
	// moves the player, moved the camera, detects for collision, detects for level barriers, all along the y-axis. returns 1 if the player icon moves, 0 if not.
	bool MoveY(int yVelocity, Level* level) { //moves the palyer in the y direction
		yPos += yVelocity;

		if (yVelocity < 0) { // if moving up -- detecting collision
			if (1 == level->CombinedCollision[yPos / TILE_HEIGHT][xPos / TILE_WIDTH] || 1 == level->CombinedCollision[(yPos / TILE_HEIGHT)][(xPos + GetWidth() - 1) / TILE_WIDTH]) {
				// printf("cannot move up!\n");
				yPos -= yVelocity;
				return 0;
			}
		}

		else if (yVelocity > 0 && yPos < LEVEL_HEIGHT * TILE_HEIGHT - GetHeight()) { // if moving down -- detecting collision -- the second statement is so that it doesn't go through here when its at the edge
			if (1 == level->CombinedCollision[(yPos + GetHeight() - 1) / TILE_HEIGHT][xPos / TILE_WIDTH] || 1 == level->CombinedCollision[(yPos + GetHeight() - 1) / TILE_HEIGHT][(xPos + GetWidth() - 1) / TILE_WIDTH]) { // check for right collision
				yPos -= yVelocity; // reverts the movement change
				// printf("cannot move down!\n");
				return 0; // fails it
			}
		}

		if (yPos < (LEVEL_HEIGHT * TILE_HEIGHT) - (SCREEN_HEIGHT * TILE_HEIGHT / 2) && yPos >(SCREEN_HEIGHT * TILE_HEIGHT / 2)) { // this will move camera
			level->Camera->y += yVelocity; // this moves the camera by the yVelocity value
			return 0;
		}
		else if (yPos < (SCREEN_HEIGHT * TILE_HEIGHT / 2) && level->Camera->y > 0) { // NEW
			level->Camera->y += yVelocity; // the only situation in which this action takes place is when the camera is moving up; thus yVelocity must be negative, so we are subtracting the camera by adding yVelocity
			return 0;
		}
		else if (yPos > (LEVEL_HEIGHT * TILE_HEIGHT) - (SCREEN_HEIGHT * TILE_HEIGHT / 2) && level->Camera->y < LEVEL_HEIGHT * TILE_HEIGHT - SCREEN_HEIGHT * TILE_HEIGHT - 1) { // NEW -- this is for some reason unncessary on x-axis but not y
			level->Camera->y += yVelocity; // the only time when this action happens is when we are moving doown, thus yVelocity would be positive.
			return 0;
		}
		else { // this will move the player icon
			if (yPos < 0 || yPos + GetHeight() - 1 >= LEVEL_HEIGHT * TILE_HEIGHT) { // determines if it is in bounds -- if it is not, go through this if statement
				yPos -= yVelocity;
				return 0;
			}
			else {
				TargetTile->y += yVelocity; // actually moves the player
				return 1;
			}
		}
	}
	// moves the player, moved the camera, detects for collision, detects for level barriers, all along the x-axis. returns 1 if the player icon moves, 0 if not.
	bool MoveX(int xVelocity, Level* level) { //moves the player in the x direction
		xPos += xVelocity;
		if (xVelocity < 0) { // if moving left
			if (1 == level->CombinedCollision[yPos / TILE_HEIGHT][(xPos / TILE_WIDTH)] || 1 == level->CombinedCollision[(yPos + GetHeight() - 1) / TILE_HEIGHT][(xPos / TILE_WIDTH)]) { // check for left collision
				// printf("cannot move left!\n");
				xPos -= xVelocity; // reverts the movement change
				return 0; // fails it
			}
		}
		else if (xVelocity > 0 && xPos < LEVEL_WIDTH * TILE_WIDTH - GetWidth()) { // if moving right -- the second statemenet means it won't go through if it's at the edge
			if (1 == level->CombinedCollision[yPos / TILE_HEIGHT][(xPos + GetWidth() - 1) / TILE_WIDTH] || 1 == level->CombinedCollision[(yPos + GetHeight() - 1) / TILE_HEIGHT][(xPos + GetWidth() - 1) / TILE_WIDTH]) { // check for right collision
				xPos -= xVelocity; // reverts the movement change
				return 0; // fails it
			}
		}
		if (xPos < (LEVEL_WIDTH * TILE_WIDTH) - (SCREEN_WIDTH * TILE_WIDTH / 2) && xPos >(SCREEN_WIDTH * TILE_WIDTH / 2)) { // this will move camera
			level->Camera->x += xVelocity;
			return 0; // the player icon did not move (only the camera)
		}
		else if (xPos < (SCREEN_WIDTH * TILE_WIDTH / 2) && level->Camera->x > 0) {
			level->Camera->x += xVelocity;  // this will only happen when we're moving left, thus, xVelocity would be negative. therefore, we are subtracting through addition.
			return 0;
		}
		else if (xPos > (LEVEL_WIDTH * TILE_WIDTH) - (SCREEN_WIDTH * TILE_WIDTH / 2) && level->Camera->x < LEVEL_WIDTH * TILE_WIDTH - SCREEN_WIDTH * TILE_WIDTH - 1) {
			level->Camera->x += xVelocity; // this will only happen when we're moving right, thus, xVelocity would be positive. thus, we are just adding as normal.
			return 0;
		}

		else { // this will move the player icon
			if (xPos < 0 || xPos + GetWidth() - 1 >= LEVEL_WIDTH * TILE_WIDTH) { // checks to see if position is out of bounds
				xPos -= xVelocity;
				return 0;
			}
			else { // if not out of bounds, move
				TargetTile->x += xVelocity;
				return 1; // the player icon moved
			}
		}
	}
	int getXPos() { // returns the x position
		return xPos;
	}
	int getYPos() { // returns the y position
		return yPos;
	}
	//make a second to handle new target positions, in the event it is changed idk.
	void RenderThis() {
		//Test Blitting is very bad, so what actually happens is it automatically wipes the information of the previous surface. So lets try placing a texture over it, and just grabe the texture from the target texture.
		SDL_RenderCopy(gRenderer, SelfImg, NULL, TargetTile);
	};
	int GetWidth() {
		return SelfTile->w;
	}
	int GetHeight() {
		return SelfTile->h;
	}
};

// constructor for the level
Level::Level() {
	printf("LEVEL CREATED!!!!!\n");

	CollisionOverride = new int* [LEVEL_HEIGHT];
	for (int i = 0; i < LEVEL_HEIGHT; i++) {
		CollisionOverride[i] = new int[LEVEL_WIDTH];
	}
	CreateCamera(0, 0);
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
		SDL_RenderCopy(gRenderer, RenderOrder[i]->SelfHiddenTexture, Camera, gFullWindowRect);
	}
	PlayerName->RenderThis(); // renders the player here
	
	SpriteLayer->BlitObjects(); // this is so we can rerender the objects -- allows them to be movable!
	// SpriteLayer->MakeSelfTexture();
	SDL_RenderCopy(gRenderer, SpriteLayer->CombinedObjects, Camera, gFullWindowRect); // this renders the texture of the objectLayer

	// for layers above the player, we will want to do another for loop here
	SDL_RenderPresent(gRenderer);
	SDL_RenderClear(gRenderer);
}
// creates the camera for the level
void Level::CreateCamera(int x, int y) {
	//Set the 'default' of PartialTexture's width and height. (May be changeable if loading different maps on events.
	Camera = new SDL_Rect();
	Camera->w = SCREEN_WIDTH * TILE_WIDTH;
	Camera->h = SCREEN_HEIGHT * TILE_HEIGHT;

	//default render location
	Camera->x = x;
	Camera->y = y;
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