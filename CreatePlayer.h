#pragma once
#include "Level+.h"
#include "SurfaceProperty.h"
#include <map>
#include <string>
// creates the player class; this is the default that we currently are using
void CreatePlayer(Player** player, Level* level, std::map<std::string, SurfaceProperty*> SPMap) {
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
	*player = new Player(DefaultSpawnX, DefaultSpawnY, DefaultPixelH, DefaultPixelW, DefaultSourceName, SourceCoordx, SourceCoordy, SourcePixelH, SourcePixelW, xVelocity, yVelocity, SPMap, level);
};