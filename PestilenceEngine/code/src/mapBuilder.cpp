#include "mapBuilder.h"

MapBuilder::MapBuilder() {

}

MapBuilder::~MapBuilder() {

}

void MapBuilder::readMap(char* filename) {
	FILE* file = fopen(filename, "r");

	std::vector<HexGridElement> tempGridElements;

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
			cout << lineHeader << endl;
			if (strcmp(lineHeader, "hex") == 0)
			{
				char texture[32];
				int height;
				int x;
				int y;
				fscanf(file, "%s %d %d %d\n", texture, &height, &x, &y);

				HexGridElement hex = HexGridElement(texture, height, x, y);
				tempGridElements.push_back(hex);
			}
		}
	}
}