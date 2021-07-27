#pragma once
#include<string>
#include<map>
#include<SDL.h>
#include <windows.h>
#include <shlobj.h>
#include <algorithm>

// used to find where the user will be writing
std::string UserDirectory() {
	char path[MAX_PATH];
	if (SHGetFolderPathA(NULL, CSIDL_PROFILE, NULL, 0, path) != S_OK) // puts the home directory, "C:/Users/user" into the string path
	{
		printf("Window User Directory could not be retrieved.\n"); // let's the user know that their directory could not be retrieved
		return "";  // returns a null byte if the user directory cannot be retrieved.
	}
	else { // if able to get the window user directory...
		std::string temp = "/source/repos/";
		std::string path2 = path + temp; // adds "/source/repos/" to the path2

		temp.erase(); // erases the temp string

		std::replace(path2.begin(), path2.end(), '\\', '/'); // replaces all of the '\' with '/'

		return path2; // returns the path2
	}
}

//Obtains the first four lines of the file. The Header Dimension, Screen (w, h) in Coord, Tile (w, h) in pixels, and Level/Layer (w, h) in Coord. sourceIMG passed as a reference, as filestreams are non-copyable. Assumes the file will be closed in another function. 
bool ScreenTileDimension(std::ifstream& sourceIMG, std::string& line) {
	//ensures the file is openable - may be unnecessary.
	if (sourceIMG.is_open()) {
		//while loop ensures the file ends
		while (!sourceIMG.eof()) {
			getline(sourceIMG, line);
			//"Dimension" Header indicates the next two Lines should be Window Coord W, Coord H "#,#", and Tile Pixel Width, Pixel Height "#,#". 
			if (IsSameString(line.c_str(), "Dimension")) { //Insert a check that if Dimensions was never read - Throw
				// printf("Dimension found\n");
				//Obtain Both SCREEN (W, H) and TILES (W, H)
				getline(sourceIMG, line);  //Line currently holds Window Coord W, Coord H "#, #'
				SplitStringStream(line, SCREEN_WIDTH, SCREEN_HEIGHT);
				getline(sourceIMG, line);
				SplitStringStream(line, TILE_WIDTH, TILE_HEIGHT);
				getline(sourceIMG, line);
				SplitStringStream(line, LEVEL_WIDTH, LEVEL_HEIGHT);

				//Set default of window target Rect
				gFullWindowRect = new SDL_Rect();
				gFullWindowRect->x = 0;
				gFullWindowRect->y = 0;
				gFullWindowRect->w = SCREEN_WIDTH * TILE_WIDTH;
				gFullWindowRect->h = SCREEN_HEIGHT* TILE_HEIGHT;
				
				//Actually create a surface to blit onto. The 32 flag just defines pixel Depth - the amount of colors to be handled. In this case, 2^32 types.
				gHiddenSurface = SDL_CreateRGBSurface(0, LEVEL_WIDTH * TILE_WIDTH, LEVEL_HEIGHT * TILE_HEIGHT, 32, 0, 0, 0, 0);

				//If Dimension was read properly - Enable the option to find for "Tilesets" header.
				return true;
			}
			else {
				//CHANGE - the close file should still be called in FileHandler, but could be called here after compartimentalization is complete.  
				printf("Error when reading in map!\n");
				return false;
			}
		}
		return false;
	}
	else {
		printf("FILE IS UNOPENABLE");
		return false;
	}
	return false;
}
