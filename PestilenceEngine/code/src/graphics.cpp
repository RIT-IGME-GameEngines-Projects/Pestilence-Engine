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
	glDepthFunc(GL_LESS);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	//Vector3 vec[] = { Vector3(-.8, -.8, 0), Vector3(1, 1, 0), Vector3(1, -1, 0) };
	//spine = new Spline(vec, 3);

	createCube();
	//createGCubes();
	buildGeometryBuffers();
}

void Graphics::render() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram(program);

	mat4 mvp = Camera::instance().MVP();
	glUniformMatrix4fv(m_MVPLoc, 1, GL_FALSE, &mvp[0][0]);

	cube.loadTexture("../assets/textures/t_crate.jpg");

	cube.render(program);

	/*glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);
	glVertexAttribPointer(
		0,
		3,
		GL_FLOAT,
		GL_FALSE,
		0,
		(void*)0
	);

	glDrawArrays(GL_TRIANGLES, 0, 3);

	glDisableVertexAttribArray(0);*/

	glutSwapBuffers();
}

void Graphics::buildGeometryBuffers() {
	/*glGenVertexArrays(1, &m_VertexArray);
	glBindVertexArray(m_VertexArray);

	m_MVPLoc = glGetUniformLocation(program, "MVP");

	static const GLfloat vertices[] = {
		-1.0f, -1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		0.0f, 1.0f, 0.0f
	};

	glGenBuffers(1, &m_VertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);*/
	cube.buildGeometryBuffers();
}

void Graphics::createCube() {
	/*cube = Primitive(Vector3(0, 0, 0), Vector3(0.2, 0.2, 0.2), Euler3(45, 30, 0));
	cube.clearPrimitive();
	cube.makeCube();
	buildGeometryBuffers();*/

	cube = Model(Vector3(0, 0, 0), Vector3(0.2, 0.2, 0.2), Euler3(45, 30, 0));
	cube.clearModel();
	cube.loadModel("../assets/models/sm_crate.obj");
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