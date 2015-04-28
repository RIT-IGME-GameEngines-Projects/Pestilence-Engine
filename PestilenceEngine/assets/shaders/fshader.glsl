#version 330 core

in vec2 UV;

out vec3 color;

uniform sampler2D textureSampler;

void main()
{
	//color = vec3(1,0,0);
	color = texture2D(textureSampler, UV).rgb;
}