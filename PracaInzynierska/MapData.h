#pragma once
#include <vector>
#include "WorldMapCoordinates.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <glm/gtc/type_ptr.hpp>
#define GLEW_STATIC
#include <GL/glew.h>

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
	void drowMap(float x, float  y, glm::mat4 model, GLint modelLoc, int index); 

};

