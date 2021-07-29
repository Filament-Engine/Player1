#pragma once
#include <stdlib.h> // this is for the random function





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
		printf("Allocating a vector of size %d", AllSprites.size());
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
		if (TempX2Math== 0) {
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
				while (OrderedPosition<LM[y1][x2].size() && LM[y1][x2][OrderedPosition]->OrderCreation < ObjectSprite->OrderCreation) {
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
	



	void Hopper(XYArr* Sorter) {
		printf("The last two overlaps were not from the same item. We'll figure out which is greater\n"); //if neither is greater, lets go with x.

		//get the x overlap
		printf("Sprite was moving Left\n");
		int x = Sorter ->SpriteXCollision.size();
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
					Sorter->SpriteXCollision.erase(Sorter->SpriteXCollision.begin()+i); //IF WE NEVER HAVE TO KNOW THE REST OF THESE COLLISIONS, DO NOT BOTHER ERASING. IT IS TIMELY FOR LARGE VECTORS
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
		bool Debug =false;
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
			int xOverlapped =0; //used exclusively to test for true collision dimension
			int yOverlapped =0; //used exclusively to test for true collision dimension.
			

		




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
								xOverlapped = ObjectSprite->xPos +TILE_WIDTH - LM[y2][x2][i]->xPos;
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
						if ((xOverlapped >0 && xOverlapped<17) && TempYOverlap < 17 && TempYOverlap > 0) {
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

		//end of Jacks insertion. I should check this later.

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
			if ( (SpriteOverlapY.size() > 0 || SpriteOverlapX.size() > 0)) {
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
	void MergeSortSpriteCollision(std::vector<Sprite*> & SpriteOverlap, std::vector<int>& SpriteArea) { //we will be editing directly onto it
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
		bool endofstackX=false;
		bool endofstackY=false;

		for (int i = 0; i < AllSprites.size(); i++) { //{1, 4, 8, 10}


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
					if (Queue2[i]->OrderCreation == 7) {
						printf("Object8 original position = {%d, %d}\n", Queue2[i]->xPos, Queue2[i]->yPos);
					}
					Queue2[i]->Behavior();
					if (Queue2[i]->OrderCreation == 7) {
						printf("Object8 attempt position = {%d, %d}\n", Queue2[i]->xPos, Queue2[i]->yPos);
					}
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
						if (Queue2[i]->OrderCreation == 7) {
							printf("Object8 Success position = {%d, %d}\n", Queue2[i]->xPos, Queue2[i]->yPos);
						}
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
							if (SpriteStacks[d]->SpriteXCollision.size() > 0 && Queue2[i] == SpriteStacks[d]->SpriteXCollision[SpriteStacks[d]->SpriteXCollision.size() - 1]) {
								SpriteStacks[d]->SpriteXCollision.pop_back();
								InvestigateIndexsX.push_back(d);
								while (SpriteStacks[d]->SpriteXCollision.size() > 0 && CompletedSprites[d] == 1) { //while there are things left to pop AND they have already successfully moved - will break when either your out of things to pop, or those items are ahead of the original Sprite you popped.
									SpriteStacks[d]->SpriteXCollision.pop_back();
									//InvestigateIndexsX.push_back(d); //already pushed back
								}

							} 
							if (SpriteStacks[d]->SpriteYCollision.size() > 0 && Queue2[i] == SpriteStacks[d]->SpriteYCollision[SpriteStacks[d]->SpriteYCollision.size() - 1]) {
								SpriteStacks[d]->SpriteYCollision.pop_back();
								InvestigateIndexsY.push_back(d);
								while (SpriteStacks[d]->SpriteYCollision.size() > 0   && CompletedSprites[d] == 1) { //while there are things left to pop AND they have already successfully moved - will break when either your out of things to pop, or those items are ahead of the original Sprite you popped.
									SpriteStacks[d]->SpriteYCollision.pop_back();
									//InvestigateIndexsY.push_back(d); //already pushed back
								}
							} 
						}
						if (Debug) {
							printf("Stacks been looked at for Object%d.\n", Queue2[i]->OrderCreation + 1);
						}
						if (InvestigateIndexsY.size() > 0 || InvestigateIndexsX.size() > 0) {
							if (Debug) {
								printf("Start Handle\n");
							}
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
						if (Queue2[i]->OrderCreation == 7) {
							printf("Object8 fail position = {%d, %d}\n", Queue2[i]->xPos, Queue2[i]->yPos);
						}
						if (TempStackable->Victim->OrderCreation == 7) {
							printf("Object8 stack looks like :\n");
							printf("SpriteX ={");
							for (int j = 0; j < TempStackable->SpriteXCollision.size(); j++) {
								printf("%d, ", TempStackable->SpriteXCollision[j]->OrderCreation+1);
							}
							printf("}\n");
							printf("SpriteY ={");
							for (int j = 0; j < TempStackable->SpriteYCollision.size(); j++) {
								printf("%d, ", TempStackable->SpriteYCollision[j]->OrderCreation + 1);
							}
							printf("}\n");
						}
						if (Debug) {
							printf("Push back the temp stack\n");
						}
						SpriteStacks.push_back(TempStackable); //do not delete until it is handled. Just overwrite Tempstackable poitner with new XYArr

						//NOTE Sprite with creation order 'i' has NOT completed it's movement. If it ever does, in relation to a stack handled elsewhere, then it shall be noted in CompletedSprites
						Queue2[i]->UndoBehavior();
						if (Queue2[i]->OrderCreation == 7) {
							printf("Object8 'original' [Undo] position = {%d, %d}\n", Queue2[i]->xPos, Queue2[i]->yPos);
						}
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
				printf("Object%d, Current Position = {%d, %d}, Old Position = {%d, %d}, Velocities = {%d, %d}, Direction = %d\n", AllSprites[i]->OrderCreation+1, AllSprites[i]->xPos, AllSprites[i]->yPos, AllSprites[i]->xPos - AllSprites[i]->xVec, AllSprites[i]->yPos - AllSprites[i]->yVec, AllSprites[i]->xVec, AllSprites[i]->yVec, Direction);
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
		if (true){ //CheckOverlap(AllSprites[7])) { //interested in object 8 rn
			if (TIME < 17) {
				for (int i = 0; i < AllSprites.size(); i++) {
					if (CheckOverlap(AllSprites[i])) {
						SDL_Delay(600000);
					}
				}
			}
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
		//SDL_Delay(250);
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
				printf("Object%d, ", VictimsNoLonger[i]->OrderCreation+1);
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
		while (VictimsNoLonger.size() != 0) {
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
		//move victim,
		if (Debug) {
			printf("Try to move Object%d [handlevictim]\n", CurrentVictim->OrderCreation + 1);
		}
		RemoveSpriteFromMap(CurrentVictim);
		CurrentVictim->Behavior();
		XYArr* TempStackable; //used to just see if it's empty or not
		TempStackable = new XYArr; //besure to delete before leaving function.
		CheckFutureSpritePosition2(CurrentVictim, TempStackable);
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
				printf("Size of Temp Stackable = %d\n", TempStackable->SpriteXCollision.size());
				printf("Size of Temp Stackable Y%d\n", TempStackable->SpriteYCollision.size());

			}
			int x = TempStackable->SpriteXCollision.size(); // this is done so the same function is not called multiple times
			int y = TempStackable->SpriteYCollision.size(); // this is done so the same function is not called multiple times

			if (true) {
				printf("Teleport! Object%d\n", CurrentVictim->OrderCreation + 1);
			}











			bool wait = false;


			/*
			XC = CurrentVictim->xPos + TILE_WIDTH - TempStackable->SpriteXCollision[x - 1]->xPos; //object 4={64, 0}, obj5 ={79, 0}. 64+16-79=1, so 79+1 is where obj 5 would be without overlap. 
						printf("Attempt 1: XC = %d\n", XC);
						XC = TempStackable->SpriteXCollision[x - 1]->xPos + TILE_WIDTH - CurrentVictim->xPos; //object 4={64, 0}, obj5 ={79, 0}. 64+16-79=1, so 79+1 is where obj 5 would be without overlap.
						printf("Attempt 2: XC = %d\n", XC);
						if (XC > 16 || XC< 0) {
							XC = CurrentVictim->xPos + TILE_WIDTH - TempStackable->SpriteXCollision[x - 1]->xPos; //object 4={64, 0}, obj5 ={79, 0}. 64+16-79=1, so 79+1 is where obj 5 would be without overlap. 
							printf("Attempt 3: XC = %d\n", XC);
						}
		*/
			 
			if (CurrentVictim->OrderCreation == 1) {
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
				if (TempStackable->SpriteXCollision.back() != TempStackable->SpriteYCollision.back()) {
					printf("The ends of these two  vectors are not the same!\n Attempt to grab the one with the highest collision on a given axis, then make them both match for appropriate undo movements!\n");
					printf("Hopper init\n");
					Hopper(TempStackable);
					printf("Hopper end\n");
					if (CurrentVictim->OrderCreation == 1) {
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
				}
			}




			if (x > 0 && y > 0) { 
				if (xChange != 0 && yChange != 0) {
					int XC;
					int YC;
					//calculate overlap according to direction
					if (xChange > 0) { // if moving right
						printf("Sprite was moving Right\n");
						 
						if (TempStackable->SpriteXCollision[x - 1]->xPos > CurrentVictim->xPos) {
							XC = CurrentVictim->xPos + TILE_WIDTH - TempStackable->SpriteXCollision[x - 1]->xPos; //object 4={64, 0}, obj5 ={79, 0}. 64+16-79=1, so 79+1 is where obj 5 would be without overlap. 
							printf("Attempt 1: XC = %d\n", XC);
						}
						else {
							XC = TempStackable->SpriteXCollision[x - 1]->xPos + TILE_WIDTH - CurrentVictim->xPos; //object 4={64, 0}, obj5 ={79, 0}. 64+16-79=1, so 79+1 is where obj 5 would be without overlap.
							printf("Attempt 2: XC = %d\n", XC);
						}

						if (XC > 16 || XC < 0) {
							XC = CurrentVictim->xPos + TILE_WIDTH - TempStackable->SpriteXCollision[x - 1]->xPos; //object 4={64, 0}, obj5 ={79, 0}. 64+16-79=1, so 79+1 is where obj 5 would be without overlap. 
							printf("Attempt 3: XC = %d\n", XC);
						}

						if (XC == 16) {
							XC = 0;
						}
						printf("1 TempOverlapX=%d\n", XC);
						pause = true;
						 
					}
					else { // if moving left
						printf("Sprite was moving Left\n");
						XC = CurrentVictim->xPos + TILE_WIDTH - TempStackable->SpriteXCollision[x - 1]->xPos; //object 4={64, 0}, obj5 ={79, 0}. 64+16-79=1, so 79+1 is where obj 5 would be without overlap. 
						printf("Attempt 1: XC = %d + %d - %d = %d\n", CurrentVictim->xPos, TILE_WIDTH, TempStackable->SpriteXCollision[x-1]->xPos, XC);
						XC = TempStackable->SpriteXCollision[x - 1]->xPos + TILE_WIDTH - CurrentVictim->xPos; //object 4={64, 0}, obj5 ={79, 0}. 64+16-79=1, so 79+1 is where obj 5 would be without overlap.
						printf("Attempt 2: XC = %d\n", XC);
						if (XC > 16 || XC < 0) {
							XC = CurrentVictim->xPos + TILE_WIDTH - TempStackable->SpriteXCollision[x - 1]->xPos; //object 4={64, 0}, obj5 ={79, 0}. 64+16-79=1, so 79+1 is where obj 5 would be without overlap. 
							printf("Attempt 3: XC = %d\n", XC);
						}
						if (XC == 16) {
							XC = 0;
						}
						printf("2 TempOverlapX=%d\n", XC);
						pause = true;
						 
					}
					if (yChange > 0) { // if moving down
						printf("Sprite was moving down\n"); 
						YC = CurrentVictim->yPos + TILE_HEIGHT - TempStackable->SpriteYCollision[y - 1]->yPos; //insert virtually the same check used for checkfuture 2, to ensure consistency among objects that move morethan 1 pxl at a time.
						printf("Attempt 1: YC = %d\n", YC);
						YC = TempStackable->SpriteYCollision[y - 1]->yPos + TILE_HEIGHT - CurrentVictim->yPos; //insert virtually the same check used for checkfuture 2, to ensure consistency among objects that move morethan 1 pxl at a time.
						printf("Attempt 2: YC = %d\n", YC);
						if (YC > 16 || YC < 0) {
							YC = CurrentVictim->yPos + TILE_HEIGHT - TempStackable->SpriteYCollision[y - 1]->yPos; //insert virtually the same check used for checkfuture 2, to ensure consistency among objects that move morethan 1 pxl at a time.
							printf("Attempt 3: YC = %d\n", YC);
						}
						if (YC == 16) {
							YC = 0;
						}
						printf("3 TempOverlapY=%d\n", YC);
						pause = true;
						 
					} 
					else { // if moving up
						printf("Sprite was moving up\n");
						YC = CurrentVictim->yPos + TILE_HEIGHT - TempStackable->SpriteYCollision[y - 1]->yPos; //insert virtually the same check used for checkfuture 2, to ensure consistency among objects that move morethan 1 pxl at a time.
						printf("Attempt 1: YC = %d\n", YC);
						YC = TempStackable->SpriteYCollision[y - 1]->yPos + TILE_HEIGHT - CurrentVictim->yPos; //insert virtually the same check used for checkfuture 2, to ensure consistency among objects that move morethan 1 pxl at a time.
						printf("Attempt 2: YC = %d\n", YC);
						if (YC > 16 || YC < 0) {
							YC = CurrentVictim->yPos + TILE_HEIGHT - TempStackable->SpriteYCollision[y - 1]->yPos; //insert virtually the same check used for checkfuture 2, to ensure consistency among objects that move morethan 1 pxl at a time.
							printf("Attempt 3: YC = %d\n", YC);
						}
						if (YC == 16) {
							YC = 0;
						}
						//YC = CurrentVictim->yPos + TILE_WIDTH - TempStackable->SpriteYCollision[y - 1]->yPos; //insert virtually the same check used for checkfuture 2, to ensure consistency among objects that move morethan 1 pxl at a time.
						printf("4 TempOverlapY=%d\n", YC);
						pause = true;
						 
					}



					//using that overlap, determine one of three cases
					if (XC == 1 && YC == 1) { //base it off of the vVec of the object in question. If it just overlapped according to one movement or less, then we can be relatively certain that the mroe meaningful overlap should be taken.
						//teleport both appropriately
						//are you going directional, or diagonal.
					
						//if diagonal,  
						if (TempStackable->SpriteXCollision[x - 1] == TempStackable->SpriteYCollision[y - 1]) { //the overlap is the same object, same distance
							//thus we need to figure out which to back out of, and which to move forward thorugh.
							
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
							int TempY2Math = oldy +16 - TILE_HEIGHT * ((oldy +16) / TILE_HEIGHT); //A = C - B * (C/B) 
							int TempX2Math = oldx+16 - TILE_WIDTH * ((oldx+16) / TILE_WIDTH);
							if (TempX2Math == 0) {

							}
							if (TempY2Math == 0) {

							}
							if (CurrentVictim->xVec > 0 && CurrentVictim->yVec > 0) { //Right, Down
								
								


							}

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

					}
					else if (XC == 1) { //if it is not less, or is the vec, then we should move accordingly
						printf("Diag x, checkfuture 2\n");
						if (xChange > 0) { //right
							CurrentVictim->TeleportX(CurrentVictim->xPos - XC);
						}
						else {//left
							CurrentVictim->TeleportX(CurrentVictim->xPos + XC);
						} 
						//temporary, just to get updates x and y overlaps of interest, to prevent the 8 9 glitcch detailed in notebook
						CheckFutureSpritePosition2(CurrentVictim, TempStackable);
						y = TempStackable->SpriteYCollision.size();
						if (y > 0) {
							if (yChange > 0) { // if moving down
								printf("Sprite was moving down\n");
								YC = CurrentVictim->yPos + TILE_HEIGHT - TempStackable->SpriteYCollision[y - 1]->yPos; //insert virtually the same check used for checkfuture 2, to ensure consistency among objects that move morethan 1 pxl at a time.
								printf("Attempt 1: YC = %d\n", YC);
								YC = TempStackable->SpriteYCollision[y - 1]->yPos + TILE_HEIGHT - CurrentVictim->yPos; //insert virtually the same check used for checkfuture 2, to ensure consistency among objects that move morethan 1 pxl at a time.
								printf("Attempt 2: YC = %d\n", YC);
								if (YC > 16 || YC < 0) {
									YC = CurrentVictim->yPos + TILE_HEIGHT - TempStackable->SpriteYCollision[y - 1]->yPos; //insert virtually the same check used for checkfuture 2, to ensure consistency among objects that move morethan 1 pxl at a time.
									printf("Attempt 3: YC = %d\n", YC);
								}
								if (YC == 16) {
									YC = 0;
								}
								printf("3 TempOverlapY=%d\n", YC);
								pause = true;

							}
							else { // if moving up
								printf("Sprite was moving up\n");
								YC = CurrentVictim->yPos + TILE_HEIGHT - TempStackable->SpriteYCollision[y - 1]->yPos; //insert virtually the same check used for checkfuture 2, to ensure consistency among objects that move morethan 1 pxl at a time.
								printf("Attempt 1: YC = %d\n", YC);
								YC = TempStackable->SpriteYCollision[y - 1]->yPos + TILE_HEIGHT - CurrentVictim->yPos; //insert virtually the same check used for checkfuture 2, to ensure consistency among objects that move morethan 1 pxl at a time.
								printf("Attempt 2: YC = %d\n", YC);
								if (YC > 16 || YC < 0) {
									YC = CurrentVictim->yPos + TILE_HEIGHT - TempStackable->SpriteYCollision[y - 1]->yPos; //insert virtually the same check used for checkfuture 2, to ensure consistency among objects that move morethan 1 pxl at a time.
									printf("Attempt 3: YC = %d\n", YC);
								}
								if (YC == 16) {
									YC = 0;
								}
								//YC = CurrentVictim->yPos + TILE_WIDTH - TempStackable->SpriteYCollision[y - 1]->yPos; //insert virtually the same check used for checkfuture 2, to ensure consistency among objects that move morethan 1 pxl at a time.
								printf("4 TempOverlapY=%d\n", YC);
								pause = true;

							}
							if (yChange > 0) { //down
								printf("Current y=%d\n", CurrentVictim->yPos);
								printf("Down, = %d\n", CurrentVictim->yPos - YC);
								CurrentVictim->TeleportY(CurrentVictim->yPos - YC);
							}
							else {//up
								printf("Current y=%d\n", CurrentVictim->yPos);
								printf("Up, = %d\n", CurrentVictim->yPos + YC);
								CurrentVictim->TeleportY(CurrentVictim->yPos + YC);
							}
						}
					}
					else if (YC == 1) {
						printf("Diag y, checkfuture 2\n");
						if (yChange > 0) { //down
							printf("Current y=%d\n", CurrentVictim->yPos);
							printf("Down, = %d\n", CurrentVictim->yPos - YC);
							CurrentVictim->TeleportY(CurrentVictim->yPos - YC);
						}
						else {//up
							printf("Current y=%d\n", CurrentVictim->yPos);
							printf("Up, = %d\n", CurrentVictim->yPos + YC);
							CurrentVictim->TeleportY(CurrentVictim->yPos + YC);
						}
						CheckFutureSpritePosition2(CurrentVictim, TempStackable);
						x = TempStackable->SpriteXCollision.size();
						if (x > 0) {
							if (xChange > 0) { // if moving right
								printf("Sprite was moving Right\n");
								if (TempStackable->SpriteXCollision[x - 1]->xPos > CurrentVictim->xPos) {
									XC = CurrentVictim->xPos + TILE_WIDTH - TempStackable->SpriteXCollision[x - 1]->xPos; //object 4={64, 0}, obj5 ={79, 0}. 64+16-79=1, so 79+1 is where obj 5 would be without overlap. 
									printf("Attempt 1: XC = %d\n", XC);
								}
								else {
									XC = TempStackable->SpriteXCollision[x - 1]->xPos - CurrentVictim->xPos; //object 4={64, 0}, obj5 ={79, 0}. 64+16-79=1, so 79+1 is where obj 5 would be without overlap.
									printf("Attempt 2: XC = %d\n", XC);
								}

								if (XC > 16 || XC < 0) {
									XC = CurrentVictim->xPos + TILE_WIDTH - TempStackable->SpriteXCollision[x - 1]->xPos; //object 4={64, 0}, obj5 ={79, 0}. 64+16-79=1, so 79+1 is where obj 5 would be without overlap. 
									printf("Attempt 3: XC = %d\n", XC);
								}

								if (XC == 16) {
									XC = 0;
								}
								printf("1 TempOverlapX=%d\n", XC);
								pause = true;

							}
							else { // if moving left
								printf("Sprite was moving Left\n");
								XC = CurrentVictim->xPos + TILE_WIDTH - TempStackable->SpriteXCollision[x - 1]->xPos; //object 4={64, 0}, obj5 ={79, 0}. 64+16-79=1, so 79+1 is where obj 5 would be without overlap. 
								printf("Attempt 1: XC = %d\n", XC);
								XC = TempStackable->SpriteXCollision[x - 1]->xPos + TILE_WIDTH - CurrentVictim->xPos; //object 4={64, 0}, obj5 ={79, 0}. 64+16-79=1, so 79+1 is where obj 5 would be without overlap.
								printf("Attempt 2: XC = %d\n", XC);
								if (XC > 16 || XC < 0) {
									XC = CurrentVictim->xPos + TILE_WIDTH - TempStackable->SpriteXCollision[x - 1]->xPos; //object 4={64, 0}, obj5 ={79, 0}. 64+16-79=1, so 79+1 is where obj 5 would be without overlap. 
									printf("Attempt 3: XC = %d\n", XC);
								}
								if (XC == 16) {
									XC = 0;
								}
								printf("2 TempOverlapX=%d\n", XC);
								pause = true;

							}
							if (xChange > 0) { //right
								CurrentVictim->TeleportX(CurrentVictim->xPos - XC);
							}
							else {//left
								CurrentVictim->TeleportX(CurrentVictim->xPos + XC);
							}
						}
					}

					else {
						//should be able to handle things ^ up there where it's not quiet a full vec move too. for now lets just get one pixel at a time movement working.
						printf("Are you sure that the vec is 1?\n"); 
					}

					if (YC > 15 || YC < 0) {
						printf("We've got a problem sir!\n");
						wait = true;
					}
					if (XC > 15 || XC < 0) {
						printf("We've got a problem sir!\n");
						wait = true;
					}

				}
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
				SDL_Delay(600000);
				wait = false;
			}



			/* 
			if (x > 0) { // this is a check just to make sure the spriteXCollision is not empty
				if (xChange > 0) { // if moving right
					printf("Sprite was moving Right\n");
					if (CurrentVictim->TargetTile->x + TILE_WIDTH <= TempStackable->SpriteXCollision[x - 1]->TargetTile->x) { // this is just making sure that the x position of Current Victim is more left than the TempStackable one
						//CurrentVictim->TeleportX(TempStackable->SpriteXCollision[x - 1]->xPos - TILE_WIDTH);
						int TempOverlapX = TempStackable->SpriteXCollision[x - 1]->xPos + TILE_WIDTH - CurrentVictim->xPos; //object 4={64, 0}, obj5 ={79, 0}. 64+16-79=1, so 79+1 is where obj 5 would be without overlap.
						printf("1 TempOverlapX=%d\n", TempOverlapX);
						CurrentVictim->TeleportX(CurrentVictim->xPos + TempOverlapX);
						pause = true;
					}
					else {
						int TempOverlapX =   CurrentVictim->xPos + TILE_WIDTH - TempStackable->SpriteXCollision[x - 1]->xPos; //object 4={64, 0}, obj5 ={79, 0}. 64+16-79=1, so 79+1 is where obj 5 would be without overlap.
						printf("2 TempOverlapX=%d\n", TempOverlapX);				
						CurrentVictim->TeleportX(CurrentVictim->xPos + TempOverlapX);
						pause = true;
					}
				}


				else { // if moving left
					printf("Sprite was moving Left\n");
					if (CurrentVictim->TargetTile->x >= TempStackable->SpriteXCollision[x - 1]->TargetTile->x + TILE_WIDTH) { // this checks to make sure the x position of the victim is more right than the sprite it's collidiing with
						//CurrentVictim->TeleportX(TempStackable->SpriteXCollision[x - 1]->xPos + TILE_WIDTH);
						int TempOverlapX = CurrentVictim->xPos + TILE_WIDTH - TempStackable->SpriteXCollision[x - 1]->xPos; //insert virtually the same check used for checkfuture 2, to ensure consistency among objects that move morethan 1 pxl at a time.
						printf("3 TempOverlapX=%d\n", TempOverlapX);
						CurrentVictim->TeleportX(CurrentVictim->xPos + TempOverlapX);
						pause = true;
					}
					else {
						int TempOverlapX = CurrentVictim->xPos + TILE_WIDTH - TempStackable->SpriteXCollision[x - 1]->xPos; //insert virtually the same check used for checkfuture 2, to ensure consistency among objects that move morethan 1 pxl at a time.
						printf("4 TempOverlapX=%d\n", TempOverlapX);				
						CurrentVictim->TeleportX(CurrentVictim->xPos + TempOverlapX);
						pause = true;
					}
				}
			}
			 
			if (y > 0) { // this is a check just to make sure the spriteYCollision is not empty
				if (yChange > 0) { // if moving down
					printf("Sprite was moving down\n");
					//The check below seems to be erroneous :/
					if (CurrentVictim->TargetTile->y + TILE_HEIGHT <= TempStackable->SpriteYCollision[y - 1]->TargetTile->y) { // this is just making sure that the y position of Current Victim is above than the TempStackable one
						//CurrentVictim->TeleportY(TempStackable->SpriteYCollision[y - 1]->yPos - TILE_HEIGHT);
						int TempOverlapY = CurrentVictim->yPos + TILE_WIDTH - TempStackable->SpriteYCollision[y - 1]->yPos; //insert virtually the same check used for checkfuture 2, to ensure consistency among objects that move morethan 1 pxl at a time.
						printf("5 TempOverlapY=%d\n", TempOverlapY);
						CurrentVictim->TeleportY(CurrentVictim->yPos - TempOverlapY);
						pause = true;
					}
					//inserted because above is eroneous
					else {
						int TempOverlapY = CurrentVictim->yPos + TILE_WIDTH - TempStackable->SpriteYCollision[y - 1]->yPos; //insert virtually the same check used for checkfuture 2, to ensure consistency among objects that move morethan 1 pxl at a time.
						printf("6 TempOverlapY=%d\n", TempOverlapY);
						CurrentVictim->TeleportY(CurrentVictim->yPos - TempOverlapY);
						pause = true;
					}
				}



				else { // if moving up
					printf("Sprite was moving up\n");
					if (CurrentVictim->TargetTile->y >= TempStackable->SpriteYCollision[y - 1]->TargetTile->y + TILE_HEIGHT) { // this checks to make sure the y position of the victim is lower than the sprite it's collidiing with
						//CurrentVictim->TeleportY(TempStackable->SpriteYCollision[y - 1]->yPos + TILE_HEIGHT);
						int TempOverlapY = CurrentVictim->yPos + TILE_HEIGHT - TempStackable->SpriteYCollision[y - 1]->yPos; //insert virtually the same check used for checkfuture 2, to ensure consistency among objects that move morethan 1 pxl at a time.
						printf("7 TempOverlapY=%d\n", TempOverlapY);
						CurrentVictim->TeleportY(CurrentVictim->yPos + TempOverlapY);
						pause = true;
					}
					else {
						int TempOverlapY = CurrentVictim->yPos + TILE_HEIGHT - TempStackable->SpriteYCollision[y - 1]->yPos; //insert virtually the same check used for checkfuture 2, to ensure consistency among objects that move morethan 1 pxl at a time.
						printf("8 TempOverlapY=%d\n", TempOverlapY);
						CurrentVictim->TeleportY(CurrentVictim->yPos + TempOverlapY);
						pause = true;
					}
				}
			}//flag it for collision 
			*/






















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

					while (SpriteStacks[d]->SpriteXCollision.size() > 0 && CompletedSprites[d] == 1) { //while there are things left to pop AND they have already successfully moved - will break when either your out of things to pop, or those items are ahead of the original Sprite you popped.
						SpriteStacks[d]->SpriteXCollision.pop_back();
						if (!AlreadyPushedIndex) { //NEW

							InvestigateIndexsX.push_back(d); //do this after the while we insert.
							AlreadyPushedIndex = true;
						}
					}
				}
				AlreadyPushedIndex = false;
				if (SpriteStacks[d]->SpriteYCollision.size() > 0) {
					while (SpriteStacks[d]->SpriteYCollision.size() > 0 && CompletedSprites[d] == 1) {
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










	//archaic
	void CheckFutureSpritePosition(Sprite* ObjectSprite, int FutureCode[8]) {
		// printf("CheckFutureSpritePosition\n");
		int x1, x2, y1, y2;
		bool failx1 = false, failx2 = false, faily1 = false, faily2 = false;

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
		// printf("Tempx2Math = x2 -16*(x2/16) = %d, from %d, %d\n", TempX2Math, TILE_WIDTH, x2);
		// printf("(x2 modulo TILE_WIDTH) != 0, %d\n", TempX2);


		// printf("Check, x1:%d, y1:%d\n", x1, y1);

		// printf("Check, x2:%d, y2:%d\n", x2, y2);



		//this does need ot check two positions, no matter what, because we don't know if it would be slightly out of it's alignment.

		y1 = y1 / TILE_HEIGHT;
		y2 = y2 / TILE_HEIGHT;
		x1 = x1 / TILE_WIDTH;
		x2 = x2 / TILE_WIDTH;

		// printf("Check, x1:%d, x2:%d, y1:%d, y2:%d \n", x1, x2, y1, y2);

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
		// printf("Found approrpiate positions\n");
		//NOTE only one fail should happen, if multiple happen let it just undo the movement once, NO NEED FOR MORE THAN ONE UNDO		

		if (true) { //UL -always 'fail' for now. It will always be mapped primarily, as this is the only one we are guarenteed to check no matter it's position (whether it be %16=0, or not.
			//if (LM[y1][x1].size() > 0) {
			failx1 = true;
			faily1 = true;
			//}
		}
		if (x1 != x2 && TempX2Math != 0) { //UR 
			//this one isn't always supposed to fail, if %16 !=0, then fail and check, otherwise skip it.
			//if (LM[y1][x2].size() > 0) {
			faily1 = true;
			failx2 = true;
			//}
		}
		if (y1 != y2 && TempY2Math != 0) { //LL always should 'fail', unless y2%16=0, because then we need to check it's off center movement. 
			//if (LM[y2][x1].size() > 0) {//LL
			failx1 = true;
			faily2 = true;
			//}
			if (x1 != x2 && TempX2Math != 0) {
				//if (LM[y2][x2].size() > 0) { //LR
				failx2 = true;
				faily2 = true;
				//}
			}
		}
		// printf("Failsafes set\n");


		//CHECK/CHANGE - PRETTY SURE THIS DOES NOT RETUR ALL THE COLLISION VECTORS, SIMPLY BASED ON THAT if y is perfect, X MIGHT NOT BE.
		if (failx1 || failx2 || faily1 || faily2) { //Vector occupied!
			// printf("Object%d is trying to go to somewhere occupied\n", ObjectSprite->OrderCreation + 1); 

			if (faily1) {
				if (failx1) {

					FutureCode[0] = y1;
					FutureCode[1] = x1;
				}
				else {
					FutureCode[0] = -1;
					FutureCode[1] = -1;
				}
				if (failx2) {
					FutureCode[2] = y1;
					FutureCode[3] = x2;
				}
				else {
					FutureCode[2] = -1;
					FutureCode[3] = -1;
				}

			}
			else {

				FutureCode[0] = -1;
				FutureCode[1] = -1;
				FutureCode[2] = -1;
				FutureCode[3] = -1;
			}


			if (faily2) {
				if (failx1) {

					FutureCode[4] = y2;
					FutureCode[5] = x1;
				}
				else {
					FutureCode[4] = -1;
					FutureCode[5] = -1;

				}
				if (failx2) {
					FutureCode[6] = y2;
					FutureCode[7] = x2;
				}
				else {
					FutureCode[6] = -1;
					FutureCode[7] = -1;
				}

			}

			else {

				FutureCode[4] = -1;
				FutureCode[5] = -1;
				FutureCode[6] = -1;
				FutureCode[7] = -1;
			}





			// printf("You moving to: ");
			if (faily1) {
				if (failx1) {
					// printf("UL [%d, %d], ", y1, x1);
					if (LM[y1][x1].size() > 0) {
						// printf("Occupied, ");

					}
				}
				if (failx2) {
					// printf("UR [%d, %d], ", y1, x2);
					if (LM[y1][x2].size() > 0) {
						// printf("Occupied, ");

					}
				}
			}
			if (faily2) {
				if (failx1) {
					// printf("LL [%d, %d], ", y2, x1);
					if (LM[y2][x1].size() > 0) {
						// printf("Occupied, ");

					}
				}
				if (failx2) {
					// printf("LR [%d, %d], ", y2, x2);
					if (LM[y2][x2].size() > 0) {
						// printf("Occupied, ");

					}
				}
			}
			// printf("Corners\n"); //so if you collide form beneth, your gaurenteeed to collide with LL, even if your just clipping LR...

		}
		else {
			// printf("nothing hit\n"); //nothing ran into
			for (int i = 0; i < 8; i++) {
				FutureCode[i] = -1;
			}

		}

		if (ObjectSprite->OrderCreation == 0) {
			// DisplayTileBasedArray();

		}

	}
	//Object 2= R2, 3, C3, 4
	//Object 1 =R4, 5, C4, 5
	void MoveAllSprites() {
		std::vector<Sprite*> CollidedSprite1; //Upper Left Corner
		std::vector<Sprite*> CollidedSprite2; //Upper Right corner
		std::vector<Sprite*> CollidedSprite3; //Lower Left Corner
		std::vector<Sprite*> CollidedSprite4; //Lower Right Corner - fourth may be unnecessary
		int FutureCode[8]; //CHECK that the size is 8! including 0;
		//NOTE - If you get an error (when going between tiles) it is likely your moving xPos before removing it from the Matrix!!!!!
		//NOTE - Especially if it says something about the vector itterators in removespritefrommap()
		std::vector<Sprite*> InterestedStack;
		int InterestedStackIndex;
		//Reset
		ReCreateQue2();




		//Collision Loop
		for (int i = 0; i < std::distance(AllSprites.begin(), AllSprites.end()); i++) {
			//printf("3\n" );
			printf("Object%d to be moved\n", Queue2[i]->OrderCreation + 1);



			if (Queue2[i] != NULL) { //because the stack replaces with null, unless its the end of stack
				// printf("4\n");

				//Find the Que item, if it's in a stack, and resolve it.

				for (int j = 0; j < SpriteStackCounter; j++) {
					if (SpriteStack[j][SpriteStack[j].size() - 1]->OrderCreation == i) {
						InterestedStack = SpriteStack[j];
						InterestedStackIndex = j;
						printf("Interested Stack found\n");

					}
				}
				// printf("5\n");

				//Was not an end of stack
				if (InterestedStack.size() < 1) {
					RemoveSpriteFromMap(Queue2[i]);//Remove from map (So it doesn't collide with self)
					Queue2[i]->Behavior();//Adjust future position
					printf("B1\n");

					CheckFutureSpritePosition(Queue2[i], FutureCode); //Will it Collide?
					if (FutureCode[0] != -1) {
						printf("7.1\n");
						//CollidedSprite1 = LM[FutureCode[0]][FutureCode[1]];
						CollidedSprite1 = {};
						for (int d = 0; d < LM[FutureCode[0]][FutureCode[1]].size(); d++) {
							if (LM[FutureCode[0]][FutureCode[1]][d]->xPos + TILE_WIDTH > Queue2[i]->xPos) {

							}


						}


					}
					if (FutureCode[2] != -1) {
						// printf("(2, 3) y=%d, c=%d\n", FutureCode[2], FutureCode[3]);
						CollidedSprite2 = LM[FutureCode[2]][FutureCode[3]];
						// printf("7.2\n");
					}
					if (FutureCode[4] != -1) {
						// printf("(4, 5) y=%d, c=%d\n", FutureCode[4], FutureCode[5]);
						CollidedSprite3 = LM[FutureCode[4]][FutureCode[5]];
						// printf("7.3\n");
					}
					if (FutureCode[6] != -1) {
						// printf("(6, 7) y=%d, c=%d\n", FutureCode[6], FutureCode[7]);
						CollidedSprite4 = LM[FutureCode[6]][FutureCode[7]];
						// printf("7.4\n");
					}

					//If does not:
					if (CollidedSprite1.size() < 1 && CollidedSprite2.size() < 1 && CollidedSprite3.size() < 1 && CollidedSprite4.size() < 1) { //if there's nothing occupying the vector it's moving to.
						// printf("9\n");
						// printf("sizes of vectors(1,2,3,4)= %d, %d, %d, %d.\n", CollidedSprite1.size(), CollidedSprite2.size(), CollidedSprite3.size(), CollidedSprite4.size());
						//DisplayTileBasedArray();
						//Move it
						Queue2[i]->MoveTargetTileX();
						Queue2[i]->MoveTargetTileY();
						//Removeit from the Que
						//
						//Remap it - so that if a later tile tries moving there, it can't.
						// printf("9.5\n");
						ReMapSprite(Queue2[i]); //update position on the vector
						// printf("10\n");
						//printf("(if) Remapped Object%d\n", Queue2[i]->OrderCreation + 1);
						// printf("(if) Object%d x = %d \n", Queue2[i]->OrderCreation + 1, Queue2[i]->xPos);






						Queue2[i] = NULL;
					}


					//If it does:
					else { //if occupied tile
						// printf("11\n");

						//ASSUME TILE=PIXEL collision. 
						//undo the move stuff, until we confirm we can move later.
						// DisplayTileBasedArray();
						Queue2[i]->UndoBehavior();
						printf("U1\n");
						//Remap it, because it was unable to move right away



						// printf("12\n");


						//This starts the recurssion, so it will take itself out of the Que, 

						//IDEALLY, you check the pixels, then call the first one that failed, but contniue for all those in the vector that actually stopped it

						//NOTE - NEEDS WORK, WHAT IF THERE ARE TWO TILES, (ORDER THE COLLIDED SPRITE TO PRIROTIZE THE LEFT UPEPER CORNER, SO YOU CAN ASSUME OR SOMETHING, THEN CHECK THE OTHER IF APPLICABLE?)
						//add self to stack


						SpriteStack.push_back({});
						SpriteStack[SpriteStackCounter].push_back(Queue2[i]->GetThis());


						//remove self from que. NOTE - we can do this, because only the end of the stack will remain in the que. 
						Queue2[i] = NULL;
						// printf("13\n");

						MoveCurrentSprite(CollidedSprite1, CollidedSprite2, CollidedSprite3, CollidedSprite4, SpriteStackCounter, 0, 0, 0, 0); //there is up to two vectors, that we must order :/.
						// printf("14\n");
						//remap after so it doesn't run into itself when moving.
						ReMapSprite(SpriteStack[SpriteStackCounter][0]); //get around the null. May change later

						if (SpriteStack[SpriteStackCounter].size() == 0) {
							SpriteStack.erase(SpriteStack.begin() + SpriteStackCounter);
						}

						SpriteStackCounter += 1; //After recursion is done, we wait. If another stack is started it should happen in a new whole stack.
						// printf("15\n");

					}

				}

				//Was the end of stack
				else {
					// printf("Stack Found\n");
						//Try to move it now
						//It can - resolve next in stack, if it's a older item than the other stacks. (It's like solitare?) AND not past the rest of the que.
						// IF the stack has a younger item, reque it. It'll discover it at the end of this stack.
						//It can't - Delete the whole stack. It's all 'stuck'

					if (HandleStack(Queue2[i], InterestedStack, InterestedStack.size() - 1, InterestedStackIndex) == 0) {
						SpriteStack.erase(SpriteStack.begin() + InterestedStackIndex); //if it failed, then the stack should end immediately and never be checked again
						Queue2[i]->UndoBehavior();
						printf("U2\n");
						SpriteStackCounter -= 1;
					}

					Queue2[i] = NULL;

					//1 Start taking the stack down in pace. - for now only a sprite can be in one stack at a time
					//This is like MoveCurrent, except it's like this, but if it fails still, then it fails the entire stack. 
					//clear stack whence finished (internal). 

				}
				//DOUBLE CHECK THE STACK IS MORE THAN ONE IN THE LOOP, THEN YOU MAY NOT NEED HTE HANDLE FINAL STACK?!
				InterestedStack = {};
				InterestedStackIndex = 0; //shouldn't actually matter,

			}
		}
		//INSERT - final stack check
		//INSERT - TOTALLY CLEAN STACK, erase literally everything. (external too?)

		//Tries to handle end of que stacks. 
		while (SpriteStack.size() != 0) {
			// printf("!\n");
			InterestedStack = {};
			InterestedStackIndex = -1;
			for (int j = 0; j < SpriteStack.size(); j++) {
				// printf("? New J is %d\n", j);
				//eliminate empty stacks, restarts the for loop
				if (SpriteStack[j].size() < 1) {
					// printf("Attempt to erase SpriteStack[%d]\n", j);
					SpriteStack.erase(SpriteStack.begin() + j);
					j--;
					// printf("! Change J to %d", j); //so we should see it 'snap' back to it's proper position.
					continue;
				}
				//find the first viable stack
				if (InterestedStackIndex < 0) {
					// printf("Set itinital StackIndex\n");
					InterestedStackIndex = j;
				}
				//find the smallest end of stack possible
				if (SpriteStack[j][SpriteStack[j].size() - 1]->OrderCreation < SpriteStack[InterestedStackIndex][SpriteStack[InterestedStackIndex].size() - 1]->OrderCreation) {
					// printf("Found new smaller sprite for index\n");
					InterestedStackIndex = j;
				}
			}
			//NOW IF there still exists any stack
			if (SpriteStack.size() != 0) {
				// printf("SpriteStack not yet 0, attempt to handle the final stack here\n");
				if (HandleFinalStack(SpriteStack[InterestedStackIndex], SpriteStack[InterestedStackIndex].size() - 1) == 0) { //if succeeded in moving that item good, else if 0, then erase the whole stack. Perhaps mark if the item couldn't move so other stacks don't get any ideas.
					// printf("An item has failed, delete that stack\n");
					SpriteStack.erase(SpriteStack.begin() + InterestedStackIndex);
				}
			}


		}

		//use .popback of vectors to do 
		//HandleFinalStack - it's important it's not recursive, but just decides if the stack can compelte. If not, inavlidate that whole stack from that point up. 


		for (int j = 0; j < SpriteStack.size(); j++) {
			SpriteStack[j].clear();
			// printf("P");
		}
		SpriteStack.clear();
		SpriteStackCounter = 0;

	}
	//Recursive
	//function takes sprite ran into, tries moving, if fails, recursive until success.
	//On success, DON'T MOVE IT, until everything before the last item in the stack has been moved. Thus in AllSprites we must look each time
	//for when a stack can be completed... :/
	void MoveCurrentSprite(std::vector<Sprite*>& OldCollidedSprite1, std::vector<Sprite*>& OldCollidedSprite2, std::vector<Sprite*>& OldCollidedSprite3, std::vector<Sprite*>& OldCollidedSprite4, int Itter1, int Itter2, int Itter3, int Itter4, int InheritedSpriteStackCounter) {
		// printf("alrighty\n"); 
		//STUFF for NEW sprite, going outside  the current location
		std::vector<Sprite*> CollidedSprite1; //Upper Left Corner
		std::vector<Sprite*> CollidedSprite2; //Upper Right corner
		std::vector<Sprite*> CollidedSprite3; //Lower Left Corner
		std::vector<Sprite*> CollidedSprite4; //Lower Right Corner - fourth may be unnecessary
		int FutureCode[8]; //CHECK that the size is 8! including 0;

		//STUFF for CURRENT sprite, Before it can actually finish itself
		int size1 = OldCollidedSprite1.size(); //Upper Left
		int size2 = OldCollidedSprite2.size(); //Upper Right
		int size3 = OldCollidedSprite3.size(); //Lower Left
		int size4 = OldCollidedSprite4.size(); //Lower Right

		int itter1 = Itter1;
		int itter2 = Itter2;
		int itter3 = Itter3;
		int itter4 = Itter4;
		Sprite* ArrHolder[4]; //UL, UR, LL, LR
		Sprite* NextSprite = NULL;
		int CurrentStackCounter = InheritedSpriteStackCounter;
		std::vector<int> ItteratorToItter;

		//initialize Array
		for (int i = 0; i < 4; i++) {
			ArrHolder[i] = NULL;
		}



		//Fill Array with appropriate sprites
		if (itter1 < size1) {

			ArrHolder[0] = OldCollidedSprite1[itter1];
		}
		if (itter2 < size2) {

			ArrHolder[1] = OldCollidedSprite2[itter2];
		}
		if (itter3 < size3) {

			ArrHolder[2] = OldCollidedSprite3[itter3];
		}
		if (itter4 < size4) {

			ArrHolder[3] = OldCollidedSprite4[itter4];
		}

		// printf("ArrHolder's Set to either a Sprite or Null\n");

		//NOTE only move itters if we actually use the found tile in that vector, 


		//INSERT CHECK - there is a chance that an vecto rlooks like {1, 2, 3}, {2, 3}, and you hit 1 and 2, need a method to control IF you've seen it already. 
		//determine which Sprite is Created First
		for (int i = 0; i < 4; i++) {
			if (ArrHolder[i] != NULL) { //while NextSprite is a Sprite, try finding the lowest possible
				// printf("Arr%d = Object%d found\n", i, ArrHolder[i]->OrderCreation + 1);

				if (NextSprite == NULL) { //while we have nothing for smallest sprite
					NextSprite = ArrHolder[i];
					ItteratorToItter.push_back(i);
				}
				else if (NextSprite->OrderCreation == ArrHolder[i]->OrderCreation) {
					NextSprite = ArrHolder[i];
					ItteratorToItter.push_back(i);
				} //Sus out if a an item is the SAME as another in a vector collision
				else if (NextSprite->OrderCreation < ArrHolder[i]->OrderCreation) {
					NextSprite = ArrHolder[i];
					ItteratorToItter.clear();
					ItteratorToItter.push_back(i);

				} //Sus out if a sprite has priority over the previous ones we've been looking at.
			}

		}
		// printf("NextSprite Set\n");

		//itterate itterator
		if (NextSprite != NULL) { //may be unnecessary
			for (int i = 0; i < ItteratorToItter.size(); i++) {
				if (ItteratorToItter[i] == 0) {
					itter1++;
				}
				else if (ItteratorToItter[i] == 1) {
					itter2++;
				}
				else if (ItteratorToItter[i] == 2) {
					itter3++;
				}
				else if (ItteratorToItter[i] == 3) {
					itter4++;
				}
			}
			//




			// printf("Itterated itters\n");


			//remove from Que IF THIS IS NOT THE END OF STACK (Queue2[NextSprite->OrderCreation] = NULL;)
			// printf("Object%d x = %d, y = %d \n", NextSprite->OrderCreation + 1, NextSprite->xPos, NextSprite->yPos);

			//CHECK CHECK - CHECK - I THINK THIS WILL BE FINE HERE
			if (Queue2[NextSprite->OrderCreation] != NULL) { //If the NextSprite is not in a stack, AND still in hte Que
				// printf("16\n");
				//Remove from map (So it doesn't collide with self)
				printf("Object%d current sprite\n", Queue2[NextSprite->OrderCreation]->OrderCreation + 1);
				RemoveSpriteFromMap(NextSprite);
				//Adjust future position
				NextSprite->Behavior();
				printf("B2\n");
				// printf("17\n");
				//Will it Collide?
				CheckFutureSpritePosition(NextSprite, FutureCode);
				// printf("18\n");
				if (FutureCode[0] != -1) {
					CollidedSprite1 = LM[FutureCode[0]][FutureCode[1]];
				}
				if (FutureCode[2] != -1) {
					CollidedSprite2 = LM[FutureCode[2]][FutureCode[3]];
				}
				if (FutureCode[4] != -1) {
					CollidedSprite3 = LM[FutureCode[4]][FutureCode[5]];
				}
				if (FutureCode[6] != -1) {
					CollidedSprite4 = LM[FutureCode[6]][FutureCode[7]];
				}
				// printf("19\n");


				//If does not:
				if (CollidedSprite1.size() < 1 && CollidedSprite2.size() < 1 && CollidedSprite3.size() < 1 && CollidedSprite4.size() < 1) { //if there's nothing occupying the vector it's moving to.
					//Success, wait for main loop to move it. Then if it was done in the main loop, check if the next in this stack was less than what it was waiting for
					//Queue2[NextSprite->OrderCreation] = NULL; //we DONT want to set it to null, otherwise we'd have to check every number against the stack, instead of just the ends.
					// printf("20\n");
					SpriteStack[SpriteStackCounter].push_back(Queue2[NextSprite->OrderCreation]);
					// printf("Stack ended with the sprite Sprite%d\n", NextSprite->OrderCreation + 1);
					//NOTE - So it doesn't double up on hte movement in the Que loop. should find a better way of doing this.
					NextSprite->UndoBehavior(); //NEW
					printf("U3\n");
					ReMapSprite(NextSprite); //NEW
					// printf("20.5\n");
				}
				//If it does:
				else { //if occupied tile
					// printf("Stack can still grow\n");
					// DisplayTileBasedArray();
					// printf("21\n");

					//IDEALLY, you check the pixels, then call the first one that failed, but contniue for all those in the vector that actually stopped it
					//NOTE - NEEDS WORK, WHAT IF THERE ARE TWO TILES, (ORDER THE COLLIDED SPRITE TO PRIROTIZE THE LEFT UPEPER CORNER, SO YOU CAN ASSUME OR SOMETHING, THEN CHECK THE OTHER IF APPLICABLE?)
					//add self to stack
					SpriteStack[SpriteStackCounter].push_back(Queue2[NextSprite->OrderCreation]);
					// printf("21\n");
					//remove self from que. NOTE - we can do this, because only the end of the stack will remain in the que. 
					Queue2[NextSprite->OrderCreation] = NULL;
					// printf("22\n");
					MoveCurrentSprite(CollidedSprite1, CollidedSprite2, CollidedSprite3, CollidedSprite4, CurrentStackCounter, 0, 0, 0, 0); //there is up to two vectors, that we must order :/.
					// printf("23\n");


					NextSprite->UndoBehavior();
					printf("U4\n");
					//Remap it, because it was unable to move right away
					// printf("25\n");

					//NOTE the undo and remap after the stack, so when we resolve backwards we have a chance at finishing entire stacks if one part fails.
					ReMapSprite(Queue2[NextSprite->OrderCreation]);
					// printf("24\n");
					//May want to add one to the spritestack here, use spritestack^
//then assign old at the start to use V



				}
			}
			else {  //if EITHER NextSprite is in a Stack (Add it to the stack we're trying to go to, we'll have some way to mark if it's already been moved by a stack), OR in the QUE still. ASSUME QUE
				//NOTE - NEXT SPRITE WAS NULL IN QUE2 EITHER IT IS IN THE MIDDLE OF A QUE, OR CLAIMED BY THE QUE2 REGULAR 
				//eventually will need to check either the stack or the que to double check
				printf("NextSprite has already been claimed by EITHER by a different stack, or the regualr Que. For now, Assume Que\n");
				// printf("26\n");
				//NOTE - Don't leave the loop, since you may have other tiles to compare too later in the vector.
			}

		}
		else {
			printf("NextSprite was NULL (Not sure exactly what this is telling me besides the vectorss were all empty...?)\n");
			// printf("27\n");
		}




		//This is called to keep grinding away the current
		while (itter1 < size1 || itter2 < size2 || itter3 < size3 || itter4 < size4) {
			// printf("28\n");
			// printf("An Itter is still less than the size of a vector, %d, %d, %d, %d\n", itter1, itter2, itter3, itter4); //I know I've got to itterate it if it's the same sprite that I just looked at. Thus I'll need an expensive compare :/
			MoveCurrentSprite(OldCollidedSprite1, OldCollidedSprite2, OldCollidedSprite3, OldCollidedSprite4, itter1, itter2, itter3, itter4, CurrentStackCounter);

		}
	}
	//Object to move first, //the stack inside the stack to attempt to move //In hte internal stack, what's the index to move?
	int HandleStack(Sprite*& ObjectSprite, std::vector<Sprite*>& InterestedStack, int InternalStackIndex, int SpriteStackIndex) {
		//InternalStack = the last index, as this recursive, subtract one so long as it's not negative.
		if (InternalStackIndex > -1) {
			// printf("Handle Stack Appropriately\n");
			printf("Object%d to be handled\n", ObjectSprite->OrderCreation + 1);

			std::vector<Sprite*> CollidedSprite1; //Upper Left Corner
			std::vector<Sprite*> CollidedSprite2; //Upper Right corner
			std::vector<Sprite*> CollidedSprite3; //Lower Left Corner
			std::vector<Sprite*> CollidedSprite4; //Lower Right Corner - fourth may be unnecessary
			int FutureCode[8]; //CHECK that the size is 8! including 0;
			//NOTE - If you get an error (when going between tiles) it is likely your moving xPos before removing it from the Matrix!!!!!
			//NOTE - Especially if it says something about the vector itterators in removespritefrommap()

			// printf("Object%d in stack to be moved\n", ObjectSprite->OrderCreation+1);


			RemoveSpriteFromMap(InterestedStack[InternalStackIndex]);
			InterestedStack[InternalStackIndex]->Behavior();
			printf("B3\n");
			//Will it Collide?
			CheckFutureSpritePosition(InterestedStack[InternalStackIndex], FutureCode);
			if (FutureCode[0] != -1) {

				CollidedSprite1 = LM[FutureCode[0]][FutureCode[1]];

			}
			if (FutureCode[2] != -1) {

				CollidedSprite2 = LM[FutureCode[2]][FutureCode[3]];

			}
			if (FutureCode[4] != -1) {

				CollidedSprite3 = LM[FutureCode[4]][FutureCode[5]];

			}
			if (FutureCode[6] != -1) {

				CollidedSprite4 = LM[FutureCode[6]][FutureCode[7]];

			}


			//

			//If does not:
			if (CollidedSprite1.size() < 1 && CollidedSprite2.size() < 1 && CollidedSprite3.size() < 1 && CollidedSprite4.size() < 1) { //if there's nothing occupying the vector it's moving to.
				//something wrong here. the number is a poitner :/
				// printf("Move Object%d, from the stack.\n", InterestedStack[InternalStackIndex]->OrderCreation + 1);
				InterestedStack[InternalStackIndex]->MoveTargetTileX();
				InterestedStack[InternalStackIndex]->MoveTargetTileY();
				ReMapSprite(InterestedStack[InternalStackIndex]); //update position on the vector



				//THINK - should be unnecessary, since we should resolve everything that's already NULL in que2....
				Queue2[InterestedStack[InternalStackIndex]->OrderCreation] = NULL;
				//WE DO need some way to mark if it's been moved if it's in multiple stacks however. 
				//WE ALSO need some way to mark if theres a deadlock.maybe flag when we visit it, then set some avlue of the same container
				//but if we see the flag's already visited, for something like the size of the stack or more, then we can comfortably say it's 'deadlocked'

				//Recursion
				//INSERT - we want to actually check each of teh available stacks in teh stack, so that we resolve those with smaller priorities first, so long as it's not older thanthe que item we ended up moving... Because if it fails, then we can just fail the others quickly. rather than trying to 
				//resolve everystack every time. Although the 'oldest' youngest item on the lsit should be triggered before the others.... I'll have ot think about this deeper.
				//inserrt - we want to pop the bck of each stack when it is able to move, then don't itterate internal stack index, instead keep it the same, and check if its empty yet.
				InternalStackIndex -= 1;
				if (InternalStackIndex > -1) {
					if (HandleStack(InterestedStack[InternalStackIndex], InterestedStack, InternalStackIndex, SpriteStackIndex) == 1) {
						// printf("Stack Handled stacklayer = %d\n", InternalStackIndex);  //previous one finished fine

					}
				}
				//else
				//erase stack, undo counter
				//NEW
				else {
					SpriteStack.erase(SpriteStack.begin() + SpriteStackIndex);
					SpriteStackCounter -= 1;
				}



				return 1; //This current sprite succeeded, even if the one in the loop failed. 



			}

			//If it does:
			else { //if occupied tile
				// printf("Stacked Sprite trying to move into another object. Fails to move\n");
				InterestedStack[InternalStackIndex]->UndoBehavior();
				printf("U5\n");
				ReMapSprite(InterestedStack[InternalStackIndex]); //get around the null. May change later
				// printf("Yo\n");

				//NEW 
				Queue2[InterestedStack[InternalStackIndex]->OrderCreation] = NULL;
				//erase stack
				//undo counter SpriteStackCounter, 
				SpriteStack.erase(SpriteStack.begin() + SpriteStackIndex);
				SpriteStackCounter -= 1;


				return 1;

			}

		}
		else {
			// printf("Itterator went passed the allowed 'end' of 0 - whole stack resolved nicely.\n");
			return 1;
		}
	};
	int HandleFinalStack(std::vector<Sprite*>& InterestedStack, int EndOfStack) {
		//If can move, return 1, if not return 0. DO NOT RECURSIVELY CALL <-we want to complete teh stack in order
		//First, store the pointer, then pop the back 
		//no, pop back after move or fail.



		std::vector<Sprite*> CollidedSprite1; //Upper Left Corner
		std::vector<Sprite*> CollidedSprite2; //Upper Right corner
		std::vector<Sprite*> CollidedSprite3; //Lower Left Corner
		std::vector<Sprite*> CollidedSprite4; //Lower Right Corner - fourth may be unnecessary
		int FutureCode[8]; //CHECK that the size is 8! including 0;


		// printf("Object%d in stack (end) to be moved\n", InterestedStack[EndOfStack]->OrderCreation + 1);
		// 
		// 
		//move
		printf("Object%d to be handled [end]\n", InterestedStack[EndOfStack]->OrderCreation + 1);

		RemoveSpriteFromMap(InterestedStack[EndOfStack]);
		InterestedStack[EndOfStack]->Behavior();
		printf("B4\n");
		//Will it Collide?
		CheckFutureSpritePosition(InterestedStack[EndOfStack], FutureCode);
		if (FutureCode[0] != -1) {

			CollidedSprite1 = LM[FutureCode[0]][FutureCode[1]];

		}
		if (FutureCode[2] != -1) {

			CollidedSprite2 = LM[FutureCode[2]][FutureCode[3]];

		}
		if (FutureCode[4] != -1) {

			CollidedSprite3 = LM[FutureCode[4]][FutureCode[5]];

		}
		if (FutureCode[6] != -1) {

			CollidedSprite4 = LM[FutureCode[6]][FutureCode[7]];

		}




		//If does not:
		if (CollidedSprite1.size() < 1 && CollidedSprite2.size() < 1 && CollidedSprite3.size() < 1 && CollidedSprite4.size() < 1) { //if there's nothing occupying the vector it's moving to.
			//something wrong here. the number is a poitner :/
			// printf("Move Object%d, from the stack.\n", InterestedStack[EndOfStack]->OrderCreation + 1);
			InterestedStack[EndOfStack]->MoveTargetTileX();
			InterestedStack[EndOfStack]->MoveTargetTileY();
			ReMapSprite(InterestedStack[EndOfStack]); //update position on the vector



			//THINK - should be unnecessary, since we should resolve everything that's already NULL in que2....
			Queue2[InterestedStack[EndOfStack]->OrderCreation] = NULL;
			//WE DO need some way to mark if it's been moved if it's in multiple stacks however. 
			//WE ALSO need some way to mark if theres a deadlock.maybe flag when we visit it, then set some avlue of the same container
			//but if we see the flag's already visited, for something like the size of the stack or more, then we can comfortably say it's 'deadlocked'

			//Don't destroy whole stack, remove  element that was successful.
			InterestedStack.pop_back();

			return 1; //This current sprite succeeded



		}

		//If it does:
		else { //if occupied tile = Erase whole stack - if I can't move, then things above me also can't.
			// printf("Stacked Sprite trying to move into another object. Fails to move\n");
			InterestedStack[EndOfStack]->UndoBehavior();
			printf("U6\n");
			ReMapSprite(InterestedStack[EndOfStack]); //get around the null. May change later
			//erase the whole stack, either that or pop back then erase in the other loop. 
			return 0;

		}

	}
};