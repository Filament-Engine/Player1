//Using SDL and all include statements
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <fstream> //https://www.cplusplus.com/reference/fstream/fstream/
#include <string> //http://www.cplusplus.com/reference/string/string/
#include <map> //https://www.cplusplus.com/reference/map/map/
#include <sstream> //used to convert strings to int, but may be better manually doing so.
#include <vector> //used to dynamically grow SurfaceSource memory. May remove if we can itterate through the map keys in a seperate function.
#include <cmath>
//for windows file pathing
#include <windows.h>
#include <shlobj.h>
#include <algorithm>

//temp for testing
#include<iostream>

//TO DO 
	//Player Class
	//Collision
	//Json +Dummy files
	//Repo for multiple levels/maps
	//Memory management
	//CreateTransparancy Edit

//change maps to combine like features into a single function, so that the map grabs data members (reduces the amount of maps)



//Introduce Hash table - convert hte string key read to a 4 digit 'pin'. Perhaps we'll convert all map 'surnames' also to pins in this vein. Well it wouldn't be just 4 digits then, it could possibly be more.... This is troubling. the digit of number is determinate by the dimensions squared, and then the surname (assume 2) could be 4 digits. So maybe 4 digit surname, and then the rest is as usual. Since that should be enough to differentiate keys?
//Meta Data^ Link.


// NEXT PHASE
//Start work on transparancy, and multi layer reading. - make a check so that if one layer ends early, you can still find the proper position, and then reset for the next potential layer. (Just helps end early if lets say, only the upperh alf of the screen is being used for a layer.


const bool gEnableDelay = false;


// fps constants
const int MAX_FPS = 60; // this is the maximum amount of fps we have
const int SCREEN_TICKS_PER_FRAME = 1000 / MAX_FPS; // this converts the fps to ticks

const int SurnameLength = 2;

//Level constant (total tiles in level)
int LEVEL_WIDTH;
int LEVEL_HEIGHT;

//Screen dimension constants - should just be our window size for the most part. (Total tiles in window)
int SCREEN_WIDTH;
int SCREEN_HEIGHT;



//Tile Constants (w,h, total, types)
int TILE_WIDTH;
int TILE_HEIGHT;

//From SurfaceMap 
const long int TotalTileOfAllSurfaces = 0;



//Map handles the Offset Tile Total of Surfaces. Prevents having to do forward then backward itteration through a map. 
std::map<std::string, long int> OffSetMap;

//Class Holds information pertinent to the Surface/Img properties. Dimensions, Texture, Transparancy, etc.
class SurfaceProperty;
//Map for traversing all Loaded images.
std::map<std::string, SurfaceProperty*> SurfacePropertyMap;
// TEMP -- temporary solution
std::map<int, std::string> SurfacePropertyEnum; // the numbers that correspond to creation order, where lower numbers are created first and higher numbers later

//Forward Declaration, class for the tiles, and obtain size of Tile before making the Tile Map. Expects (std::string n, int p, int width, int height). Naming Convention "AA##" ensures nothing repeated twice, also named with position ## from 0-TileMax Left to Right, to to bottom.
class Tile;

//Forward Declaration of TileHash, a class initialized once to hold the hash data of all Tiles generated through all Images. 
class TileHash;

//Initialize a HashTable for future use.
TileHash* GlobalTileHash; //INSERT - we also need all globals that are not const to be written to a 'Save properties' folder/document. This would be later, so on load up, we'd read in those constants perhaps... but I'm unsure hwo exactly it works.

class Timer;

class Player;

class Layer;

class Level;

//Free's Loaded Surfaces of a Map File, for all Surfaces in SurfaceSource Map. Called during close.
void FreeMapSurfaces();

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

// creates a player called player1
void CreatePlayer();

//Frees media and shuts down SDL
void close();

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The surface contained by the window
SDL_Surface* gScreenSurface = NULL;

//Hidden Surface is what loaded tiles are blited too, in order to bring down animation time
SDL_Surface* gHiddenSurface = NULL;
//Hidden surface is converted to a Texture, which will be either fully or partially displayed to the window.
SDL_Texture* gHiddenTexture = NULL;
//This Global is set to the size of the window loaded in by size of tiles, but if we were to do screen resizing we would edit this variable.
SDL_Rect* gFullWindowRect = NULL;
//Part of HiddenTexture we wish to display at any given time. Moving the x,y coordinate of the SDL_Rect Object.
SDL_Rect* gCamera = NULL;
//SDL_Renderer - we will be rendering using the GPU using this renderer.
SDL_Renderer* gRenderer = NULL;

Player* Player1;

Level* gLevel1;

//QUALITY Functions - Able to be used independent of context for a purpose. 

	//Takes a String and String and returns a char* with elements of both, the size of both, null terminated.
char* StringAndStringToCharArr(std::string& TempPath2, std::string& tempSource);

//Compares two strings. Expects (string CompareThis, string ComparedTo). Returns True if string's are the same.
bool IsSameString(std::string Question, std::string Answer);

//Expects "#x,#y", where #x, #y are coordinates like "3,4", and will return #x and #y to two given global values
void SplitStringStream(std::string& line, int& GlobalWidth, int& GlobalHeight);


//LOAD DISPLAY Functions - Handles reading a given save file - Splitting up the information into components - Displaying information based on those components quickly.
void GetDimension(std::string MapRepo, long int& TotalTileSurfaces);

//Grabs the first four 'meaningful' lines of the file -Dimension header - window size (Coord), Tile Dimensions (pixel), Level/Layer size (Coord).
bool ScreenTileDimension(std::ifstream& sourceIMG, std::string& line);

//Grabs the next 'set' of valuable lines - 'Tilesets' header (perhaps grabbed in the function before), then all textures/surfaces for Tile sources.
bool SurfaceCreation(std::ifstream& sourceIMG, std::string& line, long int& TotalTilesOfSurface);

//After surfaceProperties are set up, this function keeps track of the 'total' tile locations, so that the TileHash would work
long int GenerateOffSetMap();

//Grabs the next 'set' of valuable informaiton - Tile's header, and each tile layer. - Tiles Hash themselves.
void GenerateTiles();

//After Tiles are generated, then we draw them, convert the surface drawn as a texture, and from then on use that texture - as it's cheaper and more efficent than bliting.
bool DrawSavedTiles(std::ifstream& sourceIMG, std::string& line);



//Scrolling technique for infinite scroll for a direction
int handleXYBuffer(int vPos, int vBuff, int vVec);

//Scrolling technique for a scroll limited by the Level size
	//Handles the 0-zxis for either x or y.
int handleAxisStop(int vPos, int vVec);

//Handles the Buffer-axis for either x or y.
int handleBuffStop(int vPos, int vVec, int vBuff);


//Scrolling/wsda handles - Requires at least one scrolling technique to be choosen. If it works, but scrolling is done incorrectly, you will observe black sections where the texture has no morei nformation to display.
void handleLoop();

// converts a hexadecimal value to an integer; necessary for reading the rgb values of transparency
int hexToInt(std::string str, int start);

//////////////////////Defined Classes/Functions/////////////////////////////////////////////////////////////////////////

//  a class that can be used for fps
class Timer {
private:
	Uint32 mStartTicks; // the clock time when the timer stared
	bool mStarted; // if the timer has started
public:
	// constructor for the timer class
	Timer() {
		mStartTicks = 0;
		mStarted = false;
	}

	// starts counting
	void start() {
		mStarted = true; // sets the bool for started as true
		mStartTicks = SDL_GetTicks(); // gets the number of ticks for start ticks
	}

