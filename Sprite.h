#pragma once




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
	int directionX; //NEW, holds onto the starting dierction, and how quickly it will move when it's 'pacing'. It must be stored or returned from the function, otherwise it will cling to the edge of hte pace distance.
	int leftXlimit; //NEW don't know how I want to handle it for now, but will store in sprite for now.
	int rightXlimit; 
	



	Sprite(int x, int y, std::string l, std::map<std::string, SurfaceProperty*> SurfacePropertyMap, int Order) {
		xPos = x;
		yPos = y;
		label = l;

		IMGName = label.substr(0, 2); // this is the letter part of label -- the AA

		directionX = 0; // NEW, this is like the velocity and starti ndirection of the sprite;
		OrderCreation = Order;//NEW
		leftXlimit = 0; //edited by user potentially idk what default we want.
		rightXlimit = 0;
		


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
	Sprite(int x, int y, std::string l, std::map<std::string, SurfaceProperty*> SurfacePropertyMap, int Order, int Velx, int LeftXLimit, int RightXLimit) {
		xPos = x;
		yPos = y;
		label = l;

		IMGName = label.substr(0, 2); // this is the letter part of label -- the AA

		directionX = Velx; // NEW, this is like the velocity and starti ndirection of the sprite;
		leftXlimit=LeftXLimit;
		rightXlimit=RightXLimit;
		OrderCreation = Order;//NEW
		


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
			TargetTile->x += x;
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
			TargetTile->y += y;
			return 1;
		}
	}

	void BlitThis(SDL_Surface* TargetSurface) {
		//TargetTile->x = xPos;
		TargetTile->y = yPos;
		TargetTile->w = TILE_WIDTH;
		TargetTile->h = TILE_HEIGHT;
		SDL_BlitSurface(SurfacePropertyMap[IMGName]->GetSelfSurface(), SourceTile, TargetSurface, TargetTile); 
	}

	int AutoX() { 

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
		
			


			if (directionX > 0) { //going right
				//printf("Object %d, is going right\n", OrderCreation + 1);
				if (xPos + directionX < rightXlimit) {
					//printf("Go Right\n");
					xPos += directionX;
				}
				else {
					//turn around
					//printf("Turn Left\n");
					directionX = -directionX;
					//move - this could be disabled potentially
					xPos += directionX;
				}
			}
			else if (directionX < 0) { //going left
				//printf("Object %d, is going left\n", OrderCreation + 1);
				if (xPos + directionX > leftXlimit) {
					//printf("Go Left\n");
					xPos += directionX;
				}
				else {
					//turn around
					//printf("Turn Right\n");
					directionX = -directionX;
					//move -this coudl be disabled 
					xPos += directionX;
				}
			}
			//SDL_Delay(500);



		


		//fail -for now don't care
		//UndoAutoX();

		//Okay now check LM in object layer,
		//IF FAILS, add to a queue and figure out what blocked it
		//Check the values backwards, if fails again - CALL 'UndoMovementX' or something. haven't decided how I want to do that.for now it'll be jerryrigged.
		//if success, great. Change TargetTile then (Because objects are moving on the object layer independent of the player. They move like the background if they are still, they move themselves too) 
	}

	void MoveTargetTileX() {
		printf("Object%d,  too xPos %d\n", OrderCreation + 1, xPos);
		TargetTile->x = xPos;
		//called on success of autoMoveX, means I can move the tile location on lm, 
		//so remove it's previous position
		//move targettile=xpos

		//move it's position in the matrix


	}
	void MoveTargetTileX() {
		printf("Object%d,  too yPos %d\n", OrderCreation + 1, yPos);
		TargetTile->y = yPos;
		//called on success of autoMoveX, means I can move the tile location on lm, 
		//so remove it's previous position
		//move targettile=xpos

		//move it's position in the matrix


	}
	void UndoAutoX() {
		xPos -= directionX; //no matter what direction it's heading, this will undo it. - this also assumes your moving when your turning around. 

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


	ObjectLayer(std::vector<Sprite*> ASprites) {
		printf("ObjectLayer Created\n");

		AllSprites = ASprites;

		TargetSurface = SDL_CreateRGBSurface(0, LEVEL_WIDTH * TILE_WIDTH, LEVEL_HEIGHT * TILE_HEIGHT, 32, 0, 0, 0, 0); // ERROR WAS HERE -- SHOW JACOB!!! BECAUSE IT'S FUNNY
		CombinedObjects = NULL;
		CreateTransparency("0x000000");
		BlitObjects();

	}

	ObjectLayer() {
		printf("ObjectLayer Created\n");

		//the vector is increased each time an object appears

		TargetSurface = SDL_CreateRGBSurface(0, LEVEL_WIDTH * TILE_WIDTH, LEVEL_HEIGHT * TILE_HEIGHT, 32, 0, 0, 0, 0); // ERROR WAS HERE -- SHOW JACOB!!! BECAUSE IT'S FUNNY
		CombinedObjects = NULL;
		CreateTransparency("0x000000");
		//BlitObjects(); will call this after all sprites are called.

		LM = new std::vector<Sprite*>* [LEVEL_HEIGHT];
		for (int i = 0; i < LEVEL_HEIGHT; i++) {
			printf("\n");
			LM[i] = new std::vector<Sprite*>  [LEVEL_WIDTH];
			for (int j = 0; j < LEVEL_WIDTH; j++) {
				printf(".");

			}
		}
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
		printf("BlitObjects in SpriteLayer\n");
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
			Queue2[i] = AllSprites[i];
		}
	}


	void MoveAllSprites() {
		for (int i = 0; i < std::distance(AllSprites.begin(), AllSprites.end()); i++) {
			AllSprites[i]->AutoX();
			if (CheckFutureSpritePosition(AllSprites[i])) { //if it returns 1
				RemoveSpriteFromMap(AllSprites[i]);
				AllSprites[i]->MoveTargetTileX();
				AllSprites[i]->MoveTargetTileX();
				ReMapSprite(AllSprites[i]); //update position on the vector

			}
			else { //if returned 0
				AllSprites[i]->UndoAutoX(); //TEMP YOU DO NOT WANTTO UNDO BEFORE STACK CHECK AND MOVES

				//place on stack, at the end of all this move, we'll go through the stack/queue or somethin
			}

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
		int x1 =NULL;
		int x2 =NULL;
		int y1 =NULL;
		int y2 =NULL;
		//The null will allow us to skip it if there is no info there.
		x1 = ObjectSprite->xPos;
		x2 = ObjectSprite->xPos + TILE_WIDTH;
		y1 = ObjectSprite->yPos;
		y2 = ObjectSprite->yPos + TILE_HEIGHT;



		if (y1 % TILE_HEIGHT == 0) {
			printf("Just map y1, ");
			//just map y1 - perfectly placed in tilemap
			if (x1 % TILE_WIDTH == 0) {
				printf("and x1 = ");
				//just map x1 - perfectly placed in tilemap
				printf(" %d, %d, \n", x1/TILE_WIDTH, y1/TILE_HEIGHT);

				LM[y1 / TILE_HEIGHT][x1 / TILE_WIDTH].push_back(ObjectSprite);
			}
			else {
				printf("and x1, x2 = ");
				//map x1 and x2
				y1 = y1 / TILE_HEIGHT; //saves small amount of computation
				printf(" %d, %d, %d\n", x1/TILE_WIDTH, x2/TILE_WIDTH, y1);

				LM[y1][x1 / TILE_WIDTH].push_back(ObjectSprite);
				LM[y1][x2 / TILE_WIDTH].push_back(ObjectSprite);
			}
		}
		else {
			//map y1 and y2
			printf("Just map y1, y2, ");
			if (x1 % TILE_WIDTH == 0) {
				//just map x1 - perfectly placed in tilemap
				printf("and x1 = ");
				x1 = x1 / TILE_WIDTH; //saves an small amount of comuptation
				printf(" %d, %d, %d\n", x1, y1/TILE_HEIGHT, y2/TILE_HEIGHT);

				LM[y1 / TILE_HEIGHT][x1].push_back(ObjectSprite);
				LM[y2 / TILE_HEIGHT][x1].push_back(ObjectSprite);
			}
			else {
				//map x1 and x2
				printf("and x1, x2 = ");
				x1 = x1 / TILE_WIDTH; //saves an small amount of comuptation
				x2 = x2 / TILE_WIDTH;
				y1 = y1 / TILE_HEIGHT;
				y2 = y2 / TILE_HEIGHT;
				printf(" %d, %d, %d, %d\n", x1, x2, y1, y2);
				LM[y1][x1].push_back(ObjectSprite);
				LM[y1][x2].push_back(ObjectSprite);
				LM[y2][x1].push_back(ObjectSprite);
				LM[y2][x2].push_back(ObjectSprite);
			}
		}
		
		

	}
	void DisplayTileBasedArray() {
		/*
		LM = new std::vector<Sprite*>**[LEVEL_HEIGHT];
		for (int i = 0; i < LEVEL_HEIGHT; i++) {
			printf("\n");
			LM[i] = new std::vector<Sprite*>*[LEVEL_WIDTH];
			for (int j = 0; j < LEVEL_WIDTH; j++) {
				printf(".");
				LM[i][j] = new std::vector<Sprite*>;
			}
		}
	}
	*/

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

	}
	void RemoveSpriteFromMap(Sprite* ObjectSprite) {

		int x1, x2, y1, y2;
		x1 = ObjectSprite->xPos;
		x2 = ObjectSprite->xPos + TILE_WIDTH;
		y1 = ObjectSprite->yPos;
		y2 = ObjectSprite->yPos + TILE_HEIGHT;


		//NOTE - YOU CANT RELY on the first in order going first, this is because A may be blocked by G, so G resolves first, but if they are on the same 'tile' then A is the begiing of hte vector, which gets stupid after a while, because you move without knowing if G got out of the way.
		if (y1 % TILE_HEIGHT == 0) {
			//printf("Just remove y1, ");
			//just map y1 - perfectly placed in tilemap
			if (x1 % TILE_WIDTH == 0) {
				//printf("and x1 = ");
				//just map x1 - perfectly placed in tilemap
				//printf(" %d, %d, \n", x1 / TILE_WIDTH, y1 / TILE_HEIGHT);
				y1 = y1 / TILE_HEIGHT;
				x1 = x1 / TILE_WIDTH;
				LM[y1][x1].erase(find(LM[y1][x1].begin(), LM[y1][x1].end(), ObjectSprite));
			}
			else {
				//printf("and x1, x2 = ");
				//map x1 and x2
				y1 = y1 / TILE_HEIGHT; //saves small amount of computation
				x1 = x1 / TILE_WIDTH;
				x2 = x2 / TILE_WIDTH;
				//printf(" %d, %d, %d\n", x1 / TILE_WIDTH, x2 / TILE_WIDTH, y1);

				LM[y1][x1].erase(find(LM[y1][x1].begin(), LM[y1][x1].end(), ObjectSprite));
				LM[y1][x2].erase(find(LM[y1][x2].begin(), LM[y1][x2].end(), ObjectSprite));
			}
		}
		else {
			//map y1 and y2
			//printf("Just remove y1, y2, ");
			if (x1 % TILE_WIDTH == 0) {
				//just map x1 - perfectly placed in tilemap
				//printf("and x1 = ");
				y1 = y1 / TILE_HEIGHT;
				y2 = y2 / TILE_HEIGHT;
				x1 = x1 / TILE_WIDTH; //saves an small amount of comuptation
				//printf(" %d, %d, %d\n", x1, y1 / TILE_HEIGHT, y2 / TILE_HEIGHT);

				LM[y1][x1].erase(find(LM[y1][x1].begin(), LM[y1][x1].end(), ObjectSprite));
				LM[y2][x1].erase(find(LM[y2][x1].begin(), LM[y2][x1].end(), ObjectSprite));
			}
			else {
				//map x1 and x2
				//printf("and x1, x2 = ");
				x1 = x1 / TILE_WIDTH; //saves an small amount of comuptation
				x2 = x2 / TILE_WIDTH;
				y1 = y1 / TILE_HEIGHT;
				y2 = y2 / TILE_HEIGHT;
				//printf(" %d, %d, %d, %d\n", x1, x2, y1, y2);
				LM[y1][x1].erase(find(LM[y1][x1].begin(), LM[y1][x1].end(), ObjectSprite));
				LM[y1][x2].erase(find(LM[y1][x2].begin(), LM[y1][x2].end(), ObjectSprite));
				LM[y2][x1].erase(find(LM[y2][x1].begin(), LM[y2][x1].end(), ObjectSprite));
				LM[y2][x2].erase(find(LM[y2][x2].begin(), LM[y2][x2].end(), ObjectSprite));
			}
		}



	}
	void ReMapSprite(Sprite* ObjectSprite) {
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


		//NOTE - replace pushbacks with inserts - unless empty vector

		if (y1 % TILE_HEIGHT == 0) {
			//printf("Just map y1, ");
			//just map y1 - perfectly placed in tilemap
			if (x1 % TILE_WIDTH == 0) {
				//printf("and x1 = ");
				//just map x1 - perfectly placed in tilemap
				//printf(" %d, %d, \n", x1 / TILE_WIDTH, y1 / TILE_HEIGHT);
				y1 = y1 / TILE_HEIGHT;
				x1 = x1 / TILE_WIDTH;
				
				if (LM[y1][x1].size() == 0) {
					LM[y1][x1].push_back(ObjectSprite);
				}
				else {
					while (LM[y1][x1][OrderedPosition]->OrderCreation < ObjectSprite->OrderCreation) {
						OrderedPosition++;
					}
					LM[y1][x1].insert(LM[y1][x1].begin() + OrderedPosition, ObjectSprite);
				}


			}
			else {
				//printf("and x1, x2 = ");
				//map x1 and x2
				y1 = y1 / TILE_HEIGHT; //saves small amount of computation
				//printf(" %d, %d, %d\n", x1 / TILE_WIDTH, x2 / TILE_WIDTH, y1);
				x1 = x1 / TILE_WIDTH;
				x2 = x2 / TILE_WIDTH;

				if (LM[y1][x1].size() == 0) {
					LM[y1][x1].push_back(ObjectSprite);
				}
				else {
					while (LM[y1][x1][OrderedPosition]->OrderCreation < ObjectSprite->OrderCreation) {
						OrderedPosition++;
					}
					LM[y1][x1].insert(LM[y1][x1].begin()+OrderedPosition,ObjectSprite);
					OrderedPosition = 0;
				}


				if (LM[y1][x2].size() == 0) {
					LM[y1][x2].push_back(ObjectSprite);
				}
				else {
					while (LM[y1][x2][OrderedPosition]->OrderCreation < ObjectSprite->OrderCreation) {
						OrderedPosition++;
					}
					LM[y1][x2].insert(LM[y1][x2].begin() + OrderedPosition, ObjectSprite);
					 
				}

			 
			}
		}

		else {
			//map y1 and y2
			//printf("Just map y1, y2, ");
			if (x1 % TILE_WIDTH == 0) {
				//just map x1 - perfectly placed in tilemap
				//printf("and x1 = ");
				x1 = x1 / TILE_WIDTH; //saves an small amount of comuptation
				//printf(" %d, %d, %d\n", x1, y1 / TILE_HEIGHT, y2 / TILE_HEIGHT);
				y1 = y1 / TILE_HEIGHT;
				y2 = y2 / TILE_HEIGHT;


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

				if (LM[y2][x1].size() == 0) {
					LM[y2][x1].push_back(ObjectSprite);
				}
				else {
					while (LM[y2][x1][OrderedPosition]->OrderCreation < ObjectSprite->OrderCreation) {
						OrderedPosition++;
					}
					LM[y2][x1].insert(LM[y2][x1].begin() + OrderedPosition, ObjectSprite);
				}
				 
			}


			else {
				//map x1 and x2
				//("and x1, x2 = ");
				x1 = x1 / TILE_WIDTH; //saves an small amount of comuptation
				x2 = x2 / TILE_WIDTH;
				y1 = y1 / TILE_HEIGHT;
				y2 = y2 / TILE_HEIGHT;
				///printf(" %d, %d, %d, %d\n", x1, x2, y1, y2);

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


	}

	bool CheckFutureSpritePosition(Sprite* ObjectSprite) {
		int x1, x2, y1, y2;
		bool failx1, failx2, faily1, faily2;
		x1 = ObjectSprite->xPos;
		x2 = ObjectSprite->xPos + TILE_WIDTH;
		y1 = ObjectSprite->yPos;
		y2 = ObjectSprite->yPos + TILE_HEIGHT;





		//NOTE only one fail should happen, if multiple happen let it just undo the movement once, NO NEED FOR MORE THAN ONE UNDO
		if (y1 % TILE_HEIGHT == 0) {
			//printf("Just remove y1, ");
			//just map y1 - perfectly placed in tilemap
			if (x1 % TILE_WIDTH == 0) {
				//printf("and x1 = ");
				//just map x1 - perfectly placed in tilemap
				//printf(" %d, %d, \n", x1 / TILE_WIDTH, y1 / TILE_HEIGHT);
				y1 = y1 / TILE_HEIGHT;
				x1 = x1 / TILE_WIDTH;

				if (LM[y1][x1].size() > 0) {
					printf("TILE THAT Object%d is trying to go is occupied!\n", ObjectSprite->OrderCreation + 1);
					failx1 = true;
					faily1 = true;
				}




			}
			else {
				//printf("and x1, x2 = ");
				//map x1 and x2
				y1 = y1 / TILE_HEIGHT; //saves small amount of computation
				x1 = x1 / TILE_WIDTH;
				x2 = x2 / TILE_WIDTH;
				//printf(" %d, %d, %d\n", x1 / TILE_WIDTH, x2 / TILE_WIDTH, y1);

				if (LM[y1][x1].size() > 0) {
					printf("TILE THAT Object%d is trying to go is occupied!\n", ObjectSprite->OrderCreation + 1);
					failx1 = true;
					faily1 = true;
				}
				if (LM[y1][x2].size() > 0) {
					printf("TILE THAT Object%d is trying to go is occupied!\n", ObjectSprite->OrderCreation + 1);
					faily1 = true;
					failx2 = true;
				}



			}
		}
		else {
			//map y1 and y2
			//printf("Just remove y1, y2, ");
			if (x1 % TILE_WIDTH == 0) {
				//just map x1 - perfectly placed in tilemap
				//printf("and x1 = ");
				y1 = y1 / TILE_HEIGHT;
				y2 = y2 / TILE_HEIGHT;
				x1 = x1 / TILE_WIDTH; //saves an small amount of comuptation
				//printf(" %d, %d, %d\n", x1, y1 / TILE_HEIGHT, y2 / TILE_HEIGHT);

				if (LM[y1][x1].size() > 0) {
					printf("TILE THAT Object%d is trying to go is occupied!\n", ObjectSprite->OrderCreation + 1);
					failx1 = true;
					faily1 = true;
				}
				if (LM[y2][x1].size() > 0) {
					printf("TILE THAT Object%d is trying to go is occupied!\n", ObjectSprite->OrderCreation + 1);
					failx1 = true;
					faily2 = true;
				}


			}
			else {
				//map x1 and x2
				//printf("and x1, x2 = ");
				x1 = x1 / TILE_WIDTH; //saves an small amount of comuptation
				x2 = x2 / TILE_WIDTH;
				y1 = y1 / TILE_HEIGHT;
				y2 = y2 / TILE_HEIGHT;
				//printf(" %d, %d, %d, %d\n", x1, x2, y1, y2);
				if (LM[y1][x1].size() > 0) {
					printf("TILE THAT Object%d is trying to go is occupied!\n", ObjectSprite->OrderCreation + 1);
					failx1 = true;
					faily1 = true;
				}
				if (LM[y1][x2].size() > 0) {
					printf("TILE THAT Object%d is trying to go is occupied!\n", ObjectSprite->OrderCreation + 1);
					failx2 = true;
					faily1 = true;
				}
				if (LM[y2][x1].size() > 0) {
					printf("TILE THAT Object%d is trying to go is occupied!\n", ObjectSprite->OrderCreation + 1);
					failx1 = true;
					faily2 = true;
				}
				if (LM[y2][x2].size() > 0) {
					printf("TILE THAT Object%d is trying to go is occupied!\n", ObjectSprite->OrderCreation + 1);
					failx2 = true;
					faily2 = true;
				}




			}
		}

		if (failx1 || failx2 || faily1 || faily2) { //Vector occupied!
			return 0;
		}
		else {
			return 1; //nothing ran into
		}

	}





};