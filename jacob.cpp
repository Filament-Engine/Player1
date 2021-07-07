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


//So go to each layer, make a buffer (1 layer around camera)
	//render from copy constructor matrix (made during collision
	//Then 

//Json

//algor the loops

//Collision coloring

//Matrix of tiles, blit in each frame

//garbage map maker.

//header file


const bool gEnableDelay = false;


// fps constants
const int MAX_FPS = 120; // this is the maximum amount of fps we have

//EDITED
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
		//if you get exceptions here, double check you have the corerct pngs or bmps in the repos folder.
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
		SDL_SetTextureBlendMode(SelfTexture, SDL_BLENDMODE_BLEND);
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
	//NEW
	SDL_Texture* SelfTexture;


	//Defined in TileHash Class, for access.
	void MapThis();
	Tile* GetThis();
	void BlitThis(int Targetx, int Targety, SDL_Surface*& LayerHiddenSurface);

	//Constructor; Height and width are of source tile. Expects (std::string n, int p, int width, int height)
	Tile(std::string n, int p, int width, int height, int DefaultCollision) {
		CollisionType = DefaultCollision;
		//printf("Origin tile has collision\n");
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
		SetSelfTexture();
		//add to hash for access

		MapThis();

	}
	//Copy constructor. 
	Tile(Tile& copyTile) {

		//printf("Copy Created\n");
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
		SetSelfTexture();
		//DO NOT HASH THE OBJECT - When it's copied, it's getting the preset data. The preset data stored in the hash is used for the reason. IF WE COPY the preset, we cannot add to hash
		//unless of course you treat this special for some reason, in that case we'll have ot ad a linker to the hash.

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

	void SetSelfTexture() {
		//From my knowledge there is no copy constructor for Textures in SDL. Thus we will 
		//printf("Tile Texture Created\n");
		SelfTexture = SDL_CreateTexture(gRenderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_TARGET, TILE_WIDTH, TILE_HEIGHT);
		SDL_SetTextureBlendMode(SelfTexture, SDL_BLENDMODE_BLEND);
		//Take a part of the source texture, give it to this tile object
		SDL_SetRenderTarget(gRenderer, SelfTexture);
		SDL_RenderCopy(gRenderer, SurfacePropertyMap[IMGSource]->GetSelfTexture(), &SourceTile, NULL);
		//return render to window
		SDL_SetRenderTarget(gRenderer, NULL);
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

/////////////////////////////////////////////////////////////////////////////////

class Layer {
public:
	SDL_Surface* SelfHiddenSurface;
	SDL_Texture* SelfHiddenTexture;

	//NEW
	SDL_Texture* TextureDependentTexture;
	SDL_Rect* Stamp;

	int* CollisionData;
	std::string** DrawnTiles;
	int** Arr;

	//NEW
	Tile*** CopiedTiles;
	int PerimeterBuff;
	int TextureDepDim;

	Layer(std::string* DrawnTilesRead[]) {
		//if they end up being stored on seperate files, just assign a null to ensure all variables have something and not garbage.

		// printf("Layer Started\n");
		CopiedTiles = NULL; //just for the warning t odisappear.
		AddTiles(DrawnTilesRead);
		// printf("Tiles Added to Layer Successfully\n");
		CollisionData = new int[LEVEL_HEIGHT * LEVEL_WIDTH]; //Every layer should have data for every position 


		AddCollision();
		SelfHiddenSurface = SDL_CreateRGBSurface(0, LEVEL_WIDTH * TILE_WIDTH, LEVEL_HEIGHT * TILE_HEIGHT, 32, 0, 0, 0, 0);


		PerimeterBuff = 1;
		while (SCREEN_WIDTH + PerimeterBuff > LEVEL_WIDTH && SCREEN_HEIGHT + PerimeterBuff > LEVEL_HEIGHT) {
			PerimeterBuff -= 1;
			printf("PerimeterBuff-1 = %d\n", PerimeterBuff);
		}


		TextureDependentTexture = NULL;
		TextureDepDim = (SCREEN_WIDTH + PerimeterBuff) * (SCREEN_HEIGHT + PerimeterBuff);
		Stamp = new SDL_Rect;
		Stamp->w = TILE_WIDTH;
		Stamp->h = TILE_HEIGHT;
		Stamp->x = 0;
		Stamp->y = 0;

		//check needed to compare screen and level to determin perim buff at certain points. - camera may take care of hte general movement, but idk

		//lets not do it without camera info, maybe it'll help
		//MakeTextureDependent(); // There should be one with a camera position in the future

		SelfHiddenTexture = NULL;
		CreateTransparency("0x000000"); // takes the black background and makes it transparent 
		// printf("Texture and Surface defaults made!\n");
		BlitMatrixLayer();
		MakeSelfTexture();

		//NOW - I want to make a function that makes textures from a series of textures from the matrix


		//after addcollision and add tiles are done, matrices are made
		//blit this for all tiles in the DrawnTiles std::string** same way we used to through tilemap
		// 
		// Call Blit this AFTER all layers have been read and stored. Make it a seperate part of GetDimension
		// 
		//Turn that selfSurface into a selfTexture


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
				printf("Empty Tile Read? You Sure?\n");
			}
			DrawnTiles[i] = DrawnTilesRead[i];
			//CopiedTiles[i] = new Tile(*GlobalTileHash->find(DrawnTilesRead[i]->c_str()));
		}
		//printf("%d\n", LEVEL_WIDTH);
		CopiedTiles = new Tile * *[LEVEL_HEIGHT];
		for (int i = 0; i < LEVEL_HEIGHT; i++) {
			CopiedTiles[i] = new Tile * [LEVEL_WIDTH];
			//printf("\n\n");
			for (int j = 0; j < LEVEL_WIDTH; j++) {

				//printf("--%s--", DrawnTilesRead[((i* LEVEL_WIDTH) + j)]->c_str());
				//printf("Tile %s Placed at {%d, %d}, and was found at %d in DrawnTilesRead\n", DrawnTilesRead[(i + j)]->c_str(), i, j, i + j);
				CopiedTiles[i][j] = GlobalTileHash->find(DrawnTilesRead[((i * LEVEL_WIDTH) + j)]->c_str());//new Tile(*GlobalTileHash->find(DrawnTilesRead[((i * LEVEL_WIDTH) + j)]->c_str()));
			}

		}
		//printf("\n");
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


	//NEW - make 2, one for default, one for if given camera position
	void MakeTextureDependent() {
		//printf("Make Texture Dep\n");
		SDL_SetRenderTarget(gRenderer, TextureDependentTexture);
		//TextureDepDim is the area of the texture, since we only want to render that bit

	   //NEED A CHECK FOR SCREEN VS LEVEL SIZE - for now lets ignore.
		int TextureDepH = SCREEN_HEIGHT + PerimeterBuff;
		int TextureDepW = SCREEN_WIDTH + PerimeterBuff;
		Stamp->x = 0;
		Stamp->y = 0;
		for (int i = 0; i < TextureDepH; i++) {
			Stamp->y += TILE_HEIGHT;
			if (Stamp->y < LEVEL_HEIGHT * TILE_HEIGHT) {

				for (int j = 0; j < TextureDepW; j++) {
					Stamp->x += TILE_WIDTH;
					if (Stamp->x < LEVEL_WIDTH * TILE_WIDTH) {
						//printf("100? = %d\n", i + j);
						//printf("Render Copy = (%d, %d) %d\n", i, j, (i * TextureDepW) + j);
						SDL_RenderCopy(gRenderer, CopiedTiles[i][j]->SelfTexture, Stamp, NULL);
						//printf("Rendered \n");
					}
				}
			}
		}
		SDL_SetRenderTarget(gRenderer, NULL);
		//printf("end texturedep making process\n");
	}


	void MakeTextureDependent(SDL_Rect* Camera) {
		if (TextureDependentTexture != NULL) {
			SDL_DestroyTexture(TextureDependentTexture);
		}
		TextureDependentTexture = SDL_CreateTexture(gRenderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_TARGET, (SCREEN_WIDTH + PerimeterBuff) * TILE_WIDTH, (SCREEN_HEIGHT + PerimeterBuff) * TILE_HEIGHT);
		SDL_SetTextureBlendMode(TextureDependentTexture, SDL_BLENDMODE_BLEND);
		SDL_SetRenderTarget(gRenderer, TextureDependentTexture);
		//TextureDepDim is the area of the texture, since we only want to render that bit

	   //NEED A CHECK FOR SCREEN VS LEVEL SIZE - for now lets ignore. -2's are from the perimeter thingy, for now we can ignore I think

		int ProperX = 0;
		int ProperY = 0;

		//Relative to the frame
		int StartH = (Camera->y / TILE_HEIGHT) - PerimeterBuff;
		int StartW = (Camera->x / TILE_WIDTH) - PerimeterBuff;


		int TextureDepH = SCREEN_HEIGHT + (PerimeterBuff)+StartH;
		int TextureDepW = SCREEN_WIDTH + (PerimeterBuff)+StartW;

		//printf("Cx: %d, Cy: %d, Tx: %d, Ty: %d, Pb: %d\n", StartW, StartH, TextureDepW, TextureDepH, PerimeterBuff);

		//printf("//////////////////////////////////////////////////////////////////////////////////\n\n");

		//printf("Start H:%d, W:%d, Dep H:%d, W:%d\n", StartH, StartW, TextureDepH, TextureDepW);

		//printf("%s\n", CopiedTiles[20][0]->label.c_str());

		for (int i = StartH; i < TextureDepH + ProperY; i++) {

			if (i < 0) {
				//printf("%d < 0\n", i);
				ProperY += 1;
			}
			else {
				if (i > LEVEL_HEIGHT - 1) {
					ProperY -= 1;
				}
				else {
					Stamp->y = (i - StartH) * TILE_HEIGHT;
					for (int j = StartW; j < TextureDepW + ProperX; j++) {
						Stamp->x = (j - StartW) * TILE_WIDTH;

						if (j < 0) {
							//printf("%d < 0\n", j);
							ProperX += 1;
						}
						else {
							if (j > LEVEL_WIDTH - 1) {
								ProperX -= 1;
							}
							else {
								//printf("i= %d < %d, j= %d < %d\n", i, TextureDepH + ProperY, j, TextureDepW + ProperX);
								//printf("i+ProperY = %d  j+ProperX = %d\n", i + ProperY, j + ProperX);
								SDL_RenderCopy(gRenderer, CopiedTiles[i][j]->SelfTexture, NULL, Stamp);
							}
						}

					}
				}
			}

		}
		SDL_SetRenderTarget(gRenderer, NULL);


		//printf("//////////////////////////////////////////////////////////////////////////////////\n\n");
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
	SDL_Texture* BlankLayer; //NEW - trying pixel access. This will be exclusively for overwriting previous positions of things, or all of it. 
	Player* PlayerObject;
	//vector<sprites> Sprites 
		//renderthis ^

	ObjectLayer() {
		// printf("ObjectLayer Created\n");
		//surface will be the size of the level, because we will render all sprites - although they may not necessarily be animated. I'm also unsure if we want all of them, or if we will find a way to organize relativity between sprites for rendering. Porblems ofr later.
		TargetSurface = SDL_CreateRGBSurface(0, LEVEL_WIDTH, LEVEL_HEIGHT, 32, 0, 0, 0, 0);
		CombinedObjects = NULL;
		PlayerObject = NULL;
		//Eventually need ot do this, idk when yet.
		CombinedObjects = SDL_CreateTexture(gRenderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_TARGET, LEVEL_WIDTH * TILE_WIDTH, LEVEL_HEIGHT * TILE_HEIGHT);
		//Change Blend Mode to 1
		if (0 == SDL_SetTextureBlendMode(CombinedObjects, SDL_BLENDMODE_BLEND)) {
			//none = 0
			// Blend =1
			//SDL_BlendMode Blender = 1;
			// printf("\nChanged Blend Mode of CombinedObjects\n");
		}
		BlankLayer = SDL_CreateTexture(gRenderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_TARGET, LEVEL_WIDTH * TILE_WIDTH, LEVEL_HEIGHT * TILE_HEIGHT);

	}

	// creates the player class; this is the default that we currently are using
	void CreatePlayer();
	void RenderThis(SDL_Rect* Camera);

};


class Level {
private:
public:
	SDL_Rect* Camera;
	std::vector<Layer*> RenderOrder;
	//for testing purposes
	SDL_Surface* TempTransSurface;

	SDL_Texture* CombinedLower;
	SDL_Texture* CombinedHigher;
	int** CollisionOverride;
	int** CombinedCollision;
	//make use of swap to exchange orders dynamically perhaps.
	int LayerSplit = 1;
	ObjectLayer* SpriteLayer; //replacing PlayerLayer I think.
	SDL_Texture** SpriteTexture;;
	int NumLayers; // this is the number of layers

	int EarlyStop;

	//temp
	int CxVec = 1;//1
	int CyVec = 1;//1
	int CxVel = 0;
	int CyVel = 0;

	int Negit = -1;
	int Posit = 1;

	//Limits of the level
	//0 is implicit
	int yBuff = LEVEL_HEIGHT * TILE_HEIGHT - SCREEN_HEIGHT * TILE_HEIGHT; //the 'limit' space for the 'box' around the player to move.
	int xBuff = LEVEL_WIDTH * TILE_WIDTH - SCREEN_WIDTH * TILE_WIDTH; //the 'limit' space for the camera tracking player to move.
	int yPlayerBuff = SCREEN_HEIGHT * TILE_HEIGHT;
	int xPlayerBuff = SCREEN_WIDTH * TILE_WIDTH;

	int XLcenter;
	int XRcenter;
	int YUcenter;
	int YDcenter;



	Player* Player1;

	//NEW - since we're only rendering a small portion of the layer at any given moment, we want a textuer a bit bigger, with the same perimter buffer
		//for now ignoring the perimeter buffer
	SDL_Texture* CombinedLower2;
	SDL_Texture* CombinedHigher2;
	int PerimeterBuff;
	SDL_Rect* RenderFrame; //This moves forward the perimeter dist, then goes back. However the texture it's grabbing in the renderthis2 is different each time.
	SDL_Rect* MoreWindowRect; //This just holds all the stuff, we then drag render frame around on it.
	int RectWs;
	int RectHs;
	bool ComputedRects;

	Level();
	~Level();

	void PassToObjectLayer() {
		//send info to object layer for it's rendering.
			//basically the player and sprites. We will have to make a super class sprite that contains the player class eventually
		//For now, just treat the player as if it was all this class was doing. 

		//STEPS
		//ObjectLayer - > Combined Objects  <- this is equivelent to our Combined Lower and Combined Higher
		//Now that you have access to this texture, I want you to pass the scrolling information from this Level class
			//down to the ObjectLayer, which will then pass that argument to the player - for now (eventually it'll loop through a heap of sprites)
		//finally I want you to render copy it like we were with combineTextures 


		/*

		 SpriteLayer->CombinedObjects //should already be made for you

		SDL_SetRenderTarget(gRenderer, SpriteTexture); //Will have to set the target back to window after the function finishes.
															//https://wiki.libsdl.org/SDL_SetRenderTarget
															//https://stackoverflow.com/questions/40886350/how-to-connect-multiple-textures-in-the-one-in-sdl2

		//For now just render the player to that texture appropraitely with scrolling+Pos info

		//EVENTUALLY -> Call object layer's sprite vector
			//Player will eventually be in there

		MovePlayer(Targetx, Targety, VecX, VecY) //not sure if this is exactly how we're gonna do it, but something like this
		RenderPlayer //inside moveplayer, put it on the SpriteTexture inside object class

		//Loop for sprite vector looks like that for CombinedLower and layersplite/renderOrder


		SDL_SetRenderTarget(gRenderer, NULL);

		*/


	}
	void CombineTextures();
	void RenderThis();
	void RenderThis2();
	void CreateCamera(int x, int y);
	void MapAllCollision();
	void CreatePlayer();
	void CombineTextures2();
	//vector
	//scroll barriers
	//update player

	//INTO NOW 
	//when sdl_case called
	//check if player moving AT ALL
	//call moves, then if returns 1 at all from those (successful move in some direction) -KEY is that you don't render it until it is time
	//THEN START THE RENDER PROCESS



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

	//NEW - referenced so that the level knows if player is scrolling hte screen. We need two so that its an either or.
	bool Scrollx;
	bool Scrolly;

	//source img
	//width of player
	//height of palyer
	//target x
	//target y
	int xVel;
	int yVel;

	//new
	int xVec;
	int yVec;
	//movement speed (vel x, vel y) - movmeent vector not c vectors :P
	//animations?
	//default spawn location
	//'redraw' position x y
	//'reference' position (to compare to colision space. perhaps the 0,0 of the target tile vs movement tile.
	Player(int DefaultSpawnX, int DefaultSpawnY, int DefaultPixelH, int DefaultPixelW, std::string SourceKey, int SourceCoordx, int SourceCoordy, int SourcePixelH, int SourcePixelW, int xVelocity, int yVelocity);
	~Player();
	bool MoveY(int yVelocity, Level* level);
	bool MoveX(int xVelocity, Level* level);
	bool MoveY2(int yVelocity, Level* level);
	bool MoveX2(int xVelocity, Level* level);
	int getXPos();
	int getYPos();
	void RenderThis(SDL_Texture* CombinedObjects);
	int GetWidth();
	int GetHeight();
};


////////////////////////////////////////////////////////////////////////////////
Level::Level() {
	//printf("LEVEL CREATED!!!!!\n");

	CollisionOverride = new int* [LEVEL_HEIGHT];
	for (int i = 0; i < LEVEL_HEIGHT; i++) {
		CollisionOverride[i] = new int[LEVEL_WIDTH];
	}
	SpriteLayer = new ObjectLayer;
	SpriteTexture = &SpriteLayer->CombinedObjects; //NEW - this should point to the same object - less hassle getting to the texture in level
	//SET BLEND MODE FOR SPRITE TEXTURE?

	CreateCamera(0, 0);

	//for testing purposes
	TempTransSurface = SDL_CreateRGBSurface(0, LEVEL_WIDTH * TILE_WIDTH, LEVEL_HEIGHT * TILE_HEIGHT, 32, 0xff, 0xff00, 0xff0000, 0xff000000);

	CombinedHigher = NULL;
	CombinedLower = NULL;
	NumLayers = 0;
	//in the future if we want multiple players we'll have a pre determined array that can handle additional players. it would be fun to have a wsda and arrow key game.

	EarlyStop = 0; //used to just stop it relatively quickly from rendering more than you want
	//Player1 = NULL;
	CreatePlayer();

	//NEW - for the new rendering methods

	PerimeterBuff = 0;

	CombinedHigher2 = NULL;
	CombinedLower2 = NULL;

	RenderFrame = new SDL_Rect;

	MoreWindowRect = new SDL_Rect;

	//defaults for warning	
	RectWs = 0;
	RectHs = 0;
	//Set to false since above are 0's.
	ComputedRects = false;


	//TextureBuffer= SDL_CreateTexture(gRenderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, LEVEL_WIDTH, LEVEL_HEIGHT);
	//may want to make it only the window but for now who cares.
}
Level::~Level() {
	printf("Deconstructor called for level\n");
}
//old render level position
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


	for (int i = 0; i < LEVEL_HEIGHT; i++) {
		for (int j = 0; j < LEVEL_WIDTH; j++) {
			if (CollisionOverride[i][j] != -1) {
				CombinedCollision[i][j] = CollisionOverride[i][j];
			}
		}
	}

	// now we will go through the collision override and override any collision points in CombinedCollision
}
//Sprite superclass, eventually may want to think about these being part of that instead? 
	//CHECK - think a bit on this later
Player::Player(int DefaultSpawnX, int DefaultSpawnY, int DefaultPixelH, int DefaultPixelW, std::string SourceKey, int SourceCoordx, int SourceCoordy, int SourcePixelH, int SourcePixelW, int xVelocity, int yVelocity) {

	//SurfaceProperty* DefaultSourceSurface = SurfacePropertyMap["SourceName"]->texture;
	 //this is either atexture or a surface. 

	xPos = DefaultSpawnX;
	yPos = DefaultSpawnY;

	SourceName = SourceKey; //AA

	// printf("Init Player\n");
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

	SurfacePropertyMap[SourceName]->GetSelfSurface();


	//change - maybe. 
	//SDL_BlitSurface(SurfacePropertyMap[SourceName]->GetSelfSurface(), SourceTile, TempOrigin, SelfTile);


	//case Temp Origin to a texture
	SelfImg = SDL_CreateTextureFromSurface(gRenderer, TempOrigin);
	SDL_SetTextureBlendMode(SelfImg, SDL_BLENDMODE_BLEND);
	xVel = xVelocity;
	yVel = yVelocity;
	//not sure if your using velocities like the vectors would've been, so I'll swap
	xVec = 0;
	yVec = 0;

	//gLevel1->SpriteLayer->PlayerObject = this; //Now created from NEW - level instead.


	//NEW
	Scrollx = false;
	Scrolly = false;

}
Player::~Player() {
	printf("Destruct Player\n");
}
//void HandleEvent(); //handle collision?
//Returns 1 and 0, for successful move or a moveback respectively. 
// moves the player, moved the camera, detects for collision, detects for level barriers, all along the y-axis. returns 1 if the player icon moves, 0 if not.
bool Player::MoveY(int yVelocity, Level* level) { //move 
	//SDL_Delay(350);

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

	//mid pt reached ??
	if (yPos < (LEVEL_HEIGHT * TILE_HEIGHT) - (SCREEN_HEIGHT * TILE_HEIGHT / 2) && yPos >(SCREEN_HEIGHT * TILE_HEIGHT / 2)) { // this will move camera
		level->Camera->y += yVelocity; // this moves the camera by the yVelocity value
		//TargetTile->y += yVelocity; //NEW
		return 0;
	}
	//mid pt reached
	else if (yPos < (SCREEN_HEIGHT * TILE_HEIGHT / 2) && level->Camera->y > 0) {
		level->Camera->y += yVelocity; // the only situation in which this action takes place is when the camera is moving up; thus yVelocity must be negative, so we are subtracting the camera by adding yVelocity
		TargetTile->y += yVelocity; //NEW
		return 0;
	}
	else if (yPos > (LEVEL_HEIGHT * TILE_HEIGHT) - (SCREEN_HEIGHT * TILE_HEIGHT / 2) && level->Camera->y < LEVEL_HEIGHT * TILE_HEIGHT - SCREEN_HEIGHT * TILE_HEIGHT - 1) { // NEW -- this is for some reason unncessary on x-axis but not y
		level->Camera->y += yVelocity; // the only time when this action happens is when we are moving doown, thus yVelocity would be positive.
		TargetTile->y += yVelocity; //NEW 
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
	//SDL_Delay(350);
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
		//TargetTile->x += xVelocity; //NEW - fixed issue of accelerated movement off screen
		return 0; // the player icon did not move (only the camera)
	}
	else if (xPos < (SCREEN_WIDTH * TILE_WIDTH / 2) && level->Camera->x > 0) { // NEW 
		level->Camera->x += xVelocity;  // this will only happen when we're moving left, thus, xVelocity would be negative. therefore, we are subtracting through addition.
		TargetTile->x += xVelocity; //NEW
		return 0;
	}
	else if (xPos > (LEVEL_WIDTH * TILE_WIDTH) - (SCREEN_WIDTH * TILE_WIDTH / 2) && level->Camera->x < LEVEL_WIDTH * TILE_WIDTH - SCREEN_WIDTH * TILE_WIDTH - 1) { // NEW
		level->Camera->x += xVelocity; // this will only happen when we're moving right, thus, xVelocity would be positive. thus, we are just adding as normal.
		TargetTile->x += xVelocity; //NEW
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
/*
//make a second to handle new target positions, in the event it is changed idk.
void Player::RenderThis() {
	//Test Blitting is very bad, so what actually happens is it automatically wipes the information of the previous surface. So lets try placing a texture over it, and just grabe the texture from the target texture.
	SDL_RenderCopy(gRenderer, SelfImg, NULL, TargetTile);
};
*/
int Player::GetWidth() {
	return SelfTile->w;
}
int Player::GetHeight() {
	return SelfTile->h;
}
bool Player::MoveY2(int yVelocity, Level* level) { //move 
	//SDL_Delay(350);

	yPos += yVelocity;

	if (yVelocity < 0) { // if moving up -- detecting collision
		if (1 == level->CombinedCollision[yPos / TILE_HEIGHT][xPos / TILE_WIDTH] || 1 == level->CombinedCollision[(yPos / TILE_HEIGHT)][(xPos + GetWidth() - 1) / TILE_WIDTH]) {
			// printf("cannot move up!\n");
			//printf(" but collision was found above! cannot move!\n");
			yPos -= yVelocity;
			return 0;
		}
	}

	else if (yVelocity > 0 && yPos < LEVEL_HEIGHT * TILE_HEIGHT - GetHeight()) { // if moving down -- detecting collision -- the second statement is so that it doesn't go through here when its at the edge
		//printf("moving down...");
		if (1 == level->CombinedCollision[(yPos + GetHeight() - 1) / TILE_HEIGHT][xPos / TILE_WIDTH] || 1 == level->CombinedCollision[(yPos + GetHeight() - 1) / TILE_HEIGHT][(xPos + GetWidth() - 1) / TILE_WIDTH]) { // check for right collision
			//printf(" but collision was found below! cannot move!\n");
			yPos -= yVelocity; // reverts the movement change
			// printf("cannot move down!\n");
			return 0; // fails it
		}
	}

	//mid pt reached ??
	if (yPos < (LEVEL_HEIGHT * TILE_HEIGHT) - (SCREEN_HEIGHT * TILE_HEIGHT / 2) && yPos >(SCREEN_HEIGHT * TILE_HEIGHT / 2)) { // this will move camera
		//printf("the camera will be moving instead of the player icon.\n");
		level->Camera->y += yVelocity; // this moves the camera by the yVelocity value
		TargetTile->y += yVelocity; //NEW
		Scrolly = true;
		return 0;
	}
	//mid pt reached
	else if (yPos < (SCREEN_HEIGHT * TILE_HEIGHT / 2) && level->Camera->y > 0) {
		//printf("the camera will be moving instead of the player icon. After this point, the player icon moves up!\n");
		level->Camera->y += yVelocity; // the only situation in which this action takes place is when the camera is moving up; thus yVelocity must be negative, so we are subtracting the camera by adding yVelocity
		TargetTile->y += yVelocity; //NEW
		Scrolly = true;
		return 0;
	}
	else if (yPos > (LEVEL_HEIGHT * TILE_HEIGHT) - (SCREEN_HEIGHT * TILE_HEIGHT / 2) && level->Camera->y < LEVEL_HEIGHT * TILE_HEIGHT - SCREEN_HEIGHT * TILE_HEIGHT - 1) { // NEW -- this is for some reason unncessary on x-axis but not y
		//printf("the camera will be moving instead of the player icon. After this point, the player icon moves down!\n");
		level->Camera->y += yVelocity; // the only time when this action happens is when we are moving doown, thus yVelocity would be positive.
		TargetTile->y += yVelocity; //NEW 
		Scrolly = true;
		return 0;
	}
	else { // this will move the player icon
		if (yPos < 0 || yPos + GetHeight() - 1 >= LEVEL_HEIGHT * TILE_HEIGHT) { // determines if it is in bounds -- if it is not, go through this if statement
			//printf("player icon cannot move without going out of bonuds\n");
			yPos -= yVelocity;
			return 0;
		}
		else {
			//printf("player icon will move!\n");
			TargetTile->y += yVelocity; // actually moves the player
			return 1;
		}
	}
}
// moves the player, moved the camera, detects for collision, detects for level barriers, all along the x-axis. returns 1 if the player icon moves, 0 if not.
bool Player::MoveX2(int xVelocity, Level* level) { //move
	//SDL_Delay(350);
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
		TargetTile->x += xVelocity; //NEW - fixed issue of accelerated movement off screen
		Scrollx = true;
		return 0; // the player icon did not move (only the camera)
	}
	else if (xPos < (SCREEN_WIDTH * TILE_WIDTH / 2) && level->Camera->x > 0) { // NEW 
		level->Camera->x += xVelocity;  // this will only happen when we're moving left, thus, xVelocity would be negative. therefore, we are subtracting through addition.
		TargetTile->x += xVelocity; //NEW
		//Scrollx = true;
		Scrollx = true;
		return 0;
	}
	else if (xPos > (LEVEL_WIDTH * TILE_WIDTH) - (SCREEN_WIDTH * TILE_WIDTH / 2) && level->Camera->x < LEVEL_WIDTH * TILE_WIDTH - SCREEN_WIDTH * TILE_WIDTH - 1) { // NEW
		level->Camera->x += xVelocity; // this will only happen when we're moving right, thus, xVelocity would be positive. thus, we are just adding as normal.
		TargetTile->x += xVelocity; //NEW
		//Scrollx = true;
		Scrollx = true;
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
//these for sure this order and out 
void ObjectLayer::CreatePlayer() {
	int DefaultSpawnX = 32;
	int DefaultSpawnY = 32;
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
	PlayerObject = new Player(DefaultSpawnX, DefaultSpawnY, DefaultPixelH, DefaultPixelW, DefaultSourceName, SourceCoordx, SourceCoordy, SourcePixelH, SourcePixelW, xVelocity, yVelocity);
}
void Level::CreatePlayer() {
	SpriteLayer->CreatePlayer();
	Player1 = SpriteLayer->PlayerObject;
}






void Level::CombineTextures() { //trigger each time a layer is 'hidden' later as a boolean.
		//make new combined texture
		//printf("going through combine textures()\n");

	//Change - we might be able to make combined lower and upper just the size of hte window, or a layer larger (like if window was 5x5, then we'd have a 7x7 so that we have seamless loading and animations, the object layer would be always fully loaded however.
	//change - we want a function to be able to render in black and white collision below the object layer.

	NumLayers = RenderOrder.size();

	LayerSplit = NumLayers; //FOR JACK SPEED


	//Varibales for Testing/display
	int w, h, access;
	unsigned int format;
	unsigned char r, g, b;
	unsigned char alpha;
	SDL_BlendMode Blender;
	SDL_ScaleMode Scale;
	bool DisplayInfo = false;
	bool test = false;

	if (DisplayInfo) {
		//two differences so far, the texture access is advised to be target not static (but static for text from surface, 
		//and blend mode. 1 in surf 0 in text
			//In summary TextFromSurface - access=static, blend=1, CreateTexture - access = Target (by standard for rendering to texture), Blend=0 (none)
		//I changed back to target, since it seemed blend mode was what mattered, and I was right. 
	//alpha controls transparency of a texture, 128 is special*, it's the starting transparency from what I can tell
	//blend is how much trans to give it, (so one is a stock value, the other is a perc?)

		if (LayerSplit <= RenderOrder.size()) {
			printf("Layers are able to split.\n");
		}
		else {
			printf("Layers are able UNABLE to split.\n");
		}
	}



	//keeps the textures from having to much information. 
	if (CombinedLower != NULL) {
		SDL_DestroyTexture(CombinedLower);
	}
	if (CombinedHigher != NULL) {
		SDL_DestroyTexture(CombinedHigher);
	}

	//Combined Lower
	CombinedLower = SDL_CreateTexture(gRenderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_TARGET, LEVEL_WIDTH * TILE_WIDTH, LEVEL_HEIGHT * TILE_HEIGHT);
	//Change Blend Mode to 1
	if (0 == SDL_SetTextureBlendMode(CombinedLower, SDL_BLENDMODE_BLEND)) {
		//none = 0
		// Blend =1
		//SDL_BlendMode Blender = 1;
		//printf("\nChanged Blend Mode of CombinedLower\n");
	}

	SDL_SetRenderTarget(gRenderer, CombinedLower); //Will have to set the target back to window after the function finishes.
														//https://wiki.libsdl.org/SDL_SetRenderTarget
															//https://stackoverflow.com/questions/40886350/how-to-connect-multiple-textures-in-the-one-in-sdl2

	//Loop for Combined Lower
	for (int i = 0; i < LayerSplit; i++) {
		//INSERT - boolean in each Layer for if we want it rendered. 
			//CHANGE - Also only go up to the player, then from above the player to the last layer.
				//CHANGE - bring this check outside, when we declare how many layers total the level will have eventually. Then compare the forloops to the player layer or some thing like that

		//This Grabs all textuers below player, blits to CombinedLower Texture
		if (i <= RenderOrder.size()) {
			SDL_RenderCopy(gRenderer, RenderOrder[i]->SelfHiddenTexture, NULL, NULL); //camera, full window originally, BUT since it may be better to blit and then just move camera, since we're assuming that the levels scroll in sync, for now this is fine. A special layer will bei ntroduced wit hfree scrolling
		}
		else {
			SDL_DestroyTexture(CombinedLower);
			CombinedLower = NULL;
			break;
		}
	}

	SDL_SetRenderTarget(gRenderer, NULL);




	//INSERT - ObjectLayer RenderThis(); -goes through all subobjects (player, sprites) and renders to texture
	//Pass scroll/camera info to object layer, where it will then pass it to it's player object
		//The player object can tehn use its move functions or whatever
			//Then render it to the spritelayer/combiendobjects texture
				//then the texture is all ready to go 
	//render the objects  - may be moved out of this function
	SpriteLayer->RenderThis(Camera); //puts the sprites where they should be on spawn



	//Combined Higher
	CombinedHigher = SDL_CreateTexture(gRenderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_TARGET, LEVEL_WIDTH * TILE_WIDTH, LEVEL_HEIGHT * TILE_HEIGHT);
	//Change Blend Mode to 1
	if (0 == SDL_SetTextureBlendMode(CombinedHigher, SDL_BLENDMODE_BLEND)) {
		//none = 0
		// Blend =1
		//SDL_BlendMode Blender = 1;
		//printf("\nChanged Blend Mode of CombinedLower\n");
	}

	SDL_SetRenderTarget(gRenderer, CombinedHigher);

	//Loop for Combined Higher
	for (int i = LayerSplit; i < RenderOrder.size(); i++) {
		//This Grabs all textures above player, blits to CombiendHigher Texture
		if (i <= RenderOrder.size()) {
			SDL_RenderCopy(gRenderer, RenderOrder[i]->SelfHiddenTexture, NULL, NULL);
		}
		else {
			SDL_DestroyTexture(CombinedLower);
			CombinedLower = NULL;
			break;
		}
	}
	SDL_SetRenderTarget(gRenderer, NULL);

}

void Level::CombineTextures2() {
	printf("Combined. Does it skip?\n");
	//SDL_Delay(500);
	NumLayers = RenderOrder.size();
	LayerSplit = NumLayers; //FOR JACK SPEED
	//printf("Num LAyers = %d\n", NumLayers);

	//change to do just once if possible later
	if (RenderOrder.size() > 0) {
		PerimeterBuff = RenderOrder[0]->PerimeterBuff;
	}
	else {
		PerimeterBuff = 0;
	}


	bool DisplayInfo = false;
	bool test = false;
	if (DisplayInfo) {
		//two differences so far, the texture access is advised to be target not static (but static for text from surface, 
		//and blend mode. 1 in surf 0 in text
			//In summary TextFromSurface - access=static, blend=1, CreateTexture - access = Target (by standard for rendering to texture), Blend=0 (none)
		//I changed back to target, since it seemed blend mode was what mattered, and I was right. 
	//alpha controls transparency of a texture, 128 is special*, it's the starting transparency from what I can tell
	//blend is how much trans to give it, (so one is a stock value, the other is a perc?)

		if (LayerSplit <= RenderOrder.size()) {
			//printf("Layers are able to split.\n");
		}
		else {
			//printf("Layers are able UNABLE to split.\n");
		}
	}
	//keeps the textures from having to much information. 
	if (CombinedLower2 != NULL) {
		SDL_DestroyTexture(CombinedLower2);
	}
	if (CombinedHigher2 != NULL) {
		SDL_DestroyTexture(CombinedHigher2);
	}
	//DIFFERENCES:
	// 	   The Layers each blit each frame
	//	   The player moves, then render player, lower, higher, since camera moves from player movement (usually) - if override camera, we're gonna need a seperate function in Level
	//VITAL - Camera MUST MOVE before Layer's get called to render themselves

	// printf("Render SpriteLayer\n");
	SpriteLayer->RenderThis(Camera); //puts the sprites where they should be on spawn
	//printf("Moved Sprites\n");
	//SDL_Delay(500);
	//NEXT - have each layer redraw themselves 

	/*
	//since player was scrolling before now (since I'm only redrawing when it approaches perimbarrier's width (so it is running out of space to scroll too)
	//We don't need ot limit it this way

	if (Player1->Scrollx || Player1->Scrolly) {
		for (int i = 0; i < RenderOrder.size(); i++) {
			RenderOrder[i]->MakeTextureDependent(Camera); //This needsot be inestigated
		}
		Player1->Scrollx = false;
		Player1->Scrolly = false;
		//printf("MADE EACH LAYER DRAW SELVES\n");
		//SDL_Delay(2000);

	}
	//printf("Had each layer draw themselves\n");
	*/

	printf("Render all textures\n");
	for (int i = 0; i < RenderOrder.size(); i++) {
		RenderOrder[i]->MakeTextureDependent(Camera); //This needsot be inestigated
	}
	//SDL_Delay(500);


	if (true) {
		//Combined Lower
		CombinedLower2 = SDL_CreateTexture(gRenderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_TARGET, (SCREEN_WIDTH + 2 * PerimeterBuff) * TILE_WIDTH, (SCREEN_HEIGHT + 2 * PerimeterBuff) * TILE_HEIGHT);
		//Change Blend Mode to 1
		SDL_SetTextureBlendMode(CombinedLower2, SDL_BLENDMODE_BLEND);
		SDL_SetRenderTarget(gRenderer, CombinedLower2); //Will have to set the target back to window after the function finishes.
															//https://wiki.libsdl.org/SDL_SetRenderTarget
																//https://stackoverflow.com/questions/40886350/how-to-connect-multiple-textures-in-the-one-in-sdl2
		for (int i = 0; i < LayerSplit; i++) {
			//INSERT - boolean in each Layer for if we want it rendered. 
				//CHANGE - Also only go up to the player, then from above the player to the last layer.
					//CHANGE - bring this check outside, when we declare how many layers total the level will have eventually. Then compare the forloops to the player layer or some thing like that

			//This Grabs all textuers below player, blits to CombinedLower Texture
			if (i <= RenderOrder.size()) {
				//Blue line from this?
				SDL_RenderCopy(gRenderer, RenderOrder[i]->TextureDependentTexture, NULL, NULL); //camera, full window originally, BUT since it may be better to blit and then just move camera, since we're assuming that the levels scroll in sync, for now this is fine. A special layer will bei ntroduced wit hfree scrolling
			}
			else {
				SDL_DestroyTexture(CombinedLower2);
				CombinedLower2 = NULL;
				break;
			}
		}
		SDL_SetRenderTarget(gRenderer, NULL);
	}
	if (true) {
		//Combined Higher
		CombinedHigher2 = SDL_CreateTexture(gRenderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_TARGET, (SCREEN_WIDTH + 2 * PerimeterBuff) * TILE_WIDTH, (SCREEN_HEIGHT + 2 * PerimeterBuff) * TILE_HEIGHT);
		//Change Blend Mode to 1
		if (0 == SDL_SetTextureBlendMode(CombinedHigher2, SDL_BLENDMODE_BLEND)) {
			//none = 0
			// Blend =1
			//SDL_BlendMode Blender = 1;
			//printf("\nChanged Blend Mode of CombinedLower\n");
		}
		SDL_SetRenderTarget(gRenderer, CombinedHigher2);
		//Loop for Combined Higher
		for (int i = LayerSplit; i < RenderOrder.size(); i++) {
			//This Grabs all textures above player, blits to CombiendHigher Texture
			if (i <= RenderOrder.size()) {
				SDL_RenderCopy(gRenderer, RenderOrder[i]->TextureDependentTexture, NULL, NULL);
			}
			else {
				SDL_DestroyTexture(CombinedHigher2);
				CombinedHigher2 = NULL;
				break;
			}
		}
		SDL_SetRenderTarget(gRenderer, NULL);
	}
}


void Player::RenderThis(SDL_Texture* CombiendObjects) {
	//render Player ot the object layer texture
	bool test = false;

	//SDL_Delay(1000);
	SDL_SetRenderTarget(gRenderer, CombiendObjects);
	SDL_RenderCopy(gRenderer, SelfImg, NULL, TargetTile);
	//return target to window
	//SDL_RenderClear(gRenderer);
	SDL_SetRenderTarget(gRenderer, NULL);

}
void ObjectLayer::RenderThis(SDL_Rect* Camera) {
	//go throug hall sprites and blit to texture
	bool test = false;
	//NEW - attempt to clear the texture
		//CHANGE - in the future, use update texture to get ride of the sprite locations, or all of them. However this is a slow function.
		//We may want to use a surface and just go from there, that way the user can edit the 'create teture' function to set color modulations or stuff, althoguh that mgiht be done indivudally per object instead. Questions for later
	//printf("ObjectLayer RenderThis\n");





	CombinedObjects = SDL_CreateTexture(gRenderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_TARGET, LEVEL_WIDTH * TILE_WIDTH, LEVEL_HEIGHT * TILE_HEIGHT);
	//maybe it's using hte same memory space, and not reseting it? Try pointer juggling


	//Change Blend Mode to 1 
	SDL_SetTextureBlendMode(CombinedObjects, SDL_BLENDMODE_BLEND);






	PlayerObject->RenderThis(CombinedObjects);



	SDL_SetRenderTarget(gRenderer, NULL);

}
void Level::RenderThis() {
	// SDL_RenderClear(gRenderer);
	//SDL_RenderClear(gRenderer);
	bool test = false;
	// SDL_RenderClear(gRenderer);
	//CombineUltraLayer();
	//give these back to render this
	//NEW Camera used again, I saw the issue is that I was putting only the camera part onto the texture, now the issue is the player is being dragged behind the screen when rendered.


	//CombineTextures();

	//RenderFrame->x += Camera->x %Tile_Width
	SDL_RenderCopy(gRenderer, CombinedLower, Camera, gFullWindowRect);


	SpriteLayer->RenderThis(Camera); //If this function ran, then it must mean player is being moved, that or some other event moved. (Only reason why we'd redraw the screen atm)
	//temp



	//SDL_RenderCopy(gRenderer, *SpriteTexture, Camera, gFullWindowRect); //THIS RENDERS THE PLAYER (Essentially)

	SDL_RenderCopy(gRenderer, SpriteLayer->CombinedObjects, Camera, gFullWindowRect);

	SDL_RenderCopy(gRenderer, CombinedHigher, Camera, gFullWindowRect);


	SDL_RenderPresent(gRenderer);
	SDL_RenderClear(gRenderer);


	//NEW - also clear the various textures we've used.


}
void Level::RenderThis2() {


	//printf("\n\n");

	if (Player1->xPos % (PerimeterBuff * TILE_WIDTH) == 0 && Player1->Scrollx) {
		printf("xPos = %d ", Player1->xPos);
		printf("xPos&PerW ==0\n");
		SDL_Delay(500);
		CombineTextures2();
	}
	/*
	else if (Player1->yPos % (PerimeterBuff * TILE_HEIGHT) == 0) {
		printf("yPos = %d ", Player1->yPos);
		//printf("yPos&PerY ==0\n");
		CombineTextures2();
	}
	*/
	else {
		// printf("SpriteLayer\n");
		SpriteLayer->RenderThis(Camera);
	}


	//will move later
	//since preimeter is just one value we have t odo it indpendently. Although this will get better eventually.
	if (!ComputedRects) {
		RenderFrame->w = (SCREEN_WIDTH + 2 * PerimeterBuff);
		RenderFrame->h = (SCREEN_HEIGHT + 2 * PerimeterBuff); //the minus one was added. 
		while (RenderFrame->w > LEVEL_WIDTH) {
			RenderFrame->w -= 1;
		}
		while (RenderFrame->h > LEVEL_HEIGHT) {
			RenderFrame->h -= 1;
		}
		RenderFrame->w = RenderFrame->w * TILE_WIDTH;
		RenderFrame->h = RenderFrame->h * TILE_HEIGHT;

		MoreWindowRect->w = RenderFrame->w;
		MoreWindowRect->h = RenderFrame->h; //don't forget to add perim to more window rect.
		ComputedRects = true;
	}


	if (Player1->xPos % TILE_WIDTH == 0) {
		printf("%d, %d, %d, %d\n", Player1->xPos, Player1->yPos, Camera->x, Camera->y);
		//SDL_Delay(5000);
	}



	RenderFrame->x = 0;
	RenderFrame->y = 0;

	if (Player1->xVec > 0) {
		// printf("right\n");
		MoreWindowRect->x = (-Camera->x) % TILE_WIDTH;// TILE_WIDTH; //+PerimeterBuff * TILE_WIDTH;
	}
	else if (Player1->xVec < 0 && (-Camera->x) % TILE_WIDTH + (PerimeterBuff * TILE_WIDTH)>0) {
		// printf("Left");
		MoreWindowRect->x = ((-Camera->x - TILE_WIDTH + 1) % TILE_WIDTH) - 16;// -(PerimeterBuff * TILE_WIDTH);// TILE_WIDTH; //+PerimeterBuff * TILE_WIDTH;

	}
	else {
		MoreWindowRect->x = (-Camera->x) % TILE_WIDTH;// TILE_WIDTH; //+PerimeterBuff * TILE_WIDTH;
	}
	if (Player1->yVec > 0) {
		// printf("down\n");
		MoreWindowRect->y = (-Camera->y) % TILE_HEIGHT;// TILE_HEIGHT;// +PerimeterBuff * TILE_HEIGHT; //??	
	}
	else if (Player1->yVec < 0) {
		// printf("Up\n");
		MoreWindowRect->y = (-Camera->y) % TILE_HEIGHT;// TILE_HEIGHT;// +PerimeterBuff * TILE_HEIGHT; //??	

	}
	else {
		MoreWindowRect->y = (-Camera->y) % TILE_HEIGHT;// TILE_HEIGHT;// +PerimeterBuff * TILE_HEIGHT; //??	
	}


	//printf("PERIMETER BUFF IS %d", PerimeterBuff);
	/*
	if (true) {
		printf("Camera  X:%d, Y:%d, W:%d, H:%d\n", Camera->x, Camera->y, Camera->w, Camera->h);
		printf("MoreWin X:%d, Y:%d, W:%d, H:%d\n", MoreWindowRect->x, MoreWindowRect->y, MoreWindowRect->w, MoreWindowRect->h);
		printf("RenderF X:%d, Y:%d, W:%d, H:%d\n", RenderFrame->x, RenderFrame->y, RenderFrame->w, RenderFrame->h);
		printf("FullWin X:%d, Y:%d, W:%d, H:%d\n", gFullWindowRect->x, gFullWindowRect->y, gFullWindowRect->w, gFullWindowRect->h);
		printf("Player1 X:%d, Y:%d, W:%d, H:%d\n", Player1->xPos, Player1->yPos, Player1->GetWidth(), Player1->GetHeight());
		//printf("Combine x:%d, Y:%d, W:%d, H:%d\n", CombinedLower2->x, CombinedLower2->y, CombinedLower2->w, CombinedLower2->h);

		printf("\n");
		//SDL_Delay(500);

		if (Camera->x > 0 || Camera->y > 0) {
			SDL_Delay(1000);
		}

	}
	*/

	SDL_RenderCopy(gRenderer, CombinedLower2, RenderFrame, MoreWindowRect);
	SDL_RenderCopy(gRenderer, SpriteLayer->CombinedObjects, Camera, gFullWindowRect);
	//SDL_RenderCopy(gRenderer, CombinedHigher2, MoreWindowRect, RenderFrame);
	SDL_RenderPresent(gRenderer);
	SDL_RenderClear(gRenderer);

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
				printf("End of file was reached\n");
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
			// printf("finding tile header... \n");

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

				//	= new int[TotalExpected];;
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
						printf("%d placed into TempCollsion, which then is %d, CHECK - %d is at index %d\n \n", d, TempCollisionArr[k], SurfacePropertyMap[SurfacePropertyEnum[counter]]->collision[k], k);
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
					//printf("\n");
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

			// printf("k = %d, x=%d, y=%d\n", k, x, y);

			gLevel1->CollisionOverride[y][x] = d;

			// printf("%d\n", gLevel1->CollisionOverride[y][x]);


			i = 0;
			j++;
			k++;
			x = 0;
			y = 0;

		}
		// printf("\n");
	}
}




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

			//I think it's okay here...
			gLevel1 = new Level;

			if (FoundTileHeader && IsSameString(line.c_str(), "Tiles")) { //Insert - This check may be redudant, but if "Tiles" is not found, throw.
				FoundCollisionOverrideHeader = DrawSavedTiles(sourceIMG, line);
			}

			if (FoundCollisionOverrideHeader && IsSameString(line.c_str(), "Collision Override")) {
				OverrideCollision(sourceIMG, line);
				/*printf("collision override is...\n");
				for (int i = 0; i < LEVEL_HEIGHT; i++) {
					for (int j = 0; j < LEVEL_WIDTH; j++) {
						// printf("%d ", gLevel1->CollisionOverride[i][j]);
					}
					// printf("\n");
				}
				printf("map collision has been called...\n");*/
				gLevel1->MapAllCollision(); // NEW
				/* printf("Combined Collision is...\n");
				for (int i = 0; i < LEVEL_HEIGHT; i++) {
					for (int j = 0; j < LEVEL_WIDTH; j++) {
						// printf("%d ", gLevel1->CombinedCollision[i][j]);
					}
					printf("\n");
				}*/
			}

			//If everything was read as it should be by eof
			if (FoundTileSetHeader && FoundCollisionHeader && FoundTileHeader && FoundCollisionOverrideHeader) {
				// printf("COMBINE TEXTURES\n");

				//CreatePlayer(); // Creates the player
				//gLevel1->CombineTextures();
				//gLevel1->RenderThis(Player1);

			}
			else {
				printf("Dim Throw\n");
			}
		}
		//Close the File
		sourceIMG.close();
		// printf("Trying to make Player\n");

		gLevel1->CreatePlayer();
		gLevel1->CombineTextures2();
	}
}



