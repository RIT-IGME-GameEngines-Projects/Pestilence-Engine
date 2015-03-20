#ifndef _SHADERMANAGER_H_
#define _SHADERMANAGER_H_

#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <GL/glew.h>
#include <GL/GL.h>

//Error codes
#define E_NO_ERROR		0
#define E_VS_LOAD		1
#define E_FS_LOAD		2
#define E_VS_COMPILE	3
#define E_FS_COMPILE	4
#define E_SHADER_LINK	5

//Shader error code
extern GLuint shaderErrorCode;

GLchar* read_text_file(const char* name);

void print_shader_info_log(GLuint shader);
void print_program_info_log(GLuint shader);

const char* errorString(GLuint code);

GLuint shaderSetup(const char* vert, const char* frag);

#endif