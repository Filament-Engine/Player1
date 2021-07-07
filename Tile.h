#pragma once
#include<string>
#include<SDL.h>
#include "SurfaceProperty.h"

class Tile;
class TileHash;

class Tile {
private:
	SDL_Rect SourceTile;
	SDL_Rect TargetTile;
public:
	std::string label; // The label of the tile; something like "AA###"
	std::string IMGSource; // The label of the source image; should be something like "AA"
	int position; // The position of the tile on the source map; should be something like "1", or "12"
	int SourceX; // This is the "x" value of the tile we're taking
	int SourceY; // This is the "y" value of the tile we're taking
	int CollisionType;

	//Defined in TileHash Class, for access.
	void MapThis(TileHash* GlobalTileHash);
	Tile* GetThis();
	void BlitThis(int Targetx, int Targety, SDL_Surface*& LayerHiddenSurface, std::map<std::string, SurfaceProperty*> SurfacePropertyMap);

	//Constructor; Height and width are of source tile. Expects (std::string n, int p, int width, int height, tile width, tile height)
	Tile(std::string n, int p, int width, int height, int DefaultCollision) {

		CollisionType = DefaultCollision;
		IMGSource = n; // Sets IMGSource to input string
		position = p; // Sets position to input position
		label = IMGSource + std::to_string(position); //Gives label the equivalent "AA" portion, and the equivalent "##", such that the label is "AA##".
		int x = p; // This will be the position SourceTile is reading from -- the "##" of label


		// Use position, width, and height to determine SourceX and SourceY.
		width = width / TILE_WIDTH; // This gives us the number of tiles for x-plane
		height = height / TILE_HEIGHT; // This gives us the number of tiles for y-plane
		//Default values.
		SourceX = 0;
		SourceY = 0;

		//Determines 'position' - y=mx+b, y=position, m=width (Coord), x=SourceY, b=SourceX
		while (x >= width) {
			x = x - width;
			SourceY++; // SourceY obtains the 'row' which the position is in
		}
		SourceX = x; // makes SourceX = Position, x is the remainder by height


		//give one time values for Source Tile. Other data information are still accessible.
		SourceTile.x = SourceX * TILE_WIDTH;
		SourceTile.y = SourceY * TILE_HEIGHT;
		SourceTile.w = TILE_WIDTH;
		SourceTile.h = TILE_HEIGHT;

		//After initialized, Hash this object.
		// MapThis();
	}
	//Copy constructor. 
	Tile(Tile& copyTile) {
		CollisionType = copyTile.CollisionType;
		IMGSource = copyTile.IMGSource;
		position = copyTile.position; // Sets position to input position
		label = copyTile.label; //Gives label the equivalent "AA" portion, and the equivalent "##", such that the label is "AA##".
		SourceX = copyTile.SourceX;
		SourceY = copyTile.SourceY;

		SourceTile.x = SourceX * TILE_WIDTH;
		SourceTile.y = SourceY * TILE_HEIGHT;
		SourceTile.w = TILE_WIDTH;
		SourceTile.h = TILE_HEIGHT;

		// MapThis();
	}

	//Default Constructor - For now, it is an indicator that a Tile did not get created properly, through auto-generation mapping.
	Tile() {
		printf("WHOOPS! Default Constructor of Tile has been called.\n");
		SourceX = 16;
		SourceY = 16;
		position = 0;
		label = "AA00";
		IMGSource = "AA";
		printf("Did you intend a default Tile?\n\n\n");
	}

	~Tile() {
		//EDIT
		printf("Deconstructor called for %s\n", label.c_str());
		//check if it destroys the SDL_Rect(). 
		//If you use keyword new, then use delete;
		//if you use vectors/arrays use erase to delete it

		//DANGEROUS - delete this seems to break the code! Figure it out later!!
		//delete this;
	}

	//Checks to see if Tile exists. 
	void SayHello() {
		printf("Hi, I'm still in memory and my address is %p\n", this); //CHECK - ptr might just return 0. Might indicate a problem later.
	}

};
class TileHash { //initialized global, but HashSelf in Tile Class. Thus this should be declared after Tile in the global declaration beforehand.
public:
	std::string Key; //AA## =Tile.label;
	Tile** data; //Array/Hashtable to hold the pointer to Tiles at unique indexes.

	//Forward declarations. Undefined for now. Defiend later so that other class functions have access to them.
	void put(Tile* TargetTile);
	Tile* find(std::string label);
	long int GetInterpretation(std::string label);

	//Initialize once 
	TileHash(long int TotalTilesOfSurface, std::map<std::string, long int> OSMap) { //the pointer will be obtained from Tile.GetSelf(), which then we can ask for data memebes.
		//have exactly enough space for every tile one could make with all 'pre-loaded' Textures.
		OffSetMap = OSMap;
		data = new Tile * [TotalTilesOfSurface];
	}

	//Deconstructor
	~TileHash() {
		//EDIT - Memory management
		printf("Deconstructor for TileHash Called!\n"); //CHANGE - Add a call to deconstructor after the tile's are freed from hashtable. Still need to replace everywhere a map is used for tiles with a hash.
		// delete data;
	}
};

// Tile Functions Defined
//Maps the pointer to this particular tile, in TileHash, where it is accessible by anything through it's label ('AA##').

void Tile::MapThis(TileHash* GlobalTileHash) {
	GlobalTileHash->put(GetThis());
}
Tile* Tile::GetThis() {
	return this;
}
//Stamp this particular Tile onto the Global Window Surface. 
void Tile::BlitThis(int Targetx, int Targety, SDL_Surface*& LayerHiddenSurface, std::map<std::string, SurfaceProperty*> SurfacePropertyMap) {
	TargetTile.x = Targetx * TILE_WIDTH;
	TargetTile.y = Targety * TILE_HEIGHT;
	TargetTile.w = TILE_WIDTH;
	TargetTile.h = TILE_HEIGHT;
	SDL_BlitSurface(SurfacePropertyMap[IMGSource]->GetSelfSurface(), &SourceTile, LayerHiddenSurface, &TargetTile);
}

// TileHash Functions Defined
//Place every given tile into the HashTable. Use Interpret for initial placement
void TileHash::put(Tile* TargetTile) {
	Key = TargetTile->label; //called through Tile Mapthis, or rather, hash this. 
	data[GetInterpretation(TargetTile->label)] = TargetTile->GetThis();
}
//Return the object's pointer when given a hashkey/key "AA##"
Tile* TileHash::find(std::string label) {
	//interpret a string
	// printf("Interpreting String\n");
	return data[GetInterpretation(label)];
}
//Used for initial obtainment of index, and to find and help return the Tile for a given label
long int TileHash::GetInterpretation(std::string label) {
	//label will have "surname AA.."+"##", surname is a constant so we'll use that as reference
	//will use split string, atoi, 
	std::string TileSurname;
	std::string Position;
	TileSurname = label.substr(0, SurnameLength);
	Position = label.substr(SurnameLength, label.size()); //size might count nullbyte. We'll see
	//so this map will simply be created in global, then added to by surface creation. In sself map basically.
	return OffSetMap[TileSurname] + std::stoi(Position);
}