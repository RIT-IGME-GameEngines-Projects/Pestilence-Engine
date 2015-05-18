#ifndef _HEXGRIDELEMENT_H_
#define _HEXGRIDELEMENT_H_

class HexGridElement {
public:
	HexGridElement();
	HexGridElement(char* texture, int height, int x, int z);
	~HexGridElement();

	char* Texture;
	int Height;
	int X;
	int Y;
};

#endif