#include "map.h"

Map::Map() {
	builder = MapBuilder();

	hexModelPrefab = Model();
	hexModelPrefab.clearModel();
	hexModelPrefab.loadModel("../assets/models/sm_hexTile.obj");
	hexModelPrefab.loadTexture("../assets/textures/t_hexTile_Fallback.png");

	skyBox = SkyBox();
	skyBox.buildSkyBox("../assets/textures/t_skyBox.png");
}

Map::~Map() {

}

Map& Map::instance() {
	static Map instance;
	return instance;
}

void Map::readMap(char* filename) {
	builder.readMap(filename, hexElements);
	buildHexMap();
}

void Map::buildHexMap() {

	for (int i = 0; i < hexElements.size(); i++) {
		
		string texturePath = "../assets/textures/t_" + hexElements[i].Texture + ".jpg";
		const char* texture = texturePath.c_str();
		float x;
		float z;
		if (hexElements[i].Z % 2 == 1) {
			x = hexElements[i].X * 14;
			z = hexElements[i].Z * 4;
		}
		else {
			x = 7 + (hexElements[i].X * 14);
			z = hexElements[i].Z * 4;
			
		}

		Model hex = Model(hexModelPrefab);
		hex.loadTexture((char*)texture);
		hex.translate(x, 0, z);
		hexModels.push_back(hex);
		/*for (int y = 0; y < hexElements[i].Height; y++) {
			Model hex = Model(hexModelPrefab);
			hex.loadTexture((char*)texture);
			hex.translate(x, y * 2, z);
			hexModels.push_back(hex);
		}*/
		//cout << hexElements[i].Texture << endl;
	}
}

void Map::buildHexGeometryBuffers(GLuint program)  {
	for (int i = 0; i < hexModels.size(); i++) {
		hexModels[i].buildGeometryBuffers(program);
	}
	skyBox.buildSkyBoxBuffers(program);
}

void Map::renderHex(GLuint program) {
	for (int i = 0; i < hexModels.size(); i++) {
		hexModels[i].render(program, true);
	}
	skyBox.renderSkyBox(program);
}