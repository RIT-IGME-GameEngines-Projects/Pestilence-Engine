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
		Model hex = Model(hexModelPrefab);
		string texturePath = "../assets/textures/t_" + hexElements[i].Texture + ".jpg";
		const char* texture = texturePath.c_str();
		cout << texture << endl;
		hex.loadTexture((char*)texture);
		hex.translate(hexElements[i].X * 9, hexElements[i].Height * 2, hexElements[i].Z * 9);
		hexModels.push_back(hex);
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