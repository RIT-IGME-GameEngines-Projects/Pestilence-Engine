#include "hexGridElement.h"

HexGridElement::HexGridElement() {

}

HexGridElement::HexGridElement(char* texture, int height, int x, int y) {
	Texture = texture;
	Height = height;
	X = x;
	Y = y;
}

HexGridElement::~HexGridElement() {

}