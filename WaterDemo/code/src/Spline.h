#include <vector>
#include <iostream>
#include <cmath>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "dataStructures\matrix4.h"
#include "dataStructures\quaternion.h"
#include "dataStructures\modelStructures.h"
#include "MyVector.h" 

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
			this->controlPoints->Push(new Vector3(/*interpolation*/));

			// Push the new point
			this->controlPoints->Push(new Vector3(_vec));
		}
	};

	void removeLastPoint()
	{
		// remove last 2: one is a control point dependant on the last actual point
		this->controlPoints->Pop(); 
		this->controlPoints->Pop(); 
	}

	void moveControlAt(Vector3 approxArea)
	{

	}
private: 
	MyVector<Vector3*>* controlPoints; // Pointer to MyVector of Vector3s


};

