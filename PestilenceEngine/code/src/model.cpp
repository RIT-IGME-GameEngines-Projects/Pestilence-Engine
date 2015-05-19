#include "model.h"

Model::Model() {
	srand(time(NULL));

	angles = Euler3(0, 0, 0);
	scalem = Vector3(1, 1, 1);
	position = Vector3();

	rotx = QuaternionX::euler(angles.yaw, angles.pitch, angles.roll);

	translate(0, 0, 0);
	scale(0, 0, 0);
	rotate(0, 0, 0);
}

Model::Model(const Model& other) {
	angles = other.angles;
	scalem = other.scalem;
	position = other.position;

	rotx = QuaternionX::euler(angles.yaw, angles.pitch, angles.roll);

	translate(0, 0, 0);
	scale(0, 0, 0);
	rotate(0, 0, 0);

	vertices = other.vertices;
	uvs = other.uvs;
	normals = other.normals;

	texture = other.texture;
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
	cout << "Read model file" << endl;
}

void Model::buildGeometryBuffers(GLuint program) {
	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vec3), &vertices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &uvBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
	glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(vec2), &uvs[0], GL_STATIC_DRAW);

	glGenBuffers(1, &normalBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
	glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(vec3), &normals[0], GL_STATIC_DRAW);
}

void Model::render(GLuint program, bool lit) {
	mat4 mvp = Camera::instance().MVP();
	mat4 m = Camera::instance().World();
	mat4 v = Camera::instance().View();

	//m = m_Translate * m_Rotation * m_Scale * m;

	vec3 lightPos = LightManager::instance().Sun().Position();
	vec3 lightColor = LightManager::instance().Sun().Color();
	float lightPower = LightManager::instance().Sun().Power();

	glUniformMatrix4fv(Camera::instance().MVPLoc(), 1, GL_FALSE, &mvp[0][0]);
	glUniformMatrix4fv(Camera::instance().MLoc(), 1, GL_FALSE, &m[0][0]);
	glUniformMatrix4fv(Camera::instance().VLoc(), 1, GL_FALSE, &v[0][0]);

	glUniformMatrix4fv(Camera::instance().TranslateLoc(), 1, GL_FALSE, &m_Translate[0][0]);
	glUniformMatrix4fv(Camera::instance().RotateLoc(), 1, GL_FALSE, &m_Rotation[0][0]);
	glUniformMatrix4fv(Camera::instance().ScaleLoc(), 1, GL_FALSE, &m_Scale[0][0]);

	glUniform3f(LightManager::instance().Sun().DirLoc(), lightPos.x, lightPos.y, lightPos.z);
	glUniform3f(LightManager::instance().Sun().ColorLoc(), lightColor.x, lightColor.y, lightColor.z);
	glUniform1f(LightManager::instance().Sun().PowerLoc(), lightPower);

	GLuint litLoc = glGetUniformLocation(program, "isLit");
	glUniform1i(litLoc, lit);

	setUpTexture(program);

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
		1,                                // attribute
		2,                                // size
		GL_FLOAT,                         // type
		GL_FALSE,                         // normalized?
		0,                                // stride
		(void*)0                          // array buffer offset
		);

	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
	glVertexAttribPointer(
		2,
		3,
		GL_FLOAT,
		GL_FALSE,
		0,
		(void*)0
	);

	glDrawArrays(GL_TRIANGLES, 0, vertices.size());
	
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
}

void Model::loadTexture(char* filename) {
	texture = SOIL_load_OGL_texture(
		filename,
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_TEXTURE_REPEATS
	);

	if (texture == 0) {
		printf("SOIL loading error: '%s'\n", SOIL_last_result());
	}
	
	//GLuint textureLoc = glGetUniformLocation()
}

void Model::setUpTexture(GLuint program){
	glUseProgram(program);
	
	GLuint textureLoc = glGetUniformLocation(program, "textureSampler");

	glActiveTexture(GL_TEXTURE0 + 0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glUniform1i(textureLoc, 0);

	/*translate(0, 0, 0, program);
	rotate(0, 0, 0, program);
	scale(0, 0, 0, program);*/
}

void Model::translate(float x, float y, float z)
{
	position.x += x;
	position.y += y;
	position.z += z;

	Matrix4 transMat = Matrix4::Translate(position.x, position.y, position.z);
	m_Translate = Matrix4::ToMat4(transMat);
}

void Model::scale(float x, float y, float z) 
{
	scalem.x = x;
	scalem.y = y;
	scalem.z = z;

	Matrix4 scaleMat = Matrix4::Scale(scalem.x, scalem.y, scalem.z);
	m_Scale = Matrix4::ToMat4(scaleMat);
}

void Model::rotate(float yaw, float pitch, float roll) {
	angles.yaw += yaw;
	angles.pitch += pitch;
	angles.roll += roll;

	QuaternionX rotTo = QuaternionX::euler(angles.yaw, angles.pitch, angles.roll);
	QuaternionX slerped = QuaternionX::slerp(rotx.quatData, rotTo.quatData, 0);
	Matrix4 rotMat = QuaternionX::toMatrix(slerped.quatData);
	m_Rotation = Matrix4::ToMat4(rotMat);
	rotx = rotTo;
}

