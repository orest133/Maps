#pragma once
#include <vector>
#include "WorldMapCoordinates.h"

#include <Windows.h>
using namespace std;
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