	// stops counting
	void stop() {
		mStarted = false; // stops the timer 

		mStartTicks = 0; // resets mStartTicks
	}

	// gets the time
	Uint32 getTicks() {
		//The actual timer time
		Uint32 time = 0;

		//If the timer is running
		if (mStarted)
		{
			//Return the current time minus the start time
			time = SDL_GetTicks() - mStartTicks;
		}

		return time;
	}
};

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

	SurfaceProperty(std::string tempName, std::string tempSource, SDL_Surface* surface, std::string TempPath) {
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
		MapThis();

	}

	SurfaceProperty(std::string tempName, std::string tempSource, SDL_Surface* surface, std::string TempPath, std::string Trans) {
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
		MapThis();

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
	void ConvertSelfSurfaceToSelfTexture() {
		SelfTexture = SDL_CreateTextureFromSurface(gRenderer, SelfSurface);
	}

	void CreateTransparency() {
		//This function will need some change once we get more instances of transparancy. It should be user defined from the editor, or it should have a default value that skips changing any pixel values.
		//EDIT once Collision, Player, and Files pathing isfigured out.

		// std::string str = "0xff678b"; // this will need to change
		int r = hexToInt(TransparentPixel, 2); // instead of str, we will have transparent pixel
		int g = hexToInt(TransparentPixel, 4);
		int b = hexToInt(TransparentPixel, 6);
		SDL_SetColorKey(SelfSurface, SDL_TRUE, SDL_MapRGB(SelfSurface->format, r, g, b)); // 0xff678b
	}

	//call for map self
	void MapThis() {
		SurfacePropertyMap.insert(std::make_pair(Surname, this));
	}

	//call for hello (I exist)
	void SayHello() {
		printf("%s says hello!\n", SourcePath.c_str());
	}
};

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
	void MapThis();
	Tile* GetThis();
	void BlitThis(int Targetx, int Targety, SDL_Surface*& LayerHiddenSurface);

	//Constructor; Height and width are of source tile. Expects (std::string n, int p, int width, int height)
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
		MapThis();
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

		MapThis();
	}

	//Default Constructor - For now, it is an indicator that a Tile did not get created properly, through auto-generation mapping.
	Tile() {
		printf("WHOOPS! Default Constructor of Tile has been called.\n");
		SourceX = TILE_WIDTH;
		SourceY = TILE_HEIGHT;
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
	TileHash(long int TotalTilesOfSurface) { //the pointer will be obtained from Tile.GetSelf(), which then we can ask for data memebes.
		//have exactly enough space for every tile one could make with all 'pre-loaded' Textures.
		data = new Tile * [TotalTilesOfSurface];
	}

	//Deconstructor
	~TileHash() {
		//EDIT - Memory management
		printf("Deconstructor for TileHash Called!\n"); //CHANGE - Add a call to deconstructor after the tile's are freed from hashtable. Still need to replace everywhere a map is used for tiles with a hash.
		//delete data;
	}
};

// Tile Functions Defined
	//Maps the pointer to this particular tile, in TileHash, where it is accessible by anything through it's label ('AA##').
void Tile::MapThis() {
	GlobalTileHash->put(GetThis()); // error here
}
Tile* Tile::GetThis() {
	return this;
}
//Stamp this particular Tile onto the Global Window Surface. 


