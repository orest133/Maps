#pragma once
#include <vector>
#include "WorldMapCoordinates.h"
class MapData
{
public:
	MapData();
	static float scaleX; 
	static float scaleY;
	 std::vector<WorldMapCoordinates> worldMapCoordinateAll;
	 std::vector<WorldMapCoordinates> worldMapCoordinate;
	void loadDataMap() ;
	void selectDataMap();

};

