attribute vec4 vPosition;
attribute vec2 vTexCoord;

uniform vec3 theta;

uniform vec4 vColor;

varying vec4 color;
varying vec2 texCoord;

uniform mat4 rotation;

void main()
{   
	color = vColor;
	texCoord = vTexCoord;
    //gl_Position = vPosition;
	vec3 angles = radians (theta);
    vec3 c = cos (angles);
    vec3 s = sin (angles);
    
    // rotation matrices
    mat4 rx = mat4 (1.0,  0.0,  0.0,  0.0, 
                    0.0,  c.x,  s.x,  0.0,
                    0.0, -s.x,  c.x,  0.0,
                    0.0,  0.0,  0.0,  1.0);
                    
    mat4 ry = mat4 (c.y,  0.0, -s.y,  0.0, 
                    0.0,  1.0,  0.0,  0.0,
                    s.y,  0.0,  c.y,  0.0,
                    0.0,  0.0,  0.0,  1.0);

    mat4 rz = mat4 (c.z, s.z,  0.0,  0.0, 
                    -s.z,  c.z,  0.0,  0.0,
                    0.0,  0.0,  1.0,  0.0,
                    0.0,  0.0,  0.0,  1.0);
          
    
	//gl_Position = rotation * vPosition;
    gl_Position = rz * ry * rx * vPosition;
}
