#pragma once
// clears the SurfacePropertyMap
void FreeMapSurfaces(std::map<std::string, SurfaceProperty*>* SurfacePropertyMap) {

	//EDIT - Memory management happens here too.

	//INSERT call to delete tiles in the hash, then delete the hash

	//DANGEROUS - delete this seemd to break it!
	for (auto p : *SurfacePropertyMap) {
		p.second -> ~SurfaceProperty();
	}

	SurfacePropertyMap->clear();
	//clear all textures, and surfaces, and the global hidden's. - Unknown if this releases the memory of those objects. Assume it does not.

	//https://stackoverflow.com/questions/6952083/deleting-self-object-inside-class 
	//If object made through 'new', we should be able to deconstruct with delete this* like the others
}

//Closes everything out on the window - Deletes all Surfaces.
void close(Level* level, Player* player, std::map<std::string, SurfaceProperty*>* SurfacePropertyMap)
{
	//Deallocate surfaces, textures, sdl_rects, tiles, tilehash, etc. Anything in a data structure should be deallocated in this function.
	printf("close has been called...\n");
	FreeMapSurfaces(SurfacePropertyMap);

	//insert another function to destruct every tile in our map

	//insert another function/thing to destruct our renderer, unless it is destroyed by destroyWindow as well -like the surface of the window.

	//Destroy window -AGAIN CHECK IF THE SURFACE THAT 'GOT' IT IS DEALLOCATED SOMEHOW
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;


	level->~Level();

	player->~Player();

	//Quit SDL subsystems
	//Quit SDL_Image
	IMG_Quit();
	//Quit SDL
	SDL_Quit();
}

