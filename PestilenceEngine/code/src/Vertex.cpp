#include "Vertex.h"


Vertex::Vertex()
{
	this->x = 0;
	y = 0;
	z = 0;
}

// Copy constructor
Vertex::Vertex(const Vertex& v)
{
	Vertex a = Vertex(); 
	a.x = v.x; 
	a.y = v.y; 
	a.z = v.z; 
}
Vertex::Vertex(float _x, float _y)
{
	this->x = _x;
	this->y = _y;
	this->z = 0;
}
Vertex::Vertex(float _x, float _y, float _z)
{
	this->x = _x; 
	this->y = _y; 
	this->z = _z;
}

const float Vertex::getX()
{
	if (this->x == NULL)
		return 0;
	else return this->x;
}

const float Vertex::getY()
{
	if (this->y == NULL)
		return 0;
	else return this->y;
}

const float Vertex::getZ()
{
	if (this->z == NULL)
		return 0;
	else return this->z;
}


void Vertex::setX(float _x)
{
	this->x = _x; 
}

void Vertex::setY(float _y)
{
	this->y = _y;
}

void Vertex::setZ(float _z)
{
	this->z = _z;
}

void Vertex::set(Vertex _v)
{
	this->x = _v.getX(); 
	this->y = _v.getY(); 
	this->z = _v.getZ();
}; 


Vertex::~Vertex()
{
}