void Tile::BlitThis(int Targetx, int Targety, SDL_Surface*& LayerHiddenSurface) {
	TargetTile.x = Targetx * TILE_WIDTH;
	TargetTile.y = Targety * TILE_HEIGHT;
	TargetTile.w = TILE_WIDTH;
	TargetTile.h = TILE_WIDTH;
	//Comment out ScreenSurface blit
	//SDL_BlitSurface(SurfacePropertyMap[IMGSource]->GetSelfSurface(), &SourceTile, gScreenSurface, &TargetTile); //gScreenSurface is surface of our window.
	SDL_BlitSurface(SurfacePropertyMap[IMGSource]->GetSelfSurface(), &SourceTile, LayerHiddenSurface, &TargetTile); //not displayed at this time.
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

//collision baseed on tiles makes collision before it hits a wall. 'blocked mysteriously'. 
//Collision shouldn't be inherited.
//Pixel collision - might use vector of three values, maybe 4 for orientation. 
//Player collision could be based on user defined height/width to avoid the probelms?
//the movement still based on the upper corner of the tile, but the collision based on the collision box (they are not equivalent).


class Layer {
public:
	SDL_Surface* SelfHiddenSurface;
	SDL_Texture* SelfHiddenTexture;
	int* CollisionData;
	std::string** DrawnTiles;
	int** Arr;

	Layer(std::string* DrawnTilesRead[]) {
		//if they end up being stored on seperate files, just assign a null to ensure all variables have something and not garbage.

		// printf("Layer Started\n");
		AddTiles(DrawnTilesRead);
		// printf("Tiles Added to Layer Successfully\n");
		CollisionData = new int[LEVEL_HEIGHT * LEVEL_WIDTH]; //Every layer should have data for every position 
		AddCollision();
		SelfHiddenSurface = SDL_CreateRGBSurface(0, LEVEL_WIDTH * TILE_WIDTH, LEVEL_HEIGHT * TILE_HEIGHT, 32, 0, 0, 0, 0);
		SelfHiddenTexture = NULL;
		CreateTransparency("0x000000"); // takes the black background and makes it transparent 
		// printf("Texture and Surface defaults made!\n");
		BlitMatrixLayer();
		MakeSelfTexture();

		//after addcollision and add tiles are done, matrices are made
		//blit this for all tiles in the DrawnTiles std::string** same way we used to through tilemap
		// 
		// Call Blit this AFTER all layers have been read and stored. Make it a seperate part of GetDimension
		// 
		//Turn that selfSurface into a selfTexture


	}

	Layer(int CollisionRead[], std::string* DrawnTilesRead[]) { //if we had both info available for some reason.
		//if they end up being stored on seperate files, just assign a null to ensure all variables have something and not garbage.
		CollisionData = CollisionRead;
		AddTiles(DrawnTilesRead);
		SelfHiddenSurface = SDL_CreateRGBSurface(0, LEVEL_WIDTH * TILE_WIDTH, LEVEL_HEIGHT * TILE_HEIGHT, 32, 0, 0, 0, 0);
		CreateTransparency("0x000000"); // takes the black background and makes it transparent 
		//AddCollision(CollisionRead);
		BlitMatrixLayer();
		MakeSelfTexture();

	}

	~Layer() {
		printf("deconstructor for layer called\n");
	}

	// Makes a pixel transparent based on the hex transpcolor you pass into it.
	void CreateTransparency(std::string TranspColor) {
		int r = hexToInt(TranspColor, 2); // instead of str, we will have transparent pixel
		int g = hexToInt(TranspColor, 4);
		int b = hexToInt(TranspColor, 6);
		SDL_SetColorKey(SelfHiddenSurface, SDL_TRUE, SDL_MapRGB(SelfHiddenSurface->format, r, g, b)); // taking the black background (0x000000) and making it transparent
	}

	void AddCollision() {

		//Use the drawnTilesRead to find the pointers to the proper tile through TileHash (THIS REQUIRES A NEW MEMBER std::string*** DrawnTiles Matrix
		//two arrays one with just collision data, the other copy constructed tiles 
		//make sure the array looks like int ** = new int [height] //requires new member int ** CollisionDataMatrix
		//each pointer in that pointer pointer array has =new int [width]


		for (int i = 0; i < LEVEL_WIDTH * LEVEL_HEIGHT; i++) {
			if (0 == DrawnTiles[i]->compare("")) { //AA##, or "" empty string (\0)
				CollisionData[i] = 0; //2 is reserved for the 'no tile' information. This could then be dynamicallys tated to be collision or none in the override stage.
			}
			else {
				//If there exists a tile at that position, grab the default collision for that tile.
				CollisionData[i] = GlobalTileHash->find(*DrawnTiles[i])->CollisionType;
			}

		}
		// printf("Collision properly read for the Layer\n");
	}
	void AddTiles(std::string* DrawnTilesRead[]) {
		DrawnTiles = new std::string * [(LEVEL_WIDTH * LEVEL_HEIGHT)];
		for (int i = 0; i < (LEVEL_WIDTH * LEVEL_HEIGHT); i++) {
			if (0 == DrawnTilesRead[i]->compare("")) {
				// printf("Empty Tile Read? You Sure?\n");
			}
			DrawnTiles[i] = DrawnTilesRead[i];
		}
	}

	void BlitMatrixLayer() {

		// printf("going through Blit Layer\n");
		Arr = new int* [LEVEL_HEIGHT];
		int pos = 0;
		for (int p = 0; p < LEVEL_HEIGHT; p++) {
			Arr[p] = new int[LEVEL_WIDTH];
			for (int i = 0; i < LEVEL_WIDTH; i++) {

				if (0 == DrawnTiles[pos]->compare("\0")) {
					Arr[p][i] = CollisionData[pos]; //2 is reserved for the 'no tile' information. This could then be dynamicallys tated to be collision or none in the override stage.
				}
				else {
					Arr[p][i] = CollisionData[pos];
					GlobalTileHash->find(*DrawnTiles[pos])->BlitThis(i, p, SelfHiddenSurface); //Theres actually a tile to blit
				}
				pos += 1;
			}
		}

		//make a texture

	}

	void MakeSelfTexture() {
		SelfHiddenTexture = SDL_CreateTextureFromSurface(gRenderer, SelfHiddenSurface);
	}
	void MapThis() {
		//This isn't really a 'map' this, but it should take a global amt of it's layer #, and then add it to a level class
		//this level class then at the end of gathering all collision data and graphic data should handle rendering the textures on screen in proper order
		//As well as handling the scrolling/collision for that level.
		//add to level

		//NOTE Layer is added to the level upon reading. This function still might be used in some capacity but otherwise an artifact to be kept until file management is finished.
		//Insert is usually reserved for when you want more control over the position of objects. LEAVE HERE - for reading multiple files may want to use this.
			//gLevel1->RenderOrder.insert(gLevel1->RenderOrder.end(), new Layer(savedTiles));
	}




};



class ObjectLayer {
private:
public:
	SDL_Surface* TargetSurface;
	SDL_Texture* CombinedObjects;
	Player* PlayerObject;

	ObjectLayer() {
		printf("ObjectLayer Created\n");
		//surface will be the size of the level, because we will render all sprites - although they may not necessarily be animated. I'm also unsure if we want all of them, or if we will find a way to organize relativity between sprites for rendering. Porblems ofr later.
		TargetSurface = SDL_CreateRGBSurface(0, LEVEL_WIDTH, LEVEL_HEIGHT, 32, 0, 0, 0, 0);
		CombinedObjects = NULL;
		PlayerObject = NULL;
	};



	//So this is gonna be a bit strange.
	//Basically this is just a 'collector' and a 'source'
	//It 'collects' every object, or rather every object collects 'it' - this layer.
	//Then - somehow - we'll pass the scrolling information from level, to this, to its derivatives (Player, objects)
	//then after those derivatives have their new position to blit, each one will blit to TargetSurface
	//Finally we will make it a texture, which Level has a pointer to, or this returns a pointer to.





};

class Level {
private:
public:
	SDL_Rect* Camera;
	std::vector<Layer*> RenderOrder;
	SDL_Texture* CombinedLower;
	SDL_Texture* CombinedHigher;
	SDL_Texture* CombinedTexture;
	int** CollisionOverride;
	int** CombinedCollision;
	//make use of swap to exchange orders dynamically perhaps.
	int LayerSplit = 1;
	ObjectLayer* SpriteLayer; //replacing PlayerLayer I think.
	SDL_Texture* TextureBuffer;
	int NumLayers; // this is the number of layers

	Level();
	~Level();
	void CombineUltraLayer();
	void CombineTextures();
	void RenderThis(Player* PlayerName);
	void CreateCamera(int x, int y);
	void MapAllCollision();
};


class Player {

	//QUESTION - should we prepare the class to handle multiple different tiles to be a 'object' or should we just assume it is one rectangle and the animations are swapping between those?
private:
	SDL_Rect* SourceTile; // change


public:
	int xPos;
	int yPos;
	SDL_Rect* SelfTile;
	SDL_Rect* TargetTile; //this needs to be edited by the programmer for specific instances/screen transitions.
	std::string SourceName;
	SDL_Texture* SelfImg;
	SDL_Surface* TempOrigin;

	//source img
	//width of player
	//height of palyer
	//target x
	//target y
	int xVel;
	int yVel;
	//movement speed (vel x, vel y) - movmeent vector not c vectors :P
	//animations?
	//default spawn location
	//'redraw' position x y
	//'reference' position (to compare to colision space. perhaps the 0,0 of the target tile vs movement tile.
	Player(int DefaultSpawnX, int DefaultSpawnY, int DefaultPixelH, int DefaultPixelW, std::string SourceKey, int SourceCoordx, int SourceCoordy, int SourcePixelH, int SourcePixelW, int xVelocity, int yVelocity);
	~Player();
	bool MoveY(int yVelocity, Level* level);
	bool MoveX(int xVelocity, Level* level);
	int getXPos();
	int getYPos();
	void RenderThis();
	int GetWidth();
	int GetHeight();
};

Level::Level() {
	printf("LEVEL CREATED!!!!!\n");

	CollisionOverride = new int* [LEVEL_HEIGHT];
	for (int i = 0; i < LEVEL_HEIGHT; i++) {
		CollisionOverride[i] = new int[LEVEL_WIDTH];
	}
	SpriteLayer = new ObjectLayer;
	CreateCamera(0, 0);
	CombinedHigher = NULL;
	CombinedLower = NULL;

	CombinedTexture = SDL_CreateTexture(gRenderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, LEVEL_WIDTH, LEVEL_HEIGHT);
	NumLayers = 0;

	//TextureBuffer= SDL_CreateTexture(gRenderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, LEVEL_WIDTH, LEVEL_HEIGHT);
	//may want to make it only the window but for now who cares.
}


Level::~Level() {
	printf("Deconstructor called for level\n");
}

void Level::CombineUltraLayer() {
	//should just be three or less for now, so for now if the texture is not null we will go forth.
	printf("CombineUltraLayer Called\n");
	//render Lower - OBject/Player - Higher -check for nulls and don't render if there is a null there instead!
	SDL_SetRenderTarget(gRenderer, CombinedTexture);
	if (CombinedLower != NULL) {
		printf("Okay place into CombinedTexture the Lower\n");
		SDL_RenderCopy(gRenderer, CombinedLower, NULL, NULL);
	}
	if (SpriteLayer->CombinedObjects != NULL) {
		printf("Okay place into CombinedTexture the Player\n");
		SDL_RenderCopy(gRenderer, SpriteLayer->CombinedObjects, NULL, NULL);
	}
	if (CombinedHigher != NULL) {
		printf("Okay place into CombinedTexture the Higher\n");
		SDL_RenderCopy(gRenderer, CombinedHigher, NULL, NULL);
	}
	printf("Return the Target to the Window\n");
	SDL_SetRenderTarget(gRenderer, NULL);


}

void Level::CombineTextures() { //trigger each time a layer is 'hidden' later as a boolean.
	//make new combined texture
	printf("going through combine textures()\n");
	if (LayerSplit <= RenderOrder.size()) {
		printf("Layers are able to split - %d = size of RenderOrder \n", RenderOrder.size());
	}
	else {
		printf("Layers are able UNABLE to split - %d = size of RenderOrder \n", RenderOrder.size());
	}
	//Add another layer in doc to test the blit sandwitching.

	SDL_SetRenderTarget(gRenderer, CombinedLower); //Will have to set the target back to window after the function finishes.
														//https://wiki.libsdl.org/SDL_SetRenderTarget
															//https://stackoverflow.com/questions/40886350/how-to-connect-multiple-textures-in-the-one-in-sdl2
	for (int i = 0; i < LayerSplit; i++) {
		//INSERT - boolean in each Layer for if we want it rendered. 
		//CHANGE - Also only go up to the player, then from above the player to the last layer.
		//CHANGE - bring this check outside, when we declare how many layers total the level will have eventually. Then compare the forloops to the player layer or some thing like that
		CombinedLower = SDL_CreateTexture(gRenderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, LEVEL_WIDTH, LEVEL_HEIGHT);
		if (i <= RenderOrder.size()) {
			SDL_RenderCopy(gRenderer, RenderOrder[i]->SelfHiddenTexture, NULL, NULL);
			printf("Rendering layer %d\n", i);
		}
		else {
			SDL_DestroyTexture(CombinedLower);
			CombinedLower = NULL;
			printf("Theres not enough info, so destroy the lower texture.\n");
			break;
		}
	}
	SDL_SetRenderTarget(gRenderer, NULL); //This resets the render target to the Render window (see the wiki)
	//At this point, the texture has all previous textures.


	SDL_SetRenderTarget(gRenderer, CombinedHigher); //Will have to set the target back to window after the function finishes.
														//https://wiki.libsdl.org/SDL_SetRenderTarget
															//https://stackoverflow.com/questions/40886350/how-to-connect-multiple-textures-in-the-one-in-sdl2
	for (int i = LayerSplit; i < RenderOrder.size(); i++) {
		//INSERT - boolean in each Layer for if we want it rendered. 
		//CHANGE - Also only go up to the player, then from above the player to the last layer.
		CombinedHigher = SDL_CreateTexture(gRenderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, LEVEL_WIDTH, LEVEL_HEIGHT);
		if (i <= RenderOrder.size()) {
			SDL_RenderCopy(gRenderer, RenderOrder[i]->SelfHiddenTexture, NULL, NULL);
		}
		else {
			SDL_DestroyTexture(CombinedLower);
			CombinedHigher = NULL;
			printf("Theres not enough info, so destroy the higher texture.\n");
			break;
		}
	}


	SDL_SetRenderTarget(gRenderer, NULL); //This resets the render target to the Render window (see the wiki)


	//set it as render target
	//grab pointers to textures
	//render copy each poitner the netire thing to the entire thing
	//set render target to null
	//render present
	//then clear the renderer
	//copy the renderer, target textures (the combined one) 
	//render the texture/  
	//perhaps set as this things texture?

}
void Level::RenderThis(Player* PlayerName) {
	// printf(".1.");
	// printf("number of layers is %d\n", NumLayers);
	for (int i = 0; i < NumLayers; i++) { // instead of comparing it to NumLayers, we may want to compare it to the bottom layers -- the layers below the player
		SDL_RenderCopy(gRenderer, RenderOrder[i]->SelfHiddenTexture, Camera, gFullWindowRect);
	}
	PlayerName->RenderThis(); // renders the player here


	// for layers above the player, we will want to do another for loop here
	SDL_RenderPresent(gRenderer);
	SDL_RenderClear(gRenderer);
}

// creates the camera for the level
void Level::CreateCamera(int x, int y) {
	//Set the 'default' of PartialTexture's width and height. (May be changeable if loading different maps on events.
	Camera = new SDL_Rect();
	Camera->w = SCREEN_WIDTH * TILE_WIDTH;
	Camera->h = SCREEN_HEIGHT * TILE_HEIGHT;

	//default render location
	Camera->x = x;
	Camera->y = y;
}
void Level::MapAllCollision() { // NEW
	// this sets up the size of combined collision based on the level width and height
	CombinedCollision = new int* [LEVEL_HEIGHT];
	for (int i = 0; i < LEVEL_HEIGHT; i++) {
		CombinedCollision[i] = new int[LEVEL_WIDTH];
	}


	// this goes through every layers collision and puts it all together in CombinedCollision
	for (int counter = 0; counter < NumLayers; counter++) { // NUM LAYERS WILL HAVE TO CHANGE
		for (int i = 0; i < LEVEL_HEIGHT; i++) {
			for (int j = 0; j < LEVEL_WIDTH; j++) {
				if (counter == 0) {
					CombinedCollision[i][j] = RenderOrder[counter]->Arr[i][j];
				}
				else if (RenderOrder[counter]->Arr[i][j] != 0 && counter > 0) {
					CombinedCollision[i][j] = RenderOrder[counter]->Arr[i][j];
				}
			}
		}
	}


	printf("testing with collision override...\n");
	for (int i = 0; i < LEVEL_HEIGHT; i++) {
		for (int j = 0; j < LEVEL_WIDTH; j++) {
			if (CollisionOverride[i][j] != -1) {
				CombinedCollision[i][j] = CollisionOverride[i][j];
			}
		}
	}

	// now we will go through the collision override and override any collision points in CombinedCollision
}



Player::Player(int DefaultSpawnX, int DefaultSpawnY, int DefaultPixelH, int DefaultPixelW, std::string SourceKey, int SourceCoordx, int SourceCoordy, int SourcePixelH, int SourcePixelW, int xVelocity, int yVelocity) {

	//SurfaceProperty* DefaultSourceSurface = SurfacePropertyMap["SourceName"]->texture;
	 //this is either atexture or a surface. 

	xPos = DefaultSpawnX;
	yPos = DefaultSpawnY;

	SourceName = SourceKey; //AA

	printf("Init Player\n");
	SourceTile = new SDL_Rect();
	SelfTile = new SDL_Rect();
	TargetTile = new SDL_Rect();
	SourceTile->x = SourceCoordx * TILE_WIDTH;
	SourceTile->y = SourceCoordy * TILE_HEIGHT;
	SourceTile->h = SourcePixelH;
	SourceTile->w = SourcePixelW;

	SelfTile->x = 0;
	SelfTile->y = 0;
	SelfTile->h = SourcePixelH;
	SelfTile->w = SourcePixelW;
	//grab a portion of a texture, and make a texture.

	TargetTile->x = DefaultSpawnX;
	TargetTile->y = DefaultSpawnY;
	TargetTile->w = DefaultPixelH;
	TargetTile->h = DefaultPixelW;
	//Surface -> Texture
	TempOrigin = SDL_CreateRGBSurface(0, SourceTile->w, SourceTile->h, 32, 0, 0, 0, 0);
	printf("checking\n");
	SDL_BlitSurface(SurfacePropertyMap[SourceName]->GetSelfSurface(), SourceTile, TempOrigin, SelfTile); // ERROR HERE
	printf("checking2\n");
	//case Temp Origin to a texture
	SelfImg = SDL_CreateTextureFromSurface(gRenderer, TempOrigin);
	xVel = xVelocity;
	yVel = yVelocity;

	gLevel1->SpriteLayer->PlayerObject = this;

}
Player::~Player() {
	printf("Destruct Player\n");
}

//void HandleEvent(); //handle collision?

// moves the player, moved the camera, detects for collision, detects for level barriers, all along the y-axis. returns 1 if the player icon moves, 0 if not.
bool Player::MoveY(int yVelocity, Level* level) { //move 
	yPos += yVelocity;

	if (yVelocity < 0) { // if moving up -- detecting collision
		if (1 == level->CombinedCollision[yPos / TILE_HEIGHT][xPos / TILE_WIDTH] || 1 == level->CombinedCollision[(yPos / TILE_HEIGHT)][(xPos + GetWidth() - 1) / TILE_WIDTH]) {
			// printf("cannot move up!\n");
			yPos -= yVelocity;
			return 0;
		}
	}

	else if (yVelocity > 0 && yPos < LEVEL_HEIGHT * TILE_HEIGHT - GetHeight()) { // if moving down -- detecting collision -- the second statement is so that it doesn't go through here when its at the edge
		if (1 == level->CombinedCollision[(yPos + GetHeight() - 1) / TILE_HEIGHT][xPos / TILE_WIDTH] || 1 == level->CombinedCollision[(yPos + GetHeight() - 1) / TILE_HEIGHT][(xPos + GetWidth() - 1) / TILE_WIDTH]) { // check for right collision
			yPos -= yVelocity; // reverts the movement change
			// printf("cannot move down!\n");
			return 0; // fails it
		}
	}

	if (yPos < (LEVEL_HEIGHT * TILE_HEIGHT) - (SCREEN_HEIGHT * TILE_HEIGHT / 2) && yPos >(SCREEN_HEIGHT * TILE_HEIGHT / 2)) { // this will move camera
		level->Camera->y += yVelocity; // this moves the camera by the yVelocity value
		return 0;
	}
	else if (yPos < (SCREEN_HEIGHT * TILE_HEIGHT / 2) && level->Camera->y > 0) { // NEW
		level->Camera->y += yVelocity; // the only situation in which this action takes place is when the camera is moving up; thus yVelocity must be negative, so we are subtracting the camera by adding yVelocity
		return 0;
	}
	else if (yPos > (LEVEL_HEIGHT * TILE_HEIGHT) - (SCREEN_HEIGHT * TILE_HEIGHT / 2) && level->Camera->y < LEVEL_HEIGHT * TILE_HEIGHT - SCREEN_HEIGHT * TILE_HEIGHT - 1) { // NEW -- this is for some reason unncessary on x-axis but not y
		level->Camera->y += yVelocity; // the only time when this action happens is when we are moving doown, thus yVelocity would be positive.
		return 0;
	}
	else { // this will move the player icon
		if (yPos < 0 || yPos + GetHeight() - 1 >= LEVEL_HEIGHT * TILE_HEIGHT) { // determines if it is in bounds -- if it is not, go through this if statement
			yPos -= yVelocity;
			return 0;
		}
		else {
			TargetTile->y += yVelocity; // actually moves the player
			return 1;
		}
	}
}
// moves the player, moved the camera, detects for collision, detects for level barriers, all along the x-axis. returns 1 if the player icon moves, 0 if not.
bool Player::MoveX(int xVelocity, Level* level) { //move
	xPos += xVelocity;
	if (xVelocity < 0) { // if moving left
		if (1 == level->CombinedCollision[yPos / TILE_HEIGHT][(xPos / TILE_WIDTH)] || 1 == level->CombinedCollision[(yPos + GetHeight() - 1) / TILE_HEIGHT][(xPos / TILE_WIDTH)]) { // check for left collision
			// printf("cannot move left!\n");
			xPos -= xVelocity; // reverts the movement change
			return 0; // fails it
		}
	}
	else if (xVelocity > 0 && xPos < LEVEL_WIDTH * TILE_WIDTH - GetWidth()) { // if moving right -- the second statemenet means it won't go through if it's at the edge
		if (1 == level->CombinedCollision[yPos / TILE_HEIGHT][(xPos + GetWidth() - 1) / TILE_WIDTH] || 1 == level->CombinedCollision[(yPos + GetHeight() - 1) / TILE_HEIGHT][(xPos + GetWidth() - 1) / TILE_WIDTH]) { // check for right collision
			xPos -= xVelocity; // reverts the movement change
			// printf("cannot move right!\n");
			return 0; // fails it
		}
	}
	if (xPos < (LEVEL_WIDTH * TILE_WIDTH) - (SCREEN_WIDTH * TILE_WIDTH / 2) && xPos >(SCREEN_WIDTH * TILE_WIDTH / 2)) { // this will move camera
		level->Camera->x += xVelocity;
		return 0; // the player icon did not move (only the camera)
	}
	else if (xPos < (SCREEN_WIDTH * TILE_WIDTH / 2) && level->Camera->x > 0) { // NEW 
		level->Camera->x += xVelocity;  // this will only happen when we're moving left, thus, xVelocity would be negative. therefore, we are subtracting through addition.
		return 0;
	}
	else if (xPos > (LEVEL_WIDTH * TILE_WIDTH) - (SCREEN_WIDTH * TILE_WIDTH / 2) && level->Camera->x < LEVEL_WIDTH * TILE_WIDTH - SCREEN_WIDTH * TILE_WIDTH - 1) { // NEW
		level->Camera->x += xVelocity; // this will only happen when we're moving right, thus, xVelocity would be positive. thus, we are just adding as normal.
		return 0;
	}

	else { // this will move the player icon
		if (xPos < 0 || xPos + GetWidth() - 1 >= LEVEL_WIDTH * TILE_WIDTH) { // checks to see if position is out of bounds
			xPos -= xVelocity;
			return 0;
		}
		else { // if not out of bounds, move
			TargetTile->x += xVelocity;
			return 1; // the player icon moved
		}
	}
}

int Player::getXPos() { // returns the x position
	return xPos;
}

int Player::getYPos() { // returns the y position
	return yPos;
}
//make a second to handle new target positions, in the event it is changed idk.
void Player::RenderThis() {
	//Test Blitting is very bad, so what actually happens is it automatically wipes the information of the previous surface. So lets try placing a texture over it, and just grabe the texture from the target texture.
	SDL_RenderCopy(gRenderer, SelfImg, NULL, TargetTile);
};

int Player::GetWidth() {
	return SelfTile->w;
}

int Player::GetHeight() {
	return SelfTile->h;
}



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
		std::string path2 = path + temp; // adds "/source/repos/" to the

		temp.erase(); // erases the temp string

		std::replace(path2.begin(), path2.end(), '\\', '/'); // replaces all of the '' with ' / '

		return path2; // returns the path2
	}
}



