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

class Spline
{
public:
	// Basic constructor
	Spline();

	// Destructor
	~Spline();

private: 
	Vector3** controlPoints;
};

