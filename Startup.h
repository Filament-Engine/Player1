#pragma once
#include<SDL.h>
#include<stdio.h>
// initializes SDL
bool init()// SDL_Window* Window, SDL_Surface* ScreenSurface, SDL_Renderer* Renderer)
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		success = false;
	}
	else {
		if (TTF_Init() == -1)
		{
			printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
			success = false;
		}
		//Create window
		gWindow = SDL_CreateWindow("Filament Engine", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH*TILE_WIDTH, SCREEN_HEIGHT*TILE_HEIGHT, SDL_WINDOW_SHOWN);
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