#pragma once
#include <stdlib.h> // this is for the random function
#include <math.h>




class Sprite {
public:
	int xPos; // here the xPos is where the sprite is placed on the y position
	int yPos; // here the yPos is where the sprite is placed on the y position
	std::string label; // this is the sprite name, aka the file name, AA, and the number that tells us what tile to look at. for example, AA25
	// we may need a width and height to be passed in if it's not the same size as regular tiles
	SDL_Rect* SourceTile;
	SDL_Rect* TargetTile;
	std::string IMGName;
	int OrderCreation; //NEW holds onto the order of creation, so if this was the first object it is either 1 or 0.
	//int directionV; //NEW, holds onto the starting dierction, and how quickly it will move when it's 'pacing'. It must be stored or returned from the function, otherwise it will cling to the edge of hte pace distance.
	int leftVlimit; //NEW don't know how I want to handle it for now, but will store in sprite for now.
	int rightVlimit;

	bool DoAutoX = false;
	bool DoMoveX = false;
	bool DoMoveY = false;
	bool DoAutoY = false;
	bool DoFindPlayer = false;
	bool DoRandomMove = false;

	//For random movement, signals that the position has been adjusted do to the level's graphical limit. 
	bool AdjustedPositionY = false;
	bool AdjustedPositionX = false;

	// for random
	int RandomX;
	int RandomY;

	int xVec;
	int yVec;

	//used to calculate whether a frame has finished rendering or not within Random move
	int OriginalFrame;
	//New
	int Travel[2] = { 0,0 };
	int TravelContort[2] = { 0,0 };
	bool UseContort = false;
	int ExVel[2] = { 0,0 };
	std::vector<std::vector<int>> LastDestination = {}; //NOTE - This might only ever need to be a single pair of x y values.
	int CollisionType = 1; //Solid, Default for now, because it need st ograb it from the IMG, and then be overridden if needed,



	// normal constructor -- uses moveX and moveY
	Sprite(int x, int y, std::string l, std::map<std::string, SurfaceProperty*> SurfacePropertyMap, int Order) {
		xPos = x;
		yPos = y;
		label = l;
		OriginalFrame = -1;

		IMGName = label.substr(0, 2); // this is the letter part of label -- the AA

		OrderCreation = Order;//NEW
		leftVlimit = 0; //edited by user potentially idk what default we want.
		rightVlimit = 0;
		DoMoveX = true;
		DoMoveY = true;
		xVec = 0;
		yVec = 0;

		std::string temp; // this temp is used to get the position of the source tile
		int i = 0;
		while (label[i + 2] != '\0') {
			temp += label[i + 2];
			i++;
		}
		int SourcePos = stoi(temp); // this is the number part of label-- the number
		int SourceX;
		int SourceY = 0;


		int pos = SourcePos;
		int width = SurfacePropertyMap[IMGName]->width / TILE_WIDTH;
		while (pos >= width) {
			pos -= width;
			SourceY++;  // adds one to the y sourceY position
		}
		SourceX = pos; // makes the sourceX is remainder

		SourceTile = new SDL_Rect();
		TargetTile = new SDL_Rect();

		SourceTile->x = SourceX * TILE_WIDTH;
		SourceTile->y = SourceY * TILE_HEIGHT;
		SourceTile->w = TILE_WIDTH;
		SourceTile->h = TILE_HEIGHT;

		TargetTile->w = TILE_WIDTH;
		TargetTile->h = TILE_HEIGHT;

	}
	// constructor for different types of movement, such as only moveX, only moveY, but for now, and for  findplayer -- we pass it in as a string
	Sprite(int x, int y, std::string l, std::map<std::string, SurfaceProperty*> SurfacePropertyMap, int Order, std::string MovementType) {
		xPos = x;
		yPos = y;
		label = l;
		OriginalFrame = -1;

		if (MovementType == "MoveX") {

			DoMoveX = true;
		}
		else if (MovementType == "MoveY") {

			DoMoveY = true;
		}
		else if (MovementType == "FindPlayer") {

			DoFindPlayer = true;
		}
		else if (MovementType == "RandomMove") {

			DoRandomMove = true;
		}


		IMGName = label.substr(0, 2); // this is the letter part of label -- the AA

		OrderCreation = Order;//NEW
		leftVlimit = 0; //edited by user potentially idk what default we want.
		rightVlimit = 0;
		xVec = 0;
		yVec = 0;

		std::string temp; // this temp is used to get the position of the source tile
		int i = 0;
		while (label[i + 2] != '\0') {
			temp += label[i + 2];
			i++;
		}
		int SourcePos = stoi(temp); // this is the number part of label-- the number
		int SourceX;
		int SourceY = 0;


		int pos = SourcePos;
		int width = SurfacePropertyMap[IMGName]->width / TILE_WIDTH;
		while (pos >= width) {
			pos -= width;
			SourceY++;  // adds one to the y sourceY position
		}
		SourceX = pos; // makes the sourceX is remainder

		SourceTile = new SDL_Rect();
		TargetTile = new SDL_Rect();

		SourceTile->x = SourceX * TILE_WIDTH;
		SourceTile->y = SourceY * TILE_HEIGHT;
		SourceTile->w = TILE_WIDTH;
		SourceTile->h = TILE_HEIGHT;

		TargetTile->w = TILE_WIDTH;
		TargetTile->h = TILE_HEIGHT;

	}
	// constructors for AutoX and Y
	Sprite(int x, int y, std::string l, std::map<std::string, SurfaceProperty*> SurfacePropertyMap, int Order, int Vel, int LeftVLimit, int RightVLimit, std::string Axis) {
		xPos = x;
		yPos = y;
		label = l;
		OriginalFrame = -1;

		IMGName = label.substr(0, 2); // this is the letter part of label -- the AA

		if (Axis == "AxisX") {
			yVec = 0;
			xVec = Vel; // NEW, this is like the velocity and starting direction of the sprite;
			leftVlimit = LeftVLimit;
			rightVlimit = RightVLimit;
			OrderCreation = Order; // NEW
			DoAutoX = true;
		}
		else if (Axis == "AxisY") {
			xVec = 0;
			yVec = Vel;
			leftVlimit = LeftVLimit;
			rightVlimit = RightVLimit;
			OrderCreation = Order;//NEW
			DoAutoY = true;
		}





		std::string temp; // this temp is used to get the position of the source tile
		int i = 0;
		while (label[i + 2] != '\0') {
			temp += label[i + 2];
			i++;
		}
		int SourcePos = stoi(temp); // this is the number part of label-- the number
		int SourceX;
		int SourceY = 0;


		int pos = SourcePos;
		int width = SurfacePropertyMap[IMGName]->width / TILE_WIDTH;
		while (pos >= width) {
			pos -= width;
			SourceY++;  // adds one to the y sourceY position
		}
		SourceX = pos; // makes the sourceX is remainder

		SourceTile = new SDL_Rect();
		TargetTile = new SDL_Rect();

		SourceTile->x = SourceX * TILE_WIDTH;
		SourceTile->y = SourceY * TILE_HEIGHT;
		SourceTile->w = TILE_WIDTH;
		SourceTile->h = TILE_HEIGHT;

		TargetTile->w = TILE_WIDTH;
		TargetTile->h = TILE_HEIGHT;

	}

	Sprite() { // this is the default constructor: necessary for player to be a subclass of sprite
	   // i don't think we'll need to pass in information in here
	}


	~Sprite() {
		printf("Deconstructor for sprite called!\n");
	}

	bool MoveX(int x) { // it's possible we will want int x to be an argument in the object class instead of this function
		xPos += x;

		if (xPos < 0 || xPos + TILE_WIDTH - 1 >= LEVEL_WIDTH * TILE_WIDTH) {
			xPos -= x;
			return 1;
		}
		else {
			//TargetTile->x += x;
			return 0;
		}
	}
	bool MoveY(int y) { // it's possible we will want int y to be an argument in the object class instead of this function
		yPos += y;
		if (yPos < 0 || yPos + TILE_HEIGHT - 1 >= LEVEL_HEIGHT * TILE_HEIGHT) {
			yPos -= y;
			return 1;
		}
		else {
			//TargetTile->y += y;
			return 0;
		}
	}
	//this I think should be exclusive for handling collision from regular behavior - or maybe we make it so it can handle its own teleport to an occupied collision tile?
	void TeleportSprite(int x, int y) {
		xPos = x;
		yPos = y;
	}
	void TeleportX(int x) {
		xPos = x;
	}
	void TeleportY(int y) {
		yPos = y;
	}
	void FindPlayer() {
		printf("oh boy am i finding the player... we will get this set up once player is a subclass of sprite\n");
	}
	void RandomMove() {
		//INSERT a check so that if it's the same frame, don't recalcualte a random number. Otherwise the direction changes mid frame, which may make debugging stack errors harder.
		//theoretically it should be fine.
		// 
		//if (FrameCounter > FrameStored)


		if (TIME == 0 && TIME != OriginalFrame) { //NEW
			RandomX = rand() % 4; // 0/1 means don't move, 2 means move up, 3 means move down
			RandomY = rand() % 4; // 0/1 means don't move, 2 means move left, 3 means move right.
			OriginalFrame = TIME; //NEW
		}
		if (TIME > 15) {
			OriginalFrame = -1; //NEW
			RandomX = 0;
			RandomY = 0;
		}

		if (RandomX == 2) {
			if (OrderCreation == 7) {
				printf("xPos -1\n");
			}
			xVec = -1;
			AdjustedPositionX = MoveX(xVec);
		}
		else if (RandomX == 3) {
			if (OrderCreation == 7) {
				printf("xPos +1\n");
			}
			xVec = 1;
			AdjustedPositionX = MoveX(xVec);
		}
		else if (RandomX == 1 || RandomX == 0) {
			if (OrderCreation == 7) {
				printf("xPos -0\n");
			}
			xVec = 0;
			//AdjustedPositionX = false;
		}

		if (RandomY == 2) {
			if (OrderCreation == 7) {
				printf("yPos -1\n");
			}
			yVec = -1;
			AdjustedPositionY = MoveY(yVec);
		}
		else if (RandomY == 3) {
			if (OrderCreation == 7) {
				printf("yPos + 1\n");
			}
			yVec = 1;
			AdjustedPositionY = MoveY(yVec);
		}
		else if (RandomY == 1 || RandomY == 0) {
			if (OrderCreation == 7) {
				printf("yPos -0\n");
			}
			yVec = 0;
			//AdjustedPositionX = false; //both of these are redundant.
		}

	}
	void AutoY() {
		if (yVec > 0) { //going right

			if (yPos + yVec < rightVlimit) {

				yPos += yVec;
			}
			else {
				//turn around

				yVec = -yVec;

				yPos += yVec;
			}
		}
		else if (yVec < 0) { //going left

			if (yPos + yVec > leftVlimit) {

				yPos += yVec;
			}
			else {
				//turn around

				yVec = -yVec;

				yPos += yVec;
			}
		}
	}
	void AutoX() {

		//I'm thinking I will likely have to not move all sprites the same way. so I'll call one function that is internal to the sprite
		// Behavior(bools, 0, 1, 0, 1, ,1 ,0,0,0) {
		// if (first) { moveX }
		// if (second) {AutoX }
		// etc
		//That way we can pass in behavior on creation. Check with adam.

		//I want to move but one tile. 

		//So I have an xPos which prepresents where on the map it WANTS to go
		//TargetTile->x is where it WILL go. 
		//So I edit PosX - check matrix new position, if free, go, if not, flag (return a value maybe?)
		//I will then ave another function that 'undoes' the wanted action of xPos on a fail when we back up through the stack.
		//FOR NOW, just get something that moves in a pace.

		//CHECK, that leftXlimit, rightXlimit and direction (howfast and starting direction) won't wander ebcause direction goes over or something.
		//if it does, DONT adjust it, just let the user know.


		//for turn around, if we use SDL_TextureEx, we could flip the sprite, or we could load a 'opposite sprite' based on another tileset the user inputs if fliping is more taxing. 




		if (xVec > 0) { //going right

			if (xPos + xVec < rightVlimit) {

				xPos += xVec;
			}
			else {
				//turn around

				xVec = -xVec;

				xPos += xVec;
			}
		}
		else if (xVec < 0) { //going left

			if (xPos + xVec > leftVlimit) {

				xPos += xVec;
			}
			else {
				//turn around

				xVec = -xVec;

				xPos += xVec;
			}
		}





		//fail -for now don't care
		//UndoAutoX();

		//Okay now check LM in object layer,
		//IF FAILS, add to a queue and figure out what blocked it
		//Check the values backwards, if fails again - CALL 'UndoMovementX' or something. haven't decided how I want to do that.for now it'll be jerryrigged.
		//if success, great. Change TargetTile then (Because objects are moving on the object layer independent of the player. They move like the background if they are still, they move themselves too) 
	}
	void Behavior() {
		if (DoAutoX) {
			AutoX();
		}
		if (DoAutoY) {
			AutoY();
		}
		if (DoMoveX) {
			MoveX(xVec);
		}
		if (DoMoveY) {
			MoveY(yVec);
		}
		if (DoFindPlayer) {
			FindPlayer();
		}
		if (DoRandomMove) {
			RandomMove();
		}

	}
	void UndoBehavior() {
		//printf("UndoBehavior\n"); 
		if (DoAutoX) {
			UndoAutoX();
		}
		if (DoAutoY) {
			UndoAutoY();
		}
		if (DoMoveX) {
			UndoMoveX(xVec);
		}
		if (DoMoveY) {
			UndoMoveY(yVec);
		}
		if (DoRandomMove) {
			UndoRandomMove();
		}
	}
	void MoveTargetTileX() {

		TargetTile->x = xPos;
		//called on success of autoMoveX, means I can move the tile location on lm, 
		//so remove it's previous position
		//move targettile=xpos




	}
	void MoveTargetTileY() {

		TargetTile->y = yPos;
		//called on success of autoMoveX, means I can move the tile location on lm, 
		//so remove it's previous position
		//move targettile=xpos

	}
	void UndoAutoX() {
		xPos -= xVec; //no matter what direction it's heading, this will undo it. - this also assumes your moving when your turning around. 

	}
	void UndoAutoY() {
		yPos -= yVec; //no matter what direction it's heading, this will undo it. - this also assumes your moving when your turning around. 

	}
	int UndoMoveX(int x) {

		//This uno may be unncessary, since the original moveX and Y handle this. There is an edge case where the user wants them to be 'bounced' back 
		//a certain distance, so I'll keep it for now.
		if (xPos < 0 || xPos + TILE_WIDTH - 1 >= LEVEL_WIDTH * TILE_WIDTH) {

			return 0;
		}
		else {
			xPos -= x;
			//TargetTile->x += x;
			return 1;
		}
	}
	int UndoMoveY(int y) {

		if (yPos < 0 || yPos + TILE_HEIGHT - 1 >= LEVEL_HEIGHT * TILE_HEIGHT) {
			return 0;
		}
		else {
			yPos -= y;
			//TargetTile->y += y;
			return 1;
		}
	}
	void UndoRandomMove() {
		if (!AdjustedPositionX) {
			if (RandomX == 2) {
				if (OrderCreation == 7) {
					printf("xPos +1\n");
				}
				MoveX(-xVec);
			}
			else if (RandomX == 3) {
				if (OrderCreation == 7) {
					printf("xPos -1\n");
				}
				MoveX(-xVec);
			}
			else if (RandomX == 1 || RandomX == 0) {
				if (OrderCreation == 7) {
					printf("xPos -0\n");
				}
				xVec = 0;
			}
		}
		else {
			printf("AdjustedX is True!\n");
		}

		if (!AdjustedPositionY) {
			if (RandomY == 2) {
				if (OrderCreation == 7) {
					printf("yPos +1\n");
				}
				MoveY(-yVec);
			}
			else if (RandomY == 3) {
				if (OrderCreation == 7) {
					printf("yPos -1\n");
				}
				MoveY(-yVec);
			}
			else if (RandomY == 1 || RandomY == 0) {
				if (OrderCreation == 7) {
					printf("yPos -0\n");
				}
				yVec = 0;
			}
		}
		else {
			printf("AdjustedY is True!\n");
		}
		//AdjustPositionV is reset at the end of the loop, when we are checking for overlap. There should be better way of handling this, because the vast majority of sprites won't have to adjust like this.
		//Though they may, because of the Level Collision itself.... :/ I'll need to think about it.

	}
	Sprite* GetThis() {
		return this;
	}
	void BlitThis(SDL_Surface* TargetSurface) {
		TargetTile->x = xPos;
		TargetTile->y = yPos;
		TargetTile->w = TILE_WIDTH;
		TargetTile->h = TILE_HEIGHT;
		SDL_BlitSurface(SurfacePropertyMap[IMGName]->GetSelfSurface(), SourceTile, TargetSurface, TargetTile);
	}
	bool ChangeSource(std::string l) { // takes a string such as "AA65" and then reassigns the sprite image to this
		label = l;
		IMGName = label.substr(0, 2);

		std::string temp; // this temp is used to get the position of the source tile
		int i = 0;
		while (label[i + 2] != '\0') {
			temp += label[i + 2];
			i++;
		}
		int SourcePos = stoi(temp); // this is the number part of label-- the number
		int SourceX;
		int SourceY = 0;

		int pos = SourcePos;
		int width = SurfacePropertyMap[IMGName]->width / TILE_WIDTH;
		while (pos >= width) {
			pos -= width;
			SourceY++;  // adds one to the y sourceY position
		}
		SourceX = pos; // makes the sourceX is remainder

		SourceTile = new SDL_Rect();

		SourceTile->x = SourceX * TILE_WIDTH;
		SourceTile->y = SourceY * TILE_HEIGHT;
		SourceTile->w = TILE_WIDTH;
		SourceTile->h = TILE_HEIGHT;

		return true;

	}

};

struct XYArr {
public:
	Sprite* Victim;
	std::vector<Sprite*> SpriteXCollision;
	std::vector<Sprite*> SpriteYCollision;
}; 

struct XYArr2 {
	Sprite* CurrentVictim;
	int XCollision; //might want int
	int YCollision; //might want int
	Sprite* Collisions[4] = { nullptr, nullptr, nullptr, nullptr }; //x, y, d cases. (what you could be overlapping
	Sprite* HitSprites[4] = { nullptr, nullptr, nullptr, nullptr }; //what you actually hit/overlap with when calcualted.
	int Edge[2] = { 0,0 };
	int D1[2] = { 0,0 };
	int D2[2] = { 0,0 };
	int Final[2] = { 0,0 };
};

class ObjectLayer {
private:
public:
	SDL_Surface* TargetSurface;
	SDL_Texture* CombinedObjects;
	std::string** DrawnObjects;
	std::vector<Sprite*> AllSprites; //this stores order of creation
	std::vector<Sprite*>** LM;
	std::vector<Sprite*> Queue2; //this is the acutal order the stack completes in.
	int SpriteStackCounter;
	std::vector< std::vector<Sprite*>> SpriteStack;

	ObjectLayer(std::vector<Sprite*> ASprites) {
		printf("ObjectLayer Created\n");

		AllSprites = ASprites;
		SpriteStackCounter = 0;

		TargetSurface = SDL_CreateRGBSurface(0, LEVEL_WIDTH * TILE_WIDTH, LEVEL_HEIGHT * TILE_HEIGHT, 32, 0, 0, 0, 0); // ERROR WAS HERE -- SHOW JACOB!!! BECAUSE IT'S FUNNY
		CombinedObjects = NULL;
		CreateTransparency("0x000000");
		BlitObjects();

	}
	ObjectLayer() { //this is currently being used rather than the above.
		printf("ObjectLayer Created\n");

		//the vector is increased each time an object appears
		SpriteStackCounter = 0;
		TargetSurface = SDL_CreateRGBSurface(0, LEVEL_WIDTH * TILE_WIDTH, LEVEL_HEIGHT * TILE_HEIGHT, 32, 0, 0, 0, 0); // ERROR WAS HERE -- SHOW JACOB!!! BECAUSE IT'S FUNNY
		CombinedObjects = NULL;
		CreateTransparency("0x000000");
		//BlitObjects(); will call this after all sprites are called.

		LM = new std::vector<Sprite*>*[LEVEL_HEIGHT];
		for (int i = 0; i < LEVEL_HEIGHT; i++) {
			printf("\n");
			LM[i] = new std::vector<Sprite*>[LEVEL_WIDTH];
			for (int j = 0; j < LEVEL_WIDTH; j++) {
				printf(".");

			}
		}

		//test to see if you need to push back empty vector
		printf("vector exists? %p\n", LM[4][4]);

		printf("\nVector Matrix Made for Object Collision approx\n");


	}

	void CreateTransparency(std::string TranspColor) {
		int r = HexToInt(TranspColor, 2); // instead of str, we will have transparent pixel
		int g = HexToInt(TranspColor, 4);
		int b = HexToInt(TranspColor, 6);
		SDL_SetColorKey(TargetSurface, SDL_TRUE, SDL_MapRGB(TargetSurface->format, r, g, b)); // taking the black background (0x000000) and making it transparent
	}
	void BlitObjects() {
		SDL_FillRect(TargetSurface, NULL, 0x000000);
		for (int i = 0; i < AllSprites.size(); i++) {
			AllSprites[i]->BlitThis(TargetSurface);
		}
		//printf("BlitObjects in SpriteLayer\n");
		MakeSelfTexture(); // renders the actual texture after blitting objects.
	}
	void MakeSelfTexture() {
		if (CombinedObjects != NULL) {
			SDL_DestroyTexture(CombinedObjects);
		}
		CombinedObjects = SDL_CreateTextureFromSurface(gRenderer, TargetSurface);
	}

	//Make Que2 hold just enough information that it can hold all the Sprites order of creation. We will be using swap operations on this que to order movements.
	void AllocateQue2() {
		printf("Allocating a vector of size %d\n", AllSprites.size());
		Queue2.resize(AllSprites.size());
		for (int i = 0; i < AllSprites.size(); i++) {
			Queue2[i] = AllSprites[i];
		}
		//so the idea is that when we process the order, then want to work backwards, when we do .swap, we will then be able to go thrhough it and complete it in the order the stackc reated
	}
	//Re orders Que2 for the next set of movements
	void ReCreateQue2() {
		for (int i = 0; i < AllSprites.size(); i++) {
			Queue2[i] = AllSprites[i]->GetThis();
		}
	}
	//Adds object to AllSprites Vector, As well as places it on the initial collision map
	void MapSprite(Sprite* ObjectSprite) {
		AllSprites.push_back(ObjectSprite);


		//Add it's approx position to the matrix
		//so in LM, find this objects x and y pos, and then approx basedo n the upper left hand corner being the low value
		//it's position in the matrix. Then go down three times to the vector and put it in if applicable.

		//four values associate with possible four tiles a object could be in.
			//doesn't matter how small an object, it can only ever fit in four at a time. 
			//if it's bigger then you've got issues, maybe you can bind a larger object all together and say to ignore its partners in collision?. 




		//Put into matrix -ONLY DO ONCE PER SPRITE. 
		int x1 = NULL;
		int x2 = NULL;
		int y1 = NULL;
		int y2 = NULL;
		//The null will allow us to skip it if there is no info there.
		x1 = ObjectSprite->xPos;
		x2 = ObjectSprite->xPos + TILE_WIDTH;
		y1 = ObjectSprite->yPos;
		y2 = ObjectSprite->yPos + TILE_HEIGHT;



		int TempY2Math = y2 - TILE_HEIGHT * (y2 / TILE_HEIGHT); //A = C - B * (C/B)
		int TempX2Math = x2 - TILE_WIDTH * (x2 / TILE_WIDTH); //A = C - B * (C/B)
		if (TempX2Math == 0) {
			x2 = x1;
		}
		if (TempY2Math == 0) {
			y2 = y1;
		}



		y1 = y1 / TILE_HEIGHT;
		y2 = y2 / TILE_HEIGHT;
		x1 = x1 / TILE_WIDTH;
		x2 = x2 / TILE_WIDTH;


		//gaurds from map/matrix overflow
		if (y1 > LEVEL_HEIGHT - 1) {
			y1 = LEVEL_HEIGHT - 1;
			y2 = y1;
		}
		if (y1 < 0) {
			y1 = 0;
			y2 = y1;
		}
		if (x1 > LEVEL_WIDTH - 1) {
			x1 = LEVEL_WIDTH - 1;
			x2 = x1;
		}
		if (x1 < 0) {
			x1 = 0;
			x2 = x1;
		}


		if (true) {

			LM[y1][x1].push_back(ObjectSprite);

		}

		if (x1 != x2) {

			LM[y1][x2].push_back(ObjectSprite);

		}
		if (y1 != y2) {

			LM[y2][x1].push_back(ObjectSprite);


			if (x1 != x2) {

				LM[y2][x2].push_back(ObjectSprite);


			}
		}



	}
	void ReMapSprite(Sprite* ObjectSprite) {
		bool Debug = false;
		// printf("ReMapSprite\n");
		//Put into matrix -ONLY DO ONCE PER SPRITE. 
		int x1 = NULL;
		int x2 = NULL;
		int y1 = NULL;
		int y2 = NULL;
		int OrderedPosition = 0;
		//The null will allow us to skip it if there is no info there.
		x1 = ObjectSprite->xPos;
		x2 = ObjectSprite->xPos + TILE_WIDTH;
		y1 = ObjectSprite->yPos;
		y2 = ObjectSprite->yPos + TILE_HEIGHT;

		// printf("Remap Object%d, x1=%d, y1=%d\n", ObjectSprite->OrderCreation + 1, x1, y1);
		//NOTE - replace pushbacks with inserts - unless empty vector
		if (Debug) {
			printf("Begin Remapping Object%d\n", ObjectSprite->OrderCreation + 1);
		}
		int TempY2Math = y2 - TILE_HEIGHT * (y2 / TILE_HEIGHT); //A = C - B * (C/B)
		int TempX2Math = x2 - TILE_WIDTH * (x2 / TILE_WIDTH); //A = C - B * (C/B)
		if (TempX2Math == 0) {
			x2 = x1;
		}
		if (TempY2Math == 0) {
			y2 = y1;
		}



		y1 = y1 / TILE_HEIGHT;
		y2 = y2 / TILE_HEIGHT;
		x1 = x1 / TILE_WIDTH;
		x2 = x2 / TILE_WIDTH;


		//gaurds from map/matrix overflow
		if (y1 > LEVEL_HEIGHT - 1) {
			y1 = LEVEL_HEIGHT - 1;
			y2 = y1;
		}
		if (y1 < 0) {
			y1 = 0;
			y2 = y1;
		}
		if (x1 > LEVEL_WIDTH - 1) {
			x1 = LEVEL_WIDTH - 1;
			x2 = x1;
		}
		if (x1 < 0) {
			x1 = 0;
			x2 = x1;
		}


		if (LM[y1][x1].size() == 0) {
			if (Debug) {
				printf("a\n");
			}
			LM[y1][x1].push_back(ObjectSprite);

		}
		else {
			if (Debug) {
				printf("b\n");
			}
			while (OrderedPosition < LM[y1][x1].size() && LM[y1][x1][OrderedPosition]->OrderCreation < ObjectSprite->OrderCreation) {
				OrderedPosition++;
			}

			LM[y1][x1].insert(LM[y1][x1].begin() + OrderedPosition, ObjectSprite);

			OrderedPosition = 0;
		}
		if (x1 != x2) {

			if (LM[y1][x2].size() == 0) {
				if (Debug) {
					printf("c\n");
				}
				LM[y1][x2].push_back(ObjectSprite);
			}
			else {
				if (Debug) {
					printf("d\n");
				}
				while (OrderedPosition < LM[y1][x2].size() && LM[y1][x2][OrderedPosition]->OrderCreation < ObjectSprite->OrderCreation) {
					OrderedPosition++;
				}
				LM[y1][x2].insert(LM[y1][x2].begin() + OrderedPosition, ObjectSprite);
				OrderedPosition = 0;
			}
		}
		if (y1 != y2) {
			if (LM[y2][x1].size() == 0) {
				if (Debug) {
					printf("e\n");
				}
				LM[y2][x1].push_back(ObjectSprite);
			}
			else {
				if (Debug) {
					printf("f\n");
				}
				while (OrderedPosition < LM[y2][x1].size() && LM[y2][x1][OrderedPosition]->OrderCreation < ObjectSprite->OrderCreation) {
					OrderedPosition++;
				}
				LM[y2][x1].insert(LM[y2][x1].begin() + OrderedPosition, ObjectSprite);
				OrderedPosition = 0;
			}

			if (x1 != x2) {
				if (Debug) {
					printf("g\n");
				}
				if (LM[y2][x2].size() == 0) {
					LM[y2][x2].push_back(ObjectSprite);
				}
				else {
					while (OrderedPosition < LM[y2][x2].size() && LM[y2][x2][OrderedPosition]->OrderCreation < ObjectSprite->OrderCreation) {
						OrderedPosition++;
					}
					LM[y2][x2].insert(LM[y2][x2].begin() + OrderedPosition, ObjectSprite);
				}
			}
		}

		if (Debug) {
			printf("Done reMapping\n");
		}
	}
	void DisplayTileBasedArray() {

		for (int i = 0; i < LEVEL_HEIGHT; i++) {
			if (i < 7) {
				printf("\n R:%d", i);
			}

			for (int j = 0; j < LEVEL_WIDTH; j++) {

				if (j < 8 && i < 7) {
					printf(" C%d = [", j);

					for (int d = 0; d < std::distance(LM[i][j].begin(), LM[i][j].end()); d++) {
						printf("%d, ", LM[i][j][d]->OrderCreation);


					}
					printf("]");
				}
			}
		}
		printf("\n");

	}







	int CheckFutureSpritePosition3(Sprite* CurrentVictim, int ModxPos, int ModyPos, int ModDirection, char ModAxis) { //Mod generally tells you what we already have modified from it's original position. In otherwords, we can't use the 'true' value of hte sprite.
		bool Debug = true;
		bool Modified = false;
		//Step one, take x1, or y1, and make sure you properly 'teleported' that number for the future position
		if (Debug) {
			printf("Double check that these values seem appropraite for Object%d\n", CurrentVictim->OrderCreation + 1);
			printf("Object's Current Position = {%d, %d}\n", CurrentVictim->xPos, CurrentVictim->yPos);
			printf("Object's Proposed Position = {%d, %d}\n", ModxPos, ModyPos);
		}
		//Step two, make sure you passed in the right 'moddirection', so if your going down right, and get pushed back on the x axis, then we want to check/undo the y axis overlap.

		if (Debug) {
			if (CurrentVictim->xVec > 0 && CurrentVictim->yVec > 0) {
				printf("Actual Direction is = %d\n", 15);
			}
			else if (CurrentVictim->xVec < 0 && CurrentVictim->yVec > 0) {
				printf("Actual Direction is = %d\n", 7);
			}
			else if (CurrentVictim->xVec > 0 && CurrentVictim->yVec < 0) {
				printf("Actual Direction is = %d\n", 13);
			}

			else if (CurrentVictim->xVec < 0 && CurrentVictim->yVec < 0) {
				printf("Actual Direction is = %d\n", 5);
			}
			else {
				printf("HM? NANI\n");
				return 0;
			}
			printf("Proposed Direction (For Proposed Position) = %d\n", ModDirection);
		}

		//Step three, Mod Axis controls roughly how much we have to program at first. 
		if (ModAxis = 'x') {
			printf("The first modified axis is = x, so we wish to jostle on the y axis.\n"); //the axis of which to 'jostle' the sprite
		}
		else if (ModAxis = 'y') {
			printf("The first modified axis is = y, so we wish to jostle on the x axis.\n"); //the axis of which to 'jostle' the sprite 	 
		}
		else {
			printf("ModAxis must be either x or y\n"); return 0;
		}


		//step 4 - check for the x1 x2 y1 y2 TempMath
		//step 5 - Guard from Map/Matrix Overflow
		int x1 = ModxPos;
		int y1 = ModyPos;
		int y2 = ModyPos + TILE_HEIGHT;
		int x2 = ModxPos + TILE_WIDTH;
		int TempY2Math = y2 - TILE_HEIGHT * (y2 / TILE_HEIGHT); //A = C - B * (C/B)
		int TempX2Math = x2 - TILE_WIDTH * (x2 / TILE_WIDTH);
		//adjusts all the values to be in map bound, as well as x1==x2?.
		if (true) {
			y1 = y1 / TILE_HEIGHT;
			y2 = y2 / TILE_HEIGHT;
			x1 = x1 / TILE_WIDTH;
			x2 = x2 / TILE_WIDTH;
			//gaurds from map/matrix overflow
			if (y1 > LEVEL_HEIGHT - 1) {
				y1 = LEVEL_HEIGHT - 1;
				y2 = y1;
			}
			if (y1 < 0) {
				y1 = 0;
				y2 = y1;
			}
			if (x1 > LEVEL_WIDTH - 1) {
				x1 = LEVEL_WIDTH - 1;
				x2 = x1;
			}
			if (x1 < 0) {
				x1 = 0;
				x2 = x1;
			}
			//So we don't check further than we want to, and when we don't need to. In these cases, it doens't matter now if we use x1, or x2. For consistency, we use whatever appears the most as appropriate. 
			if (TempX2Math == 0) {
				x2 = x1;
			}
			if (TempY2Math == 0) {
				y2 = y1;
			}
		}
		printf("Proposed LM positions to Check:\nUL=LM[%d][%d]\nUR=LM[%d][%d]\nLL=LM[%d][%d]\nLR=LM[%d][%d]\n", x1, y1, x2, y1, x1, y2, x2, y2);


		//step 6 - becomes a bit unclear from here on. Obtain the directoin (somehow) known as Measure in checkfuture2
		int Measure = ModDirection;
		printf("Measure set to = %d\n", ModDirection);




		//step 7 -Store TempXOverlap, TempYOverlap, as well as two others, xOverlpped, yOverlapped=0;
		//Step 8 - Figure out hte overlap based on the future CORNER position on the LM Matrix, store the overlap in TempXOverlap, TempYOverlap.
			//This should be able to be taken directly from The Measure checks. 
		//Step 9 - Pushback to SpriteOVerlapX, or SpriteOverlapY vectors.
			//Reset the TempX/YOverlap to 0. 
			//Vector that holds the 'area' of overlap - this is to be compared with, and then swapped if one with larger area shows up
			//if tie, look at order creation

			//Okay Laymen, check the end of each measure will show you I'm storing a ptr to the sprite, and then the overlap associated. WE DO GET DUPLICATES, because of how we're finding it. still worth it for the most aprt for speed.
			//That's the purpose of Jacks inserted code, to get rid of duplicates I beleive. 
			//The reason why we have two vectors, one with ptrs, one with actaul integers,i s so we can sort it according to what is ran into first.
		std::vector<int> SpriteX = {};
		std::vector<int> SpriteY = {};
		//vector that holds the pointer itself. to be returned as a stack
		std::vector<Sprite*> SpriteOverlapX = {};
		std::vector<Sprite*> SpriteOverlapY = {};
		int TempXOverlap = 0;
		int TempYOverlap = 0;
		if (true) {
			//bug caused if you don't check that it's overlapepd at least one pixel.
			int xOverlapped = 0; //used exclusively to test for true collision dimension
			int yOverlapped = 0; //used exclusively to test for true collision dimension.
			//base l,r,u,d directions
			if (Measure == 11) {//D
				//edges are [x1][y2] and [x2][y2]
				printf("Measure == 11\n");
				if (Debug && PAUSECOLLISIONJOSTLE[0] == 0) {
					printf("%d", TOTALFRAMECOUNT);
					PAUSECOLLISIONJOSTLE[0] = 1;
					printf("First Jostle int he down direction\n");
					SDL_Delay(10000);
					Modified = true;
				}
				if (TempX2Math == 0) {
					if (Debug) {
						printf("al\n");
					}
					for (int i = 0; i < LM[y2][x1].size(); i++) {

						//Figureout if the overlap is at least 1
						if (true) {
							if (LM[y2][x1][i]->xPos > ModxPos) {
								xOverlapped = ModxPos + TILE_WIDTH - LM[y2][x1][i]->xPos;
							}
							else { //if (Spos =< Posx 
								xOverlapped = LM[y2][x1][i]->xPos + TILE_WIDTH - ModxPos;
							}
							if (xOverlapped > 0 && xOverlapped < 17) {
								if (Debug) {
									printf("Truely overalpped with something (Going Down, at least one x pixel overlap LL)\n");
								}
							}
						}

						//Figureout the actual overlap to be recorded (LL)
						if (true) {
							if (LM[y2][x1][i]->yPos > ModyPos) {
								TempYOverlap = ModyPos + TILE_HEIGHT - LM[y2][x1][i]->yPos;
							}
							else {
								TempYOverlap = LM[y2][x1][i]->yPos + TILE_HEIGHT - ModyPos;
							}
						}

						//Pushback
						printf("1) [y2][x1] xOverlap = %d, TempYOverlap = %d\n", xOverlapped, TempYOverlap);
						if ((xOverlapped > 0 && xOverlapped < 17) && TempYOverlap < 17 && TempYOverlap > 0) {
							SpriteOverlapY.push_back(LM[y2][x1][i]);
							SpriteY.push_back(TempYOverlap);
							xOverlapped = 0;
							TempYOverlap = 0;
						}
					}
				}
				else {
					if (Debug) {
						printf("am\n");
					}
					for (int i = 0; i < LM[y2][x1].size(); i++) {

						//Figureout if the overlap is at least 1
						if (true) {
							xOverlapped = LM[y2][x1][i]->xPos + TILE_WIDTH - ModxPos;
							if (xOverlapped > 0 && xOverlapped < 17) {
								if (Debug) {
									printf("Truely overalpped with something (Going Down, at least one x pixel overlap LL)\n");
								}
							}
						}

						//Figureout the actual overlap to be recorded (LL)
						if (true) {
							if (LM[y2][x1][i]->yPos > ModyPos) {
								TempYOverlap = ModyPos + TILE_HEIGHT - LM[y2][x1][i]->yPos;
							}
							else {
								TempYOverlap = LM[y2][x1][i]->yPos + TILE_HEIGHT - ModyPos;
							}
						}

						//Pushback
						printf("2) [y2][x1] xOverlap = %d, TempYOverlap = %d\n", xOverlapped, TempYOverlap);
						if ((xOverlapped > 0 && xOverlapped < 17) && TempYOverlap < 17 && TempYOverlap > 0) {
							SpriteOverlapY.push_back(LM[y2][x1][i]);
							SpriteY.push_back(TempYOverlap);
							xOverlapped = 0;
							TempYOverlap = 0;
						}

					}
					if (Debug) {
						printf("an\n");
					}
					for (int i = 0; i < LM[y2][x2].size(); i++) {

						//Figureout if the overlap is at least 1
						if (true) {
							if (LM[y2][x2][i]->xPos > ModxPos) {
								xOverlapped = ModxPos + TILE_WIDTH - LM[y2][x2][i]->xPos;
							}
							else { //if (Spos =< Posx
								xOverlapped = LM[y2][x2][i]->xPos + TILE_WIDTH - ModxPos;
							}
							if (xOverlapped > 0 && xOverlapped < 17) {
								if (Debug) {
									printf("Truely overalpped with something (Going Down, at least one x pixel overlap LR)\n");
								}
							}
						}

						//Figureout the actual overlap to be recorded (LR)
						if (true) {
							if (LM[y2][x2][i]->yPos > ModyPos) {
								TempYOverlap = ModyPos + TILE_HEIGHT - LM[y2][x2][i]->yPos;
							}
							else {
								TempYOverlap = LM[y2][x2][i]->yPos + TILE_HEIGHT - ModyPos;
							}
						}

						//Pushback
						printf("3) [y2][x2] xOverlap = %d, TempYOverlap = %d\n", xOverlapped, TempYOverlap);
						if ((xOverlapped > 0 && xOverlapped < 17) && TempYOverlap < 17 && TempYOverlap > 0) {
							SpriteOverlapY.push_back(LM[y2][x2][i]);
							SpriteY.push_back(TempYOverlap);
							xOverlapped = 0;
							TempYOverlap = 0;
						}

					}
				}
			}
			else if (Measure == 6) {//L
			//edges are [x1][y1] and [x1][y2]
				if (Debug && PAUSECOLLISIONJOSTLE[1] == 0) {
					printf("%d", TOTALFRAMECOUNT);
					PAUSECOLLISIONJOSTLE[1] = 1;
					printf("First Jostle int he left direction\n");
					SDL_Delay(10000);
					Modified = true;
				}
				if (TempY2Math == 0) {
					if (Debug) {
						printf("af\n");
					}
					for (int i = 0; i < LM[y1][x1].size(); i++) {

						//Figureout if the overlap is at least 1
						if (true) {
							if (LM[y1][x1][i]->yPos > ModyPos) {
								yOverlapped = ModyPos + TILE_HEIGHT - LM[y1][x1][i]->yPos;
							}
							else { //if (Spos =< Posy 
								yOverlapped = LM[y1][x1][i]->yPos + TILE_HEIGHT - ModyPos;
							}
							if (yOverlapped > 0 && yOverlapped < 17) {
								//old debug statement would go here. Archaic
							}
						}

						//Overlap to be recorded
						if (true) {
							if (LM[y1][x1][i]->xPos > ModxPos) { //NEW (CHANGED)
								TempXOverlap = ModxPos + TILE_WIDTH - LM[y1][x1][i]->xPos;
							}
							else {
								TempXOverlap = LM[y1][x1][i]->xPos + TILE_WIDTH - ModxPos;
							}
						}

						//Pushback
						printf("1) [y1][x1] yOverlap = %d, TempYOverlap = %d\n", yOverlapped, TempXOverlap);
						if ((yOverlapped > 0 && yOverlapped < 17) && TempXOverlap < 17 && TempXOverlap > 0) {
							SpriteOverlapX.push_back(LM[y1][x1][i]);
							SpriteX.push_back(TempXOverlap);
							yOverlapped = 0;
							TempXOverlap = 0;

						}
					}
				}
				else {
					if (Debug) {
						printf("ag\n");
					}
					for (int i = 0; i < LM[y1][x1].size(); i++) {

						//Figureout if the overlap is at least 1
						if (true) {

							yOverlapped = LM[y1][x1][i]->yPos + TILE_HEIGHT - ModyPos;

							if (yOverlapped > 0 && yOverlapped < 17) {
								//archaic
							}
						}

						//Overlap to be recorded
						if (true) {
							if (LM[y1][x1][i]->xPos > ModxPos) { //NEW (CHANGED)
								TempXOverlap = ModxPos + TILE_WIDTH - LM[y1][x1][i]->xPos;
							}
							else {
								TempXOverlap = LM[y1][x1][i]->xPos + TILE_WIDTH - ModxPos;
							}
						}

						//Pushback
						printf("2) [y1][x1] yOverlap = %d, TempYOverlap = %d\n", yOverlapped, TempXOverlap);
						if ((yOverlapped > 0 && yOverlapped < 17) && TempXOverlap < 17 && TempXOverlap > 0) {
							SpriteOverlapX.push_back(LM[y1][x1][i]);
							SpriteX.push_back(TempXOverlap);
							yOverlapped = 0;
							TempXOverlap = 0;

						}
					}
					if (Debug) {
						printf("ah\n");
					}
					for (int i = 0; i < LM[y2][x1].size(); i++) {

						//Figureout if the overlap is at least 1
						if (true) {
							if (LM[y2][x1][i]->yPos > ModyPos) {
								yOverlapped = ModyPos + TILE_HEIGHT - LM[y2][x1][i]->yPos;
							}
							else { //if (Spos =< Posy  
								yOverlapped = LM[y2][x1][i]->yPos + TILE_HEIGHT - ModyPos;
							}
							if (yOverlapped > 0 && yOverlapped < 17) {
								//archaic
							}
						}

						//Overlap to be recorded
						if (true) {
							if (LM[y2][x1][i]->xPos > ModxPos) { //NEW (CHANGED)
								TempXOverlap = ModxPos + TILE_WIDTH - LM[y2][x1][i]->xPos;
							}
							else {
								TempXOverlap = LM[y2][x1][i]->xPos + TILE_WIDTH - ModxPos;
							}
						}

						//Pushback
						printf("3) [y2][x1] yOverlap = %d, TempYOverlap = %d\n", yOverlapped, TempXOverlap);
						if ((yOverlapped > 0 && yOverlapped < 17) && TempXOverlap < 17 && TempXOverlap > 0) {
							SpriteOverlapX.push_back(LM[y2][x1][i]);
							SpriteX.push_back(TempXOverlap);
							yOverlapped = 0;
							TempXOverlap = 0;

						}
					}
				}
			}
			else if (Measure == 14) {//R
				//edges are [x2][y1] and [x2][y2]
				if (TempY2Math == 0) {
					if (Debug) {
						printf("ai\n");
					}
					for (int i = 0; i < LM[y1][x2].size(); i++) {

						//Figureout if the overlap is at least 1
						if (true) {
							if (LM[y1][x2][i]->yPos > ModyPos) {
								yOverlapped = ModyPos + TILE_HEIGHT - LM[y1][x2][i]->yPos;
							}
							else { //if (Spos =< Posy   
								yOverlapped = LM[y1][x2][i]->yPos + TILE_HEIGHT - ModyPos;
							}
							if (yOverlapped > 0 && yOverlapped < 17) {
								if (Debug) {
									printf("Truely overalpped with something (Going Right, at least one x pixel overlap UR)\n");
								}
							}
						}

						//Overlap to be recorded
						if (true) {
							if (LM[y1][x2][i]->xPos > ModxPos) { //NEW (CHANGED)
								TempXOverlap = ModxPos + TILE_WIDTH - LM[y1][x2][i]->xPos;

							}
							else {
								TempXOverlap = LM[y1][x2][i]->xPos + TILE_WIDTH - ModxPos;

							}
						}

						//Pushback
						printf("1) [y1][x2] yOverlap = %d, TempYOverlap = %d\n", yOverlapped, TempXOverlap);
						if ((yOverlapped > 0 && yOverlapped < 17) && TempXOverlap < 17 && TempXOverlap > 0) {
							SpriteOverlapX.push_back(LM[y1][x2][i]);
							SpriteX.push_back(TempXOverlap);
							yOverlapped = 0;
							TempXOverlap = 0;
						}
					}
				}
				else {
					if (Debug) {
						printf("aj\n");
					}
					for (int i = 0; i < LM[y1][x2].size(); i++) {

						//Figureout if the overlap is at least 1
						if (true) {

							yOverlapped = LM[y1][x2][i]->yPos + TILE_HEIGHT - ModyPos;



							if (yOverlapped > 0 && yOverlapped < 17) {
								if (Debug) {
									printf("Truely overalpped with something (Going Right, at least one x pixel overlap UR)\n");
								}
							}
						}

						//Overlap to be recorded
						if (true) {
							if (LM[y1][x2][i]->xPos > ModxPos) {//NEW (CHANGED)
								TempXOverlap = ModxPos + TILE_WIDTH - LM[y1][x2][i]->xPos;

							}
							else {
								TempXOverlap = LM[y1][x2][i]->xPos + TILE_WIDTH - ModxPos;

							}
						}

						//Pushback
						printf("2) [y1][x2] yOverlap = %d, TempYOverlap = %d\n", yOverlapped, TempXOverlap);
						if ((yOverlapped > 0 && yOverlapped < 17) && TempXOverlap < 17 && TempXOverlap > 0) {
							SpriteOverlapX.push_back(LM[y1][x2][i]);
							SpriteX.push_back(TempXOverlap);
							yOverlapped = 0;
							TempXOverlap = 0;
						}
					}
					if (Debug) {
						printf("ak\n");
					}
					for (int i = 0; i < LM[y2][x2].size(); i++) {

						//Figureout if the overlap is at least 1
						if (true) {
							if (LM[y2][x2][i]->yPos > ModyPos) {
								yOverlapped = ModyPos + TILE_HEIGHT - LM[y2][x2][i]->yPos;
							}
							else { //if (Spos =< Posy
								yOverlapped = LM[y2][x2][i]->yPos + TILE_HEIGHT - ModyPos;
							}
							if (yOverlapped > 0 && yOverlapped < 17) {
								if (Debug) {
									printf("Truely overalpped with something (Going Right, at least one x pixel overlap LR)\n");
								}
							}
						}

						//Overlap to be recorded
						if (true) {
							if (LM[y2][x2][i]->xPos > ModxPos) {//NEW (CHANGED)
								TempXOverlap = ModxPos + TILE_WIDTH - LM[y2][x2][i]->xPos;

							}
							else {
								TempXOverlap = LM[y2][x2][i]->xPos + TILE_WIDTH - ModxPos;
							}
						}

						//Pushback
						printf("3) [y2][x2] yOverlap = %d, TempYOverlap = %d\n", yOverlapped, TempXOverlap);
						if ((yOverlapped > 0 && yOverlapped < 17) && TempXOverlap < 17 && TempXOverlap > 0) {
							SpriteOverlapX.push_back(LM[y2][x2][i]);
							SpriteX.push_back(TempXOverlap);
							yOverlapped = 0;
							TempXOverlap = 0;
						}
					}
				}
			}
			else if (Measure == 9) {//U
				//edges are [x1][y1] and [x2][x1]
				if (TempX2Math == 0) {
					if (Debug) {
						printf("ao\n");
					}
					for (int i = 0; i < LM[y1][x1].size(); i++) {

						//Figureout if the overlap is at least 1
						if (true) {
							if (LM[y1][x1][i]->xPos > ModxPos) {
								xOverlapped = ModxPos + TILE_WIDTH - LM[y1][x1][i]->xPos;
							}
							else { //if (Spos =< Posx 
								xOverlapped = LM[y1][x1][i]->xPos + TILE_WIDTH - ModxPos;
							}
							if (xOverlapped > 0 && xOverlapped < 17) {
								if (Debug) {
									printf("Truely overalpped with something (Going UP, at least one x pixel overlap UL)\n");
								}
							}
						}

						//Overlap to be recorded
						if (true) {
							if (LM[y1][x1][i]->yPos < ModyPos) {
								TempYOverlap = LM[y1][x1][i]->yPos + TILE_HEIGHT - ModyPos;
							}
							else {
								TempYOverlap = ModyPos + TILE_HEIGHT - LM[y1][x1][i]->yPos;
							}
						}

						//Pushback
						printf("1) [y1][x1] yOverlap = %d, TempYOverlap = %d\n", xOverlapped, TempYOverlap);
						if ((xOverlapped > 0 && xOverlapped < 17) && TempYOverlap < 17 && TempYOverlap > 0) {
							SpriteOverlapY.push_back(LM[y1][x1][i]);
							SpriteY.push_back(TempYOverlap);
							xOverlapped = 0;
							TempYOverlap = 0;
						}
					}
				}
				else {
					if (Debug) {
						printf("ap\n");
					}
					for (int i = 0; i < LM[y1][x1].size(); i++) {

						//Figureout if the overlap is at least 1
						if (true) {

							xOverlapped = LM[y1][x1][i]->xPos + TILE_WIDTH - ModxPos;

							if (xOverlapped > 0 && xOverlapped < 17) {
								if (Debug) {
									printf("Truely overalpped with something (Going UP, at least one x pixel overlap UL)\n");
								}
							}
						}

						//Overlap to be Recorded
						if (true) {
							if (LM[y1][x1][i]->yPos < ModyPos) {
								TempYOverlap = LM[y1][x1][i]->yPos + TILE_HEIGHT - ModyPos;
							}
							else {
								TempYOverlap = ModyPos + TILE_HEIGHT - LM[y1][x1][i]->yPos;
							}
						}

						//Pushback
						printf("2) [y1][x1] yOverlap = %d, TempYOverlap = %d\n", xOverlapped, TempYOverlap);
						if ((xOverlapped > 0 && xOverlapped < 17) && TempYOverlap < 17 && TempYOverlap > 0) {
							SpriteOverlapY.push_back(LM[y1][x1][i]);
							SpriteY.push_back(TempYOverlap);
							xOverlapped = 0;
							TempYOverlap = 0;
						}
					}
					if (Debug) {
						printf("aq\n");
					}
					for (int i = 0; i < LM[y1][x2].size(); i++) {

						//Figureout if the overlap is at least 1
						if (true) {
							if (LM[y1][x2][i]->xPos > ModxPos) {
								xOverlapped = ModxPos + TILE_WIDTH - LM[y1][x2][i]->xPos;
							}
							else { //if (Spos =< Posx
								xOverlapped = LM[y1][x2][i]->xPos + TILE_WIDTH - ModxPos;
							}
							if (xOverlapped > 0 && xOverlapped < 17) {
								if (Debug) {
									printf("Truely overalpped with something (Going UP, at least one x pixel overlap UR)\n");
								}
							}
						}

						//Overlap to be recorded
						if (true) {
							if (LM[y1][x2][i]->yPos < ModyPos) {
								TempYOverlap = LM[y1][x2][i]->yPos + TILE_HEIGHT - ModyPos;
							}
							else {
								TempYOverlap = ModyPos + TILE_HEIGHT - LM[y1][x2][i]->yPos;
							}
						}

						//Pushback
						printf("3) [y1][x2] yOverlap = %d, TempYOverlap = %d\n", xOverlapped, TempYOverlap);
						if ((xOverlapped > 0 && xOverlapped < 17) && TempYOverlap < 17 && TempYOverlap > 0) {
							SpriteOverlapY.push_back(LM[y1][x2][i]);
							SpriteY.push_back(TempYOverlap);
							xOverlapped = 0;
							TempYOverlap = 0;
						}


					}
				}
			}
			else {
				if (Debug) {
					printf("Measure doesn't make sense! [CheckFuture3]\n");
				}
			}
		}
		//Step 9.5 - I want to doble check that I'm not getting a list that doesn't make sense, but I also just want to see it printed
		if (true) {
			printf("\n\nIf we hit anything at all, we should see it:\n");
			if (SpriteX.size() > 0) {
				printf("SpriteX = {");
				for (int i = 0; i < SpriteX.size(); i++) {
					printf("%d, ", SpriteX[i]);
				}
				printf("}\n");

				printf("SpriteOverlapX = {");
				for (int i = 0; i < SpriteX.size(); i++) {
					printf("Object%d, ", SpriteOverlapX[i]->OrderCreation + 1);
				}
				printf("}\n");
			}

			if (SpriteY.size() > 0) {
				printf("SpriteY = {");
				for (int i = 0; i < SpriteY.size(); i++) {
					printf("%d, ", SpriteY[i]);
				}
				printf("}\n");

				printf("SpriteOverlapY = {");
				for (int i = 0; i < SpriteY.size(); i++) {
					printf("Object%d, ", SpriteOverlapY[i]->OrderCreation + 1);
				}
				printf("}\n");
			}
			printf("\n\n");
		}
		//step 9.6 - prune and sort (in the event you have overlapped with multiple sprites
		//Step10 - after the overlap's all be nstorred, we will merge sort it into a new vector, SpriteOVerlapX, SpriteOverlapY, and SpriteX, and SpriteY that hold overlap values

			//PRUNE -Eliminate any dobules, and anything that doesn't collide. For now assume everything you overlap with collides -Sort by overlap most, figure out the order of collision. 
			//mergesort then merge
			//then prune doubles
			//then prune those without collision
		if (true) {
			/*
			//using swap since it's constant as opposed to insert.
			//also if we get one that is the exact same creation order, we want to erase it rather than swap it.
			std::vector<int> HaveSeen = {};
			bool found = false;
			//eliminate all doubles
			/*
			for (int i = 0; i < SpriteOverlap.size(); i++) {
				for (int j = 0; j < HaveSeen.size(); j++) { //would like a better version of this that stops when found
					if (SpriteOverlap[i]->OrderCreation == HaveSeen[j]) {
						found = true;
					}
				}
				if (found = true) {
					SpriteOverlap.erase(SpriteOverlap.begin() + i);
					SpriteArea.erase(SpriteArea.begin()+i);
					i--; //to balance out the erasure and the itteration of hte loop
				}
				else {
					HaveSeen.push_back(SpriteOverlap[i]->OrderCreation);
				}
				found = false;
			}
			//sort the stack by priority of colliding first. So it should go {this, ..., collides third, collides second, collides first}
			//This will differ from the previous tile collision because NOW we have every single tile possibly creating a localized stack. it is easier to find deadlocks probably. this also brings more value to a holder for items we have successfully moved.
			//for now we'll do a merge sort, but in the future we want to weigh how many things an object collided with/overlapped, and then sort it based on the size. If you say, collide with 100 objects, it is wort hdoing a merge sort or binary.
			MergeSortSpriteCollision(SpriteOverlap, SpriteArea, 0, SpriteOverlap.size());
			*/

			//merge sort each side individually
			SpriteOverlapX; //holds pointers to those overlapping x
			SpriteOverlapY; //hlds poitners to those overlapping y
			SpriteX; //holds x overlap values
			SpriteY; //holds y overlap values
			if (SpriteOverlapX.size() > 0) {
				MergeSortSpriteCollision(SpriteOverlapX, SpriteX);
			}
			if (SpriteOverlapY.size() > 0) {
				MergeSortSpriteCollision(SpriteOverlapY, SpriteY);
			}

		}
		//NOTE - jacks code might not be finding and pruning duplicates, but it may be.
		//jack (inserted here hope its right) - here is fine, we will improve the merge eventually so this bit would be faster.
		int xloop = 0;
		int yloop = 0;
		if (true) {
			if (SpriteOverlapX.size() > 1) {
				while (xloop < SpriteOverlapX.size() - 1) {
					for (int i = xloop + 1; i < SpriteOverlapX.size(); i++) {
						if (SpriteOverlapX[xloop] == SpriteOverlapX[i]) {
							SpriteOverlapX.erase(SpriteOverlapX.begin() + i);
							SpriteX.erase(SpriteX.begin() + i);
							i--;
						}
					}
					xloop++;
				}
			}
			if (SpriteOverlapY.size() > 1) {
				while (yloop < SpriteOverlapY.size() - 1) {
					for (int i = yloop + 1; i < SpriteOverlapY.size(); i++) {
						if (SpriteOverlapY[yloop] == SpriteOverlapY[i]) {
							SpriteOverlapY.erase(SpriteOverlapY.begin() + i);
							SpriteY.erase(SpriteY.begin() + i);
							i--;
						}
					}
					yloop++;
				}
			}
			//end of Jacks insertion. I should check this later. - I believe this gets rid of duplicates in the collision list (because multiple corners could collide, or a sprite may occupy two cells and be collided with by two different corners for hte check or something
			if (Debug) {
				if (Measure != 10) {
					printf("Direction for the moving sprite is = %d\n", Measure);
					printf("Moving Sprite positions = {xPos= %d, yPos= %d}\n", ModxPos, ModyPos);
				}
				if (SpriteOverlapX.size() > 0) {
					printf("Every item in the SpriteOverlapX =");
					for (int i = 0; i < SpriteOverlapX.size(); i++) {
						printf("{Object%d, ", SpriteOverlapX[i]->OrderCreation + 1);
						printf("Overlap = %d, xPos=%d, yPos=%d}", SpriteX[i], SpriteOverlapX[i]->xPos, SpriteOverlapX[i]->yPos);
						if (SpriteX[i] > 0) {

						}
					}
					printf("\n");
				}
				if (SpriteOverlapY.size() > 0) {
					printf("Every item in the SpriteOverlapY =");
					for (int i = 0; i < SpriteOverlapY.size(); i++) {
						printf("{Object%d, ", SpriteOverlapY[i]->OrderCreation + 1);
						printf("Overlap = %d, xPos=%d, yPos=%d}", SpriteY[i], SpriteOverlapY[i]->xPos, SpriteOverlapY[i]->yPos);
						if (SpriteY[i] > 0) {

						}
					}
					printf("\n");
				}
			}
			if (Debug) {
				if ((SpriteOverlapY.size() > 0 || SpriteOverlapX.size() > 0)) {
					printf("Take Time to ensure the above looks correct for Object%d.\n", CurrentVictim->OrderCreation + 1);
				}
				if (SpriteOverlapY.size() > 2 || SpriteOverlapX.size() > 2) {
					printf("Double check that duplicates are actually gotten rid of. Pretty sure jacks code does so but I forget.\n");
					SDL_Delay(360000);
				}
			}
		}










		//Now the code jack insterted code. forgot what it does exactly. I believe it's to sift through and only take the most collision? Or something?
		//Step 11 - in the other one, CheckFuture 2 we woudl return the TempStackable, HOWEVER we don't, we will just take the highest, most relevant collision type overlap and adjust according to that. 
		if (Debug) {
			//figure out for hte printf
			if (SpriteY.size() > 0) {
				if (Measure == 11) {
					ModyPos = ModyPos - SpriteY[SpriteY.size() - 1];
				}
				else if (Measure == 9) {
					ModyPos = ModyPos + SpriteY[SpriteY.size() - 1];

				}
			}
			if (SpriteX.size() > 0) {
				if (Measure == 6) {
					ModxPos = ModxPos + SpriteX[SpriteX.size() - 1];
				}
				else if (Measure == 14) {
					ModxPos = ModxPos - SpriteX[SpriteX.size() - 1];
				}
			}

			printf("Object's Proposed Jostled Position = {%d, %d}\n", ModxPos, ModyPos);
			if (Debug && Modified) {
				SDL_Delay(10000);
			}
		}

		//so instead of returning the whole vector of collisions, I'm only interested in the one you overlap most with (likely the first one you collided with with the current way we're doing things)
		//that will be stored at the end of the vector.
		if (SpriteY.size() > 0) {
			return SpriteY[SpriteY.size() - 1]; //return end overlap (because it will be the sprite you likely collide with, but we only care about the integer itself.
		}
		if (SpriteX.size() > 0) {
			return SpriteX[SpriteX.size() - 1]; //we should only have a list of one or the other, not both.
		}



		if (ModAxis == 'x') {
			printf("No collisions on y axis\n");
		}
		if (ModAxis == 'y') {
			printf("No collisions on x axis\n");
		}
		return 0; //default

	}

	void FigureOverlap(Sprite* CurrentVictim, Sprite* Xptr[2], Sprite* Yptr[2], int OverlapX[2], int OverlapY[2], bool& wait) {
		//will have to test that the arrays are edited back in the MoveAllSprites 
		//NOTE, we should change each of these to resemble the logic in xChange>0

		bool Debug = true;

		if (Debug) {
			printf("XY = {%d, %d}\n", OverlapX[0], OverlapY[1]);
		}

		if (Debug) {

			if (Xptr[0] != nullptr && Yptr[1] != nullptr) {
				if (Xptr[0] != Yptr[1]) {
					printf("DIAGONAL COLLISION: ");
				}
				printf("Object%d, Object%d\n", Xptr[0]->OrderCreation + 1, Yptr[1]->OrderCreation + 1);
			}
			else if (Xptr[0] != nullptr) {
				printf("X = Object%d\n", Xptr[0]->OrderCreation + 1);
			}
			else if (Yptr[1] != nullptr) {
				printf("Y = Object%d\n", Yptr[1]->OrderCreation + 1);
			}
		}
		int XC;
		int YC;
		int xChange = CurrentVictim->xVec;
		int yChange = CurrentVictim->yVec;
		//calculate overlap according to direction

		if (Debug) {
			printf("CALCULATE X\n");
		}
		if (Xptr[0] != nullptr) {
			if (xChange > 0) { // if moving right
				if (Debug) {
					printf("Sprite was moving Right\n");
				}
				if (Xptr[0]->xPos > CurrentVictim->xPos) {
					XC = CurrentVictim->xPos + TILE_WIDTH - Xptr[0]->xPos; //object 4={64, 0}, obj5 ={79, 0}. 64+16-79=1, so 79+1 is where obj 5 would be without overlap. 
					if (Debug) {
						printf("Attempt 1: XC = %d\n", XC);
					}
				}
				else {
					XC = Xptr[0]->xPos + TILE_WIDTH - CurrentVictim->xPos; //object 4={64, 0}, obj5 ={79, 0}. 64+16-79=1, so 79+1 is where obj 5 would be without overlap.
					if (Debug) {
						printf("Attempt 2: XC = %d\n", XC);
					}
				}

				if (XC > 16 || XC < 0) {
					XC = CurrentVictim->xPos + TILE_WIDTH - Xptr[0]->xPos; //object 4={64, 0}, obj5 ={79, 0}. 64+16-79=1, so 79+1 is where obj 5 would be without overlap. 
					if (Debug) {
						printf("Attempt 3: XC = %d\n", XC);
					}
				}
				/*
				if (XC == 16) {
					XC = 0;
				}
				*/
				if (Debug) {
					printf("1 TempOverlapX=%d\n", XC);
				}
				pause = true;
				/* if (XC == 0) {
					XC = 16;
				}*/
			}
			else { // if moving left
				printf("Sprite was moving Left\n");
				if (Xptr[0]->xPos > CurrentVictim->xPos) {
					XC = CurrentVictim->xPos + TILE_WIDTH - Xptr[0]->xPos; //object 4={64, 0}, obj5 ={79, 0}. 64+16-79=1, so 79+1 is where obj 5 would be without overlap. 
					printf("Attempt 1: XC = %d\n", XC);
				}
				else {
					XC = CurrentVictim->xPos + TILE_WIDTH - Xptr[0]->xPos; //object 4={64, 0}, obj5 ={79, 0}. 64+16-79=1, so 79+1 is where obj 5 would be without overlap. 
					XC = Xptr[0]->xPos + TILE_WIDTH - CurrentVictim->xPos; //object 4={64, 0}, obj5 ={79, 0}. 64+16-79=1, so 79+1 is where obj 5 would be without overlap.
					printf("Attempt 2: XC = %d\n", XC);
				}
				/*
				if (XC == 16) {
					XC = 0;
				}
				*/
				printf("2 TempOverlapX=%d\n", XC);
				pause = true;
				/* if (XC == 0) {
					XC = 16;
				}*/

			}
		}
		else {
			if (Debug) {
				printf("nullptr passed for Xptr\n");
			}
			XC = 0;
		}
		if (Debug) {
			printf("CALCULATE Y\n");
		}
		if (Yptr[1] != nullptr) {
			if (yChange > 0) { // if moving down
				if (Debug) {

					printf("Sprite was moving down\n");
				}
				YC = CurrentVictim->yPos + TILE_HEIGHT - Yptr[1]->yPos; //insert virtually the same check used for checkfuture 2, to ensure consistency among objects that move morethan 1 pxl at a time.
				if (Debug) {
					printf("Attempt 1: YC = %d\n", YC);
				}
				YC = Yptr[1]->yPos + TILE_HEIGHT - CurrentVictim->yPos; //insert virtually the same check used for checkfuture 2, to ensure consistency among objects that move morethan 1 pxl at a time.
				if (Debug) {
					printf("Attempt 2: YC = %d\n", YC);
				}if (YC > 16 || YC < 0) {
					YC = CurrentVictim->yPos + TILE_HEIGHT - Yptr[1]->yPos; //insert virtually the same check used for checkfuture 2, to ensure consistency among objects that move morethan 1 pxl at a time.
					if (Debug) {
						printf("Attempt 3: YC = %d\n", YC);
					}
				}
				/*
				if (YC == 16) {
					YC = 0;
				}
				*/
				if (Debug) {
					printf("3 TempOverlapY=%d\n", YC);
				}
				pause = true;
				/* if (YC == 0) {
					YC = 16;
				}*/

			}
			else { // if moving up
				if (Debug) {
					printf("Sprite was moving up\n");
				}
				YC = CurrentVictim->yPos + TILE_HEIGHT - Yptr[1]->yPos; //insert virtually the same check used for checkfuture 2, to ensure consistency among objects that move morethan 1 pxl at a time.
				if (Debug) {
					printf("Attempt 1: YC = %d\n", YC);
				}
				YC = Yptr[1]->yPos + TILE_HEIGHT - CurrentVictim->yPos; //insert virtually the same check used for checkfuture 2, to ensure consistency among objects that move morethan 1 pxl at a time.
				if (Debug) {
					printf("Attempt 2: YC = %d\n", YC);
				}
				if (YC > 16 || YC < 0) {
					YC = CurrentVictim->yPos + TILE_HEIGHT - Yptr[1]->yPos; //insert virtually the same check used for checkfuture 2, to ensure consistency among objects that move morethan 1 pxl at a time.
					if (Debug) {
						printf("Attempt 3: YC = %d\n", YC);
					}
				}
				/*
				if (YC == 16) {
					YC = 0;
				}
				*/
				//YC = CurrentVictim->yPos + TILE_WIDTH - TempStackable->SpriteYCollision[y - 1]->yPos; //insert virtually the same check used for checkfuture 2, to ensure consistency among objects that move morethan 1 pxl at a time.
				if (Debug) {
					printf("4 TempOverlapY=%d\n", YC);
				}
				pause = true;
				/* if (YC == 0) {
					YC = 16;
				}*/

			}
		}
		else {
			if (Debug) {
				printf("nullptr passed for Yptr\n");
			}
			YC = 0;
		}


		OverlapX[0] = XC;
		OverlapY[1] = YC;
		if (Debug) {
			printf("4 TempOverlapY=%d\n", YC);
			printf("2 TempOverlapX=%d\n", XC);
			printf("XY = {%d, %d}\n", OverlapX[0], OverlapY[1]);
		}


		//NEW stuff, trying to jostle in this if statement
		if (CurrentVictim->xVec != 0 && CurrentVictim->yVec != 0 && (Xptr[0] != Yptr[1])) {
			//corners for 'teleport', so adjusted for it's future movement position (already done in ahdnlevictim), then teleport (done in this next if), then jostle, then return the jostle into the appropriate VC.
			int x1 = CurrentVictim->xPos;
			int y1 = CurrentVictim->yPos;
			if (YC == 0 && XC != 0) {
				if (Debug) {
					printf("Y Axis needs to be checked after a 'teleport' on the X Axis\n");
				}
				if (CurrentVictim->xVec > 0) { //going right
					if (CurrentVictim->yVec > 0) {
						if (Debug) {
							printf("1\n");
						}
						YC = CheckFutureSpritePosition3(CurrentVictim, x1 - XC, y1, 11, 'y'); //just going down
					}
					else {
						if (Debug) {
							printf("2\n");
						}
						YC = CheckFutureSpritePosition3(CurrentVictim, x1 - XC, y1, 9, 'y'); //just going up
					}
				}
				else { //going left
					if (CurrentVictim->yVec > 0) {
						if (Debug) {
							printf("3\n");
						}
						YC = CheckFutureSpritePosition3(CurrentVictim, x1 + XC, y1, 11, 'x'); //just going down
					}
					else {
						if (Debug) {
							printf("4\n");
						}
						YC = CheckFutureSpritePosition3(CurrentVictim, x1 + XC, y1, 9, 'x'); //just going up
					}
				}
			}
			else if (YC != 0 && XC == 0) {
				if (Debug) {
					printf("X Axis needs to be checked after a 'teleport' on the Y Axis\n");
				}
				if (CurrentVictim->yVec > 0) { //going down
					if (CurrentVictim->xVec > 0) {
						if (Debug) {
							printf("5\n");
						}
						XC = CheckFutureSpritePosition3(CurrentVictim, x1, y1 - YC, 14, 'y'); //just going right
					}
					else {
						if (Debug) {
							printf("6\n");
						}
						XC = CheckFutureSpritePosition3(CurrentVictim, x1, y1 - YC, 6, 'y'); //just going left
					}
				}
				else { //going up
					if (CurrentVictim->xVec > 0) {
						if (Debug) {
							printf("7\n");
						}
						XC = CheckFutureSpritePosition3(CurrentVictim, x1, y1 + YC, 9, 'y'); //just going right
					}
					else {
						if (Debug) {
							printf("8\n");
						}
						XC = CheckFutureSpritePosition3(CurrentVictim, x1, y1 + YC, 9, 'y'); //just going left
					}
				}
			}
		}
		if (Debug) {
			printf("After Jostling\n");
		}
		OverlapX[0] = XC;
		OverlapY[1] = YC;
		if (Debug) {
			printf("4 TempOverlapY=%d\n", YC);
			printf("2 TempOverlapX=%d\n", XC);
			printf("XY = {%d, %d}\n", OverlapX[0], OverlapY[1]);
		}


		//make sure each overlap is appropriate....
		if (YC > 16 || YC < 0) {
			printf("We've got a problem sir!\n");
			wait = true;
		}
		if (XC > 16 || XC < 0) {
			printf("We've got a problem sir!\n");
			wait = true;
		}


	}



	void Hopper(XYArr* Sorter) {
		printf("The last two overlaps were not from the same item. We'll figure out which is greater\n"); //if neither is greater, lets go with x.

		//get the x overlap
		printf("Sprite was moving Left\n");
		int x = Sorter->SpriteXCollision.size();
		int y = Sorter->SpriteYCollision.size();
		int XC;
		XC = Sorter->Victim->xPos + TILE_WIDTH - Sorter->SpriteXCollision[x - 1]->xPos; //object 4={64, 0}, obj5 ={79, 0}. 64+16-79=1, so 79+1 is where obj 5 would be without overlap. 
		printf("Attempt 1: XC = %d + %d - %d = %d\n", Sorter->Victim->xPos, TILE_WIDTH, Sorter->SpriteXCollision[x - 1]->xPos, XC);
		XC = Sorter->SpriteXCollision[x - 1]->xPos + TILE_WIDTH - Sorter->Victim->xPos; //object 4={64, 0}, obj5 ={79, 0}. 64+16-79=1, so 79+1 is where obj 5 would be without overlap.
		printf("Attempt 2: XC = %d\n", XC);
		if (XC > 16 || XC < 0) {
			XC = Sorter->Victim->xPos + TILE_WIDTH - Sorter->SpriteXCollision[x - 1]->xPos; //object 4={64, 0}, obj5 ={79, 0}. 64+16-79=1, so 79+1 is where obj 5 would be without overlap. 
			printf("Attempt 3: XC = %d\n", XC);
		}
		if (XC == 16) {
			XC = 0;
		}
		int YC;
		YC = Sorter->Victim->yPos + TILE_WIDTH - Sorter->SpriteYCollision[y - 1]->yPos; //object 4={64, 0}, obj5 ={79, 0}. 64+16-79=1, so 79+1 is where obj 5 would be without overlap. 
		printf("Attempt 1: YC = %d + %d - %d = %d\n", Sorter->Victim->yPos, TILE_HEIGHT, Sorter->SpriteYCollision[y - 1]->yPos, YC);
		YC = Sorter->SpriteYCollision[y - 1]->yPos + TILE_HEIGHT - Sorter->Victim->yPos; //object 4={64, 0}, obj5 ={79, 0}. 64+16-79=1, so 79+1 is where obj 5 would be without overlap.
		printf("Attempt 2: YC = %d\n", YC);
		if (YC > 16 || YC < 0) {
			YC = Sorter->Victim->yPos + TILE_HEIGHT - Sorter->SpriteYCollision[y - 1]->yPos; //object 4={64, 0}, obj5 ={79, 0}. 64+16-79=1, so 79+1 is where obj 5 would be without overlap. 
			printf("Attempt 3: YC = %d\n", YC);
		}
		if (YC == 16) {
			YC = 0;
		}

		//if th eobject can't be found in the other list, theres an error. All objects in either list should also be found in the other.

		if (XC < YC) {
			//We'll look for YC's object, and emplace it on the back. 
			//we can't use swap, instead we'll pop it's found loaction, and emplace it on the back. this won't screw up the order of the other elements that way, in the event it matters. 
			printf("YC had larger overlap\n");
			//Search through XC for the object of YC
			for (int i = 0; i < x; i++) {
				if (Sorter->SpriteXCollision[i] == Sorter->SpriteYCollision.back()) {
					Sorter->SpriteXCollision.erase(Sorter->SpriteXCollision.begin() + i); //IF WE NEVER HAVE TO KNOW THE REST OF THESE COLLISIONS, DO NOT BOTHER ERASING. IT IS TIMELY FOR LARGE VECTORS
					Sorter->SpriteXCollision.push_back(Sorter->SpriteYCollision.back());
					break;
				}
			}
		}

		else {
			//We'll look for XC's object, and emplace it on the back. 
			//we can't use swap, instead we'll pop it's found loaction, and emplace it on the back. this won't screw up the order of the other elements that way, in the event it matters. 
			printf("XC had larger overlap\n");
			//Search through YC for the object of XC
			for (int i = 0; i < y; i++) {
				if (Sorter->SpriteYCollision[i] == Sorter->SpriteXCollision.back()) {
					Sorter->SpriteYCollision.erase(Sorter->SpriteYCollision.begin() + i); //IF WE NEVER HAVE TO KNOW THE REST OF THESE COLLISIONS, DO NOT BOTHER ERASING. IT IS TIMELY FOR LARGE VECTORS
					Sorter->SpriteYCollision.push_back(Sorter->SpriteXCollision.back());
					break;
				}
			}
		}

	}

	void CheckFutureSpritePosition2(Sprite* ObjectSprite, XYArr* TempStackable) {
		bool Debug = false;
		if (Debug) {
			printf("Object Creation Order == %d\n", ObjectSprite->OrderCreation);
		}
		if (ObjectSprite->OrderCreation == 1 || ObjectSprite->OrderCreation == 0) {
			Debug = true;
		}
		else {
			Debug = false;
		}
		Debug = false;

		int xD = 0;
		int yD = 0;
		if (true || Debug) {
			//Y=-1,0,1, [1, 2, 3] X=-1, 0, 1, [4, 8, 12] 
			xD = 8;
			yD = 2;
			if (ObjectSprite->xVec > 0) {
				xD = 12;
			}
			else if (ObjectSprite->xVec < 0) {
				xD = 4;
			}
			if (ObjectSprite->yVec > 0) {
				yD = 3;
			}
			else if (ObjectSprite->yVec < 0) {
				yD = 1;
			}
			printf("Original direction for Object%d = %d\n", ObjectSprite->OrderCreation + 1, xD + yD);
		}

		// printf("CheckFutureSpritePosition\n");
		int x1, x2, y1, y2;

		int TempX2, TempY2;

		x1 = ObjectSprite->xPos;
		x2 = ObjectSprite->xPos + TILE_WIDTH;
		y1 = ObjectSprite->yPos;
		y2 = ObjectSprite->yPos + TILE_HEIGHT;

		TempX2 = x2 % TILE_WIDTH;
		TempY2 = y1 % TILE_HEIGHT;
		int TempY2Math = y2 - TILE_HEIGHT * (y2 / TILE_HEIGHT); //A = C - B * (C/B)
		// printf("TempY2Math = y2 -16*(y2/16) = %d, from %d, %d\n", TempY2Math, TILE_HEIGHT, y2);
		int TempX2Math = x2 - TILE_WIDTH * (x2 / TILE_WIDTH);
		y1 = y1 / TILE_HEIGHT;
		y2 = y2 / TILE_HEIGHT;
		x1 = x1 / TILE_WIDTH;
		x2 = x2 / TILE_WIDTH;
		//NOTE - gaurds from map/matrix overflow - NEW 8/19 - since I edited it, becaue the moves seem to guard against going out of bounds in the first place, I made it so that this guards the directions, so it's easier to process. Odd behavior is that once the original is adjusted, it stays adjused until the key is pressed again. Don't think I like that. It's stays that way because the =, but I can't just get rid of it. Maybe I'll make a case when it's on vs when it's off the very edge, so that it's only triggered once per button press or something...
		if (ObjectSprite->yPos >= (LEVEL_WIDTH - 1) * TILE_HEIGHT) {
			y1 = LEVEL_HEIGHT - 1;
			y2 = y1;
			ObjectSprite->yVec = 0; //NEW - after we tried to jostle, I noted that there is a special bug that happens when your going diagonal into a wall. Because a null is passed for both, it doesn't try to jostle.
			if (Debug || PAUSECOLLISIONJOSTLE[4] == 0) {
				printf("%d", TOTALFRAMECOUNT);
				printf(" Sprite%d can no longer go further down\n", ObjectSprite->OrderCreation + 1);
				PAUSECOLLISIONJOSTLE[4] = 1;
				SDL_Delay(10000);
			}
		} //NOTE - this fix cannot be moved lower, because we need to trigger the jostle initially by setting at least one of the diagonals 'edges' to be not a nullptr, OR just let it slide down the sides of the edge of the map.
		if (ObjectSprite->yPos <= 0) {
			y1 = 0;
			y2 = y1;
			ObjectSprite->yVec = 0;
			if (Debug || PAUSECOLLISIONJOSTLE[5] == 0) {
				printf("%d", TOTALFRAMECOUNT);
				printf(" Sprite%dcan no longer go further up\n", ObjectSprite->OrderCreation + 1);
				PAUSECOLLISIONJOSTLE[5] = 1;
				SDL_Delay(10000);
			}
		}
		if (ObjectSprite->xPos >= (LEVEL_WIDTH - 1) * TILE_WIDTH) {
			x1 = LEVEL_WIDTH - 1;
			x2 = x1;
			ObjectSprite->xVec = 0;
			if (Debug || PAUSECOLLISIONJOSTLE[6] == 0) {
				printf("%d", TOTALFRAMECOUNT);
				printf(" Sprite%d can no longer go further right\n", ObjectSprite->OrderCreation + 1);
				PAUSECOLLISIONJOSTLE[6] = 1;
				SDL_Delay(10000);
			}
		}
		if (ObjectSprite->xPos <= 0) { //NEW - 8/19/21 This is done because the move's already track the bounds of hte level, so here I want to know whether the mod is higher than it should be or the actual position is less (because the mod is not solid enough)
			x1 = 0;
			x2 = x1;
			ObjectSprite->xVec = 0;
			if (Debug || PAUSECOLLISIONJOSTLE[7] == 0) {
				printf("%d", TOTALFRAMECOUNT);
				printf(" Sprite%d can no longer go further left\n", ObjectSprite->OrderCreation + 1);
				PAUSECOLLISIONJOSTLE[7] = 1;
				SDL_Delay(10000);
			}
		}

		//So we don't check further than we want to, and when we don't need to. In these cases, it doens't matter now if we use x1, or x2. For consistency, we use whatever appears the most as appropriate. 
		if (TempX2Math == 0) {
			x2 = x1;
		}
		if (TempY2Math == 0) {
			y2 = y1;
		}



		if (true || Debug) {
			//Y=-1,0,1, [1, 2, 3] X=-1, 0, 1, [4, 8, 12] 
			xD = 8;
			yD = 2;
			if (ObjectSprite->xVec > 0) {
				xD = 12;
			}
			else if (ObjectSprite->xVec < 0) {
				xD = 4;
			}
			if (ObjectSprite->yVec > 0) {
				yD = 3;
			}
			else if (ObjectSprite->yVec < 0) {
				yD = 1;
			}
			printf("New direction for Object%d = %d\n", ObjectSprite->OrderCreation + 1, xD + yD);
		}


		//Vector that holds the 'area' of overlap - this is to be compared with, and then swapped if one with larger area shows up
		//if tie, look at order creation
		std::vector<int> SpriteX = {};
		std::vector<int> SpriteY = {};
		//vector that holds the pointer itself. to be returned as a stack
		std::vector<Sprite*> SpriteOverlapX = {};
		std::vector<Sprite*> SpriteOverlapY = {};
		//default is still
		int xAxis = 0;
		int yAxis = 0;
		if (true) {
			if (Debug) {
				printf("3.0\n"); //initalized all variables
			}
			//Get direction (diagnonal, or 
			if (ObjectSprite->xVec > 0) {
				//going right
				xAxis = 1;
			}
			else if (ObjectSprite->xVec < 0) {
				//going left
				xAxis = -1;
			}
			if (ObjectSprite->yVec > 0) {
				//going down
				yAxis = 1;
			}
			else if (ObjectSprite->yVec < 0) {
				//going up
				yAxis = -1;
			}
		} //get the Y and X direction, for Measure
		if (Debug) {
			printf("3.1\n"); //General Direction found
		}
		int Measure; //Y=-1,0,1, [1, 2, 3] X=-1, 0, 1, [4, 8, 12] 
		if (true) {
			//can be improved by nesting. for now ignore.
			if (yAxis < 0 && xAxis < 0) { //diag UL
				Measure = 1 + 4; //5
			}
			else if (yAxis > 0 && xAxis > 0) { //diag LR
				Measure = 3 + 12; //15
			}
			else if (yAxis < 0 && xAxis > 0) { //diag UR
				Measure = 1 + 12;//13
			}
			else if (yAxis > 0 && xAxis < 0) { //diag LL
				Measure = 3 + 4; //7
			}
			else if (xAxis > 0) { //Right
				Measure = 12 + 2;//14
			}
			else if (xAxis < 0) { //Left
				Measure = 4 + 2; //6
			}
			else if (yAxis > 0) { //Down
				Measure = 3 + 8; //11
			}
			else if (yAxis < 0) { //Up
				Measure = 1 + 8; //9
			}
			else { //still
				Measure = 2 + 8; //10
			}
		}//Find Measure's value
		int TempXOverlap;
		int TempYOverlap;
		if (Debug) {
			printf("3.2\n"); //Measure found
		}
		//figure out what your hitting, and how far overlapped.
		if (true) {
			//2) NOTE IF THERE IS A BUG, WHERE ITS COLLIDIG OT ITS RIGHT OR BELOW EXTRA, MAKE A CHECK THAT IF x2%16=0 IT IS NOW EQUAL TO x1, THUS IT DOESNT MATTER IF WE DO x2 OR x1 IN THE X CHECK, so long as they are the same, TAHT IS ALL. - a bug from previous, but the naming convention should be based on hte edge that is 'leading'

			//NOTE SPECIAL CASE is when x1,x2, or y1,y2 are % W or H =0, this means we check the position of x1,y1, otherwise error is thrown. <-also mod doesn't work
			// instead of % to check, use C = A - B*(A/B) <- used in TempMath
			//GOING TO

			//bug caused if you don't check that it's overlapepd at least one pixel.
			int xOverlapped = 0; //used exclusively to test for true collision dimension
			int yOverlapped = 0; //used exclusively to test for true collision dimension.







			//diagonals
			if (Measure == 5) {//UL
				//edges are [x1][y1], [y2][x1], [x2][y1], each of these three are 'points' that form 2 edges.
				//Depending on how perfectly inligned with the grid you are, you can skip checking some edges/points.
				if (TempX2Math == 0 && TempY2Math == 0) { //you are perfectly in line with the gird
					if (Debug) {
						printf("a\n");
					}
					for (int i = 0; i < LM[y1][x1].size(); i++) {
						//2) now check for overlap, diagonal so check for x and y. These formulas change every time. For simplcity, attempt to make sure that if there is a gap between the two object, 
						if (LM[y1][x1][i]->xPos > ObjectSprite->xPos) { //NEW (CHANGED)
							TempXOverlap = ObjectSprite->xPos + TILE_WIDTH - LM[y1][x1][i]->xPos;
						}
						else {
							TempXOverlap = LM[y1][x1][i]->xPos + TILE_WIDTH - ObjectSprite->xPos;
						}
						if (LM[y1][x1][i]->yPos < ObjectSprite->yPos) {
							TempYOverlap = LM[y1][x1][i]->yPos + TILE_HEIGHT - ObjectSprite->yPos;
						}
						else {
							TempYOverlap = ObjectSprite->yPos + TILE_HEIGHT - LM[y1][x1][i]->yPos;
						}
						//2) if you didn't collide, even if your in the same grid space, then the equation returned negative, or 0 if just barely touching. (butnot collding)
						if ((TempYOverlap < 17 && TempYOverlap > 0) && TempXOverlap < 17 && TempXOverlap > 0) {
							SpriteOverlapX.push_back(LM[y1][x1][i]);
							SpriteX.push_back(TempXOverlap);
							SpriteOverlapY.push_back(LM[y1][x1][i]);
							SpriteY.push_back(TempYOverlap);
							TempXOverlap = 0;
							TempYOverlap = 0;
						}
					}
				}
				else {
					if (TempX2Math == 0) { //you are perfectly in line with an x axis'
						//2) Don't worry about pushing back more than one pointer to the same object. At the end of hte loop we will ensure that only one ptr remains, along with it sorted by overlap.
						if (Debug) {
							printf("b\n");
						}
						for (int i = 0; i < LM[y1][x1].size(); i++) {//UL

							if (LM[y1][x1][i]->xPos > ObjectSprite->xPos) { //NEW (CHANGED)
								TempXOverlap = ObjectSprite->xPos + TILE_WIDTH - LM[y1][x1][i]->xPos;
							}
							else {
								TempXOverlap = LM[y1][x1][i]->xPos + TILE_WIDTH - ObjectSprite->xPos;
							}
							if (LM[y1][x1][i]->yPos < ObjectSprite->yPos) {
								TempYOverlap = LM[y1][x1][i]->yPos + TILE_HEIGHT - ObjectSprite->yPos;
							}
							else {
								TempYOverlap = ObjectSprite->yPos + TILE_HEIGHT - LM[y1][x1][i]->yPos;
							}
							if ((TempYOverlap < 17 && TempYOverlap > 0) && TempXOverlap < 17 && TempXOverlap > 0) {
								SpriteOverlapX.push_back(LM[y1][x1][i]);
								SpriteX.push_back(TempXOverlap); //2) The overlap value will be the same, even if we end up pushing it twice.
								SpriteOverlapY.push_back(LM[y1][x1][i]);
								SpriteY.push_back(TempYOverlap);
								TempXOverlap = 0;
								TempYOverlap = 0;
							}
						}
						if (Debug) {
							printf("c\n");
						}
						for (int i = 0; i < LM[y2][x1].size(); i++) {//LL

							if (LM[y2][x1][i]->xPos > ObjectSprite->xPos) { //NEW (CHANGED)
								TempXOverlap = ObjectSprite->xPos + TILE_WIDTH - LM[y2][x1][i]->xPos;
							}
							else {
								TempXOverlap = LM[y2][x1][i]->xPos + TILE_WIDTH - ObjectSprite->xPos;
							}
							if (LM[y2][x1][i]->yPos > ObjectSprite->yPos) {
								TempYOverlap = ObjectSprite->yPos + TILE_HEIGHT - LM[y2][x1][i]->yPos;
							}
							else {
								TempYOverlap = LM[y2][x1][i]->yPos + TILE_HEIGHT - ObjectSprite->yPos;
							}

							if ((TempYOverlap < 17 && TempYOverlap > 0) && TempXOverlap < 17 && TempXOverlap > 0) {
								SpriteOverlapX.push_back(LM[y2][x1][i]);
								SpriteX.push_back(TempXOverlap);
								SpriteOverlapY.push_back(LM[y2][x1][i]);
								SpriteY.push_back(TempYOverlap);
								TempXOverlap = 0;
								TempYOverlap = 0;
							}
						}
					}
					else if (TempY2Math == 0) { //you are perfectly in line with an y axis'
						if (Debug) {
							printf("d\n");
						}
						for (int i = 0; i < LM[y1][x1].size(); i++) { //UL
							if (LM[y1][x1][i]->xPos > ObjectSprite->xPos) { //NEW (CHANGED)
								TempXOverlap = ObjectSprite->xPos + TILE_WIDTH - LM[y1][x1][i]->xPos;
							}
							else {
								TempXOverlap = LM[y1][x1][i]->xPos + TILE_WIDTH - ObjectSprite->xPos;
							}
							if (LM[y1][x1][i]->yPos < ObjectSprite->yPos) {
								TempYOverlap = LM[y1][x1][i]->yPos + TILE_HEIGHT - ObjectSprite->yPos;
							}
							else {
								TempYOverlap = ObjectSprite->yPos + TILE_HEIGHT - LM[y1][x1][i]->yPos;
							}
							if ((TempYOverlap < 17 && TempYOverlap > 0) && TempXOverlap < 17 && TempXOverlap > 0) {
								SpriteOverlapX.push_back(LM[y1][x1][i]);
								SpriteX.push_back(TempXOverlap);
								SpriteOverlapY.push_back(LM[y1][x1][i]);
								SpriteY.push_back(TempYOverlap);
								TempXOverlap = 0;
								TempYOverlap = 0;
							}
						}
						if (Debug) {
							printf("e\n");
						}
						for (int i = 0; i < LM[y1][x2].size(); i++) { //UR

							if (LM[y1][x2][i]->xPos > ObjectSprite->xPos) {//NEW (CHANGED)
								TempXOverlap = ObjectSprite->xPos + TILE_WIDTH - LM[y1][x2][i]->xPos;

							}
							else {
								TempXOverlap = LM[y1][x2][i]->xPos + TILE_WIDTH - ObjectSprite->xPos;

							}
							if (LM[y1][x2][i]->yPos < ObjectSprite->yPos) {
								TempYOverlap = LM[y1][x2][i]->yPos + TILE_HEIGHT - ObjectSprite->yPos;
							}
							else {
								TempYOverlap = ObjectSprite->yPos + TILE_HEIGHT - LM[y1][x2][i]->yPos;
							}
							if (Debug) {
								printf("%d %d Overlap X and Y\n", TempXOverlap, TempYOverlap);
							}
							if ((TempYOverlap < 17 && TempYOverlap > 0) && TempXOverlap < 17 && TempXOverlap > 0) {
								SpriteOverlapX.push_back(LM[y2][x2][i]);
								SpriteX.push_back(TempXOverlap);
								SpriteOverlapY.push_back(LM[y2][x2][i]);
								SpriteY.push_back(TempYOverlap);
								TempXOverlap = 0;
								TempYOverlap = 0;
							}



						}
					}
					//2) these are always the points we're interested in.
					else { //you are not perfectly aligned with anything, every 'point' matters.
						if (Debug) {
							printf("f\n");
						}
						for (int i = 0; i < LM[y1][x1].size(); i++) { //UL

							if (LM[y1][x1][i]->xPos > ObjectSprite->xPos) { //NEW (CHANGED)
								TempXOverlap = ObjectSprite->xPos + TILE_WIDTH - LM[y1][x1][i]->xPos;
							}
							else {
								TempXOverlap = LM[y1][x1][i]->xPos + TILE_WIDTH - ObjectSprite->xPos;
							}
							if (LM[y1][x1][i]->yPos < ObjectSprite->yPos) {
								TempYOverlap = LM[y1][x1][i]->yPos + TILE_HEIGHT - ObjectSprite->yPos;
							}
							else {
								TempYOverlap = ObjectSprite->yPos + TILE_HEIGHT - LM[y1][x1][i]->yPos;
							}
							if ((TempYOverlap < 17 && TempYOverlap > 0) && TempXOverlap < 17 && TempXOverlap > 0) {
								SpriteOverlapX.push_back(LM[y1][x1][i]);
								SpriteX.push_back(TempXOverlap);
								SpriteOverlapY.push_back(LM[y1][x1][i]);
								SpriteY.push_back(TempYOverlap);
								TempXOverlap = 0;
								TempYOverlap = 0;
							}
						}
						if (Debug) {
							printf("g\n");
						}
						for (int i = 0; i < LM[y1][x2].size(); i++) { //UR

							if (LM[y1][x2][i]->xPos > ObjectSprite->xPos) {//NEW (CHANGED)
								TempXOverlap = ObjectSprite->xPos + TILE_WIDTH - LM[y1][x2][i]->xPos;

							}
							else {
								TempXOverlap = LM[y1][x2][i]->xPos + TILE_WIDTH - ObjectSprite->xPos;

							}
							if (LM[y1][x2][i]->yPos < ObjectSprite->yPos) {
								TempYOverlap = LM[y1][x2][i]->yPos + TILE_HEIGHT - ObjectSprite->yPos;
							}
							else {
								TempYOverlap = ObjectSprite->yPos + TILE_HEIGHT - LM[y1][x2][i]->yPos;
							}
							if ((TempYOverlap < 17 && TempYOverlap > 0) && TempXOverlap < 17 && TempXOverlap > 0) {
								SpriteOverlapX.push_back(LM[y1][x2][i]);
								SpriteX.push_back(TempXOverlap);
								SpriteOverlapY.push_back(LM[y1][x2][i]);
								SpriteY.push_back(TempYOverlap);
								TempXOverlap = 0;
								TempYOverlap = 0;
							}
						}
						if (Debug) {
							printf("h\n");
						}
						for (int i = 0; i < LM[y2][x1].size(); i++) { //LL

							if (LM[y2][x1][i]->xPos > ObjectSprite->xPos) { //NEW (CHANGED)
								TempXOverlap = ObjectSprite->xPos + TILE_WIDTH - LM[y2][x1][i]->xPos;
							}
							else {
								TempXOverlap = LM[y2][x1][i]->xPos + TILE_WIDTH - ObjectSprite->xPos;
							}
							if (LM[y2][x1][i]->yPos > ObjectSprite->yPos) {
								TempYOverlap = ObjectSprite->yPos + TILE_HEIGHT - LM[y2][x1][i]->yPos;
							}
							else {
								TempYOverlap = LM[y2][x1][i]->yPos + TILE_HEIGHT - ObjectSprite->yPos;
							}

							if ((TempYOverlap < 17 && TempYOverlap > 0) && TempXOverlap < 17 && TempXOverlap > 0) {
								SpriteOverlapX.push_back(LM[y2][x1][i]);
								SpriteX.push_back(TempXOverlap);
								SpriteOverlapY.push_back(LM[y2][x1][i]);
								SpriteY.push_back(TempYOverlap);
								TempXOverlap = 0;
								TempYOverlap = 0;
							}
						}
					}
				}

			}
			else if (Measure == 13) {//UR
				//edges are [x1][y1], [x2][y1], [x2][y2]

				//Depending on how perfectly inligned with the grid you are, you can skip checking some edges/points.

				if (TempX2Math == 0 && TempY2Math == 0) { //you are perfectly in line with the gird
					if (Debug) {
						printf("i\n");
					}
					for (int i = 0; i < LM[y1][x2].size(); i++) { // first
						if (LM[y1][x2][i]->xPos > ObjectSprite->xPos) {//NEW (CHANGED)
							TempXOverlap = ObjectSprite->xPos + TILE_WIDTH - LM[y1][x2][i]->xPos;

						}
						else {
							TempXOverlap = LM[y1][x2][i]->xPos + TILE_WIDTH - ObjectSprite->xPos;

						}
						if (LM[y1][x2][i]->yPos < ObjectSprite->yPos) {
							TempYOverlap = LM[y1][x2][i]->yPos + TILE_HEIGHT - ObjectSprite->yPos;
						}
						else {
							TempYOverlap = ObjectSprite->yPos + TILE_HEIGHT - LM[y1][x2][i]->yPos;
						}
						if ((TempYOverlap < 17 && TempYOverlap > 0) && TempXOverlap < 17 && TempXOverlap > 0) {
							SpriteOverlapX.push_back(LM[y1][x2][i]);
							SpriteX.push_back(TempXOverlap);
							SpriteOverlapY.push_back(LM[y1][x2][i]);
							SpriteY.push_back(TempYOverlap);
							TempXOverlap = 0;
							TempYOverlap = 0;
						}
					}
				}
				else {
					if (TempX2Math == 0) { //you are perfectly in line with an x axis'
						if (Debug) {
							printf("j\n");
						}
						for (int i = 0; i < LM[y1][x2].size(); i++) { // UR

							if (LM[y1][x2][i]->xPos > ObjectSprite->xPos) {//NEW (CHANGED)
								TempXOverlap = ObjectSprite->xPos + TILE_WIDTH - LM[y1][x2][i]->xPos;

							}
							else {
								TempXOverlap = LM[y1][x2][i]->xPos + TILE_WIDTH - ObjectSprite->xPos;

							}
							if (LM[y1][x2][i]->yPos < ObjectSprite->yPos) {
								TempYOverlap = LM[y1][x2][i]->yPos + TILE_HEIGHT - ObjectSprite->yPos;
							}
							else {
								TempYOverlap = ObjectSprite->yPos + TILE_HEIGHT - LM[y1][x2][i]->yPos;
							}
							if ((TempYOverlap < 17 && TempYOverlap > 0) && TempXOverlap < 17 && TempXOverlap > 0) {
								SpriteOverlapX.push_back(LM[y1][x2][i]);
								SpriteX.push_back(TempXOverlap);
								SpriteOverlapY.push_back(LM[y1][x2][i]);
								SpriteY.push_back(TempYOverlap);
								TempXOverlap = 0;
								TempYOverlap = 0;
							}
						}
						if (Debug) {
							printf("k\n");
						}
						for (int i = 0; i < LM[y2][x2].size(); i++) { // LR

							if (LM[y2][x2][i]->xPos > ObjectSprite->xPos) {//NEW (CHANGED)
								TempXOverlap = ObjectSprite->xPos + TILE_WIDTH - LM[y2][x2][i]->xPos;

							}
							else {
								TempXOverlap = LM[y2][x2][i]->xPos + TILE_WIDTH - ObjectSprite->xPos;
							}
							if (LM[y2][x2][i]->yPos > ObjectSprite->yPos) {
								TempYOverlap = ObjectSprite->yPos + TILE_HEIGHT - LM[y2][x2][i]->yPos;
							}
							else {
								TempYOverlap = LM[y2][x2][i]->yPos + TILE_HEIGHT - ObjectSprite->yPos;
							}

							if ((TempYOverlap < 17 && TempYOverlap > 0) && TempXOverlap < 17 && TempXOverlap > 0) {
								SpriteOverlapX.push_back(LM[y2][x2][i]);
								SpriteX.push_back(TempXOverlap);
								SpriteOverlapY.push_back(LM[y2][x2][i]);
								SpriteY.push_back(TempYOverlap);
								TempXOverlap = 0;
								TempYOverlap = 0;
							}
						}
					}
					else if (TempY2Math == 0) { //you are perfectly in line with an y axis'
						if (Debug) {
							printf("l\n");
						}
						for (int i = 0; i < LM[y1][x1].size(); i++) { // UL

							if (LM[y1][x1][i]->xPos > ObjectSprite->xPos) { //NEW (CHANGED)
								TempXOverlap = ObjectSprite->xPos + TILE_WIDTH - LM[y1][x1][i]->xPos;
							}
							else {
								TempXOverlap = LM[y1][x1][i]->xPos + TILE_WIDTH - ObjectSprite->xPos;
							}
							if (LM[y1][x1][i]->yPos < ObjectSprite->yPos) {
								TempYOverlap = LM[y1][x1][i]->yPos + TILE_HEIGHT - ObjectSprite->yPos;
							}
							else {
								TempYOverlap = ObjectSprite->yPos + TILE_HEIGHT - LM[y1][x1][i]->yPos;
							}
							if ((TempYOverlap < 17 && TempYOverlap > 0) && TempXOverlap < 17 && TempXOverlap > 0) {
								SpriteOverlapX.push_back(LM[y1][x1][i]);
								SpriteX.push_back(TempXOverlap);
								SpriteOverlapY.push_back(LM[y1][x1][i]);
								SpriteY.push_back(TempYOverlap);
								TempXOverlap = 0;
								TempYOverlap = 0;
							}
						}
						if (Debug) {
							printf("m\n");
						}
						for (int i = 0; i < LM[y1][x2].size(); i++) { // UR

							if (LM[y1][x2][i]->xPos > ObjectSprite->xPos) {//NEW (CHANGED)
								TempXOverlap = ObjectSprite->xPos + TILE_WIDTH - LM[y1][x2][i]->xPos;

							}
							else {
								TempXOverlap = LM[y1][x2][i]->xPos + TILE_WIDTH - ObjectSprite->xPos;

							}
							if (LM[y1][x2][i]->yPos < ObjectSprite->yPos) {
								TempYOverlap = LM[y1][x2][i]->yPos + TILE_HEIGHT - ObjectSprite->yPos;
							}
							else {
								TempYOverlap = ObjectSprite->yPos + TILE_HEIGHT - LM[y1][x2][i]->yPos;
							}
							if ((TempYOverlap < 17 && TempYOverlap > 0) && TempXOverlap < 17 && TempXOverlap > 0) {
								SpriteOverlapX.push_back(LM[y1][x2][i]);
								SpriteX.push_back(TempXOverlap);
								SpriteOverlapY.push_back(LM[y1][x2][i]);
								SpriteY.push_back(TempYOverlap);
								TempXOverlap = 0;
								TempYOverlap = 0;
							}
						}

					}
					else { //you are not perfectly aligned with anything, every 'point' matters.
						if (Debug) {
							printf("n\n");
						}
						for (int i = 0; i < LM[y1][x1].size(); i++) { // UL

							if (LM[y1][x1][i]->xPos > ObjectSprite->xPos) { //NEW (CHANGED)
								TempXOverlap = ObjectSprite->xPos + TILE_WIDTH - LM[y1][x1][i]->xPos;
							}
							else {
								TempXOverlap = LM[y1][x1][i]->xPos + TILE_WIDTH - ObjectSprite->xPos;
							}
							if (LM[y1][x1][i]->yPos < ObjectSprite->yPos) {
								TempYOverlap = LM[y1][x1][i]->yPos + TILE_HEIGHT - ObjectSprite->yPos;
							}
							else {
								TempYOverlap = ObjectSprite->yPos + TILE_HEIGHT - LM[y1][x1][i]->yPos;
							}
							if ((TempYOverlap < 17 && TempYOverlap > 0) && TempXOverlap < 17 && TempXOverlap > 0) {
								SpriteOverlapX.push_back(LM[y1][x1][i]);
								SpriteX.push_back(TempXOverlap);
								SpriteOverlapY.push_back(LM[y1][x1][i]);
								SpriteY.push_back(TempYOverlap);
								TempXOverlap = 0;
								TempYOverlap = 0;
							}
						}
						if (Debug) {
							printf("o\n");
						}
						for (int i = 0; i < LM[y2][x2].size(); i++) { // LR

							if (LM[y2][x2][i]->xPos > ObjectSprite->xPos) {//NEW (CHANGED)
								TempXOverlap = ObjectSprite->xPos + TILE_WIDTH - LM[y2][x2][i]->xPos;

							}
							else {
								TempXOverlap = LM[y2][x2][i]->xPos + TILE_WIDTH - ObjectSprite->xPos;
							}
							if (LM[y2][x2][i]->yPos > ObjectSprite->yPos) {
								TempYOverlap = ObjectSprite->yPos + TILE_HEIGHT - LM[y2][x2][i]->yPos;
							}
							else {
								TempYOverlap = LM[y2][x2][i]->yPos + TILE_HEIGHT - ObjectSprite->yPos;
							}
							if ((TempYOverlap < 17 && TempYOverlap > 0) && TempXOverlap < 17 && TempXOverlap > 0) {
								SpriteOverlapX.push_back(LM[y2][x2][i]);
								SpriteX.push_back(TempXOverlap);
								SpriteOverlapY.push_back(LM[y2][x2][i]);
								SpriteY.push_back(TempYOverlap);
								TempXOverlap = 0;
								TempYOverlap = 0;
							}
						}
						if (Debug) {
							printf("p\n");
						}
						for (int i = 0; i < LM[y1][x2].size(); i++) { // UR

							if (LM[y1][x2][i]->xPos > ObjectSprite->xPos) {//NEW (CHANGED)
								TempXOverlap = ObjectSprite->xPos + TILE_WIDTH - LM[y1][x2][i]->xPos;

							}
							else {
								TempXOverlap = LM[y1][x2][i]->xPos + TILE_WIDTH - ObjectSprite->xPos;

							}
							if (LM[y1][x2][i]->yPos < ObjectSprite->yPos) {
								TempYOverlap = LM[y1][x2][i]->yPos + TILE_HEIGHT - ObjectSprite->yPos;
							}
							else {
								TempYOverlap = ObjectSprite->yPos + TILE_HEIGHT - LM[y1][x2][i]->yPos;
							}
							if ((TempYOverlap < 17 && TempYOverlap > 0) && TempXOverlap < 17 && TempXOverlap > 0) {
								SpriteOverlapX.push_back(LM[y1][x2][i]);
								SpriteX.push_back(TempXOverlap);
								SpriteOverlapY.push_back(LM[y1][x2][i]);
								SpriteY.push_back(TempYOverlap);
								TempXOverlap = 0;
								TempYOverlap = 0;
							}

						}

					}
				}

			}
			else if (Measure == 7) {//DL
				//edges are [x1][y1], [x1][y2], [x2][y2]

				//Depending on how perfectly inligned with the grid you are, you can skip checking some edges/points.

				if (TempX2Math == 0 && TempY2Math == 0) { //you are perfectly in line with the gird
					if (Debug) {
						printf("q\n");
					}
					for (int i = 0; i < LM[y2][x1].size(); i++) { // first

						if (LM[y2][x1][i]->xPos > ObjectSprite->xPos) { //NEW (CHANGED)
							TempXOverlap = ObjectSprite->xPos + TILE_WIDTH - LM[y2][x1][i]->xPos;
						}
						else {
							TempXOverlap = LM[y2][x1][i]->xPos + TILE_WIDTH - ObjectSprite->xPos;
						}
						if (LM[y2][x1][i]->yPos > ObjectSprite->yPos) {
							TempYOverlap = ObjectSprite->yPos + TILE_HEIGHT - LM[y2][x1][i]->yPos;
						}
						else {
							TempYOverlap = LM[y2][x1][i]->yPos + TILE_HEIGHT - ObjectSprite->yPos;
						}

						if ((TempYOverlap < 17 && TempYOverlap > 0) && TempXOverlap < 17 && TempXOverlap > 0) {
							SpriteOverlapX.push_back(LM[y2][x1][i]);
							SpriteX.push_back(TempXOverlap);
							SpriteOverlapY.push_back(LM[y2][x1][i]);
							SpriteY.push_back(TempYOverlap);
							TempXOverlap = 0;
							TempYOverlap = 0;
						}
					}
				}
				else {
					if (TempX2Math == 0) { //you are perfectly in line with an x axis'
						if (Debug) {
							printf("r\n");
						}
						for (int i = 0; i < LM[y1][x1].size(); i++) { // UL

							if (LM[y1][x1][i]->xPos > ObjectSprite->xPos) { //NEW (CHANGED)
								TempXOverlap = ObjectSprite->xPos + TILE_WIDTH - LM[y1][x1][i]->xPos;
							}
							else {
								TempXOverlap = LM[y1][x1][i]->xPos + TILE_WIDTH - ObjectSprite->xPos;
							}
							if (LM[y1][x1][i]->yPos < ObjectSprite->yPos) {
								TempYOverlap = LM[y1][x1][i]->yPos + TILE_HEIGHT - ObjectSprite->yPos;
							}
							else {
								TempYOverlap = ObjectSprite->yPos + TILE_HEIGHT - LM[y1][x1][i]->yPos;
							}
							if ((TempYOverlap < 17 && TempYOverlap > 0) && TempXOverlap < 17 && TempXOverlap > 0) {
								SpriteOverlapX.push_back(LM[y1][x1][i]);
								SpriteX.push_back(TempXOverlap);
								SpriteOverlapY.push_back(LM[y1][x1][i]);
								SpriteY.push_back(TempYOverlap);
								TempXOverlap = 0;
								TempYOverlap = 0;
							}
						}
						if (Debug) {
							printf("s\n");
						}
						for (int i = 0; i < LM[y2][x1].size(); i++) { // LL

							if (LM[y2][x1][i]->xPos > ObjectSprite->xPos) { //NEW (CHANGED)
								TempXOverlap = ObjectSprite->xPos + TILE_WIDTH - LM[y2][x1][i]->xPos;
							}
							else {
								TempXOverlap = LM[y2][x1][i]->xPos + TILE_WIDTH - ObjectSprite->xPos;
							}
							if (LM[y2][x1][i]->yPos > ObjectSprite->yPos) {
								TempYOverlap = ObjectSprite->yPos + TILE_HEIGHT - LM[y2][x1][i]->yPos;
							}
							else {
								TempYOverlap = LM[y2][x1][i]->yPos + TILE_HEIGHT - ObjectSprite->yPos;
							}
							if ((TempYOverlap < 17 && TempYOverlap > 0) && TempXOverlap < 17 && TempXOverlap > 0) {
								SpriteOverlapX.push_back(LM[y2][x1][i]);
								SpriteX.push_back(TempXOverlap);
								SpriteOverlapY.push_back(LM[y2][x1][i]);
								SpriteY.push_back(TempYOverlap);
								TempXOverlap = 0;
								TempYOverlap = 0;
							}
						}
					}
					else if (TempY2Math == 0) { //you are perfectly in line with an y axis'
						for (int i = 0; i < LM[y2][x1].size(); i++) { // LL

							if (LM[y2][x1][i]->xPos > ObjectSprite->xPos) { //NEW (CHANGED)
								TempXOverlap = ObjectSprite->xPos + TILE_WIDTH - LM[y2][x1][i]->xPos;
							}
							else {
								TempXOverlap = LM[y2][x1][i]->xPos + TILE_WIDTH - ObjectSprite->xPos;
							}
							if (LM[y2][x1][i]->yPos > ObjectSprite->yPos) {
								TempYOverlap = ObjectSprite->yPos + TILE_HEIGHT - LM[y2][x1][i]->yPos;
							}
							else {
								TempYOverlap = LM[y2][x1][i]->yPos + TILE_HEIGHT - ObjectSprite->yPos;
							}
							if ((TempYOverlap < 17 && TempYOverlap > 0) && TempXOverlap < 17 && TempXOverlap > 0) {
								SpriteOverlapX.push_back(LM[y2][x1][i]);
								SpriteX.push_back(TempXOverlap);
								SpriteOverlapY.push_back(LM[y2][x1][i]);
								SpriteY.push_back(TempYOverlap);
								TempXOverlap = 0;
								TempYOverlap = 0;
							}
						}
						if (Debug) {
							printf("t\n");
						}
						for (int i = 0; i < LM[y2][x2].size(); i++) { // LR

							if (LM[y2][x2][i]->xPos > ObjectSprite->xPos) {//NEW (CHANGED)
								TempXOverlap = ObjectSprite->xPos + TILE_WIDTH - LM[y2][x2][i]->xPos;

							}
							else {
								TempXOverlap = LM[y2][x2][i]->xPos + TILE_WIDTH - ObjectSprite->xPos;
							}
							if (LM[y2][x2][i]->yPos > ObjectSprite->yPos) {
								TempYOverlap = ObjectSprite->yPos + TILE_HEIGHT - LM[y2][x2][i]->yPos;
							}
							else {
								TempYOverlap = LM[y2][x2][i]->yPos + TILE_HEIGHT - ObjectSprite->yPos;
							}
							if ((TempYOverlap < 17 && TempYOverlap > 0) && TempXOverlap < 17 && TempXOverlap > 0) {
								SpriteOverlapX.push_back(LM[y2][x2][i]);
								SpriteX.push_back(TempXOverlap);
								SpriteOverlapY.push_back(LM[y2][x2][i]);
								SpriteY.push_back(TempYOverlap);
								TempXOverlap = 0;
								TempYOverlap = 0;
							}
						}

					}
					else { //you are not perfectly aligned with anything, every 'point' matters.
						if (Debug) {
							printf("u\n");
						}
						for (int i = 0; i < LM[y1][x1].size(); i++) { // UL

							if (LM[y1][x1][i]->xPos > ObjectSprite->xPos) { //NEW (CHANGED)
								TempXOverlap = ObjectSprite->xPos + TILE_WIDTH - LM[y1][x1][i]->xPos;
							}
							else {
								TempXOverlap = LM[y1][x1][i]->xPos + TILE_WIDTH - ObjectSprite->xPos;
							}
							if (LM[y1][x1][i]->yPos < ObjectSprite->yPos) {
								TempYOverlap = LM[y1][x1][i]->yPos + TILE_HEIGHT - ObjectSprite->yPos;
							}
							else {
								TempYOverlap = ObjectSprite->yPos + TILE_HEIGHT - LM[y1][x1][i]->yPos;
							}

							if ((TempYOverlap < 17 && TempYOverlap > 0) && TempXOverlap < 17 && TempXOverlap > 0) {
								SpriteOverlapX.push_back(LM[y1][x1][i]);
								SpriteX.push_back(TempXOverlap);
								SpriteOverlapY.push_back(LM[y1][x1][i]);
								SpriteY.push_back(TempYOverlap);
								TempXOverlap = 0;
								TempYOverlap = 0;
							}
						}
						if (Debug) {
							printf("v\n");
						}
						for (int i = 0; i < LM[y2][x2].size(); i++) { // LR

							if (LM[y2][x2][i]->xPos > ObjectSprite->xPos) {//NEW (CHANGED)
								TempXOverlap = ObjectSprite->xPos + TILE_WIDTH - LM[y2][x2][i]->xPos;

							}
							else {
								TempXOverlap = LM[y2][x2][i]->xPos + TILE_WIDTH - ObjectSprite->xPos;
							}
							if (LM[y2][x2][i]->yPos > ObjectSprite->yPos) {
								TempYOverlap = ObjectSprite->yPos + TILE_HEIGHT - LM[y2][x2][i]->yPos;
							}
							else {
								TempYOverlap = LM[y2][x2][i]->yPos + TILE_HEIGHT - ObjectSprite->yPos;
							}
							if ((TempYOverlap < 17 && TempYOverlap > 0) && TempXOverlap < 17 && TempXOverlap > 0) {
								SpriteOverlapX.push_back(LM[y2][x2][i]);
								SpriteX.push_back(TempXOverlap);
								SpriteOverlapY.push_back(LM[y2][x2][i]);
								SpriteY.push_back(TempYOverlap);
								TempXOverlap = 0;
								TempYOverlap = 0;
							}
						}
						if (Debug) {
							printf("w\n");
						}
						for (int i = 0; i < LM[y2][x1].size(); i++) { // LL

							if (LM[y2][x1][i]->xPos > ObjectSprite->xPos) { //NEW (CHANGED)
								TempXOverlap = ObjectSprite->xPos + TILE_WIDTH - LM[y2][x1][i]->xPos;
							}
							else {
								TempXOverlap = LM[y2][x1][i]->xPos + TILE_WIDTH - ObjectSprite->xPos;
							}
							if (LM[y2][x1][i]->yPos > ObjectSprite->yPos) {
								TempYOverlap = ObjectSprite->yPos + TILE_HEIGHT - LM[y2][x1][i]->yPos;
							}
							else {
								TempYOverlap = LM[y2][x1][i]->yPos + TILE_HEIGHT - ObjectSprite->yPos;
							}

							if ((TempYOverlap < 17 && TempYOverlap > 0) && TempXOverlap < 17 && TempXOverlap > 0) {
								SpriteOverlapX.push_back(LM[y2][x1][i]);
								SpriteX.push_back(TempXOverlap);
								SpriteOverlapY.push_back(LM[y2][x1][i]);
								SpriteY.push_back(TempYOverlap);
								TempXOverlap = 0;
								TempYOverlap = 0;
							}
						}

					}
				}

			}
			else if (Measure == 15) {//DR
				//edges are [x1][y2], [x2][y2], [x2][y1]

				//Depending on how perfectly inligned with the grid you are, you can skip checking some edges/points.

				if (TempX2Math == 0 && TempY2Math == 0) { //you are perfectly in line with the gird

					if (Debug) {
						printf("x\n");
					}
					for (int i = 0; i < LM[y2][x2].size(); i++) { // LL
						if (LM[y2][x2][i]->xPos > ObjectSprite->xPos) {//NEW (CHANGED)
							TempXOverlap = ObjectSprite->xPos + TILE_WIDTH - LM[y2][x2][i]->xPos;

						}
						else {
							TempXOverlap = LM[y2][x2][i]->xPos + TILE_WIDTH - ObjectSprite->xPos;
						}
						if (LM[y2][x2][i]->yPos > ObjectSprite->yPos) {
							TempYOverlap = ObjectSprite->yPos + TILE_HEIGHT - LM[y2][x2][i]->yPos;
						}
						else {
							TempYOverlap = LM[y2][x2][i]->yPos + TILE_HEIGHT - ObjectSprite->yPos;
						}
						if ((TempYOverlap < 17 && TempYOverlap > 0) && TempXOverlap < 17 && TempXOverlap > 0) {
							SpriteOverlapX.push_back(LM[y2][x2][i]);
							SpriteX.push_back(TempXOverlap);
							SpriteOverlapY.push_back(LM[y2][x2][i]);
							SpriteY.push_back(TempYOverlap);
							TempXOverlap = 0;
							TempYOverlap = 0;
						}
					}
				}
				else {
					if (TempX2Math == 0) { //you are perfectly in line with an x axis'
						if (Debug) {
							printf("y\n");
						}
						for (int i = 0; i < LM[y1][x2].size(); i++) { // UR

							if (LM[y1][x2][i]->xPos > ObjectSprite->xPos) {//NEW (CHANGED)
								TempXOverlap = ObjectSprite->xPos + TILE_WIDTH - LM[y1][x2][i]->xPos;

							}
							else {
								TempXOverlap = LM[y1][x2][i]->xPos + TILE_WIDTH - ObjectSprite->xPos;

							}
							if (LM[y1][x2][i]->yPos < ObjectSprite->yPos) {
								TempYOverlap = LM[y1][x2][i]->yPos + TILE_HEIGHT - ObjectSprite->yPos;
							}
							else {
								TempYOverlap = ObjectSprite->yPos + TILE_HEIGHT - LM[y1][x2][i]->yPos;
							}
							if ((TempYOverlap < 17 && TempYOverlap > 0) && TempXOverlap < 17 && TempXOverlap > 0) {
								SpriteOverlapX.push_back(LM[y1][x2][i]);
								SpriteX.push_back(TempXOverlap);
								SpriteOverlapY.push_back(LM[y1][x2][i]);
								SpriteY.push_back(TempYOverlap);
								TempXOverlap = 0;
								TempYOverlap = 0;
							}
						}
						if (Debug) {
							printf("z\n");
						}
						for (int i = 0; i < LM[y2][x2].size(); i++) { // LR 

							if (LM[y2][x2][i]->xPos > ObjectSprite->xPos) {//NEW (CHANGED)
								TempXOverlap = ObjectSprite->xPos + TILE_WIDTH - LM[y2][x2][i]->xPos;

							}
							else {
								TempXOverlap = LM[y2][x2][i]->xPos + TILE_WIDTH - ObjectSprite->xPos;
							}
							if (LM[y2][x2][i]->yPos > ObjectSprite->yPos) {
								TempYOverlap = ObjectSprite->yPos + TILE_HEIGHT - LM[y2][x2][i]->yPos;

							}
							else {
								TempYOverlap = LM[y2][x2][i]->yPos + TILE_HEIGHT - ObjectSprite->yPos;

							}

							if ((TempYOverlap < 17 && TempYOverlap > 0) && TempXOverlap < 17 && TempXOverlap > 0) {
								SpriteOverlapX.push_back(LM[y2][x2][i]);
								SpriteX.push_back(TempXOverlap);
								SpriteOverlapY.push_back(LM[y2][x2][i]);
								SpriteY.push_back(TempYOverlap);
								TempXOverlap = 0;
								TempYOverlap = 0;
							}
						}
					}
					else if (TempY2Math == 0) { //you are perfectly in line with an y axis'
						if (Debug) {
							printf("aa\n");
						}
						for (int i = 0; i < LM[y2][x1].size(); i++) { // LR

							if (LM[y2][x1][i]->xPos > ObjectSprite->xPos) { //NEW (CHANGED)
								TempXOverlap = ObjectSprite->xPos + TILE_WIDTH - LM[y2][x1][i]->xPos;
							}
							else {
								TempXOverlap = LM[y2][x1][i]->xPos + TILE_WIDTH - ObjectSprite->xPos;
							}
							if (LM[y2][x1][i]->yPos > ObjectSprite->yPos) {
								TempYOverlap = ObjectSprite->yPos + TILE_HEIGHT - LM[y2][x1][i]->yPos;
							}
							else {
								TempYOverlap = LM[y2][x1][i]->yPos + TILE_HEIGHT - ObjectSprite->yPos;
							}

							if ((TempYOverlap < 17 && TempYOverlap > 0) && TempXOverlap < 17 && TempXOverlap > 0) {
								SpriteOverlapX.push_back(LM[y2][x1][i]);
								SpriteX.push_back(TempXOverlap);
								SpriteOverlapY.push_back(LM[y2][x1][i]);
								SpriteY.push_back(TempYOverlap);
								TempXOverlap = 0;
								TempYOverlap = 0;
							}
						}
						if (Debug) {
							printf("ab\n");
						}
						for (int i = 0; i < LM[y2][x2].size(); i++) { // LR

							if (LM[y2][x2][i]->xPos > ObjectSprite->xPos) {//NEW (CHANGED)
								TempXOverlap = ObjectSprite->xPos + TILE_WIDTH - LM[y2][x2][i]->xPos;

							}
							else {
								TempXOverlap = LM[y2][x2][i]->xPos + TILE_WIDTH - ObjectSprite->xPos;
							}
							if (LM[y2][x2][i]->yPos > ObjectSprite->yPos) {
								TempYOverlap = ObjectSprite->yPos + TILE_HEIGHT - LM[y2][x2][i]->yPos;
							}
							else {
								TempYOverlap = LM[y2][x2][i]->yPos + TILE_HEIGHT - ObjectSprite->yPos;
							}
							if ((TempYOverlap < 17 && TempYOverlap > 0) && TempXOverlap < 17 && TempXOverlap > 0) {
								SpriteOverlapX.push_back(LM[y2][x2][i]);
								SpriteX.push_back(TempXOverlap);
								SpriteOverlapY.push_back(LM[y2][x2][i]);
								SpriteY.push_back(TempYOverlap);
								TempXOverlap = 0;
								TempYOverlap = 0;
							}
						}

					}
					else { //you are not perfectly aligned with anything, every 'point' matters.
						if (Debug) {
							printf("ac\n");
						}
						for (int i = 0; i < LM[y2][x1].size(); i++) { // LL

							if (LM[y2][x1][i]->xPos > ObjectSprite->xPos) { //NEW (CHANGED)
								TempXOverlap = ObjectSprite->xPos + TILE_WIDTH - LM[y2][x1][i]->xPos;
							}
							else {
								TempXOverlap = LM[y2][x1][i]->xPos + TILE_WIDTH - ObjectSprite->xPos;
							}
							if (LM[y2][x1][i]->yPos > ObjectSprite->yPos) {
								TempYOverlap = ObjectSprite->yPos + TILE_HEIGHT - LM[y2][x1][i]->yPos;
							}
							else {
								TempYOverlap = LM[y2][x1][i]->yPos + TILE_HEIGHT - ObjectSprite->yPos;
							}

							if ((TempYOverlap < 17 && TempYOverlap > 0) && TempXOverlap < 17 && TempXOverlap > 0) {
								SpriteOverlapX.push_back(LM[y2][x1][i]);
								SpriteX.push_back(TempXOverlap);
								SpriteOverlapY.push_back(LM[y2][x1][i]);
								SpriteY.push_back(TempYOverlap);
								TempXOverlap = 0;
								TempYOverlap = 0;
							}
						}
						if (Debug) {
							printf("ad\n");
						}
						for (int i = 0; i < LM[y2][x2].size(); i++) { // LR

							if (LM[y2][x2][i]->xPos > ObjectSprite->xPos) {//NEW (CHANGED)
								TempXOverlap = ObjectSprite->xPos + TILE_WIDTH - LM[y2][x2][i]->xPos;

							}
							else {
								TempXOverlap = LM[y2][x2][i]->xPos + TILE_WIDTH - ObjectSprite->xPos;
							}
							if (LM[y2][x2][i]->yPos > ObjectSprite->yPos) {
								TempYOverlap = ObjectSprite->yPos + TILE_HEIGHT - LM[y2][x2][i]->yPos;
							}
							else {
								TempYOverlap = LM[y2][x2][i]->yPos + TILE_HEIGHT - ObjectSprite->yPos;
							}
							if ((TempYOverlap < 17 && TempYOverlap > 0) && TempXOverlap < 17 && TempXOverlap > 0) {
								SpriteOverlapX.push_back(LM[y2][x2][i]);
								SpriteX.push_back(TempXOverlap);
								SpriteOverlapY.push_back(LM[y2][x2][i]);
								SpriteY.push_back(TempYOverlap);
								TempXOverlap = 0;
								TempYOverlap = 0;
							}
						}
						if (Debug) {
							printf("ae\n");
						}
						for (int i = 0; i < LM[y1][x2].size(); i++) { // UR

							if (LM[y1][x2][i]->xPos > ObjectSprite->xPos) {//NEW (CHANGED)
								TempXOverlap = ObjectSprite->xPos + TILE_WIDTH - LM[y1][x2][i]->xPos;

							}
							else {
								TempXOverlap = LM[y1][x2][i]->xPos + TILE_WIDTH - ObjectSprite->xPos;

							}
							if (LM[y1][x2][i]->yPos < ObjectSprite->yPos) {
								TempYOverlap = LM[y1][x2][i]->yPos + TILE_HEIGHT - ObjectSprite->yPos;
							}
							else {
								TempYOverlap = ObjectSprite->yPos + TILE_HEIGHT - LM[y1][x2][i]->yPos;
							}

							if ((TempYOverlap < 17 && TempYOverlap > 0) && TempXOverlap < 17 && TempXOverlap > 0) {
								SpriteOverlapX.push_back(LM[y1][x2][i]);
								SpriteX.push_back(TempXOverlap);
								SpriteOverlapY.push_back(LM[y1][x2][i]);
								SpriteY.push_back(TempYOverlap);
								TempXOverlap = 0;
								TempYOverlap = 0;
							}

						}

					}
				}

			}
			//base l,r,u,d directions
			else if (Measure == 6) {//L
			//edges are [x1][y1] and [x1][y2]
				if (TempY2Math == 0) {
					if (Debug) {
						printf("af\n");
					}
					for (int i = 0; i < LM[y1][x1].size(); i++) {

						//Figureout if the overlap is at least 1
						if (true) {
							if (LM[y1][x1][i]->yPos > ObjectSprite->yPos) {
								yOverlapped = ObjectSprite->yPos + TILE_HEIGHT - LM[y1][x1][i]->yPos;
							}
							else { //if (Spos =< Posy 
								yOverlapped = LM[y1][x1][i]->yPos + TILE_HEIGHT - ObjectSprite->yPos;
							}
							if (yOverlapped > 0 && yOverlapped < 17) {
							}
						}

						//Overlap to be recorded
						if (true) {
							if (LM[y1][x1][i]->xPos > ObjectSprite->xPos) { //NEW (CHANGED)
								TempXOverlap = ObjectSprite->xPos + TILE_WIDTH - LM[y1][x1][i]->xPos;
							}
							else {
								TempXOverlap = LM[y1][x1][i]->xPos + TILE_WIDTH - ObjectSprite->xPos;
							}
						}

						//Pushback
						if ((yOverlapped > 0 && yOverlapped < 17) && TempXOverlap < 17 && TempXOverlap > 0) {
							SpriteOverlapX.push_back(LM[y1][x1][i]);
							SpriteX.push_back(TempXOverlap);
							yOverlapped = 0;
							TempXOverlap = 0;

						}
					}
				}
				else {
					if (Debug) {
						printf("ag\n");
					}
					for (int i = 0; i < LM[y1][x1].size(); i++) {

						//Figureout if the overlap is at least 1
						if (true) {

							yOverlapped = LM[y1][x1][i]->yPos + TILE_HEIGHT - ObjectSprite->yPos;

							if (yOverlapped > 0 && yOverlapped < 17) {
							}
						}

						//Overlap to be recorded
						if (true) {
							if (LM[y1][x1][i]->xPos > ObjectSprite->xPos) { //NEW (CHANGED)
								TempXOverlap = ObjectSprite->xPos + TILE_WIDTH - LM[y1][x1][i]->xPos;
							}
							else {
								TempXOverlap = LM[y1][x1][i]->xPos + TILE_WIDTH - ObjectSprite->xPos;
							}
						}

						//Pushback
						if ((yOverlapped > 0 && yOverlapped < 17) && TempXOverlap < 17 && TempXOverlap > 0) {
							SpriteOverlapX.push_back(LM[y1][x1][i]);
							SpriteX.push_back(TempXOverlap);
							yOverlapped = 0;
							TempXOverlap = 0;

						}
					}
					if (Debug) {
						printf("ah\n");
					}
					for (int i = 0; i < LM[y2][x1].size(); i++) {

						//Figureout if the overlap is at least 1
						if (true) {
							if (LM[y2][x1][i]->yPos > ObjectSprite->yPos) {
								yOverlapped = ObjectSprite->yPos + TILE_HEIGHT - LM[y2][x1][i]->yPos;
							}
							else { //if (Spos =< Posy  
								yOverlapped = LM[y2][x1][i]->yPos + TILE_HEIGHT - ObjectSprite->yPos;
							}
							if (yOverlapped > 0 && yOverlapped < 17) {
							}
						}

						//Overlap to be recorded
						if (true) {
							if (LM[y2][x1][i]->xPos > ObjectSprite->xPos) { //NEW (CHANGED)
								TempXOverlap = ObjectSprite->xPos + TILE_WIDTH - LM[y2][x1][i]->xPos;
							}
							else {
								TempXOverlap = LM[y2][x1][i]->xPos + TILE_WIDTH - ObjectSprite->xPos;
							}
						}

						//Pushback
						if ((yOverlapped > 0 && yOverlapped < 17) && TempXOverlap < 17 && TempXOverlap > 0) {
							SpriteOverlapX.push_back(LM[y2][x1][i]);
							SpriteX.push_back(TempXOverlap);
							yOverlapped = 0;
							TempXOverlap = 0;

						}
					}
				}
			}
			else if (Measure == 14) {//R
				//edges are [x2][y1] and [x2][y2]
				if (TempY2Math == 0) {
					if (Debug) {
						printf("ai\n");
					}
					for (int i = 0; i < LM[y1][x2].size(); i++) {

						//Figureout if the overlap is at least 1
						if (true) {
							if (LM[y1][x2][i]->yPos > ObjectSprite->yPos) {
								yOverlapped = ObjectSprite->yPos + TILE_HEIGHT - LM[y1][x2][i]->yPos;
							}
							else { //if (Spos =< Posy   
								yOverlapped = LM[y1][x2][i]->yPos + TILE_HEIGHT - ObjectSprite->yPos;
							}
							if (yOverlapped > 0 && yOverlapped < 17) {
								if (Debug) {
									printf("Truely overalpped with something (Going Right, at least one x pixel overlap UR)\n");
								}
							}
						}

						//Overlap to be recorded
						if (true) {
							if (LM[y1][x2][i]->xPos > ObjectSprite->xPos) { //NEW (CHANGED)
								TempXOverlap = ObjectSprite->xPos + TILE_WIDTH - LM[y1][x2][i]->xPos;

							}
							else {
								TempXOverlap = LM[y1][x2][i]->xPos + TILE_WIDTH - ObjectSprite->xPos;

							}
						}

						//Pushback
						if ((yOverlapped > 0 && yOverlapped < 17) && TempXOverlap < 17 && TempXOverlap > 0) {
							SpriteOverlapX.push_back(LM[y1][x2][i]);
							SpriteX.push_back(TempXOverlap);
							yOverlapped = 0;
							TempXOverlap = 0;
						}
					}
				}
				else {
					if (Debug) {
						printf("aj\n");
					}
					for (int i = 0; i < LM[y1][x2].size(); i++) {

						//Figureout if the overlap is at least 1
						if (true) {

							yOverlapped = LM[y1][x2][i]->yPos + TILE_HEIGHT - ObjectSprite->yPos;



							if (yOverlapped > 0 && yOverlapped < 17) {
								if (Debug) {
									printf("Truely overalpped with something (Going Right, at least one x pixel overlap UR)\n");
								}
							}
						}

						//Overlap to be recorded
						if (true) {
							if (LM[y1][x2][i]->xPos > ObjectSprite->xPos) {//NEW (CHANGED)
								TempXOverlap = ObjectSprite->xPos + TILE_WIDTH - LM[y1][x2][i]->xPos;

							}
							else {
								TempXOverlap = LM[y1][x2][i]->xPos + TILE_WIDTH - ObjectSprite->xPos;

							}
						}

						//Pushback
						if ((yOverlapped > 0 && yOverlapped < 17) && TempXOverlap < 17 && TempXOverlap > 0) {
							SpriteOverlapX.push_back(LM[y1][x2][i]);
							SpriteX.push_back(TempXOverlap);
							yOverlapped = 0;
							TempXOverlap = 0;
						}
					}
					if (Debug) {
						printf("ak\n");
					}
					for (int i = 0; i < LM[y2][x2].size(); i++) {

						//Figureout if the overlap is at least 1
						if (true) {
							if (LM[y2][x2][i]->yPos > ObjectSprite->yPos) {
								yOverlapped = ObjectSprite->yPos + TILE_HEIGHT - LM[y2][x2][i]->yPos;
							}
							else { //if (Spos =< Posy
								yOverlapped = LM[y2][x2][i]->yPos + TILE_HEIGHT - ObjectSprite->yPos;
							}
							if (yOverlapped > 0 && yOverlapped < 17) {
								if (Debug) {
									printf("Truely overalpped with something (Going Right, at least one x pixel overlap LR)\n");
								}
							}
						}

						//Overlap to be recorded
						if (true) {
							if (LM[y2][x2][i]->xPos > ObjectSprite->xPos) {//NEW (CHANGED)
								TempXOverlap = ObjectSprite->xPos + TILE_WIDTH - LM[y2][x2][i]->xPos;

							}
							else {
								TempXOverlap = LM[y2][x2][i]->xPos + TILE_WIDTH - ObjectSprite->xPos;
							}
						}

						//Pushback
						if ((yOverlapped > 0 && yOverlapped < 17) && TempXOverlap < 17 && TempXOverlap > 0) {
							SpriteOverlapX.push_back(LM[y2][x2][i]);
							SpriteX.push_back(TempXOverlap);
							yOverlapped = 0;
							TempXOverlap = 0;
						}
					}
				}
			}
			else if (Measure == 11) {//D
				//edges are [x1][y2] and [x2][y2]


				if (TempX2Math == 0) {
					if (Debug) {
						printf("al\n");
					}
					for (int i = 0; i < LM[y2][x1].size(); i++) {

						//Figureout if the overlap is at least 1
						if (true) {
							if (LM[y2][x1][i]->xPos > ObjectSprite->xPos) {
								xOverlapped = ObjectSprite->xPos + TILE_WIDTH - LM[y2][x1][i]->xPos;
							}
							else { //if (Spos =< Posx 
								xOverlapped = LM[y2][x1][i]->xPos + TILE_WIDTH - ObjectSprite->xPos;
							}
							if (xOverlapped > 0 && xOverlapped < 17) {
								if (Debug) {
									printf("Truely overalpped with something (Going Down, at least one x pixel overlap LL)\n");
								}
							}
						}

						//Figureout the actual overlap to be recorded (LL)
						if (true) {
							if (LM[y2][x1][i]->yPos > ObjectSprite->yPos) {
								TempYOverlap = ObjectSprite->yPos + TILE_HEIGHT - LM[y2][x1][i]->yPos;
								if (ObjectSprite->OrderCreation == 1) {
									printf("[yPos+16 - Spos] : %d + 16 - %d\n", ObjectSprite->yPos, LM[y2][x1][i]->yPos);
								}
							}
							else {
								TempYOverlap = LM[y2][x1][i]->yPos + TILE_HEIGHT - ObjectSprite->yPos;
							}
						}

						//Pushback
						if ((xOverlapped > 0 && xOverlapped < 17) && TempYOverlap < 17 && TempYOverlap > 0) {
							if (ObjectSprite->OrderCreation == 1) {
								printf("Pushback the D stack\n");
							}
							SpriteOverlapY.push_back(LM[y2][x1][i]);
							SpriteY.push_back(TempYOverlap);
							xOverlapped = 0;
							TempYOverlap = 0;
						}
					}
				}
				else {
					if (Debug) {
						printf("am\n");
					}
					for (int i = 0; i < LM[y2][x1].size(); i++) {

						//Figureout if the overlap is at least 1
						if (true) {

							xOverlapped = LM[y2][x1][i]->xPos + TILE_WIDTH - ObjectSprite->xPos;


							if (xOverlapped > 0 && xOverlapped < 17) {
								if (Debug) {
									printf("Truely overalpped with something (Going Down, at least one x pixel overlap LL)\n");
								}
							}
						}

						//Figureout the actual overlap to be recorded (LL)
						if (true) {
							if (LM[y2][x1][i]->yPos > ObjectSprite->yPos) {
								TempYOverlap = ObjectSprite->yPos + TILE_HEIGHT - LM[y2][x1][i]->yPos;
							}
							else {
								TempYOverlap = LM[y2][x1][i]->yPos + TILE_HEIGHT - ObjectSprite->yPos;
							}
						}

						//Pushback
						if ((xOverlapped > 0 && xOverlapped < 17) && TempYOverlap < 17 && TempYOverlap > 0) {
							SpriteOverlapY.push_back(LM[y2][x1][i]);
							SpriteY.push_back(TempYOverlap);
							xOverlapped = 0;
							TempYOverlap = 0;
						}

					}
					if (Debug) {
						printf("an\n");
					}
					for (int i = 0; i < LM[y2][x2].size(); i++) {

						//Figureout if the overlap is at least 1
						if (true) {
							if (LM[y2][x2][i]->xPos > ObjectSprite->xPos) {
								xOverlapped = ObjectSprite->xPos + TILE_WIDTH - LM[y2][x2][i]->xPos;
							}
							else { //if (Spos =< Posx
								xOverlapped = LM[y2][x2][i]->xPos + TILE_WIDTH - ObjectSprite->xPos;
							}
							if (xOverlapped > 0 && xOverlapped < 17) {
								if (Debug) {
									printf("Truely overalpped with something (Going Down, at least one x pixel overlap LR)\n");
								}
							}
						}

						//Figureout the actual overlap to be recorded (LR)
						if (true) {
							if (LM[y2][x2][i]->yPos > ObjectSprite->yPos) {
								TempYOverlap = ObjectSprite->yPos + TILE_HEIGHT - LM[y2][x2][i]->yPos;
							}
							else {
								TempYOverlap = LM[y2][x2][i]->yPos + TILE_HEIGHT - ObjectSprite->yPos;
							}
						}

						//Pushback
						if ((xOverlapped > 0 && xOverlapped < 17) && TempYOverlap < 17 && TempYOverlap > 0) {
							SpriteOverlapY.push_back(LM[y2][x2][i]);
							SpriteY.push_back(TempYOverlap);
							xOverlapped = 0;
							TempYOverlap = 0;
						}

					}
				}

			}
			else if (Measure == 9) {//U
				//edges are [x1][y1] and [x2][x1]
				if (TempX2Math == 0) {
					if (Debug) {
						printf("ao\n");
					}
					for (int i = 0; i < LM[y1][x1].size(); i++) {

						//Figureout if the overlap is at least 1
						if (true) {
							if (LM[y1][x1][i]->xPos > ObjectSprite->xPos) {
								xOverlapped = ObjectSprite->xPos + TILE_WIDTH - LM[y1][x1][i]->xPos;
							}
							else { //if (Spos =< Posx 
								xOverlapped = LM[y1][x1][i]->xPos + TILE_WIDTH - ObjectSprite->xPos;
							}
							if (xOverlapped > 0 && xOverlapped < 17) {
								if (Debug) {
									printf("Truely overalpped with something (Going UP, at least one x pixel overlap UL)\n");
								}
							}
						}

						//Overlap to be recorded
						if (true) {
							if (LM[y1][x1][i]->yPos < ObjectSprite->yPos) {
								TempYOverlap = LM[y1][x1][i]->yPos + TILE_HEIGHT - ObjectSprite->yPos;
							}
							else {
								TempYOverlap = ObjectSprite->yPos + TILE_HEIGHT - LM[y1][x1][i]->yPos;
							}
						}

						//Pushback
						if ((xOverlapped > 0 && xOverlapped < 17) && TempYOverlap < 17 && TempYOverlap > 0) {
							SpriteOverlapY.push_back(LM[y1][x1][i]);
							SpriteY.push_back(TempYOverlap);
							xOverlapped = 0;
							TempYOverlap = 0;
						}
					}
				}
				else {
					if (Debug) {
						printf("ap\n");
					}
					for (int i = 0; i < LM[y1][x1].size(); i++) {

						//Figureout if the overlap is at least 1
						if (true) {

							xOverlapped = LM[y1][x1][i]->xPos + TILE_WIDTH - ObjectSprite->xPos;

							if (xOverlapped > 0 && xOverlapped < 17) {
								if (Debug) {
									printf("Truely overalpped with something (Going UP, at least one x pixel overlap UL)\n");
								}
							}
						}

						//Overlap to be Recorded
						if (true) {
							if (LM[y1][x1][i]->yPos < ObjectSprite->yPos) {
								TempYOverlap = LM[y1][x1][i]->yPos + TILE_HEIGHT - ObjectSprite->yPos;
							}
							else {
								TempYOverlap = ObjectSprite->yPos + TILE_HEIGHT - LM[y1][x1][i]->yPos;
							}
						}

						//Pushback
						if ((xOverlapped > 0 && xOverlapped < 17) && TempYOverlap < 17 && TempYOverlap > 0) {
							SpriteOverlapY.push_back(LM[y1][x1][i]);
							SpriteY.push_back(TempYOverlap);
							xOverlapped = 0;
							TempYOverlap = 0;
						}
					}
					if (Debug) {
						printf("aq\n");
					}
					for (int i = 0; i < LM[y1][x2].size(); i++) {

						//Figureout if the overlap is at least 1
						if (true) {
							if (LM[y1][x2][i]->xPos > ObjectSprite->xPos) {
								xOverlapped = ObjectSprite->xPos + TILE_WIDTH - LM[y1][x2][i]->xPos;
							}
							else { //if (Spos =< Posx
								xOverlapped = LM[y1][x2][i]->xPos + TILE_WIDTH - ObjectSprite->xPos;
							}
							if (xOverlapped > 0 && xOverlapped < 17) {
								if (Debug) {
									printf("Truely overalpped with something (Going UP, at least one x pixel overlap UR)\n");
								}
							}
						}

						//Overlap to be recorded
						if (true) {
							if (LM[y1][x2][i]->yPos < ObjectSprite->yPos) {
								TempYOverlap = LM[y1][x2][i]->yPos + TILE_HEIGHT - ObjectSprite->yPos;
							}
							else {
								TempYOverlap = ObjectSprite->yPos + TILE_HEIGHT - LM[y1][x2][i]->yPos;
							}
						}

						//Pushback
						if ((xOverlapped > 0 && xOverlapped < 17) && TempYOverlap < 17 && TempYOverlap > 0) {
							SpriteOverlapY.push_back(LM[y1][x2][i]);
							SpriteY.push_back(TempYOverlap);
							xOverlapped = 0;
							TempYOverlap = 0;
						}


					}
				}
			}
			//still
			else if (Measure == 10) {//0
				if (Debug) {
					printf("ar\n");
				}
			}
			//All overlap, no collision
			if (Measure != 10) {
				//used just for testing directional/diag movements
			}

		}
		//	printf("3.3\n"); //Matrixes checked has been decided
			//We've got what we could be colliding with
			//Merge sort for most at the last of hte vector
			//If collide, don't flag for overlaps
			//If it does collide, then flag for overlap (all four corners)
		//PRUNE -Eliminate any dobules, and anything that doesn't collide. For now assume everything you overlap with collides -Sort by overlap most, figure out the order of collision. 
			//mergesort then merge
			//then prune doubles
			//then prune those without collision
		if (true) {
			/*
			//using swap since it's constant as opposed to insert.
			//also if we get one that is the exact same creation order, we want to erase it rather than swap it.
			std::vector<int> HaveSeen = {};
			bool found = false;
			//eliminate all doubles
			/*
			for (int i = 0; i < SpriteOverlap.size(); i++) {
				for (int j = 0; j < HaveSeen.size(); j++) { //would like a better version of this that stops when found
					if (SpriteOverlap[i]->OrderCreation == HaveSeen[j]) {
						found = true;
					}
				}
				if (found = true) {
					SpriteOverlap.erase(SpriteOverlap.begin() + i);
					SpriteArea.erase(SpriteArea.begin()+i);
					i--; //to balance out the erasure and the itteration of hte loop
				}
				else {
					HaveSeen.push_back(SpriteOverlap[i]->OrderCreation);
				}
				found = false;
			}
			//sort the stack by priority of colliding first. So it should go {this, ..., collides third, collides second, collides first}
			//This will differ from the previous tile collision because NOW we have every single tile possibly creating a localized stack. it is easier to find deadlocks probably. this also brings more value to a holder for items we have successfully moved.
			//for now we'll do a merge sort, but in the future we want to weigh how many things an object collided with/overlapped, and then sort it based on the size. If you say, collide with 100 objects, it is wort hdoing a merge sort or binary.
			MergeSortSpriteCollision(SpriteOverlap, SpriteArea, 0, SpriteOverlap.size());
			*/

			//merge sort each side individually
			SpriteOverlapX; //holds pointers to those overlapping x
			SpriteOverlapY; //hlds poitners to those overlapping y
			SpriteX; //holds x overlap values
			SpriteY; //holds y overlap values
			if (SpriteOverlapX.size() > 0) {
				MergeSortSpriteCollision(SpriteOverlapX, SpriteX);
			}
			if (SpriteOverlapY.size() > 0) {
				MergeSortSpriteCollision(SpriteOverlapY, SpriteY);
			}

		}


		//jack (inserted here hope its right) - here is fine, we will improve the merge eventually so this bit would be faster.
		int xloop = 0;
		int yloop = 0;
		if (SpriteOverlapX.size() > 1) {
			while (xloop < SpriteOverlapX.size() - 1) {
				for (int i = xloop + 1; i < SpriteOverlapX.size(); i++) {
					if (SpriteOverlapX[xloop] == SpriteOverlapX[i]) {
						SpriteOverlapX.erase(SpriteOverlapX.begin() + i);
						SpriteX.erase(SpriteX.begin() + i);
						i--;
					}
				}
				xloop++;
			}
		}
		if (SpriteOverlapY.size() > 1) {
			while (yloop < SpriteOverlapY.size() - 1) {
				for (int i = yloop + 1; i < SpriteOverlapY.size(); i++) {
					if (SpriteOverlapY[yloop] == SpriteOverlapY[i]) {
						SpriteOverlapY.erase(SpriteOverlapY.begin() + i);
						SpriteY.erase(SpriteY.begin() + i);
						i--;
					}
				}
				yloop++;
			}
		}

		//end of Jacks insertion. I should check this later. - I believe this gets rid of duplicates in the collision list (because multiple corners could collide, or a sprite may occupy two cells and be collided with by two different corners for hte check or something


		if (Debug) {
			if (Measure != 10) {
				printf("Direction for the moving sprite is = %d\n", Measure);
				printf("Moving Sprite positions = {xPos= %d, yPos= %d}\n", ObjectSprite->xPos, ObjectSprite->yPos);
			}
			if (SpriteOverlapX.size() > 0) {
				printf("Every item in the SpriteOverlapX =");
				for (int i = 0; i < SpriteOverlapX.size(); i++) {
					printf("{Object%d, ", SpriteOverlapX[i]->OrderCreation + 1);
					printf("Overlap = %d, xPos=%d, yPos=%d}", SpriteX[i], SpriteOverlapX[i]->xPos, SpriteOverlapX[i]->yPos);
					if (SpriteX[i] > 0) {

					}
				}
				printf("\n");
			}
			if (SpriteOverlapY.size() > 0) {
				printf("Every item in the SpriteOverlapY =");
				for (int i = 0; i < SpriteOverlapY.size(); i++) {
					printf("{Object%d, ", SpriteOverlapY[i]->OrderCreation + 1);
					printf("Overlap = %d, xPos=%d, yPos=%d}", SpriteY[i], SpriteOverlapY[i]->xPos, SpriteOverlapY[i]->yPos);
					if (SpriteY[i] > 0) {

					}
				}
				printf("\n");
			}
		}
		if (Debug) {
			if ((SpriteOverlapY.size() > 0 || SpriteOverlapX.size() > 0)) {
				printf("Take Time to ensure the above looks correct for Object%d.\n", ObjectSprite->OrderCreation + 1);

			}
		}




		//return the vector
		if (SpriteOverlapX.size() < 1) {
			if (Debug) {
				printf("no X collisions. empty vector pushed\n");
			}
			TempStackable->SpriteXCollision = {};
		}
		else {
			if (Debug) {
				printf("Collidied on X, something's pushed!\n");
			}
			TempStackable->SpriteXCollision = {};
			for (int i = 0; i < SpriteOverlapX.size(); i++) {
				TempStackable->SpriteXCollision.push_back(SpriteOverlapX[i]);
			}
		}
		if (SpriteOverlapY.size() < 1) {
			if (Debug) {
				printf("no Y collisions. empty vector pushed\n");
			}
			TempStackable->SpriteYCollision = {};
		}
		else {
			if (Debug) {
				printf("Collidied on Y, something's pushed!\n");
			}
			TempStackable->SpriteYCollision = {};
			for (int i = 0; i < SpriteOverlapY.size(); i++) {
				TempStackable->SpriteYCollision.push_back(SpriteOverlapY[i]);
			}
		}
		//Trying to figure out how to store then 'return' these values as readable.
		if (Debug) {
			if (TempStackable->SpriteXCollision.size() > 0) {

				printf("I've got an X collision with Object%d\n", TempStackable->SpriteXCollision[0]->OrderCreation + 1);

			}
			if (TempStackable->SpriteYCollision.size() > 0) {

				printf("I've got an Y collision with Object%d\n", TempStackable->SpriteYCollision[0]->OrderCreation + 1);

			}
		}
		if (TempStackable->SpriteYCollision.size() > 0 || TempStackable->SpriteXCollision.size() > 0) {
			TempStackable->Victim = ObjectSprite; //Our sprite is a 'victim', it can't move.
		}
		else {
			TempStackable->Victim = NULL; //it moved, so there is no 'victim'.
		}
		//= [{SpriteOverlapX}, {SpriteOverlapY}];
		if (Debug) {
			printf("3.4\n"); //arrray to return is created
		}
	}

	int CheckOverlap(Sprite* ObjectSprite) {
		RemoveSpriteFromMap(ObjectSprite); //Temporary, this is just for the testing for collision and the strange overlap. In the future it won't remove and then readd, but instead ignore itself when checking.
		bool Debug = false;
		if (Debug) {
			printf("Object Creation Order == %d\n", ObjectSprite->OrderCreation);
		}
		if (ObjectSprite->OrderCreation == 1 || ObjectSprite->OrderCreation == 0) {
			Debug = true;
		}
		else {
			Debug = false;
		}
		Debug = false;


		// printf("CheckFutureSpritePosition\n");
		int x1, x2, y1, y2;

		int TempX2, TempY2;

		x1 = ObjectSprite->xPos;
		x2 = ObjectSprite->xPos + TILE_WIDTH;
		y1 = ObjectSprite->yPos;
		y2 = ObjectSprite->yPos + TILE_HEIGHT;

		TempX2 = x2 % TILE_WIDTH;
		TempY2 = y1 % TILE_HEIGHT;
		int TempY2Math = y2 - TILE_HEIGHT * (y2 / TILE_HEIGHT); //A = C - B * (C/B)
		// printf("TempY2Math = y2 -16*(y2/16) = %d, from %d, %d\n", TempY2Math, TILE_HEIGHT, y2);
		int TempX2Math = x2 - TILE_WIDTH * (x2 / TILE_WIDTH);
		y1 = y1 / TILE_HEIGHT;
		y2 = y2 / TILE_HEIGHT;
		x1 = x1 / TILE_WIDTH;
		x2 = x2 / TILE_WIDTH;
		//gaurds from map/matrix overflow
		if (true) {
			if (y1 > LEVEL_HEIGHT - 1) {
				y1 = LEVEL_HEIGHT - 1;
				y2 = y1;
			}
			if (y1 < 0) {
				y1 = 0;
				y2 = y1;
			}
			if (x1 > LEVEL_WIDTH - 1) {
				x1 = LEVEL_WIDTH - 1;
				x2 = x1;
			}
			if (x1 < 0) {
				x1 = 0;
				x2 = x1;
			}
		}
		//So we don't check further than we want to, and when we don't need to. In these cases, it doens't matter now if we use x1, or x2. For consistency, we use whatever appears the most as appropriate. 
		if (true) {
			if (TempX2Math == 0) {
				x2 = x1;
			}
			if (TempY2Math == 0) {
				y2 = y1;
			}
		}

		int yOverlapped = 0;
		int xOverlapped = 0;
		if (true) {
			for (int i = 0; i < LM[y1][x1].size(); i++) {
				//Figureout if the overlapX is at least 1
				if (true) {
					if (LM[y1][x1][i]->yPos > ObjectSprite->yPos) {
						yOverlapped = ObjectSprite->yPos + TILE_HEIGHT - LM[y1][x1][i]->yPos;
					}
					else { //if (Spos =< Posy 
						yOverlapped = LM[y1][x1][i]->yPos + TILE_HEIGHT - ObjectSprite->yPos;
					}
				}

				//Figureout if the overlap is at least 1
				if (true) {
					if (LM[y1][x1][i]->xPos > ObjectSprite->xPos) {
						xOverlapped = ObjectSprite->xPos + TILE_WIDTH - LM[y1][x1][i]->xPos;
					}
					else { //if (Spos =< Posx 
						xOverlapped = LM[y1][x1][i]->xPos + TILE_WIDTH - ObjectSprite->xPos;
					}
				}

				if ((xOverlapped > 0 && xOverlapped < 17) && (yOverlapped > 0 && yOverlapped < 17)) {
					printf("Object%d overlapped with Object%d!\n", ObjectSprite->OrderCreation + 1, LM[y1][x1][i]->OrderCreation + 1);
					ReMapSprite(ObjectSprite);
					return 1; //you have overlapped 
				}
				yOverlapped = 0;
				xOverlapped = 0;
			}
			if (x1 != x2) {
				for (int i = 0; i < LM[y1][x2].size(); i++) {
					//Figureout if the overlap is at least 1
					if (true) {
						if (LM[y1][x2][i]->yPos > ObjectSprite->yPos) {
							yOverlapped = ObjectSprite->yPos + TILE_HEIGHT - LM[y1][x2][i]->yPos;
						}
						else { //if (Spos =< Posy   
							yOverlapped = LM[y1][x2][i]->yPos + TILE_HEIGHT - ObjectSprite->yPos;
						}
					}

					//Figureout if the overlap is at least 1
					if (true) {
						if (LM[y1][x2][i]->xPos > ObjectSprite->xPos) {
							xOverlapped = ObjectSprite->xPos + TILE_WIDTH - LM[y1][x2][i]->xPos;
						}
						else { //if (Spos =< Posx
							xOverlapped = LM[y1][x2][i]->xPos + TILE_WIDTH - ObjectSprite->xPos;
						}
					}

					if ((xOverlapped > 0 && xOverlapped < 17) && (yOverlapped > 0 && yOverlapped < 17)) {
						printf("Object%d overlapped with Object%d!\n", ObjectSprite->OrderCreation + 1, LM[y1][x2][i]->OrderCreation + 1);
						ReMapSprite(ObjectSprite);
						return 1; //you have overlapped 
					}
					yOverlapped = 0;
					xOverlapped = 0;
				}
			}
			if (y1 != y2) {
				for (int i = 0; i < LM[y2][x1].size(); i++) {
					//Figureout if the overlap is at least 1
					if (true) {
						if (LM[y2][x1][i]->xPos > ObjectSprite->xPos) {
							xOverlapped = ObjectSprite->xPos + TILE_WIDTH - LM[y2][x1][i]->xPos;
						}
						else { //if (Spos =< Posx 
							xOverlapped = LM[y2][x1][i]->xPos + TILE_WIDTH - ObjectSprite->xPos;
						}
					}

					//Figureout if the overlap is at least 1
					if (true) {
						if (LM[y2][x1][i]->yPos > ObjectSprite->yPos) {
							yOverlapped = ObjectSprite->yPos + TILE_HEIGHT - LM[y2][x1][i]->yPos;
						}
						else { //if (Spos =< Posy  
							yOverlapped = LM[y2][x1][i]->yPos + TILE_HEIGHT - ObjectSprite->yPos;
						}
					}

					if ((xOverlapped > 0 && xOverlapped < 17) && (yOverlapped > 0 && yOverlapped < 17)) {
						printf("Object%d overlapped with Object%d!\n", ObjectSprite->OrderCreation + 1, LM[y2][x1][i]->OrderCreation + 1);
						ReMapSprite(ObjectSprite);
						return 1; //you have overlapped 
					}
					yOverlapped = 0;
					xOverlapped = 0;
				}
				if (x1 != x2) {
					for (int i = 0; i < LM[y2][x2].size(); i++) {
						//Figureout if the overlap is at least 1
						if (true) {
							if (LM[y2][x2][i]->yPos > ObjectSprite->yPos) {
								yOverlapped = ObjectSprite->yPos + TILE_HEIGHT - LM[y2][x2][i]->yPos;
							}
							else { //if (Spos =< Posy
								yOverlapped = LM[y2][x2][i]->yPos + TILE_HEIGHT - ObjectSprite->yPos;
							}
						}

						//Figureout if the overlap is at least 1
						if (true) {
							if (LM[y2][x2][i]->xPos > ObjectSprite->xPos) {
								xOverlapped = ObjectSprite->xPos + TILE_WIDTH - LM[y2][x2][i]->xPos;
							}
							else { //if (Spos =< Posx
								xOverlapped = LM[y2][x2][i]->xPos + TILE_WIDTH - ObjectSprite->xPos;
							}
						}

						if ((xOverlapped > 0 && xOverlapped < 17) && (yOverlapped > 0 && yOverlapped < 17)) {
							printf("Object%d overlapped with Object%d!\n", ObjectSprite->OrderCreation + 1, LM[y2][x2][i]->OrderCreation + 1);
							ReMapSprite(ObjectSprite);
							return 1; //you have overlapped 
						}
						yOverlapped = 0;
						xOverlapped = 0;
					}
				}

			}
		}
		ReMapSprite(ObjectSprite);
		return 0;

	}

	//You may test this by just testing integers in a seperate file.
	void MergeSortSpriteCollision(std::vector<Sprite*>& SpriteOverlap, std::vector<int>& SpriteArea) { //we will be editing directly onto it
		bool Debug = false;
		if (Debug) {
			printf("MergeSort\n");
		}
		if (SpriteArea.size() > 1) {
			int M = SpriteArea.size() / 2;
			std::vector<int> LeftHalfArea(SpriteArea.begin(), SpriteArea.begin() + M);
			std::vector<int> RightHalfArea(SpriteArea.begin() + M, SpriteArea.begin() + SpriteArea.size());

			std::vector<Sprite*> LeftHalfOverlap(SpriteOverlap.begin(), SpriteOverlap.begin() + M);
			std::vector<Sprite*> RightHalfOverlap(SpriteOverlap.begin() + M, SpriteOverlap.begin() + SpriteOverlap.size());


			MergeSortSpriteCollision(LeftHalfOverlap, LeftHalfArea);
			MergeSortSpriteCollision(RightHalfOverlap, RightHalfArea);




			unsigned LeftItter = 0;
			unsigned RightItter = 0;
			unsigned SourceItter = 0;
			while (LeftItter < LeftHalfArea.size() && RightItter < RightHalfArea.size()) {
				if (LeftHalfArea[LeftItter] < RightHalfArea[RightItter]) {
					SpriteArea[SourceItter] = LeftHalfArea[LeftItter];
					SpriteOverlap[SourceItter] = LeftHalfOverlap[LeftItter];
					LeftItter++;
				}
				else {
					SpriteArea[SourceItter] = RightHalfArea[RightItter];
					SpriteOverlap[SourceItter] = RightHalfOverlap[RightItter];
					RightItter++;
				}
				SourceItter++;
			}

			while (LeftItter < LeftHalfArea.size()) {
				SpriteArea[SourceItter] = LeftHalfArea[LeftItter];
				SpriteOverlap[SourceItter] = LeftHalfOverlap[LeftItter];
				LeftItter++;
				SourceItter++;
			}

			while (RightItter < RightHalfArea.size()) {
				SpriteArea[SourceItter] = RightHalfArea[RightItter];
				SpriteOverlap[SourceItter] = RightHalfOverlap[RightItter];
				RightItter++;
				SourceItter++;
			}

		}



		if (Debug) {
			printf("Try Merging\n");
		}

	}

	void MoveAllSprites2() {
		bool Debug = false;

		ReCreateQue2();
		/**/
		std::vector<XYArr*> SpriteStacks = {}; //hold each XYArr with information
		int SpriteStacksCounter; //keeps track of something I forgot XD, maybe the current position when handling
		XYArr* TempStackable; //Holds the possible collision information
		std::vector<int> CompletedSprites;
		//Marking good moves/finished stops.
		CompletedSprites.resize(Queue2.size()); //this way we can simply insert to this a null or a poitner if worked.
		for (int i = 0; i < CompletedSprites.size(); i++) {
			CompletedSprites[i] = 0; //there are none that are initially 'completed'
		}
		bool endofstackX = false;
		bool endofstackY = false;

		for (int i = 0; i < AllSprites.size(); i++) { //{1, 4, 8, 10}

			if (i == 7 || i == 9 || i == 10) {
				Debug = true;
			}
			else {
				Debug = false;
			}
			//deleted large comment here, not sure why I had it. maybe based on previous version of stack?

			//for now who cares about handling the stack. For right now we are focused on just making sure we can see the stack we care about.
			if (Queue2[i] != NULL) { //redudant, archaic

				if (Debug) {
					printf("1\n");
				}
				RemoveSpriteFromMap(Queue2[i]);
				if (Debug) {
					printf("2\n");
				}
				Queue2[i]->Behavior();
				if (Debug) {
					printf("3\n");
				}
				TempStackable = new XYArr; //will delete if emptied, otherwise we'll push the object to the stack.
			   //Question, if I make a new XYArr, without deleting this one, will it change pointers automatically without overwritting? Yes it does :D!
				CheckFutureSpritePosition2(Queue2[i], TempStackable);
				//printf("TempStackable poitner is %p, for object%d\n", TempStackable, Queue2[i]->OrderCreation+1);
				// 
				//Check if we got anything

				//success
				if (TempStackable->Victim == NULL || (TempStackable->SpriteXCollision.size() < 1 && TempStackable->SpriteYCollision.size() < 1)) { //victim reduces the checks

					delete TempStackable;
					if (Debug) {
						printf("4\n");
					}
					Queue2[i]->MoveTargetTileX();
					if (Debug) {
						printf("5\n");
					}
					Queue2[i]->MoveTargetTileY();
					if (Debug) {
						printf("6\n");
					}
					ReMapSprite(Queue2[i]);
					CompletedSprites[i] = 1; //the Sprite with creation order 'i' has successfully completed it's movement
					if (Debug) {
						printf("Object%d is marked as completed, begin the Stack Check\n", Queue2[i]->OrderCreation + 1);
					}

					std::vector<int> InvestigateIndexsX = {};
					std::vector<int> InvestigateIndexsY = {};
					//search for the compelted sprite in the stack
					for (int d = 0; d < SpriteStacks.size(); d++) {

						//NOTE NOTE NOTE NOTE THIS NEEDS TO WORK UP A QUE SO LONG AS I>POPPED CREATIONORDER && COMPLETEDSPRITES[ORDERCREATION]==1, SO WE'VE FOUND THE START OF IT, NOW MAKE A WHILE THAT GOES 'UP' THE STACK
						if (SpriteStacks[d]->SpriteXCollision.size() > 0 && CompletedSprites[SpriteStacks[d]->SpriteXCollision[SpriteStacks[d]->SpriteXCollision.size() - 1]->OrderCreation] == 1) {
							SpriteStacks[d]->SpriteXCollision.pop_back();
							InvestigateIndexsX.push_back(d);
							while (SpriteStacks[d]->SpriteXCollision.size() > 0 && CompletedSprites[SpriteStacks[d]->SpriteXCollision[SpriteStacks[d]->SpriteXCollision.size() - 1]->OrderCreation] == 1) { //while there are things left to pop AND they have already successfully moved - will break when either your out of things to pop, or those items are ahead of the original Sprite you popped.
								SpriteStacks[d]->SpriteXCollision.pop_back();
								//InvestigateIndexsX.push_back(d); //already pushed back
							}

						}
						if (SpriteStacks[d]->SpriteYCollision.size() > 0 && CompletedSprites[SpriteStacks[d]->SpriteYCollision[SpriteStacks[d]->SpriteYCollision.size() - 1]->OrderCreation] == 1) {
							SpriteStacks[d]->SpriteYCollision.pop_back();
							InvestigateIndexsY.push_back(d);
							while (SpriteStacks[d]->SpriteYCollision.size() > 0 && CompletedSprites[SpriteStacks[d]->SpriteYCollision[SpriteStacks[d]->SpriteYCollision.size() - 1]->OrderCreation] == 1) { //while there are things left to pop AND they have already successfully moved - will break when either your out of things to pop, or those items are ahead of the original Sprite you popped.
								SpriteStacks[d]->SpriteYCollision.pop_back();
								//InvestigateIndexsY.push_back(d); //already pushed back
							}
						}
					}
					if (Debug) {
						printf("Stacks been looked at for Object%d.\n", Queue2[i]->OrderCreation + 1);
					}
					if (InvestigateIndexsY.size() > 0 || InvestigateIndexsX.size() > 0) {

						printf("Start Handle\n\n");

						HandleCollision2(InvestigateIndexsX, InvestigateIndexsY, SpriteStacks, CompletedSprites, i);
						if (Debug) {
							printf("Finished Handle\n");

						}
					}
					//should check for empty stacks, or pass them together to check as a pair.


					if (Debug) {
						printf("Null in Que Object%d\n", Queue2[i]->OrderCreation + 1);
					}
					Queue2[i] = NULL;

				}
				else {

					if (Debug) {
						printf("Push back the temp stack\n");
					}
					SpriteStacks.push_back(TempStackable); //do not delete until it is handled. Just overwrite Tempstackable poitner with new XYArr

					//NOTE Sprite with creation order 'i' has NOT completed it's movement. If it ever does, in relation to a stack handled elsewhere, then it shall be noted in CompletedSprites
					Queue2[i]->UndoBehavior();

					ReMapSprite(Queue2[i]);
					Queue2[i] = NULL;

				}

				//if you find an item at the end of a stack (whether that be the X or Y overlap), and attempt to move it.
				//either you fail, and it makes a new stack
				//you've reached the end, and it still fails, thus it's 'completed' and the stack it blocked is erased
				//you've succeeded, and thus move on to the one behind it. - marking on CompletedSprites the sprite.
					//Regarding the one behind it. If it has a creationiorder less than your current Que digit, you can move it
					// IF AND ONLY IF it is not 'true' in completed Sprites. Then mark it completed
					// if it has a creationorder greater than current que digit, you cannot move it. wait.



				//fail
				// undobehavior
				//remap
				// store the collision (could be collsion) prune the the no collision tiles.
				//When stack, x = {1, 5, 10, 8} -> 8
				//x = {1, 5, 8, 10} ->10, 8, 5, 1 (because they are less than 10).
				//XYArr[0]->push_back({}); <-these may be done already within checkfuture!
				//XYArr[1]->push_back({});


			//	printf("7\n");
				//SDL_Delay(100);
			}
			//satisfy the Stack

		}
		if (Debug) {
			printf("8	 HANLE THE REST OF STACK	\n");
		}
		/*
		while (SpriteStacks.size() > 0) {
			TempStackable = new XYArr; //besure to delete before leaving function.
			CheckFutureSpritePosition2(SpriteStacks[0]->Victim, TempStackable);
			printf("%d %d, %d %d\n", SpriteStacks[0]->Victim->xPos, SpriteStacks[0]->Victim->yPos, SpriteStacks[0]->Victim->TargetTile->x, SpriteStacks[0]->Victim->TargetTile->y);
			//ask jack to explain more in detail what each operation is doing. I'll look at it later tonight if I have time.
			int xChange = SpriteStacks[0]->Victim->xPos - SpriteStacks[0]->Victim->TargetTile->x; // +1 means moved right, -1 means moved left
			int yChange = SpriteStacks[0]->Victim->yPos - SpriteStacks[0]->Victim->TargetTile->y; // +1 means moved down, -1 means moved up
			printf("%d %d\n", xChange, yChange);
			printf("%d\n", TempStackable->SpriteXCollision.size());
			int x = TempStackable->SpriteXCollision.size(); // this is done so the same function is not called multiple times
			int y = TempStackable->SpriteYCollision.size(); // this is done so the same function is not called multiple times
			//teleports to appropriate position <-ask jack to make this afunction, not just an operation.
			if (x > 0) { // this is a check just to make sure the spriteXCollision is not empty
				if (xChange > 0) { // if moving right
					if (SpriteStacks[0]->Victim->TargetTile->x + TILE_WIDTH <= TempStackable->SpriteXCollision[x - 1]->TargetTile->x) { // this is just making sure that the x position of Current Victim is more left than the TempStackable one
						SpriteStacks[0]->Victim->TeleportX(TempStackable->SpriteXCollision[x - 1]->xPos - TILE_WIDTH);
					}
				}
				else { // if moving left
					if (SpriteStacks[0]->Victim->TargetTile->x >= TempStackable->SpriteXCollision[x - 1]->TargetTile->x + TILE_WIDTH) { // this checks to make sure the x position of the victim is more right than the sprite it's collidiing with
						SpriteStacks[0]->Victim->TeleportX(TempStackable->SpriteXCollision[x - 1]->xPos + TILE_WIDTH);
					}
				}
			}
			if (y > 0) { // this is a check just to make sure the spriteYCollision is not empty
				if (yChange > 0) { // if moving down
					if (SpriteStacks[0]->Victim->TargetTile->y + TILE_HEIGHT <= TempStackable->SpriteYCollision[y - 1]->TargetTile->y) { // this is just making sure that the y position of Current Victim is above than the TempStackable one
						SpriteStacks[0]->Victim->TeleportY(TempStackable->SpriteYCollision[y - 1]->yPos - TILE_HEIGHT);
					}
				}
				else { // if moving up
					if (SpriteStacks[0]->Victim->TargetTile->y >= TempStackable->SpriteYCollision[y - 1]->TargetTile->y + TILE_HEIGHT) { // this checks to make sure the y position of the victim is lower than the sprite it's collidiing with
						SpriteStacks[0]->Victim->TeleportY(TempStackable->SpriteYCollision[y - 1]->yPos + TILE_HEIGHT);
					}
				}
			}//flag it for collision
			ReMapSprite(SpriteStacks[0]->Victim); //quesiton, if I have two objects taht odn't oved on top of one another, this collision shoudl go off, and the undo, does that just keep it in the same space, no matter what? I feel like kif it doesn't move I shouldn't even allow it to enter the que in the first place... questions for later, might be less worth while the less object collision stacks that are possible. I should make some ratio of level to sprites to control how 'involved' the stack process is. for now lets go as deep as possible with the computation aspect, and trim down for other cases where the user doesn't care for such exact detections.
			printf("Remap Object%d [Current Victim]\n", SpriteStacks[0]->Victim->OrderCreation + 1);
			//no need ot pop from SpriteStacks
			//no need to insert to spritestacks
			CompletedSprites[SpriteStacks[0]->Victim->OrderCreation] = 1; //it's completed, won't move anymore. This way when we try to move the victims at the end of que2 to appropriate spaces, if they would collide with obj1 then that's what they'll do
			SpriteStacks.erase(SpriteStacks.begin());
			//SDL_Delay(10000);
		}
		printf("9	 HANLED THE REST OF STACK	\n");
		*/

		//clear the stack (delete teh stacks in spritestacks)
		//figure out why the sprites sometimes stutter, or move over more tahn they should
		//We need a frame global counter, so that random move doesn't switch directions mid frame, 
		// int GlobalFrame = x - (A)*(x/A), A=MaxFramerate - 
		//Eraseable size error

		//NEW
		SpriteStacks.clear();
		if (Debug) {
			printf("9 	 HANDLED REST OF STACK	 \n");
		}



		//For Random Sprites
		int xAxis = 0;
		int yAxis = 0;


		int Direction = 10;


		if (TIME < 18) {
			printf("Check all positions at the end of movement:\n");
			for (int i = 0; i < AllSprites.size(); i++) {
				if (true) {
					//Get direction (diagnonal, or 
					if (AllSprites[i]->xVec > 0) {
						//going right
						xAxis = 1;
					}
					else if (AllSprites[i]->xVec < 0) {
						//going left
						xAxis = -1;
					}
					else {
						xAxis = 0;
					}
					if (AllSprites[i]->yVec > 0) {
						//going down
						yAxis = 1;
					}
					else if (AllSprites[i]->yVec < 0) {
						//going up
						yAxis = -1;
					}
					else {
						yAxis = 0;
					}

					//can be improved by nesting. for now ignore.
					if (yAxis < 0 && xAxis < 0) { //diag UL
						Direction = 1 + 4; //5
					}
					else if (yAxis > 0 && xAxis > 0) { //diag LR
						Direction = 3 + 12; //15
					}
					else if (yAxis < 0 && xAxis > 0) { //diag UR
						Direction = 1 + 12;//13
					}
					else if (yAxis > 0 && xAxis < 0) { //diag LL
						Direction = 3 + 4; //7
					}
					else if (xAxis > 0) { //Right
						Direction = 12 + 2;//14
					}
					else if (xAxis < 0) { //Left
						Direction = 4 + 2; //6
					}
					else if (yAxis > 0) { //Down
						Direction = 3 + 8; //11
					}
					else if (yAxis < 0) { //Up
						Direction = 1 + 8; //9
					}
					else { //still
						Direction = 2 + 8; //10
					}


				}
				AllSprites[i]->AdjustedPositionX = false;
				AllSprites[i]->AdjustedPositionY = false;
				printf("Object%d, Current Position = {%d, %d}, Old Position = {%d, %d}, Velocities = {%d, %d}, Direction = %d\n", AllSprites[i]->OrderCreation + 1, AllSprites[i]->xPos, AllSprites[i]->yPos, AllSprites[i]->xPos - AllSprites[i]->xVec, AllSprites[i]->yPos - AllSprites[i]->yVec, AllSprites[i]->xVec, AllSprites[i]->yVec, Direction);
			}
		}
		/*
		if (TIME == 15) {
			printf("TIME==15\n");
			SDL_Delay(5000);
		}
		if (TIME == 16) {
			printf("TIME==16\n");
		}
		*/
		if (TIME == 17) {
			printf("TIME==17\n");
		}

		//For Test Sprites
		/*
		printf("Check all positions at the end of movement:\n");
		for (int i = 0; i < AllSprites.size(); i++) {
			printf("Object%d, {%d, %d}\n", AllSprites[i]->OrderCreation + 1, AllSprites[i]->xPos, AllSprites[i]->yPos);
		}
		SDL_Delay(500);
		*/

		if (Debug) {
			printf("Flag overlaps\n");
		}
		if (true) { //CheckOverlap(AllSprites[7])) { //interested in object 8 rn
			if (TIME < 17) {
				for (int i = 0; i < AllSprites.size(); i++) {
					if (CheckOverlap(AllSprites[i])) {
						printf("Total Frames Passed since inintialization = %d\n", TOTALFRAMECOUNT);
						SDL_Delay(3600000);
					}
				}
			}
		}

		if (Debug) {
			printf("Pause Opportunity\n"); //SDL_Delay(1500);
			printf("Frame = %d\n\n\n", TOTALFRAMECOUNT);
		}


	}

	void HandleCollision2(std::vector<int>InvestigateX, std::vector<int>InvestigateY, std::vector<XYArr*>& SpriteStacks, std::vector<int>& CompletedSprites, int QueLocation) {

		//already popped back the first we found. Now investigate those idnexes
		//1) Are you already completed <-pop back, add to our list
		//2) are you less than the current que location? And are you not a victim? pop back (this may be unlikely or mpossible)
		//3) are you empty at this index location for both x and y? Then erase it and move the interested stack, restarting the handle collision2.
		Sprite* TempSprite;
		bool IsTempSpriteVictim;
		std::vector<int> EraseableX = {};
		std::vector<int> EraseableY = {};
		bool Debug = false;
		//xs




		if (Debug) {
			printf("Remove Sprite we found at the end of the stack (I believe already done in the main)\n");
		}
		/*
		for (int i = 0; i < InvestigateX.size(); i++) {
			//if it's already been moved completely
			TempSprite = SpriteStacks[InvestigateX[i]]->SpriteXCollision[SpriteStacks[InvestigateX[i]]->SpriteXCollision.size() - 1]; //points to the end of the stack
			if (CompletedSprites[TempSprite->OrderCreation] == 1) {
				SpriteStacks[InvestigateX[i]]->SpriteXCollision.pop_back(); //record for next itteration?
			}


			//If your not a victim, and your already supposed to be moved, check the CompeltedSprites, if it is completed, remove it.
			//Your less than the que, and you've likely already gone, and your not in a stack, just double check that it has gone.
			if (TempSprite->OrderCreation < i && CompletedSprites[TempSprite->OrderCreation]==1) { //really only need the second but in th eevent we want an override for the order I want to be able to change the collision, or order creation somehow.
				if (CompletedSprites[TempSprite->OrderCreation] == 1) {
					SpriteStacks[InvestigateX[i]]->SpriteXCollision.pop_back(); //record for next itteration?
				}
			}
		}
		*/

		//the above comment is what we'd do if we didn't in main.

		//Okay, now we actually want to investigate those changed positions. 
		if (Debug) {
			printf("Now investigate those edited, see if we can get rid of any\n");
		}
		if (Debug) {
			printf("Displaying InvestigateX = {");
			for (int i = 0; i < InvestigateX.size(); i++) {
				printf("%d, ", InvestigateX[i]);
			}
			printf("}\n");
			printf("Displaying InvestigateY = {");
			for (int i = 0; i < InvestigateY.size(); i++) {
				printf("%d, ", InvestigateY[i]);
			}
			printf("}\n");
		}


		//Step 1) Figure out which ones to pop next if any. MAINLY: take the edited vectors, if both X and that Y are empty at the end of popping, attempt to move the victim, 
		for (int i = 0; i < InvestigateX.size(); i++) {
			if (SpriteStacks[InvestigateX[i]]->SpriteXCollision.size() < 1 && SpriteStacks[InvestigateX[i]]->SpriteYCollision.size() < 1) {
				EraseableX.push_back(InvestigateX[i]); //we're going to erase backwards, so the larger index of x and Y
			}
		}
		for (int i = 0; i < InvestigateY.size(); i++) {
			if (SpriteStacks[InvestigateY[i]]->SpriteYCollision.size() < 1 && SpriteStacks[InvestigateY[i]]->SpriteXCollision.size() < 1) {
				EraseableY.push_back(InvestigateY[i]); //we're going to erase backwards, so the larger index of x and Y
			}
		}
		if (Debug) {
			printf("Now that we've looked at them, EraseableV should have stacks whose victims are ready to be checked\n");
		}
		if (Debug) {
			if (EraseableX.size() > 0) {
				printf("EraseableX={");
				for (auto i = 0; i < EraseableX.size(); i++) {
					printf("%d, ", EraseableX[i]);
				}
				printf("}\n");
			}
			if (EraseableY.size() > 0) {
				printf("EraseableY={");
				for (auto i = 0; i < EraseableY.size(); i++) {
					printf("%d, ", EraseableY[i]);
				}
				printf("}\n");
			}
		}

		std::vector<Sprite*> VictimsNoLonger = {};

		//step 2, investigate those popped, see if any victims are left fully-alone
		//BREAKS SOMEWHERE BELOW HERE! 
		int Total = EraseableX.size() + EraseableY.size() - 1;

		for (int i = Total; i > -1; i--) {

			//if one of the sizes is empty, but the other is full
			if (EraseableX.size() > 0 && EraseableY.size() > 0) {

				//We have these three calls because if it's in ErasableX, it's from the InestigateX, likewise for Y, thus if it appeared in both of them somehow, we want to popit back from both of them
				//we also check the size of each, because we want to maintain some order (Earlier Sprites move before Later created Sprites)

				if (EraseableX[EraseableX.size() - 1] > EraseableY[EraseableY.size() - 1]) {


					VictimsNoLonger.push_back(SpriteStacks[EraseableX[EraseableX.size() - 1]]->Victim);
					SpriteStacks.erase(SpriteStacks.begin() + EraseableX[EraseableX.size() - 1]);
					EraseableX.pop_back();

				}
				else if (EraseableY[EraseableY.size() - 1] > EraseableX[EraseableX.size() - 1]) {

					VictimsNoLonger.push_back(SpriteStacks[EraseableY[EraseableY.size() - 1]]->Victim);
					SpriteStacks.erase(SpriteStacks.begin() + EraseableY[EraseableY.size() - 1]);
					EraseableY.pop_back();

				}
				else if (EraseableY[EraseableY.size() - 1] == EraseableX[EraseableX.size() - 1]) {

					VictimsNoLonger.push_back(SpriteStacks[EraseableX[EraseableX.size() - 1]]->Victim);
					SpriteStacks.erase(SpriteStacks.begin() + EraseableX[EraseableX.size() - 1]);
					EraseableX.pop_back();
					EraseableY.pop_back();

					i--;//popped twice, so go down an extra step in the loop.
				}
			}
			//If one or the other ran out of items to add to the vector.
			else if (EraseableX.size() > 0) {
				VictimsNoLonger.push_back(SpriteStacks[EraseableX[EraseableX.size() - 1]]->Victim); // error here
				SpriteStacks.erase(SpriteStacks.begin() + EraseableX[EraseableX.size() - 1]);
				EraseableX.pop_back();

			}
			else if (EraseableY.size() > 0) { //this should be a definite, but just for now
				VictimsNoLonger.push_back(SpriteStacks[EraseableY[EraseableY.size() - 1]]->Victim);
				SpriteStacks.erase(SpriteStacks.begin() + EraseableY[EraseableY.size() - 1]);
				EraseableY.pop_back();
			}
			//note on how this operation works.
			//EraseableX = {0, 5, 9, 12}, where these numbers are the index's on SpriteStacks that we last popped from, organized from least to greatest, Y is same.
			// Eraseable, also are those who's XYArr has empty X,Y collisions (as in those have been moved at some point). 
			//Then we don't want to accidently shift hte indexs, sowe approach from the back of the SpriteStacks while checking if we can erase. We ensure we don't erase any out of order through the first three if statements
			//The next two last are just to get rid of remaining.
			//Now we don't have doubles of indexs to erase. - we needed both of them, because it might've alerady had an empty X or Y by the time we popped the sprite.
			//Finally we store these indexes into VictimsNoLonger. we will, one by one, from youngest to oldest (so starting at the end of VictimsNoLonger)
				//see if we can move it. If checkfuture finds ANY collosion overlap, then do the proper undo's and flag it for collision.
			//don't flag for overlap, since that happens after everythings been moved properly. 

		}
		if (Debug) {
			printf("Now handle the victims no longer\n"); //so edit htevictims no longer so it goes once for the youngest, and then checks the indexs edited, and inserts properly new victims that are checkable. That way we can just run until victimsnolonger runs out.
		}
		if (Debug) {
			printf("VictimsNoLonger = {");
			for (int i = 0; i < VictimsNoLonger.size(); i++) {
				printf("Object%d, ", VictimsNoLonger[i]->OrderCreation + 1);
			}
			printf("}\n");
		}

		//Step 3, of those looked at, any victims that are empty should now beb moved. If they still cannot move, just do the proper undo procedure. 
			//This is because, from the get go we ahve everything it overlaps with, so everything it could've possibly ran into is known. Thus if we moved everything it could've run into, and it still hits something, it means it hit it for sure.

		//Step 4, if it could move, find the proper indexes to investigate in the Sprites stack, mark it as completed, and do this all over again

		//step 5 - exit
			//if you no longer find any stacks with pop able elements, return  to the que
		if (Debug) {
			printf("Take care of victims\n");
		}

		if (VictimsNoLonger.size() == 0) {
			printf("This might've caused the issue XD if size==0, then inside while size!=0, this was used to test something earlier by accident slipped through.\n");
		}

		while (VictimsNoLonger.size() != 0) {
			if (VictimsNoLonger[VictimsNoLonger.size() - 1]->OrderCreation == 7 || VictimsNoLonger[VictimsNoLonger.size() - 1]->OrderCreation == 9 || VictimsNoLonger[VictimsNoLonger.size() - 1]->OrderCreation == 10) {
				Debug = true;
			}
			else {
				Debug = false;
			}

			if (Debug) {
				printf("Top of VictimsNoLonger while loop\n");
				printf("Take care of victim = Object%d\n", VictimsNoLonger[VictimsNoLonger.size() - 1]->OrderCreation + 1);
			}
			HandleVictims(VictimsNoLonger[VictimsNoLonger.size() - 1], SpriteStacks, CompletedSprites, QueLocation, VictimsNoLonger); //new
			if (Debug) {
				printf("Finished HandleVictims\n");
			}
			VictimsNoLonger.pop_back(); //no matter what, either it moves or it doesn't, but it won't be part of the sprites stack anymore, thus there will never be another check for it
			if (Debug) {
				printf("Popped the victim from the stack\n");
			}
		}

		//since we popbacked each instance of the stacked sprite, we will investigate each of these locations again. We will erase it if it could not be erased.

	}

	void HandleVictims(Sprite* CurrentVictim, std::vector<XYArr*>& SpriteStacks, std::vector<int>& CompletedSprites, int QueLocation, std::vector<Sprite*>& VictimsNoLongerOrigin) {

		bool Debug = false;

		if (CurrentVictim->OrderCreation == 7 || CurrentVictim->OrderCreation == 9 || CurrentVictim->OrderCreation == 10) {
			Debug = true;
		}
		else {
			Debug = false;
		}



		//move victim,
		if (Debug) {
			printf("Try to move Object%d [handlevictim]\n", CurrentVictim->OrderCreation + 1);
		}
		RemoveSpriteFromMap(CurrentVictim);
		CurrentVictim->Behavior();
		XYArr* TempStackable; //used to just see if it's empty or not
		TempStackable = new XYArr; //besure to delete before leaving function.
		CheckFutureSpritePosition2(CurrentVictim, TempStackable);

		int xD = 0;
		int yD = 0;
		if (true || Debug) {
			//Y=-1,0,1, [1, 2, 3] X=-1, 0, 1, [4, 8, 12] 
			xD = 8;
			yD = 2;
			if (CurrentVictim->xVec > 0) {
				xD = 12;
			}
			else {
				xD = 4;
			}
			if (CurrentVictim->yVec > 0) {
				yD = 3;
			}
			else {
				yD = 1;
			}
			printf("Check new direction was saved direction for Object%d = %d\n", CurrentVictim->OrderCreation + 1, xD + yD);
		}


		if (Debug) {
			printf("Finished checking Object%d's future\n", CurrentVictim->OrderCreation + 1);
		}
		//disiabled simply so that I can test the other statement

		if (TempStackable->SpriteXCollision.size() > 0 || TempStackable->SpriteYCollision.size() > 0) {
			if (Debug) {
				printf("Collided at the end of it's movement\n");
			}
			//undo the behavior, or teleport it to the most appropriate position,
			//undo the behavior, or teleport it to the most appropriate position,
			// CurrentVictim->UndoBehavior(); //temporary, what will have ot happen is a teleport to appropriate collision location.
			if (Debug) {
				printf("%d %d, %d %d\n", CurrentVictim->xPos, CurrentVictim->yPos, CurrentVictim->TargetTile->x, CurrentVictim->TargetTile->y);
			}
			int xChange = CurrentVictim->xVec; // +1 means moved right, -1 means moved left
			int yChange = CurrentVictim->yVec; // +1 means moved down, -1 means moved up
			if (Debug) {
				printf("%d %d\n", xChange, yChange);
				printf("Size of Temp StackableX = %d\n", TempStackable->SpriteXCollision.size());
				printf("Size of Temp StackableY =%d\n", TempStackable->SpriteYCollision.size());

			}
			int x = TempStackable->SpriteXCollision.size(); // this is done so the same function is not called multiple times
			int y = TempStackable->SpriteYCollision.size(); // this is done so the same function is not called multiple times

			if (true) {
				printf("Teleport! Object%d\n", CurrentVictim->OrderCreation + 1);
			}




			bool wait = false;

			//print out stackables
			if (false) {
				printf("SpriteXC = {");
				for (int d = 0; d < x; d++) {
					printf("Object%d, ", TempStackable->SpriteXCollision[d]->OrderCreation + 1);
				}
				printf("}\n");
				printf("SpriteYC = {");
				for (int d = 0; d < y; d++) {
					printf("Object%d, ", TempStackable->SpriteYCollision[d]->OrderCreation + 1);
				}
				printf("}\n");
			}





			if (x > 0 && y > 0) {
				if (xChange != 0 && yChange != 0) {
					if (Debug || true) {
						printf("Diagonal xChange !=0, yChange !=0\n");
					}
					//hopper called before - so that we have the same object. 
						//this may cause errors, consider theres a 1 by 1 overlap with an object above you, to the right, and one to your left. obviously you want to stop in that case, but if we just loook at one, it'll have us keep going left for hte sliding. in that case, we should adjust to be at the proper location, pop_back, and then adjust again on the other axis.

						//teleport both appropriately
						//are you going directional, or diagonal.



					//Pause printf("1) Moving Diagonally\n"); SDL_Delay(2000);
					//if diagonal,  AND there are things that we hit?

						//figure out the relative position of the object in question
							//first we will find the 'travel path', then we will check each of the three possible locations (using the 'old' position 
							//finally, using find to go thorugh the vectors of the map, and if we do not find it, it will make a boolean false.
						//where the object collided with resides.
					bool up = false;
					bool down = false;
					bool left = false;
					bool right = false;
					int oldx = CurrentVictim->xPos - CurrentVictim->xVec;
					int oldy = CurrentVictim->yPos - CurrentVictim->yVec;
					int TempY2MathOld = oldy + 16 - TILE_HEIGHT * ((oldy + 16) / TILE_HEIGHT); //A = C - B * (C/B) 
					int TempX2MathOld = oldx + 16 - TILE_WIDTH * ((oldx + 16) / TILE_WIDTH);
					int TempX2Math = CurrentVictim->xPos - TILE_WIDTH * (CurrentVictim->xPos / TILE_WIDTH);
					int TempY2Math = CurrentVictim->yPos - TILE_HEIGHT * (CurrentVictim->yPos / TILE_HEIGHT);
					int x1 = CurrentVictim->xPos;
					int x2 = CurrentVictim->xPos + TILE_WIDTH;
					int y1 = CurrentVictim->yPos;
					int y2 = CurrentVictim->yPos + TILE_HEIGHT;
					if (TempX2Math == 0) {
						x2 = x1;
					}
					if (TempY2Math == 0) {
						y2 = y1;
					}
					x1 = x1 / TILE_WIDTH;
					x2 = x2 / TILE_WIDTH;
					y1 = y1 / TILE_HEIGHT;
					y2 = y2 / TILE_HEIGHT;

					//NEW - these are to prevent the jittering when the overlap is equal on the diagonal collision, when it should only stop on one axis because of how it was sliding. Of course, if you slide against two it's another story.
					//CHECK - IDEA - perhaps I should compare overlap of diagonal to the edges, and figure out which axis matters first, resolve those, then attempt to resolve the remaining axis' if still relavent. Implement this after getting the jitter fixed maybe.
					bool AdjustedX = false;
					bool AdjustedY = false;

					//Okay, so thinking this through, we want to calculate our overlap independently of what is doing above. 
					//CHANGE - make hte loops work if x2=x1, but only run the necessary ones.
					//INSERT - insert temporary x and y overlaps to set the arrays equal to
					//INSERT - at the end of all the corner fangaling, figure out the proper teleport, if you can compare them.
					//INSERT - teleport the two 'edge' cases, then figure out the overlap of the diagonal. 


					int UL[2] = { -1000, -1000 }; //holds, for this corner, the upper left quadrent, the first index in both {xc, yc}, of which the first item of overlap appears (whether that be in the x or y)?
					int LL[2] = { -1000, -1000 };
					int UR[2] = { -1000, -1000 };
					int LR[2] = { -1000, -1000 };

					Sprite* ULptr[2] = { nullptr,nullptr };
					Sprite* LLptr[2] = { nullptr,nullptr };
					Sprite* URptr[2] = { nullptr,nullptr };
					Sprite* LRptr[2] = { nullptr,nullptr };



					//what direction are you heading?
					if (CurrentVictim->xVec < 0) {
						left = true;
					}
					else {
						right = true;
					}
					if (CurrentVictim->yVec < 0) {
						up = true;
					}
					else {
						down = true;
					}

					bool EarlyBreak = false;

					//Great, now what sprites are you potentially hitting? (Relys on XYArr right now)
					if (left && up) { //left up

						if (x1 == x2 && y1 == y2) {
							//just the diagonal

							//search both x and y for the first that appears.  both overlap values will be important.
							for (int j = 0; j < TempStackable->SpriteXCollision.size(); j++) {
								for (int i = 0; i < LM[y1][x1].size(); i++) {
									if (LM[y1][x1][i] == TempStackable->SpriteXCollision[j]) {
										//calcualte the overlap 
										printf("UL -> Ran into Object%d first\n", TempStackable->SpriteXCollision[j]->OrderCreation + 1);
										ULptr[0] = TempStackable->SpriteXCollision[j];
										EarlyBreak = true;
										break;
									}
								}
								if (EarlyBreak) {
									break;
								}
							}
							EarlyBreak = false;
							for (int j = 0; j < TempStackable->SpriteYCollision.size(); j++) {
								for (int i = 0; i < LM[y1][x1].size(); i++) {
									if (LM[y1][x1][i] == TempStackable->SpriteYCollision[j]) {
										//calcualte the overlap 
										printf("UL -> Ran into Object%d first\n", TempStackable->SpriteYCollision[j]->OrderCreation + 1);
										ULptr[1] = TempStackable->SpriteYCollision[j];
										EarlyBreak = true;
										break;
									}
								}
								if (EarlyBreak) {
									break;
								}
							}
							EarlyBreak = false;
						}
						else if (x1 == x2) {
							//just test the y axis edge

							//search both x and y for the first that appears.  both overlap values will be important.
							for (int j = 0; j < TempStackable->SpriteXCollision.size(); j++) {
								for (int i = 0; i < LM[y1][x1].size(); i++) {
									if (LM[y1][x1][i] == TempStackable->SpriteXCollision[j]) {
										//calcualte the overlap 
										printf("UL -> Ran into Object%d first\n", TempStackable->SpriteXCollision[j]->OrderCreation + 1);
										ULptr[0] = TempStackable->SpriteXCollision[j];
										EarlyBreak = true;
										break;
									}
								}
								if (EarlyBreak) {
									break;
								}
							}
							EarlyBreak = false;
							for (int j = 0; j < TempStackable->SpriteYCollision.size(); j++) {
								for (int i = 0; i < LM[y1][x1].size(); i++) {
									if (LM[y1][x1][i] == TempStackable->SpriteYCollision[j]) {
										//calcualte the overlap 
										printf("UL -> Ran into Object%d first\n", TempStackable->SpriteYCollision[j]->OrderCreation + 1);
										ULptr[1] = TempStackable->SpriteYCollision[j];
										EarlyBreak = true;
										break;
									}
								}
								if (EarlyBreak) {
									break;
								}
							}
							EarlyBreak = false;

							//Serch for first xc taht appears, only hte X overlap will be important.
							for (int j = 0; j < TempStackable->SpriteXCollision.size(); j++) {
								for (int i = 0; i < LM[y2][x1].size(); i++) {
									if (LM[y2][x1][i] == TempStackable->SpriteXCollision[j]) {
										//calcualte the overlap 
										printf("LL -> Ran into Object%d first\n", TempStackable->SpriteXCollision[j]->OrderCreation + 1);
										LLptr[0] = TempStackable->SpriteXCollision[j];
										LLptr[1] = TempStackable->SpriteYCollision[j];
										EarlyBreak = true;
										break;
									}
								}
								if (EarlyBreak) {
									break;
								}
							}
							EarlyBreak = false;

						}
						else if (y1 == y2) {
							//just test the x axis edge

							//search both x and y for the first that appears.  both overlap values will be important.
							for (int j = 0; j < TempStackable->SpriteXCollision.size(); j++) {
								for (int i = 0; i < LM[y1][x1].size(); i++) {
									if (LM[y1][x1][i] == TempStackable->SpriteXCollision[j]) {
										//calcualte the overlap 
										printf("UL -> Ran into Object%d first\n", TempStackable->SpriteXCollision[j]->OrderCreation + 1);
										ULptr[0] = TempStackable->SpriteXCollision[j];
										EarlyBreak = true;
										break;
									}
								}
								if (EarlyBreak) {
									break;
								}
							}
							EarlyBreak = false;
							for (int j = 0; j < TempStackable->SpriteYCollision.size(); j++) {
								for (int i = 0; i < LM[y1][x1].size(); i++) {
									if (LM[y1][x1][i] == TempStackable->SpriteYCollision[j]) {
										//calcualte the overlap 
										printf("UL -> Ran into Object%d first\n", TempStackable->SpriteYCollision[j]->OrderCreation + 1);
										ULptr[1] = TempStackable->SpriteYCollision[j];
										EarlyBreak = true;
										break;
									}
								}
								if (EarlyBreak) {
									break;
								}
							}
							EarlyBreak = false;
							//search for the first yc that appears, only the Y overlap will be important
							for (int j = 0; j < TempStackable->SpriteYCollision.size(); j++) {
								for (int i = 0; i < LM[y1][x2].size(); i++) {
									if (LM[y1][x2][i] == TempStackable->SpriteYCollision[j]) {
										//calcualte the overlap 
										printf("UR -> Ran into Object%d first\n", TempStackable->SpriteYCollision[j]->OrderCreation + 1);
										URptr[1] = TempStackable->SpriteYCollision[j];
										URptr[0] = TempStackable->SpriteYCollision[j];
										EarlyBreak = true;
										break;
									}
								}
								if (EarlyBreak) {
									break;
								}
							}
							EarlyBreak = false;
						}
						else {
							//test all three

							//search both x and y for the first that appears.  both overlap values will be important.
							for (int j = 0; j < TempStackable->SpriteXCollision.size(); j++) {
								for (int i = 0; i < LM[y1][x1].size(); i++) {
									if (LM[y1][x1][i] == TempStackable->SpriteXCollision[j]) {
										//calcualte the overlap 
										printf("UL -> Ran into Object%d first\n", TempStackable->SpriteXCollision[j]->OrderCreation + 1);
										ULptr[0] = TempStackable->SpriteXCollision[j];
										EarlyBreak = true;
										break;
									}
								}
								if (EarlyBreak) {
									break;
								}
							}
							EarlyBreak = false;
							for (int j = 0; j < TempStackable->SpriteYCollision.size(); j++) {
								for (int i = 0; i < LM[y1][x1].size(); i++) {
									if (LM[y1][x1][i] == TempStackable->SpriteYCollision[j]) {
										//calcualte the overlap 
										printf("UL -> Ran into Object%d first\n", TempStackable->SpriteYCollision[j]->OrderCreation + 1);
										ULptr[1] = TempStackable->SpriteYCollision[j];
										EarlyBreak = true;
										break;
									}
								}
								if (EarlyBreak) {
									break;
								}
							}
							EarlyBreak = false;

							//search for the first yc that appears, only the Y overlap will be important
							for (int j = 0; j < TempStackable->SpriteYCollision.size(); j++) {
								for (int i = 0; i < LM[y1][x2].size(); i++) {
									if (LM[y1][x2][i] == TempStackable->SpriteYCollision[j]) {
										//calcualte the overlap 
										printf("UR -> Ran into Object%d first\n", TempStackable->SpriteYCollision[j]->OrderCreation + 1);
										URptr[1] = TempStackable->SpriteYCollision[j];
										URptr[0] = TempStackable->SpriteYCollision[j];
										EarlyBreak = true;
										break;
									}
								}
								if (EarlyBreak) {
									break;
								}
							}
							EarlyBreak = false;

							//Serch for first xc taht appears, only hte X overlap will be important.
							for (int j = 0; j < TempStackable->SpriteXCollision.size(); j++) {
								for (int i = 0; i < LM[y2][x1].size(); i++) {
									if (LM[y2][x1][i] == TempStackable->SpriteXCollision[j]) {
										//calcualte the overlap 
										printf("LL -> Ran into Object%d first\n", TempStackable->SpriteXCollision[j]->OrderCreation + 1);
										LLptr[0] = TempStackable->SpriteXCollision[j];
										LLptr[1] = TempStackable->SpriteYCollision[j];
										EarlyBreak = true;
										break;
									}
								}
								if (EarlyBreak) {
									break;
								}
							}
							EarlyBreak = false;

						}

					}
					else if (right && down) { //right, down 

						if (x1 == x2 && y1 == y2) {
							//just the diagonal
							//search both x and y for the first that appears.  both overlap values will be important.
							for (int j = 0; j < TempStackable->SpriteXCollision.size(); j++) {
								for (int i = 0; i < LM[y2][x2].size(); i++) {
									if (LM[y2][x2][i] == TempStackable->SpriteXCollision[j]) {
										//calcualte the overlap 
										printf("LR -> Ran into Object%d first\n", TempStackable->SpriteXCollision[j]->OrderCreation + 1);
										LRptr[0] = TempStackable->SpriteXCollision[j];
										EarlyBreak = true;
										break;
									}
								}
								if (EarlyBreak) {
									break;
								}
							}
							EarlyBreak = false;
							for (int j = 0; j < TempStackable->SpriteYCollision.size(); j++) {
								for (int i = 0; i < LM[y2][x2].size(); i++) {
									if (LM[y2][x2][i] == TempStackable->SpriteYCollision[j]) {
										//calcualte the overlap 
										printf("LR -> Ran into Object%d first\n", TempStackable->SpriteYCollision[j]->OrderCreation + 1);
										LRptr[1] = TempStackable->SpriteYCollision[j];
										EarlyBreak = true;
										break;
									}
								}
								if (EarlyBreak) {
									break;
								}
							}
							EarlyBreak = false;
						}
						else if (x1 == x2) {
							//just test the y axis edge

							//search both x and y for the first that appears.  both overlap values will be important.
							for (int j = 0; j < TempStackable->SpriteXCollision.size(); j++) {
								for (int i = 0; i < LM[y2][x2].size(); i++) {
									if (LM[y2][x2][i] == TempStackable->SpriteXCollision[j]) {
										//calcualte the overlap 
										printf("LR -> Ran into Object%d first\n", TempStackable->SpriteXCollision[j]->OrderCreation + 1);
										LRptr[0] = TempStackable->SpriteXCollision[j];
										EarlyBreak = true;
										break;
									}
								}
								if (EarlyBreak) {
									break;
								}
							}
							EarlyBreak = false;

							for (int j = 0; j < TempStackable->SpriteYCollision.size(); j++) {
								for (int i = 0; i < LM[y2][x2].size(); i++) {
									if (LM[y2][x2][i] == TempStackable->SpriteYCollision[j]) {
										//calcualte the overlap 
										printf("LR -> Ran into Object%d first\n", TempStackable->SpriteYCollision[j]->OrderCreation + 1);
										LRptr[1] = TempStackable->SpriteYCollision[j];
										EarlyBreak = true;
										break;
									}
								}
								if (EarlyBreak) {
									break;
								}
							}
							EarlyBreak = false;
							//Serch for first xc taht appears, only hte X overlap will be important. 
							for (int j = 0; j < TempStackable->SpriteXCollision.size(); j++) {
								for (int i = 0; i < LM[y1][x2].size(); i++) {
									if (LM[y1][x2][i] == TempStackable->SpriteXCollision[j]) {
										//calcualte the overlap 
										printf("UR -> Ran into Object%d first\n", TempStackable->SpriteXCollision[j]->OrderCreation + 1);
										URptr[0] = TempStackable->SpriteXCollision[j];
										URptr[1] = TempStackable->SpriteYCollision[j];
										EarlyBreak = true;
										break;
									}
								}
								if (EarlyBreak) {
									break;
								}
							}
							EarlyBreak = false;
						}
						else if (y1 == y2) {
							//just test the x axis edge
							//search both x and y for the first that appears.  both overlap values will be important.
							for (int j = 0; j < TempStackable->SpriteXCollision.size(); j++) {
								for (int i = 0; i < LM[y2][x2].size(); i++) {
									if (LM[y2][x2][i] == TempStackable->SpriteXCollision[j]) {
										//calcualte the overlap 
										printf("LR -> Ran into Object%d first\n", TempStackable->SpriteXCollision[j]->OrderCreation + 1);
										LRptr[0] = TempStackable->SpriteXCollision[j];
										EarlyBreak = true;
										break;
									}
								}
								if (EarlyBreak) {
									break;
								}
							}
							EarlyBreak = false;
							for (int j = 0; j < TempStackable->SpriteYCollision.size(); j++) {
								for (int i = 0; i < LM[y2][x2].size(); i++) {
									if (LM[y2][x2][i] == TempStackable->SpriteYCollision[j]) {
										//calcualte the overlap 
										printf("LR -> Ran into Object%d first\n", TempStackable->SpriteYCollision[j]->OrderCreation + 1);
										LRptr[1] = TempStackable->SpriteYCollision[j];
										EarlyBreak = true;
										break;
									}
								}
								if (EarlyBreak) {
									break;
								}
							}
							EarlyBreak = false;
							//search for the first yc that appears, only the Y overlap will be important
							for (int j = 0; j < TempStackable->SpriteYCollision.size(); j++) {
								for (int i = 0; i < LM[y2][x1].size(); i++) {
									if (LM[y2][x1][i] == TempStackable->SpriteYCollision[j]) {
										//calcualte the overlap 
										printf("LL -> Ran into Object%d first\n", TempStackable->SpriteYCollision[j]->OrderCreation + 1);
										LLptr[1] = TempStackable->SpriteYCollision[j];
										LLptr[0] = TempStackable->SpriteXCollision[j];
										EarlyBreak = true;
										break;
									}
								}
								if (EarlyBreak) {
									break;
								}
							}
							EarlyBreak = false;
						}
						else {
							//test all three

							//search both x and y for the first that appears.  both overlap values will be important.
							for (int j = 0; j < TempStackable->SpriteXCollision.size(); j++) {
								for (int i = 0; i < LM[y2][x2].size(); i++) {
									if (LM[y2][x2][i] == TempStackable->SpriteXCollision[j]) {
										//calcualte the overlap 
										printf("LR -> Ran into Object%d first\n", TempStackable->SpriteXCollision[j]->OrderCreation + 1);
										LRptr[0] = TempStackable->SpriteXCollision[j];
										EarlyBreak = true;
										break;
									}
								}
								if (EarlyBreak) {
									break;
								}
							}
							EarlyBreak = false;
							for (int j = 0; j < TempStackable->SpriteYCollision.size(); j++) {
								for (int i = 0; i < LM[y2][x2].size(); i++) {
									if (LM[y2][x2][i] == TempStackable->SpriteYCollision[j]) {
										//calcualte the overlap 
										printf("LR -> Ran into Object%d first\n", TempStackable->SpriteYCollision[j]->OrderCreation + 1);
										LRptr[1] = TempStackable->SpriteYCollision[j];
										EarlyBreak = true;
										break;
									}
								}
								if (EarlyBreak) {
									break;
								}
							}
							EarlyBreak = false;
							//search for the first yc that appears, only the Y overlap will be important
							for (int j = 0; j < TempStackable->SpriteYCollision.size(); j++) {
								for (int i = 0; i < LM[y2][x1].size(); i++) {
									if (LM[y2][x1][i] == TempStackable->SpriteYCollision[j]) {
										//calcualte the overlap 
										printf("LL -> Ran into Object%d first\n", TempStackable->SpriteYCollision[j]->OrderCreation + 1);
										LLptr[1] = TempStackable->SpriteYCollision[j];
										LLptr[0] = TempStackable->SpriteXCollision[j];
										EarlyBreak = true;
										break;
									}
								}
								if (EarlyBreak) {
									break;
								}
							}
							EarlyBreak = false;
							//Serch for first xc taht appears, only hte X overlap will be important. 
							for (int j = 0; j < TempStackable->SpriteXCollision.size(); j++) {
								for (int i = 0; i < LM[y1][x2].size(); i++) {
									if (LM[y1][x2][i] == TempStackable->SpriteXCollision[j]) {
										//calcualte the overlap 
										printf("UR -> Ran into Object%d first\n", TempStackable->SpriteXCollision[j]->OrderCreation + 1);
										URptr[0] = TempStackable->SpriteXCollision[j];
										URptr[1] = TempStackable->SpriteYCollision[j];
										EarlyBreak = true;
										break;
									}
								}
								if (EarlyBreak) {
									break;
								}
							}
							EarlyBreak = false;

						}

					}
					else if (left && down) { //left down

						if (x1 == x2 && y1 == y2) {
							//just the diagonal

							//search both x and y for the first that appears.  both overlap values will be important. 
							for (int j = 0; j < TempStackable->SpriteXCollision.size(); j++) {
								for (int i = 0; i < LM[y2][x1].size(); i++) {
									if (LM[y2][x1][i] == TempStackable->SpriteXCollision[j]) {
										//calcualte the overlap 
										printf("LL -> Ran into Object%d first\n", TempStackable->SpriteXCollision[j]->OrderCreation + 1);
										LLptr[0] = TempStackable->SpriteXCollision[j];
										EarlyBreak = true;
										break;
									}
								}
								if (EarlyBreak) {
									break;
								}
							}
							EarlyBreak = false;
							for (int j = 0; j < TempStackable->SpriteYCollision.size(); j++) {
								for (int i = 0; i < LM[y2][x1].size(); i++) {
									if (LM[y2][x1][i] == TempStackable->SpriteYCollision[j]) {
										//calcualte the overlap 
										printf("LL -> Ran into Object%d first\n", TempStackable->SpriteYCollision[j]->OrderCreation + 1);
										LLptr[1] = TempStackable->SpriteYCollision[j];
										EarlyBreak = true;
										break;
									}
								}
								if (EarlyBreak) {
									break;
								}
							}
							EarlyBreak = false;
						}
						else if (x1 == x2) {
							//just test the y axis edge

							//search both x and y for the first that appears.  both overlap values will be important. 
							for (int j = 0; j < TempStackable->SpriteXCollision.size(); j++) {
								for (int i = 0; i < LM[y2][x1].size(); i++) {
									if (LM[y2][x1][i] == TempStackable->SpriteXCollision[j]) {
										//calcualte the overlap 
										printf("LL -> Ran into Object%d first\n", TempStackable->SpriteXCollision[j]->OrderCreation + 1);
										LLptr[0] = TempStackable->SpriteXCollision[j];
										EarlyBreak = true;
										break;
									}
								}
								if (EarlyBreak) {
									break;
								}
							}
							EarlyBreak = false;
							for (int j = 0; j < TempStackable->SpriteYCollision.size(); j++) {
								for (int i = 0; i < LM[y2][x1].size(); i++) {
									if (LM[y2][x1][i] == TempStackable->SpriteYCollision[j]) {
										//calcualte the overlap 
										printf("LL -> Ran into Object%d first\n", TempStackable->SpriteYCollision[j]->OrderCreation + 1);
										LLptr[1] = TempStackable->SpriteYCollision[j];
										EarlyBreak = true;
										break;
									}
								}
								if (EarlyBreak) {
									break;
								}
							}
							EarlyBreak = false;

							//Serch for first xc taht appears, only hte X overlap will be important.
							for (int j = 0; j < TempStackable->SpriteXCollision.size(); j++) {
								for (int i = 0; i < LM[y1][x1].size(); i++) {
									if (LM[y1][x1][i] == TempStackable->SpriteXCollision[j]) {
										//calcualte the overlap 
										printf("UL -> Ran into Object%d first\n", TempStackable->SpriteXCollision[j]->OrderCreation + 1);
										ULptr[0] = TempStackable->SpriteXCollision[j];
										ULptr[1] = TempStackable->SpriteYCollision[j];
										EarlyBreak = true;
										break;
									}
								}
								if (EarlyBreak) {
									break;
								}
							}
							EarlyBreak = false;
						}
						else if (y1 == y2) {
							//just test the x axis edge

							//search both x and y for the first that appears.  both overlap values will be important. 
							for (int j = 0; j < TempStackable->SpriteXCollision.size(); j++) {
								for (int i = 0; i < LM[y2][x1].size(); i++) {
									if (LM[y2][x1][i] == TempStackable->SpriteXCollision[j]) {
										//calcualte the overlap 
										printf("LL -> Ran into Object%d first\n", TempStackable->SpriteXCollision[j]->OrderCreation + 1);
										LLptr[0] = TempStackable->SpriteXCollision[j];
										EarlyBreak = true;
										break;
									}
								}
								if (EarlyBreak) {
									break;
								}
							}
							EarlyBreak = false;
							for (int j = 0; j < TempStackable->SpriteYCollision.size(); j++) {
								for (int i = 0; i < LM[y2][x1].size(); i++) {
									if (LM[y2][x1][i] == TempStackable->SpriteYCollision[j]) {
										//calcualte the overlap 
										printf("LL -> Ran into Object%d first\n", TempStackable->SpriteYCollision[j]->OrderCreation + 1);
										LLptr[1] = TempStackable->SpriteYCollision[j];
										EarlyBreak = true;
										break;
									}
								}
								if (EarlyBreak) {
									break;
								}
							}
							EarlyBreak = false;
							//search for the first yc that appears, only the Y overlap will be important
							for (int j = 0; j < TempStackable->SpriteYCollision.size(); j++) {
								for (int i = 0; i < LM[y2][x2].size(); i++) {
									if (LM[y2][x2][i] == TempStackable->SpriteYCollision[j]) {
										//calcualte the overlap 
										printf("LR -> Ran into Object%d first\n", TempStackable->SpriteYCollision[j]->OrderCreation + 1);
										LRptr[1] = TempStackable->SpriteYCollision[j];
										LRptr[0] = TempStackable->SpriteXCollision[j];
										EarlyBreak = true;
										break;
									}
								}
								if (EarlyBreak) {
									break;
								}
							}
							EarlyBreak = false;
						}
						else {
							//test all three

							//search both x and y for the first that appears.  both overlap values will be important. 
							for (int j = 0; j < TempStackable->SpriteXCollision.size(); j++) {
								for (int i = 0; i < LM[y2][x1].size(); i++) {
									if (LM[y2][x1][i] == TempStackable->SpriteXCollision[j]) {
										//calcualte the overlap 
										printf("LL -> Ran into Object%d first\n", TempStackable->SpriteXCollision[j]->OrderCreation + 1);
										LLptr[0] = TempStackable->SpriteXCollision[j];
										EarlyBreak = true;
										break;
									}
								}
								if (EarlyBreak) {
									break;
								}
							}
							EarlyBreak = false;
							for (int j = 0; j < TempStackable->SpriteYCollision.size(); j++) {
								for (int i = 0; i < LM[y2][x1].size(); i++) {
									if (LM[y2][x1][i] == TempStackable->SpriteYCollision[j]) {
										//calcualte the overlap 
										printf("LL -> Ran into Object%d first\n", TempStackable->SpriteYCollision[j]->OrderCreation + 1);
										LLptr[1] = TempStackable->SpriteYCollision[j];
										EarlyBreak = true;
										break;
									}
								}
								if (EarlyBreak) {
									break;
								}
							}
							EarlyBreak = false;
							//Serch for first xc taht appears, only hte X overlap will be important.
							for (int j = 0; j < TempStackable->SpriteXCollision.size(); j++) {
								for (int i = 0; i < LM[y1][x1].size(); i++) {
									if (LM[y1][x1][i] == TempStackable->SpriteXCollision[j]) {
										//calcualte the overlap 
										printf("UL -> Ran into Object%d first\n", TempStackable->SpriteXCollision[j]->OrderCreation + 1);
										ULptr[0] = TempStackable->SpriteXCollision[j];
										ULptr[1] = TempStackable->SpriteYCollision[j];
										EarlyBreak = true;
										break;
									}
								}
								if (EarlyBreak) {
									break;
								}
							}
							EarlyBreak = false;
							//search for the first yc that appears, only the Y overlap will be important
							for (int j = 0; j < TempStackable->SpriteYCollision.size(); j++) {
								for (int i = 0; i < LM[y2][x2].size(); i++) {
									if (LM[y2][x2][i] == TempStackable->SpriteYCollision[j]) {
										//calcualte the overlap 
										printf("LR -> Ran into Object%d first\n", TempStackable->SpriteYCollision[j]->OrderCreation + 1);
										LRptr[1] = TempStackable->SpriteYCollision[j];
										LRptr[0] = TempStackable->SpriteXCollision[j];
										EarlyBreak = true;
										break;
									}
								}
								if (EarlyBreak) {
									break;
								}
							}
							EarlyBreak = false;
						}

					}
					else if (right && up) { //right up 

						if (x1 == x2 && y1 == y2) {
							//just the diagonal

							//search both x and y for the first that appears.  both overlap values will be important. 
							for (int j = 0; j < TempStackable->SpriteXCollision.size(); j++) {
								for (int i = 0; i < LM[y1][x2].size(); i++) {
									if (LM[y1][x2][i] == TempStackable->SpriteXCollision[j]) {
										//calcualte the overlap 
										printf("UR -> Ran into Object%d first\n", TempStackable->SpriteXCollision[j]->OrderCreation + 1);
										URptr[0] = TempStackable->SpriteXCollision[j];
										EarlyBreak = true;
										break;
									}
								}
								if (EarlyBreak) {
									break;
								}
							}
							EarlyBreak = false;
							for (int j = 0; j < TempStackable->SpriteYCollision.size(); j++) {
								for (int i = 0; i < LM[y1][x2].size(); i++) {
									if (LM[y1][x2][i] == TempStackable->SpriteYCollision[j]) {
										//calcualte the overlap 
										printf("UR -> Ran into Object%d first\n", TempStackable->SpriteYCollision[j]->OrderCreation + 1);
										URptr[1] = TempStackable->SpriteYCollision[j];
										EarlyBreak = true;
										break;
									}
								}
								if (EarlyBreak) {
									break;
								}
							}
							EarlyBreak = false;
						}
						else if (x1 == x2) {
							//just test the y axis edge

							//search both x and y for the first that appears.  both overlap values will be important. 
							for (int j = 0; j < TempStackable->SpriteXCollision.size(); j++) {
								for (int i = 0; i < LM[y1][x2].size(); i++) {
									if (LM[y1][x2][i] == TempStackable->SpriteXCollision[j]) {
										//calcualte the overlap 
										printf("UR -> Ran into Object%d first\n", TempStackable->SpriteXCollision[j]->OrderCreation + 1);
										URptr[0] = TempStackable->SpriteXCollision[j];
										EarlyBreak = true;
										break;
									}
								}
								if (EarlyBreak) {
									break;
								}
							}
							EarlyBreak = false;
							for (int j = 0; j < TempStackable->SpriteYCollision.size(); j++) {
								for (int i = 0; i < LM[y1][x2].size(); i++) {
									if (LM[y1][x2][i] == TempStackable->SpriteYCollision[j]) {
										//calcualte the overlap 
										printf("UR -> Ran into Object%d first\n", TempStackable->SpriteYCollision[j]->OrderCreation + 1);
										URptr[1] = TempStackable->SpriteYCollision[j];
										EarlyBreak = true;
										break;
									}
								}
								if (EarlyBreak) {
									break;
								}
							}
							EarlyBreak = false;

							//Serch for first xc taht appears, only hte X overlap will be important.
							for (int j = 0; j < TempStackable->SpriteXCollision.size(); j++) {
								for (int i = 0; i < LM[y2][x2].size(); i++) {
									if (LM[y2][x2][i] == TempStackable->SpriteXCollision[j]) {
										//calcualte the overlap 
										printf("LR -> Ran into Object%d first\n", TempStackable->SpriteXCollision[j]->OrderCreation + 1);
										LRptr[0] = TempStackable->SpriteXCollision[j];
										LRptr[1] = TempStackable->SpriteYCollision[j];
										EarlyBreak = true;
										break;
									}
								}
								if (EarlyBreak) {
									break;
								}
							}
							EarlyBreak = false;
						}
						else if (y1 == y2) {
							//just test the x axis edge

							//search both x and y for the first that appears.  both overlap values will be important. 
							for (int j = 0; j < TempStackable->SpriteXCollision.size(); j++) {
								for (int i = 0; i < LM[y1][x2].size(); i++) {
									if (LM[y1][x2][i] == TempStackable->SpriteXCollision[j]) {
										//calcualte the overlap 
										printf("UR -> Ran into Object%d first\n", TempStackable->SpriteXCollision[j]->OrderCreation + 1);
										URptr[0] = TempStackable->SpriteXCollision[j];
										EarlyBreak = true;
										break;
									}
								}
								if (EarlyBreak) {
									break;
								}
							}
							EarlyBreak = false;
							for (int j = 0; j < TempStackable->SpriteYCollision.size(); j++) {
								for (int i = 0; i < LM[y1][x2].size(); i++) {
									if (LM[y1][x2][i] == TempStackable->SpriteYCollision[j]) {
										//calcualte the overlap 
										printf("UR -> Ran into Object%d first\n", TempStackable->SpriteYCollision[j]->OrderCreation + 1);
										URptr[1] = TempStackable->SpriteYCollision[j];
										EarlyBreak = true;
										break;
									}
								}
								if (EarlyBreak) {
									break;
								}
							}
							EarlyBreak = false;

							//search for the first yc that appears, only the Y overlap will be important
							for (int j = 0; j < TempStackable->SpriteYCollision.size(); j++) {
								for (int i = 0; i < LM[y1][x1].size(); i++) {
									if (LM[y1][x1][i] == TempStackable->SpriteYCollision[j]) {
										//calcualte the overlap 
										printf("UL -> Ran into Object%d first\n", TempStackable->SpriteYCollision[j]->OrderCreation + 1);
										ULptr[1] = TempStackable->SpriteYCollision[j];
										ULptr[0] = TempStackable->SpriteXCollision[j];
										EarlyBreak = true;
										break;
									}
								}
								if (EarlyBreak) {
									break;
								}
							}
							EarlyBreak = false;
						}
						else {
							//test all three

							//search both x and y for the first that appears.  both overlap values will be important. 
							for (int j = 0; j < TempStackable->SpriteXCollision.size(); j++) {
								for (int i = 0; i < LM[y1][x2].size(); i++) {
									if (LM[y1][x2][i] == TempStackable->SpriteXCollision[j]) {
										//calcualte the overlap 
										printf("UR -> Ran into Object%d first\n", TempStackable->SpriteXCollision[j]->OrderCreation + 1);
										URptr[0] = TempStackable->SpriteXCollision[j];
										EarlyBreak = true;
										break;
									}
								}
								if (EarlyBreak) {
									break;
								}
							}
							EarlyBreak = false;
							for (int j = 0; j < TempStackable->SpriteYCollision.size(); j++) {
								for (int i = 0; i < LM[y1][x2].size(); i++) {
									if (LM[y1][x2][i] == TempStackable->SpriteYCollision[j]) {
										//calcualte the overlap 
										printf("UR -> Ran into Object%d first\n", TempStackable->SpriteYCollision[j]->OrderCreation + 1);
										URptr[1] = TempStackable->SpriteYCollision[j];
										EarlyBreak = true;
										break;
									}
								}
								if (EarlyBreak) {
									break;
								}
							}
							EarlyBreak = false;

							//search for the first yc that appears, only the Y overlap will be important
							for (int j = 0; j < TempStackable->SpriteYCollision.size(); j++) {
								for (int i = 0; i < LM[y1][x1].size(); i++) {
									if (LM[y1][x1][i] == TempStackable->SpriteYCollision[j]) {
										//calcualte the overlap 
										printf("UL -> Ran into Object%d first\n", TempStackable->SpriteYCollision[j]->OrderCreation + 1);
										ULptr[1] = TempStackable->SpriteYCollision[j];
										ULptr[0] = TempStackable->SpriteXCollision[j];
										EarlyBreak = true;
										break;
									}
								}
								if (EarlyBreak) {
									break;
								}
							}
							EarlyBreak = false;

							//Serch for first xc taht appears, only hte X overlap will be important.
							for (int j = 0; j < TempStackable->SpriteXCollision.size(); j++) {
								for (int i = 0; i < LM[y2][x2].size(); i++) {
									if (LM[y2][x2][i] == TempStackable->SpriteXCollision[j]) {
										//calcualte the overlap 
										printf("LR -> Ran into Object%d first\n", TempStackable->SpriteXCollision[j]->OrderCreation + 1);
										LRptr[0] = TempStackable->SpriteXCollision[j];
										LRptr[1] = TempStackable->SpriteYCollision[j];
										EarlyBreak = true;
										break;
									}
								}
								if (EarlyBreak) {
									break;
								}
							}
							EarlyBreak = false;
						}

					}


					//FIX put the early break in the other for loop.

					//SDL_Delay(5000);

					//pause printf("2) Moving Diagonally\n"); SDL_Delay(2000);
					//Awesome, now figure out the overlap on the two directional sprites. (so not the sprite hit by your directions corner, but the edges)
					if (left && up) {
						//figure out overlap on x and y
						//LL = x, UR = y
						FigureOverlap(CurrentVictim, LLptr, URptr, LL, UR, wait);
						if (LL[0] != 0) {
							AdjustedX = true;
						}
						if (UR[1] != 0) {
							AdjustedY = true;
						}

					}
					else if (right && down) {
						//figure out overlap on x and y
						//UR = x, LL = y
						FigureOverlap(CurrentVictim, URptr, LLptr, UR, LL, wait);
						if (UR[0] != 0) {
							AdjustedX = true;
						}
						if (LL[1] != 0) {
							AdjustedY = true;
						}
					}
					else if (left && down) {
						//figure out overlap on x and y
						//UL = x, LR = y 
						FigureOverlap(CurrentVictim, ULptr, LRptr, UL, LR, wait);
						if (UL[0] != 0) {
							AdjustedX = true;
						}
						if (LR[1] != 0) {
							AdjustedY = true;
						}
					}
					else if (right && up) {
						//figure out overlap on x and y
						//LR = x, UL = y
						FigureOverlap(CurrentVictim, LRptr, ULptr, LR, UL, wait);
						if (LR[0] != 0) {
							AdjustedX = true;
						}
						if (UL[1] != 0) {
							AdjustedY = true;
						}
					}

					//Great, now lets see if we got them edited back in hte original array.
					printf("UL = {%d, %d}\n", UL[0], UL[1]);
					printf("UR = {%d, %d}\n", UR[0], UR[1]);
					printf("LL = {%d, %d}\n", LL[0], LL[1]);
					printf("LR = {%d, %d}\n", LR[0], LR[1]);
					//SDL_Delay(500);



					//Now I'd like you to teleport based solely on the two directionals we got. 
					int XC;
					int YC;
					if (left && up) {
						XC = LL[0];
						YC = UR[1];
					}
					else if (right && down) {
						XC = UR[0];
						YC = LL[1];
					}
					else if (left && down) {
						XC = UL[0];
						YC = LR[1];
					}
					else if (right && up) {
						XC = LR[0];
						YC = UL[1];
					}
					//if directional, undo just the direction you came from
					if (xChange > 0) { //right
						CurrentVictim->TeleportX(CurrentVictim->xPos - XC);
					}
					else { //left
						CurrentVictim->TeleportX(CurrentVictim->xPos + XC);
					}
					if (yChange > 0) { //down
						CurrentVictim->TeleportY(CurrentVictim->yPos - YC);
					}
					else { //up
						CurrentVictim->TeleportY(CurrentVictim->yPos + YC);
					}

					//NOTE - try to make the teleport a seperate function to reduce repetitiveness.
					//NOW calculate if theres any overlap on the diagonal
						//If even, teleport equal to both axis
						//If X>Y, teleport only on the y axis (because you wish to maintain the X slide)
						//if Y>X, teleport only on the x axis (because you wish to maintain the Y slide)
					if (left && up) {
						FigureOverlap(CurrentVictim, ULptr, ULptr, UL, UL, wait);
						if (UL[0] < UL[1]) { //X>Y
							XC = UL[0];
							if (xChange > 0) { //right
								CurrentVictim->TeleportX(CurrentVictim->xPos - XC);
							}
							else { //left
								CurrentVictim->TeleportX(CurrentVictim->xPos + XC);
							}
						}
						else if (UL[1] < UL[0]) { //Y>X
							YC = UL[1];
							if (yChange > 0) { //down
								CurrentVictim->TeleportY(CurrentVictim->yPos - YC);
							}
							else { //up
								CurrentVictim->TeleportY(CurrentVictim->yPos + YC);
							}
						}
						else { //Y=X
							XC = UL[0];
							YC = UL[1];
							if ((AdjustedX && AdjustedY) || (!AdjustedX && !AdjustedY)) {
								if (xChange > 0) { //right
									CurrentVictim->TeleportX(CurrentVictim->xPos - XC);
								}
								else { //left
									CurrentVictim->TeleportX(CurrentVictim->xPos + XC);
								}
								if (yChange > 0) { //down
									CurrentVictim->TeleportY(CurrentVictim->yPos - YC);
								}
								else { //up
									CurrentVictim->TeleportY(CurrentVictim->yPos + YC);
								}
							}
							else if (AdjustedX) {
								if (yChange > 0) { //down
									CurrentVictim->TeleportY(CurrentVictim->yPos - YC);
								}
								else { //up
									CurrentVictim->TeleportY(CurrentVictim->yPos + YC);
								}
							}
							else if (AdjustedY) {
								if (xChange > 0) { //right
									CurrentVictim->TeleportX(CurrentVictim->xPos - XC);
								}
								else { //left
									CurrentVictim->TeleportX(CurrentVictim->xPos + XC);
								}
							}

						}
					}
					else if (right && down) {
						FigureOverlap(CurrentVictim, LRptr, LRptr, LR, LR, wait);

						if (LR[0] == 0 || LR[1] == 0) { //new, attempt to fix sliding. This is because the diagonal even though the overlap became 0 on one of the axis', it didn't slide because one or the other wasn't 0.
							printf("NEW : Try to just ignore the overlap since one of the two is 0.\n");
							CurrentVictim->TeleportX(CurrentVictim->xPos);
							CurrentVictim->TeleportY(CurrentVictim->yPos);
						}
						else if (LR[0] < LR[1]) { //X>Y
							printf("X<Y\n");
							XC = LR[0];
							if (xChange > 0) { //right
								CurrentVictim->TeleportX(CurrentVictim->xPos - XC);
							}
							else { //left
								CurrentVictim->TeleportX(CurrentVictim->xPos + XC);
							}
						}
						else if (LR[1] < LR[0]) { //Y>X
							printf("Y<X\n");
							YC = LR[1];
							if (yChange > 0) { //down
								CurrentVictim->TeleportY(CurrentVictim->yPos - YC);
							}
							else { //up
								CurrentVictim->TeleportY(CurrentVictim->yPos + YC);
							}
						}
						else { //Y=X 
							XC = LR[0];
							YC = LR[1];
							if ((AdjustedX && AdjustedY) || (!AdjustedX && !AdjustedY)) {
								if (xChange > 0) { //right
									CurrentVictim->TeleportX(CurrentVictim->xPos - XC);
								}
								else { //left
									CurrentVictim->TeleportX(CurrentVictim->xPos + XC);
								}
								if (yChange > 0) { //down
									CurrentVictim->TeleportY(CurrentVictim->yPos - YC);
								}
								else { //up
									CurrentVictim->TeleportY(CurrentVictim->yPos + YC);
								}
							}
							else if (AdjustedX) {
								if (yChange > 0) { //down
									CurrentVictim->TeleportY(CurrentVictim->yPos - YC);
								}
								else { //up
									CurrentVictim->TeleportY(CurrentVictim->yPos + YC);
								}
							}
							else if (AdjustedY) {
								if (xChange > 0) { //right
									CurrentVictim->TeleportX(CurrentVictim->xPos - XC);
								}
								else { //left
									CurrentVictim->TeleportX(CurrentVictim->xPos + XC);
								}
							}
						}



					}
					else if (left && down) {
						FigureOverlap(CurrentVictim, LLptr, LLptr, LL, LL, wait);
						if (LL[0] < LL[1]) { //X>Y
							XC = LL[0];
							if (XC == 16) {
								XC = 0;
							}
							if (xChange > 0) { //right
								CurrentVictim->TeleportX(CurrentVictim->xPos - XC);
							}
							else { //left
								CurrentVictim->TeleportX(CurrentVictim->xPos + XC);
							}
						}
						else if (LL[1] < LL[0]) { //Y>X
							printf("TELEPORT DIAGONAL Y\n");
							YC = LL[1];
							if (YC == 16) { //didn't work :/
								YC = 0;
							}
							if (yChange > 0) { //down
								CurrentVictim->TeleportY(CurrentVictim->yPos - YC);
							}
							else { //up
								CurrentVictim->TeleportY(CurrentVictim->yPos + YC);
							}
						}
						else { //Y=X
							XC = LL[0];
							YC = LL[1];
							if ((AdjustedX && AdjustedY) || (!AdjustedX && !AdjustedY)) {
								if (xChange > 0) { //right
									CurrentVictim->TeleportX(CurrentVictim->xPos - XC);
								}
								else { //left
									CurrentVictim->TeleportX(CurrentVictim->xPos + XC);
								}
								if (yChange > 0) { //down
									CurrentVictim->TeleportY(CurrentVictim->yPos - YC);
								}
								else { //up
									CurrentVictim->TeleportY(CurrentVictim->yPos + YC);
								}
							}
							else if (AdjustedX) {
								if (yChange > 0) { //down
									CurrentVictim->TeleportY(CurrentVictim->yPos - YC);
								}
								else { //up
									CurrentVictim->TeleportY(CurrentVictim->yPos + YC);
								}
							}
							else if (AdjustedY) {
								if (xChange > 0) { //right
									CurrentVictim->TeleportX(CurrentVictim->xPos - XC);
								}
								else { //left
									CurrentVictim->TeleportX(CurrentVictim->xPos + XC);
								}
							}
						}
					}
					else if (right && up) {
						FigureOverlap(CurrentVictim, URptr, URptr, UR, UR, wait);
						if (UR[0] < UR[1]) { //X>Y
							XC = UR[0];
							if (xChange > 0) { //right
								CurrentVictim->TeleportX(CurrentVictim->xPos - XC);
							}
							else { //left
								CurrentVictim->TeleportX(CurrentVictim->xPos + XC);
							}
						}
						else if (UR[1] < UR[0]) { //Y>X
							YC = UR[1];
							if (yChange > 0) { //down
								CurrentVictim->TeleportY(CurrentVictim->yPos - YC);
							}
							else { //up
								CurrentVictim->TeleportY(CurrentVictim->yPos + YC);
							}
						}
						else { //Y=X
							XC = UR[0];
							YC = UR[1];
							if ((AdjustedX && AdjustedY) || (!AdjustedX && !AdjustedY)) {
								if (xChange > 0) { //right
									CurrentVictim->TeleportX(CurrentVictim->xPos - XC);
								}
								else { //left
									CurrentVictim->TeleportX(CurrentVictim->xPos + XC);
								}
								if (yChange > 0) { //down
									CurrentVictim->TeleportY(CurrentVictim->yPos - YC);
								}
								else { //up
									CurrentVictim->TeleportY(CurrentVictim->yPos + YC);
								}
							}
							else if (AdjustedX) {
								if (yChange > 0) { //down
									CurrentVictim->TeleportY(CurrentVictim->yPos - YC);
								}
								else { //up
									CurrentVictim->TeleportY(CurrentVictim->yPos + YC);
								}
							}
							else if (AdjustedY) {
								if (xChange > 0) { //right
									CurrentVictim->TeleportX(CurrentVictim->xPos - XC);
								}
								else { //left
									CurrentVictim->TeleportX(CurrentVictim->xPos + XC);
								}
							}
						}
					}
					//CHANGE - flip the less than, and swap between the two the insides of each if else.


					printf("Time to pause\n");
					//SDL_Delay(500);


					//Now, if this works, there should be no jumping, no overlap, and most importantly, no stopping when sliding.
					//okay so the overlap = 0 when it should be 16 is a problem... so I'll make it able to be 16, BUT if thats an issue, I'll check for if it's 0 in the statements above.




				}






				//pause printf("3) Moving Diagonally\n"); SDL_Delay(2000);




			}


			else if (x > 0) {
				int XC;
				if (xChange > 0) { // if moving right
					printf("Sprite was moving Right\n");

					XC = CurrentVictim->xPos + TILE_WIDTH - TempStackable->SpriteXCollision[x - 1]->xPos; //object 4={64, 0}, obj5 ={79, 0}. 64+16-79=1, so 79+1 is where obj 5 would be without overlap.
					printf("5 TempOverlapX=%d\n", XC);
					pause = true;

				}
				else { // if moving left
					printf("Sprite was moving Left\n");

					XC = TempStackable->SpriteXCollision[x - 1]->xPos + TILE_WIDTH - CurrentVictim->xPos; //insert virtually the same check used for checkfuture 2, to ensure consistency among objects that move morethan 1 pxl at a time.
					printf("6 TempOverlapX=%d\n", XC);
					pause = true;

				}

				if (xChange > 0) { //right
					CurrentVictim->TeleportX(CurrentVictim->xPos - XC);
				}
				else {//left
					CurrentVictim->TeleportX(CurrentVictim->xPos + XC);
				}

				if (XC > 16 || XC < 0) {
					printf("We've got a problem sir!\n");
					wait = true;
				}
			} //don't have ot worry about diag considerations, where inline map could be a problem.


			else if (y > 0) {
				int YC;
				if (yChange > 0) { // if moving down
					printf("Sprite was moving down\n");

					YC = CurrentVictim->yPos + TILE_WIDTH - TempStackable->SpriteYCollision[y - 1]->yPos; //insert virtually the same check used for checkfuture 2, to ensure consistency among objects that move morethan 1 pxl at a time.
					printf("7 TempOverlapY=%d\n", YC);
					pause = true;

				}
				else { // if moving up
					printf("Sprite was moving up\n");
					YC = TempStackable->SpriteYCollision[y - 1]->yPos + TILE_HEIGHT - CurrentVictim->yPos; //insert virtually the same check used for checkfuture 2, to ensure consistency among objects that move morethan 1 pxl at a time.
					printf("8 TempOverlapY=%d\n", YC);
					pause = true;

				}

				if (yChange > 0) { //down
					CurrentVictim->TeleportY(CurrentVictim->yPos - YC);
				}
				else {//up
					CurrentVictim->TeleportY(CurrentVictim->yPos + YC);
				}

				if (YC > 16 || YC < 0) {
					printf("We've got a problem sir!\n");
					wait = true;
				}
			}

			if (wait) {
				//SDL_Delay(10000);
				wait = false;
			}




			if (Debug) {
				printf("Teleport Complete!\n");
			}
			ReMapSprite(CurrentVictim); //quesiton, if I have two objects taht odn't oved on top of one another, this collision shoudl go off, and the undo, does that just keep it in the same space, no matter what? I feel like kif it doesn't move I shouldn't even allow it to enter the que in the first place... questions for later, might be less worth while the less object collision stacks that are possible. I should make some ratio of level to sprites to control how 'involved' the stack process is. for now lets go as deep as possible with the computation aspect, and trim down for other cases where the user doesn't care for such exact detections.
			if (Debug) {
				printf("Remap Object%d [Current Victim]\n", CurrentVictim->OrderCreation + 1);
			}
			//no need ot pop from SpriteStacks
			//no need to insert to spritestacks
			CompletedSprites[CurrentVictim->OrderCreation] = 1; //it's completed, won't move anymore. This way when we try to move the victims at the end of que2 to appropriate spaces, if they would collide with obj1 then that's what they'll do

		}
		else { //it moved! 
			if (Debug) {
				printf("It moved! Now to recheck the stack!\n");
			}
			//move target tile
			CurrentVictim->MoveTargetTileX();
			CurrentVictim->MoveTargetTileY();
			//remap it, 
			ReMapSprite(CurrentVictim);
			CompletedSprites[CurrentVictim->OrderCreation] = 1;
			if (Debug) {
				printf("Successfully moved Object%d, marked as completed and remapped it.\n", CurrentVictim->OrderCreation + 1);
			}


			//Code below these comments are what was done in antoher function, so perhaps export it to a seperate function all together?
			//search all stacks for this item, and pop it 
			//mark down which edited
			//investigate
			//get new victims

			bool AlreadyPushedIndex = false; //NEW <- to avoid pushing back tons of indexX when we only looked at it once and all we needed to know.
			std::vector<int> InvestigateIndexsX = {};
			std::vector<int> InvestigateIndexsY = {};
			//search for the compelted sprite in the stack -this function needs to be improved to work up a stack, not just across all stacks.
			for (int d = 0; d < SpriteStacks.size(); d++) {
				//NOTE NOTE NOTE NOTE THIS NEEDS TO WORK UP A QUE SO LONG AS I>POPPED CREATIONORDER && COMPLETEDSPRITES[ORDERCREATION]==1, SO WE'VE FOUND THE START OF IT, NOW MAKE A WHILE THAT GOES 'UP' THE STACK

				if (SpriteStacks[d]->SpriteXCollision.size() > 0) { //if there are still things your colliding with on X, AND The SpriteMoved pointer MATCHES the pointer at the end of that stack!
					//we may just need the while statement

					if (Debug) {
						printf("Check SpriteXCollsion for dobules, there should be none if properly pruned\n");
						printf("SpriteXCollsion = {");
						for (int j = 0; j < SpriteStacks[d]->SpriteXCollision.size(); j++) {
							printf("%d, ", SpriteStacks[d]->SpriteXCollision[j]->OrderCreation);
						}
						printf("}\n");
					}

					while (SpriteStacks[d]->SpriteXCollision.size() > 0 && CompletedSprites[SpriteStacks[d]->SpriteXCollision[SpriteStacks[d]->SpriteXCollision.size() - 1]->OrderCreation] == 1) { //while there are things left to pop AND they have already successfully moved - will break when either your out of things to pop, or those items are ahead of the original Sprite you popped.
						SpriteStacks[d]->SpriteXCollision.pop_back();
						if (!AlreadyPushedIndex) { //NEW

							InvestigateIndexsX.push_back(d); //do this after the while we insert.
							AlreadyPushedIndex = true;
						}
					}
				}
				AlreadyPushedIndex = false;
				if (SpriteStacks[d]->SpriteYCollision.size() > 0) {
					while (SpriteStacks[d]->SpriteYCollision.size() > 0 && CompletedSprites[SpriteStacks[d]->SpriteYCollision[SpriteStacks[d]->SpriteYCollision.size() - 1]->OrderCreation] == 1) {
						SpriteStacks[d]->SpriteYCollision.pop_back();
						if (!AlreadyPushedIndex) { //NEW

							InvestigateIndexsY.push_back(d);
							AlreadyPushedIndex = true;
						}
					}
				}
				AlreadyPushedIndex = false;
			}

			if (Debug) {
				printf("PAY ATTENTION - MAKE SURE THERE ARE NO DOUBLES INSIDE EACH\n");
				printf("InvestigateIndexsX ={");
				for (int j = 0; j < InvestigateIndexsX.size(); j++) {
					printf("%d, ", InvestigateIndexsX[j]);
				}
				printf("}\n");
				printf("InvestigateIndexsY ={");
				for (int j = 0; j < InvestigateIndexsY.size(); j++) {
					printf("%d, ", InvestigateIndexsY[j]);
				}
				printf("}\n");
			}

			//^From the main loop
			//now every stack should be popped as much as it could be. Then we must find the eraseable elements again. NOTE I SHOULD ERASE IT FROM THE STACK WHEN WE FIRST ADD IT
			//THEN SORT IT INTO VICTIMSPRITES


			std::vector<int> EraseableX = {};
			std::vector<int> EraseableY = {};

			//Then the victim finding from HAndleCollision2 V
			//Step 1) Figure out which ones to pop next if any. MAINLY: take the edited vectors, if both X and that Y are empty at the end of popping, attempt to move the victim,
			for (int i = 0; i < InvestigateIndexsX.size(); i++) {
				if (SpriteStacks[InvestigateIndexsX[i]]->SpriteXCollision.size() < 1 && SpriteStacks[InvestigateIndexsX[i]]->SpriteYCollision.size() < 1) {
					EraseableX.push_back(InvestigateIndexsX[i]); //we're going to erase backwards, so the larger index of x and Y
				}
			}
			for (int i = 0; i < InvestigateIndexsY.size(); i++) {
				if (SpriteStacks[InvestigateIndexsY[i]]->SpriteYCollision.size() < 1 && SpriteStacks[InvestigateIndexsY[i]]->SpriteXCollision.size() < 1) {
					EraseableY.push_back(InvestigateIndexsY[i]); //we're going to erase backwards, so the larger index of x and Y
				}
			}
			//now we have all the erasables. Use binary search to insert into the VictimSprites


			//step 2, investigate those popped, see if any victims are left fully-alone
			if (Debug) {

				printf("Start Erasing [HandleVictims]\n");
			}

			if (Debug) {
				printf("EraseableX = {");
				for (int j = 0; j < EraseableX.size(); j++) {
					printf("%d, ", EraseableX[j]);
				}
				printf("}\n");

				printf("EraseableY = {");
				for (int j = 0; j < EraseableY.size(); j++) {
					printf("%d, ", EraseableY[j]);
				}
				printf("}\n");
			}


			//BREAKS SOMEWHERE BELOW HERE! 
			int Total = EraseableX.size() + EraseableY.size() - 1;
			if (Debug) {

				printf("Total = %d\n", Total);
			}
			std::vector<Sprite*> VictimsNoLonger = {};
			for (int i = Total; i > -1; i--) {
				//if one of the sizes is empty, but the other is full
				if (EraseableX.size() > 0 && EraseableY.size() > 0) {
					if (EraseableX[EraseableX.size() - 1] > EraseableY[EraseableY.size() - 1]) {

						VictimsNoLonger.push_back(SpriteStacks[EraseableX[EraseableX.size() - 1]]->Victim);
						SpriteStacks.erase(SpriteStacks.begin() + EraseableX[EraseableX.size() - 1]);
						EraseableX.pop_back();
						if (Debug) {
							printf("EraseableX = {");
							for (int j = 0; j < EraseableX.size(); j++) {
								printf("%d, ", EraseableX[j]);
							}
							printf("}\n");

							printf("EraseableY = {");
							for (int j = 0; j < EraseableY.size(); j++) {
								printf("%d, ", EraseableY[j]);
							}
							printf("}\n");
						}
					}
					else if (EraseableY[EraseableY.size() - 1] > EraseableX[EraseableX.size() - 1]) {
						VictimsNoLonger.push_back(SpriteStacks[EraseableY[EraseableY.size() - 1]]->Victim);
						SpriteStacks.erase(SpriteStacks.begin() + EraseableY[EraseableY.size() - 1]);
						EraseableY.pop_back();
						if (Debug) {
							printf("EraseableX = {");
							for (int j = 0; j < EraseableX.size(); j++) {
								printf("%d, ", EraseableX[j]);
							}
							printf("}\n");

							printf("EraseableY = {");
							for (int j = 0; j < EraseableY.size(); j++) {
								printf("%d, ", EraseableY[j]);
							}
							printf("}\n");
						}
					}
					else if (EraseableY[EraseableY.size() - 1] == EraseableX[EraseableX.size() - 1]) {
						VictimsNoLonger.push_back(SpriteStacks[EraseableX[EraseableX.size() - 1]]->Victim);
						SpriteStacks.erase(SpriteStacks.begin() + EraseableX[EraseableX.size() - 1]);
						EraseableX.pop_back();
						EraseableY.pop_back();
						i--;//popped twice, so go down an extra step in he loop.
						if (Debug) {
							printf("EraseableX = {");
							for (int j = 0; j < EraseableX.size(); j++) {
								printf("%d, ", EraseableX[j]);
							}
							printf("}\n");

							printf("EraseableY = {");
							for (int j = 0; j < EraseableY.size(); j++) {
								printf("%d, ", EraseableY[j]);
							}
							printf("}\n");
						}
					}
				}
				else if (EraseableX.size() > 0) {
					VictimsNoLonger.push_back(SpriteStacks[EraseableX[EraseableX.size() - 1]]->Victim);
					SpriteStacks.erase(SpriteStacks.begin() + EraseableX[EraseableX.size() - 1]);
					EraseableX.pop_back();
					if (Debug) {
						printf("EraseableX = {");
						for (int j = 0; j < EraseableX.size(); j++) {
							printf("%d, ", EraseableX[j]);
						}
						printf("}\n");

						printf("EraseableY = {");
						for (int j = 0; j < EraseableY.size(); j++) {
							printf("%d, ", EraseableY[j]);
						}
						printf("}\n");
					}
				}
				else if (EraseableY.size() > 0) { //this should be a definite, but just for now
					VictimsNoLonger.push_back(SpriteStacks[EraseableY[EraseableY.size() - 1]]->Victim);
					SpriteStacks.erase(SpriteStacks.begin() + EraseableY[EraseableY.size() - 1]);
					EraseableY.pop_back();
					if (Debug) {
						printf("EraseableX = {");
						for (int j = 0; j < EraseableX.size(); j++) {
							printf("%d, ", EraseableX[j]);
						}
						printf("}\n");

						printf("EraseableY = {");
						for (int j = 0; j < EraseableY.size(); j++) {
							printf("%d, ", EraseableY[j]);
						}
						printf("}\n");
					}
				}
				//note on how this operation works.
				//EraseableX = {0, 5, 9, 12}, where these numbers are the index's on SpriteStacks that we last popped from, organized from least to greatest, Y is same.
				// Eraseable, also are those who's XYArr has empty X,Y collisions (as in those have been moved at some point).
				//Then we don't want to accidently shift hte indexs, sowe approach from the back of the SpriteStacks while checking if we can erase. We ensure we don't erase any out of order through the first three if statements
				//The next two last are just to get rid of remaining.
				//Now we don't have doubles of indexs to erase. - we needed both of them, because it might've alerady had an empty X or Y by the time we popped the sprite.
				//Finally we store these indexes into VictimsNoLonger. we will, one by one, from youngest to oldest (so starting at the end of VictimsNoLonger)
					//see if we can move it. If checkfuture finds ANY collosion overlap, then do the proper undo's and flag it for collision.
				//don't flag for overlap, since that happens after everythings been moved properly.

			}


			if (Debug) {
				printf("Now show off which new victims to test/insert\n"); //so edit htevictims no longer so it goes once for the youngest, and then checks the indexs edited, and inserts properly new victims that are checkable. That way we can just run until victimsnolonger runs out.
				printf("New Victims to Insert= {");
				for (int i = 0; i < VictimsNoLonger.size(); i++) {
					printf("Object%d, ", VictimsNoLonger[i]->OrderCreation + 1);
				}
				printf("}\n");
			}

			if (Debug) {
				printf("And here's the Original VictimList = {");
				for (int i = 0; i < VictimsNoLongerOrigin.size(); i++) {
					printf("Object%d, ", VictimsNoLongerOrigin[i]->OrderCreation + 1);
				}
				printf("}\n");
			}


			//This now inserts newly uncovered victims into the victimsNoLonger vector appropriately. This is so when this function returns, you can then try moving it again. 
			while (VictimsNoLonger.size() > 0) {

				if (Debug) {
					printf("Top of VictimsNoLonger BinSearch Loop\n");
					printf("Victims No Longer Size = %d, Origin Size = %d\n", VictimsNoLonger.size(), VictimsNoLongerOrigin.size());
				}
				BinSearchInsert(VictimsNoLongerOrigin, VictimsNoLonger, 0, VictimsNoLongerOrigin.size() - 1);
				if (Debug) {
					printf("Inserted VictimsNoLonger = {");
					for (int i = 0; i < VictimsNoLongerOrigin.size(); i++) {
						printf("Object%d, ", VictimsNoLongerOrigin[i]->OrderCreation + 1);
					}
					printf("}\n");
				}
				if (Debug) {
					printf("This is rare, so give your self a minute to get some photos or look at it\n");
				}
				//SDL_Delay(5000);
			}
		}
		//add those new victims into the appropraite posiiton on the current victim que.  
		   //Mark CompletedSprites as successful
	   //so this will just run one at a time. So it is fine for just to insert because I'm not trying to do the items right as they are revealed, rather I just want to add any new eraseable items, 
	   //This SHOULD work if I'm doing what I think I am - which is anything amrked as compeltedsprites[x]==1 is removed from the stack, thus we should be able to remove everything up to the currentQue location
	   //thus we should be able to get through all of victimsnomore.

	   //pause printf("6) Moving Diagonally\n"); SDL_Delay(2000);
	}


	//recursive
	void BinSearchInsert(std::vector<Sprite*>& Origin, std::vector<Sprite*>& Insertable, int Left, int Right) {
		bool Debug = false;
		int Middle;
		Middle = (Left - (Right - Left) / 2);
		if (Debug) {
			printf("BinSearch, L = %d, R = %d, M = %d\n", Left, Right, Middle);
		}


		if (Middle < 0) {
			if (Origin[0]->OrderCreation > Insertable.back()->OrderCreation) {
				if (Debug) {
					printf("I thinK the position your looking for is %d\n", 1);
				}Origin.insert(Origin.begin() + 1, Insertable.back());
				if (Debug) {
					printf("Inserted the new Victim into the Original list\n");
				}Insertable.pop_back(); //this hsould keep it from being infinite.
				if (Debug) {
					printf("Pop backed from the new victims\n");
				}
			}
			else {
				if (Debug) {
					printf("I thinK the position your looking for is %d\n", 0);
				}
				Origin.insert(Origin.begin() + 0, Insertable.back());
				if (Debug) {
					printf("Inserted the new Victim into the Original list\n");
				}
				Insertable.pop_back(); //this hsould keep it from being infinite.

				if (Debug) {
					printf("Pop backed from the new victims\n");
				}
			}
		}
		else {
			if (Left == Middle || Right == Middle) {
				//this si for the error {3} inserted into {15, 12} resulting in {3, 15, 12} when we want {15, 3, 12}, which will then po pto be {15, 3}. - should only rely on it at a certain size...
				if (Middle + 1 < Origin.size()) {
					if (Origin[Middle]->OrderCreation > Insertable.back()->OrderCreation) {
						//if the item to your right is greater than yourself, you want to move forward because your younger
						if (Debug) {
							printf("Move the middle!\n");
						}
						Middle += 1;
					}
				}
				if (Debug) {
					printf("I thinK the position your looking for is %d\n", Middle);
				}
				Origin.insert(Origin.begin() + Middle, Insertable.back());
				if (Debug) {
					printf("Inserted the new Victim into the Original list\n");
				}
				Insertable.pop_back(); //this hsould keep it from being infinite.
				if (Debug) {
					printf("Pop backed from the new victims\n");
				}
			}
			else {
				//it is somewhere in the left half of the array (begining, if odd, round down the half)
				if (Insertable.back()->OrderCreation > Origin[Middle]->OrderCreation) {
					BinSearchInsert(Origin, Insertable, Left, Middle);
					if (Debug) {
						printf("Item we're trying to insert is greater than the middle's order creation\n");
					}
				}
				//it is somewhere in the rihg thalf of hte array (if odd, round up, to end)
				else if (Insertable.back()->OrderCreation < Origin[Middle]->OrderCreation) {
					BinSearchInsert(Origin, Insertable, Middle + 1, Right);
					if (Debug) {
						printf("Item we're trying to insert is less than the middle's order creation\n");
					}
				}
				//you found an equivalent position (should be impossible!)
				else {
					if (Debug) {
						printf("Impossible insertion?");
					}
				}
			}
		}
	}

	void RemoveSpriteFromMap(Sprite* ObjectSprite) {
		// printf("RemoveSpriteFromMap\n");
		int x1 = NULL;
		int x2 = NULL;
		int y1 = NULL;
		int y2 = NULL;
		x1 = ObjectSprite->xPos;
		x2 = ObjectSprite->xPos + TILE_WIDTH;
		y1 = ObjectSprite->yPos;
		y2 = ObjectSprite->yPos + TILE_HEIGHT;


		//NOTE - YOU CANT RELY on the first in order going first, this is because A may be blocked by G, so G resolves first, but if they are on the same 'tile' then A is the begiing of hte vector, which gets stupid after a while, because you move without knowing if G got out of the way.
		int TempY2Math = y2 - TILE_HEIGHT * (y2 / TILE_HEIGHT); //A = C - B * (C/B)
		int TempX2Math = x2 - TILE_WIDTH * (x2 / TILE_WIDTH); //A = C - B * (C/B)
		if (TempX2Math == 0) {
			x2 = x1;
		}
		if (TempY2Math == 0) {
			y2 = y1;
		}


		x1 = x1 / TILE_WIDTH; //saves an small amount of comuptation
		x2 = x2 / TILE_WIDTH;
		y1 = y1 / TILE_HEIGHT;
		y2 = y2 / TILE_HEIGHT;
		//gaurds from map/matrix overflow
		if (y1 > LEVEL_HEIGHT - 1) {
			y1 = LEVEL_HEIGHT - 1;
			y2 = y1;
		}
		if (y1 < 0) {
			y1 = 0;
			y2 = y1;
		}
		if (x1 > LEVEL_WIDTH - 1) {
			x1 = LEVEL_WIDTH - 1;
			x2 = x1;
		}
		if (x1 < 0) {
			x1 = 0;
			x2 = x1;
		}


		//find, if it doesn't find the item,  returns the LAST element of the vector. CAREFUL - this was a major error thattook us a while to find. you'd think find would return null or end() when it fails.
		if (true) {
			// printf("Erasing Object%d, from UL", ObjectSprite->OrderCreation + 1);
			LM[y1][x1].erase(find(LM[y1][x1].begin(), LM[y1][x1].end() - 1, ObjectSprite));
		}
		if (x1 != x2) {
			LM[y1][x2].erase(find(LM[y1][x2].begin(), LM[y1][x2].end() - 1, ObjectSprite));
		}
		if (y1 != y2) {
			LM[y2][x1].erase(find(LM[y2][x1].begin(), LM[y2][x1].end() - 1, ObjectSprite));
			if (x1 != x2) {
				LM[y2][x2].erase(find(LM[y2][x2].begin(), LM[y2][x2].end() - 1, ObjectSprite));
			}

		}


		// printf("Erased all\n");
	}










	int CheckOverlapSTART2(Sprite* ObjectSprite) {
		bool Debug = false;
		if (TOTALFRAMECOUNT > 120000) {
			Debug = true;
		} 

		//should already be removed (in this case)
		if (Debug) {
			printf("CHECKOVERLAPSTART2\n");
			printf("Remove ObjectSprite from Map\n");
		}
		RemoveSpriteFromMap(ObjectSprite); //Temporary, this is just for the testing for collision and the strange overlap. In the future it won't remove and then readd, but instead ignore itself when checking.

		// printf("CheckFutureSpritePosition\n");
		int x1, x2, y1, y2;

		int TempX2, TempY2;

		x1 = ObjectSprite->xPos;
		x2 = ObjectSprite->xPos + TILE_WIDTH;
		y1 = ObjectSprite->yPos;
		y2 = ObjectSprite->yPos + TILE_HEIGHT;

		TempX2 = x2 % TILE_WIDTH;
		TempY2 = y1 % TILE_HEIGHT;
		int TempY2Math = y2 - TILE_HEIGHT * (y2 / TILE_HEIGHT); //A = C - B * (C/B)
		// printf("TempY2Math = y2 -16*(y2/16) = %d, from %d, %d\n", TempY2Math, TILE_HEIGHT, y2);
		int TempX2Math = x2 - TILE_WIDTH * (x2 / TILE_WIDTH);
		y1 = y1 / TILE_HEIGHT;
		y2 = y2 / TILE_HEIGHT;
		x1 = x1 / TILE_WIDTH;
		x2 = x2 / TILE_WIDTH;
		//gaurds from map/matrix overflow
		if (true) {
			if (y1 > LEVEL_HEIGHT - 1) {
				y1 = LEVEL_HEIGHT - 1;
				y2 = y1;
			}
			if (y1 < 0) {
				y1 = 0;
				y2 = y1;
			}
			if (x1 > LEVEL_WIDTH - 1) {
				x1 = LEVEL_WIDTH - 1;
				x2 = x1;
			}
			if (x1 < 0) {
				x1 = 0;
				x2 = x1;
			}
		}
		//So we don't check further than we want to, and when we don't need to. In these cases, it doens't matter now if we use x1, or x2. For consistency, we use whatever appears the most as appropriate. 
		if (true) {
			if (TempX2Math == 0) {
				x2 = x1;
			}
			if (TempY2Math == 0) {
				y2 = y1;
			}
		}

		int yOverlapped = 0;
		int xOverlapped = 0;
		bool HaveOverlapped = false;

		if (Debug) {
			printf("Finished initial variables for CheckOverlap2\n");
			printf("Check the four corners\n");
		}

		//Check all four corners! (for now it's just checking the sprites.
		if (true) {
			for (int i = 0; i < LM[y1][x1].size(); i++) {
				//Figureout if the overlapX is at least 1
				if (true) {
					if (LM[y1][x1][i]->yPos > ObjectSprite->yPos) {
						yOverlapped = ObjectSprite->yPos + TILE_HEIGHT - LM[y1][x1][i]->yPos;
					}
					else { //if (Spos =< Posy 
						yOverlapped = LM[y1][x1][i]->yPos + TILE_HEIGHT - ObjectSprite->yPos;
					}
				}

				//Figureout if the overlap is at least 1
				if (true) {
					if (LM[y1][x1][i]->xPos > ObjectSprite->xPos) {
						xOverlapped = ObjectSprite->xPos + TILE_WIDTH - LM[y1][x1][i]->xPos;
					}
					else { //if (Spos =< Posx 
						xOverlapped = LM[y1][x1][i]->xPos + TILE_WIDTH - ObjectSprite->xPos;
					}
				}

				if ((xOverlapped > 0 && xOverlapped < 17) && (yOverlapped > 0 && yOverlapped < 17)) {
					printf("Object%d overlapped with Object%d!\n", ObjectSprite->OrderCreation + 1, LM[y1][x1][i]->OrderCreation + 1);
					ReMapSprite(ObjectSprite);
					HaveOverlapped = true; //you have overlapped 
				}
				yOverlapped = 0;
				xOverlapped = 0;
			}
			if (x1 != x2) {
				for (int i = 0; i < LM[y1][x2].size(); i++) {
					//Figureout if the overlap is at least 1
					if (true) {
						if (LM[y1][x2][i]->yPos > ObjectSprite->yPos) {
							yOverlapped = ObjectSprite->yPos + TILE_HEIGHT - LM[y1][x2][i]->yPos;
						}
						else { //if (Spos =< Posy   
							yOverlapped = LM[y1][x2][i]->yPos + TILE_HEIGHT - ObjectSprite->yPos;
						}
					}

					//Figureout if the overlap is at least 1
					if (true) {
						if (LM[y1][x2][i]->xPos > ObjectSprite->xPos) {
							xOverlapped = ObjectSprite->xPos + TILE_WIDTH - LM[y1][x2][i]->xPos;
						}
						else { //if (Spos =< Posx
							xOverlapped = LM[y1][x2][i]->xPos + TILE_WIDTH - ObjectSprite->xPos;
						}
					}

					if ((xOverlapped > 0 && xOverlapped < 17) && (yOverlapped > 0 && yOverlapped < 17)) {
						printf("Object%d overlapped with Object%d!\n", ObjectSprite->OrderCreation + 1, LM[y1][x2][i]->OrderCreation + 1);
						ReMapSprite(ObjectSprite);
						HaveOverlapped = true; //you have overlapped 
					}
					yOverlapped = 0;
					xOverlapped = 0;
				}
			}
			if (y1 != y2) {
				for (int i = 0; i < LM[y2][x1].size(); i++) {
					//Figureout if the overlap is at least 1
					if (true) {
						if (LM[y2][x1][i]->xPos > ObjectSprite->xPos) {
							xOverlapped = ObjectSprite->xPos + TILE_WIDTH - LM[y2][x1][i]->xPos;
						}
						else { //if (Spos =< Posx 
							xOverlapped = LM[y2][x1][i]->xPos + TILE_WIDTH - ObjectSprite->xPos;
						}
					}

					//Figureout if the overlap is at least 1
					if (true) {
						if (LM[y2][x1][i]->yPos > ObjectSprite->yPos) {
							yOverlapped = ObjectSprite->yPos + TILE_HEIGHT - LM[y2][x1][i]->yPos;
						}
						else { //if (Spos =< Posy  
							yOverlapped = LM[y2][x1][i]->yPos + TILE_HEIGHT - ObjectSprite->yPos;
						}
					}

					if ((xOverlapped > 0 && xOverlapped < 17) && (yOverlapped > 0 && yOverlapped < 17)) {
						printf("Object%d overlapped with Object%d!\n", ObjectSprite->OrderCreation + 1, LM[y2][x1][i]->OrderCreation + 1);
						ReMapSprite(ObjectSprite);
						HaveOverlapped = true; //you have overlapped 
					}
					yOverlapped = 0;
					xOverlapped = 0;
				}
				if (x1 != x2) {
					for (int i = 0; i < LM[y2][x2].size(); i++) {
						//Figureout if the overlap is at least 1
						if (true) {
							if (LM[y2][x2][i]->yPos > ObjectSprite->yPos) {
								yOverlapped = ObjectSprite->yPos + TILE_HEIGHT - LM[y2][x2][i]->yPos;
							}
							else { //if (Spos =< Posy
								yOverlapped = LM[y2][x2][i]->yPos + TILE_HEIGHT - ObjectSprite->yPos;
							}
						}

						//Figureout if the overlap is at least 1
						if (true) {
							if (LM[y2][x2][i]->xPos > ObjectSprite->xPos) {
								xOverlapped = ObjectSprite->xPos + TILE_WIDTH - LM[y2][x2][i]->xPos;
							}
							else { //if (Spos =< Posx
								xOverlapped = LM[y2][x2][i]->xPos + TILE_WIDTH - ObjectSprite->xPos;
							}
						}

						if ((xOverlapped > 0 && xOverlapped < 17) && (yOverlapped > 0 && yOverlapped < 17)) {
							printf("Object%d overlapped with Object%d!\n", ObjectSprite->OrderCreation + 1, LM[y2][x2][i]->OrderCreation + 1);
							ReMapSprite(ObjectSprite);
							HaveOverlapped = true; //you have overlapped 
						}
						yOverlapped = 0;
						xOverlapped = 0;
					}
				}

			}
		}
		if (Debug) {
			printf("Set the Travel, ExVel, and Last Destination of the Sprite\n");
		}
		//WORK - Based on what you overlapped Sprites, determine what to set for Travel, ExVec, etc.
		//For now lets just set the basic stuff
		ObjectSprite->Travel[0] = absolute(ObjectSprite->xVec);
		ObjectSprite->Travel[1] = absolute(ObjectSprite->yVec);
		ObjectSprite->ExVel[0] = ObjectSprite->xVec;
		ObjectSprite->ExVel[1] = ObjectSprite->yVec;
		ObjectSprite->LastDestination.push_back({ ObjectSprite->xPos , ObjectSprite->yPos });

		if (Debug) {
			printf("Remap Sprite!\n");
		}
		ReMapSprite2(ObjectSprite);

		 

		if (HaveOverlapped == true) {
			if (Debug) {
				printf("You have overlapped with something\n");
				if (ObjectSprite->OrderCreation == AllSprites.size() - 1) {
					printf("END OF OVERLAPSTART2");
				}
			}
			return 1;
		}
		if (Debug) {
			printf("overlapped with nothing\n");
			if (ObjectSprite->OrderCreation == AllSprites.size() - 1) {
				printf("END OF OVERLAPSTART2\n\n\n");
			}
		}
		return 0;

	}

	void ReMapSprite2(Sprite* ObjectSprite) {
		bool Debug = true;
		// printf("ReMapSprite\n");
		//Put into matrix -ONLY DO ONCE PER SPRITE. 
		int x1 = NULL;
		int x2 = NULL;
		int y1 = NULL;
		int y2 = NULL;
		int OrderedPosition = 0;
		//The null will allow us to skip it if there is no info there.
		x1 = ObjectSprite->LastDestination.back()[0];
		x2 = ObjectSprite->LastDestination.back()[0] + TILE_WIDTH;
		y1 = ObjectSprite->LastDestination.back()[1];
		y2 = ObjectSprite->LastDestination.back()[1] + TILE_HEIGHT;

		// printf("Remap Object%d, x1=%d, y1=%d\n", ObjectSprite->OrderCreation + 1, x1, y1);
		//NOTE - replace pushbacks with inserts - unless empty vector
		if (Debug) {
			printf("Begin Remapping Object%d\n", ObjectSprite->OrderCreation + 1);
		}
		int TempY2Math = y2 - TILE_HEIGHT * (y2 / TILE_HEIGHT); //A = C - B * (C/B)
		int TempX2Math = x2 - TILE_WIDTH * (x2 / TILE_WIDTH); //A = C - B * (C/B)
		if (TempX2Math == 0) {
			x2 = x1;
		}
		if (TempY2Math == 0) {
			y2 = y1;
		}



		y1 = y1 / TILE_HEIGHT;
		y2 = y2 / TILE_HEIGHT;
		x1 = x1 / TILE_WIDTH;
		x2 = x2 / TILE_WIDTH;


		//gaurds from map/matrix overflow
		if (y1 > LEVEL_HEIGHT - 1) {
			y1 = LEVEL_HEIGHT - 1;
			y2 = y1;
		}
		if (y1 < 0) {
			y1 = 0;
			y2 = y1;
		}
		if (x1 > LEVEL_WIDTH - 1) {
			x1 = LEVEL_WIDTH - 1;
			x2 = x1;
		}
		if (x1 < 0) {
			x1 = 0;
			x2 = x1;
		}

		if (Debug) {
			printf("Finished Initial variables for ReMapSprite2\n");
			printf("Now insert it back into the cells on the LM Matrix\n");
		}

		if (LM[y1][x1].size() == 0) {
			if (Debug) {
				printf("a\n");
			}
			LM[y1][x1].push_back(ObjectSprite);

		}
		else {
			if (Debug) {
				printf("b\n");
			}
			while (OrderedPosition < LM[y1][x1].size() && LM[y1][x1][OrderedPosition]->OrderCreation < ObjectSprite->OrderCreation) {
				OrderedPosition++;
			}

			LM[y1][x1].insert(LM[y1][x1].begin() + OrderedPosition, ObjectSprite);

			OrderedPosition = 0;
		}
		if (x1 != x2) {

			if (LM[y1][x2].size() == 0) {
				if (Debug) {
					printf("c\n");
				}
				LM[y1][x2].push_back(ObjectSprite);
			}
			else {
				if (Debug) {
					printf("d\n");
				}
				while (OrderedPosition < LM[y1][x2].size() && LM[y1][x2][OrderedPosition]->OrderCreation < ObjectSprite->OrderCreation) {
					OrderedPosition++;
				}
				LM[y1][x2].insert(LM[y1][x2].begin() + OrderedPosition, ObjectSprite);
				OrderedPosition = 0;
			}
		}
		if (y1 != y2) {
			if (LM[y2][x1].size() == 0) {
				if (Debug) {
					printf("e\n");
				}
				LM[y2][x1].push_back(ObjectSprite);
			}
			else {
				if (Debug) {
					printf("f\n");
				}
				while (OrderedPosition < LM[y2][x1].size() && LM[y2][x1][OrderedPosition]->OrderCreation < ObjectSprite->OrderCreation) {
					OrderedPosition++;
				}
				LM[y2][x1].insert(LM[y2][x1].begin() + OrderedPosition, ObjectSprite);
				OrderedPosition = 0;
			}

			if (x1 != x2) {
				if (Debug) {
					printf("g\n");
				}
				if (LM[y2][x2].size() == 0) {
					LM[y2][x2].push_back(ObjectSprite);
				}
				else {
					while (OrderedPosition < LM[y2][x2].size() && LM[y2][x2][OrderedPosition]->OrderCreation < ObjectSprite->OrderCreation) {
						OrderedPosition++;
					}
					LM[y2][x2].insert(LM[y2][x2].begin() + OrderedPosition, ObjectSprite);
				}
			}
		}

		if (Debug) {
			printf("Done reMapping\n");
		}
	}

	void MergeSortSpriteCollision2(std::vector<Sprite*>& SpriteOverlap, std::vector<int>& SpriteArea) { //we will be editing directly onto it
		bool Debug = false;
		if (TOTALFRAMECOUNT > 120000) {
			Debug = true;
		}
		Debug = false;

		if (SpriteArea.size() > 1) {
			int M = SpriteArea.size() / 2;
			std::vector<int> LeftHalfArea(SpriteArea.begin(), SpriteArea.begin() + M);
			std::vector<int> RightHalfArea(SpriteArea.begin() + M, SpriteArea.begin() + SpriteArea.size());

			std::vector<Sprite*> LeftHalfOverlap(SpriteOverlap.begin(), SpriteOverlap.begin() + M);
			std::vector<Sprite*> RightHalfOverlap(SpriteOverlap.begin() + M, SpriteOverlap.begin() + SpriteOverlap.size());


			MergeSortSpriteCollision2(LeftHalfOverlap, LeftHalfArea);
			MergeSortSpriteCollision2(RightHalfOverlap, RightHalfArea);




			unsigned LeftItter = 0;
			unsigned RightItter = 0;
			unsigned SourceItter = 0;
			while (LeftItter < LeftHalfArea.size() && RightItter < RightHalfArea.size()) {
				if (LeftHalfArea[LeftItter] < RightHalfArea[RightItter]) {
					SpriteArea[SourceItter] = LeftHalfArea[LeftItter];
					SpriteOverlap[SourceItter] = LeftHalfOverlap[LeftItter];
					LeftItter++;
				}
				else {
					SpriteArea[SourceItter] = RightHalfArea[RightItter];
					SpriteOverlap[SourceItter] = RightHalfOverlap[RightItter];
					RightItter++;
				}
				SourceItter++;
			}

			while (LeftItter < LeftHalfArea.size()) {
				SpriteArea[SourceItter] = LeftHalfArea[LeftItter];
				SpriteOverlap[SourceItter] = LeftHalfOverlap[LeftItter];
				LeftItter++;
				SourceItter++;
			}

			while (RightItter < RightHalfArea.size()) {
				SpriteArea[SourceItter] = RightHalfArea[RightItter];
				SpriteOverlap[SourceItter] = RightHalfOverlap[RightItter];
				RightItter++;
				SourceItter++;
			}

		}



		if (Debug) {
			printf("Try Merging\n");
		}

	}

	int CheckOverlap2(Sprite* ObjectSprite) {
		bool Debug = false;
		if (TOTALFRAMECOUNT > 120000) {
			Debug = true;
		}
		Debug = true;

		//should already be removed (in this case)
		if (Debug) {
			printf("RemoveObjectSpritefromMap2\n");
			printf("Current position = {%d, %d}\n", ObjectSprite->xPos, ObjectSprite->yPos);
			printf("Last Destination = {%d, %d}\n",ObjectSprite->LastDestination.back()[0], ObjectSprite->LastDestination.back()[1]);
		}
		RemoveSpriteFromMap2(ObjectSprite); //Temporary, this is just for the testing for collision and the strange overlap. In the future it won't remove and then readd, but instead ignore itself when checking.
		
		if (Debug) {
			printf("Finished RemoveSpriteFromMap2 in Overlap2\n");
		}
		// printf("CheckFutureSpritePosition\n");
		int x1, x2, y1, y2;

		int TempX2, TempY2;

		x1 = ObjectSprite->LastDestination.back()[0];
		x2 = ObjectSprite->LastDestination.back()[0] + TILE_WIDTH;
		y1 = ObjectSprite->LastDestination.back()[1];
		y2 = ObjectSprite->LastDestination.back()[1] + TILE_HEIGHT;

		TempX2 = x2 % TILE_WIDTH;
		TempY2 = y1 % TILE_HEIGHT;
		int TempY2Math = y2 - TILE_HEIGHT * (y2 / TILE_HEIGHT); //A = C - B * (C/B)
		// printf("TempY2Math = y2 -16*(y2/16) = %d, from %d, %d\n", TempY2Math, TILE_HEIGHT, y2);
		int TempX2Math = x2 - TILE_WIDTH * (x2 / TILE_WIDTH);
		y1 = y1 / TILE_HEIGHT;
		y2 = y2 / TILE_HEIGHT;
		x1 = x1 / TILE_WIDTH;
		x2 = x2 / TILE_WIDTH;
		//gaurds from map/matrix overflow
		if (true) {
			if (y1 > LEVEL_HEIGHT - 1) {
				y1 = LEVEL_HEIGHT - 1;
				y2 = y1;
			}
			if (y1 < 0) {
				y1 = 0;
				y2 = y1;
			}
			if (x1 > LEVEL_WIDTH - 1) {
				x1 = LEVEL_WIDTH - 1;
				x2 = x1;
			}
			if (x1 < 0) {
				x1 = 0;
				x2 = x1;
			}
		}
		//So we don't check further than we want to, and when we don't need to. In these cases, it doens't matter now if we use x1, or x2. For consistency, we use whatever appears the most as appropriate. 
		if (true) {
			if (TempX2Math == 0) {
				x2 = x1;
			}
			if (TempY2Math == 0) {
				y2 = y1;
			}
		}

		int yOverlapped = 0;
		int xOverlapped = 0;
		bool HaveOverlapped = false;
		
		if (Debug) {
			printf("Finished initial variables for CheckOverlap2\n");
			printf("Check the four corners\n");
		}

		//Check all four corners! (for now it's just checking the sprites.
		if (true) {
			for (int i = 0; i < LM[y1][x1].size(); i++) {
				//Figureout if the overlapX is at least 1
				if (true) {
					if (LM[y1][x1][i]->yPos > ObjectSprite->yPos) {
						yOverlapped = ObjectSprite->yPos + TILE_HEIGHT - LM[y1][x1][i]->yPos;
					}
					else { //if (Spos =< Posy 
						yOverlapped = LM[y1][x1][i]->yPos + TILE_HEIGHT - ObjectSprite->yPos;
					}
				}

				//Figureout if the overlap is at least 1
				if (true) {
					if (LM[y1][x1][i]->xPos > ObjectSprite->xPos) {
						xOverlapped = ObjectSprite->xPos + TILE_WIDTH - LM[y1][x1][i]->xPos;
					}
					else { //if (Spos =< Posx 
						xOverlapped = LM[y1][x1][i]->xPos + TILE_WIDTH - ObjectSprite->xPos;
					}
				}

				if ((xOverlapped > 0 && xOverlapped < 17) && (yOverlapped > 0 && yOverlapped < 17)) {
					printf("Object%d overlapped with Object%d!\n", ObjectSprite->OrderCreation + 1, LM[y1][x1][i]->OrderCreation + 1);
					ReMapSprite(ObjectSprite);
					HaveOverlapped = true; //you have overlapped 
				}
				yOverlapped = 0;
				xOverlapped = 0;
			}
			if (x1 != x2) {
				for (int i = 0; i < LM[y1][x2].size(); i++) {
					//Figureout if the overlap is at least 1
					if (true) {
						if (LM[y1][x2][i]->yPos > ObjectSprite->yPos) {
							yOverlapped = ObjectSprite->yPos + TILE_HEIGHT - LM[y1][x2][i]->yPos;
						}
						else { //if (Spos =< Posy   
							yOverlapped = LM[y1][x2][i]->yPos + TILE_HEIGHT - ObjectSprite->yPos;
						}
					}

					//Figureout if the overlap is at least 1
					if (true) {
						if (LM[y1][x2][i]->xPos > ObjectSprite->xPos) {
							xOverlapped = ObjectSprite->xPos + TILE_WIDTH - LM[y1][x2][i]->xPos;
						}
						else { //if (Spos =< Posx
							xOverlapped = LM[y1][x2][i]->xPos + TILE_WIDTH - ObjectSprite->xPos;
						}
					}

					if ((xOverlapped > 0 && xOverlapped < 17) && (yOverlapped > 0 && yOverlapped < 17)) {
						printf("Object%d overlapped with Object%d!\n", ObjectSprite->OrderCreation + 1, LM[y1][x2][i]->OrderCreation + 1);
						ReMapSprite(ObjectSprite);
						HaveOverlapped = true; //you have overlapped 
					}
					yOverlapped = 0;
					xOverlapped = 0;
				}
			}
			if (y1 != y2) {
				for (int i = 0; i < LM[y2][x1].size(); i++) {
					//Figureout if the overlap is at least 1
					if (true) {
						if (LM[y2][x1][i]->xPos > ObjectSprite->xPos) {
							xOverlapped = ObjectSprite->xPos + TILE_WIDTH - LM[y2][x1][i]->xPos;
						}
						else { //if (Spos =< Posx 
							xOverlapped = LM[y2][x1][i]->xPos + TILE_WIDTH - ObjectSprite->xPos;
						}
					}

					//Figureout if the overlap is at least 1
					if (true) {
						if (LM[y2][x1][i]->yPos > ObjectSprite->yPos) {
							yOverlapped = ObjectSprite->yPos + TILE_HEIGHT - LM[y2][x1][i]->yPos;
						}
						else { //if (Spos =< Posy  
							yOverlapped = LM[y2][x1][i]->yPos + TILE_HEIGHT - ObjectSprite->yPos;
						}
					}

					if ((xOverlapped > 0 && xOverlapped < 17) && (yOverlapped > 0 && yOverlapped < 17)) {
						printf("Object%d overlapped with Object%d!\n", ObjectSprite->OrderCreation + 1, LM[y2][x1][i]->OrderCreation + 1);
						ReMapSprite(ObjectSprite);
						HaveOverlapped = true; //you have overlapped 
					}
					yOverlapped = 0;
					xOverlapped = 0;
				}
				if (x1 != x2) {
					for (int i = 0; i < LM[y2][x2].size(); i++) {
						//Figureout if the overlap is at least 1
						if (true) {
							if (LM[y2][x2][i]->yPos > ObjectSprite->yPos) {
								yOverlapped = ObjectSprite->yPos + TILE_HEIGHT - LM[y2][x2][i]->yPos;
							}
							else { //if (Spos =< Posy
								yOverlapped = LM[y2][x2][i]->yPos + TILE_HEIGHT - ObjectSprite->yPos;
							}
						}

						//Figureout if the overlap is at least 1
						if (true) {
							if (LM[y2][x2][i]->xPos > ObjectSprite->xPos) {
								xOverlapped = ObjectSprite->xPos + TILE_WIDTH - LM[y2][x2][i]->xPos;
							}
							else { //if (Spos =< Posx
								xOverlapped = LM[y2][x2][i]->xPos + TILE_WIDTH - ObjectSprite->xPos;
							}
						}

						if ((xOverlapped > 0 && xOverlapped < 17) && (yOverlapped > 0 && yOverlapped < 17)) {
							printf("Object%d overlapped with Object%d!\n", ObjectSprite->OrderCreation + 1, LM[y2][x2][i]->OrderCreation + 1);
							ReMapSprite(ObjectSprite);
							HaveOverlapped = true; //you have overlapped 
						}
						yOverlapped = 0;
						xOverlapped = 0;
					}
				}

			}
		}
		if (Debug) {
			printf("Set the Travel, ExVel, and Last Destination of the Sprite\n");
		}
		//WORK - Based on what you overlapped Sprites, determine what to set for Travel, ExVec, etc.
		//For now lets just set the basic stuff
		ObjectSprite->Travel[0] = absolute(ObjectSprite->xVec);
		ObjectSprite->Travel[1] = absolute(ObjectSprite->yVec);
		ObjectSprite->ExVel[0] = ObjectSprite->xVec;
		ObjectSprite->ExVel[1] = ObjectSprite->yVec;
		//might be unnecessaryV
		ObjectSprite->LastDestination.push_back({ ObjectSprite->xPos , ObjectSprite->yPos });

		if (Debug) {
			printf("Remap Sprite!\n");
		}
		ReMapSprite2(ObjectSprite);

		if (HaveOverlapped == true) {
			if (Debug) {
				printf("You have overlapped with something\n");
			}
			return 1;
		}
		if (Debug) {
			printf("overlapped with nothing\n");
		}
		return 0;

	}
	
	
	//Goes into LM, figures out the one closest to your travel path, returns it, and figures out appropriate overlap value.
	void JostleX(Sprite* ObjectSprite, int Edge[2], int Measure, XYArr2* TempStackable, int xDist) {
		bool Debug = false;
		int xPos, yPos;
		int x1, x2, y1, y2;

		int TempX2Math, TempY2Math;

		//the 'jostle'
		x1 = ObjectSprite->xPos +  xDist;
		y1 = ObjectSprite->yPos;
		x2 = ObjectSprite->xPos + TILE_WIDTH +  xDist;
		y2 = ObjectSprite->yPos + TILE_HEIGHT;

		//NOTE - gaurds from map/matrix overflow - NEW 8/19 - since I edited it, becaue the moves seem to guard against going out of bounds in the first place, I made it so that this guards the directions, so it's easier to process. Odd behavior is that once the original is adjusted, it stays adjused until the key is pressed again. Don't think I like that. It's stays that way because the =, but I can't just get rid of it. Maybe I'll make a case when it's on vs when it's off the very edge, so that it's only triggered once per button press or something...
		if (true) {
			if (x1 >= (LEVEL_WIDTH - 1) * TILE_WIDTH) {
				x1 = LEVEL_WIDTH - 1;
				x2 = x1;
				ObjectSprite->xVec = 0;
				if (Debug || PAUSECOLLISIONJOSTLE[6] == 0) {
					printf("%d", TOTALFRAMECOUNT);
					printf(" Sprite%d can no longer go further right\n", ObjectSprite->OrderCreation + 1);
					PAUSECOLLISIONJOSTLE[6] = 1;
					SDL_Delay(10000);
				}
			}
			if (x1 <= 0) { //NEW - 8/19/21 This is done because the move's already track the bounds of hte level, so here I want to know whether the mod is higher than it should be or the actual position is less (because the mod is not solid enough)
				x1 = 0;
				x2 = x1;
				ObjectSprite->xVec = 0;
				if (Debug || PAUSECOLLISIONJOSTLE[7] == 0) {
					printf("%d", TOTALFRAMECOUNT);
					printf(" Sprite%d can no longer go further left\n", ObjectSprite->OrderCreation + 1);
					PAUSECOLLISIONJOSTLE[7] = 1;
					SDL_Delay(10000);
				}
			}
		}
		//WORK - maybe change measure if this is used to adjust position? 
		xPos = x1; //so we work wit hthe adjusted position of the ObjectSprite
		yPos = y1;
		TempY2Math = y2 - TILE_HEIGHT * (y2 / TILE_HEIGHT); //A = C - B * (C/B)
		TempX2Math = x2 - TILE_WIDTH * (x2 / TILE_WIDTH);
		y1 = y1 / TILE_HEIGHT;
		y2 = y2 / TILE_HEIGHT;
		x1 = x1 / TILE_WIDTH;
		x2 = x2 / TILE_WIDTH;

		//So we don't check further than we want to, and when we don't need to. In these cases, it doens't matter now if we use x1, or x2. For consistency, we use whatever appears the most as appropriate. 
		if (TempX2Math == 0) {
			x2 = x1;
		}
		if (TempY2Math == 0) {
			y2 = y1;
		}
		//Vector that holds the 'area' of overlap - this is to be compared with, and then swapped if one with larger area shows up
		//if tie, look at order creation
		std::vector<Sprite*> SpritesHit = {};
		std::vector<int> SpriteX = {};
		std::vector<int> SpriteY = {};

		std::vector<Sprite*> SpriteOverlapX = {};
		std::vector<Sprite*> SpriteOverlapY = {};

		int TempXOverlap = 0;
		int TempYOverlap = 0;
		//EDIT Switch all ObjextSprite pos' to x1, y1's!
		if (true) {
			if (Measure == 6) {//L
			//edges are [x1][y1] and [x1][y2]
				if (TempY2Math == 0) {
					if (Debug) {
						printf("af\n");
					}
					for (int i = 0; i < LM[y1][x1].size(); i++) {
						if (true) {
							if (LM[y1][x1][i]->xPos < xPos) {
								SpritesHit.push_back(LM[y1][x1][i]);
							}
						}
					}
				}
				else {
					if (Debug) {
						printf("ag\n");
					}
					for (int i = 0; i < LM[y1][x1].size(); i++) {
						if (true) {
							if (LM[y1][x1][i]->xPos < xPos) { //NEW (CHANGED)
								SpritesHit.push_back(LM[y1][x1][i]);
							}
						}
					}
					if (Debug) {
						printf("ah\n");
					}
					for (int i = 0; i < LM[y2][x1].size(); i++) {
						//Overlap to be recorded
						if (true) {
							if (LM[y2][x1][i]->xPos < xPos) { //NEW (CHANGED)
								SpritesHit.push_back(LM[y2][x1][i]);
							}
						}
					}
				}
			}
			else if (Measure == 14) {//R
				//edges are [x2][y1] and [x2][y2]
				if (TempY2Math == 0) {
					if (Debug) {
						printf("ai\n");
					}
					for (int i = 0; i < LM[y1][x2].size(); i++) {
						if (true) {
							if (LM[y1][x2][i]->xPos > xPos) { //NEW (CHANGED)
								SpritesHit.push_back(LM[y1][x2][i]);
							}
						}
					}
				}
				else {
					if (Debug) {
						printf("aj\n");
					}
					for (int i = 0; i < LM[y1][x2].size(); i++) {
						if (true) {
							if (LM[y1][x2][i]->xPos > xPos) {//NEW (CHANGED)
								SpritesHit.push_back(LM[y1][x2][i]);

							}
						}
					}
					if (Debug) {
						printf("ak\n");
					}
					for (int i = 0; i < LM[y2][x2].size(); i++) {
						if (true) {
							if (LM[y2][x2][i]->xPos > xPos) {//NEW (CHANGED)
								SpritesHit.push_back(LM[y2][x2][i]);
							}
						}
					}
				}
			}
		}
		//Hit sprites should now have all the sprites to the X side of travel of the object in question. 


		//Now I have to figure out if there's any  REAL overlap.
		if (true) {
			if (Measure == 6) {
				for (int i = 0; i < SpritesHit.size(); i++) {
					//2) now check for overlap, diagonal so check for x and y. These formulas change every time. For simplcity, attempt to make sure that if there is a gap between the two object, 
					if (SpritesHit[i]->xPos > xPos) { //NEW (CHANGED)
						TempXOverlap = xPos + TILE_WIDTH - SpritesHit[i]->xPos;
					}
					else {
						TempXOverlap = SpritesHit[i]->xPos + TILE_WIDTH - xPos;
					}
					if (SpritesHit[i]->yPos < ObjectSprite->yPos) {
						TempYOverlap = SpritesHit[i]->yPos + TILE_HEIGHT - yPos;
					}
					else {
						TempYOverlap = yPos + TILE_HEIGHT - SpritesHit[i]->yPos;
					}
					//2) if you didn't collide, even if your in the same grid space, then the equation returned negative, or 0 if just barely touching. (butnot collding)
					if ((TempYOverlap < 17 && TempYOverlap > 0) && TempXOverlap < 17 && TempXOverlap > 0) {
						SpriteOverlapX.push_back(SpritesHit[i]);
						SpriteX.push_back(TempXOverlap);
						TempXOverlap = 0;
						TempYOverlap = 0;
					}
				}
			}
			else if (Measure == 14) {
				for (int i = 0; i < SpritesHit.size(); i++) {
					if (SpritesHit[i]->xPos > xPos) { //NEW (CHANGED)
						TempXOverlap = xPos + TILE_WIDTH - SpritesHit[i]->xPos;
					}
					else {
						TempXOverlap = SpritesHit[i]->xPos + TILE_WIDTH - xPos;
					}
					if (SpritesHit[i]->yPos < ObjectSprite->yPos) {
						TempYOverlap = SpritesHit[i]->yPos + TILE_HEIGHT - yPos;
					}
					else {
						TempYOverlap = yPos + TILE_HEIGHT - SpritesHit[i]->yPos;
					}
					//2) if you didn't collide, even if your in the same grid space, then the equation returned negative, or 0 if just barely touching. (butnot collding)
					if ((TempYOverlap < 17 && TempYOverlap > 0) && TempXOverlap < 17 && TempXOverlap > 0) {
						SpriteOverlapX.push_back(SpritesHit[i]);
						SpriteX.push_back(TempXOverlap);
						TempXOverlap = 0;
						TempYOverlap = 0;
					}
				}
			}
		}
		if (Debug) {
			printf("Before Merge:\n");
			printf("SpriteX = {");
			for (auto x : SpriteX) {
				printf("%d, ", SpriteX[x]);
			}
			printf("}\n");
		}
		//Now SpriteX has integers, and SpriteXOverlap has the sprites,
		//sowe must sort them as usual, then select the largest, return the poitner, set the pointer in the XYArr2, and other stuffn' junk.
		MergeSortSpriteCollision2(SpriteOverlapX, SpriteX);
		if (Debug) {
			printf("After Merge:\n");
			printf("SpriteX = {");
			for (auto x : SpriteX) {
				printf("%d, ", SpriteX[x]);
			}
			printf("}\n");
		}


		//WORK - tie collision types, overlap amount, priorities, default on order creation.
		if (SpriteX.size() > 0) {
			if (SpriteX[SpriteOverlapX.size()] > 0) {
				//There is only one diagonal we need to consider
				Edge[0] = SpriteX[SpriteX.size() - 1];
				TempStackable->HitSprites[0] = SpriteOverlapX.back();
			}
			else {
				Edge[0] = 0;
			}
		}
	}


	void JostleY(Sprite* ObjectSprite, int Edge[2], int Measure, XYArr2* TempStackable, int yDist) {
		bool Debug = false;
		int xPos, yPos;
		int x1, x2, y1, y2;

		int TempX2Math, TempY2Math;

		//the 'jostle'
		x1 = ObjectSprite->xPos  ;
		y1 = ObjectSprite->yPos + yDist;
		x2 = ObjectSprite->xPos + TILE_WIDTH;
		y2 = ObjectSprite->yPos + TILE_HEIGHT + yDist;

		//NOTE - gaurds from map/matrix overflow - NEW 8/19 - since I edited it, becaue the moves seem to guard against going out of bounds in the first place, I made it so that this guards the directions, so it's easier to process. Odd behavior is that once the original is adjusted, it stays adjused until the key is pressed again. Don't think I like that. It's stays that way because the =, but I can't just get rid of it. Maybe I'll make a case when it's on vs when it's off the very edge, so that it's only triggered once per button press or something...
		if (true) {
			if (y1 >= (LEVEL_WIDTH - 1) * TILE_HEIGHT) {
				y1 = LEVEL_HEIGHT - 1;
				y2 = y1;
				ObjectSprite->yVec = 0; //NEW - after we tried to jostle, I noted that there is a special bug that happens when your going diagonal into a wall. Because a null is passed for both, it doesn't try to jostle.
				if (Debug || PAUSECOLLISIONJOSTLE[4] == 0) {
					printf("%d", TOTALFRAMECOUNT);
					printf(" Sprite%d can no longer go further down\n", ObjectSprite->OrderCreation + 1);
					PAUSECOLLISIONJOSTLE[4] = 1;
					SDL_Delay(10000);
				}
			} //NOTE - this fix cannot be moved lower, because we need to trigger the jostle initially by setting at least one of the diagonals 'edges' to be not a nullptr, OR just let it slide down the sides of the edge of the map.
			if (y1 <= 0) {
				y1 = 0;
				y2 = y1;
				ObjectSprite->yVec = 0;
				if (Debug || PAUSECOLLISIONJOSTLE[5] == 0) {
					printf("%d", TOTALFRAMECOUNT);
					printf(" Sprite%dcan no longer go further up\n", ObjectSprite->OrderCreation + 1);
					PAUSECOLLISIONJOSTLE[5] = 1;
					SDL_Delay(10000);
				}
			}
			if (x1 >= (LEVEL_WIDTH - 1) * TILE_WIDTH) {
				x1 = LEVEL_WIDTH - 1;
				x2 = x1;
				ObjectSprite->xVec = 0;
				if (Debug || PAUSECOLLISIONJOSTLE[6] == 0) {
					printf("%d", TOTALFRAMECOUNT);
					printf(" Sprite%d can no longer go further right\n", ObjectSprite->OrderCreation + 1);
					PAUSECOLLISIONJOSTLE[6] = 1;
					SDL_Delay(10000);
				}
			}
			if (x1 <= 0) { //NEW - 8/19/21 This is done because the move's already track the bounds of hte level, so here I want to know whether the mod is higher than it should be or the actual position is less (because the mod is not solid enough)
				x1 = 0;
				x2 = x1;
				ObjectSprite->xVec = 0;
				if (Debug || PAUSECOLLISIONJOSTLE[7] == 0) {
					printf("%d", TOTALFRAMECOUNT);
					printf(" Sprite%d can no longer go further left\n", ObjectSprite->OrderCreation + 1);
					PAUSECOLLISIONJOSTLE[7] = 1;
					SDL_Delay(10000);
				}
			}
		}
		//WORK - maybe change measure if this is used to adjust position? 
		xPos = x1; //so we work wit hthe adjusted position of the ObjectSprite
		yPos = y1;
		TempY2Math = y2 - TILE_HEIGHT * (y2 / TILE_HEIGHT); //A = C - B * (C/B)
		TempX2Math = x2 - TILE_WIDTH * (x2 / TILE_WIDTH);
		y1 = y1 / TILE_HEIGHT;
		y2 = y2 / TILE_HEIGHT;
		x1 = x1 / TILE_WIDTH;
		x2 = x2 / TILE_WIDTH;

		//So we don't check further than we want to, and when we don't need to. In these cases, it doens't matter now if we use x1, or x2. For consistency, we use whatever appears the most as appropriate. 
		if (TempX2Math == 0) {
			x2 = x1;
		}
		if (TempY2Math == 0) {
			y2 = y1;
		}

		//Vector that holds the 'area' of overlap - this is to be compared with, and then swapped if one with larger area shows up
		//if tie, look at order creation
		std::vector<Sprite*> SpritesHit = {};
		std::vector<int> SpriteX = {};
		std::vector<int> SpriteY = {};

		std::vector<Sprite*> SpriteOverlapX = {};
		std::vector<Sprite*> SpriteOverlapY = {};

		int TempXOverlap = 0;
		int TempYOverlap = 0;
		//EDIT Switch all ObjextSprite pos' to x1, y1's!

		//direcctionals
		//Get all those possibly hit
		if (true) {
			if (Measure == 9) { //up
				if (Debug) {
					printf("af\n");
				}
				if (TempX2Math == 0) {
					for (int i = 0; i < LM[y1][x1].size(); i++) {
						if (true) {
							if (LM[y1][x1][i]->yPos < yPos) {
								SpritesHit.push_back(LM[y1][x1][i]);
							}
						}
					}
				}
				else {
					for (int i = 0; i < LM[y1][x1].size(); i++) {
						if (true) {
							if (LM[y1][x1][i]->yPos < yPos) {
								SpritesHit.push_back(LM[y1][x1][i]);
							}
						}
					}
					for (int i = 0; i < LM[y1][x2].size(); i++) {
						if (true) {
							if (LM[y1][x2][i]->yPos < yPos) {
								SpritesHit.push_back(LM[y1][x2][i]);
							}
						}
					}
				}
			}
			else if (Measure == 11) { //down
				if (Debug) {
					printf("af\n");
				}
				if (TempX2Math == 0) {
					for (int i = 0; i < LM[y1][x1].size(); i++) {
						if (true) {
							if (LM[y2][x1][i]->yPos > yPos) {
								SpritesHit.push_back(LM[y2][x1][i]);
							}
						}
					}
				}
				else {
					for (int i = 0; i < LM[y2][x1].size(); i++) {
						if (true) {
							if (LM[y2][x1][i]->yPos > yPos) {
								SpritesHit.push_back(LM[y2][x1][i]);
							}
						}
					}
					for (int i = 0; i < LM[y2][x2].size(); i++) {
						if (true) {
							if (LM[y2][x2][i]->yPos > yPos) {
								SpritesHit.push_back(LM[y2][x2][i]);
							}
						}
					}
				}
			}
		}


		//Hit sprites should now have all the sprites to the Y side of travel of the object in question. 

		//Now I have to figure out if there's any  REAL overlap.
		if (true) {
			if (Measure == 9) {
				for (int i = 0; i < SpritesHit.size(); i++) {
					if (SpritesHit[i]->xPos > xPos) { //NEW (CHANGED)
						TempXOverlap = xPos + TILE_WIDTH - SpritesHit[i]->xPos;
					}
					else {
						TempXOverlap = SpritesHit[i]->xPos + TILE_WIDTH - xPos;
					}
					if (SpritesHit[i]->yPos < ObjectSprite->yPos) {
						TempYOverlap = SpritesHit[i]->yPos + TILE_HEIGHT - yPos;
					}
					else {
						TempYOverlap = yPos + TILE_HEIGHT - SpritesHit[i]->yPos;
					}
					//2) if you didn't collide, even if your in the same grid space, then the equation returned negative, or 0 if just barely touching. (butnot collding)
					if ((TempYOverlap < 17 && TempYOverlap > 0) && TempXOverlap < 17 && TempXOverlap > 0) {
						SpriteOverlapY.push_back(SpritesHit[i]);
						SpriteY.push_back(TempYOverlap);
						TempXOverlap = 0;
						TempYOverlap = 0;
					}
				}
			}
			else if (Measure == 11) {
				for (int i = 0; i < SpritesHit.size(); i++) {
					if (SpritesHit[i]->xPos > xPos) { //NEW (CHANGED)
						TempXOverlap = xPos + TILE_WIDTH - SpritesHit[i]->xPos;
					}
					else {
						TempXOverlap = SpritesHit[i]->xPos + TILE_WIDTH - xPos;
					}
					if (SpritesHit[i]->yPos < ObjectSprite->yPos) {
						TempYOverlap = SpritesHit[i]->yPos + TILE_HEIGHT - yPos;
					}
					else {
						TempYOverlap = yPos + TILE_HEIGHT - SpritesHit[i]->yPos;
					}
					//2) if you didn't collide, even if your in the same grid space, then the equation returned negative, or 0 if just barely touching. (butnot collding)
					if ((TempYOverlap < 17 && TempYOverlap > 0) && TempXOverlap < 17 && TempXOverlap > 0) {
						SpriteOverlapY.push_back(SpritesHit[i]);
						SpriteY.push_back(TempYOverlap);
						TempXOverlap = 0;
						TempYOverlap = 0;
					}
				}
			}
		}

		if (Debug) {
			printf("Before Merge:\n");
			printf("SpriteY = {");
			for (auto y : SpriteY) {
				printf("%d, ", SpriteY[y]);
			}
			printf("}\n");
		}
		//Now SpriteX has integers, and SpriteXOverlap has the sprites,
		//sowe must sort them as usual, then select the largest, return the poitner, set the pointer in the XYArr2, and other stuffn' junk.
		MergeSortSpriteCollision2(SpriteOverlapY, SpriteY);
		if (Debug) {
			printf("After Merge:\n");
			printf("SpriteY = {");
			for (auto y : SpriteY) {
				printf("%d, ", SpriteY[y]);
			}
			printf("}\n");
		}


		//WORK - tie collision types, overlap amount, priorities, default on order creation.
		if (SpriteY.size() > 0) {
			if (SpriteY[SpriteOverlapY.size()] > 0) {
				//There is only one diagonal we need to consider
				Edge[1] = SpriteY[SpriteY.size() - 1];
				TempStackable->HitSprites[1] = SpriteOverlapY.back();
			}
			else {
				Edge[1] = 0;
			}
		}
	}

	  
	void JostleD(Sprite* ObjectSprite, int D1[2], int D2[2], int Measure, XYArr2* TempStackable, int xDist, int yDist) {
		bool Debug = false;
		int xPos, yPos;
		int x1, x2, y1, y2;

		int TempX2Math, TempY2Math;

		//the 'jostle'
		x1 = ObjectSprite->xPos + xDist;
		y1 = ObjectSprite->yPos + yDist;
		x2 = ObjectSprite->xPos + TILE_WIDTH + xDist;
		y2 = ObjectSprite->yPos + TILE_HEIGHT + yDist;

		//NOTE - gaurds from map/matrix overflow - NEW 8/19 - since I edited it, becaue the moves seem to guard against going out of bounds in the first place, I made it so that this guards the directions, so it's easier to process. Odd behavior is that once the original is adjusted, it stays adjused until the key is pressed again. Don't think I like that. It's stays that way because the =, but I can't just get rid of it. Maybe I'll make a case when it's on vs when it's off the very edge, so that it's only triggered once per button press or something...
		if (true) {
			if (y1 >= (LEVEL_WIDTH - 1) * TILE_HEIGHT) {
				y1 = LEVEL_HEIGHT - 1;
				y2 = y1;
				ObjectSprite->yVec = 0; //NEW - after we tried to jostle, I noted that there is a special bug that happens when your going diagonal into a wall. Because a null is passed for both, it doesn't try to jostle.
				if (Debug || PAUSECOLLISIONJOSTLE[4] == 0) {
					printf("%d", TOTALFRAMECOUNT);
					printf(" Sprite%d can no longer go further down\n", ObjectSprite->OrderCreation + 1);
					PAUSECOLLISIONJOSTLE[4] = 1;
					SDL_Delay(10000);
				}
			} //NOTE - this fix cannot be moved lower, because we need to trigger the jostle initially by setting at least one of the diagonals 'edges' to be not a nullptr, OR just let it slide down the sides of the edge of the map.
			if (y1 <= 0) {
				y1 = 0;
				y2 = y1;
				ObjectSprite->yVec = 0;
				if (Debug || PAUSECOLLISIONJOSTLE[5] == 0) {
					printf("%d", TOTALFRAMECOUNT);
					printf(" Sprite%dcan no longer go further up\n", ObjectSprite->OrderCreation + 1);
					PAUSECOLLISIONJOSTLE[5] = 1;
					SDL_Delay(10000);
				}
			}
			if (x1 >= (LEVEL_WIDTH - 1) * TILE_WIDTH) {
				x1 = LEVEL_WIDTH - 1;
				x2 = x1;
				ObjectSprite->xVec = 0;
				if (Debug || PAUSECOLLISIONJOSTLE[6] == 0) {
					printf("%d", TOTALFRAMECOUNT);
					printf(" Sprite%d can no longer go further right\n", ObjectSprite->OrderCreation + 1);
					PAUSECOLLISIONJOSTLE[6] = 1;
					SDL_Delay(10000);
				}
			}
			if (x1 <= 0) { //NEW - 8/19/21 This is done because the move's already track the bounds of hte level, so here I want to know whether the mod is higher than it should be or the actual position is less (because the mod is not solid enough)
				x1 = 0;
				x2 = x1;
				ObjectSprite->xVec = 0;
				if (Debug || PAUSECOLLISIONJOSTLE[7] == 0) {
					printf("%d", TOTALFRAMECOUNT);
					printf(" Sprite%d can no longer go further left\n", ObjectSprite->OrderCreation + 1);
					PAUSECOLLISIONJOSTLE[7] = 1;
					SDL_Delay(10000);
				}
			}
		}
		//WORK - maybe change measure if this is used to adjust position? 
		xPos = x1; //so we work wit hthe adjusted position of the ObjectSprite
		yPos = y1;
		TempY2Math = y2 - TILE_HEIGHT * (y2 / TILE_HEIGHT); //A = C - B * (C/B)
		TempX2Math = x2 - TILE_WIDTH * (x2 / TILE_WIDTH);
		y1 = y1 / TILE_HEIGHT;
		y2 = y2 / TILE_HEIGHT;
		x1 = x1 / TILE_WIDTH;
		x2 = x2 / TILE_WIDTH;

		//So we don't check further than we want to, and when we don't need to. In these cases, it doens't matter now if we use x1, or x2. For consistency, we use whatever appears the most as appropriate. 
		if (TempX2Math == 0) {
			x2 = x1;
		}
		if (TempY2Math == 0) {
			y2 = y1;
		}

		//so we're going to have to return two pointers... :/ but each I think still jives with the logic I had. This is if there are two sprites overalpped, such that dy, dx are equal, but from seperate sprites.
		//Sort the list by x, y values. cloest ones to your position (if not your position!)
		//double check that the largest overlap is actually overlap (at least 1 in the other direction)
		//Now sort the list by largest overlap in Y, do the same as above.
		//if largest X and Y do not point to the same object, return two *
		//Else return just the one. 
		//Place the largest X, Y into D[2], if any!



		//Vector that holds the 'area' of overlap - this is to be compared with, and then swapped if one with larger area shows up
		//if tie, look at order creation
		std::vector<Sprite*> SpritesHit = {};
		std::vector<int> SpriteX = {};
		std::vector<int> SpriteY = {};

		std::vector<Sprite*> SpriteOverlapX = {};
		std::vector<Sprite*> SpriteOverlapY = {};

		int TempXOverlap = 0;
		int TempYOverlap = 0;
		//EDIT Switch all ObjextSprite pos' to x1, y1's!

		//diagonals
		//Get all those possibly hit
		if (true) {
			if (Measure == 5) {//UL 
				//Depending on how perfectly inligned with the grid you are, you can skip checking some edges/points.
				if (Debug) {
					printf("a\n");
				}
				for (int i = 0; i < LM[y1][x1].size(); i++) {
					if (LM[y1][x1][i]->xPos < xPos && LM[y1][x1][i]->yPos < yPos) { //NEW (CHANGED)
						SpritesHit.push_back(LM[y1][x1][i]);
					}
				}
			}
			else if (Measure == 13) {//UR 
				if (Debug) {
					printf("i\n");
				}
				for (int i = 0; i < LM[y1][x2].size(); i++) { // first
					if (LM[y1][x2][i]->xPos > xPos && LM[y1][x2][i]->yPos < yPos) { //NEW (CHANGED)
						SpritesHit.push_back(LM[y1][x2][i]);
					}
				}
			}
			else if (Measure == 7) {//DL 
				if (Debug) {
					printf("q\n");
				}
				for (int i = 0; i < LM[y2][x1].size(); i++) { // first
					if (LM[y2][x1][i]->xPos <  xPos && LM[y2][x1][i]->yPos > yPos) { //NEW (CHANGED)
						SpritesHit.push_back(LM[y2][x1][i]);
					}
				}
			}
			else if (Measure == 15) {//DR 
				if (Debug) {
					printf("x\n");
				}
				for (int i = 0; i < LM[y2][x2].size(); i++) { // LL
					if (LM[y2][x2][i]->xPos > xPos && LM[y2][x2][i]->yPos > yPos) { //NEW (CHANGED)
						SpritesHit.push_back(LM[y2][x2][i]);
					}
				}
			}
		}
		//Now we have all possible Sprites we could've hit for that given measure.


		//Now I have to figure out if there's any  REAL overlap.
		if (true) {
			if (Measure == 5) {//UL 
				//Depending on how perfectly inligned with the grid you are, you can skip checking some edges/points.
				if (Debug) {
					printf("a\n");
				}
				for (int i = 0; i < SpritesHit.size(); i++) {
					//2) now check for overlap, diagonal so check for x and y. These formulas change every time. For simplcity, attempt to make sure that if there is a gap between the two object, 
					if (SpritesHit[i]->xPos > xPos) { //NEW (CHANGED)
						TempXOverlap = xPos + TILE_WIDTH - SpritesHit[i]->xPos;
					}
					else {
						TempXOverlap = SpritesHit[i]->xPos + TILE_WIDTH - xPos;
					}
					if (SpritesHit[i]->yPos < ObjectSprite->yPos) {
						TempYOverlap = SpritesHit[i]->yPos + TILE_HEIGHT - yPos;
					}
					else {
						TempYOverlap = yPos + TILE_HEIGHT - SpritesHit[i]->yPos;
					}
					//2) if you didn't collide, even if your in the same grid space, then the equation returned negative, or 0 if just barely touching. (butnot collding)
					if ((TempYOverlap < 17 && TempYOverlap > 0) && TempXOverlap < 17 && TempXOverlap > 0) {
						SpriteOverlapX.push_back(SpritesHit[i]);
						SpriteX.push_back(TempXOverlap);
						SpriteOverlapY.push_back(SpritesHit[i]);
						SpriteY.push_back(TempYOverlap);
						TempXOverlap = 0;
						TempYOverlap = 0;
					}
				}
			}
			else if (Measure == 13) {//UR 
				if (Debug) {
					printf("i\n");
				}
				for (int i = 0; i < SpritesHit.size(); i++) { // first 
					if (SpritesHit[i]->xPos > xPos) {//NEW (CHANGED)
						TempXOverlap = xPos + TILE_WIDTH - SpritesHit[i]->xPos;
					}
					else {
						TempXOverlap = xPos + TILE_WIDTH - xPos;
					}
					if (SpritesHit[i]->yPos < yPos) {
						TempYOverlap = SpritesHit[i]->yPos + TILE_HEIGHT - yPos;
					}
					else {
						TempYOverlap = yPos + TILE_HEIGHT - SpritesHit[i]->yPos;
					}
					if ((TempYOverlap < 17 && TempYOverlap > 0) && TempXOverlap < 17 && TempXOverlap > 0) {
						SpriteOverlapX.push_back(SpritesHit[i]);
						SpriteX.push_back(TempXOverlap);
						SpriteOverlapY.push_back(SpritesHit[i]);
						SpriteY.push_back(TempYOverlap);
						TempXOverlap = 0;
						TempYOverlap = 0;
					}
				}
			}
			else if (Measure == 7) {//DL 
				if (Debug) {
					printf("q\n");
				}
				for (int i = 0; i < SpritesHit.size(); i++) { // first
					if (SpritesHit[i]->xPos > xPos) { //NEW (CHANGED)
						TempXOverlap = xPos + TILE_WIDTH - SpritesHit[i]->xPos;
					}
					else {
						TempXOverlap = SpritesHit[i]->xPos + TILE_WIDTH - xPos;
					}
					if (SpritesHit[i]->yPos > yPos) {
						TempYOverlap = yPos + TILE_HEIGHT - SpritesHit[i]->yPos;
					}
					else {
						TempYOverlap = SpritesHit[i]->yPos + TILE_HEIGHT - yPos;
					}
					if ((TempYOverlap < 17 && TempYOverlap > 0) && TempXOverlap < 17 && TempXOverlap > 0) {
						SpriteOverlapX.push_back(SpritesHit[i]);
						SpriteX.push_back(TempXOverlap);
						SpriteOverlapY.push_back(SpritesHit[i]);
						SpriteY.push_back(TempYOverlap);
						TempXOverlap = 0;
						TempYOverlap = 0;
					}
				}
			}
			else if (Measure == 15) {//DR  if (Debug) {
				if (Debug) {
					printf("x\n");
				}
				for (int i = 0; i < SpritesHit.size(); i++) { // LL
					if (SpritesHit[i]->xPos > xPos) {//NEW (CHANGED)
						TempXOverlap = xPos + TILE_WIDTH - SpritesHit[i]->xPos;
					}
					else {
						TempXOverlap = SpritesHit[i]->xPos + TILE_WIDTH - xPos;
					}
					if (SpritesHit[i]->yPos > yPos) {
						TempYOverlap = yPos + TILE_HEIGHT - SpritesHit[i]->yPos;
					}
					else {
						TempYOverlap = SpritesHit[i]->yPos + TILE_HEIGHT - yPos;
					}
					if ((TempYOverlap < 17 && TempYOverlap > 0) && TempXOverlap < 17 && TempXOverlap > 0) {
						SpriteOverlapX.push_back(SpritesHit[i]);
						SpriteX.push_back(TempXOverlap);
						SpriteOverlapY.push_back(SpritesHit[i]);
						SpriteY.push_back(TempYOverlap);
						TempXOverlap = 0;
						TempYOverlap = 0;
					}
				}
			}
		}



		//Now I want to mergeSort it into SpriteOverlapX and SpriteOverlapY by how 'close' it is, and then sort via order creation.

		//Then, once we sorted it by most aggressive overlap by least, we then want to ensure that it's an actual dimension.

		//Then also mergesort into SpriteOverlapY (again, using SpriteOverlapX, saving the ptr to the largest overlap)
		if (Debug) {
			printf("Before Merge:\n");
			printf("SpriteX = {");
			for (auto x : SpriteX) {
				printf("%d, ", SpriteX[x]);
			}
			printf("}\n");
			printf("SpriteY = {");
			for (auto x : SpriteY) {
				printf("%d, ", SpriteX[x]);
			}
			printf("}\n");
		}

		MergeSortSpriteCollision2(SpriteOverlapX, SpriteX);
		MergeSortSpriteCollision2(SpriteOverlapY, SpriteY);
		if (Debug) {
			printf("After Merge:\n");
			printf("SpriteX = {");
			for (auto x : SpriteX) {
				printf("%d, ", SpriteX[x]);
			}
			printf("}\n");
			printf("SpriteY = {");
			for (auto x : SpriteY) {
				printf("%d, ", SpriteX[x]);
			}
			printf("}\n");
		}


		//Assuming the max overlap is at the back. -this needs to change to consider the collision type, of both, and see if they are same, and itterate independently to get the correct answer.
		if (SpriteX.size() > 0 && SpriteY.size() > 0) {
			if (SpriteOverlapX[SpriteOverlapX.size() - 1] = SpriteOverlapY[SpriteOverlapY.size() - 1]) {
				//There is only one diagonal we need to consider
				D1[0] = SpriteX[SpriteX.size() - 1];
				D1[1] = SpriteY[SpriteY.size() - 1];
			}

			int xItter = SpriteX.size() - 1;
			int yItter = SpriteY.size() - 1;
			bool EarlyBreak1 = false;
			bool EarlyBreak2 = false;
			while ((yItter > -1 && xItter > -1) && (D1[0] == 0 || D1[1] == 0)) {
				if (SpriteOverlapX[xItter]->CollisionType == 1) {
					xItter -= 1;
					//break early
					EarlyBreak1 = true;
				}
				if (SpriteOverlapY[yItter]->CollisionType == 1) {
					yItter -= 1;
					//break early
					EarlyBreak2 = true;
				}




				//WORK - Need  to figure out overlap, then figure out which one has priority 
				//(if there's a tie in either for overlap), then figure out if the same sprite is used. 
				//If theres a tie in collision priority, default to creation order. <-will do later


				if (EarlyBreak1 && EarlyBreak2) {
					//at the end of each of these vectors is the sprite wit hthe most overlap 
					if (SpriteOverlapX[xItter] = SpriteOverlapY[yItter]) {
						//There is only one diagonal we need to consider
						D1[0] = SpriteX[xItter];
						D1[1] = SpriteY[yItter];
						TempStackable->HitSprites[2] = SpriteOverlapX[xItter];
					}
					else {
						//Therea re two idagonals we need to consider - use find to find the overlap, returns itterator, if no element found returns last, but we know it will be there.
						D1[0] = SpriteX[xItter];
						D1[1] = SpriteY[yItter];

						//Find the other two dimensions for later
						for (int x = 0; x < SpriteOverlapX.size(); x++) {
							if (SpriteOverlapX[x] == SpriteOverlapY[yItter]) {
								D2[0] = SpriteX[x];
								break;
							}
						}
						for (int y = 0; y < SpriteOverlapY.size(); y++) {
							if (SpriteOverlapY[y] == SpriteOverlapX[xItter]) {
								D2[1] = SpriteY[y];
								break;
							}
						}

						TempStackable->HitSprites[2] = SpriteOverlapX[xItter];
						TempStackable->HitSprites[3] = SpriteOverlapY[yItter];
					} //So we'll have to check whether there are two collisions to pay attention to or not.
				}
				if (EarlyBreak1 && EarlyBreak2) {
					break;
				}
			}

			 

		}

	}
	
	
	//WORK - figure out when you want to jostle again
	//figure out when we want to update position
	//figure out when we want to stack (or end early)
	//edittravel on successful moves.
	void CheckFuture3(Sprite* ObjectSprite, XYArr2* TempStackable, int Measure) {
		bool Debug = true;
		int Edge[2]; //{x,y}
		int D1[2];
		int D2[2]; //The reason there are two diagonals is that if in some case we perfectly align with two sprites on the diagonal, and they have different axis' max, but equal, then we want to the ake the minimum appropriate values.
		int Final[2]; //the values that matter. Figure out how to move for this
		for (int x = 0; x < 2; x++) {
			Edge[x] = 0;
			D1[x] = 0;
			D2[x] = 0;
			Final[x] = 0;
		}


		//NOTE - the double percentage for now will always result in a rounded down value. Look into using static cast instead of (int)
		//NEW - figure out the jostle distance using rise over run, and the min maximum allowable distance.
		int xDistance = ObjectSprite->ExVel[0];
		int yDistance = ObjectSprite->ExVel[1];
		int NewXDistance, NewYDistance;
		double Percentage=0;
		if (xDistance > yDistance) {
			if (xDistance > TILE_WIDTH) {
				Percentage = TILE_WIDTH / xDistance; //some inconcsistencies will happen here with my current method, but no ones perfect!
				NewXDistance = (int)std::floor(xDistance * Percentage);
				NewYDistance = (int)std::floor(yDistance * Percentage); 
			}
			else {
				NewXDistance = xDistance;
				NewYDistance = yDistance;
			}
		}
		else { //ydistance >= xdistance
			if (yDistance > TILE_HEIGHT) {
				Percentage = TILE_HEIGHT / yDistance; //some inconcsistencies will happen here with my current method, but no ones perfect!
				NewXDistance = (int)std::floor(xDistance * Percentage);
				NewYDistance = (int)std::floor(yDistance * Percentage);
			} 
			else{ 
				NewXDistance = xDistance;
				NewYDistance = yDistance;
			}
		}
		if (Debug) {
			printf("Original ExVel ={%d, %d}\n", ObjectSprite->ExVel[0], ObjectSprite->ExVel[1]); 
			if (NewYDistance != 0 && NewXDistance != 0) {
				Percentage = NewYDistance / NewXDistance;
			} 
			else {
				Percentage = 0;
			}
			printf("Rise overRun = %f\n", Percentage);
			printf("New (temp) ExVel for this Jostle ={%d, %d}\n", NewXDistance, NewYDistance);
			//SDL_Delay(300);
		}

		//INSERT - guard against overflow on matrix here, this avoids adjusting the values multiple times throughout each jostling.

		//figure out direction then send to jostle (appropriately!) 
		TempStackable = new XYArr2;
		TempStackable->CurrentVictim = ObjectSprite;

		//only do the necessary ones //WORK - double check that Edge and D are properlly storing some values when they finish!
		JostleX(ObjectSprite, Edge, Measure, TempStackable, NewXDistance);
		JostleY(ObjectSprite, Edge, Measure, TempStackable, NewYDistance);
		JostleD(ObjectSprite, D1, D2, Measure, TempStackable, NewXDistance, NewYDistance);
		//Edge = {x,y}, D = {Dx, Dy}



		int xPos = ObjectSprite->LastDestination.back()[0];
		int yPos = ObjectSprite->LastDestination.back()[1];
		int x = Edge[0];
		int y = Edge[1];
		int dx = D1[0];
		int dy = D1[1];
		//Figure out How to move - Note the Sprite you choose to run into.
		if (Measure == 5 || Measure == 7 || Measure == 13 || Measure == 15) {
			//Diagonal ONLY
			if (x == 0 || y == 0 && (dx != 0 && dy != 0)) { //Xor gate maybe? on the XY check?
				if (x == 0) {
					if (dy > y) {
						Final[0] = dx;
						Final[1] = y;
						TempStackable->HitSprites[2] = TempStackable->Collisions[2]; //the hit sprite is only equal to whatever you COULD'VE hit.
						TempStackable->HitSprites[1] = TempStackable->Collisions[1];
					}
				}
				if (y == 0) {
					if (dx > x) {
						Final[0] = x;
						Final[1] = dy;
						TempStackable->HitSprites[0] = TempStackable->Collisions[0];
						TempStackable->HitSprites[2] = TempStackable->Collisions[2];
					}
				}
			}
			if (x != 0 && y != 0 && dx != 0 && dy != 0) {
				if (x > dx) {
					Final[0] = x;
					Final[1] = y;
					TempStackable->HitSprites[0] = TempStackable->Collisions[0];
					TempStackable->HitSprites[1] = TempStackable->Collisions[1];
					//exit early if possible
				}
				if (y > dy) {
					Final[0] = x;
					Final[1] = y;
					TempStackable->HitSprites[0] = TempStackable->Collisions[0];
					TempStackable->HitSprites[1] = TempStackable->Collisions[1];
					//Exit early if possible
				}
				if (x == dx && dy == dy) {
					Final[0] = x;
					Final[1] = y;
					TempStackable->HitSprites[0] = TempStackable->Collisions[0];
					TempStackable->HitSprites[1] = TempStackable->Collisions[1];
					TempStackable->HitSprites[2] = TempStackable->Collisions[2];
				}
				if (dy > y && dx > x) {
					Final[0] = dx;
					Final[1] = dy;
					TempStackable->HitSprites[2] = TempStackable->Collisions[2];
				}
			}
			if (x == 0 && y == 0) {
				Final[0] = dx;
				Final[1] = dy;
				TempStackable->HitSprites[2] = TempStackable->Collisions[2];
			}
			if (dx == 0 && dy == 0) {
				Final[0] = x;
				Final[0] = y;
				TempStackable->HitSprites[0] = TempStackable->Collisions[0];
				TempStackable->HitSprites[1] = TempStackable->Collisions[1];
			}
		}
		else {
			//Directional ONLY
			if (x != 0) {
				Final[0] = x;
				TempStackable->HitSprites[0] = TempStackable->Collisions[0];
			}
			if (y != 0) {
				Final[1] = y;
				TempStackable->HitSprites[1] = TempStackable->Collisions[1];
			}
		}
		 



		//NOTE NOTE NOTE - when sliding, and checking if your clear, this is only optimal when you are hitting something that is already complete, OTHERWISE DON'T

		//Figure out How to move - Note the Sprite you choose to run into.
		if (Measure == 5 || Measure == 7 || Measure == 13 || Measure == 15) { //ObjectSprite->LastDestination.push_back({ xPos+NewXDistance, yPos +NewYDistance});
			//Diagonal ONLY
			if (Measure == 15) {
				//{0,y},{dx,dy}
				if (x == 0 && y != 0 && (dx != 0 && dy != 0)) {
					if (y < dy) {
						ObjectSprite->LastDestination.push_back({ xPos + NewXDistance - dx, yPos + NewYDistance - dy }); //this is slightly wrong. we want to glide UNLESS dx==dy
					}
					else if (y == dy) {
						ObjectSprite->LastDestination.push_back({ xPos + NewXDistance, yPos + NewYDistance - y });
					}
					else if (y > dy) {
						ObjectSprite->LastDestination.push_back({ xPos + NewXDistance, yPos + NewYDistance - y });//Check when your clear, so that you can edit y appropriately
					}
				}  
				//{x,0},{dx,dy}
				if (x != 0 && y == 0 && (dx != 0 && dy != 0)) {
					if (x < dx) {
						ObjectSprite->LastDestination.push_back({ xPos + NewXDistance -dx, yPos + NewYDistance -dy }); //See previous
					}
					else if (x == dx) {
						ObjectSprite->LastDestination.push_back({ xPos + NewXDistance -x, yPos + NewYDistance });
					}
					else if (x > dx) {
						ObjectSprite->LastDestination.push_back({ xPos + NewXDistance -x, yPos + NewYDistance }); //Check when your clear, so that you can edit x appropriately
					}

				} 
				//{x,y}, {0,0}
				if (x != 0 && y != 0 && (dx == 0 && dy == 0)) {
					ObjectSprite->LastDestination.push_back({ xPos +NewXDistance-x, yPos+NewYDistance-y });
				}
				//{0,0},{dx, dy}
				if (x == 0 && y == 0 && (dx != 0 && dy != 0)) {
					//slight error here potentially. Check to see if overlap is the same and if so freeze there for a bit.
					 
					//freeze, perfect colllision
					if (dx == dy) {
						ObjectSprite->LastDestination.push_back({ xPos + NewXDistance - dx, yPos + NewYDistance - dy });
					}
					//Tp on the dx, but slide down dy
					else if (dx > dy) {
						ObjectSprite->LastDestination.push_back({ xPos + NewXDistance - x, yPos + NewYDistance - dy });
					}
					//Tp on the dy, but slide down the dx
					else if (dy > dx) {
						ObjectSprite->LastDestination.push_back({ xPos + NewXDistance - dx, yPos + NewYDistance - y });
					}
				}
				//{0,0},{0,0}
				if (x == 0 && y == 0 && dx == 0 && dy == 0) {
					ObjectSprite->LastDestination.push_back({ xPos + NewXDistance, yPos + NewYDistance });
				} 
				//{x,y}{dx,dy}
				if (x != 0 && y != 0 && (dx != 0 && dy != 0)) { 
					if (x >= dx) {
						if (y >= dy) {
							ObjectSprite->LastDestination.push_back({ xPos + NewXDistance-x, yPos + NewYDistance -y});
						}
						else if (y < dy) { //this is because we just slide down the side a small bit away on the x axis from the D. Insert a check to move if you'r free a bit on the x axis. (same as other ones for the same considerations)
							ObjectSprite->LastDestination.push_back({ xPos + NewXDistance -x, yPos + NewYDistance -y });
						}
					}
					else if (y >= dy) {
						if (x >= dx) {
							ObjectSprite->LastDestination.push_back({ xPos + NewXDistance -x, yPos + NewYDistance-y });
						}
						else if (x < dx) {
							ObjectSprite->LastDestination.push_back({ xPos + NewXDistance - x, yPos + NewYDistance - y });
						}
					}
					else if (dx > x && dy > y) { //yoink this code for earlier if statements
						//Like the others, if there is a preference based on the rise over run, implementit here. 
						//Also if it's perfect collision freeze it by default (freeze as in don't slide down a side or something)
					
						//freeze, perfect colllision
						if (dx == dy) { 
							ObjectSprite->LastDestination.push_back({ xPos + NewXDistance -dx, yPos + NewYDistance-dy });
						} 
						//Tp on the dx, but slide down dy
						else if (dx > dy) { 
							ObjectSprite->LastDestination.push_back({ xPos + NewXDistance - x, yPos + NewYDistance - dy });
						} 
						//Tp on the dy, but slide down the dx
						else if (dy >dx) { 
							ObjectSprite->LastDestination.push_back({ xPos + NewXDistance - dx, yPos + NewYDistance - y });
						}
					}
				}
			}
			if (Measure == 13) { //see commments above for fixes
				//{0,y},{dx,dy}
				if (x == 0 && y != 0 && (dx != 0 && dy != 0)) {
					if (y < dy) {
						ObjectSprite->LastDestination.push_back({ xPos + NewXDistance - dx, yPos + NewYDistance + dy });  
					}
					else if (y == dy) {
						ObjectSprite->LastDestination.push_back({ xPos + NewXDistance, yPos + NewYDistance + y });
					}
					else if (y > dy) {
						ObjectSprite->LastDestination.push_back({ xPos + NewXDistance, yPos + NewYDistance + y }); 
					}
				}
				//{x,0},{dx,dy}
				if (x != 0 && y == 0 && (dx != 0 && dy != 0)) {
					if (x < dx) {
						ObjectSprite->LastDestination.push_back({ xPos + NewXDistance - dx, yPos + NewYDistance + dy });  
					}
					else if (x == dx) {
						ObjectSprite->LastDestination.push_back({ xPos + NewXDistance - x, yPos + NewYDistance });
					}
					else if (x > dx) {
						ObjectSprite->LastDestination.push_back({ xPos + NewXDistance - x, yPos + NewYDistance }); 
					}

				}
				//{x,y}, {0,0}
				if (x != 0 && y != 0 && (dx == 0 && dy == 0)) {
					ObjectSprite->LastDestination.push_back({ xPos + NewXDistance - x, yPos + NewYDistance + y });
				}
				//{0,0},{dx, dy}
				if (x == 0 && y == 0 && (dx != 0 && dy != 0)) {  //slight error here potentially. Check to see if overlap is the same and if so freeze there for a bit.
				
				//freeze, perfect colllision
					if (dx == dy) {
						ObjectSprite->LastDestination.push_back({ xPos + NewXDistance - dx, yPos + NewYDistance + dy });
					}
					//Tp on the dx, but slide down dy
					else if (dx > dy) {
						ObjectSprite->LastDestination.push_back({ xPos + NewXDistance - x, yPos + NewYDistance + dy });
					}
					//Tp on the dy, but slide down the dx
					else if (dy > dx) {
						ObjectSprite->LastDestination.push_back({ xPos + NewXDistance - dx, yPos + NewYDistance + y });
					}
				}
				//{0,0},{0,0}
				if (x == 0 && y == 0 && dx == 0 && dy == 0) {
					ObjectSprite->LastDestination.push_back({ xPos + NewXDistance, yPos + NewYDistance });
				}
				//{x,y}{dx,dy}
				if (x != 0 && y != 0 && (dx != 0 && dy != 0)) {
					if (x >= dx) {
						if (y >= dy) {
							ObjectSprite->LastDestination.push_back({ xPos + NewXDistance - x, yPos + NewYDistance + y });
						}
						else if (y < dy) { //this is because we just slide down the side a small bit away on the x axis from the D. Insert a check to move if you'r free a bit on the x axis. (same as other ones for the same considerations)
							ObjectSprite->LastDestination.push_back({ xPos + NewXDistance - x, yPos + NewYDistance + y });
						}
					}
					else if (y >= dy) {
						if (x >= dx) {
							ObjectSprite->LastDestination.push_back({ xPos + NewXDistance - x, yPos + NewYDistance + y });
						}
						else if (x < dx) {
							ObjectSprite->LastDestination.push_back({ xPos + NewXDistance - x, yPos + NewYDistance + y });
						}
					}
					else if (dx > x && dy > y) { //yoink this code for earlier if statements
						//Like the others, if there is a preference based on the rise over run, implementit here. 
						//Also if it's perfect collision freeze it by default (freeze as in don't slide down a side or something)

						//freeze, perfect colllision
						if (dx == dy) {
							ObjectSprite->LastDestination.push_back({ xPos + NewXDistance - dx, yPos + NewYDistance + dy });
						}
						//Tp on the dx, but slide down dy
						else if (dx > dy) {
							ObjectSprite->LastDestination.push_back({ xPos + NewXDistance - x, yPos + NewYDistance + dy });
						}
						//Tp on the dy, but slide down the dx
						else if (dy > dx) {
							ObjectSprite->LastDestination.push_back({ xPos + NewXDistance - dx, yPos + NewYDistance + y });
						}
					}
				}
			}
			if (Measure == 5) { //see commments above for fixes
				//{0,y},{dx,dy}
				if (x == 0 && y != 0 && (dx != 0 && dy != 0)) {
					if (y < dy) {
						ObjectSprite->LastDestination.push_back({ xPos + NewXDistance + dx, yPos + NewYDistance + dy });
					}
					else if (y == dy) {
						ObjectSprite->LastDestination.push_back({ xPos + NewXDistance, yPos + NewYDistance + y });
					}
					else if (y > dy) {
						ObjectSprite->LastDestination.push_back({ xPos + NewXDistance, yPos + NewYDistance + y });
					}
				}
				//{x,0},{dx,dy}
				if (x != 0 && y == 0 && (dx != 0 && dy != 0)) {
					if (x < dx) {
						ObjectSprite->LastDestination.push_back({ xPos + NewXDistance + dx, yPos + NewYDistance + dy });
					}
					else if (x == dx) {
						ObjectSprite->LastDestination.push_back({ xPos + NewXDistance + x, yPos + NewYDistance });
					}
					else if (x > dx) {
						ObjectSprite->LastDestination.push_back({ xPos + NewXDistance + x, yPos + NewYDistance });
					}

				}
				//{x,y}, {0,0}
				if (x != 0 && y != 0 && (dx == 0 && dy == 0)) {
					ObjectSprite->LastDestination.push_back({ xPos + NewXDistance + x, yPos + NewYDistance + y });
				}
				//{0,0},{dx, dy}
				if (x == 0 && y == 0 && (dx != 0 && dy != 0)) { //slight error here potentially. Check to see if overlap is the same and if so freeze there for a bit.

					//freeze, perfect colllision
					if (dx == dy) {
						ObjectSprite->LastDestination.push_back({ xPos + NewXDistance + dx, yPos + NewYDistance + dy });
					}
					//Tp on the dx, but slide down dy
					else if (dx > dy) {
						ObjectSprite->LastDestination.push_back({ xPos + NewXDistance + x, yPos + NewYDistance + dy });
					}
					//Tp on the dy, but slide down the dx
					else if (dy > dx) {
						ObjectSprite->LastDestination.push_back({ xPos + NewXDistance + dx, yPos + NewYDistance + y });
					}
				}
				//{0,0},{0,0}
				if (x == 0 && y == 0 && dx == 0 && dy == 0) {
					ObjectSprite->LastDestination.push_back({ xPos + NewXDistance, yPos + NewYDistance });
				}
				//{x,y}{dx,dy}
				if (x != 0 && y != 0 && (dx != 0 && dy != 0)) {
					if (x >= dx) {
						if (y >= dy) {
							ObjectSprite->LastDestination.push_back({ xPos + NewXDistance + x, yPos + NewYDistance + y });
						}
						else if (y < dy) { //this is because we just slide down the side a small bit away on the x axis from the D. Insert a check to move if you'r free a bit on the x axis. (same as other ones for the same considerations)
							ObjectSprite->LastDestination.push_back({ xPos + NewXDistance + x, yPos + NewYDistance + y });
						}
					}
					else if (y >= dy) {
						if (x >= dx) {
							ObjectSprite->LastDestination.push_back({ xPos + NewXDistance + x, yPos + NewYDistance + y });
						}
						else if (x < dx) {
							ObjectSprite->LastDestination.push_back({ xPos + NewXDistance + x, yPos + NewYDistance + y });
						}
					}
					else if (dx > x && dy > y) { //yoink this code for earlier if statements
						//Like the others, if there is a preference based on the rise over run, implementit here. 
						//Also if it's perfect collision freeze it by default (freeze as in don't slide down a side or something)

						//freeze, perfect colllision
						if (dx == dy) {
							ObjectSprite->LastDestination.push_back({ xPos + NewXDistance + dx, yPos + NewYDistance + dy });
						}
						//Tp on the dx, but slide down dy
						else if (dx > dy) {
							ObjectSprite->LastDestination.push_back({ xPos + NewXDistance + x, yPos + NewYDistance + dy });
						}
						//Tp on the dy, but slide down the dx
						else if (dy > dx) {
							ObjectSprite->LastDestination.push_back({ xPos + NewXDistance + dx, yPos + NewYDistance + y });
						}
					}
				}
			}
			if (Measure == 7) {
				//{0,y},{dx,dy}
				if (x == 0 && y != 0 && (dx != 0 && dy != 0)) {
					if (y < dy) {
						ObjectSprite->LastDestination.push_back({ xPos + NewXDistance + dx, yPos + NewYDistance - dy }); //this is slightly wrong. we want to glide UNLESS dx==dy
					}
					else if (y == dy) {
						ObjectSprite->LastDestination.push_back({ xPos + NewXDistance, yPos + NewYDistance - y });
					}
					else if (y > dy) {
						ObjectSprite->LastDestination.push_back({ xPos + NewXDistance, yPos + NewYDistance - y });//Check when your clear, so that you can edit y appropriately
					}
				}
				//{x,0},{dx,dy}
				if (x != 0 && y == 0 && (dx != 0 && dy != 0)) {
					if (x < dx) {
						ObjectSprite->LastDestination.push_back({ xPos + NewXDistance + dx, yPos + NewYDistance - dy }); //See previous
					}
					else if (x == dx) {
						ObjectSprite->LastDestination.push_back({ xPos + NewXDistance + x, yPos + NewYDistance });
					}
					else if (x > dx) {
						ObjectSprite->LastDestination.push_back({ xPos + NewXDistance + x, yPos + NewYDistance }); //Check when your clear, so that you can edit x appropriately
					}

				}
				//{x,y}, {0,0}
				if (x != 0 && y != 0 && (dx == 0 && dy == 0)) {
					ObjectSprite->LastDestination.push_back({ xPos + NewXDistance + x, yPos + NewYDistance - y });
				}
				//{0,0},{dx, dy}
				if (x == 0 && y == 0 && (dx != 0 && dy != 0)) {  //slight error here potentially. Check to see if overlap is the same and if so freeze there for a bit.
					
					//freeze, perfect colllision
					if (dx == dy) {
						ObjectSprite->LastDestination.push_back({ xPos + NewXDistance + dx, yPos + NewYDistance - dy });
					}
					//Tp on the dx, but slide down dy
					else if (dx > dy) {
						ObjectSprite->LastDestination.push_back({ xPos + NewXDistance + x, yPos + NewYDistance - dy });
					}
					//Tp on the dy, but slide down the dx
					else if (dy > dx) {
						ObjectSprite->LastDestination.push_back({ xPos + NewXDistance + dx, yPos + NewYDistance - y });
					}
				}
				//{0,0},{0,0}
				if (x == 0 && y == 0 && dx == 0 && dy == 0) {
					ObjectSprite->LastDestination.push_back({ xPos + NewXDistance, yPos + NewYDistance });
				}
				//{x,y}{dx,dy}
				if (x != 0 && y != 0 && (dx != 0 && dy != 0)) {
					if (x >= dx) {
						if (y >= dy) {
							ObjectSprite->LastDestination.push_back({ xPos + NewXDistance + x, yPos + NewYDistance - y });
						}
						else if (y < dy) { //this is because we just slide down the side a small bit away on the x axis from the D. Insert a check to move if you'r free a bit on the x axis. (same as other ones for the same considerations)
							ObjectSprite->LastDestination.push_back({ xPos + NewXDistance + x, yPos + NewYDistance - y });
						}
					}
					else if (y >= dy) {
						if (x >= dx) {
							ObjectSprite->LastDestination.push_back({ xPos + NewXDistance + x, yPos + NewYDistance - y });
						}
						else if (x < dx) {
							ObjectSprite->LastDestination.push_back({ xPos + NewXDistance + x, yPos + NewYDistance - y });
						}
					}
					else if (dx > x && dy > y) { //yoink this code for earlier if statements
						//Like the others, if there is a preference based on the rise over run, implementit here. 
						//Also if it's perfect collision freeze it by default (freeze as in don't slide down a side or something)

						//freeze, perfect colllision
						if (dx == dy) {
							ObjectSprite->LastDestination.push_back({ xPos + NewXDistance + dx, yPos + NewYDistance - dy });
						}
						//Tp on the dx, but slide down dy
						else if (dx > dy) {
							ObjectSprite->LastDestination.push_back({ xPos + NewXDistance + x, yPos + NewYDistance - dy });
						}
						//Tp on the dy, but slide down the dx
						else if (dy > dx) {
							ObjectSprite->LastDestination.push_back({ xPos + NewXDistance + dx, yPos + NewYDistance - y });
						}
					}
				}
			}
		}
		else {//ObjectSprite->LastDestination.push_back({ xPos+NewXDistance, yPos +NewYDistance});
	
			//Directional ONLY
			if (Measure == 6) {
				if (x != 0) {
					ObjectSprite->LastDestination.push_back({ xPos + NewXDistance+x, yPos + NewYDistance });
				}
				else  {
					ObjectSprite->LastDestination.push_back({ xPos + NewXDistance, yPos + NewYDistance });
				}
			}
			else if (Measure == 14) {
				if (x != 0) {
					ObjectSprite->LastDestination.push_back({ xPos + NewXDistance -x, yPos + NewYDistance });
				}
				else {
					ObjectSprite->LastDestination.push_back({ xPos + NewXDistance, yPos + NewYDistance });
				}
			}
			else if (Measure == 9) {
				 
				if (y != 0) {
					ObjectSprite->LastDestination.push_back({ xPos + NewXDistance+y, yPos + NewYDistance });
				}
				else {
					ObjectSprite->LastDestination.push_back({ xPos + NewXDistance, yPos + NewYDistance });
				}
			}
			else if (Measure == 11) {
				if (y != 0) {
					ObjectSprite->LastDestination.push_back({ xPos + NewXDistance -y, yPos + NewYDistance });
				}
				else {
					ObjectSprite->LastDestination.push_back({ xPos + NewXDistance, yPos + NewYDistance });
				}
			}
		}




		//WORK
		//use rise over run, keep axis movements the same (for each axis, but can be independent amounts between x and y) and then compare.
		// 
		//x>=dx, treat it as just sliding on x
		//y>=dy, treat it as just slding on y
		//if x,y, if either is greater than the diagonal, then take x and y





		//WORK - figure out how to move now that we have Edge, Greater Diagonal, Lesser Diagonal overlaps,
		
		//dobule check this, but I think we'll update the last position to it's 'Final' and then deal with the stack, and the teleport when we get tothe main function.
		//We only figure out the final in the check future, since it's 'predicting' the future. The teleport and stack handling happens back in the MoveAllSprites3.
		//should update travel based on the EXVel that we're able to move in. For now, let's only remove the ones we are capable of moving in the direction of (moveAllSprites3).
		//then update FinalDestination


		if (Debug) {
			TempStackable->D1[0] = D1[0];
			TempStackable->D2[1] = D1[1];
			TempStackable->D1[0] = D2[0];
			TempStackable->D2[1] = D2[1];
			TempStackable->Edge[0] = Edge[0];
			TempStackable->Edge[1] = Edge[1];
			TempStackable->Final[0] = Final[0];
			TempStackable->Final[1] = Final[1];
		}

		TempStackable->XCollision = Final[0];
		TempStackable->YCollision = Final[1];

		//TempStackable
		//Up to 3 Sprite*'s for things we WOULD hit if moving to that position.
		//Up to 2 integers, for the 'safe' position to TP


	};


	//WORK - Change behavior to just edit vec each frame, without touching position!
	void MoveAllSprites3() {
		bool Debug = true;
		if (Debug) {
			printf("MoveAll3\n");
		}
		std::vector<XYArr2*> SpriteStacks = {}; //hold each XYArr with information
		int SpriteStacksCounter; //keeps track of something I forgot XD, maybe the current position when handling
		XYArr2* TempStackable; //Holds the possible collision information
		std::vector<int> CompletedSprites;
		//Marking good moves/finished stops.
		
		CompletedSprites.resize(Queue2.size()); //this way we can simply insert to this a null or a poitner if worked.
		for (auto x : CompletedSprites) {
			CompletedSprites[x] = 0;
		}
		int Completed = 0; //NEW used to reduce repetition, and allow jostling to finish before compeltely ending. 

		if (Debug) {
			printf("Completed initial variables for MoveAll3\n");
		}

		//make sure first time program opens CheckOverlap2 is read before hand!

		while (Completed < AllSprites.size()) {
			if (Debug) {
				printf("Completed<AllSprites.size()\n");
			}
			for (int i = 0; i < AllSprites.size(); i++) {
				if (Debug) {
					printf("For AllSprites \n");
				}
				if (CompletedSprites[i] == 0) { //If a sprite is not finished
					if (Debug) {
						printf("CheckOverlap2\n");
					}

					//CheckOverlap2, CheckOverlapSTART2 <-NOTE, for now I'm storing all the sucessful end destinations, then erasing them all at the end of the Que handling. - however we may only ever need to store the most recent successful destination, or the last two.
					if (i == 0) {
						for (int s = 0; s <  AllSprites.size(); s++) {
							 CheckOverlapSTART2(AllSprites[s]); //presets the last destination, so taht it'll always work from the get go.
							//at the end of handlingthe stack, we should ensure that the last successsful destination is set totheir current position, or do so at the start of the functioneach time, besides through checkoverlap. maybe it's unnecessary to call here.. :/
						}
					}
					else {
						CheckOverlap2(AllSprites[i]); //Sets Extravel, exVec, and the Contort variables. For now just ExTravel and exVec
					}


					if (Debug) {
						printf("RemoveSpriteFromMap2\n");
					}
					RemoveSpriteFromMap2(AllSprites[i]); //WORK - make a second one, based on last viable position.
					if (Debug) {
						printf("Figure out the direction\n");
					}
					//find the direction
					int Measure = 0;
					if (true) {
						if (AllSprites[i]->ExVel[0] > 0 && AllSprites[i]->ExVel[1] > 0) { //DR
							Measure = 15;
						}
						else if (AllSprites[i]->ExVel[0] < 0 && AllSprites[i]->ExVel[1] < 0) { //UL
							Measure = 5;
						}
						else if (AllSprites[i]->ExVel[0] > 0 && AllSprites[i]->ExVel[1] < 0) { //UR
							Measure = 13;
						}
						else if (AllSprites[i]->ExVel[0] < 0 && AllSprites[i]->ExVel[1] > 0) { //DL
							Measure = 7;
						}
						else if (AllSprites[i]->ExVel[0] > 0) { //Right
							Measure = 14;
						}
						else if (AllSprites[i]->ExVel[0] < 0) { //Left
							Measure = 6;
						}
						else if (AllSprites[i]->ExVel[1] > 0) {//Down
							Measure = 11;
						}
						else if (AllSprites[i]->ExVel[1] < 0) { //Up
							Measure = 9;
						}
						else {
							Measure = 10;
						}
					}
					if (Debug) {
						printf("New TempStackable\n");
					}

					TempStackable = new XYArr2;
					TempStackable->CurrentVictim = AllSprites[i]; //purely for the debug purposes. Shouldn't have t oeven make one until it's required.
					if (Debug) {
						printf("CheckFuture3\n");
					}

					CheckFuture3(AllSprites[i], TempStackable, Measure);
					if (Debug) {
						printf("\n_______________________________\n");
						printf("|TempStackable:                 |\n");
						printf("|CurrentVictim = Object%d        |\n", TempStackable->CurrentVictim->OrderCreation + 1);
						if (TempStackable->HitSprites[0] != nullptr) {
							printf("|HitSprite X: Object%d          |\n", TempStackable->HitSprites[0]->OrderCreation + 1);
						}
						else {
							printf("|HitSprite X:                   |\n");
						}
						if (TempStackable->HitSprites[1] != nullptr) {
							printf("|HitSprite Y: Object%d          |\n", TempStackable->HitSprites[0]->OrderCreation + 1);
						}
						else {
							printf("|HitSprite Y:                   |\n");
						}
						if (TempStackable->HitSprites[2] != nullptr) {
							printf("|HitSprite Greater D: Object%d  |\n", TempStackable->HitSprites[0]->OrderCreation + 1);
						}
						else {
							printf("|HitSprite Greater D:           |\n");
						}
						if (TempStackable->HitSprites[3] != nullptr) {
							printf("|HitSprite Lesser D: Object%d   |\n", TempStackable->HitSprites[0]->OrderCreation + 1);
						}
						else {
							printf("|HitSprite Lesser D:            |\n");
						}
						printf("|E={%d, %d}                       |\n", TempStackable->Edge[0], TempStackable->Edge[1]);
						printf("|D1={%d, %d}                      |\n", TempStackable->D1[0], TempStackable->D1[1]);
						printf("|D2={%d, %d}                      |\n", TempStackable->D2[0], TempStackable->D2[1]);
						printf("|F={%d, %d}                       |\n", TempStackable->Final[0], TempStackable->Final[1]);
						printf("_______________________________\n\n");
					}


					ReMapSprite2(AllSprites[i]);
					//if all HitCollision is compelte, or nothing, update Latest 'viable positoin'.
					//then pause, 
					//if Travel is empty, then mark as completed.
					//remap (based on last viable position) 
					//If you updated viable position, push self to stack, Search the stack, remove any children, investigate, handle victim list
					if (Debug) {
						printf("That's all\n");
					}
				}
			}
			if (Debug) {
				printf("\n\n\nFinished AllSprite for loop\n");
				printf("For now itterate completed\n\n\n"); 
				Completed =AllSprites.size();
				for (int i = 0; i < AllSprites.size(); i++) {
					AllSprites[i]->xPos = AllSprites[i]->LastDestination.back()[0];
					AllSprites[i]->yPos = AllSprites[i]->LastDestination.back()[1];
					AllSprites[i]->LastDestination.clear();
				}
			}
		}
	}


	void RemoveSpriteFromMap2(Sprite* ObjectSprite) {
		// printf("RemoveSpriteFromMap\n");
		bool Debug = true;
		if (Debug) {
			 printf("RemoveSpriteFromMap2, Object%d\n", ObjectSprite->OrderCreation + 1); 
		}
		int x1 = NULL;
		int x2 = NULL;
		int y1 = NULL;
		int y2 = NULL;

		x1 = ObjectSprite->LastDestination.back()[0];
		x2 = ObjectSprite->LastDestination.back()[0]+TILE_WIDTH;
		y1 = ObjectSprite->LastDestination.back()[1];
		y2 = ObjectSprite->LastDestination.back()[1]+TILE_HEIGHT;


		//NOTE - YOU CANT RELY on the first in order going first, this is because A may be blocked by G, so G resolves first, but if they are on the same 'tile' then A is the begiing of hte vector, which gets stupid after a while, because you move without knowing if G got out of the way.
		int TempY2Math = y2 - TILE_HEIGHT * (y2 / TILE_HEIGHT); //A = C - B * (C/B)
		int TempX2Math = x2 - TILE_WIDTH * (x2 / TILE_WIDTH); //A = C - B * (C/B)
		if (TempX2Math == 0) {
			x2 = x1;
		}
		if (TempY2Math == 0) {
			y2 = y1;
		}


		x1 = x1 / TILE_WIDTH; //saves an small amount of comuptation
		x2 = x2 / TILE_WIDTH;
		y1 = y1 / TILE_HEIGHT;
		y2 = y2 / TILE_HEIGHT;
		//gaurds from map/matrix overflow
		if (y1 > LEVEL_HEIGHT - 1) {
			y1 = LEVEL_HEIGHT - 1;
			y2 = y1;
		}
		if (y1 < 0) {
			y1 = 0;
			y2 = y1;
		}
		if (x1 > LEVEL_WIDTH - 1) {
			x1 = LEVEL_WIDTH - 1;
			x2 = x1;
		}
		if (x1 < 0) {
			x1 = 0;
			x2 = x1;
		}
		if (Debug) {
			printf("Finished Initial variables for RemoveSprite2\n"); 
			printf("%d %d %d %d\n", x1, x2, y1, y2);
		}

		//find, if it doesn't find the item,  returns the LAST element of the vector. CAREFUL - this was a major error thattook us a while to find. you'd think find would return null or end() when it fails.
		
		
		if (true) {
			if (Debug) {
				printf("Erasing Object%d, from UL", ObjectSprite->OrderCreation + 1);
			}
			LM[y1][x1].erase(find(LM[y1][x1].begin(), LM[y1][x1].end() - 1, ObjectSprite));
		}
		if (x1 != x2) {
			if (Debug) {
				printf("Erasing Object%d, from UR", ObjectSprite->OrderCreation + 1);
			}
			LM[y1][x2].erase(find(LM[y1][x2].begin(), LM[y1][x2].end() - 1, ObjectSprite));
		}
		if (y1 != y2) {
			if (Debug) {
				printf("Erasing Object%d, from LL", ObjectSprite->OrderCreation + 1);
			}
			LM[y2][x1].erase(find(LM[y2][x1].begin(), LM[y2][x1].end() - 1, ObjectSprite));
			if (x1 != x2) {
				if (Debug) {
					printf("Erasing Object%d, from LR", ObjectSprite->OrderCreation + 1);
				}
				LM[y2][x2].erase(find(LM[y2][x2].begin(), LM[y2][x2].end() - 1, ObjectSprite));
			}

		}
		if (Debug) {
			printf("Finished removing Sprite from LM Matrix\n");
		}

		// printf("Erased all\n");
	}
	 

	//list, 
	//mergesort for checkfuture
	//other two checkfuture cases
	//update XYArr2 for the two diagonal case
	//Make Remap2 for Viableposition based.
	//handle victim, 
	//Also, I'd like to have the vector of overlapped sprites available to the program somehow. 

	 


	 





};