#version 330 core

// m_ = modelspace
// w_ = worlspace
// c_ = cameraspace

layout(location = 0) in vec3 m_position;
layout(location = 1) in vec2 m_uv;
layout(location = 2) in vec3 m_normal;

out vec2 UV;
out vec3 w_position;
out vec3 c_normal;
out vec3 c_eyeDir;
out vec3 c_lightDir;

uniform mat4 MVP;
uniform mat4 V;
uniform mat4 M;
uniform mat4 m_translation;
uniform mat4 m_rotation;
uniform mat4 m_scale;
uniform vec3 w_lightPos;

void main()
{   
	// Output position
	gl_Position = MVP * m_translation * m_rotation * vec4(m_position, 1);

	// Position of vertex in worldspace
	w_position = (M * vec4(m_position,1)).xyz;

	// Vector from vertex to camera
	vec3 c_position = (V * M * vec4(m_position, 1)).xyz;
	c_eyeDir = vec3(0,0,0) - c_position;

	// Vector from vertex to light
	vec3 c_lightPos = (V * vec4(w_lightPos, 1)).xyz;
	c_lightDir = c_lightPos + c_eyeDir;

	// Normal of the vertex
	c_normal = (V * M * vec4(m_normal,0)).xyz;

	// UV of vertex
	UV = m_uv;
}

// REFERENCE: https://code.google.com/p/opengl-tutorial-org/source/browse/tutorial08_basic_shading/StandardShading.vertexshader