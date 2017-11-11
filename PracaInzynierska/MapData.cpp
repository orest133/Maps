#include "MapData.h"

float MapData::scaleX;
float MapData::scaleY;

MapData::MapData()
{
	loadDataMap();
	selectDataMap();
	scaleX= worldMapCoordinate[1].getTopRightX() - worldMapCoordinate[1].getTopLeftX();
	scaleY = worldMapCoordinate[1].getBottomLeftY() - worldMapCoordinate[1].getTopLeftY();
}

void MapData::loadDataMap()
{
	worldMapCoordinateAll.push_back(WorldMapCoordinates("maps/M-34-080-C-d-1-1.tif"));
   worldMapCoordinateAll.push_back(WorldMapCoordinates("maps/M-34-080-C-d-1-2.tif"));
	worldMapCoordinateAll.push_back(WorldMapCoordinates("maps/M-34-080-C-d-1-3.tif"));
	worldMapCoordinateAll.push_back(WorldMapCoordinates("maps/M-34-080-C-d-1-4.tif"));
	
}

void MapData::selectDataMap()
{
	worldMapCoordinate.push_back(WorldMapCoordinates("maps/M-34-080-C-d-1-1.tif"));
   worldMapCoordinate.push_back(WorldMapCoordinates("maps/M-34-080-C-d-1-2.tif"));
	worldMapCoordinate.push_back(WorldMapCoordinates("maps/M-34-080-C-d-1-3.tif"));
	worldMapCoordinate.push_back(WorldMapCoordinates("maps/M-34-080-C-d-1-4.tif"));
}

