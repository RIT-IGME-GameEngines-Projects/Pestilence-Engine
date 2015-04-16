#include "model.h"

Model::Model() {
	srand(time(NULL));

	angles = Euler3(45, 30, 0);
	scalem = Vector3(0.1, 0.1, 0.1);
	position = Vector3();

	rotx = QuaternionX::euler(angles.yaw, angles.pitch, angles.roll);
}

Model::Model(Vector3 pos, Vector3 scal, Euler3 angle) {
	srand(time(NULL));

	angles = angle;
	scalem = scal;
	position = pos;

	rotx = QuaternionX::euler(angles.yaw, angles.pitch, angles.roll);
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

void Model::loadModel(char* filename) {
	ObjLoader* loader = new ObjLoader();
	loader->readFile(filename);
}

void Model::addTriangle(float x0, float y0, float z0, float u0, float v0,
	float x1, float y1, float z1, float u1, float v1,
	float x2, float y2, float z2, float u2, float v2) {
	points.push_back(x0);
	points.push_back(y0);
	points.push_back(z0);
	points.push_back(1.0);

	Point p0; p0.x = x0; p0.y = y0; p0.z = z0; p0.w = 1.0f;

	points.push_back(x1);
	points.push_back(y1);
	points.push_back(z1);
	points.push_back(1.0);

	Point p1; p1.x = x1; p1.y = y1; p1.z = z1; p1.w = 1.0f;

	points.push_back(x2);
	points.push_back(y2);
	points.push_back(z2);
	points.push_back(1.0);

	Point p2; p2.x = x2; p2.y = y2; p2.z = z2; p2.w = 1.0f;

	Point* fPoints = new Point[3]; fPoints[0] = p0; fPoints[1] = p1; fPoints[2] = p2;

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

	Normal* fNormals = new Normal[3];

	// Attach the normal to all 3 vertices
	for (int i = 0; i < 3; i++) {
		normals.push_back(nx);
		normals.push_back(ny);
		normals.push_back(nz);

		Normal n; n.x = nx; n.y = ny; n.z = nz;
		fNormals[i] = n;
	}

	// Attach the texture coords
	uv.push_back(u0);
	uv.push_back(v0);
	uv.push_back(u1);
	uv.push_back(v1);
	uv.push_back(u2);
	uv.push_back(v2);

	UV uv0; uv0.u = u0; uv0.v = v0;
	UV uv1; uv1.u = u1; uv0.v = v1;
	UV uv2; uv2.u = u2; uv2.v = v2;

	UV* fUVs = new UV[3]; fUVs[0] = uv0; fUVs[1] = uv1; fUVs[2] = uv2;

	Face face; face.points = fPoints; face.normals = fNormals; face.uvs = fUVs;
	faces.push_back(face);
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
	//cout << points.size() << endl;
	for (unsigned int i = 0; i < points.size(); i++) {
		indexArray[i] = i;
	}

	return indexArray;
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

	GLfloat color[4] = { 1.0, 1.0, 1.0, 1.0 };
	glUniform1i(textureLoc, 0);
	glUniform4fv(colorLoc, 1, color);

	translate(0, 0, 0, program);
	rotate(0, 0, 0, program);
	scale(0, 0, 0, program);
}

void Model::translate(float x, float y, float z, GLuint program)
{
	position.x += x;
	position.y += y;
	position.z += z;

	Matrix4 transMat = Matrix4::Translate(position.x, position.y, position.z);
	float* transMat4 = Matrix4::ToMat4(transMat);

	GLuint translateLoc = glGetUniformLocation(program, "translation");
	glUniformMatrix4fv(translateLoc, 1, false, transMat4);
}

void Model::scale(float x, float y, float z, GLuint program) 
{
	scalem.x += x;
	scalem.y += y;
	scalem.z += z;

	Matrix4 scaleMat = Matrix4::Scale(scalem.x, scalem.y, scalem.z);
	float* scaleMat4 = Matrix4::ToMat4(scaleMat);

	GLuint scaleLoc = glGetUniformLocation(program, "scale");
	glUniformMatrix4fv(scaleLoc, 1, false, scaleMat4);
}

void Model::rotate(float yaw, float pitch, float roll, GLuint program) {
	angles.yaw += yaw;
	angles.pitch += pitch;
	angles.roll += roll;

	QuaternionX rotTo = QuaternionX::euler(angles.yaw, angles.pitch, angles.roll);
	QuaternionX slerped = QuaternionX::slerp(rotx.quatData, rotTo.quatData, 0);
	Matrix4 rotMat = QuaternionX::toMatrix(slerped.quatData);
	float* rotMat4 = Matrix4::ToMat4(rotMat);
	rotx = rotTo;

	GLuint rotationLoc = glGetUniformLocation(program, "rotation");
	glUniformMatrix4fv(rotationLoc, 1, false, rotMat4);
}

