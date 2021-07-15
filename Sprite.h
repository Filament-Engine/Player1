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
	int directionV; //NEW, holds onto the starting dierction, and how quickly it will move when it's 'pacing'. It must be stored or returned from the function, otherwise it will cling to the edge of hte pace distance.
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

		directionV = 0; // NEW, this is like the velocity and starti ndirection of the sprite;
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

		directionV = 0; // NEW, this is like the velocity and starti ndirection of the sprite;
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

			directionV = Vel; // NEW, this is like the velocity and starting direction of the sprite;
			leftVlimit = LeftVLimit;
			rightVlimit = RightVLimit;
			OrderCreation = Order; // NEW
			DoAutoX = true;
		}
		else if (Axis == "AxisY") {

			directionV = Vel;
			leftVlimit = LeftVLimit;
			rightVlimit = RightVLimit;
			OrderCreation = Order;//NEW
			DoAutoY = true;
		}




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
		if (directionV > 0) { //going right

			if (yPos + directionV < rightVlimit) {

				yPos += directionV;
			}
			else {
				//turn around

				directionV = -directionV;

				yPos += directionV;
			}
		}
		else if (directionV < 0) { //going left

			if (yPos + directionV > leftVlimit) {

				yPos += directionV;
			}
			else {
				//turn around

				directionV = -directionV;

				yPos += directionV;
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
		
			


			if (directionV > 0) { //going right

				if (xPos + directionV < rightVlimit) {

					xPos += directionV;
				}
				else {
					//turn around

					directionV = -directionV;

					xPos += directionV;
				}
			}
			else if (directionV < 0) { //going left

				if (xPos + directionV > leftVlimit) {

					xPos += directionV;
				}
				else {
					//turn around

					directionV = -directionV;

					xPos += directionV;
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
		xPos -= directionV; //no matter what direction it's heading, this will undo it. - this also assumes your moving when your turning around. 

	}
	void UndoAutoY() {
		yPos -= directionV; //no matter what direction it's heading, this will undo it. - this also assumes your moving when your turning around. 

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



		if (y1 % TILE_HEIGHT == 0) {

			//just map y1 - perfectly placed in tilemap
			if (x1 % TILE_WIDTH == 0) {



				LM[y1 / TILE_HEIGHT][x1 / TILE_WIDTH].push_back(ObjectSprite);
			}
			else {

				//map x1 and x2
				y1 = y1 / TILE_HEIGHT; //saves small amount of computation


				LM[y1][x1 / TILE_WIDTH].push_back(ObjectSprite);
				LM[y1][x2 / TILE_WIDTH].push_back(ObjectSprite);
			}
		}
		else {
			//map y1 and y2

			if (x1 % TILE_WIDTH == 0) {
				//just map x1 - perfectly placed in tilemap

				x1 = x1 / TILE_WIDTH; //saves an small amount of comuptation


				LM[y1 / TILE_HEIGHT][x1].push_back(ObjectSprite);
				LM[y2 / TILE_HEIGHT][x1].push_back(ObjectSprite);
			}
			else {
				//map x1 and x2

				x1 = x1 / TILE_WIDTH; //saves an small amount of comuptation
				x2 = x2 / TILE_WIDTH;
				y1 = y1 / TILE_HEIGHT;
				y2 = y2 / TILE_HEIGHT;

				LM[y1][x1].push_back(ObjectSprite);
				LM[y1][x2].push_back(ObjectSprite);
				LM[y2][x1].push_back(ObjectSprite);
				LM[y2][x2].push_back(ObjectSprite);
			}
		}



	}
	void DisplayTileBasedArray() {

		for (int i = 0; i < LEVEL_HEIGHT; i++) {
			printf("\n R:%d", i);


			for (int j = 0; j < LEVEL_WIDTH; j++) {
				printf(" C%d = [", j);

				for (int d = 0; d < std::distance(LM[i][j].begin(), LM[i][j].end()); d++) {
					printf("%d, ", LM[i][j][d]->OrderCreation);


				}
				printf("]");

			}
		}
		printf("\n");

	}
	void ReMapSprite(Sprite* ObjectSprite) {
		printf("ReMapSprite\n");
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

		printf("Remap Object%d\n", ObjectSprite->OrderCreation + 1);
		//NOTE - replace pushbacks with inserts - unless empty vector
 

			x1 = x1 / TILE_WIDTH; //saves an small amount of comuptation
			x2 = x2 / TILE_WIDTH;
			y1 = y1 / TILE_HEIGHT;
			y2 = y2 / TILE_HEIGHT;

			//gaurds from map/matrix overflow
			if (y2 > LEVEL_HEIGHT - 1) {
				y2 = LEVEL_HEIGHT - 1;
				y1 = LEVEL_HEIGHT - 2;
			}
			if (y1 < 0) {
				y1 = 0;
				y2 = TILE_HEIGHT;
			}
			if (x2 > LEVEL_WIDTH - 1) {
				x2 = LEVEL_WIDTH - 1;
				x1 = LEVEL_WIDTH - 2;
			}
			if (x1 < 0) {
				x1 = 0;
				x2 = TILE_WIDTH - 1;
			}



			if (LM[y1][x1].size() == 0) {

				LM[y1][x1].push_back(ObjectSprite);

			}
			else {
				while (LM[y1][x1][OrderedPosition]->OrderCreation < ObjectSprite->OrderCreation) {
					OrderedPosition++;
				}

				LM[y1][x1].insert(LM[y1][x1].begin() + OrderedPosition, ObjectSprite);

				OrderedPosition = 0;
			}
			if (x1 != x2) {
				if (LM[y1][x2].size() == 0) {
					LM[y1][x2].push_back(ObjectSprite);
				}
				else {
					while (LM[y1][x2][OrderedPosition]->OrderCreation < ObjectSprite->OrderCreation) {
						OrderedPosition++;
					}
					LM[y1][x2].insert(LM[y1][x2].begin() + OrderedPosition, ObjectSprite);
					OrderedPosition = 0;
				}
			}
			if (y1 != y2) {
				if (LM[y2][x1].size() == 0) {
					LM[y2][x1].push_back(ObjectSprite);
				}
				else {
					while (LM[y2][x1][OrderedPosition]->OrderCreation < ObjectSprite->OrderCreation) {
						OrderedPosition++;
					}
					LM[y2][x1].insert(LM[y2][x1].begin() + OrderedPosition, ObjectSprite);
					OrderedPosition = 0;
				}

				if (x1 != x2) {
					if (LM[y2][x2].size() == 0) {
						LM[y2][x2].push_back(ObjectSprite);
					}
					else {
						while (LM[y2][x2][OrderedPosition]->OrderCreation < ObjectSprite->OrderCreation) {
							OrderedPosition++;
						}
						LM[y2][x2].insert(LM[y2][x2].begin() + OrderedPosition, ObjectSprite);
					}
				}
			}
		

		printf("Done reMapping\n");

	}

	void CheckFutureSpritePosition(Sprite* ObjectSprite, int FutureCode[8]) {
		printf("CheckFutureSpritePosition\n");
		int x1, x2, y1, y2;
		bool failx1 = false, failx2 = false, faily1 = false, faily2 = false;
		
		x1 = ObjectSprite->xPos;
		x2 = ObjectSprite->xPos + TILE_WIDTH;
		y1 = ObjectSprite->yPos;
		y2 = ObjectSprite->yPos + TILE_HEIGHT;




		y1 = y1 / TILE_HEIGHT;
		y2 = y2 / TILE_HEIGHT;
		x1 = x1 / TILE_WIDTH;
		x2 = x2 / TILE_WIDTH; 


		//gaurds from map/matrix overflow
			if (y2 > LEVEL_HEIGHT-1) {
				y2 = LEVEL_HEIGHT-1;
				y1 = LEVEL_HEIGHT -2;
			}
			if (y1 < 0) {
				y1 = 0;
				y2 = TILE_HEIGHT;
			}
			if (x2 > LEVEL_WIDTH-1) {
				x2 = LEVEL_WIDTH - 1;
				x1 = LEVEL_WIDTH -2;
			}
			if (x1 < 0) {
				x1 = 0;
				x2 = TILE_WIDTH-1;
			}
			printf("Found approrpiate positions\n");





		//NOTE only one fail should happen, if multiple happen let it just undo the movement once, NO NEED FOR MORE THAN ONE UNDO
		
		if (true) { //UL
			if (LM[y1][x1].size() > 0) {
				failx1 = true;
				faily1 = true;
			}
		}
		if (x1 != x2) { //UR
			if (LM[y1][x2].size() > 0) {
				faily1 = true;
				failx2 = true;
			}
		}	
		if (y1 != y2) {
			if (LM[y2][x1].size() > 0) {//LL
				failx1 = true;
				faily2 = true;
			}
			if (x1 != x2) {
				if (LM[y2][x2].size() > 0) { //LR
					failx2 = true;
					faily2 = true;
				}
			}
		}
		printf("Failsafes set\n");


		//CHECK/CHANGE - PRETTY SURE THIS DOES NOT RETUR ALL THE COLLISION VECTORS, SIMPLY BASED ON THAT if y is perfect, X MIGHT NOT BE.
		if (failx1 || failx2 || faily1 || faily2) { //Vector occupied!
			printf("Object%d is trying to go to somewhere occupied\n", ObjectSprite->OrderCreation + 1); 

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
			printf("You moving to: ");
			if (faily1) {
				if (failx1) {
					printf("UL [%d, %d], ", y1, x1);
				}
				if (failx2) {
					printf("UR [%d, %d], ", y1, x2);
				}
			}
			if (faily2) {
				if (failx1) {
					printf("LL [%d, %d], ", y2, x1);
				}
				if (failx2) {
					printf("LR [%d, %d], ", y2, x2);
				}
			}
			printf("Corners\n"); //so if you collide form beneth, your gaurenteeed to collide with LL, even if your just clipping LR...
		 
		}
		else {
			printf("nothing hit\n"); //nothing ran into
			for (int i = 0; i < 8; i++) {
				FutureCode[i] = -1;
			}

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
		
		printf("1\n");
		

		//Reset
		ReCreateQue2();

		 
	
		
		//Collision Loop
		for (int i = 0; i < std::distance(AllSprites.begin(), AllSprites.end()); i++) {
			printf("3\n" );
			



			if (Queue2[i] != NULL) { //because the stack replaces with null, unless its the end of stack
				printf("4\n");

				//Find the Que item, if it's in a stack, and resolve it.
				
				for (int j = 0; j < SpriteStackCounter; j++) {
					if (SpriteStack[j][SpriteStack[j].size() - 1]->OrderCreation == i) {
						InterestedStack = SpriteStack[j];
						InterestedStackIndex = j;

					}
				}
				printf("5\n");

				//Was not an end of stack
				if (InterestedStack.size() < 1) {

					printf("6\n");

					printf("Object%d x = %d, y = %d\n", Queue2[i]->OrderCreation + 1, Queue2[i]->xPos, Queue2[i]->yPos);
					//DisplayTileBasedArray();
					//Remove from map (So it doesn't collide with self)
					RemoveSpriteFromMap(Queue2[i]);
					//Adjust future position
					Queue2[i]->Behavior();
					//Will it Collide?

					
					 


					printf("7\n");

					
					CheckFutureSpritePosition(Queue2[i], FutureCode);
					if (FutureCode[0] != -1) {
						printf("(0,1) y=%d, c=%d\n", FutureCode[0], FutureCode[1]);
						CollidedSprite1 = LM[FutureCode[0]][FutureCode[1]];
						printf("7.1\n");
					}
					if (FutureCode[2] != -1) {
						printf("(2, 3) y=%d, c=%d\n", FutureCode[2], FutureCode[3]);
						CollidedSprite2 = LM[FutureCode[2]][FutureCode[3]];
						printf("7.2\n");
					}
					if (FutureCode[4] != -1) {
						printf("(4, 5) y=%d, c=%d\n", FutureCode[4], FutureCode[5]);
						CollidedSprite3 = LM[FutureCode[4]][FutureCode[5]];
						printf("7.3\n");
					}
					if (FutureCode[6] != -1) {
						printf("(6, 7) y=%d, c=%d\n", FutureCode[6], FutureCode[7]);
						CollidedSprite4 = LM[FutureCode[6]][FutureCode[7]];
						printf("7.4\n");
					}
					printf("8\n");
					
					
					
					//If does not:
					if (CollidedSprite1.size() < 1 && CollidedSprite2.size() < 1 && CollidedSprite3.size() < 1 && CollidedSprite4.size() < 1) { //if there's nothing occupying the vector it's moving to.
						printf("9\n");
						printf("sizes of vectors(1,2,3,4)= %d, %d, %d, %d.\n", CollidedSprite1.size(), CollidedSprite2.size(), CollidedSprite3.size(), CollidedSprite4.size());
						//DisplayTileBasedArray();
						//Move it
						Queue2[i]->MoveTargetTileX();
						Queue2[i]->MoveTargetTileY();
						//Removeit from the Que
						//
						//Remap it - so that if a later tile tries moving there, it can't.
						printf("9.5\n");
						ReMapSprite(Queue2[i]); //update position on the vector
						printf("10\n");
						//printf("(if) Remapped Object%d\n", Queue2[i]->OrderCreation + 1);
						printf("(if) Object%d x = %d \n", Queue2[i]->OrderCreation + 1, Queue2[i]->xPos);


						 



						Queue2[i] = NULL;
					}

					
					//If it does:
					else { //if occupied tile
						printf("11\n");
						
						//ASSUME TILE=PIXEL collision. 
						//undo the move stuff, until we confirm we can move later.
						DisplayTileBasedArray();
						Queue2[i]->UndoBehavior();
						//Remap it, because it was unable to move right away
						
						

						printf("12\n");
						

						//This starts the recurssion, so it will take itself out of the Que, 

						//IDEALLY, you check the pixels, then call the first one that failed, but contniue for all those in the vector that actually stopped it

						//NOTE - NEEDS WORK, WHAT IF THERE ARE TWO TILES, (ORDER THE COLLIDED SPRITE TO PRIROTIZE THE LEFT UPEPER CORNER, SO YOU CAN ASSUME OR SOMETHING, THEN CHECK THE OTHER IF APPLICABLE?)
						//add self to stack
						

						SpriteStack.push_back({});
						SpriteStack[SpriteStackCounter].push_back(Queue2[i]->GetThis());  


						//remove self from que. NOTE - we can do this, because only the end of the stack will remain in the que. 
						Queue2[i] = NULL;
						printf("13\n");
					
						MoveCurrentSprite(CollidedSprite1, CollidedSprite2, CollidedSprite3, CollidedSprite4, SpriteStackCounter, 0, 0, 0, 0); //there is up to two vectors, that we must order :/.
						printf("14\n");
						//remap after so it doesn't run into itself when moving.
						ReMapSprite(SpriteStack[SpriteStackCounter][0]); //get around the null. May change later
						

						SpriteStackCounter += 1; //After recursion is done, we wait. If another stack is started it should happen in a new whole stack.
						printf("15\n");
						
					}

				}

				//Was the end of stack
				else {
					printf("Stack Found\n");
					//Try to move it now
					//It can - resolve next in stack, if it's a older item than the other stacks. (It's like solitare?) AND not past the rest of the que.
					// IF the stack has a younger item, reque it. It'll discover it at the end of this stack.
					//It can't - Delete the whole stack. It's all 'stuck'
					
					if (HandleStack(Queue2[i], InterestedStack, InterestedStack.size() - 1) == 0) {
						SpriteStack.erase(SpriteStack.begin() + InterestedStackIndex); //if it failed, then the stack should end immediately and never be checked again
						Queue2[i]->UndoBehavior(); 
						SpriteStackCounter -= 1;
					}
		
					Queue2[i] = NULL;
					
					//1 Start taking the stack down in pace. - for now only a sprite can be in one stack at a time
					//This is like MoveCurrent, except it's like this, but if it fails still, then it fails the entire stack. 
					//clear stack whence finished (internal). 

				}
				//DOUBLE CHECK THE STACK IS MORE THAN ONE IN THE LOOP, THEN YOU MAY NOT NEED HTE HANDLE FINAL STACK?!


			}
		}
		//INSERT - final stack check
		//INSERT - TOTALLY CLEAN STACK, erase literally everything. (external too?)
		
		//Tries to handle end of que stacks. 
		while (SpriteStack.size() != 0) {
			printf("!\n");
			InterestedStack = {};
			InterestedStackIndex = -1;
			for (int j = 0; j < SpriteStack.size(); j++) {
				printf("? New J is %d\n", j);
				//eliminate empty stacks, restarts the for loop
				if (SpriteStack[j].size() < 1) {
					printf("Attempt to erase SpriteStack[%d]\n", j);
					SpriteStack.erase(SpriteStack.begin()+j);
					j--;
					printf("! Change J to %d", j); //so we should see it 'snap' back to it's proper position.
					continue;
				}
				//find the first viable stack
				if (InterestedStackIndex < 0) {
					printf("Set itinital StackIndex\n");
					InterestedStackIndex = j;
				}
				//find the smallest end of stack possible
				if (SpriteStack[j][SpriteStack[j].size() - 1]->OrderCreation < SpriteStack[InterestedStackIndex][SpriteStack[InterestedStackIndex].size() - 1]->OrderCreation) {
					printf("Found new smaller sprite for index\n");
					InterestedStackIndex = j;
				}
			}
			//NOW IF there still exists any stack
			if (SpriteStack.size() != 0) {
				printf("SpriteStack not yet 0, attempt to handle the final stack here\n");
				if (HandleFinalStack(SpriteStack[InterestedStackIndex], SpriteStack[InterestedStackIndex].size()-1) == 0) { //if succeeded in moving that item good, else if 0, then erase the whole stack. Perhaps mark if the item couldn't move so other stacks don't get any ideas.
					printf("An item has failed, delete that stack\n");
					SpriteStack.erase(SpriteStack.begin() + InterestedStackIndex);
				}
			}


		}

		//use .popback of vectors to do 
		//HandleFinalStack - it's important it's not recursive, but just decides if the stack can compelte. If not, inavlidate that whole stack from that point up. 


		for (int j = 0; j < SpriteStack.size(); j++) {
			SpriteStack[j].clear();
			printf("P");
		}
		SpriteStack.clear();
		SpriteStackCounter = 0;

	}


	//Recursive
	//function takes sprite ran into, tries moving, if fails, recursive until success.
	//On success, DON'T MOVE IT, until everything before the last item in the stack has been moved. Thus in AllSprites we must look each time
	//for when a stack can be completed... :/
	void MoveCurrentSprite(std::vector<Sprite*>& OldCollidedSprite1, std::vector<Sprite*>& OldCollidedSprite2, std::vector<Sprite*>& OldCollidedSprite3, std::vector<Sprite*>& OldCollidedSprite4, int Itter1, int Itter2, int Itter3, int Itter4, int InheritedSpriteStackCounter) {
		printf("alrighty\n");

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

		printf("ArrHolder's Set to either a Sprite or Null\n");

		//NOTE only move itters if we actually use the found tile in that vector, 


		//INSERT CHECK - there is a chance that an vecto rlooks like {1, 2, 3}, {2, 3}, and you hit 1 and 2, need a method to control IF you've seen it already. 
		//determine which Sprite is Created First
		for (int i = 0; i < 4; i++) {
			if (ArrHolder[i]!=NULL) { //while NextSprite is a Sprite, try finding the lowest possible
				printf("Arr%d = Object%d found\n", i, ArrHolder[i]->OrderCreation + 1);

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
		printf("NextSprite Set\n");

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




			printf("Itterated itters\n");


			//remove from Que IF THIS IS NOT THE END OF STACK (Queue2[NextSprite->OrderCreation] = NULL;)
			printf("Object%d x = %d, y = %d \n", NextSprite->OrderCreation + 1, NextSprite->xPos, NextSprite->yPos);

			//CHECK CHECK - CHECK - I THINK THIS WILL BE FINE HERE
			if (Queue2[NextSprite->OrderCreation] != NULL) { //If the NextSprite is not in a stack, AND still in hte Que
				printf("16\n");
				//Remove from map (So it doesn't collide with self)
				RemoveSpriteFromMap(NextSprite);
				//Adjust future position
				NextSprite->Behavior();
				printf("17\n");
				//Will it Collide?
				CheckFutureSpritePosition(NextSprite, FutureCode);
				printf("18\n");
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
				printf("19\n");


				//If does not:
				if (CollidedSprite1.size() < 1 && CollidedSprite2.size() < 1 && CollidedSprite3.size() < 1 && CollidedSprite4.size() < 1) { //if there's nothing occupying the vector it's moving to.
					//Success, wait for main loop to move it. Then if it was done in the main loop, check if the next in this stack was less than what it was waiting for
					//Queue2[NextSprite->OrderCreation] = NULL; //we DONT want to set it to null, otherwise we'd have to check every number against the stack, instead of just the ends.
					printf("20\n");
					SpriteStack[SpriteStackCounter].push_back(Queue2[NextSprite->OrderCreation]);
					printf("Stack ended with the sprite Sprite%d\n", NextSprite->OrderCreation + 1);
					//NOTE - So it doesn't double up on hte movement in the Que loop. should find a better way of doing this.
					NextSprite->UndoBehavior(); //NEW
					ReMapSprite(NextSprite); //NEW
					printf("20.5\n");
				}
				//If it does:
				else { //if occupied tile
					printf("Stack can still grow\n");
					DisplayTileBasedArray();
					printf("21\n");

					//IDEALLY, you check the pixels, then call the first one that failed, but contniue for all those in the vector that actually stopped it
					//NOTE - NEEDS WORK, WHAT IF THERE ARE TWO TILES, (ORDER THE COLLIDED SPRITE TO PRIROTIZE THE LEFT UPEPER CORNER, SO YOU CAN ASSUME OR SOMETHING, THEN CHECK THE OTHER IF APPLICABLE?)
					//add self to stack
					SpriteStack[SpriteStackCounter].push_back(Queue2[NextSprite->OrderCreation]);
					printf("21\n");
					//remove self from que. NOTE - we can do this, because only the end of the stack will remain in the que. 
					Queue2[NextSprite->OrderCreation] = NULL;
					printf("22\n");
					MoveCurrentSprite(CollidedSprite1, CollidedSprite2, CollidedSprite3, CollidedSprite4, CurrentStackCounter, 0, 0, 0, 0); //there is up to two vectors, that we must order :/.
					printf("23\n");


					NextSprite->UndoBehavior();
					//Remap it, because it was unable to move right away
					printf("25\n");

					//NOTE the undo and remap after the stack, so when we resolve backwards we have a chance at finishing entire stacks if one part fails.
					ReMapSprite(Queue2[NextSprite->OrderCreation]);
					printf("24\n");
					//May want to add one to the spritestack here, use spritestack^
//then assign old at the start to use V

					

				}
			}
			else {  //if EITHER NextSprite is in a Stack (Add it to the stack we're trying to go to, we'll have some way to mark if it's already been moved by a stack), OR in the QUE still. ASSUME QUE
				//NOTE - NEXT SPRITE WAS NULL IN QUE2 EITHER IT IS IN THE MIDDLE OF A QUE, OR CLAIMED BY THE QUE2 REGULAR 
				//eventually will need to check either the stack or the que to double check
				printf("NextSprite has already been claimed by EITHER by a different stack, or the regualr Que. For now, Assume Que\n");  
				printf("26\n");
				//NOTE - Don't leave the loop, since you may have other tiles to compare too later in the vector.
			}

		}
		else {
			printf("NextSprite was NULL (Not sure exactly what this is telling me besides the vectorss were all empty...?)\n");
			printf("27\n");
		}
		//think about this thing
		//  4   5 
		//  ^ >^
		//  2   1
		//   ^< ^
		// 3  < 0
		//
		//0, 1 5 2 4 5 3
		//so when completing a stack, just check to see if que is null there as well.

		
		//This is called to keep grinding away the current
		while (itter1 < size1 || itter2 < size2 || itter3 < size3 || itter4 < size4) {
			printf("28\n");
			printf("An Itter is still less than the size of a vector, %d, %d, %d, %d\n", itter1, itter2, itter3, itter4); //I know I've got to itterate it if it's the same sprite that I just looked at. Thus I'll need an expensive compare :/
			MoveCurrentSprite(OldCollidedSprite1, OldCollidedSprite2, OldCollidedSprite3, OldCollidedSprite4, itter1, itter2, itter3, itter4, CurrentStackCounter);
		
		}
	}
	
	//Object to move first, //the stack inside the stack to attempt to move //In hte internal stack, what's the index to move?
	int HandleStack(Sprite*& ObjectSprite, std::vector<Sprite*>& InterestedStack, int InternalStackIndex) {
		//InternalStack = the last index, as this recursive, subtract one so long as it's not negative.
		if (InternalStackIndex >-1) {
			printf("Handle Stack Appropriately\n");


			std::vector<Sprite*> CollidedSprite1; //Upper Left Corner
			std::vector<Sprite*> CollidedSprite2; //Upper Right corner
			std::vector<Sprite*> CollidedSprite3; //Lower Left Corner
			std::vector<Sprite*> CollidedSprite4; //Lower Right Corner - fourth may be unnecessary
			int FutureCode[8]; //CHECK that the size is 8! including 0;
			//NOTE - If you get an error (when going between tiles) it is likely your moving xPos before removing it from the Matrix!!!!!
			//NOTE - Especially if it says something about the vector itterators in removespritefrommap()

			printf("Object%d in stack to be moved\n", ObjectSprite->OrderCreation+1);
			//SDL_Delay(10000);

			RemoveSpriteFromMap(InterestedStack[InternalStackIndex]);
			InterestedStack[InternalStackIndex]->Behavior();
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
			



			//If does not:
			if (CollidedSprite1.size() < 1 && CollidedSprite2.size() < 1 && CollidedSprite3.size() < 1 && CollidedSprite4.size() < 1) { //if there's nothing occupying the vector it's moving to.
				//something wrong here. the number is a poitner :/
				printf("Move Object%d, from the stack.\n", InterestedStack[InternalStackIndex]->OrderCreation + 1);
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
				InternalStackIndex -= 1;
				if (InternalStackIndex > -1) {
					if (HandleStack(InterestedStack[InternalStackIndex], InterestedStack, InternalStackIndex) == 1) {
						printf("Stack Handled stacklayer = %d\n", InternalStackIndex);  //previous one finished fine

					}
				}
				return 1; //This current sprite succeeded, even if the one in the loop failed. 



			}

			//If it does:
			else { //if occupied tile
				printf("Stacked Sprite trying to move into another object. Fails to move\n");
				InterestedStack[InternalStackIndex]->UndoBehavior();
				ReMapSprite(InterestedStack[InternalStackIndex]); //get around the null. May change later
				return 1;

			}

		}
		else {
			printf("Itterator went passed the allowed 'end' of 0 - whole stack resolved nicely.\n");
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
			

			printf("Object%d in stack (end) to be moved\n", InterestedStack[EndOfStack]->OrderCreation + 1);
			//SDL_Delay(10000);

			//move
			RemoveSpriteFromMap(InterestedStack[EndOfStack]);
			InterestedStack[EndOfStack]->Behavior();
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
				printf("Move Object%d, from the stack.\n", InterestedStack[EndOfStack]->OrderCreation + 1);
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
				printf("Stacked Sprite trying to move into another object. Fails to move\n");
				InterestedStack[EndOfStack]->UndoBehavior();
				ReMapSprite(InterestedStack[EndOfStack]); //get around the null. May change later
				//erase the whole stack, either that or pop back then erase in the other loop. 
				return 0;

			}

	}
		
	


//AllSprites = Every Sprite in order (first to last created)
//Queue2 =Every Sprite in order -Moved Sprites
							  //-Sprites in Stack
							 //+ Sprites at the end of a stack.
//Stack						// -moved good //if it mvoed good, it's the end of stack
							//-end of stack //if it's the end of stack, keep it in que AND stack
							//+in stack
							//+end stack

	
	

	void RemoveSpriteFromMap(Sprite* ObjectSprite) {
		printf("RemoveSpriteFromMap\n");
		int x1, x2, y1, y2;
		x1 = ObjectSprite->xPos;
		x2 = ObjectSprite->xPos + TILE_WIDTH;
		y1 = ObjectSprite->yPos;
		y2 = ObjectSprite->yPos + TILE_HEIGHT;
		

		//NOTE - YOU CANT RELY on the first in order going first, this is because A may be blocked by G, so G resolves first, but if they are on the same 'tile' then A is the begiing of hte vector, which gets stupid after a while, because you move without knowing if G got out of the way.
	


		x1 = x1 / TILE_WIDTH; //saves an small amount of comuptation
		x2 = x2 / TILE_WIDTH;
		y1 = y1 / TILE_HEIGHT;
		y2 = y2 / TILE_HEIGHT;
		//gaurds from map/matrix overflow
		if (y2 > LEVEL_HEIGHT - 1) {
			y2 = LEVEL_HEIGHT - 1;
			y1 = LEVEL_HEIGHT - 2;
		}
		if (y1 < 0) {
			y1 = 0;
			y2 = TILE_HEIGHT;
		}
		if (x2 > LEVEL_WIDTH - 1) {
			x2 = LEVEL_WIDTH - 1;
			x1 = LEVEL_WIDTH - 2;
		}
		if (x1 < 0) {
			x1 = 0;
			x2 = TILE_WIDTH - 1;
		}
		if (LM[y1][x1].size() > 0) {
			LM[y1][x1].erase(find(LM[y1][x1].begin(), LM[y1][x1].end() - 1, ObjectSprite));
			
		}
		if (LM[y1][x2].size() > 0) {
			LM[y1][x2].erase(find(LM[y1][x2].begin(), LM[y1][x2].end() - 1, ObjectSprite));
			
		}
		if (LM[y2][x1].size() > 0) {
			LM[y2][x1].erase(find(LM[y2][x1].begin(), LM[y2][x1].end() - 1, ObjectSprite));
			
		}
		if (LM[y2][x2].size() > 0) {
			LM[y2][x2].erase(find(LM[y2][x2].begin(), LM[y2][x2].end() - 1, ObjectSprite));
			
		}

		printf("Erased all\n");
	}
	

};
