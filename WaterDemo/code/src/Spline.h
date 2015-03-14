#include <vector>
#include <iostream>
#include <cmath>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "MyVector.h" 
#include "dataStructures\modelStructures.h"


using namespace std;

// Basically every other point will be a "control" 
// That is used to determine what kind of curve will be drawn. 

class Spline
{
public:
	// Basic constructor
	Spline()
	{
		// initialize control points data structure
		this->controlPoints = new MyVector<Vector3*>();
	};

	//Constructor with array of Vector3s
	Spline(Vector3 vec[], int length)
	{
		// initialize vector
		this->controlPoints = new MyVector<Vector3*>(); 
		for (int i = 0; i < length; i++)
		{
			this->addControlPoint(vec[i]);
		}

		this->Print();
	}

	// Destructor
	~Spline();

	// Add a control point to the spline. 
	void addControlPoint(Vector3 _vec)
	{
		// For the first point of the spline, don't add a control point
		if (this->controlPoints->GetSize() == 0)
			this->controlPoints->Push(new Vector3(_vec));
		else
		{
			// Generate a control point - for values, look at the vector currently on top
			// and the vector that we're adding and interpolate a circle that has them both as points
			this->controlPoints->Push(new Vector3(0,0,0));

			// Push the new point
			this->controlPoints->Push(new Vector3(_vec));
		}
	};

	// print out each vertex
	void Print()
	{
		for (int i = 0; i < controlPoints->GetSize(); i++)
		{
			Vector3 vec = *(controlPoints->GetCopyAt(i)); 
			if (i % 2 == 0) std::cout << "P:"; 
			else std::cout << "C:";
			std::cout << "[" <<  vec.x << ", " << vec.y << ", " << vec.z << "]" <<  std::endl; 
		}
	}

	void removeLastPoint()
	{
		// remove last 2: one is a control point dependant on the last actual point
		this->controlPoints->Pop(); 
		this->controlPoints->Pop(); 
	}

	// ignore for now
	void moveControlAt(Vector3 approxArea)
	{

	}
private: 
	MyVector<Vector3*>* controlPoints; // Pointer to MyVector of Vector3s


};


