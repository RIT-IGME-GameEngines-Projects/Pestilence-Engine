#ifndef _MAPBUILDER_H_
#define _MAPBUILDER_H_

#include <iostream> 
#include <fstream> 
#include <string>
#include <vector>
#include "hexGridElement.h"

using namespace std;

class MapBuilder
{
public:
	MapBuilder();
	~MapBuilder();

	void readMap(char* filename);
};

#endif