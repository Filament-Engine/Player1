#pragma once
//Assumes the file will be closed in another function. 
bool SurfaceCreation(std::ifstream& sourceIMG, std::string& line, long int& TotalTilesOfSurface, std::map<std::string, SurfaceProperty*>* SurfacePropertyMap, TileHash** GlobalTileHash) {
	int counter = 0;
	//Ensures the Filestream is open
	if (sourceIMG.is_open()) {

		getline(sourceIMG, line); //Line holds the first Image.format,Surname - Example: Bitmap.bmp,AA. 

		//For Every following line, until Tiles is found. 
		while (!IsSameString(line.c_str(), "Collision")) { // go through txt file until you reach "collision"

			//INSERT - check If Image.format,Surname

			//Obtain the Image.format String
			std::string tempSource = line.substr(0, line.length() - (SurnameLength + 1));

			//Obtain the Image.format's Surname.
			std::string tempName = line.substr(line.length() - SurnameLength, line.length());

			//These steps are necessary to use IMG_Load.

			//CHANGE - these variable names
			std::string TempPath2 = UserDirectory();
			char* TempPath = StringAndStringToCharArr(TempPath2, tempSource);
			//Create new surface with expected file location
			new SurfaceProperty(tempName, tempSource, IMG_Load(TempPath), TempPath, &*SurfacePropertyMap);

			SurfacePropertyEnum.insert(std::make_pair(counter, tempName));

			//Grab the next the img file, and the 'label'. Or "Tiles" header.
			getline(sourceIMG, line);
			counter++;
		}
		//Generate OffSetMap NEW
		TotalTilesOfSurface = GenerateOffSetMap(&*SurfacePropertyMap);
		*GlobalTileHash = new TileHash(TotalTilesOfSurface, OffSetMap); //gotta be global for access purposes. Again, we'd have to pass ref all the way back to main eventually. HUGE pain though.
		return true;
	}
	else {
		printf("FILE UNOPENABLE (Surface Creation)\n");
		return false;
	}
	return false;
}