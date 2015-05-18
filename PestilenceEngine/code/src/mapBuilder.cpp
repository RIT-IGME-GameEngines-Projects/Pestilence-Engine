#include "mapBuilder.h"

MapBuilder::MapBuilder() {

}

MapBuilder::~MapBuilder() {

}

void MapBuilder::readMap(char* filename, vector<HexGridElement> &outElements) {
	FILE* file = fopen(filename, "r");

	if (file == NULL)
	{
		std::cout << "Unable to open file " << filename << "." << std::endl;
		return;
	}

	while (1)
	{
		char lineHeader[256];
		// First word of the line
		int res = fscanf(file, "%s", lineHeader);
		if (res == EOF)
			break;
		else // parse lineHeader
		{
			if (strcmp(lineHeader, "hex") == 0)
			{
				char texture[32];
				int height;
				int x;
				int z;
				fscanf(file, "%s %d %d %d\n", texture, &height, &x, &z);

				HexGridElement hex = HexGridElement(texture, height, x, z);
				outElements.push_back(hex);
			}
		}
	}
}