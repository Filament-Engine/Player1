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

	// for random
	int RandomX;
	int RandomY;

	int xVec;
	int yVec;

	// normal constructor -- uses moveX and moveY
	Sprite(int x, int y, std::string l, std::map<std::string, SurfaceProperty*> SurfacePropertyMap, int Order) {
		xPos = x;
		yPos = y;
		label = l;

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
	// constructors for AutoX and Y
	Sprite(int x, int y, std::string l, std::map<std::string, SurfaceProperty*> SurfacePropertyMap, int Order, int Vel, int LeftVLimit, int RightVLimit, std::string Axis) {
		xPos = x;
		yPos = y;
		label = l;

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
	~Sprite() {
		printf("Deconstructor for sprite called!\n");
	}

	bool MoveX(int x) { // it's possible we will want int x to be an argument in the object class instead of this function
		xPos += x;
		if (xPos < 0 || xPos + TILE_WIDTH - 1 >= LEVEL_WIDTH * TILE_WIDTH) {
			xPos -= x;
			return 0;
		}
		else {
			//TargetTile->x += x;
			return 1;
		}
	}
	bool MoveY(int y) { // it's possible we will want int y to be an argument in the object class instead of this function
		yPos += y;
		if (yPos < 0 || yPos + TILE_HEIGHT - 1 >= LEVEL_HEIGHT * TILE_HEIGHT) {
			yPos -= y;
			return 0;
		}
		else {
			//TargetTile->y += y;
			return 1;
		}
	}
	void FindPlayer() {
		printf("oh boy am i finding the player... we will get this set up once player is a subclass of sprite\n");
	}
	void RandomMove() {
		if (TIME == 0) {
			RandomX = rand() % 4; // 0/1 means don't move, 2 means move up, 3 means move down
			RandomY = rand() % 4; // 0/1 means don't move, 2 means move left, 3 means move right.
		}
		if (TIME >= 16) {
			RandomX = 0;
			RandomY = 0;
		}


		if (RandomX == 2) {

			MoveX(-1);
		}
		else if (RandomX == 3) {

			MoveX(1);
		}

		if (RandomY == 2) {

			MoveY(-1);
		}
		else if (RandomY == 3) {

			MoveY(1);
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
		printf("UndoBehavior\n"); 
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
		printf("Begin Remapping Object%d\n", ObjectSprite->OrderCreation+1);

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
			printf("a\n");
			LM[y1][x1].push_back(ObjectSprite);

		}
		else {
			printf("b\n");
			while (OrderedPosition < LM[y1][x1].size() && LM[y1][x1][OrderedPosition]->OrderCreation < ObjectSprite->OrderCreation) {
				OrderedPosition++;
			}

			LM[y1][x1].insert(LM[y1][x1].begin() + OrderedPosition, ObjectSprite);

			OrderedPosition = 0;
		}
		if (x1 != x2) {
			
			if (LM[y1][x2].size() == 0) {
				printf("c\n");
				LM[y1][x2].push_back(ObjectSprite);
			}
			else {
				printf("d\n");
				while (OrderedPosition<LM[y1][x2].size() && LM[y1][x2][OrderedPosition]->OrderCreation < ObjectSprite->OrderCreation) {
					OrderedPosition++;
				}
				LM[y1][x2].insert(LM[y1][x2].begin() + OrderedPosition, ObjectSprite);
				OrderedPosition = 0;
			}
		}
		if (y1 != y2) {
			if (LM[y2][x1].size() == 0) {
				printf("e\n");
				LM[y2][x1].push_back(ObjectSprite);
			}
			else {
				printf("f\n");
				while (OrderedPosition < LM[y2][x1].size() && LM[y2][x1][OrderedPosition]->OrderCreation < ObjectSprite->OrderCreation) {
					OrderedPosition++;
				}
				LM[y2][x1].insert(LM[y2][x1].begin() + OrderedPosition, ObjectSprite);
				OrderedPosition = 0;
			}

			if (x1 != x2) {
				printf("g\n");
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


		printf("Done reMapping\n");

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
						// SDL_Delay(1000);
					}
				}
				if (failx2) {
					// printf("UR [%d, %d], ", y1, x2);
					if (LM[y1][x2].size() > 0) {
						// printf("Occupied, ");
						// SDL_Delay(1000);
					}
				}
			}
			if (faily2) {
				if (failx1) {
					// printf("LL [%d, %d], ", y2, x1);
					if (LM[y2][x1].size() > 0) {
						// printf("Occupied, ");
						// SDL_Delay(1000);
					}
				}
				if (failx2) {
					// printf("LR [%d, %d], ", y2, x2);
					if (LM[y2][x2].size() > 0) {
						// printf("Occupied, ");
						// SDL_Delay(1000);
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
		//	SDL_Delay(500);
		}

	}



	std::vector<Sprite*>* CheckFutureSpritePosition2(Sprite* ObjectSprite) {
		bool BugTest;
		printf("Object Creation Order == %d\n", ObjectSprite->OrderCreation);
		if (ObjectSprite->OrderCreation == 0) {
			BugTest = true;
		}
		else {
			BugTest = false;
		}



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
			printf("3.0\n"); //initalized all variables
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
		printf("3.1\n"); //General Direction found
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

		printf("3.2\n"); //Measure found

		//figure out what your hitting, and how far overlapped.
		if (true) {
			//2) NOTE IF THERE IS A BUG, WHERE ITS COLLIDIG OT ITS RIGHT OR BELOW EXTRA, MAKE A CHECK THAT IF x2%16=0 IT IS NOW EQUAL TO x1, THUS IT DOESNT MATTER IF WE DO x2 OR x1 IN THE X CHECK, so long as they are the same, TAHT IS ALL. - a bug from previous, but the naming convention should be based on hte edge that is 'leading'

			//NOTE SPECIAL CASE is when x1,x2, or y1,y2 are % W or H =0, this means we check the position of x1,y1, otherwise error is thrown. <-also mod doesn't work
			// instead of % to check, use C = A - B*(A/B) <- used in TempMath
			//GOING TO

			if (Measure == 5) {//UL
				//edges are [x1][y1], [y2][x1], [x2][y1], each of these three are 'points' that form 2 edges.
				//Depending on how perfectly inligned with the grid you are, you can skip checking some edges/points.
				if (TempX2Math == 0 && TempY2Math == 0) { //you are perfectly in line with the gird
					if (BugTest) {
						printf("a\n");
					}
					for (int i = 0; i < LM[y1][x1].size(); i++) {
						//2) now check for overlap, diagonal so check for x and y. These formulas change every time. For simplcity, attempt to make sure that if there is a gap between the two object, 
						TempXOverlap = LM[y1][x1][i]->xPos + TILE_WIDTH - ObjectSprite->xPos;
						TempYOverlap = LM[y1][x1][i]->yPos + TILE_HEIGHT - ObjectSprite->yPos; 
						//2) if you didn't collide, even if your in the same grid space, then the equation returned negative, or 0 if just barely touching. (butnot collding)
						if (TempXOverlap > 0) {
							SpriteOverlapX.push_back(LM[y1][x1][i]);
							SpriteX.push_back(TempXOverlap);
						}
						if (TempYOverlap > 0) {
							SpriteOverlapY.push_back(LM[y1][x1][i]);
							SpriteY.push_back(TempYOverlap);
						}
					}
				}
				else {
					if (TempX2Math == 0) { //you are perfectly in line with an x axis'
						//2) Don't worry about pushing back more than one pointer to the same object. At the end of hte loop we will ensure that only one ptr remains, along with it sorted by overlap.
						if (BugTest) {
							printf("b\n");
						}
						for (int i = 0; i < LM[y1][x1].size(); i++) {//UL

							TempXOverlap = LM[y1][x1][i]->xPos + TILE_WIDTH - ObjectSprite->xPos;
							TempYOverlap = LM[y1][x1][i]->yPos + TILE_HEIGHT - ObjectSprite->yPos;

							if (TempXOverlap > 0) {
								SpriteOverlapX.push_back(LM[y1][x1][i]);
								SpriteX.push_back(TempXOverlap); //2) The overlap value will be the same, even if we end up pushing it twice.
							}
							if (TempYOverlap > 0) {
								SpriteOverlapY.push_back(LM[y1][x1][i]);
								SpriteY.push_back(TempYOverlap);
							}
						}
						if (BugTest) {
							printf("c\n");
						}
						for (int i = 0; i < LM[y2][x1].size(); i++) {//LL

							TempXOverlap = LM[y2][x1][i]->xPos + TILE_WIDTH - ObjectSprite->xPos;
							TempYOverlap = ObjectSprite->yPos + TILE_HEIGHT - LM[y2][x1][i]->yPos;

							if (TempXOverlap > 0) {
								SpriteOverlapX.push_back(LM[y2][x1][i]);
								SpriteX.push_back(TempXOverlap);
							}
							if (TempYOverlap > 0) {
								SpriteOverlapY.push_back(LM[y2][x1][i]);
								SpriteY.push_back(TempYOverlap);
							}
						}
					}
					else if (TempY2Math == 0) { //you are perfectly in line with an y axis'
						if (BugTest) {
							printf("d\n");
						}
						for (int i = 0; i < LM[y1][x1].size(); i++) { //UL
							TempXOverlap = LM[y1][x1][i]->xPos + TILE_WIDTH - ObjectSprite->xPos;
							TempYOverlap = LM[y1][x1][i]->yPos + TILE_HEIGHT - ObjectSprite->yPos;

							if (TempXOverlap > 0) {
								SpriteOverlapX.push_back(LM[y1][x1][i]);
								SpriteX.push_back(TempXOverlap);
							}
							if (TempYOverlap > 0) {
								SpriteOverlapY.push_back(LM[y1][x1][i]);
								SpriteY.push_back(TempYOverlap);
							}
						}
						if (BugTest) {
							printf("e\n");
						}
						for (int i = 0; i < LM[y1][x2].size(); i++) { //UR

							TempXOverlap = ObjectSprite->xPos + TILE_WIDTH - LM[y1][x2][i]->xPos;
							TempYOverlap = LM[y1][x2][i]->yPos + TILE_HEIGHT - ObjectSprite->yPos;
							if (BugTest) {
								printf("%d %d Overlap X and Y\n", TempXOverlap, TempYOverlap);
							}
							if (TempXOverlap > 0) {
								printf("Push overlapx\n");
								SpriteOverlapX.push_back(LM[y2][x2][i]);
								printf("Push spritex\n");
								SpriteX.push_back(TempXOverlap);
							}
							if (TempYOverlap > 0) {
								printf("Push overlapy\n");
								SpriteOverlapY.push_back(LM[y2][x2][i]);
								printf("Push spritey\n");
								SpriteY.push_back(TempYOverlap);
							}



						}
					}
					//2) these are always the points we're interested in.
					else { //you are not perfectly aligned with anything, every 'point' matters.
						if (BugTest) {
							printf("f\n");
						}
						for (int i = 0; i < LM[y1][x1].size(); i++) { //UL

							TempXOverlap = LM[y1][x1][i]->xPos + TILE_WIDTH - ObjectSprite->xPos;
							TempYOverlap = LM[y1][x1][i]->yPos + TILE_HEIGHT - ObjectSprite->yPos;

							if (TempXOverlap > 0) {
								SpriteOverlapX.push_back(LM[y1][x1][i]);
								SpriteX.push_back(TempXOverlap);
							}
							if (TempYOverlap > 0) {
								SpriteOverlapY.push_back(LM[y1][x1][i]);
								SpriteY.push_back(TempYOverlap);
							}
						}
						if (BugTest) {
							printf("g\n");
						}
						for (int i = 0; i < LM[y1][x2].size(); i++) { //UR

							TempXOverlap = ObjectSprite->xPos + TILE_WIDTH - LM[y1][x2][i]->xPos;
							TempYOverlap = LM[y1][x2][i]->yPos + TILE_HEIGHT - ObjectSprite->yPos;

							if (TempXOverlap > 0) {
								SpriteOverlapX.push_back(LM[y1][x2][i]);
								SpriteX.push_back(TempXOverlap);
							}
							if (TempYOverlap > 0) {
								SpriteOverlapY.push_back(LM[y1][x2][i]);
								SpriteY.push_back(TempYOverlap);
							}
						}
						if (BugTest) {
							printf("h\n");
						}
						for (int i = 0; i < LM[y2][x1].size(); i++) { //LL

							TempXOverlap = LM[y2][x1][i]->xPos + TILE_WIDTH - ObjectSprite->xPos;
							TempYOverlap = ObjectSprite->yPos + TILE_HEIGHT - LM[y2][x1][i]->yPos;

							if (TempXOverlap > 0) {
								SpriteOverlapX.push_back(LM[y2][x1][i]);
								SpriteX.push_back(TempXOverlap);
							}
							if (TempYOverlap > 0) {
								SpriteOverlapY.push_back(LM[y2][x1][i]);
								SpriteY.push_back(TempYOverlap);
							}
						}
					}
				}

			}
			else if (Measure == 13) {//UR
				//edges are [x1][y1], [x2][y1], [x2][y2]

				//Depending on how perfectly inligned with the grid you are, you can skip checking some edges/points.

				if (TempX2Math == 0 && TempY2Math == 0) { //you are perfectly in line with the gird
					if (BugTest) {
						printf("i\n");
					}
					for (int i = 0; i < LM[y1][x2].size(); i++) { // first
						TempXOverlap = ObjectSprite->xPos + TILE_WIDTH - LM[y1][x2][i]->xPos;
						TempYOverlap = LM[y1][x2][i]->yPos + TILE_HEIGHT - ObjectSprite->yPos;

						if (TempXOverlap > 0) {
							SpriteOverlapX.push_back(LM[y1][x2][i]);
							SpriteX.push_back(TempXOverlap);
						}
						if (TempYOverlap > 0) {
							SpriteOverlapY.push_back(LM[y1][x2][i]);
							SpriteY.push_back(TempYOverlap);
						}
					}
				}
				else {
					if (TempX2Math == 0) { //you are perfectly in line with an x axis'
						if (BugTest) {
							printf("j\n");
						}
						for (int i = 0; i < LM[y1][x2].size(); i++) { // UR

							TempXOverlap = ObjectSprite->xPos + TILE_WIDTH - LM[y1][x2][i]->xPos;
							TempYOverlap = LM[y1][x2][i]->yPos + TILE_HEIGHT - ObjectSprite->yPos;

							if (TempXOverlap > 0) {
								SpriteOverlapX.push_back(LM[y1][x2][i]);
								SpriteX.push_back(TempXOverlap);
							}
							if (TempYOverlap > 0) {
								SpriteOverlapY.push_back(LM[y1][x2][i]);
								SpriteY.push_back(TempYOverlap);
							}
						}
						if (BugTest) {
							printf("k\n");
						}
						for (int i = 0; i < LM[y2][x2].size(); i++) { // LR

							TempXOverlap = ObjectSprite->xPos + TILE_WIDTH - LM[y2][x2][i]->xPos;
							TempYOverlap = ObjectSprite->yPos + TILE_HEIGHT - LM[y2][x2][i]->yPos;

							if (TempXOverlap > 0) {
								SpriteOverlapX.push_back(LM[y2][x2][i]);
								SpriteX.push_back(TempXOverlap);
							}
							if (TempYOverlap > 0) {
								SpriteOverlapY.push_back(LM[y2][x2][i]);
								SpriteY.push_back(TempYOverlap);
							}
						}
					}
					else if (TempY2Math == 0) { //you are perfectly in line with an y axis'
						if (BugTest) {
							printf("l\n");
						}
						for (int i = 0; i < LM[y1][x1].size(); i++) { // UL

							TempXOverlap = LM[y1][x1][i]->xPos + TILE_WIDTH - ObjectSprite->xPos;
							TempYOverlap = LM[y1][x1][i]->yPos + TILE_HEIGHT - ObjectSprite->yPos;

							if (TempXOverlap > 0) {
								SpriteOverlapX.push_back(LM[y1][x1][i]);
								SpriteX.push_back(TempXOverlap);
							}
							if (TempYOverlap > 0) {
								SpriteOverlapY.push_back(LM[y1][x1][i]);
								SpriteY.push_back(TempYOverlap);
							}
						}
						if (BugTest) {
							printf("m\n");
						}
						for (int i = 0; i < LM[y1][x2].size(); i++) { // UR

							TempXOverlap = ObjectSprite->xPos + TILE_WIDTH - LM[y1][x2][i]->xPos;
							TempYOverlap = LM[y1][x2][i]->yPos + TILE_HEIGHT - ObjectSprite->yPos;

							if (TempXOverlap > 0) {
								SpriteOverlapX.push_back(LM[y1][x2][i]);
								SpriteX.push_back(TempXOverlap);
							}
							if (TempYOverlap > 0) {
								SpriteOverlapY.push_back(LM[y1][x2][i]);
								SpriteY.push_back(TempYOverlap);
							}
						}

					}
					else { //you are not perfectly aligned with anything, every 'point' matters.
						if (BugTest) {
							printf("n\n");
						}
						for (int i = 0; i < LM[y1][x1].size(); i++) { // UL

							TempXOverlap = LM[y1][x1][i]->xPos + TILE_WIDTH - ObjectSprite->xPos;
							TempYOverlap = LM[y1][x1][i]->yPos + TILE_HEIGHT - ObjectSprite->yPos;

							if (TempXOverlap > 0) {
								SpriteOverlapX.push_back(LM[y1][x1][i]);
								SpriteX.push_back(TempXOverlap);
							}
							if (TempYOverlap > 0) {
								SpriteOverlapY.push_back(LM[y1][x1][i]);
								SpriteY.push_back(TempYOverlap);
							}
						}
						if (BugTest) {
							printf("o\n");
						}
						for (int i = 0; i < LM[y2][x2].size(); i++) { // LR

							TempXOverlap = ObjectSprite->xPos + TILE_WIDTH - LM[y2][x2][i]->xPos;
							TempYOverlap = ObjectSprite->yPos + TILE_HEIGHT - LM[y2][x2][i]->yPos;

							if (TempXOverlap > 0) {
								SpriteOverlapX.push_back(LM[y2][x2][i]);
								SpriteX.push_back(TempXOverlap);
							}
							if (TempYOverlap > 0) {
								SpriteOverlapY.push_back(LM[y2][x2][i]);
								SpriteY.push_back(TempYOverlap);
							}
						}
						if (BugTest) {
							printf("p\n");
						}
						for (int i = 0; i < LM[y1][x2].size(); i++) { // UR

							TempXOverlap = ObjectSprite->xPos + TILE_WIDTH - LM[y1][x2][i]->xPos;
							TempYOverlap = LM[y1][x2][i]->yPos + TILE_HEIGHT - ObjectSprite->yPos;

							if (TempXOverlap > 0) {
								SpriteOverlapX.push_back(LM[y1][x2][i]);
								SpriteX.push_back(TempXOverlap);
							}
							if (TempYOverlap > 0) {
								SpriteOverlapY.push_back(LM[y1][x2][i]);
								SpriteY.push_back(TempYOverlap);
							}
						}

					}
				}

			}
			else if (Measure == 7) {//DL
				//edges are [x1][y1], [x1][y2], [x2][y2]

				//Depending on how perfectly inligned with the grid you are, you can skip checking some edges/points.

				if (TempX2Math == 0 && TempY2Math == 0) { //you are perfectly in line with the gird
					if (BugTest) {
						printf("q\n");
					}
					for (int i = 0; i < LM[y2][x1].size(); i++) { // first

						TempXOverlap = LM[y2][x1][i]->xPos + TILE_WIDTH - ObjectSprite->xPos;
						TempYOverlap = ObjectSprite->yPos + TILE_HEIGHT - LM[y2][x1][i]->yPos;

						if (TempXOverlap > 0) {
							SpriteOverlapX.push_back(LM[y2][x1][i]);
							SpriteX.push_back(TempXOverlap);
						}
						if (TempYOverlap > 0) {
							SpriteOverlapY.push_back(LM[y2][x1][i]);
							SpriteY.push_back(TempYOverlap);
						}
					}
				}
				else {
					if (TempX2Math == 0) { //you are perfectly in line with an x axis'
						if (BugTest) {
							printf("r\n");
						}
						for (int i = 0; i < LM[y1][x1].size(); i++) { // UL

							TempXOverlap = LM[y1][x1][i]->xPos + TILE_WIDTH - ObjectSprite->xPos;
							TempYOverlap = LM[y1][x1][i]->yPos + TILE_HEIGHT - ObjectSprite->yPos;
							if (TempXOverlap > 0) {
								SpriteOverlapX.push_back(LM[y1][x1][i]);
								SpriteX.push_back(TempXOverlap);
							}
							if (TempYOverlap > 0) {
								SpriteOverlapY.push_back(LM[y1][x1][i]);
								SpriteY.push_back(TempYOverlap);
							}
						}
						if (BugTest) {
							printf("s\n");
						}
						for (int i = 0; i < LM[y2][x1].size(); i++) { // LL

							TempXOverlap = LM[y2][x1][i]->xPos + TILE_WIDTH - ObjectSprite->xPos;
							TempYOverlap = ObjectSprite->yPos + TILE_HEIGHT - LM[y2][x1][i]->yPos;
							if (TempXOverlap > 0) {
								SpriteOverlapX.push_back(LM[y2][x1][i]);
								SpriteX.push_back(TempXOverlap);
							}
							if (TempYOverlap > 0) {
								SpriteOverlapY.push_back(LM[y2][x1][i]);
								SpriteY.push_back(TempYOverlap);
							}
						}
					}
					else if (TempY2Math == 0) { //you are perfectly in line with an y axis'
						for (int i = 0; i < LM[y2][x1].size(); i++) { // LL

							TempXOverlap = LM[y2][x1][i]->xPos + TILE_WIDTH - ObjectSprite->xPos;
							TempYOverlap = ObjectSprite->yPos + TILE_HEIGHT - LM[y2][x1][i]->yPos;
							if (TempXOverlap > 0) {
								SpriteOverlapX.push_back(LM[y2][x1][i]);
								SpriteX.push_back(TempXOverlap);
							}
							if (TempYOverlap > 0) {
								SpriteOverlapY.push_back(LM[y2][x1][i]);
								SpriteY.push_back(TempYOverlap);
							}
						}
						if (BugTest) {
							printf("t\n");
						}
						for (int i = 0; i < LM[y2][x2].size(); i++) { // LR

							TempXOverlap = ObjectSprite->xPos + TILE_WIDTH - LM[y2][x2][i]->xPos;
							TempYOverlap = ObjectSprite->yPos + TILE_HEIGHT - LM[y2][x2][i]->yPos;
							if (TempXOverlap > 0) {
								SpriteOverlapX.push_back(LM[y2][x2][i]);
								SpriteX.push_back(TempXOverlap);
							}
							if (TempYOverlap > 0) {
								SpriteOverlapY.push_back(LM[y2][x2][i]);
								SpriteY.push_back(TempYOverlap);
							}
						}

					}
					else { //you are not perfectly aligned with anything, every 'point' matters.
						if (BugTest) {
							printf("u\n");
						}
						for (int i = 0; i < LM[y1][x1].size(); i++) { // UL

							TempXOverlap = LM[y1][x1][i]->xPos + TILE_WIDTH - ObjectSprite->xPos;
							TempYOverlap = LM[y1][x1][i]->yPos + TILE_HEIGHT - ObjectSprite->yPos;

							if (TempXOverlap > 0) {
								SpriteOverlapX.push_back(LM[y1][x1][i]);
								SpriteX.push_back(TempXOverlap);
							}
							if (TempYOverlap > 0) {
								SpriteOverlapY.push_back(LM[y1][x1][i]);
								SpriteY.push_back(TempYOverlap);
							}
						}
						if (BugTest) {
							printf("v\n");
						}
						for (int i = 0; i < LM[y2][x2].size(); i++) { // LR

							TempXOverlap = ObjectSprite->xPos + TILE_WIDTH - LM[y2][x2][i]->xPos;
							TempYOverlap = ObjectSprite->yPos + TILE_HEIGHT - LM[y2][x2][i]->yPos;

							if (TempXOverlap > 0) {
								SpriteOverlapX.push_back(LM[y2][x2][i]);
								SpriteX.push_back(TempXOverlap);
							}
							if (TempYOverlap > 0) {
								SpriteOverlapY.push_back(LM[y2][x2][i]);
								SpriteY.push_back(TempYOverlap);
							}
						}
						if (BugTest) {
							printf("w\n");
						}
						for (int i = 0; i < LM[y2][x1].size(); i++) { // LL

							TempXOverlap = LM[y2][x1][i]->xPos + TILE_WIDTH - ObjectSprite->xPos;
							TempYOverlap = ObjectSprite->yPos + TILE_HEIGHT - LM[y2][x1][i]->yPos;

							if (TempXOverlap > 0) {
								SpriteOverlapX.push_back(LM[y2][x1][i]);
								SpriteX.push_back(TempXOverlap);
							}
							if (TempYOverlap > 0) {
								SpriteOverlapY.push_back(LM[y2][x1][i]);
								SpriteY.push_back(TempYOverlap);
							}
						}

					}
				}

			}
			else if (Measure == 15) {//DR
				//edges are [x1][y2], [x2][y2], [x2][y1]

				//Depending on how perfectly inligned with the grid you are, you can skip checking some edges/points.

				if (TempX2Math == 0 && TempY2Math == 0) { //you are perfectly in line with the gird

					if (BugTest) {
						printf("x\n");
					}
					for (int i = 0; i < LM[y2][x2].size(); i++) { // LL
						TempXOverlap = ObjectSprite->xPos + TILE_WIDTH - LM[y2][x2][i]->xPos;
						TempYOverlap = ObjectSprite->yPos + TILE_HEIGHT - LM[y2][x2][i]->yPos;
						if (TempXOverlap > 0) {
							SpriteOverlapX.push_back(LM[y2][x2][i]);
							SpriteX.push_back(TempXOverlap);
						}
						if (TempYOverlap > 0) {
							SpriteOverlapY.push_back(LM[y2][x2][i]);
							SpriteY.push_back(TempYOverlap);
						}
					}
				}
				else {
					if (TempX2Math == 0) { //you are perfectly in line with an x axis'
						if (BugTest) {
							printf("y\n");
						}
						for (int i = 0; i < LM[y1][x2].size(); i++) { // UR

							TempXOverlap = ObjectSprite->xPos + TILE_WIDTH - LM[y1][x2][i]->xPos;
							TempYOverlap = LM[y1][x2][i]->yPos + TILE_HEIGHT - ObjectSprite->yPos;
							if (TempXOverlap > 0) {
								SpriteOverlapX.push_back(LM[y1][x2][i]);
								SpriteX.push_back(TempXOverlap);
							}
							if (TempYOverlap > 0) {
								SpriteOverlapY.push_back(LM[y1][x2][i]);
								SpriteY.push_back(TempYOverlap);
							}
						}
						if (BugTest) {
							printf("z\n");
						}
						for (int i = 0; i < LM[y1][x2].size(); i++) { // LL

							TempXOverlap = ObjectSprite->xPos + TILE_WIDTH - LM[y1][x2][i]->xPos;
							TempYOverlap = ObjectSprite->yPos + TILE_HEIGHT - LM[y1][x2][i]->yPos;

							if (TempXOverlap > 0) {
								SpriteOverlapX.push_back(LM[y1][x2][i]);
								SpriteX.push_back(TempXOverlap);
							}
							if (TempYOverlap > 0) {
								SpriteOverlapY.push_back(LM[y1][x2][i]);
								SpriteY.push_back(TempYOverlap);
							}
						}
					}
					else if (TempY2Math == 0) { //you are perfectly in line with an y axis'
						if (BugTest) {
							printf("aa\n");
						}
						for (int i = 0; i < LM[y2][x1].size(); i++) { // LR

							TempXOverlap = LM[y2][x1][i]->xPos + TILE_WIDTH - ObjectSprite->xPos;
							TempYOverlap = ObjectSprite->yPos + TILE_HEIGHT - LM[y2][x1][i]->yPos;

							if (TempXOverlap > 0) {
								SpriteOverlapX.push_back(LM[y2][x1][i]);
								SpriteX.push_back(TempXOverlap);
							}
							if (TempYOverlap > 0) {
								SpriteOverlapY.push_back(LM[y2][x1][i]);
								SpriteY.push_back(TempYOverlap);
							}
						}
						if (BugTest) {
							printf("ab\n");
						}
						for (int i = 0; i < LM[y2][x2].size(); i++) { // LR

							TempXOverlap = ObjectSprite->xPos + TILE_WIDTH - LM[y2][x2][i]->xPos;
							TempYOverlap = ObjectSprite->yPos + TILE_HEIGHT - LM[y2][x2][i]->yPos;

							if (TempXOverlap > 0) {
								SpriteOverlapX.push_back(LM[y2][x2][i]);
								SpriteX.push_back(TempXOverlap);
							}
							if (TempYOverlap > 0) {
								SpriteOverlapY.push_back(LM[y2][x2][i]);
								SpriteY.push_back(TempYOverlap);
							}
						}

					}
					else { //you are not perfectly aligned with anything, every 'point' matters.
						if (BugTest) {
							printf("ac\n");
						}
						for (int i = 0; i < LM[y2][x1].size(); i++) { // LL

							TempXOverlap = LM[y2][x1][i]->xPos + TILE_WIDTH - ObjectSprite->xPos;
							TempYOverlap = ObjectSprite->yPos + TILE_HEIGHT - LM[y2][x1][i]->yPos;

							if (TempXOverlap > 0) {
								SpriteOverlapX.push_back(LM[y2][x1][i]);
								SpriteX.push_back(TempXOverlap);
							}
							if (TempYOverlap > 0) {
								SpriteOverlapY.push_back(LM[y2][x1][i]);
								SpriteY.push_back(TempYOverlap);
							}
						}
						if (BugTest) {
							printf("ad\n");
						}
						for (int i = 0; i < LM[y2][x2].size(); i++) { // LR

							TempXOverlap = ObjectSprite->xPos + TILE_WIDTH - LM[y2][x2][i]->xPos;
							TempYOverlap = ObjectSprite->yPos + TILE_HEIGHT - LM[y2][x2][i]->yPos;

							if (TempXOverlap > 0) {
								SpriteOverlapX.push_back(LM[y2][x2][i]);
								SpriteX.push_back(TempXOverlap);
							}
							if (TempYOverlap > 0) {
								SpriteOverlapY.push_back(LM[y2][x2][i]);
								SpriteY.push_back(TempYOverlap);
							}
						}
						if (BugTest) {
							printf("ae\n");
						}
						for (int i = 0; i < LM[y1][x2].size(); i++) { // UR

							TempXOverlap = ObjectSprite->xPos + TILE_WIDTH - LM[y1][x2][i]->xPos;
							TempYOverlap = LM[y1][x2][i]->yPos + TILE_HEIGHT - ObjectSprite->yPos;

							if (TempXOverlap > 0) {
								SpriteOverlapX.push_back(LM[y1][x2][i]);
								SpriteX.push_back(TempXOverlap);
							}
							if (TempYOverlap > 0) {
								SpriteOverlapY.push_back(LM[y1][x2][i]);
								SpriteY.push_back(TempYOverlap);
							}
						}

					}
				}

			}
			else if (Measure == 6) {//L
			//edges are [x1][y1] and [x1][y2]
				if (TempY2Math == 0) {
					if (BugTest) {
						printf("af\n");
					}
					for (int i = 0; i < LM[y1][x1].size(); i++) {
						if (LM[y1][x1][i]->xPos > ObjectSprite->xPos) {
							TempXOverlap = LM[y1][x1][i]->xPos + TILE_WIDTH - ObjectSprite->xPos;
						}
						else {
							TempXOverlap = ObjectSprite->xPos + TILE_WIDTH - LM[y1][x1][i]->xPos;
						}
						if (TempXOverlap < 17) {
							SpriteOverlapX.push_back(LM[y1][x1][i]);
							SpriteX.push_back(TempXOverlap);
						}
					}
				}
				else {
					if (BugTest) {
						printf("ag\n");
					}
					for (int i = 0; i < LM[y1][x1].size(); i++) {
						if (LM[y1][x1][i]->xPos > ObjectSprite->xPos) {
							TempXOverlap = LM[y1][x1][i]->xPos + TILE_WIDTH - ObjectSprite->xPos;
						}
						else {
							TempXOverlap = ObjectSprite->xPos + TILE_WIDTH - LM[y1][x1][i]->xPos;
						}
						if (TempXOverlap < 17) {
							SpriteOverlapX.push_back(LM[y1][x1][i]);
							SpriteX.push_back(TempXOverlap);
						}
					}
					if (BugTest) {
						printf("ah\n");
					}
					for (int i = 0; i < LM[y2][x1].size(); i++) {
						if (LM[y1][x1][i]->xPos > ObjectSprite->xPos) {
							TempXOverlap = LM[y2][x1][i]->xPos + TILE_WIDTH - ObjectSprite->xPos;
						}
						else {
							TempXOverlap = ObjectSprite->xPos + TILE_WIDTH - LM[y2][x1][i]->xPos;
						}		
						if (TempXOverlap < 17) {
							SpriteOverlapX.push_back(LM[y2][x1][i]);
							SpriteX.push_back(TempXOverlap);
						}
					}
				}
			}
			else if (Measure == 14) {//R
				//edges are [x2][y1] and [x2][y2]
				if (TempY2Math == 0) {
					if (BugTest) {
						printf("ai\n");
					}
					for (int i = 0; i < LM[y1][x2].size(); i++) {
						if (LM[y1][x2][i]->xPos > ObjectSprite->xPos) {

							TempXOverlap = LM[y1][x2][i]->xPos + TILE_WIDTH - ObjectSprite->xPos;
						}
						else { 
							TempXOverlap=ObjectSprite->xPos+TILE_WIDTH - LM[y1][x2][i]->xPos;
						}
						if (TempXOverlap < 17) {
							SpriteOverlapX.push_back(LM[y1][x2][i]);
							SpriteX.push_back(TempXOverlap);
						}
					}
				}
				else {
					if (BugTest) {
						printf("aj\n");
					}
					for (int i = 0; i < LM[y1][x2].size(); i++) {
						if (LM[y1][x2][i]->xPos > ObjectSprite->xPos) {

							TempXOverlap = LM[y1][x2][i]->xPos + TILE_WIDTH - ObjectSprite->xPos;
						}
						else {
							TempXOverlap = ObjectSprite->xPos + TILE_WIDTH - LM[y1][x2][i]->xPos;
						}
						if (TempXOverlap < 17) {
							SpriteOverlapX.push_back(LM[y1][x2][i]);
							SpriteX.push_back(TempXOverlap);
						}
					}
					if (BugTest) {
						printf("ak\n");
					}
					for (int i = 0; i < LM[y2][x2].size(); i++) {
						if (LM[y1][x2][i]->xPos > ObjectSprite->xPos) {

							TempXOverlap = LM[y2][x2][i]->xPos + TILE_WIDTH - ObjectSprite->xPos;
						}
						else {
							TempXOverlap = ObjectSprite->xPos + TILE_WIDTH - LM[y2][x2][i]->xPos;
						}
						if (TempXOverlap < 17) {
							SpriteOverlapX.push_back(LM[y2][x2][i]);
							SpriteX.push_back(TempXOverlap);
						}
					}
				}
			}
			else if (Measure == 11) {//D
				//edges are [x1][y2] and [x2][y2]


				if (TempX2Math == 0) {
					if (BugTest) {
						printf("al\n");
					}
					for (int i = 0; i < LM[y2][x1].size(); i++) {

						TempYOverlap = ObjectSprite->yPos + TILE_HEIGHT - LM[y2][x1][i]->yPos;
						if (TempYOverlap > 0) {
							SpriteOverlapY.push_back(LM[y2][x1][i]);
							SpriteY.push_back(TempYOverlap);
						}
					}
				}
				else {
					if (BugTest) {
						printf("am\n");
					}
					for (int i = 0; i < LM[y2][x1].size(); i++) {

						TempYOverlap = ObjectSprite->yPos + TILE_HEIGHT - LM[y2][x1][i]->yPos;
						if (TempYOverlap > 0) {
							SpriteOverlapY.push_back(LM[y2][x1][i]);
							SpriteY.push_back(TempYOverlap);
						}
					}
					if (BugTest) {
						printf("an\n");
					}
					for (int i = 0; i < LM[y2][x2].size(); i++) {

						TempYOverlap = ObjectSprite->yPos + TILE_HEIGHT - LM[y2][x2][i]->yPos;
						if (TempYOverlap > 0) {
							SpriteOverlapY.push_back(LM[y2][x2][i]);
							SpriteY.push_back(TempYOverlap);
						}
					}
				}

			}
			else if (Measure == 9) {//U
				//edges are [x1][y1] and [x2][x1]


				if (TempX2Math == 0) {
					if (BugTest) {
						printf("ao\n");
					}
					for (int i = 0; i < LM[y1][x1].size(); i++) {

						TempYOverlap = LM[y1][x1][i]->yPos + TILE_HEIGHT - ObjectSprite->yPos;
						if (TempYOverlap > 0) {
							SpriteOverlapY.push_back(LM[y1][x1][i]);
							SpriteY.push_back(TempYOverlap);
						}
					}
				}
				else {
					if (BugTest) {
						printf("ap\n");
					}
					for (int i = 0; i < LM[y1][x1].size(); i++) {

						TempYOverlap = LM[y1][x1][i]->yPos + TILE_HEIGHT - ObjectSprite->yPos;
						if (TempYOverlap > 0) {
							SpriteOverlapY.push_back(LM[y1][x1][i]);
							SpriteY.push_back(TempYOverlap);
						}
					}
					if (BugTest) {
						printf("aq\n");
					}
					for (int i = 0; i < LM[y1][x2].size(); i++) {

						TempYOverlap = LM[y1][x2][i]->yPos + TILE_HEIGHT - ObjectSprite->yPos;
						if (TempYOverlap > 0) {
							SpriteOverlapY.push_back(LM[y1][x2][i]);
							SpriteY.push_back(TempYOverlap);
						}


					}
				}

			}
			else if (Measure == 10) {//0
				if (BugTest) {
					printf("ar\n");
				}
			}
			//All overlap, no collision


			//NOTHING :D
		}
		printf("3.3\n"); //Matrixes checked has been decided


		//We've got what we could be colliding with
		//Merge sort for most at the last of hte vector

		//If collide, don't flag for overlaps
		//If it does collide, then flag for overlap (all four corners)


	//Sort by overlap most, figure out the order of collision. 
		if (true) {
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
		}


		if (Measure != 10) {
			printf("Direction for the moving sprite is = %d\n", Measure);
		}
		if (SpriteOverlapX.size() > 0) {
			printf("Every item in the SpriteOverlapX =");
			for (int i = 0; i < SpriteOverlapX.size(); i++) {
				printf("Sprite %s, ", SpriteOverlapX[i]->label.c_str());
				printf("Overlap = %d, ", SpriteX[i]); //should always be +, should always be equal in number to the sprite overlap
				if (SpriteX[i] > 15) {
					SDL_Delay(5000);
				}
			}
			printf("\n");
		}
		if (SpriteOverlapY.size() > 0) {
			printf("Every item in the SpriteOverlapY =");
			for (int i = 0; i < SpriteOverlapY.size(); i++) {
				printf("Sprite %s, ", SpriteOverlapY[i]->label.c_str());
				printf("Overlap = %d, ", SpriteY[i]);
				if (SpriteY[i] > 15) {
					SDL_Delay(5000);
				}
			}
			printf("\n");
		}



		if (BugTest && (SpriteOverlapY.size()> 0 || SpriteOverlapX.size()>0) ) {
			printf("Take Time to ensure the above looks correct for Object%d.\n", ObjectSprite->OrderCreation + 1);
		//	SDL_Delay(5000);
		}

		//return the vector
		std::vector<Sprite*> XYArr[2] = { SpriteOverlapX, SpriteOverlapY };
		printf("3.4\n"); //arrray to return is created
		return XYArr;

	}




	void MergeSpriteCollision(std::vector<Sprite*>& SpriteOverlap, std::vector<int>& SpriteArea, int L, int M, int R) {

		int LeftItter = L;
		int RightItter = M + 1;
		if (LeftItter > M || RightItter > R) {
			printf("Left or Right finished\n");
		}

		/*
		auto const subArrayOne = M - L + 1;
		auto const subArrayTwo = R - M;

		if (SpriteArea[

		*/

		/*
			auto const subArrayOne = M - L + 1;
			auto const subArrayTwo = R - M;

			// Create temp arrays
			auto *leftOverlapArray = new int[subArrayOne], *rightOverlapArray = new int[subArrayTwo];
			auto *leftAreaArray = new int[subArrayOne], *rightAreaArray = new int[subArrayTwo];


			// Copy data to temp arrays leftArray[] and rightArray[]
			for (auto i = 0; i < subArrayOne; i++)
				leftOverlapArray[i] = SpriteOverlap[L + i];
				leftAreaArray[i] = SpriteArea[L + i];
			for (auto j = 0; j < subArrayTwo; j++)
				rightOverlapArray[j] = SpriteOverlap[M + 1 + j];
				rightAreaArray[j] = SpriteArea[M + 1 + j];

			auto indexOfSubArrayOne = 0, // Initial index of first sub vec
				indexOfSubArrayTwo = 0; // Initial index of second sub vec
			int indexOfMergedArray = left; // Initial index of merged array

			// Merge the temp arrays back into array[left..right]
			while (indexOfSubArrayOne < subArrayOne && indexOfSubArrayTwo < subArrayTwo) {
				if (leftArray[indexOfSubArrayOne] <= rightArray[indexOfSubArrayTwo]) {
					array[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
					indexOfSubArrayOne++;
				}
				else {
					array[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
					indexOfSubArrayTwo++;
				}
				indexOfMergedArray++;
			}
			// Copy the remaining elements of
			// left[], if there are any
			while (indexOfSubArrayOne < subArrayOne) {
				array[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
				indexOfSubArrayOne++;
				indexOfMergedArray++;
			}
			// Copy the remaining elements of
			// right[], if there are any
			while (indexOfSubArrayTwo < subArrayTwo) {
				array[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
				indexOfSubArrayTwo++;
				indexOfMergedArray++;
			}
		}
		*/
	}

	void MergeSortSpriteCollision(std::vector<Sprite*>& SpriteOverlap, std::vector<int>& SpriteArea, int L, int R) { //we will be editing directly onto it
		if (L >= R) {
			return; //returns recursively
		}

		int M = L + (R - L) / 2;
		MergeSortSpriteCollision(SpriteOverlap, SpriteArea, L, M);
		MergeSortSpriteCollision(SpriteOverlap, SpriteArea, M + 1, R);
		MergeSpriteCollision(SpriteOverlap, SpriteArea, L, M, R);



	};


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


	void MoveAllSprites2() {


		ReCreateQue2();

		for (int i = 0; i < AllSprites.size(); i++) { //{1, 4, 8, 10}
			if (Queue2[i] != NULL) {
				printf("1\n");
				RemoveSpriteFromMap(Queue2[i]);
				printf("2\n");
				Queue2[i]->Behavior();
				printf("3\n");
				CheckFutureSpritePosition2(Queue2[i]);
				//success
				printf("4\n");
				Queue2[i]->MoveTargetTileX();
				printf("5\n");
				Queue2[i]->MoveTargetTileY();
				printf("6\n");
				ReMapSprite(Queue2[i]);

				//fail
				// undobehavior
				//remap
				// store the collision (could be collsion) prune the the no collision tiles.
				//When stack, x = {1, 5, 10, 8} -> 8
				//x = {1, 5, 8, 10} ->10, 8, 5, 1 (because they are less than 10).

				printf("7\n");
			}
		}
		printf("8\n");
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
			//SDL_Delay(10000);

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
		//SDL_Delay(10000);

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


};