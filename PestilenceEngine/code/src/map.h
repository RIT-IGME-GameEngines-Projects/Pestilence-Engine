#ifndef _MAP_H_
#define _MAP_H_

#include <vector>

#include "mapBuilder.h"
#include "model.h"

using namespace std;

class Map {

public:
	static Map& instance();

	void readMap(char* filename);

	void buildHexGeometryBuffers(GLuint program);

	void renderHex(GLuint program);

	~Map();

private:
	Map();

	void buildHexMap();

	vector<HexGridElement> hexElements;
	MapBuilder builder;

	Model hexModelPrefab;

	vector<Model> hexModels;
};

#endif