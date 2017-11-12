#include "MapData.h"

float MapData::scaleX;
float MapData::scaleY;



MapData::MapData()
{
	loadDataMap();
	selectDataMap();
	scaleX = worldMapCoordinate[0].getTopRightX() - worldMapCoordinate[0].getTopLeftX();
	scaleY = worldMapCoordinate[0].getBottomLeftY() - worldMapCoordinate[0].getTopLeftY();
}

void MapData::loadDataMap()
{
	vector<string> pathsToTifFile;
	WIN32_FIND_DATA FindFileData;
	HANDLE hf;
	hf = FindFirstFile("maps/*.tif", &FindFileData);
	if (hf != INVALID_HANDLE_VALUE)
	{
		do
		{
			pathsToTifFile.push_back(FindFileData.cFileName);
		} while (FindNextFile(hf, &FindFileData) != 0);
		FindClose(hf);
	}

	string pathTmp;
	string prefix = "maps/";
	for (vector<string>::iterator path = pathsToTifFile.begin(); path != pathsToTifFile.end(); ++path)
	{
		pathTmp = prefix + path->data();
		const char* c = pathTmp.c_str();
		worldMapCoordinateAll.push_back(WorldMapCoordinates(c));
	}
	
}

void MapData::selectDataMap()
{
	for (vector<WorldMapCoordinates>::iterator map = worldMapCoordinateAll.begin(); map != worldMapCoordinateAll.end(); ++map) {
		if (map->getTopLeftX() >= Setup::startingPointX && map->getTopLeftX() <= Setup::endPointX )
			if( map->getTopLeftY() <= Setup::startingPointY && map->getTopLeftY() >= Setup::endPointY)
		{
			worldMapCoordinate.push_back(*map);
		}
		
	}
}

