#version 330 core

in vec2 UV;
in vec3 w_position;
in vec3 c_normal
in vec3 c_eyeDir;
in vec3 c_lightDir;

out vec3 color;

uniform sampler2D textureSampler;
uniform vec3 w_lightPos;
uniform vec3 lightColor;
uniform float lightPower;

void main()
{
	// Material properties
	vec3 DiffuseColor = texture2D(textureSampler, UV).rgb;
	vec3 AmbientColor = vec3(0.1, 0.1, 0.1) * DiffuseColor;
	vec3 SpecularColor = vec3(0.3, 0.3, 0.3);

	// Distance to light
	float distance = length(w_lightPos - w_position);

	// Normal to computed fragment
	vec3 n = normalize(c_normal);
	// Direction of light
	vec3 l = normalize(c_lightDir);

	float cosTheta = clamp(dot(n,l), 0, 1);

	// Eye vector
	vec3 E = normalize(c_eyeDir);
	// Reflection angle
	vec3 R = reflect(-l, n);

	float cosAlpha - clamp(dot(E,R), 0, 1);

	color = AmbientColor + 
			DiffuseColor * lightColor * lightPower * cosTheta / (distance*distance) + 
			SpecularColor * lightColor * lightPower * pow(cosAlpha, 5) / (distance*distance);
}

// REFERENCE: https://code.google.com/p/opengl-tutorial-org/source/browse/tutorial08_basic_shading/StandardShading.fragmentshader