// clears the SurfacePropertyMap
void FreeMapSurfaces() {

	//EDIT - Memory management happens here too.

	//INSERT call to delete tiles in the hash, then delete the hash

	//DANGEROUS - delete this seemd to break it!
	for (auto p : SurfacePropertyMap) {
		p.second -> ~SurfaceProperty();
	}

	SurfacePropertyMap.clear();
	//clear all textures, and surfaces, and the global hidden's. - Unknown if this releases the memory of those objects. Assume it does not.

	//https://stackoverflow.com/questions/6952083/deleting-self-object-inside-class 
	//If object made through 'new', we should be able to deconstruct with delete this* like the others
}

// initializes SDL
bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		//Create window
		gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH * TILE_WIDTH, SCREEN_HEIGHT * TILE_HEIGHT, SDL_WINDOW_SHOWN);
		//Get window surface -I BELIEVE THAT ONCE THIS IS ATTACHED TO GWINDOW, THAT IT'S DEALLOCATED WITH IT. BE SURE TO CHECK LATER. MENTION IT EXPLICITLY ON TOP OF FILE IF CHECKED.
		gScreenSurface = SDL_GetWindowSurface(gWindow);

		//Fill with color, aesthetic. Displays red before texture is loaded/displayed.
		SDL_FillRect(gScreenSurface, NULL, SDL_MapRGB(gScreenSurface->format, 255, 0, 0));

		//initialize our Renderer, using the GPU, 
		gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);

		//Update surface to show red before textures are loaded.
		SDL_UpdateWindowSurface(gWindow);
	}
	return success;
}

