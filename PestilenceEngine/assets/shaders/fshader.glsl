varying vec4 color;
varying vec2 texCoord;

uniform sampler2D texture;

void main() 
{ 
  gl_FragColor = color * texture2D(texture, texCoord);
} 

//#version 330 core

//in vec2 UV;

//out vec3 color;

//uniform sampler2D textureSampler;

//void main()
//{
//	color = texture2D(textureSampler, UV).rgb;
//}