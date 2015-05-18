#ifndef _HEXGRIDELEMENT_H_
#define _HEXGRIDELEMENT_H_

#include <iostream> 
#include <string>

using namespace std;

class HexGridElement {
public:
	HexGridElement();
	HexGridElement(const string& texture, int height, int x, int z);
	~HexGridElement();

	string Texture;
	int Height;
	int X;
	int Z;
};

#endif