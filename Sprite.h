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
	int Measure = 10; //default movement is still. 
	int Completed = 0; //lets us know the status of it's movement in the que
	bool InStack = false;



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
	int XCollision=0; //might want int
	int YCollision=0; //might want int
	Sprite* Collisions[4] = { nullptr, nullptr, nullptr, nullptr }; //x, y, d1, d2 cases. (what you could be overlapping
	Sprite* HitSprites[4] = { nullptr, nullptr, nullptr, nullptr }; //what you actually hit/overlap with when calcualted. (x, y, d1, d2) -where d1 and d2 are seperated because of the possible ties and such that cause additional considerations. 
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
	} //see if we can remove it later.

	void ResetTempStackable(XYArr2* TempStackable) {
		TempStackable->D1[0] = 0;
		TempStackable->D1[1] = 0;
		TempStackable->D2[0] = 0;
		TempStackable->D2[1] = 0;
		TempStackable->Edge[0] = 0;
		TempStackable->Edge[1] = 0;
		TempStackable->Final[0] = 0;
		TempStackable->Final[1] = 0;
		TempStackable->XCollision = 0;
		TempStackable->YCollision = 0;
		for (int i = 0; i < 4; i++) {
			TempStackable->HitSprites[i] = nullptr ;
			TempStackable->Collisions[i] = nullptr;
		}
	}
	void SetTempStackableDebugInfo(XYArr2* TempStackable, int D1[], int D2[], int Edge[], int Final[]) {
		TempStackable->D1[0] = D1[0];
		TempStackable->D1[1] = D1[1];
		TempStackable->D2[0] = D2[0];
		TempStackable->D2[1] = D2[1];
		TempStackable->Edge[0] = Edge[0];
		TempStackable->Edge[1] = Edge[1];
		TempStackable->Final[0] = Final[0];
		TempStackable->Final[1] = Final[1];
		TempStackable->XCollision = Final[0];
		TempStackable->YCollision = Final[1];
	}
	int CheckOverlapSTART2(Sprite* ObjectSprite) {
		bool Debug = false;
		if (TOTALFRAMECOUNT > 120000) {
			Debug = false;
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

					SDL_Delay(2000);
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

						SDL_Delay(2000);
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

						SDL_Delay(2000);
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

							SDL_Delay(2000);
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
		bool Debug = false;
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
		Debug = false;

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

					SDL_Delay(2000);
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

						SDL_Delay(2000);
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

						SDL_Delay(2000);
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
							SDL_Delay(2000);
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
				SDL_Delay(2000);
			}
			return 1;
		}
		if (Debug) {
			printf("overlapped with nothing\n");
		}
		return 0;

	}
	
	
	//Goes into LM, figures out the one closest to your travel path, returns it, and figures out appropriate overlap value.
	void JostleX(Sprite* ObjectSprite, int* Edge , int Measure, XYArr2*& TempStackable, int xDist) {
		bool Debug = true;
		int xPos, yPos;
		int x1, x2, y1, y2;

		int TempX2Math, TempY2Math;

		//the 'jostle'
		x1 = ObjectSprite->LastDestination.back()[0] +  xDist;
		y1 = ObjectSprite->LastDestination.back()[1];
		x2 = ObjectSprite->LastDestination.back()[0] + TILE_WIDTH +  xDist;
		y2 = ObjectSprite->LastDestination.back()[1] + TILE_HEIGHT;
		if (Debug) {
			printf("LastPos = {%d, %d}\n", TempStackable->CurrentVictim->LastDestination.back()[0], TempStackable->CurrentVictim->LastDestination.back()[1]);
			printf("LastPos = {%d, %d}\n", x1, y1);
		}
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
							if (LM[y1][x1][i]->xPos +TILE_WIDTH > xPos) {
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
							if (LM[y1][x1][i]->xPos + TILE_WIDTH > xPos) { //NEW (CHANGED)
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
							if (LM[y2][x1][i]->xPos + TILE_WIDTH > xPos) { //NEW (CHANGED)
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
							if (LM[y1][x2][i]->xPos < xPos + TILE_WIDTH) { //NEW (CHANGED)
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
							if (LM[y1][x2][i]->xPos < xPos + TILE_WIDTH) {//NEW (CHANGED)
								SpritesHit.push_back(LM[y1][x2][i]);

							}
						}
					}
					if (Debug) {
						printf("ak\n");
					}
					for (int i = 0; i < LM[y2][x2].size(); i++) {
						if (true) {
							if (LM[y2][x2][i]->xPos < xPos + TILE_WIDTH) {//NEW (CHANGED)
								SpritesHit.push_back(LM[y2][x2][i]);
							}
						}
					}
				}
			}
		}
		//Hit sprites should now have all the sprites to the X side of travel of the object in question. 
		if (Debug) {
			for (int hs = 0; hs < SpritesHit.size(); hs++) {
				printf("HS[%d] = Object%d\n", hs, SpritesHit[hs]->OrderCreation + 1);
			}
		}

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
					 
					TempYOverlap = SpritesHit[i]->yPos + TILE_HEIGHT - yPos;
					 
					if (TempYOverlap < 0 || TempYOverlap>16) {
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
					TempYOverlap = SpritesHit[i]->yPos + TILE_HEIGHT - yPos;
					if (TempYOverlap < 0 || TempYOverlap>16) {
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
			if (SpriteX.size() > 0) {
				for (int x = 0; x < SpriteX.size(); x++) {
					printf("%d, ", SpriteX[x]);
				}
			}
			printf("}\n");
		}
		//Now SpriteX has integers, and SpriteXOverlap has the sprites,
		//sowe must sort them as usual, then select the largest, return the poitner, set the pointer in the XYArr2, and other stuffn' junk.
		MergeSortSpriteCollision2(SpriteOverlapX, SpriteX);
		if (Debug) {
			printf("After Merge:\n");
			printf("SpriteX = {");
			if (SpriteX.size() > 0) {
				for (int x = 0; x < SpriteX.size(); x++) {
					printf("%d, ", SpriteX[x]);
				}
			}
			printf("}\n");
		}


		//WORK - tie collision types, overlap amount, priorities, default on order creation.
		if (SpriteX.size() > 0) {
			if (SpriteX[SpriteX.size()-1] > 0) {
				//There is only one diagonal we need to consider
				Edge[0] = SpriteX[SpriteX.size() - 1];
				TempStackable->HitSprites[0] = SpriteOverlapX.back();
			}
			else {
				Edge[0] = 0;
			}
		}
	}


	void JostleY(Sprite* ObjectSprite, int* Edge, int Measure, XYArr2*& TempStackable, int yDist) {
		bool Debug = true;
		int xPos, yPos;
		int x1, x2, y1, y2;

		int TempX2Math, TempY2Math;

		//the 'jostle'
		x1 = ObjectSprite->LastDestination.back()[0];
		y1 = ObjectSprite->LastDestination.back()[1] + yDist;
		x2 = ObjectSprite->LastDestination.back()[0] + TILE_WIDTH;
		y2 = ObjectSprite->LastDestination.back()[1] + TILE_HEIGHT + yDist;
		 
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
		
		if (Debug) { //accouting for map changes perhaps
			printf("LastPos = {%d, %d}\n", TempStackable->CurrentVictim->LastDestination.back()[0], TempStackable->CurrentVictim->LastDestination.back()[1]);
			printf("New Des = {%d, %d}\n", x1, y1);
		}
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
					printf("up\n");
				}
				if (TempX2Math == 0) {
					for (int i = 0; i < LM[y1][x1].size(); i++) {
						if (true) {
							if (LM[y1][x1][i]->yPos + TILE_HEIGHT > yPos) {
								SpritesHit.push_back(LM[y1][x1][i]);
							}
						}
					}
				}
				else {
					for (int i = 0; i < LM[y1][x1].size(); i++) {
						if (true) {
							if (LM[y1][x1][i]->yPos + TILE_HEIGHT > yPos) {
								SpritesHit.push_back(LM[y1][x1][i]);
							}
						}
					}
					for (int i = 0; i < LM[y1][x2].size(); i++) {
						if (true) {
							if (LM[y1][x2][i]->yPos + TILE_HEIGHT > yPos) {
								SpritesHit.push_back(LM[y1][x2][i]);
							}
						}
					}
				}
			}
			else if (Measure == 11) { //down
				if (Debug) {
					printf("down\n");
				}
				if (TempX2Math == 0) {
					for (int i = 0; i < LM[y2][x1].size(); i++) {
						if (true) {
							if (LM[y2][x1][i]->yPos < yPos +TILE_HEIGHT) { //WORK <-these formuals forget that tile height and width need to be applied!
								SpritesHit.push_back(LM[y2][x1][i]);
							}
						}
					}
				}
				else {
					for (int i = 0; i < LM[y2][x1].size(); i++) {
						if (true) {
							if (LM[y2][x1][i]->yPos < yPos + TILE_HEIGHT) {
								SpritesHit.push_back(LM[y2][x1][i]);
							}
						}
					}
					for (int i = 0; i < LM[y2][x2].size(); i++) {
						if (true) {
							if (LM[y2][x2][i]->yPos < yPos + TILE_HEIGHT) {
								SpritesHit.push_back(LM[y2][x2][i]);
							}
						}
					}
				}
			}
		}
		if (Debug) {
			for (int hs = 0; hs < SpritesHit.size(); hs++) {
					printf("HS[%d] = Object%d\n", hs, SpritesHit[hs]->OrderCreation+1);
			}
		}


		//Hit sprites should now have all the sprites to the Y side of travel of the object in question. 

		//Now I have to figure out if there's any  REAL overlap.
		if (true) {
			if (Measure == 9) {
				for (int i = 0; i < SpritesHit.size(); i++) {
					 
					TempXOverlap = xPos + TILE_WIDTH - SpritesHit[i]->xPos;
						 
					if (TempXOverlap < 0 || TempXOverlap>16) {
						TempXOverlap = SpritesHit[i]->xPos + TILE_WIDTH - xPos;
					}
					if (Debug) { printf("JostleY X = %d\n", TempXOverlap); }
					if (SpritesHit[i]->yPos <  yPos) {
						TempYOverlap = SpritesHit[i]->yPos + TILE_HEIGHT - yPos;
						if (Debug) { printf("JostleY Y = %d\n", TempYOverlap); }
					}
					else {
						TempYOverlap = yPos + TILE_HEIGHT - SpritesHit[i]->yPos;
						if (Debug) { printf("JostleY Y = %d\n", TempYOverlap); }
					}
					//2) if you didn't collide, even if your in the same grid space, then the equation returned negative, or 0 if just barely touching. (butnot collding)
					if ((TempYOverlap < 17 && TempYOverlap > 0) && TempXOverlap < 17 && TempXOverlap > 0) {
						if (Debug) { printf("JostleY pushback Y\n"); }
						SpriteOverlapY.push_back(SpritesHit[i]);
						SpriteY.push_back(TempYOverlap);
						TempXOverlap = 0;
						TempYOverlap = 0;
					}
				}
			}
			else if (Measure == 11) {
				for (int i = 0; i < SpritesHit.size(); i++) { 
					TempXOverlap = xPos + TILE_WIDTH - SpritesHit[i]->xPos; 
					if (TempXOverlap<0 || TempXOverlap>16) {
						TempXOverlap = SpritesHit[i]->xPos + TILE_WIDTH - xPos; 
					}
					if (Debug) { printf("JostleY X = %d\n", TempXOverlap); }
					if (SpritesHit[i]->yPos < ObjectSprite->yPos) {
						TempYOverlap = SpritesHit[i]->yPos + TILE_HEIGHT - yPos;
						if (Debug) { printf("JostleY Y = %d\n", TempYOverlap); }
					}
					else {
						TempYOverlap = yPos + TILE_HEIGHT - SpritesHit[i]->yPos;
						if (Debug) { printf("JostleY Y = %d\n", TempYOverlap); }
					}
					printf("JostleY {%d, %d}\n", TempXOverlap, TempYOverlap);
					//2) if you didn't collide, even if your in the same grid space, then the equation returned negative, or 0 if just barely touching. (butnot collding)
					if ((TempYOverlap < 17 && TempYOverlap > 0) && TempXOverlap < 17 && TempXOverlap > 0) {
						if (Debug) { printf("JostleY pushback Y\n"); }
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
			if (SpriteY.size() > 0) {
				for (int y = 0; y < SpriteY.size(); y++) {
					printf("%d, ", SpriteY[y]);
				}
			}
			printf("}\n");
		}
		//Now SpriteX has integers, and SpriteXOverlap has the sprites,
		//sowe must sort them as usual, then select the largest, return the poitner, set the pointer in the XYArr2, and other stuffn' junk.
		MergeSortSpriteCollision2(SpriteOverlapY, SpriteY);
		if (Debug) {
			printf("After Merge:\n");
			printf("SpriteY = {");
			if (SpriteY.size() > 0) {
				for (int y = 0; y < SpriteY.size(); y++) {
					printf("%d, ", SpriteY[y]);
				}
			}
			printf("}\n");
		}

		 
		//WORK - tie collision types, overlap amount, priorities, default on order creation.
		if (SpriteY.size() > 0) {
			
			if (SpriteY[SpriteY.size()-1] > 0) {
				//There is only one diagonal we need to consider
				Edge[1] = SpriteY[SpriteY.size() - 1]; 
				TempStackable->HitSprites[1] = SpriteOverlapY.back();
				 }
			else { 
				Edge[1] = 0;
			}
		}
		 
		if (Debug) {
			printf("Jostle Y finished\n");
		}
	}

	  
	void JostleD(Sprite* ObjectSprite, int* D1, int* D2, int Measure, XYArr2*& TempStackable, int xDist, int yDist) {
		bool Debug = true;
		int xPos, yPos;
		int x1, x2, y1, y2;

		int TempX2Math, TempY2Math;
		if (Debug) {
			printf("DIST= %d / %d\n", xDist, yDist);
		}
		//the 'jostle'
		x1 = ObjectSprite->LastDestination.back()[0] + xDist;
		y1 = ObjectSprite->LastDestination.back()[1] + yDist;
		x2 = ObjectSprite->LastDestination.back()[0] + TILE_WIDTH + xDist;
		y2 = ObjectSprite->LastDestination.back()[1] + TILE_HEIGHT + yDist;
		if (Debug) {
			printf("LastPos = {%d, %d}\n", TempStackable->CurrentVictim->LastDestination.back()[0], TempStackable->CurrentVictim->LastDestination.back()[1]);
			printf("LastPos = {%d, %d}\n", x1, y1);
		}

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
					if (LM[y1][x1][i]->xPos +TILE_WIDTH > xPos  && LM[y1][x1][i]->yPos + TILE_HEIGHT > yPos) { //NEW (CHANGED)
						SpritesHit.push_back(LM[y1][x1][i]);
					}
				}
			}
			else if (Measure == 13) {//UR 
				if (Debug) {
					printf("i\n");
				}
				for (int i = 0; i < LM[y1][x2].size(); i++) { // first
					if (LM[y1][x2][i]->xPos < xPos +TILE_WIDTH && LM[y1][x2][i]->yPos + TILE_HEIGHT > yPos) { //NEW (CHANGED)
						SpritesHit.push_back(LM[y1][x2][i]);
					}
				}
			}
			else if (Measure == 7) {//DL 
				if (Debug) {
					printf("q\n");
				}
				for (int i = 0; i < LM[y2][x1].size(); i++) { // first
					if (LM[y2][x1][i]->xPos + TILE_WIDTH > xPos && LM[y2][x1][i]->yPos < yPos +TILE_HEIGHT) { //NEW (CHANGED)
						SpritesHit.push_back(LM[y2][x1][i]);
					}
				}
			}
			else if (Measure == 15) {//DR 
				if (Debug) {
					printf("x\n");
				}
				for (int i = 0; i < LM[y2][x2].size(); i++) { // LL
					if (LM[y2][x2][i]->xPos < xPos + TILE_WIDTH && LM[y2][x2][i]->yPos < yPos + TILE_HEIGHT) { //NEW (CHANGED)
						SpritesHit.push_back(LM[y2][x2][i]);
					}
				}
			}
		}
		//Now we have all possible Sprites we could've hit for that given measure.
		if (Debug) {
			for (int hs = 0; hs < SpritesHit.size(); hs++) {
				printf("HS[%d] = Object%d\n", hs, SpritesHit[hs]->OrderCreation + 1);
			}
		}

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
					if (SpritesHit[i]->yPos <  yPos) {
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
						if (Debug) {
							printf("%d\n", TempXOverlap);
						}
					}
					else {
						TempXOverlap = SpritesHit[i]->xPos + TILE_WIDTH - xPos;
						if (Debug) {
							printf("%d\n", TempXOverlap);
						}
					}
					if (SpritesHit[i]->yPos > yPos) {
						TempYOverlap = yPos + TILE_HEIGHT - SpritesHit[i]->yPos;
						if (Debug) {
							printf("%d\n", TempYOverlap);
						}
					}
					else {
						TempYOverlap = SpritesHit[i]->yPos + TILE_HEIGHT - yPos;
						if (Debug) {
							printf("%d\n", TempYOverlap);
						}
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
						if (Debug) {
							printf("%d\n", TempXOverlap);
						}
					}
					else {
						TempXOverlap = SpritesHit[i]->xPos + TILE_WIDTH - xPos;
						if (Debug) {
							printf("%d\n", TempXOverlap);
						}
					}
					if (SpritesHit[i]->yPos > yPos) {
						TempYOverlap = yPos + TILE_HEIGHT - SpritesHit[i]->yPos;
						if (Debug) {
							printf("%d\n", TempYOverlap);
						}
					}
					else {
						TempYOverlap = SpritesHit[i]->yPos + TILE_HEIGHT - yPos;
						if (Debug) {
							printf("%d\n", TempYOverlap);
						}
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
			if (SpriteX.size() > 0) {
				for (int x = 0; x < SpriteX.size(); x++) {
					printf("%d, ", SpriteX[x]);
				}
			}
			printf("}\n");
			printf("SpriteY = {");
			if (SpriteY.size() > 0) {
				for (int y = 0; y < SpriteY.size(); y++) {
					printf("%d, ", SpriteY[y]);
				}
			}
			printf("}\n");
		}

		MergeSortSpriteCollision2(SpriteOverlapX, SpriteX);
		MergeSortSpriteCollision2(SpriteOverlapY, SpriteY);
		if (Debug) {
			printf("After Merge:\n");
			printf("SpriteX = {");
			if (SpriteX.size() > 0) {
				for (int x = 0; x < SpriteX.size(); x++) {
					printf("%d, ", SpriteX[x]);
				}
			}
			printf("}\n");
			printf("SpriteY = {");
			if (SpriteY.size() > 0) {
				for (int y = 0; y < SpriteY.size(); y++) { 
					printf("%d, ", SpriteY[y]);
				}
			}
			printf("}\n");
		}


		//Assuming the max overlap is at the back. -this needs to change to consider the collision type, of both, and see if they are same, and itterate independently to get the correct answer.
		if (SpriteX.size() > 0 && SpriteY.size() > 0) {
			if (SpriteOverlapX[SpriteOverlapX.size() - 1] == SpriteOverlapY[SpriteOverlapY.size() - 1]) {
				//There is only one diagonal we need to consider
			
				D1[0] = SpriteX[SpriteX.size() - 1];
				D1[1] = SpriteY[SpriteY.size() - 1];
				TempStackable->HitSprites[2] = SpriteOverlapX[SpriteOverlapX.size()-1];
			}
			else {
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
						if (SpriteOverlapX[xItter] == SpriteOverlapY[yItter]) {
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

	}
	
	
	//WORK - figure out when you want to jostle again
	//figure out when we want to update position
	//figure out when we want to stack (or end early)
	//edittravel on successful moves.
	//guear ffor distance out of map
	//Add D2 functionality. for now we'll never have a case as such but for now we've gotto check
	int CheckFuture3(Sprite* ObjectSprite, XYArr2*& TempStackable, int Measure) {
		bool Debug = true;
		int Edge[2]; //{x,y}
		int D1[2];
		int D2[2]; //The reason there are two diagonals is that if in some case we perfectly align with two sprites on the diagonal, and they have different axis' max, but equal, then we want to the ake the minimum appropriate values.
		int Final[2]; //the values that matter. Figure out how to move for this
		int xDistance;
		int yDistance;
		int NewXDistance, NewYDistance;
		double Percentage; 
		TempStackable = new XYArr2;
		TempStackable->CurrentVictim = ObjectSprite;
		int xPos;
		int yPos; 
		int x;
		int y;
		int dx;
		int dy;

		while (true) {
			for (int x = 0; x < 2; x++) {
				Edge[x] = 0;
				D1[x] = 0;
				D2[x] = 0;
				Final[x] = 0;
			}
			if (Measure != 10) {
				//NOTE - the double percentage for now will always result in a rounded down value. Look into using static cast instead of (int)
				//NEW - figure out the jostle distance using rise over run, and the min maximum allowable distance.
				xDistance = ObjectSprite->ExVel[0];
				yDistance = ObjectSprite->ExVel[1];

				Percentage = 0;
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
					else {
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


				if (Debug) { printf("Jostle\n");}
				if (ObjectSprite->Measure == 5 || ObjectSprite->Measure == 7 || ObjectSprite->Measure == 13 || ObjectSprite->Measure == 15) {
					if (Debug) { printf("Diagonal\n"); }
					//only do the necessary ones //WORK - double check that Edge and D are properlly storing some values when they finish!
					int TempMeasureX;
					int TempMeasureY;
					if (true) {
						if (Measure == 15) {
							TempMeasureX = 14;
							TempMeasureY = 11;
						}
						else if (Measure == 13) {
							TempMeasureX = 14;
							TempMeasureY = 9;
						}
						else if (Measure == 5) {
							TempMeasureX = 6;
							TempMeasureY = 9;
						}
						else if (Measure == 7) {
							TempMeasureX = 6;
							TempMeasureY = 11;
						}
					}
					JostleX(ObjectSprite, Edge, TempMeasureX, TempStackable, NewXDistance);
					if (Debug) { printf("Jostling x done\n"); }
					JostleY(ObjectSprite, Edge, TempMeasureY, TempStackable, NewYDistance);
					if (Debug) { printf("Jostling y done\n"); }
					JostleD(ObjectSprite, D1, D2, Measure, TempStackable, NewXDistance, NewYDistance);
					if (Debug) { printf("Jostling d done\n"); }
				}
				else if (ObjectSprite->Measure == 9 || ObjectSprite->Measure == 11) {
					if (Debug) { printf("Y Jostle\n"); }
					JostleY(ObjectSprite, Edge, Measure, TempStackable, NewYDistance); 
					if (Debug) { printf("Jostling y done\n"); }
				}
				else if (ObjectSprite->Measure == 6 || ObjectSprite->Measure == 14) {
					if (Debug) { printf("X Jostle\n"); }
					JostleX(ObjectSprite, Edge, Measure, TempStackable, NewXDistance);
					if (Debug) { printf("Jostling x done\n"); }
				}
				//Edge = {x,y}, D = {Dx, Dy}
				if (Debug) { printf("Jostling done\n"); }


				xPos = ObjectSprite->LastDestination.back()[0];
				yPos = ObjectSprite->LastDestination.back()[1];
				x = Edge[0];
				y = Edge[1];
				dx = D1[0];
				dy = D1[1];
				if (Debug) { printf("Initial values set\n"); }

				//NOTE NOTE NOTE - when sliding, and checking if your clear, this is only optimal when you are hitting something that is already complete, OTHERWISE DON'T

				//Figure out How to move - Note the Sprite you choose to run into.
				//use rise over run, keep axis movements the same (for each axis, but can be independent amounts between x and y) and then compare.
				// 
				//x>=dx, treat it as just sliding on x
				//y>=dy, treat it as just slding on y
				//if x,y, if either is greater than the diagonal, then take x and y
				
				//WORK - these formulas aren't quite right for what I'm expecting. I'm expecting Final to be absolutely positive, but the additions and such to be correct
				if (Measure == 5 || Measure == 7 || Measure == 13 || Measure == 15) { //ObjectSprite->LastDestination.push_back({ xPos+NewXDistance, yPos +NewYDistance});
					//Diagonal ONLY
					if (Measure == 15) {
						//{0,y},{dx,dy}
						if (x == 0 && y != 0 && (dx != 0 && dy != 0)) {
							if (y < dy) { 
								Final[0] = NewXDistance - dx;
								Final[1] = NewYDistance - dy;
								SetTempStackableDebugInfo(TempStackable, D1, D2, Edge, Final);
								ObjectSprite->LastDestination.push_back({ xPos + NewXDistance - dx, yPos + NewYDistance - dy }); //this is slightly wrong. we want to glide UNLESS dx==dy
							}
							else if (y == dy) {
								Final[0] = NewXDistance;
								Final[1] = NewYDistance - y;
								 SetTempStackableDebugInfo(TempStackable, D1, D2, Edge, Final);
								ObjectSprite->LastDestination.push_back({ xPos + NewXDistance, yPos + NewYDistance - y });
							}
							else if (y > dy) {
								Final[0] = NewXDistance;
								Final[1] = NewYDistance - y;
								 SetTempStackableDebugInfo(TempStackable, D1, D2, Edge, Final);
								ObjectSprite->LastDestination.push_back({ xPos + NewXDistance, yPos + NewYDistance - y });//Check when your clear, so that you can edit y appropriately
							}
						}
						//{x,0},{dx,dy}
						if (x != 0 && y == 0 && (dx != 0 && dy != 0)) {
							if (x < dx) {
								Final[0] = NewXDistance - dx;
								Final[1] = NewYDistance - dy;
								 SetTempStackableDebugInfo(TempStackable, D1, D2, Edge, Final);
								ObjectSprite->LastDestination.push_back({ xPos + NewXDistance - dx, yPos + NewYDistance - dy }); //See previous
							}
							else if (x == dx) {
								Final[0] = NewXDistance - x;
								Final[1] = NewYDistance  ;
								SetTempStackableDebugInfo(TempStackable, D1, D2, Edge, Final);
								ObjectSprite->LastDestination.push_back({ xPos + NewXDistance - x, yPos + NewYDistance });
							}
							else if (x > dx) {
								Final[0] = NewXDistance - x;
								Final[1] = NewYDistance ;
								SetTempStackableDebugInfo(TempStackable, D1, D2, Edge, Final);
								ObjectSprite->LastDestination.push_back({ xPos + NewXDistance - x, yPos + NewYDistance }); //Check when your clear, so that you can edit x appropriately
							}

						}
						//{x,y}, {0,0}
						if (x != 0 && y != 0 && (dx == 0 && dy == 0)) {
							Final[0] = NewXDistance - x;
							Final[1] = NewYDistance- y;
							SetTempStackableDebugInfo(TempStackable, D1, D2, Edge, Final);
							ObjectSprite->LastDestination.push_back({ xPos + NewXDistance - x, yPos + NewYDistance - y });
						}
						//{0,0},{dx, dy}
						if (x == 0 && y == 0 && (dx != 0 && dy != 0)) {
							//slight error here potentially. Check to see if overlap is the same and if so freeze there for a bit.

							//freeze, perfect colllision
							if (dx == dy) {
								Final[0] = NewXDistance - dx;
								Final[1] = NewYDistance - dy;
								SetTempStackableDebugInfo(TempStackable, D1, D2, Edge, Final);
								ObjectSprite->LastDestination.push_back({ xPos + NewXDistance - dx, yPos + NewYDistance - dy });
							}
							//Tp on the dx, but slide down dy
							else if (dx > dy) {
								Final[0] = NewXDistance - x;
								Final[1] = NewYDistance - dy;
								SetTempStackableDebugInfo(TempStackable, D1, D2, Edge, Final);
								ObjectSprite->LastDestination.push_back({ xPos + NewXDistance - x, yPos + NewYDistance - dy });
							}
							//Tp on the dy, but slide down the dx
							else if (dy > dx) {
								Final[0] = NewXDistance - dx;
								Final[1] = NewYDistance - y;
								SetTempStackableDebugInfo(TempStackable, D1, D2, Edge, Final);
								ObjectSprite->LastDestination.push_back({ xPos + NewXDistance - dx, yPos + NewYDistance - y });
							}
						}
						//{0,0},{0,0}
						if (x == 0 && y == 0 && dx == 0 && dy == 0) {
							Final[0] = NewXDistance  ;
							Final[1] = NewYDistance  ;
							SetTempStackableDebugInfo(TempStackable, D1, D2, Edge, Final);
							ObjectSprite->LastDestination.push_back({ xPos + NewXDistance, yPos + NewYDistance });
						}
						//{x,y}{dx,dy}
						if (x != 0 && y != 0 && (dx != 0 && dy != 0)) {
							if (x >= dx) {
								if (y >= dy) {
									Final[0] = NewXDistance - x;
									Final[1] = NewYDistance -y;
									SetTempStackableDebugInfo(TempStackable, D1, D2, Edge, Final);
									ObjectSprite->LastDestination.push_back({ xPos + NewXDistance - x, yPos + NewYDistance - y });
								}
								else if (y < dy) { //this is because we just slide down the side a small bit away on the x axis from the D. Insert a check to move if you'r free a bit on the x axis. (same as other ones for the same considerations)
									Final[0] = NewXDistance - x;
									Final[1] = NewYDistance - y;
									SetTempStackableDebugInfo(TempStackable, D1, D2, Edge, Final);
									ObjectSprite->LastDestination.push_back({ xPos + NewXDistance - x, yPos + NewYDistance - y });
								}
							}
							else if (y >= dy) {
								if (x >= dx) {
									Final[0] = NewXDistance - x;
									Final[1] = NewYDistance - y;
									SetTempStackableDebugInfo(TempStackable, D1, D2, Edge, Final);
									ObjectSprite->LastDestination.push_back({ xPos + NewXDistance - x, yPos + NewYDistance - y });
								}
								else if (x < dx) {
									Final[0] = NewXDistance - x;
									Final[1] = NewYDistance - y;
									SetTempStackableDebugInfo(TempStackable, D1, D2, Edge, Final);
									ObjectSprite->LastDestination.push_back({ xPos + NewXDistance - x, yPos + NewYDistance - y });
								}
							}
							else if (dx > x && dy > y) { //yoink this code for earlier if statements
								//Like the others, if there is a preference based on the rise over run, implementit here. 
								//Also if it's perfect collision freeze it by default (freeze as in don't slide down a side or something)

								//freeze, perfect colllision
								if (dx == dy) {
									Final[0] = NewXDistance - dx;
									Final[1] = NewYDistance - dy;
									SetTempStackableDebugInfo(TempStackable, D1, D2, Edge, Final);
									ObjectSprite->LastDestination.push_back({ xPos + NewXDistance - dx, yPos + NewYDistance - dy });
								}
								//Tp on the dx, but slide down dy
								else if (dx > dy) {
									Final[0] = NewXDistance - x;
									Final[1] = NewYDistance - dy;
									SetTempStackableDebugInfo(TempStackable, D1, D2, Edge, Final);
									ObjectSprite->LastDestination.push_back({ xPos + NewXDistance - x, yPos + NewYDistance - dy });
								}
								//Tp on the dy, but slide down the dx
								else if (dy > dx) {
									Final[0] = NewXDistance - dx;
									Final[1] = NewYDistance - y;
									SetTempStackableDebugInfo(TempStackable, D1, D2, Edge, Final);
									ObjectSprite->LastDestination.push_back({ xPos + NewXDistance - dx, yPos + NewYDistance - y });
								}
							}
						}
					}
					if (Measure == 13) { //see commments above for fixes
						//{0,y},{dx,dy}
						if (x == 0 && y != 0 && (dx != 0 && dy != 0)) {
							if (y < dy) {
								Final[0] = NewXDistance - dx;
								Final[1] = NewYDistance + dy;
								SetTempStackableDebugInfo(TempStackable, D1, D2, Edge, Final);
								ObjectSprite->LastDestination.push_back({ xPos + NewXDistance - dx, yPos + NewYDistance + dy });
							}
							else if (y == dy) {
								Final[1] = NewYDistance + y;
								SetTempStackableDebugInfo(TempStackable, D1, D2, Edge, Final);
								ObjectSprite->LastDestination.push_back({ xPos + NewXDistance, yPos + NewYDistance + y });
							}
							else if (y > dy) {
								Final[0] = NewXDistance;
								Final[1] = NewYDistance - y;
								SetTempStackableDebugInfo(TempStackable, D1, D2, Edge, Final);
								ObjectSprite->LastDestination.push_back({ xPos + NewXDistance, yPos + NewYDistance + y });
							}
						}
						//{x,0},{dx,dy}
						if (x != 0 && y == 0 && (dx != 0 && dy != 0)) {
							if (x < dx) {
								Final[0] = NewXDistance - dx;
								Final[1] = NewYDistance + dy;
								SetTempStackableDebugInfo(TempStackable, D1, D2, Edge, Final);
								ObjectSprite->LastDestination.push_back({ xPos + NewXDistance - dx, yPos + NewYDistance + dy });
							}
							else if (x == dx) {
								Final[0] = NewXDistance - x;
								Final[1] = NewYDistance ;
								SetTempStackableDebugInfo(TempStackable, D1, D2, Edge, Final);
								ObjectSprite->LastDestination.push_back({ xPos + NewXDistance - x, yPos + NewYDistance });
							}
							else if (x > dx) {
								Final[0] = NewXDistance - x;
								Final[1] = NewYDistance;
								SetTempStackableDebugInfo(TempStackable, D1, D2, Edge, Final);
								ObjectSprite->LastDestination.push_back({ xPos + NewXDistance - x, yPos + NewYDistance });
							}

						}
						//{x,y}, {0,0}
						if (x != 0 && y != 0 && (dx == 0 && dy == 0)) {
							Final[0] = NewXDistance - x;
							Final[1] = NewYDistance + y;
							SetTempStackableDebugInfo(TempStackable, D1, D2, Edge, Final);
							ObjectSprite->LastDestination.push_back({ xPos + NewXDistance - x, yPos + NewYDistance + y });
						}
						//{0,0},{dx, dy}
						if (x == 0 && y == 0 && (dx != 0 && dy != 0)) {  //slight error here potentially. Check to see if overlap is the same and if so freeze there for a bit.

						//freeze, perfect colllision
							if (dx == dy) {
								Final[0] = NewXDistance - dx;
								Final[1] = NewYDistance + dy;
								SetTempStackableDebugInfo(TempStackable, D1, D2, Edge, Final);
								ObjectSprite->LastDestination.push_back({ xPos + NewXDistance - dx, yPos + NewYDistance + dy });
							}
							//Tp on the dx, but slide down dy
							else if (dx > dy) {
								Final[0] = NewXDistance - x;
								Final[1] = NewYDistance + dy;
								SetTempStackableDebugInfo(TempStackable, D1, D2, Edge, Final);
								ObjectSprite->LastDestination.push_back({ xPos + NewXDistance - x, yPos + NewYDistance + dy });
							}
							//Tp on the dy, but slide down the dx
							else if (dy > dx) {
								Final[0] = NewXDistance - dx;
								Final[1] = NewYDistance + y;
								SetTempStackableDebugInfo(TempStackable, D1, D2, Edge, Final);
								ObjectSprite->LastDestination.push_back({ xPos + NewXDistance - dx, yPos + NewYDistance + y });
							}
						}
						//{0,0},{0,0}
						if (x == 0 && y == 0 && dx == 0 && dy == 0) {
							Final[0] = NewXDistance  ;
							Final[1] = NewYDistance  ;
							SetTempStackableDebugInfo(TempStackable, D1, D2, Edge, Final);
							ObjectSprite->LastDestination.push_back({ xPos + NewXDistance, yPos + NewYDistance });
						}
						//{x,y}{dx,dy}
						if (x != 0 && y != 0 && (dx != 0 && dy != 0)) {
							if (x >= dx) {
								if (y >= dy) {
									Final[0] = NewXDistance - x;
									Final[1] = NewYDistance + y;
									SetTempStackableDebugInfo(TempStackable, D1, D2, Edge, Final);
									ObjectSprite->LastDestination.push_back({ xPos + NewXDistance - x, yPos + NewYDistance + y });
								}
								else if (y < dy) { //this is because we just slide down the side a small bit away on the x axis from the D. Insert a check to move if you'r free a bit on the x axis. (same as other ones for the same considerations)
									Final[0] = NewXDistance - x;
									Final[1] = NewYDistance + y;
									SetTempStackableDebugInfo(TempStackable, D1, D2, Edge, Final);
									ObjectSprite->LastDestination.push_back({ xPos + NewXDistance - x, yPos + NewYDistance + y });
								}
							}
							else if (y >= dy) {
								if (x >= dx) {
									Final[0] = NewXDistance - x;
									Final[1] = NewYDistance + y;
									SetTempStackableDebugInfo(TempStackable, D1, D2, Edge, Final);
									ObjectSprite->LastDestination.push_back({ xPos + NewXDistance - x, yPos + NewYDistance + y });
								}
								else if (x < dx) {
									Final[0] = NewXDistance - x;
									Final[1] = NewYDistance + y;
									SetTempStackableDebugInfo(TempStackable, D1, D2, Edge, Final);
									ObjectSprite->LastDestination.push_back({ xPos + NewXDistance - x, yPos + NewYDistance + y });
								}
							}
							else if (dx > x && dy > y) { //yoink this code for earlier if statements
								//Like the others, if there is a preference based on the rise over run, implementit here. 
								//Also if it's perfect collision freeze it by default (freeze as in don't slide down a side or something)

								//freeze, perfect colllision
								if (dx == dy) {
									Final[0] = NewXDistance - dx;
									Final[1] = NewYDistance + dy;
									SetTempStackableDebugInfo(TempStackable, D1, D2, Edge, Final);
									ObjectSprite->LastDestination.push_back({ xPos + NewXDistance - dx, yPos + NewYDistance + dy });
								}
								//Tp on the dx, but slide down dy
								else if (dx > dy) {
									Final[0] = NewXDistance - x;
									Final[1] = NewYDistance + dy;
									SetTempStackableDebugInfo(TempStackable, D1, D2, Edge, Final);
									ObjectSprite->LastDestination.push_back({ xPos + NewXDistance - x, yPos + NewYDistance + dy });
								}
								//Tp on the dy, but slide down the dx
								else if (dy > dx) {
									Final[0] = NewXDistance - dx;
									Final[1] = NewYDistance + y;
									SetTempStackableDebugInfo(TempStackable, D1, D2, Edge, Final);
									ObjectSprite->LastDestination.push_back({ xPos + NewXDistance - dx, yPos + NewYDistance + y });
								}
							}
						}
					}
					if (Measure == 5) { //see commments above for fixes
						//{0,y},{dx,dy}
						if (x == 0 && y != 0 && (dx != 0 && dy != 0)) {
							if (y < dy) {
								Final[0] = NewXDistance + dx;
								Final[1] = NewYDistance + dy;
								SetTempStackableDebugInfo(TempStackable, D1, D2, Edge, Final);
								ObjectSprite->LastDestination.push_back({ xPos + NewXDistance + dx, yPos + NewYDistance + dy });
							}
							else if (y == dy) {
								Final[0] = NewXDistance;
								Final[1] = NewYDistance + y;
								SetTempStackableDebugInfo(TempStackable, D1, D2, Edge, Final);
								ObjectSprite->LastDestination.push_back({ xPos + NewXDistance, yPos + NewYDistance + y });
							}
							else if (y > dy) {
								Final[0] = NewXDistance;
								Final[1] = NewYDistance + y;
								SetTempStackableDebugInfo(TempStackable, D1, D2, Edge, Final);
								ObjectSprite->LastDestination.push_back({ xPos + NewXDistance, yPos + NewYDistance + y });
							}
						}
						//{x,0},{dx,dy}
						if (x != 0 && y == 0 && (dx != 0 && dy != 0)) {
							if (x < dx) {
								Final[0] = NewXDistance + dx;
								Final[1] = NewYDistance + dy;
								SetTempStackableDebugInfo(TempStackable, D1, D2, Edge, Final);
								ObjectSprite->LastDestination.push_back({ xPos + NewXDistance + dx, yPos + NewYDistance + dy });
							}
							else if (x == dx) {
								Final[0] = NewXDistance + x;
								Final[1] = NewYDistance;
								SetTempStackableDebugInfo(TempStackable, D1, D2, Edge, Final);
								ObjectSprite->LastDestination.push_back({ xPos + NewXDistance + x, yPos + NewYDistance });
							}
							else if (x > dx) {
								Final[0] = NewXDistance + x;
								Final[1] = NewYDistance;
								SetTempStackableDebugInfo(TempStackable, D1, D2, Edge, Final);
								ObjectSprite->LastDestination.push_back({ xPos + NewXDistance + x, yPos + NewYDistance });
							}

						}
						//{x,y}, {0,0}
						if (x != 0 && y != 0 && (dx == 0 && dy == 0)) {
							Final[0] = NewXDistance + x;
							Final[1] = NewYDistance + y;
							SetTempStackableDebugInfo(TempStackable, D1, D2, Edge, Final);
							ObjectSprite->LastDestination.push_back({ xPos + NewXDistance + x, yPos + NewYDistance + y });
						}
						//{0,0},{dx, dy}
						if (x == 0 && y == 0 && (dx != 0 && dy != 0)) { //slight error here potentially. Check to see if overlap is the same and if so freeze there for a bit.

							//freeze, perfect colllision
							if (dx == dy) {
								Final[0] = NewXDistance + dx;
								Final[1] = NewYDistance + dy;
								SetTempStackableDebugInfo(TempStackable, D1, D2, Edge, Final);
								ObjectSprite->LastDestination.push_back({ xPos + NewXDistance + dx, yPos + NewYDistance + dy });
							}
							//Tp on the dx, but slide down dy
							else if (dx > dy) {
								Final[0] = NewXDistance + x;
								Final[1] = NewYDistance + dy;
								SetTempStackableDebugInfo(TempStackable, D1, D2, Edge, Final);
								ObjectSprite->LastDestination.push_back({ xPos + NewXDistance + x, yPos + NewYDistance + dy });
							}
							//Tp on the dy, but slide down the dx
							else if (dy > dx) {
								Final[0] = NewXDistance + dx;
								Final[1] = NewYDistance + y;
								SetTempStackableDebugInfo(TempStackable, D1, D2, Edge, Final);
								ObjectSprite->LastDestination.push_back({ xPos + NewXDistance + dx, yPos + NewYDistance + y });
							}
						}
						//{0,0},{0,0}
						if (x == 0 && y == 0 && dx == 0 && dy == 0) {
							Final[0] = NewXDistance  ;
							Final[1] = NewYDistance  ;
							SetTempStackableDebugInfo(TempStackable, D1, D2, Edge, Final);
							ObjectSprite->LastDestination.push_back({ xPos + NewXDistance, yPos + NewYDistance });
						}
						//{x,y}{dx,dy}
						if (x != 0 && y != 0 && (dx != 0 && dy != 0)) {
							if (x >= dx) {
								if (y >= dy) {
									Final[0] = NewXDistance + x;
									Final[1] = NewYDistance + y;
									SetTempStackableDebugInfo(TempStackable, D1, D2, Edge, Final);
									ObjectSprite->LastDestination.push_back({ xPos + NewXDistance + x, yPos + NewYDistance + y });
								}
								else if (y < dy) { //this is because we just slide down the side a small bit away on the x axis from the D. Insert a check to move if you'r free a bit on the x axis. (same as other ones for the same considerations)
									Final[0] = NewXDistance + x;
									Final[1] = NewYDistance + y;
									SetTempStackableDebugInfo(TempStackable, D1, D2, Edge, Final);
									ObjectSprite->LastDestination.push_back({ xPos + NewXDistance + x, yPos + NewYDistance + y });
								}
							}
							else if (y >= dy) {
								if (x >= dx) {
									Final[0] = NewXDistance + x;
									Final[1] = NewYDistance + y;
									SetTempStackableDebugInfo(TempStackable, D1, D2, Edge, Final);
									ObjectSprite->LastDestination.push_back({ xPos + NewXDistance + x, yPos + NewYDistance + y });
								}
								else if (x < dx) {
									Final[0] = NewXDistance + x;
									Final[1] = NewYDistance + y;
									SetTempStackableDebugInfo(TempStackable, D1, D2, Edge, Final);
									ObjectSprite->LastDestination.push_back({ xPos + NewXDistance + x, yPos + NewYDistance + y });
								}
							}
							else if (dx > x && dy > y) { //yoink this code for earlier if statements
								//Like the others, if there is a preference based on the rise over run, implementit here. 
								//Also if it's perfect collision freeze it by default (freeze as in don't slide down a side or something)

								//freeze, perfect colllision
								if (dx == dy) {
									Final[0] = NewXDistance + dx;
									Final[1] = NewYDistance + dy;
									SetTempStackableDebugInfo(TempStackable, D1, D2, Edge, Final);
									ObjectSprite->LastDestination.push_back({ xPos + NewXDistance + dx, yPos + NewYDistance + dy });
								}
								//Tp on the dx, but slide down dy
								else if (dx > dy) {
									Final[0] = NewXDistance + x;
									Final[1] = NewYDistance + dy;
									SetTempStackableDebugInfo(TempStackable, D1, D2, Edge, Final);
									ObjectSprite->LastDestination.push_back({ xPos + NewXDistance + x, yPos + NewYDistance + dy });
								}
								//Tp on the dy, but slide down the dx
								else if (dy > dx) {
									Final[0] = NewXDistance + dx;
									Final[1] = NewYDistance + y;
									SetTempStackableDebugInfo(TempStackable, D1, D2, Edge, Final);
									ObjectSprite->LastDestination.push_back({ xPos + NewXDistance + dx, yPos + NewYDistance + y });
								}
							}
						}
					}
					if (Measure == 7) {
						//{0,y},{dx,dy}
						if (x == 0 && y != 0 && (dx != 0 && dy != 0)) {
							if (y < dy) {
								Final[0] = NewXDistance + dx;
								Final[1] = NewYDistance - dy;
								SetTempStackableDebugInfo(TempStackable, D1, D2, Edge, Final);
								ObjectSprite->LastDestination.push_back({ xPos + NewXDistance + dx, yPos + NewYDistance - dy }); //this is slightly wrong. we want to glide UNLESS dx==dy
							}
							else if (y == dy) {
								Final[0] = NewXDistance;
								Final[1] = NewYDistance - y;
								SetTempStackableDebugInfo(TempStackable, D1, D2, Edge, Final);
								ObjectSprite->LastDestination.push_back({ xPos + NewXDistance, yPos + NewYDistance - y });
							}
							else if (y > dy) {
								Final[0] = NewXDistance;
								Final[1] = NewYDistance - y;
								SetTempStackableDebugInfo(TempStackable, D1, D2, Edge, Final);
								ObjectSprite->LastDestination.push_back({ xPos + NewXDistance, yPos + NewYDistance - y });//Check when your clear, so that you can edit y appropriately
							}
						}
						//{x,0},{dx,dy}
						if (x != 0 && y == 0 && (dx != 0 && dy != 0)) {
							if (x < dx) {
								Final[0] = NewXDistance + dx;
								Final[1] = NewYDistance - dy;
								SetTempStackableDebugInfo(TempStackable, D1, D2, Edge, Final);
								ObjectSprite->LastDestination.push_back({ xPos + NewXDistance + dx, yPos + NewYDistance - dy }); //See previous
							}
							else if (x == dx) {
								Final[0] = NewXDistance + x;
								Final[1] = NewYDistance;
								SetTempStackableDebugInfo(TempStackable, D1, D2, Edge, Final);
								ObjectSprite->LastDestination.push_back({ xPos + NewXDistance + x, yPos + NewYDistance });
							}
							else if (x > dx) {
								Final[0] = NewXDistance + x;
								Final[1] = NewYDistance;
								SetTempStackableDebugInfo(TempStackable, D1, D2, Edge, Final);
								ObjectSprite->LastDestination.push_back({ xPos + NewXDistance + x, yPos + NewYDistance }); //Check when your clear, so that you can edit x appropriately
							}

						}
						//{x,y}, {0,0}
						if (x != 0 && y != 0 && (dx == 0 && dy == 0)) {
							Final[0] = NewXDistance + x;
							Final[1] = NewYDistance - y;
							SetTempStackableDebugInfo(TempStackable, D1, D2, Edge, Final);
							ObjectSprite->LastDestination.push_back({ xPos + NewXDistance + x, yPos + NewYDistance - y });
						}
						//{0,0},{dx, dy}
						if (x == 0 && y == 0 && (dx != 0 && dy != 0)) {  //slight error here potentially. Check to see if overlap is the same and if so freeze there for a bit.

							//freeze, perfect colllision
							if (dx == dy) {
								Final[0] = NewXDistance + dx;
								Final[1] = NewYDistance - dy;
								SetTempStackableDebugInfo(TempStackable, D1, D2, Edge, Final);
								ObjectSprite->LastDestination.push_back({ xPos + NewXDistance + dx, yPos + NewYDistance - dy });
							}
							//Tp on the dx, but slide down dy
							else if (dx > dy) {
								Final[0] = NewXDistance + x;
								Final[1] = NewYDistance - dy;
								SetTempStackableDebugInfo(TempStackable, D1, D2, Edge, Final);
								ObjectSprite->LastDestination.push_back({ xPos + NewXDistance + x, yPos + NewYDistance - dy });
							}
							//Tp on the dy, but slide down the dx
							else if (dy > dx) {
								Final[0] = NewXDistance + dx;
								Final[1] = NewYDistance - y;
								SetTempStackableDebugInfo(TempStackable, D1, D2, Edge, Final);
								ObjectSprite->LastDestination.push_back({ xPos + NewXDistance + dx, yPos + NewYDistance - y });
							}
						}
						//{0,0},{0,0}
						if (x == 0 && y == 0 && dx == 0 && dy == 0) {
							Final[0] = NewXDistance ;
							Final[1] = NewYDistance  ;
							SetTempStackableDebugInfo(TempStackable, D1, D2, Edge, Final);
							ObjectSprite->LastDestination.push_back({ xPos + NewXDistance, yPos + NewYDistance });
						}
						//{x,y}{dx,dy}
						if (x != 0 && y != 0 && (dx != 0 && dy != 0)) {
							if (x >= dx) {
								if (y >= dy) {
									Final[0] = NewXDistance + x;
									Final[1] = NewYDistance - dy;
									SetTempStackableDebugInfo(TempStackable, D1, D2, Edge, Final);
									ObjectSprite->LastDestination.push_back({ xPos + NewXDistance + x, yPos + NewYDistance - y });
								}
								else if (y < dy) { //this is because we just slide down the side a small bit away on the x axis from the D. Insert a check to move if you'r free a bit on the x axis. (same as other ones for the same considerations)
									Final[0] = NewXDistance + x;
									Final[1] = NewYDistance - y;
									SetTempStackableDebugInfo(TempStackable, D1, D2, Edge, Final);
									ObjectSprite->LastDestination.push_back({ xPos + NewXDistance + x, yPos + NewYDistance - y });
								}
							}
							else if (y >= dy) {
								if (x >= dx) {
									Final[0] = NewXDistance + x;
									Final[1] = NewYDistance - y;
									SetTempStackableDebugInfo(TempStackable, D1, D2, Edge, Final);
									ObjectSprite->LastDestination.push_back({ xPos + NewXDistance + x, yPos + NewYDistance - y });
								}
								else if (x < dx) {
									Final[0] = NewXDistance + x;
									Final[1] = NewYDistance - y;
									SetTempStackableDebugInfo(TempStackable, D1, D2, Edge, Final);
									ObjectSprite->LastDestination.push_back({ xPos + NewXDistance + x, yPos + NewYDistance - y });
								}
							}
							else if (dx > x && dy > y) { //yoink this code for earlier if statements
								//Like the others, if there is a preference based on the rise over run, implementit here. 
								//Also if it's perfect collision freeze it by default (freeze as in don't slide down a side or something)

								//freeze, perfect colllision
								if (dx == dy) {
									Final[0] = NewXDistance + dx;
									Final[1] = NewYDistance - dy;
									SetTempStackableDebugInfo(TempStackable, D1, D2, Edge, Final);
									ObjectSprite->LastDestination.push_back({ xPos + NewXDistance + dx, yPos + NewYDistance - dy });
								}
								//Tp on the dx, but slide down dy
								else if (dx > dy) {
									Final[0] = NewXDistance + x;
									Final[1] = NewYDistance - dy;
									SetTempStackableDebugInfo(TempStackable, D1, D2, Edge, Final);
									ObjectSprite->LastDestination.push_back({ xPos + NewXDistance + x, yPos + NewYDistance - dy });
								}
								//Tp on the dy, but slide down the dx
								else if (dy > dx) {
									Final[0] = NewXDistance + dx;
									Final[1] = NewYDistance - y;
									SetTempStackableDebugInfo(TempStackable, D1, D2, Edge, Final);
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
							Final[0] = NewXDistance + x;
							Final[1] = NewYDistance;
							SetTempStackableDebugInfo(TempStackable, D1, D2, Edge, Final);
							ObjectSprite->LastDestination.push_back({ xPos + NewXDistance + x, yPos + NewYDistance });
						}
						else {
							Final[0] = NewXDistance  ;
							Final[1] = NewYDistance;
							SetTempStackableDebugInfo(TempStackable, D1, D2, Edge, Final);
							ObjectSprite->LastDestination.push_back({ xPos + NewXDistance, yPos + NewYDistance });
						}
					}
					else if (Measure == 14) {
						if (x != 0) { 
							Final[0] = NewXDistance - x;
							Final[1] = NewYDistance;
							SetTempStackableDebugInfo(TempStackable, D1, D2, Edge, Final);
							ObjectSprite->LastDestination.push_back({ xPos + NewXDistance - x, yPos + NewYDistance });
						}
						else {
							Final[0] = NewXDistance;
							Final[1] = NewYDistance;
							SetTempStackableDebugInfo(TempStackable, D1, D2, Edge, Final);
							ObjectSprite->LastDestination.push_back({ xPos + NewXDistance, yPos + NewYDistance });
						}
					}
					else if (Measure == 9) {

						if (y != 0) { 
							Final[0] = NewXDistance;
							Final[1] = NewYDistance + y;
							SetTempStackableDebugInfo(TempStackable, D1, D2, Edge, Final);
							printf("Final={%d, %d}, LastDestination = {%d, %d}\n", Final[0], Final[1], xPos + NewXDistance, yPos + NewYDistance + y);
							ObjectSprite->LastDestination.push_back({ xPos + NewXDistance , yPos + NewYDistance + y });
						}
						else {
							Final[0] = NewXDistance;
							Final[1] = NewYDistance;
							SetTempStackableDebugInfo(TempStackable, D1, D2, Edge, Final);
							ObjectSprite->LastDestination.push_back({ xPos + NewXDistance, yPos + NewYDistance });
						}
					}
					else if (Measure == 11) {
						if (y != 0) { 
							Final[0] = NewXDistance; 
							Final[1] = NewYDistance - y;
							SetTempStackableDebugInfo(TempStackable, D1, D2, Edge, Final);
							ObjectSprite->LastDestination.push_back({ xPos + NewXDistance  , yPos + NewYDistance - y });
						}
						else {
							Final[0] = NewXDistance;
							Final[1] = NewYDistance;
							SetTempStackableDebugInfo(TempStackable, D1, D2, Edge, Final);
							ObjectSprite->LastDestination.push_back({ xPos + NewXDistance, yPos + NewYDistance });
						}
					}
				}

				//Adjust Travel (The amount of space left to go to fulfill the velocity given to the sprite
				if (true) {
					if (Debug) {
						printf("Final = {%d, %d}\n", Final[0], Final[1]);
					}
					ObjectSprite->Travel[0] -= absolute(Final[0]); //0 <= Final <=TW //or something like taht
					ObjectSprite->Travel[1] -= absolute(Final[1]); //0 <= Final <=TH //or something like taht
					if (Debug) {
						printf("Object%d Travel = {%d, %d}\n", ObjectSprite->OrderCreation + 1, ObjectSprite->Travel[0], ObjectSprite->Travel[1]);
						//SDL_Delay(500);
						TempStackable->D1[0] = D1[0];
						TempStackable->D1[1] = D1[1];

						TempStackable->D2[0] = D2[0];
						TempStackable->D2[1] = D2[1];

						TempStackable->Edge[0] = Edge[0];
						TempStackable->Edge[1] = Edge[1];
					}
				}



				//Should we jostle, push to stack, or complete? (in moveallsprites)







				//WORK - figure out how to move now that we have Edge, Greater Diagonal, Lesser Diagonal overlaps,

				//dobule check this, but I think we'll update the last position to it's 'Final' and then deal with the stack, and the teleport when we get tothe main function.
				//We only figure out the final in the check future, since it's 'predicting' the future. The teleport and stack handling happens back in the MoveAllSprites3.
				//should update travel based on the EXVel that we're able to move in. For now, let's only remove the ones we are capable of moving in the direction of (moveAllSprites3).
				//then update FinalDestination




				//TempStackable
				//Up to 3 Sprite*'s for things we WOULD hit if moving to that position.
				//Up to 2 integers, for the 'safe' position to TP 



				//EXIT guard
				if (Debug) {
					printf("Attempt to figure out whether to Jostle, Complete, or Stack\n");
				}
				if (true) {
					int C = 0; //completed sprites hit
					int IC = 0; //incompleted sprites hit

					if (ObjectSprite->Travel[0] == 0 && ObjectSprite->Travel[1] == 0) {
						//mark as complete 
						ObjectSprite->Completed = 1;
						return 1;
					}
					else if (ObjectSprite->InStack==false) {
							if (Debug) { printf("HitSprites="); }
						for (int n = 0; n < 4; n++) {
							if (TempStackable->HitSprites[n] != nullptr) {
								if (Debug) { printf(".  "); }
								//check to see if it's marked as completed or not
								if (TempStackable->HitSprites[n]->Completed == 1) {
									C += 1;
								}
								else if (TempStackable->HitSprites[n]->Completed == 0 || TempStackable->HitSprites[n]->InStack==true) {
									IC += 1;
								} 
							}
						}
						if (Debug) { printf("\n"); }
						//if you only hit completed sprites (jostle again) (GIVEN your directionof travel)
						//if you only hit incomplete sprites (stack)
						//if you hit a completed sprite and an incomplete sprite (stack)
						if (Debug) {
							printf("C=%d, IC=%d\n", C, IC);
						}
						if (ObjectSprite->Measure == 5 || ObjectSprite->Measure == 7 || ObjectSprite->Measure == 13 || ObjectSprite->Measure == 15) {
							if (C == 2) {
								//mark as complete
								ObjectSprite->Completed = 1;
								return 1;
							}
							else if (C == 1 && IC == 1) {
								//push to stack
								ObjectSprite->InStack = true;
								return 0;
							}
							else if (IC == 2) {
								//push to stack
								ObjectSprite->InStack = true;
								return 0;
							}
							else if (C == 1 && IC == 0) {
								//jostle
								if (Debug) {
									printf("jostle 1\n");
								}
							}
							else if (C == 0 && IC == 1) {
								//stack
								ObjectSprite->InStack = true;
								return 0;
							}
							else if (C == 0 && IC == 0) {
								//jostle
								if (Debug) {
									printf("jostle 2\n");
								}
								//WORK for some reason, a diagonal does not seem to be counted among C or IC.
							}
						}
						else if (ObjectSprite->Measure == 6 || ObjectSprite->Measure == 14 || ObjectSprite->Measure == 9 || ObjectSprite->Measure == 11) {

							if (C == 1 && IC == 0) {
								//mark as complete
								ObjectSprite->Completed = 1;
								return 1;
							}
							else if (C == 0 && IC == 1) {
								//stack
								ObjectSprite->InStack = true;
								return 0;
							}
							else if (C == 0 && IC == 0) {
								//jostle
								if (Debug) {
									printf("jostle 3\n");
								}
							}
						}

					}
				}



			}
			else { //Measure==10, there's no need to check it's future
				return 1;
			}
		}
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
		CompletedSprites.resize(AllSprites.size()); //this way we can simply insert to this a null or a poitner if worked.
		for (auto x : CompletedSprites) {
			CompletedSprites[x] = 0;
		}
		for (int x = 0; x < AllSprites.size(); x++) { //for some reason I've got to do this. Likely the presets weren't saved or something in assignment default.
			AllSprites[x]->Completed = 0; 
			AllSprites[x]->InStack = false;
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
				if (AllSprites[i]->Completed == 0 && AllSprites[i]->InStack == false) { //If a sprite has not finished, and not in the stack
					if (Debug) {
						printf("CheckOverlap2\n");
					}

					//CheckOverlap2, CheckOverlapSTART2 <-NOTE, for now I'm storing all the sucessful end destinations, then erasing them all at the end of the Que handling. - however we may only ever need to store the most recent successful destination, or the last two.
					if (i == 0) {
						for (int s = 0; s < AllSprites.size(); s++) {
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
					RemoveSpriteFromMap2(AllSprites[i]);
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
							Measure = 10; //immediately mark as complete if the overlap doesn't change thigns so yea...
						}
					}
					AllSprites[i]->Measure = Measure; //new.
					if (Measure != 10) {

						if (Debug) {
							printf("New TempStackable\n");
						}

						TempStackable = new XYArr2;
						TempStackable->CurrentVictim = AllSprites[i]; //purely for the debug purposes. Shouldn't have t oeven make one until it's required.
						if (Debug) {
							printf("CheckFuture3\n");
						}

						int Outcome = CheckFuture3(AllSprites[i], TempStackable, Measure);
						if (Outcome == 1) {//if 1 = complete, if 0=stack, 
						//if 1, delete tempstackable, check the stack, mark investigates,make into a list of victims
						// Send list to VictimHandle,  attempt to move them, if there are no more incomplete sprites in their list.
						//if 0, push to stack
							if (Debug) { printf("TempStackable should be deleted, sprite either finished or got stopped by completed sprites\n"); }

						}
						else if (Outcome == 0) {
							if (Debug) { printf("Pushed TempStackable to the Stack!\n"); }
							SpriteStacks.push_back(TempStackable);
						}

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
								printf("|HitSprite Y: Object%d          |\n", TempStackable->HitSprites[1]->OrderCreation + 1);
							}
							else {
								printf("|HitSprite Y:                   |\n");
							}
							if (TempStackable->HitSprites[2] != nullptr) {
								printf("|HitSprite Greater D: Object%d  |\n", TempStackable->HitSprites[2]->OrderCreation + 1);
							}
							else {
								printf("|HitSprite Greater D:           |\n");
							}
							if (TempStackable->HitSprites[3] != nullptr) {
								printf("|HitSprite Lesser D: Object%d   |\n", TempStackable->HitSprites[3]->OrderCreation + 1);
							}
							else {
								printf("|HitSprite Lesser D:            |\n");
							}
							printf("|E={%d, %d}                       |\n", TempStackable->Edge[0], TempStackable->Edge[1]);
							printf("|D1={%d, %d}                      |\n", TempStackable->D1[0], TempStackable->D1[1]);
							printf("|D2={%d, %d}                      |\n", TempStackable->D2[0], TempStackable->D2[1]);
							printf("|F={%d, %d}                       |\n", TempStackable->Final[0], TempStackable->Final[1]);
							printf("_______________________________\n\n");
							if (AllSprites[i]->OrderCreation == 0) {
								SDL_Delay(500);
							}
						}





						if (AllSprites[i]->xPos != AllSprites[i]->LastDestination.back()[0] || AllSprites[i]->yPos != AllSprites[i]->LastDestination.back()[1]) {
							if (Debug) { printf("Sprite Moved, even if it did not complete it's movement! Check the Stack\n"); } 
							std::vector<int> InvestigateIndexs = {};
							//search for the moved sprite in the stack
							for (int d = 0; d < SpriteStacks.size(); d++) {
								for (int j = 0; j < SpriteStacks.size(); j++) {
									if (SpriteStacks[j]->HitSprites[j] == AllSprites[i]) {
										SpriteStacks[j]->HitSprites[j] = nullptr; //since it moved, it should no longer block the sprite.
										InvestigateIndexs.push_back(d); //Mark that particular tempstackable to attempt moving again, 
									}
								}
								if (Debug && d == SpriteStacks.size() - 1) { printf("Finished looking through the stack\n"); }

							}
							if (Debug) {
								printf("Stacks been looked at for Object%d.\n", AllSprites[i]->OrderCreation + 1);
							}

							//This while was an if. 
							//This while should  
							// 1)take care of interesting sprites. 
							// 2)Remove from SpriteStacks ONLY if it was compelted (this involves moving the whole vector :/)
							// 3)Increase the number of interesting sprites, when we get a successful move. 
							// 4)Help verify that the checkfuture does not have infinite IC cases, since we desire everything to slide and freeze when desired.
							//
							if (InvestigateIndexs.size() > 0) { //WORK - need ot think about how to move with IC surrounded sprites, such that we don't get an infinite loop, nor get out of order (try to move sprites greater than what you can), and still resovle timely.s
								if (Debug) { printf("Sprite Found. Attempt to move the other sprites\n"); }
								for (int d = 0; d < InvestigateIndexs.size(); d++) {
									XYArr2* ShortenAddress = SpriteStacks[InvestigateIndexs[d]];
									if (ShortenAddress->HitSprites[0] == nullptr && ShortenAddress->HitSprites[2] == nullptr && ShortenAddress->HitSprites[2] == nullptr && ShortenAddress->HitSprites[3] == nullptr) {
										//INSERT - this can be improved by asking for that victims measure first, then you only really need to check 1->4 per instead of all 4.
										RemoveSpriteFromMap2(AllSprites[i]);
										ResetTempStackable(ShortenAddress);
										if (Debug) { printf("STACK: CheckFuture(Object%d)\n", ShortenAddress->CurrentVictim->OrderCreation + 1); }
										CheckFuture3(ShortenAddress->CurrentVictim, ShortenAddress, ShortenAddress->CurrentVictim->Measure); //objectsprite, tempstackable, Measure. 
									
										ReMapSprite2(ShortenAddress->CurrentVictim);
									}
								}

							}




						}

					}
					else {
						if (Debug) {
							printf("\n_______________________________\n");
							printf("|TempStackable:N/A              |\n");
							printf("|CurrentVictim = Object%d        |\n", AllSprites[i]->OrderCreation + 1);
							printf("|HitSprite X:                   |\n");
							printf("|HitSprite Y:                   |\n");
							printf("|HitSprite Greater D:           |\n");
							printf("|HitSprite Lesser D:            |\n");
							printf("|E={%d, %d}                       |\n", 0, 0);
							printf("|D1={%d, %d}                      |\n", 0, 0);
							printf("|D2={%d, %d}                      |\n", 0, 0);
							printf("|F={%d, %d}                       |\n", 0, 0);
							printf("_______________________________\n\n");
							if (AllSprites[i]->OrderCreation == 0) {
								SDL_Delay(500);
							}
						}
					}

				

					 





					 



					//NOTE - likely will actually put into the end of CheckFuture3, after travel is edited, and have it break when it's time to mark as completed or push to stack
					// using a while loop to conitnously jostle it until then.
					//Should we jostle, push to stack, or complete?
					 








					ReMapSprite2(AllSprites[i]);
					//if all HitCollision is compelte, or nothing, update Latest 'viable positoin'.
					//then pause, 
					//if Travel is empty, then mark as completed.
					//remap (based on last viable position) 
					//If you updated viable position, push self to stack, Search the stack, remove any children, investigate, handle victim list
					if (Debug) {
						printf("Remapped Sprite.\nThat's all\n");
					}
				}
				else if (Debug) {
					printf("Completed or in Stack\n");
				}
			}
			if (Debug) {
				printf("\n\n\nFinished AllSprite for loop\n");
				printf("For now itterate completed\n\n\n"); 
				Completed =AllSprites.size();
				for (int i = 0; i < AllSprites.size(); i++) {
					AllSprites[i]->xPos = AllSprites[i]->LastDestination.back()[0];
					AllSprites[i]->yPos = AllSprites[i]->LastDestination.back()[1];
					AllSprites[i]->Completed = 0;
					AllSprites[i]->InStack = false;
					AllSprites[i]->LastDestination.clear();
				}
			}
		}
	}


	void RemoveSpriteFromMap2(Sprite* ObjectSprite) {
		// printf("RemoveSpriteFromMap\n");
		bool Debug = false;
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