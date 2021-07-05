#pragma once

bool CollisionCreation(std::ifstream& sourceIMG, std::string& line, std::map<std::string, SurfaceProperty*> SurfacePropertyMap) {
	//for all globals that aren't constant, we'll be passing references through where they are needed, then storing in main. TotalTilesOfSurface is one example.
	// printf("Tilesets found\n");


	int i;
	int j; // this is the variable that corresponds to the total amount of collision data in a layer
	int k;
	int d; // this will be the integer we read in for s2.
	int counter = 0; // creates a counter
	int TotalExpected;


	std::string s1; // these should be declared out of the while loop
	std::string* s2; // should be declared out of the while loop


	//Ensure the Filestream is open
	if (sourceIMG.is_open()) {

		getline(sourceIMG, line); //Line holds the first Image.format,Surname - Example: Bitmap.bmp,AA.
		//For Every following line, until Tiles is found. 
		while (!IsSameString(line.c_str(), "Tiles") && !sourceIMG.eof()) { // go through the txt file until you reach "Tiles"
			printf("finding tile header... \n");

			// grab the first element of the SurfacePropertyMap (the png in this case)
			// make an int array = new int [SurfacePropertyMap["AA"]->w * SurfacePropertyMap["AA"]->h] 
			// printf("line is %s\n", line.c_str());
			s1 = line;
			// printf("s1 is %s\n", s1.c_str());
			s2 = new std::string[4]; // (4, '\0');  // (2 characters).

			i = 0;
			j = 0; // this is the variable that corresponds to the total amount of collision data in a layer
			k = 0;

			//If there is to much counter throw
			if (counter < SurfacePropertyMap.size()) { //it's alright if it is < since we started enum at 0. 
				// printf("%s is Enum[counter]\n", SurfacePropertyEnum[counter].c_str());
				TotalExpected = SurfacePropertyMap[SurfacePropertyEnum[counter]]->TotalTile;

				//	= new int[TotalExpected];
				// printf("Total Expected it %d\n", TotalExpected);
				// printf("counter is %d\n", counter);
				//printf("TOTAL EXPECTED IS %d\n", TotalExpected); //checkto see if width and height are stored as pixels or tiles
				//INSERT destructor
				int* TempCollisionArr = new int[TotalExpected];
				// printf("TempCollisionArr array made with %d total \n", TotalExpected);
				//if this throws an exceptoin, violation error it means the information are inaccessible in the map for some reason other than going off the map.



				while (s1[j] != '\0') {
					while (s1[j] != ',') {
						s2[i] = s1[j];
						i++;
						j++;
					}

					//Recast s2 as an integer, store it in the array

					d = 0;

					//i is the size of the string! s2. THUS


					for (int l = 0; l < 4; l++) {
						if (s2[l] != "\0") {

							d += std::stoi(s2[l]) * (std::pow(10, ((i - 1) - l)));

							s2[l] = "\0";
						}
					}

					if (k > TotalExpected) { //CHECK - it might also be if they are equal
						printf("YOU READ TO MANY COLLISION DATA FOR THE AMOUNT OF TILES YOUR ASSIGNING TOO\n");
						return false;
					}
					TempCollisionArr[k] = d;
					SurfacePropertyMap[SurfacePropertyEnum[counter]]->collision[k] = d;

					if (d != 0) { //reduces spam.
						// printf("%d placed into TempCollsion, which then is %d, CHECK - %d is at index %d\n \n", d, TempCollisionArr[k], SurfacePropertyMap[SurfacePropertyEnum[counter]]->collision[k], k);
					}

					//make a check that if there are MORE elements expected - throw ("Wrong layer collision data read!!")
					//k is the number of elements read so far
					//i is the length of s2, reset each time
					//j is the position in s1, our got line (0,0,0,0,01,1,1,10,0,0 etc]

					//iterates forward position
					k++;
					//resets key
					i = 0;
					//iterates while loop
					j++;

				}
				if (SurfacePropertyMap[SurfacePropertyEnum[counter]]->TotalTile > k) {
					printf("NOT ALL TILES IN SURFACE %s IS GIVEN A DEFAULT COLLISION. TRY:\n", SurfacePropertyEnum[counter].c_str());
					for (int a = 0; a < TotalExpected; a++) {
						printf("0,");
					}
					printf("\n");
					return false;
				}
				//Before you grab the NEXt line, store the entire array inside that surface property's array of collision data
				//Eventually we'll skip this middle man array and go directly to surface property expected, but for now seperate for bug testing.


				//Grab the next the img file, and the 'label'. Or "Tiles" header.
					//check to see if you have more room to grow

				//release memory - CHECK V
				printf("Released Temp Collision Arr -scalar delete is because it moves out of the function, and gets freed anyways I believe\n");
				delete TempCollisionArr;


				getline(sourceIMG, line);
				counter++; // iterates the counter
			}

			else { //if this triggers, you have to high a counter, more ocllision data than surfaces to give them to.
				printf("YOU HAVE MORE COLLISION DEFAULTS THAN SURFACES TO APPLY THEM.\n");
				return false;
			}
		}
		if (IsSameString(line.c_str(), "Tiles")) {
			printf("Found tile header\n");
			return true;
		}
		else if (sourceIMG.eof()) {
			printf("Never found tile header!\n");
			return false;
		}
	}
	else {
		printf("FILE UNOPENABLE (Surface Creation)\n");
		return false;
	}
	return false;
}

void OverrideCollision(std::ifstream& sourceIMG, std::string& line, Level* level) {
	if (sourceIMG.is_open()) {

		std::string s1; // these should be declared out of the while loop
		std::string* s2; // should be declared out of the while loop

		getline(sourceIMG, line); //Line holds the first Image.format,Surname - Example: Bitmap.bmp,AA.
		// printf("line is %s\n", line.c_str());

		int i = 0;
		int j = 0;
		int k = 0;
		int y = 0; // y position
		int x = LEVEL_WIDTH; // x position
		int temp;
		int d; // the integer we will use to read in collision into CollisionOverride
		s1 = line;
		s2 = new std::string[4];
		int TotalExpected = LEVEL_WIDTH * LEVEL_HEIGHT;

		while (s1[j] != '\0') {
			d = -1;
			while (s1[j] != ',') {
				s2[i] = s1[j];
				i++;
				j++;
				if (d == -1) { d++; } // makes it so we add 1, this way, when it's something like 0, we get 0 as opposed to -1
			}


			for (int l = 0; l < 4; l++) { // this is a loop to handle integers that have a length greater than 1!
				if (s2[l] != "\0") {

					d += std::stoi(s2[l]) * (std::pow(10, ((i - 1) - l)));

					s2[l] = "\0";
				}
			}

			//printf("%d ", d);


			temp = k; // using the k value to find x and y positions
			while (temp >= LEVEL_WIDTH) {
				y++;
				temp -= LEVEL_WIDTH;
			}
			x = temp;


			level->CollisionOverride[y][x] = d;



			i = 0;
			j++;
			k++;
			x = 0;
			y = 0;

		}
	}
}
