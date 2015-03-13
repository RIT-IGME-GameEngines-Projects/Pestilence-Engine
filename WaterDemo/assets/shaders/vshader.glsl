attribute vec4 vPosition;
attribute vec2 vTexCoord;

uniform vec4 vColor;

varying vec4 color;
varying vec2 texCoord;

uniform mat4 translation;
uniform mat4 rotation;

void main()
{   
	color = vColor;
	texCoord = vTexCoord;
          
	gl_Position = translation * rotation * vPosition;
}