//Currently not in Use
bool loadMedia()
{ //EDIT, this may replace get dimension when time to split files into JSON.
	//Loading success flag
	bool success = true;

	/*
	//Load splash image
	gTileSourceSurface = SDL_LoadBMP("C:/Users/thebl/source/repos/Dungeon(1).bmp"); //CHANGE ME
	if (gTileSourceSurface == NULL)
	{
		printf("Unable to load image %s! SDL Error: %s\n", "02_getting_an_image_on_the_screen/hello_world.bmp", SDL_GetError());
		success = false;
	}*/

	return success;
}

//Closes everything out on the window - Deletes all Surfaces.
void close()
{
	//Deallocate surfaces, textures, sdl_rects, tiles, tilehash, etc. Anything in a data structure should be deallocated in this function.
	FreeMapSurfaces();

	//insert another function to destruct every tile in our map

	//insert another function/thing to destruct our renderer, unless it is destroyed by destroyWindow as well -like the surface of the window.

	//Destroy window -AGAIN CHECK IF THE SURFACE THAT 'GOT' IT IS DEALLOCATED SOMEHOW
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;


	gLevel1->~Level();

	Player1->~Player();

	//Quit SDL subsystems
	//Quit SDL_Image
	IMG_Quit();
	//Quit SDL
	SDL_Quit();
}


