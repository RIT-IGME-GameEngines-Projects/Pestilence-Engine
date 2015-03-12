#include "shaderManager.h"

GLuint shaderErrorCode;

GLchar* read_text_file(const char* name) {
	FILE* fp;
	GLchar* content = NULL;
	int count = 0;

	if (name != NULL) {
		fp = fopen(name, "r");
		if (fp != NULL) {
			fseek(fp, 0, SEEK_END);
			count = ftell(fp);
			rewind(fp);

			if (count > 0) {
				content = new GLchar[sizeof(GLchar) * (count + 1)];

				count = fread(content, sizeof(GLchar), count, fp);
				content[count] = '\0';
			}
			fclose(fp);
		}
		else {
			perror(name);
		}
	} 
	else {
		fprintf(stderr, "error: no file name specified\n");
	}

	return content;
}

void print_shader_info_log(GLuint shader) {
	GLint length = 0;
	GLsizei nchars = 0;
	char *log;

	// Determine the length of the information log
	glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);

	if (length > 0) {
		log = new char[length];

		if (log != NULL) {
			glGetShaderInfoLog(shader, length, &nchars, log);

			if (log[0] != '\0') {
				printf("Shader log: '%s'\n", log);
			}

			delete [] log;
		}
		else {
			printf("Shader log non-empty, but allocate failed\n");
		}
	}
}

void print_porgram_info_log(GLuint shader) {
	GLint length = 0;
	GLsizei nchars = 0;
	char* log;

	glGetProgramiv(shader, GL_INFO_LOG_LENGTH, &length);

	if (length > 0) {
		log = new char[length];

		if (log != NULL) {
			glGetProgramInfoLog(shader, length, &nchars, log);

			if (log[0] != '\0') {
				printf("Program log: '%s'\n", log);
			}

			delete [] log;
		}
		else {
			printf("Program log non-empty, but allocate failed\n");
		}
	}
}

const char* errorString(GLuint code) {
	const char* msg;
	static char buffer[256];

	switch (code) {
		case E_NO_ERROR:
			msg = "No Error";
			break;
		case E_VS_LOAD:
			msg = "Error loading vertex shader";
			break;
		case E_FS_LOAD:
			msg = "Error loading fragment shader";
			break;
		case E_VS_COMPILE:
			msg = "Error compiling vertex shader";
			break;
		case E_FS_COMPILE:
			msg = "Error compiling fragment shader";
			break;
		case E_SHADER_LINK:
			msg = "Error linking shader";
			break;
		default:
			sprintf(buffer, "Unknown error code %d", code);
			msg = (const char*)buffer;
	}

	return msg;
}

GLuint shaderSetup(const char* vert, const char* frag) {
	GLchar *vsrc = NULL, *fsrc = NULL;
	GLuint vs, fs, prog;
	GLint flag;

	shaderErrorCode = E_NO_ERROR;

	GLenum err = glewInit();

	vs = glCreateShader(GL_VERTEX_SHADER);
	fs = glCreateShader(GL_FRAGMENT_SHADER);

	vsrc = read_text_file(vert);
	if (vsrc == NULL) {
		fprintf(stderr, "Error reading vertex shader file '%s'\n", vert);
		shaderErrorCode = E_VS_LOAD;
		return 0;
	}

	fsrc = read_text_file(frag);
	if (fsrc == NULL) {
		fprintf(stderr, "Error reading fragment shader file '%s'\n", frag);
		shaderErrorCode = E_FS_LOAD;
		delete [] vsrc;
		return 0;
	}

	glShaderSource(vs, 1, (const GLchar**)&vsrc, NULL);
	glShaderSource(fs, 1, (const GLchar**)&fsrc, NULL);

	delete [] vsrc;
	delete [] fsrc;

	glCompileShader(vs);
	glGetShaderiv(vs, GL_COMPILE_STATUS, &flag);
	print_shader_info_log(vs);
	if (flag == GL_FALSE) {
		shaderErrorCode = E_VS_COMPILE;
		return 0;
	}

	glCompileShader(fs);
	glGetShaderiv(fs, GL_COMPILE_STATUS, &flag);
	print_shader_info_log(fs);
	if (flag == GL_FALSE) {
		shaderErrorCode = E_FS_COMPILE;
		return 0;
	}

	prog = glCreateProgram();
	glAttachShader(prog, vs);
	glAttachShader(prog, fs);

	//print_program_info_log(prog);

	glLinkProgram(prog);
	glGetProgramiv(prog, GL_LINK_STATUS, &flag);
	//print_program_info_log(prog);
	if (flag == GL_FALSE) {
		shaderErrorCode = E_SHADER_LINK;
		return 0;
	}

	return prog;
}