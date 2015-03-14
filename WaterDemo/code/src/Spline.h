#include <vector>
#include <iostream>
#include <cmath>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "MyVector.h" 
#include "dataStructures\modelStructures.h"
#define MATH_PI 3.14

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
		this->graphPoints = new MyVector<Vector3*>();
	};

	//Constructor with array of Vector3s
	Spline(Vector3 vec[], int length)
	{
		// initialize vector
		this->controlPoints = new MyVector<Vector3*>(); 
		this->graphPoints = new MyVector<Vector3*>();
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
			this->controlPoints->Push(
				new Vector3(generateControlPoint((*this->controlPoints->GetTop()), _vec)));

			// Push the new point
			this->controlPoints->Push(new Vector3(_vec));
		}
	};

	void generateGraphPts()
	{
		this->graphPoints->Release();
		float increment = .001; 
		for (int i = 0; i < (this->controlPoints->GetSize()-2); i+=2)
		{
			// for each "curve"; e.g. [0,1,2], [2,3,4]
			Vector3 s = *(this->controlPoints->GetCopyAt(i));
			Vector3 m = *(this->controlPoints->GetCopyAt(i+1));
			Vector3 f = *(this->controlPoints->GetCopyAt(i+2));
			for (float j = s.x; j < f.x; j += increment)
			{
				// draw points along the curve
				// this DEFINITELY needs to get fixed but we'll see where it goes for now
				float xPt = ((1 + cos(MATH_PI + j * MATH_PI)) / 2);

				float yPt = ((1 + sin(MATH_PI + j * MATH_PI)) / 2);
				this->graphPoints->Push(new Vector3(xPt, yPt, 0));
			}

		}
	}
	// we will ignore z for now
	Vector3 generateControlPoint(Vector3 start, Vector3 end)
	{
		// make a standard kind of control point
		// this will be the average between the two plus
		// half the largest dimension distance between them
		// in the axis that has the least distance between them
		float xDist = fabs( start.x - end.x );
		float yDist = fabs(start.y - end.y);

		float gDist;
		enum axis { XAX, YAX };
		axis gAxis;
		// get greatest distance - the average of the axis points will be the halfway pt
		gDist = xDist; gAxis = XAX;
		if (yDist > gDist){ gDist = yDist; gAxis = YAX;}

		Vector3 cPoint; // our returnable
		switch (gAxis)
		{
			case XAX: 
				cPoint.x = start.x + (.5 * gDist); 
				cPoint.y = start.y + (.5 * yDist); 
			case YAX: 
				cPoint.y = start.y + (.5 * gDist);
				cPoint.x = start.x + (.5 * xDist);
		}
		cPoint.z = 0; 
		generateGraphPts(); // generate graph points
		return cPoint;

	};

	// print out each vertex - for debugging
	void Print()
	{
		for (int i = 0; i < controlPoints->GetSize(); i++)
		{
			Vector3 vec = *(controlPoints->GetCopyAt(i)); 
			if (i % 2 == 0) std::cout << "P:"; 
			else std::cout << "C:";
			std::cout << "[" <<  vec.x << ", " << vec.y << ", " << vec.z << "]" <<  std::endl; 
		}

		for (int i = 0; i < graphPoints->GetSize(); i++)
		{
			Vector3 vec = *(graphPoints->GetCopyAt(i));
			std::cout << "Graph: [" << vec.x <<", " << vec.y << "]" << std::endl;
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
	MyVector<Vector3*>* controlPoints; // Pointer to MyVector of Vector3s
	MyVector<Vector3*>* graphPoints; // pointer to myVector of Vector3s representing points along the bezier curved spline

};


