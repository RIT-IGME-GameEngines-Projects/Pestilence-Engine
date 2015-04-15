#include "graphics.h"

Graphics::Graphics() {

}

Graphics::~Graphics() {

}

void Graphics::init() {
	program = shaderSetup("../assets/shaders/vshader.glsl", "../assets/shaders/fshader.glsl");
	if (!program) {
		cerr << "Error setting up shaders - " << errorString(shaderErrorCode) << endl;

		exit(1);
	}

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glClearColor(0.0, 0.0, 0.0, 1.0);

	Vector3 vec[] = { Vector3(-.8, -.8, 0), Vector3(1, 1, 0), Vector3(1, -1, 0) };
	spine = new Spline(vec, 3);

	createCube();
	createGCubes();

	cube.loadTexture("../assets/textures/dirt.jpg");
}

void Graphics::render() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glBindBuffer(GL_ARRAY_BUFFER, buffer[0]);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebuffer[0]);

	glUseProgram(program);

	int dataSize = numVerts[0] * 4 * sizeof(float);
	GLuint vPosition = glGetAttribLocation(program, "vPosition");
	glEnableVertexAttribArray(vPosition);
	glVertexAttribPointer(vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

	GLuint vTexCoords = glGetAttribLocation(program, "vTexCoord");
	glEnableVertexAttribArray(vTexCoords);
	glVertexAttribPointer(vTexCoords, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(dataSize));

	cube.setUpTexture(program);
	/*for (int i = 0; i < gCubes.GetSize(); i++)
	{
	gCubes[i].setUpTexture(program);
	}*/

	glDrawElements(GL_TRIANGLES, numVerts[0], GL_UNSIGNED_SHORT, (void*)0);

	glutSwapBuffers();
}

void Graphics::buildGeometryBuffers() {
	NumElements = cube.nVertices();
	float* points = cube.getVertices();
	int dataSize = cube.nVertices() * 4 * sizeof(float);
	float* texCoords = cube.getUV();
	int tdataSize = cube.nVertices() * 2 * sizeof(float);
	GLushort* elements = cube.getIndices();
	int edataSize = cube.nVertices() * sizeof(GLushort);

	glGenBuffers(1, &buffer[0]);
	glBindBuffer(GL_ARRAY_BUFFER, buffer[0]);

	glBufferData(GL_ARRAY_BUFFER, dataSize + tdataSize, 0, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, dataSize, points);
	glBufferSubData(GL_ARRAY_BUFFER, dataSize, tdataSize, texCoords);

	glGenBuffers(1, &ebuffer[0]);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebuffer[0]);

	glBufferData(GL_ELEMENT_ARRAY_BUFFER, edataSize, elements, GL_STATIC_DRAW);

	numVerts[0] = cube.nVertices();
}

void Graphics::createCube() {
	cube = Model(Vector3(0, 0, 0), Vector3(0.2, 0.2, 0.2), Euler3(45, 30, 0));
	cube.clearModel();

	cube.makeCube();
	//cube.makePlane();
	//cube.makeStrip();

	buildGeometryBuffers();
}

void Graphics::createGCubes() {
	for (int i = 0; i < spine->graphPoints->GetSize(); i++)
	{
		Vector3 currPt = *(spine->graphPoints->GetCopyAt(i));
		if (i == 0)
		{
			cube.position.x = currPt.x;
			cube.position.y = currPt.y;
		}
		//Model m = Model();
		//m.clearModel(); 
		//m.makeCube(); 
		//m.translate(currPt.x, currPt.y, currPt.z, program);
		gCubes.Push(currPt);
	}
	buildGeometryBuffers();
}