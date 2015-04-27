attribute vec4 vPosition;
attribute vec2 vTexCoord;

uniform vec4 vColor;

varying vec4 color;
varying vec2 texCoord;

uniform mat4 translation;
uniform mat4 rotation;
uniform mat4 scale;

void main()
{   
	color = vColor;
	texCoord = vTexCoord;
          
	gl_Position = translation * rotation * scale * vPosition;
}


//#version 330 core

//layout(location = 0) in vec3 vertexPosition_modelspace;
//layout(location = 1) in vec2 vertexUV;

//out vec2 UV;

//uniform mat4 MVP;

//void main()
//{   
//	gl_Position = MVP * vec4(vertexPosition_modelspace, 1);

//	UV = vertexUV;
//}
