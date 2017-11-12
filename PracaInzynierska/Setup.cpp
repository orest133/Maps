#include "Setup.h"



Setup::Setup()
{
}


Setup::~Setup()
{
}
void Setup::loadDate()
{
	string  data[4] ;
	ifstream in("res/setup/setup.txt");

	if (!in) {
	//	cout << "Cannot open input file.\n";
	}

	char str[255];
	while (in) {
		in.getline(str, 255);  // delim defaults to '\n'
		//if (in) cout << str << endl;

	}

	in.close();

}
float Setup::startingPointX = 680032;
float Setup::startingPointY = 222647;

float Setup::endPointX = 699366;
float Setup::endPointY = 200251;