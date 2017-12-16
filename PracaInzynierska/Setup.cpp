#include "Setup.h"



Setup::Setup()
{
}


Setup::~Setup()
{
}
void Setup::loadDate()
{
	vector<string> dataFromSetup;
	ifstream in("res/setup/setup.txt");
	if (!in) {
	cout << "Cannot open input file.\n";
	}
	char str[255];

	while (in) {
		in.getline(str, 255); 
		 dataFromSetup.push_back(std::string(str));	
	}
	in.close();
	string tmp = dataFromSetup[0].substr(dataFromSetup[0].find('=')+1, dataFromSetup[0].length());
	startingPointX= (float)atof(dataFromSetup[0].substr(dataFromSetup[0].find('=') + 1, dataFromSetup[0].length()).c_str());
	startingPointY= (float)atof(dataFromSetup[1].substr(dataFromSetup[1].find('=') + 1, dataFromSetup[1].length()).c_str());
	endPointX= (float)atof(dataFromSetup[2].substr(dataFromSetup[2].find('=') + 1, dataFromSetup[2].length()).c_str());
	endPointY= (float)atof(dataFromSetup[3].substr(dataFromSetup[3].find('=') + 1, dataFromSetup[3].length()).c_str());

	in.open("res/setup/dataDronePosition2.txt");
	if (!in) {
		cout << "Cannot open input file.\n";
	}
	
	while (in) {
		in.getline(str, 255);
		tmp = string(str);	

		if (tmp.find("X:")==0) {
			tmp = tmp.substr(tmp.find('X') + 3, tmp.length());
			positionXFromFile.push_back((float)atof(tmp.c_str()));
		}
		if (tmp.find("Y:")==0) {
			tmp = tmp.substr(tmp.find('Y') + 3, tmp.length());
			positionYFromFile.push_back((float)atof(tmp.c_str()));
		}
		if (tmp.find("H:") == 0) {
			tmp = tmp.substr(tmp.find('H') + 3, tmp.length());
			positionHFromFile.push_back((float)atof(tmp.c_str()));
		}
		if (tmp.find("D:") == 0) {
			tmp = tmp.substr(tmp.find('D') + 3, tmp.length());
			positionDFromFile.push_back((float)atof(tmp.c_str()));
		}

	}
	in.close();
	std::reverse(positionXFromFile.begin(), positionXFromFile.end());
	std::reverse(positionYFromFile.begin(), positionYFromFile.end());
	std::reverse(positionHFromFile.begin(), positionHFromFile.end());
	std::reverse(positionDFromFile.begin(), positionDFromFile.end());


} 
float Setup::startingPointX = 0;
float Setup::startingPointY = 0;

float Setup::endPointX = 0;
float Setup::endPointY = 0;

vector<float> Setup::positionXFromFile;
vector<float> Setup::positionYFromFile;
vector<float> Setup::positionHFromFile;
vector<float> Setup::positionDFromFile;