//QUALITY Functions
	//Takes two strirngs and asks if they are the same. Return true if so. False if not.
bool IsSameString(std::string Question, std::string Answer) { //REORGANIZE the if statements, so that we could cut out while loop early.
	unsigned int i = 0;
	while (Question[i] != '\0' && Answer[i] != '\0' && Question[i] == Answer[i]) {
		i++;
	}
	if (i == Question.length() && i == Answer.length()) {
		return true;
	}
	else {
		return false;
	}
}

// converts a hexadecimal value to an integer; necessary for reading the rgb values of transparency
int hexToInt(std::string str, int start) {
	// the string is the hexadecimal we are reading, and the integer is where we start reading the string 
	std::string temp;
	int ret; // the integer value we will be returning
	temp += str[start];
	temp += str[start + 1];
	std::stringstream ss;
	ss << std::hex << temp;
	ss >> ret; // putting the decimal integer value of the hexadecimal into ret
	return ret;
}

//Splits a string (value,value) into two globals. 
void SplitStringStream(std::string& line, int& GlobalWidth, int& GlobalHeight) {
	long long d = 0; //Modified to prevent overflow, long long = long long int, which is an 8 byte integer. Required by (I believe) substr function.
	std::string tempWidth;
	std::string tempHeight;
	//Find comma's position in the string
	while (line[d] != ',') {
		d++;
	}
	d++;
	//Create two substrings, to isolate the integer portion of each side of the comma.
	tempWidth = line.substr(0, line.length() - d);
	tempHeight = line.substr(d, line.length());
	// printf("Dimensions are %s, %s\n", tempWidth.c_str(), tempHeight.c_str());

	//Convert both substrings to integer values.
	std::istringstream iss1(tempWidth);
	std::istringstream iss2(tempHeight);

	//Assign as Globals for Window Width and Widow Height - From Text Save File.
	iss1 >> GlobalWidth;
	iss2 >> GlobalHeight;
}

