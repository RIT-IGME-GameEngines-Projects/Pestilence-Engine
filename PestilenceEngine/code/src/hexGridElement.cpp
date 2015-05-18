#include "hexGridElement.h"

HexGridElement::HexGridElement() {

}

HexGridElement::HexGridElement(const string& texture, int height, int x, int z) {
	Texture = texture;
	Height = height;
	X = x;
	Z = z;
}

HexGridElement::~HexGridElement() {

}