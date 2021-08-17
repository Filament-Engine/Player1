#pragma once

bool CollisionCreation(std::ifstream& sourceIMG, std::string& line, std::map<std::string, SurfaceProperty*> SurfacePropertyMap) {
	// these ar evariables for the loop
	int i;
	int j; // this is the variable that corresponds to the total amount of collision data in a layer
	int k;
	int d; // this will be the integer we read in for s2.
	int counter = 0; // creates a counter
	int TotalExpected;


	std::string s1; // this takes the full line
	std::string* s2; // this is the part of the line we want to be reading at any given moment

	//Ensure the Filestream is open
	if (sourceIMG.is_open()) {

		getline(sourceIMG, line); //Line holds the first Image.format,Surname - Example: Bitmap.bmp,AA.
		//For Every following line, until Tiles is found. 
		while (!IsSameString(line.c_str(), "Tiles") && !sourceIMG.eof()) { // go through the txt file until you reach "Tiles"
			
			// grab the first element of the SurfacePropertyMap (the png in this case)
			s1 = line;
			s2 = new std::string[4]; // (4, '\0');  // (2 characters).

			i = 0;
			j = 0; // this is the variable that corresponds to the total amount of collision data in a layer
			k = 0;

			//k is the number of elements read so far
			//i is the length of s2, reset each time
			//j is the position in s1, our got line (0,0,0,0,01,1,1,10,0,0 etc]

			//If there is to much counter throw
			if (counter < SurfacePropertyMap.size()) { //it's alright if it is < since we started enum at 0. 
				
				TotalExpected = SurfacePropertyMap[SurfacePropertyEnum[counter]]->TotalTile;

				//INSERT destructor
				int* TempCollisionArr = new int[TotalExpected];



				while (s1[j] != '\0') { // here we read the entirety of the line
					while (s1[j] != ',') {
						s2[i] = s1[j];
						i++;
						j++;
					}

					//Recast s2 as an integer, store it in the array

					d = 0;

					//i is the size of the string, s2


					for (int l = 0; l < 4; l++) { // here we read in the string as an integer
						if (s2[l] != "\0") {

							d += std::stoi(s2[l]) * (std::pow(10, ((i - 1) - l)));

							s2[l] = "\0";
						}
					}

					if (k >= TotalExpected) { // checks to see if there are more values read than expected
						printf("YOU READ TO MANY COLLISION DATA FOR THE AMOUNT OF TILES YOUR ASSIGNING TOO\n");
						return false;
					}
					TempCollisionArr[k] = d;
					SurfacePropertyMap[SurfacePropertyEnum[counter]]->collision[k] = d;

					//iterates forward position
					k++;
					//resets key
					i = 0;
					//iterates while loop
					j++;

				}
				if (SurfacePropertyMap[SurfacePropertyEnum[counter]]->TotalTile > k) { // if we've reached the end and there are less values read than expected
					printf("NOT ALL TILES IN SURFACE %s IS GIVEN A DEFAULT COLLISION. TRY:\n", SurfacePropertyEnum[counter].c_str());
					for (int a = 0; a < TotalExpected; a++) {
						printf("0,");
					}
					printf("\n");
					return false;
				}

				//release memory
				delete TempCollisionArr;

				// gets the next line to see if we can continue or if we stop
				getline(sourceIMG, line);
				counter++; // iterates the counter
			}

			else { //if this triggers, you have too high a counter, more collision data than surfaces to give them to.
				printf("YOU HAVE MORE COLLISION DEFAULTS THAN SURFACES TO APPLY THEM.\n");
				return false;
			}
		}
		if (IsSameString(line.c_str(), "Tiles")) {
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

// this is a function that reads in the "OverridCollision" part of the map and then overrides any part of the collision where there is data
void OverrideCollision(std::ifstream& sourceIMG, std::string& line, Level* level) {
	if (sourceIMG.is_open()) {

		std::string s1; // these should be declared out of the while loop
		std::string* s2; // should be declared out of the while loop

		getline(sourceIMG, line); //Line holds the first Image.format,Surname - Example: Bitmap.bmp,AA.
		

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