//Takes a String and String and returns a char* with elements of both, the size of both, null terminated.
char* StringAndStringToCharArr(std::string& TempPath2, std::string& tempSource) {
	//CHECK - the warning might just be the byte size of size() is 8 or 32 bytes while ints are by default 4.
	int TempPath2Len = TempPath2.size();
	int TempSourceLen = tempSource.size();
	char* TempPath = new char[TempPath2Len + TempSourceLen];
	//Concatonate Repo Path and the Image.Format. 
	for (int i = 0; i < TempPath2Len; i++) {
		TempPath[i] = TempPath2[i];
	}
	for (int i = 0; i < TempSourceLen; i++) {
		TempPath[(i + TempPath2Len)] = tempSource[i];
	}
	//Mull Terminate
	TempPath[TempPath2Len + TempSourceLen] = '\0';
	return TempPath;
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
				gFullWindowRect->h = SCREEN_HEIGHT * TILE_HEIGHT;

				//Set the 'default' of PartialTexture's width and height. (May be changeable if loading different maps on events.
				gCamera = new SDL_Rect();
				gCamera->w = SCREEN_WIDTH * TILE_WIDTH;
				gCamera->h = SCREEN_HEIGHT * TILE_HEIGHT;

				//default render location
				gCamera->x = 0;
				gCamera->y = 0;

				//Actually create a surface to blit onto. The 32 flag just defines pixel Depth - the amount of colors to be handled. In this case, 2^32 types.
				gHiddenSurface = SDL_CreateRGBSurface(0, LEVEL_WIDTH * TILE_WIDTH, LEVEL_HEIGHT * TILE_HEIGHT, 32, 0, 0, 0, 0);

				//If Dimension was read properly - Enable the option to find for "Tilesets" header.
				return true;
			}
			else {
				//CHANGE - the close file should still be called in getDimensions, but could be called here after compartimentalization is complete.  
				printf("End of file was reached :/\n");
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

//Necessary for Surface Creation
long int GenerateOffSetMap() {
	long int Offset = 0;
	for (auto p : SurfacePropertyMap) {
		// printf("OFFSET INSERTED IS %d FOR %s\n", Offset, p.first.c_str());
		OffSetMap.insert(std::make_pair(p.first, Offset));
		Offset += p.second->GetTotalTile(); //accumulates
	}

	return Offset; //should have still accumulated the total amount of tiles, but only assigned up to the last surfaces worth
}



//Assumes the file will be closed in another function. 
bool SurfaceCreation(std::ifstream& sourceIMG, std::string& line, long int& TotalTilesOfSurface) {
	//for all globals that aren't constant, we'll be passing references through where they are needed, then storing in main. TotalTilesOfSurface is one example.
	// printf("Tilesets found\n");
	int counter = 0;
	//Ensure the Filestream is open
	if (sourceIMG.is_open()) {

		getline(sourceIMG, line); //Line holds the first Image.format,Surname - Example: Bitmap.bmp,AA. 

		//For Every following line, until Tiles is found. 
		while (!IsSameString(line.c_str(), "Collision")) { // go through txt file until you reach "collision"

			//INSERT - check If Image.format,Surname

			//Obtain the Image.format String
			std::string tempSource = line.substr(0, line.length() - (SurnameLength + 1));
			// printf("Bitmap %s found\n", tempSource.c_str());

			//Obtain the Image.format's Surname.
			std::string tempName = line.substr(line.length() - SurnameLength, line.length());

			//These steps are necessary to use IMG_Load.

			//CHANGE - these variable names
			std::string TempPath2 = UserDirectory();//CHANGE ME - Need to know Save File Repository Path.
			char* TempPath = StringAndStringToCharArr(TempPath2, tempSource);
			//Create new surface with expected file location
			new SurfaceProperty(tempName, tempSource, IMG_Load(TempPath), TempPath);

			SurfacePropertyEnum.insert(std::make_pair(counter, tempName));
			// printf("%s added as enum = %d\n", tempName.c_str(), counter);
			//Grab the next the img file, and the 'label'. Or "Tiles" header.
			getline(sourceIMG, line);
			counter++;
		}
		//Generate OffSetMap NEW
		TotalTilesOfSurface = GenerateOffSetMap();
		GlobalTileHash = new TileHash(TotalTilesOfSurface); //gotta be global for access purposes. Again, we'd have to pass ref all the way back to main eventually. HUGE pain though.
		return true;
	}
	else {
		printf("FILE UNOPENABLE (Surface Creation)\n");
		return false;
	}
	return false;
}


bool CollisionCreation(std::ifstream& sourceIMG, std::string& line) { // JACK CHANGE
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
// generates all of the tiles
void GenerateTiles() {
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
bool DrawSavedTiles(std::ifstream& sourceIMG, std::string& line) {
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
			gLevel1->RenderOrder.push_back(new Layer(savedTiles));
			gLevel1->NumLayers++;
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

void OverrideCollision(std::ifstream& sourceIMG, std::string& line) {
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


			gLevel1->CollisionOverride[y][x] = d;



			i = 0;
			j++;
			k++;
			x = 0;
			y = 0;

		}
	}
}



// creates the player class; this is the default that we currently are using
void CreatePlayer() {
	int DefaultSpawnX = 0;
	int DefaultSpawnY = 0;
	int DefaultPixelH = 16;
	int DefaultPixelW = 16;
	//SurfaceProperty* DefaultSourceSurface = SurfacePropertyMap["AA"]; -default for now
	std::string DefaultSourceName = "AA";
	int SourceCoordx = 5;
	int SourceCoordy = 0;
	int SourcePixelH = 16;
	int SourcePixelW = 16;

	int xVelocity = 1;
	int yVelocity = 1;
	Player1 = new Player(DefaultSpawnX, DefaultSpawnY, DefaultPixelH, DefaultPixelW, DefaultSourceName, SourceCoordx, SourceCoordy, SourcePixelH, SourcePixelW, xVelocity, yVelocity);
};

//Grabs everything from the file. Maps paths to letter names, creates tiles, and finds screen dimensions
void GetDimension(std::string MapRepo, long int& TotalTilesOfSurface) {
	//CHANGE All variable declarations must be declared at the start of this function, before anything else, as much as applicable, after making sub functions.

	//Object to hold our Saved Map File
	std::ifstream sourceIMG;

	//Open our Map File from our Repository - Repository should be known through the Saving of the program.
	sourceIMG.open(MapRepo); //Insert a check to see if it exists, or it opened properly.



	if (sourceIMG.is_open()) { //Insert a check to see if the map was openable, if not throw error should be thrown, so I guess make this bool?
		std::string line;
		int FoundTileSetHeader = false; //controls if getline() is to look for "TileSet" header. Tileset is equivalent to the Surfaces we are opening.
		int FoundTileHeader = false; //controls if getline() is to look for "Tiles" header. Tiles is equivlanet to all the SDL_Rect's we will want to blit.
		int FoundCollisionHeader = false;
		int FoundCollisionOverrideHeader = false;

		FoundTileSetHeader = ScreenTileDimension(sourceIMG, line);
		//NEW - temporary, declared here since we are only working with one level, and might as well, although ideally we'd only do so right when we need to
		//placed here since we need the screen width and height at minimum. -although we could wait to declare override array..
		gLevel1 = new Level;

		//create the window/screen surface
		if (!init())
		{
			printf("Failed to initialize!\n");
		}

		//While we are not at the end of the file. 
		while (!sourceIMG.eof()) {
			getline(sourceIMG, line);

			if (FoundTileSetHeader && IsSameString(line.c_str(), "Tilesets")) { //Insert a check, if Header not found, throw.
				FoundCollisionHeader = SurfaceCreation(sourceIMG, line, TotalTilesOfSurface);
			}

			if (FoundCollisionHeader && IsSameString(line.c_str(), "Collision")) { //Insert - This check may be redudant, but if "Tiles" is not found, throw.
				FoundTileHeader = CollisionCreation(sourceIMG, line);
			}
			if (SurfacePropertyMap.size() > 0) {
				GenerateTiles();
			}


			if (FoundTileHeader && IsSameString(line.c_str(), "Tiles")) { //Insert - This check may be redudant, but if "Tiles" is not found, throw.
				FoundCollisionOverrideHeader = DrawSavedTiles(sourceIMG, line);
			}

			if (FoundCollisionOverrideHeader && IsSameString(line.c_str(), "Collision Override")) {
				OverrideCollision(sourceIMG, line);
				// printf("collision override is...\n");
				for (int i = 0; i < LEVEL_HEIGHT; i++) {
					for (int j = 0; j < LEVEL_WIDTH; j++) {
						// printf("%d ", gLevel1->CollisionOverride[i][j]);
					}
					// printf("\n");
				}
				// printf("map collision has been called...\n");
				gLevel1->MapAllCollision(); // NEW
				// printf("Combined Collision is...\n");
				for (int i = 0; i < LEVEL_HEIGHT; i++) {
					for (int j = 0; j < LEVEL_WIDTH; j++) {
						// printf("%d ", gLevel1->CombinedCollision[i][j]);
					}
					// printf("\n");
				}
			}

			//If everything was read as it should be by eof
			if (FoundTileSetHeader && FoundCollisionHeader && FoundTileHeader && FoundCollisionOverrideHeader) {
				printf("COMBINE TEXTURES\n");
				CreatePlayer(); // Creates the player
				gLevel1->CombineTextures();
				gLevel1->RenderThis(Player1);

			}
			else {
				printf("Dim Throw\n");
			}
		}
		//Close the File
		sourceIMG.close();
	}
}



// function that finds where the center of the camera is; this way, the camera only moves depending on where the player is
void FindCameraCenters(int& XLcenter, int& XRcenter, int& YUcenter, int& YDcenter) {
	printf("SCREEN WIDTH : %d, SCREEN HEIGHT : %d\n", SCREEN_WIDTH, SCREEN_HEIGHT);
	//is there an even amount of tiles on x axis?
	if ((SCREEN_WIDTH % 2) * TILE_WIDTH != 0) { //if Odd
		XLcenter = (SCREEN_WIDTH / 2) * TILE_WIDTH - 1;
		XRcenter = (SCREEN_WIDTH / 2) * TILE_WIDTH + 1;
	}
	else { //if even length
		XLcenter = (((SCREEN_WIDTH * TILE_HEIGHT) / 2) - 1);
		XRcenter = (SCREEN_WIDTH / 2) * TILE_WIDTH + 1;
	}

	if (SCREEN_HEIGHT % 2 * TILE_HEIGHT != 0) { //if Odd
		YUcenter = (SCREEN_HEIGHT / 2) * TILE_HEIGHT - 1;
		YDcenter = (SCREEN_HEIGHT / 2) * TILE_HEIGHT + 1;
	}
	else { //if even
		//trouble! if HEIGHT is odd, either one, then /2 is DANGEROUS CHECK
		YUcenter = (((SCREEN_HEIGHT * TILE_HEIGHT) / 2) - 1);
		YDcenter = (SCREEN_HEIGHT / 2) * TILE_HEIGHT + 1;
	}

};

// is this necessary???
void KeyBoardStackRate() {
	if (gEnableDelay) {
		SDL_Delay(100); //this needs to be tested, basically we don't want 0 delay for reading inputs, but we want it snappy. 
		//This prevents a backlog of keypresses from being pushed onto the stack. This or we take our events into an array as 'instances' and then only keep the one in process and the one most recently recieved. 
		//for now this delay will do.
	}
}


// determines where the camera is able to move on the x axis
bool ScrollLevelBarrierX(int xVel, int xBuff) {
	gLevel1->Camera->x += xVel;
	if (gLevel1->Camera->x < 0 || gLevel1->Camera->x > xBuff) {
		// printf("Camera reached limit");
		gLevel1->Camera->x -= xVel;
		return 0; //fail, move back
	}

	//check for collision -may depend on direction
	std::string dir;
	if (xVel < 0) {
		dir = "Left";
	}
	else {
		dir = "Right";
	}
	// printf("Add one xVel, movin %s\n", dir.c_str());


	return 1; //success
}

// determines where the camera is able to move on the y axis
bool ScrollLevelBarrierY(int yVel, int yBuff) {
	gLevel1->Camera->y += yVel;
	if (gLevel1->Camera->y <0 || gLevel1->Camera->y > yBuff) {
		gLevel1->Camera->y -= yVel;
		return 0; //fail, move back
	}
	return 1; //success
}

// handles the loop in main. this determines fps and user inputted events
void handleLoop() {
	// fps timers
	Timer fpsTimer; // calculates the fps
	Timer capTimer; // limits the max possible fps

	// begin counting fps
	int countedFrames = 0;
	fpsTimer.start();

	// movement variables

	//Player movements
	int xVel = 0; // velocity of x
	int yVel = 0; // velocity of y position
	int xVec = 1; //how many pixels x movement is on x axis
	int yVec = 1; //how many pixels y movement is on y axis
	// Camera movements
	int xPos = 0; // Target Tile position on original texture
	int yPos = 0; // Target Tile position on original texture

	//Limits of the level
	//0 is implicit
	int yBuff = LEVEL_HEIGHT * TILE_HEIGHT - SCREEN_HEIGHT * TILE_HEIGHT; //the 'limit' space for the 'box' around the player to move.
	int xBuff = LEVEL_WIDTH * TILE_WIDTH - SCREEN_WIDTH * TILE_WIDTH; //the 'limit' space for the camera tracking player to move.
	int yPlayerBuff = SCREEN_HEIGHT * TILE_HEIGHT;
	int xPlayerBuff = SCREEN_WIDTH * TILE_WIDTH;


	//center of camera
	int XLcenter;
	int XRcenter;
	int YUcenter;
	int YDcenter;
	FindCameraCenters(XLcenter, XRcenter, YUcenter, YDcenter);
	printf("Centers are : XL: %d, XR: %d, YU: %d, YD: %d\n", XLcenter, XRcenter, YUcenter, YDcenter);

	// loop variables
	bool quit = false; // handles the loop; whether we want to quit, or continue
	SDL_Event e; // event handler



	// begin loop
	while (!quit) {
		capTimer.start(); // starts the max fps timer 
		while (SDL_PollEvent(&e) != 0) {	// this is checking to see if there is an event or not 
			if (e.type == SDL_QUIT) {	// if the user event is "QUIT" then...
				quit = true;	// this will end the loop
			}
			// if the user does not want to quit, continue with the loop
			if (e.type == SDL_KEYDOWN && e.key.repeat == 0) // if the user presses down a key
			{
				switch (e.key.keysym.sym) // Select surfaces based on key press
				{
				case SDLK_w: // if the user presses 'w'
					yVel -= yVec;
					break;
				case SDLK_s: // if the user presses 's'
					yVel += yVec;
					break;
				case SDLK_a: // if the user presses 'a'
					xVel -= xVec;
					break;
				case SDLK_d: // if the user presses 'd'
					xVel += xVec;
					break;
				}
			}
			else if (e.type == SDL_KEYUP && e.key.repeat == 0) // if the user releases a key, go through this statement
			{
				switch (e.key.keysym.sym) // Select surfaces based on key press
				{
				case SDLK_w: // if the user releases 'w'
					yVel += yVec;
					break;
				case SDLK_s: // if the user releases 's'
					yVel -= yVec;
					break;
				case SDLK_a: // if the user releases 'a'
					xVel += xVec;
					break;
				case SDLK_d: // if the user releases 'd'
					xVel -= xVec;
					break;
				}
			}
		}

		Player1->MoveY(yVel, gLevel1);
		Player1->MoveX(xVel, gLevel1);

		// printf("%d %d -- %d %d\n", Player1->xPos, Player1->yPos, gLevel1->Camera->x, gLevel1->Camera->y); // camera x and y are not going back to 0. they need to when moving back up tho... awk.


		gLevel1->RenderThis(Player1);

		// calculating fps
		float avgFPS = countedFrames / (fpsTimer.getTicks() / 1000.f); // calculates fps
		if (avgFPS > 2000000) { // this is an extremely large fps that may occur at startup; this is not correct, though, so we are putting the avgFPS as 0, instead
			avgFPS = 0;
		}
		++countedFrames; // adds 1 to the countedFrames
		//If frame finished early
		printf("Average FPS: %f\n", avgFPS); // printf the fps text to the terminal -- CAN BE COMMENTED OUT IF NOT WANTING TO BE DISPLAYED
		int frameTicks = capTimer.getTicks();
		if (frameTicks < SCREEN_TICKS_PER_FRAME)
		{
			//Wait remaining time
			SDL_Delay(SCREEN_TICKS_PER_FRAME - frameTicks);
		}

	}
}
//universal timer

//smoother scroll - fps consistant, tie to clock, stretch pixel, don't redraw (things) unncessarily
//frame of animation based on universal timer for specific animation tile set tile.
//intregal divison, counter%delay then integer divison. is intger faster or slower than decimal divison?
//if you put five aniamtion tiles on a map, (series on tile set) that tileset would store five 'counters' to denote what animation it's on.
//then depending on place thand offset.
//four frames in animation, can put any four as the'start'


int main(int argc, char* args[]) {
	long int TotalTilesOfSurface;
	//getDimension assumed ot be 'load file'
	std::string MapRepo = UserDirectory() + "Collision Dummy.txt"; //CHANGE ME - Requires knowing Repo from Save Files


	//Heres a good question. Why does init() work before we get the proper window size?
	//Technically it is not working, as window dimensions aren't set until getDimension is used. However Dimension needs the target surface to blit. 
	//Thus we will break Dimension to pass fstream through the process of reading the file. 

	//Start up SDL and create window


		//Load media
	if (!loadMedia())
	{
		printf("Failed to load media!\n");
	}
	else
	{
		GetDimension(MapRepo, TotalTilesOfSurface);
		//TEMP
		handleLoop();
	}

	close(); //Free resources and close SDL - INSERT call deconstructor of every tile. 

	return 0;
}