#pragma once
#include<SDL.h>
#include "Quality_Functions.h" // needed for HexToInt() function
// Tilesets/Img sources
class SurfaceProperty {
public:
	int width;
	int height;
	int TotalTile;
	SDL_Surface* SelfSurface;
	SDL_Texture* SelfTexture;
	std::string Surname;
	std::string SourceName;
	std::string SourcePath;
	std::string TransparentPixel;
	int* collision = NULL;

	//note to self, try making TempPath a larger byte value for the storage. may solve warning C26451 (google later)
	// 
	//CHECK THAT THOSE FILES EXIST!!!!
			//https://stackoverflow.com/questions/12774207/fastest-way-to-check-if-a-file-exist-using-standard-c-c11-c

	SurfaceProperty(std::string tempName, std::string tempSource, SDL_Surface* surface, std::string TempPath, std::map<std::string, SurfaceProperty*>* SurfacePropertyMap) {
		width = surface->w;
		height = surface->h;
		TotalTile = (width / TILE_WIDTH) * (height / TILE_HEIGHT);
		collision = new int[TotalTile];
		SelfSurface = surface;
		SelfTexture = NULL; //for a warning -_-
		SourceName = tempSource;
		Surname = tempName;
		SourcePath = TempPath;
		TransparentPixel = "0xff678b"; //CHANGE will need to change / remove when get more info

		CreateTransparency(); //CHANGE - change / remove when get more info
		ConvertSelfSurfaceToSelfTexture();
		MapThis(SurfacePropertyMap);

	}

	SurfaceProperty(std::string tempName, std::string tempSource, SDL_Surface* surface, std::string TempPath, std::string Trans, std::map<std::string, SurfaceProperty*>* SurfacePropertyMap) {
		width = surface->w;
		height = surface->h;
		TotalTile = (width / TILE_WIDTH) * (height / TILE_HEIGHT);
		collision = new int[TotalTile];
		SelfSurface = surface;
		SelfTexture = NULL;  //for a warning -_-
		SourceName = tempSource;
		Surname = tempName;
		SourcePath = TempPath;
		TransparentPixel = Trans;

		CreateTransparency(); //CHANGE - change / remove when get more info
		ConvertSelfSurfaceToSelfTexture();
		MapThis(SurfacePropertyMap);

	}

	//call for surface destruction (for close(), going throuhg all in map)
	~SurfaceProperty() {
		printf("Deconstructor called for %s\n", SourcePath.c_str());
		// destroy SDL_Surface
		// may have to destroy collision here

		//SDL_FreeSurface(SelfSurface);		
		//free texture
		//delete this
		//destroy the map after all deconstructed.

		//used keyword new for all initailizations

	}

	int GetWidth() {
		return width;
	}
	int GetHeight() {
		return height;
	}
	int GetTotalTile() {
		return TotalTile;
	}
	int GetCollision(int index) {
		return collision[index];
	}
	std::string GetName() {
		return SourcePath;
	}
	std::string GetSurname() {
		return Surname;
	}
	std::string GetSourcePath() {
		return SourcePath;
	}
	SDL_Surface* GetSelfSurface() {
		return SelfSurface;
	}
	SDL_Texture* GetSelfTexture() {
		return SelfTexture;
	}
	void ConvertSelfSurfaceToSelfTexture() { // MAY NOT BE NECESSARY
		SelfTexture = SDL_CreateTextureFromSurface(gRenderer, SelfSurface);
	}

	void CreateTransparency() {
		//This function will need some change once we get more instances of transparancy. It should be user defined from the editor, or it should have a default value that skips changing any pixel values.
		//EDIT once Collision, Player, and Files pathing isfigured out.

		// std::string str = "0xff678b"; // this will need to change
		int r = HexToInt(TransparentPixel, 2); // instead of str, we will have transparent pixel
		int g = HexToInt(TransparentPixel, 4);
		int b = HexToInt(TransparentPixel, 6);
		SDL_SetColorKey(SelfSurface, SDL_TRUE, SDL_MapRGB(SelfSurface->format, r, g, b)); // 0xff678b
	}

	//call for map self
	
	void MapThis(std::map<std::string, SurfaceProperty*> *SurfacePropertyMap) {
		SurfacePropertyMap->insert(std::make_pair(Surname, this));
	}
	

	//call for hello (I exist)
	void SayHello() {
		printf("%s says hello!\n", SourcePath.c_str());
	}
};