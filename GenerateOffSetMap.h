#pragma once
#include<map>
#include<string>
#include "SurfaceProperty.h"

//Necessary for Surface Creation
long int GenerateOffSetMap(std::map<std::string, SurfaceProperty*>* SurfacePropertyMap) {
	long int Offset = 0;
	for (auto p : *SurfacePropertyMap) {
		// printf("OFFSET INSERTED IS %d FOR %s\n", Offset, p.first.c_str());
		OffSetMap.insert(std::make_pair(p.first, Offset));
		Offset += p.second->GetTotalTile(); //accumulates
	}

	return Offset; //should have still accumulated the total amount of tiles, but only assigned up to the last surfaces worth
}