// function that finds where the center of the camera is; this way, the camera only moves depending on where the player is
void FindCameraCenters(int& XLcenter, int& XRcenter, int& YUcenter, int& YDcenter) {
	// printf("SCREEN WIDTH : %d, SCREEN HEIGHT : %d\n", SCREEN_WIDTH, SCREEN_HEIGHT);
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
	int CxVec = 1;
	int CyVec = 1;
	int CxVel = 0;
	int CyVel = 0;

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

	bool test = false;


	FindCameraCenters(XLcenter, XRcenter, YUcenter, YDcenter);
	// printf("Centers are : XL: %d, XR: %d, YU: %d, YD: %d\n", XLcenter, XRcenter, YUcenter, YDcenter);

	// loop variables
	bool quit = false; // handles the loop; whether we want to quit, or continue
	SDL_Event e; // event handler

	gLevel1->Player1->Scrollx = true;
	gLevel1->Player1->Scrolly = true;

	//printf("Start\n");

	//gLevel1->CombineTextures2(); //Start the screen (needed jsut so that a button press isn't required for starting screen.
	//gLevel1->SpriteLayer->RenderThis(gLevel1->Camera);
	//printf("Initial render done\n");

	gLevel1->RenderThis2();

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
					gLevel1->Player1->yVec -= yVec;
					//CyVel -= CyVec;
					break;
				case SDLK_s: // if the user presses 's'
					yVel += yVec;
					gLevel1->Player1->yVec += yVec;
					//CyVel += CyVec;
					break;
				case SDLK_a: // if the user presses 'a'
					xVel -= xVec;
					gLevel1->Player1->xVec -= xVec;
					//CxVel -= CxVec;
					break;
				case SDLK_d: // if the user presses 'd'
					xVel += xVec;
					gLevel1->Player1->xVec += xVec;
					//CxVel += CxVec;
					break;
				}
			}
			else if (e.type == SDL_KEYUP && e.key.repeat == 0) // if the user releases a key, go through this statement
			{
				switch (e.key.keysym.sym) // Select surfaces based on key press
				{
				case SDLK_w: // if the user releases 'w'
					yVel += yVec;
					gLevel1->Player1->yVec += yVec;
					//CyVel += CyVec;
					break;
				case SDLK_s: // if the user releases 's'
					yVel -= yVec;
					gLevel1->Player1->yVec -= yVec;
					//CyVel -= CyVec;
					break;
				case SDLK_a: // if the user releases 'a'
					xVel += xVec;
					gLevel1->Player1->xVec += xVec;
					//CxVel += CxVec;
					break;
				case SDLK_d: // if the user releases 'd'
					xVel -= xVec;
					gLevel1->Player1->xVec -= xVec;
					//CxVel -= CxVec;
					break;
				}
			}
		}


		if (xVel != 0 || yVel != 0) {

			//I'd like to move these into the level :/ but for now I'll refrain.
			gLevel1->Player1->MoveX2(xVel, gLevel1);
			gLevel1->Player1->MoveY2(yVel, gLevel1);
			//printf("Loop Render\n");
			gLevel1->RenderThis2();
			//printf("Render Complete\n");
		}



		// printing out the player's position
		// printf("xPos %d yPos %d\n", Player1->getXPos(), Player1->getYPos());
		// calculating fps
		float avgFPS = countedFrames / (fpsTimer.getTicks() / 1000.f); // calculates fps
		if (avgFPS > 2000000) { // this is an extremely large fps that may occur at startup; this is not correct, though, so we are putting the avgFPS as 0, instead
			avgFPS = 0;
		}
		++countedFrames; // adds 1 to the countedFrames
		//If frame finished early
		//printf("Average FPS: %f\n", avgFPS); // printf the fps text to the terminal -- CAN BE COMMENTED OUT IF NOT WANTING TO BE DISPLAYED
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
	//std::string MapRepo = UserDirectory() + "600,000.txt";//CHANGE ME - Requires knowing Repo from Save Files
	std::string MapRepo = UserDirectory() + "jacob.txt";

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