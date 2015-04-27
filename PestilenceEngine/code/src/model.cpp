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

}

void Model::loadModel(char* filename) {
	ObjLoader* loader = new ObjLoader();
	loader->readFile(filename, vertices, uvs, normals);
}

void Model:: buildGeometryBuffers() {
	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vec3), &vertices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &uvBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
	glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(vec2), &uvs[0], GL_STATIC_DRAW);
}

void Model::render(GLuint program) {
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glVertexAttribPointer(
		0,
		3, 
		GL_FLOAT,
		GL_FALSE,
		0,
		(void*)0
	);

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
	glVertexAttribPointer(
		1,
		2,
		GL_FLOAT,
		GL_FALSE,
		0, 
		(void*)0
	);

	glDrawArrays(GL_TRIANGLES, 0, vertices.size());
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
	scalem.x = x;
	scalem.y = y;
	scalem.z = z;

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

