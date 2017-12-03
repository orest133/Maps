#pragma once
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
class Setup
{
public:
	Setup();
	~Setup();
	static float startingPointX ;
	static float startingPointY ;
	static float endPointX;
	static float endPointY;
	static void loadDate();
	static vector<float> positionXFromFile;
	static vector<float> positionYFromFile;
	static vector<float> positionHFromFile;
	static vector<float> positionDFromFile;
};

