#include "model.h"

Model::Model() {

}

Model::~Model() {

}

void Model::clearModel() {
	if (pointArray) {
		delete pointArray;
		delete indexArray;
		delete normalArray;
		delete uvArray;
		pointArray = 0;
		indexArray = 0;
		normalArray = 0;
		uvArray = 0;
	}
	points.clear();
	normals.clear();
	uv.clear();
}

void Model::addTriangle(float x0, float y0, float z0, float u0, float v0,
	float x1, float y1, float z1, float u1, float v1,
	float x2, float y2, float z2, float u2, float v2) {
	points.push_back(x0);
	points.push_back(y0);
	points.push_back(z0);
	points.push_back(1.0);

	points.push_back(x1);
	points.push_back(y1);
	points.push_back(z1);
	points.push_back(1.0);

	points.push_back(x2);
	points.push_back(y2);
	points.push_back(z2);
	points.push_back(1.0);

	// calculate the normal
	float ux = x1 - x0;
	float uy = y1 - y0;
	float uz = z1 - z0;

	float vx = x2 - x0;
	float vy = y2 - y0;
	float vz = z2 - z0;

	float nx = (uy * vz) - (uz * vy);
	float ny = (uz * vx) - (ux * vz);
	float nz = (ux * vy) - (uy * vx);

	// Attach the normal to all 3 vertices
	for (int i = 0; i < 3; i++) {
		normals.push_back(nx);
		normals.push_back(ny);
		normals.push_back(nz);
	}

	// Attach the texture coords
	uv.push_back(u0);
	uv.push_back(v0);
	uv.push_back(u1);
	uv.push_back(v1);
	uv.push_back(u2);
	uv.push_back(v2);
}

int Model::nVertices() {
	return points.size() / 4;
}

float* Model::getVertices() {
	if (pointArray) {
		delete pointArray;
	}

	pointArray = new float[points.size()];
	for (unsigned int i = 0; i < points.size(); i++) {
		pointArray[i] = points[i];
	}

	return pointArray;
}

float* Model::getNormals() {
	if (normalArray) {
		delete normalArray;
	}

	normalArray = new float[normals.size()];
	for (unsigned int i = 0; i < normals.size(); i++) {
		normalArray[i] = normals[i];
	}

	return normalArray;
}

float* Model::getUV() {
	if (uvArray) {
		delete uvArray;
	}

	uvArray = new float[uv.size()];
	for (unsigned int i = 0; i < uv.size(); i++) {
		uvArray[i] = uv[i];
	}

	return uvArray;
}

GLushort* Model::getIndices() {
	if (indexArray) {
		delete indexArray;
	}

	indexArray = new GLushort[points.size()];
	for (unsigned int i = 0; i < points.size(); i++) {
		indexArray[i] = i;
	}

	return indexArray;
}

void Model::makeCube() {
	int subdivisions = 9;

	float width = 1;
	float incremental = (width / 2) / subdivisions * 2;

	struct Point {
		float* x;
		float* y;
	};

	Point* points = new Point[subdivisions];

	for (int i = 0; i < subdivisions; i++){
		points[i].x = new float[subdivisions];
		points[i].y = new float[subdivisions];
	}
	//std::cout << incremental << std::endl;

	float currY = width / 2;

	for (int i = 0; i < subdivisions; i++){
		float currX = width / 2;
		points[i].x[0] = currX;
		points[i].y[0] = currY;
		currX -= incremental;
		for (int j = 1; j < subdivisions; j++){
			points[i].x[j] = currX;
			currX -= incremental;
			points[i].y[j] = currY;
		}
		currY -= incremental;
	}

	//
	for (int i = 0; i < subdivisions; i++){
		for (int j = 0; j < subdivisions; j++){
			float x1 = points[i].x[j];
			float x2 = x1 - incremental;
			float y1 = points[i].y[j];
			float y2 = y1 - incremental;

			float u1 = -(x1 + width / 2);
			float v1 = -(y1 + width / 2);
			float u2 = u1 + incremental;
			float v2 = v1 + incremental;

			//top corner
			//facing Z
			addTriangle(x1, y1, width / 2, u1, v1,
				x2, y1, width / 2, u2, v1,
				x2, y2, width / 2, u2, v2);
			addTriangle(x2, y2, width / 2, u2, v2,
				x1, y2, width / 2, u1, v2,
				x1, y1, width / 2, u1, v1);


			//Facing X
			addTriangle(width / 2, x1, y1, u1, v1,
				width / 2, x2, y1, u2, v1,
				width / 2, x2, y2, u2, v2);
			addTriangle(width / 2, x2, y2, u2, v2,
				width / 2, x1, y2, u1, v2,
				width / 2, x1, y1, u1, v1);

			//Facing Y
			addTriangle(x1, width / 2, y1, u1, v1,
				x1, width / 2, y2, u1, v2,
				x2, width / 2, y2, u2, v2);
			addTriangle(x2, width / 2, y2, u2, v2,
				x2, width / 2, y1, u2, v1,
				x1, width / 2, y1, u1, v1);

			//bot corner
			// Facing Z
			addTriangle(x2, y2, -width / 2, u2, v2,
				x2, y1, -width / 2, u2, v1,
				x1, y1, -width / 2, u1, v1);
			addTriangle(x1, y1, -width / 2, u1, v1,
				x1, y2, -width / 2, u1, v2,
				x2, y2, -width / 2, u2, v2);

			//facing X
			addTriangle(-width / 2, x2, y2, u2, v2,
				-width / 2, x2, y1, u2, v1,
				-width / 2, x1, y1, u1, v1);
			addTriangle(-width / 2, x1, y1, u1, v1,
				-width / 2, x1, y2, u1, v2,
				-width / 2, x2, y2, u2, v2);

			//facing Y
			addTriangle(x2, -width / 2, y2, u2, v2,
				x1, -width / 2, y2, u1, v2,
				x1, -width / 2, y1, u1, v1);
			addTriangle(x1, -width / 2, y1, u1, v1,
				x2, -width / 2, y1, u2, v1,
				x2, -width / 2, y2, u2, v2);
		}
	}
}

