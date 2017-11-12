#pragma once
#include <iostream>
#include <fstream>
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
};

