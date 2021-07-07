#pragma once
// generates all of the tiles
void GenerateTiles(std::map<std::string, SurfaceProperty*> SurfacePropertyMap, TileHash* GlobalTileHash) {
	//GENERATE ALL TILES FOR ALL PATH/IMAGE.FORMAT MAPPED.  
	int SurfaceWidth;
	int SurfaceHeight;
	int XCordTotal;
	int YCordTotal;
	int TotalCord;
	for (auto p : SurfacePropertyMap) {
		SurfaceWidth = SurfacePropertyMap[p.first]->GetWidth();
		SurfaceHeight = SurfacePropertyMap[p.first]->GetHeight();
		XCordTotal = SurfaceWidth / TILE_WIDTH;
		YCordTotal = SurfaceHeight / TILE_HEIGHT;
		TotalCord = XCordTotal * YCordTotal;
		//INSERT memory management
		//DELETED the array that took total amount of tiles expected and stored them. Instead I realized we are mapping inside the classes
		Tile** TotalTile = new Tile * [TotalCord];
		for (int j = 0; j < TotalCord; j++) {
			TotalTile[j] = new Tile(p.first, j, SurfaceWidth, SurfaceHeight, SurfacePropertyMap[p.first]->GetCollision(j)); // p.first is the "AA", j is the coordinate, ###, SourceX, SourceY
			TotalTile[j]->MapThis(GlobalTileHash);
		}
	}

	//NEW - Placed here as now HiddenSurface should have all the tiles of a level. In the future we may make HiddenTexture a class to clear but for now this will do.

}

//THIS is where layers will be created, it reads in the save data, passes this string array to a layer, 
// the layer then uses this information to find both the 'parent surface' for collision and constructs dynamically it's own matrix for collision informaiton
// the layer also makes a secondary array (which we may not use) with copy constructed tiles (which have the collision data so maybe just make this one first)
// The Layer then has 5 things 1)Tile Array, 2) Collision Matrix, 3)Tile Matrix (copy constructed), 4)Surface which they were blited to, 5)texture saved
// The Layer should have a mapthis() function to put into either a level (likely) or a map (unlikely)
//This should be improved.
bool DrawSavedTiles(std::ifstream& sourceIMG, std::string& line, std::map<std::string, SurfaceProperty*> SurfacePropertyMap, Level* level, TileHash* GlobalTileHash) {
	printf("working now\n");
	int TotalExpected = LEVEL_HEIGHT * LEVEL_WIDTH;
	std::string** savedTiles = new std::string * [TotalExpected];
	char temp = 'a';
	int counter = 0;


	if (sourceIMG.is_open()) {
		getline(sourceIMG, line);
		while (!IsSameString(line.c_str(), "Collision Override") && !sourceIMG.eof()) {
			//NEW - holds every string we have found thus far



			// printf("Running tiles now - each time you see this message, expect another layer\n");

			//Insert - Make seperate function

			//s1 Holds total String from Line
			std::string s1 = line;
			//CHANGE - s2 Holds a string, Tile Label, of allocated length equal to s1. This is more than the space used ,and likely we can figure out the length divided by total possible tiles on the screen. 
			std::string s2(s1.size(), '\0');
			//i is the current position of s2.
			int i = 0;
			//j is the current position of s1.
			int j = 0;
			//Position of the Target Tile
			int k = 0;


			//reads the entire string, finds the key each time. //ERROR - reading incorrectly in 5x5 with 25 tiles.
			while (s1[j] != '\0') {
				while (s1[j] != ',') {
					//INSERT a check to say if eof is reached/s1[j]=\0, your missing stuff.
					s2[i] = s1[j];
					i++;
					j++;
				}

				//if it s a comma, just null, if not it's a proper label.
				s2[i] = '\0';
				temp = s2[0];
				//std::cout << temp << " IS OUR 0th index of S2!!!!!!!\n";
				//Check that s2 indeed should hold a Tile Label


				//transfer to player (Don't take k out of here^V, but instead make another k back in layer.
				if (temp != '\0') {

					//Figure out Target Position. See y=mx+b within Tile Class for Logic.
					int x = k;
					int TargetX;
					int TargetY = 0;
					while (x >= LEVEL_WIDTH) {
						x = x - LEVEL_WIDTH;
						TargetY++;  // adds 1 to the TargetY
					}
					TargetX = x;

					//Use the key - if it is found - and blit it.
					//INSERT - check if s2.c_str IS IN THE MAP. If not, throw.

					//add to array s2--- instead of global hash

					//GlobalTileHash->find(s2)->BlitThis(TargetX, TargetY);
				}

				if (k < TotalExpected) {
					//printf("%d = %s\n", k, s2.c_str());
					//now place s2 into the savedTiles array

					//i holds the actual size of s2... I think.

					if (temp != '\0') {
						//printf("Adding %s to the savedTiles\n", s2);
						// printf(".");
						savedTiles[k] = new std::string(s2);

					}
					else {
						//delete savedTiles[k];
						savedTiles[k] = new std::string("");
						//savedTiles[k] = new std::string(1, '\0');
					}


					// std::cout << " 2, = " << *savedTiles[k] << std::endl;
					//now print savedTiles array Stored information

				}



				//iterates forward position
				k++;
				//resets key
				i = 0;
				//iterates while loop
				j++;
			}

			//pushback -insert default to the end
			level->RenderOrder.push_back(new Layer(savedTiles, GlobalTileHash, SurfacePropertyMap));
			level->NumLayers++;
			//Insert is usually reserved for when you want more control over the position of objects. LEAVE HERE - for reading multiple files may want to use this.
			// gLevel1->RenderOrder.insert(gLevel1->RenderOrder.end(), new Layer(savedTiles));


			//Now that all tiles have been read, create a texture from the undisplayed surface. 

			//CHANGE - default for now, will overwrite with level class I think
			//gHiddenTexture = SDL_CreateTextureFromSurface(gRenderer, gHiddenSurface);
			//INSERT - Clear hidden surface here?
			//printf("%d\n", counter);
			//Now make a layer before savedTiles is overwritten.



			//INSERT - a way to check that there are equal collision data for each layer. Requries editing collision functino (compare against this counter at end of function before returning true.

			if (k == TotalExpected) {
				// printf("All Level Tiles are found for this layer : %d\n", counter);
			}
			else { //INSERT - check comes to late. See while loop.
				printf("You are missing %d commas/labels at layer : %d\n", TotalExpected - k, counter);
				return false;
			}

			counter++;
			getline(sourceIMG, line); //Should hold information of tiles, going left to right, top to bottom, as  AA##,,BB##,CB#, etc. Each comma before a given label indicates the position. Example, AA## position is 0.


		}

		if (IsSameString(line.c_str(), "Collision Override")) {
			// printf("Found Collision Override header\n");
			return true;
		}
		else if (sourceIMG.eof()) {
			printf("Never found Collision Override header!\n");
			return false;
		}

		/*if (sourceIMG.eof()) {
			printf("eof reached\n");
			return false;
		}*/
		return false;

	}
	else {
		return false;
	}
	return false; //for warning
}