void Model::makePlane() {
	int subdivisions = 3;

	float width = 1;
	float incremental = (width / 2) / subdivisions * 2;

	struct Point {
		float* x;
		float* y;
	};

	Point* points = new Point[subdivisions];

	for (int i = 0; i < subdivisions; i++){
		points[i].x = new float[subdivisions];
		points[i].y = new float[subdivisions];
	}
	//std::cout << incremental << std::endl;

	float currY = width / 2;

	for (int i = 0; i < subdivisions; i++){
		float currX = width / 2;
		points[i].x[0] = currX;
		points[i].y[0] = currY;
		currX -= incremental;
		for (int j = 1; j < subdivisions; j++){
			points[i].x[j] = currX;
			currX -= incremental;
			points[i].y[j] = currY;
		}
		currY -= incremental;
	}

	//
	for (int i = 0; i < subdivisions; i++){
		for (int j = 0; j < subdivisions; j++){
			float x1 = points[i].x[j];
			float x2 = x1 - incremental;
			float y1 = points[i].y[j];
			float y2 = y1 - incremental;

			float u1 = -(x1 + width / 2);
			float v1 = -(y1 + width / 2);
			float u2 = u1 + incremental;
			float v2 = v1 + incremental;

			//top corner
			//facing Z
			/*addTriangle(x1, y1, width / 2, u1, v1,
				x2, y1, width / 2, u2, v1,
				x2, y2, width / 2, u2, v2);
			addTriangle(x2, y2, width / 2, u2, v2,
				x1, y2, width / 2, u1, v2,
				x1, y1, width / 2, u1, v1);


			//Facing X
			addTriangle(width / 2, x1, y1, u1, v1,
				width / 2, x2, y1, u2, v1,
				width / 2, x2, y2, u2, v2);
			addTriangle(width / 2, x2, y2, u2, v2,
				width / 2, x1, y2, u1, v2,
				width / 2, x1, y1, u1, v1);*/

			//Facing Y
			addTriangle(x1, width / 2, y1, u1, v1,
				x1, width / 2, y2, u1, v2,
				x2, width / 2, y2, u2, v2);
			addTriangle(x2, width / 2, y2, u2, v2,
				x2, width / 2, y1, u2, v1,
				x1, width / 2, y1, u1, v1);
		}
	}
}

void Model::loadTexture(char* filename) {
	GLuint texture = SOIL_load_OGL_texture(
		filename,
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_TEXTURE_REPEATS
	);

	if (texture == 0) {
		printf("SOIL loading error: '%s'\n", SOIL_last_result());
	}

	glActiveTexture(GL_TEXTURE0 + 0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
}

void Model::setUpTexture(GLuint program){
	glUseProgram(program);
	
	GLuint textureLoc = glGetUniformLocation(program, "texture");
	GLuint colorLoc = glGetUniformLocation(program, "vColor");
	GLuint theta = glGetUniformLocation(program, "theta");

	float angles[3] = { 30.0, 30.0, 0.0 };
	glUniform3fv(theta, 1, angles);

	GLfloat color[4] = { 1.0, 1.0, 1.0, 1.0 };
	glUniform1i(textureLoc, 0);
	glUniform4fv(colorLoc, 1, color);
}