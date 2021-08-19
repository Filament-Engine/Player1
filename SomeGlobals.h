#pragma once
#include <SDL.h>

int PAUSECOLLISIONJOSTLE[8] = {0,0,0,0,0,0,0,0};

int TOTALFRAMECOUNT=0;
int TIME = 0; // NEW -- used for randomMove, and likely other things too! functions as a sort of clock

// determines the size of the level
int LEVEL_WIDTH;
int LEVEL_HEIGHT;

// determines the size of the screen
int SCREEN_WIDTH;
int SCREEN_HEIGHT;

// determines the size of the tiles
int TILE_WIDTH;
int TILE_HEIGHT;

// displaying changes
const bool gEnableDelay = false;
bool displayFPS = false;

// fps constants
const int MAX_FPS = 60; // this is the maximum amount of fps we have
const int SCREEN_TICKS_PER_FRAME = 1000 / MAX_FPS; // this converts the fps to ticks

const int SurnameLength = 2;


//From SurfaceMap 
const long int TotalTileOfAllSurfaces = 0;


//Map handles the Offset Tile Total of Surfaces. Prevents having to do forward then backward itteration through a map. 
std::map<std::string, long int> OffSetMap;

std::map<int, std::string> SurfacePropertyEnum; // the numbers that correspond to creation order, where lower numbers are created first and higher numbers later

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
//SDL_Renderer - we will be rendering using the GPU using this renderer.
SDL_Renderer* gRenderer = NULL;


//Struct tree for the first attempt at handling events.
	//Event Order/Diagram
	
//Event arr[] = [Move Button (Player), Collision, Handle Collides, Move (Objects that can move), Collision, Handle Collides, DrawLevel]

//Those above won't actually be in an array, but it will be when we go through the tree, or parts ofthe tree.

//Organizationally, I think I will load all sprites into the tree without distinction (Because Adam's document has only 'sprite').
//Ideally we'd have the ability to 'classify' sprites as a type, like 'npc', 'monster', 'chest', 'unmoving', etc. 
//This would help because we would only need ot go down a narrow bit of hte tree. 

//Or we would give it a bool to see if the page enabled it. Default would be false for all, unless user selected then it's true, and attempts to get the info form the suer input. Not sure how we'd implement however.


//Tree - on object creation. Player as root. - or maybe not....
//Tree's onl useful if I get collision working 
//Make array in Level [LevelWidth*LevelHeight], each object, on move and creation, if x,y %TileV !=0, then CollisionObject[x,y/TileV]=1, and CollisionObject[x,y/TileV  +1] (because it would've rounded down I believe, so throw more collision to its right).
//When putting collision in, if 1 is already at its location, - note it, then afterall the movements, if there is still a 1 in that location 'collide' (2),  if not, write your 1 there.
//Decide how we'll handle collision basedo n that sprite/objects collision. 

//collision order
//Player move, check against Map, check against Objects     - if Collide, wait, but this one should resolve first.
//Object move, check against map, check against Objects     - if Collide, wait until all objects have moved. 

//How to tell which object Collided with what?
//If you hit a 


//[0,0,1,2,1,0,0]
//[Null, Null, $%$, $%$ ->?%$%?, %$%, Null, Null]
//if Arr[position] !=Null (when trying to fill) {
//		Note down the object which you collided with, ->Vector<[Moving Object, Potentialhit Object, ContestedPosition]>
//else {
//      Fill Arr[Position]=this
//}

//Now that all collisions have 'happened',
//go through hte vector, and check 
//	If Arr[ContestedPosition] ==Null {
//		Fill
// }
// Else {
//		Check between the two collision types (This in itself will need a tree to determine which collision takes precedent)
//		If PotentialHit Object.Collisiontype=1;
//		DONT MOVE, Allow it to occupy the position  <- this is tile based for now, but if they collide we can ask deeper like, are their pixels going to occupy the smae or overlapped locations
// }
// 
// 
// 
// 
//




