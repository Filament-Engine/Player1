#pragma once
#include <SDL.h>
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
