using namespace std; 
#include <iostream>
class Vertex
{
public:
	// Default constructor: Set values to 0. 
	Vertex();

	// Copy Constructor
	Vertex(const Vertex& v);

	// All three points initialized
	Vertex(float _x, float _y, float _z);
	// 2D version: Initialize x and y, z is set to 0
	Vertex(float _x, float _y);

	// Destructor
	~Vertex();

	// Getters for individual values
	const float& getX(); 
	const float& getY(); 
	const float& getZ(); 

	// Getter for all three values
	const Vertex& get()
	{
		return *this;
	};

	// Setter
	void setX(float); 
	void setY(float); 
	void setZ(float); 

	void set(Vertex); 

	void print()
	{
		cout << "[x: " << this->getX() << ", y: " << this->getY() << ", z: " << this->getZ() << "]" << std::endl;
	};

private: 
	float* x = nullptr;
	float* y = nullptr;
	float* z = nullptr;
};

