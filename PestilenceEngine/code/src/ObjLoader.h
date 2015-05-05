#ifndef _OBJLOADER_H_
#define _OBJLOADER_H_

#include "Triangle.h" 
#include <iostream> 
#include <fstream> 
#include <string>
#include <vector>

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/GL.h>

#include "dataStructures/modelStructures.h"
#include "../extern/glm/glm.hpp"

using namespace std; 
using namespace glm;

// OBJ Loader: Can read in files and generate game meshes with it. 
class ObjLoader
{
public:
	ObjLoader()
	{
		std::cout << "Obj loader created." << std::endl;
		//readFile("models/cube.obj");
	};

	void readFile(const char* filename,
		vector<vec3> &out_vertices,
		vector<vec2> &out_uvs,
		vector<vec3> &out_normals)
	{
		vector<unsigned int> vertexIndices, uvIndices, normalIndices;
		vector<vec3> temp_verts;
		vector<vec2> temp_uvs;
		vector<vec3> temp_norms;

		FILE* file = fopen(filename, "r"); 
		if (file == NULL)
		{
			std::cout << "Unable to open file " << filename << "." << std::endl;
			return;
		}
		while (1)
		{
			char lineHeader[256];
			// First word of the line
			int res = fscanf(file, "%s", lineHeader);
			if (res == EOF)
				break;
			else // parse lineHeader
			{
				if (strcmp(lineHeader, "v") == 0)
				{
					float a; float b; float c;
					fscanf(file, "%f %f %f\n", &a, &b, &c);
					vec3 v = vec3(a, b, c);
					temp_verts.push_back(v);
				}
				else if (strcmp(lineHeader, "vt") == 0)
				{
					float a; float b;
					fscanf(file, "%f %f\n", &a, &b);
					vec2 uv = vec2(a, b);
					temp_uvs.push_back(uv);
				}
				else if (strcmp(lineHeader, "vn") == 0)
				{
					float x; float y; float z;
					fscanf(file, "%f %f %f\n", &x, &y, &z);
					vec3 n = vec3(x, y, z);
					temp_norms.push_back(n);
				}
				else if (strcmp(lineHeader, "f") == 0)
				{
					GLuint vIndex[3], uvIndex[3], nIndex[3];
					string v1, v2, v3;
					int indices = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n",
						&vIndex[0], &uvIndex[0], &nIndex[0],
						&vIndex[1], &uvIndex[1], &nIndex[1],
						&vIndex[2], &uvIndex[2], &nIndex[2]);
					if (indices != 9) {
						cout << "File can't be read." << endl;
						return;
					}
					vertexIndices.push_back(vIndex[0]);
					vertexIndices.push_back(vIndex[1]);
					vertexIndices.push_back(vIndex[2]);

					uvIndices.push_back(uvIndex[0]);
					uvIndices.push_back(uvIndex[1]);
					uvIndices.push_back(uvIndex[2]);

					normalIndices.push_back(nIndex[0]);
					normalIndices.push_back(nIndex[1]);
					normalIndices.push_back(nIndex[2]);
				}
			}
		}

		for (unsigned int i = 0; i < vertexIndices.size(); i++) {
			GLuint vIndex = vertexIndices[i] - 1;
			vec3 vert = temp_verts[vIndex];
			out_vertices.push_back(vert);
		}
		for (unsigned int i = 0; i < uvIndices.size(); i++) {
			GLuint uvIndex = uvIndices[i] - 1;
			vec2 uv = temp_uvs[uvIndex];
			out_uvs.push_back(uv);
		}
		for (unsigned int i = 0; i < normalIndices.size(); i++) {
			GLuint nIndex = normalIndices[i] - 1;
			vec3 normal = temp_norms[nIndex];
			out_normals.push_back(normal);
		}
	}

	//void readFile(char* filename, vector<Triangle>* triangles)
	//{
	//	// Crete temporary vars for verts, uvs and normals
	//	vector<Vertex*> temp_verts; 
	//	vector<Vertex*> temp_uvs; 
	//	vector<Vertex*> temp_norms;
	//	vector<FaceIndices> temp_faces;
	//	const char* path = filename;
	//	//FILE* file = fopen_s(path, "r"); 
	//	FILE** file = new FILE*();
	//	fopen_s(file, path, "r");
	//	if (file == NULL)
	//	{
	//		std::cout << "Unable to open file " << filename << "." << std::endl;
	//		return;
	//	}
	//	while (1)
	//	{
	//		char lineHeader[128];
	//		// First word of the line
	//		int res = fscanf(*file, "%s", lineHeader); 
	//		if (res == EOF)
	//			break;
	//		else // parse lineHeader
	//		{
	//			if (strcmp(lineHeader, "v") == 0)
	//			{
	//				float a; float b; float c; 
	//				fscanf(*file, "%f %f %f\n", &a, &b, &c);
	//				Vertex* v = new Vertex(a, b, c);
	//				std::cout << "Vertex found: ";  v->print();
	//				temp_verts.push_back(v);
	//			}
	//			else if (strcmp(lineHeader, "vt") == 0)
	//			{
	//				float a; float b; 
	//				fscanf(*file, "%f %f\n", &a, &b);
	//				Vertex* v = new Vertex(a, b); 
	//				std::cout << "UV found: ";  v->print();
	//				temp_uvs.push_back(v); 
	//			}
	//			else if (strcmp(lineHeader, "vn") == 0)
	//			{ 
	//				float x; float y; float z;
	//				fscanf(*file, "%f %f %f\n", &x, &y, &z);
	//				Vertex* n = new Vertex(x, y, z); 
	//				std::cout << "Normal found: ";  n->print();
	//				temp_norms.push_back(n);
	//			}
	//			else if (strcmp(lineHeader, "f") == 0)
	//			{
	//				float v1, v2, v3;
	//				float t1, t2, t3;
	//				float n1, n2, n3;
	//				char p1[10];
	//				char p2[10];
	//				char p3[10];
	//				fscanf(*file, "%s %s %s\n", &p1, &p2, &p3);
	//				
	//				string p1s = string(p1);
	//				string p2s = string(p2);
	//				string p3s = string(p3);

	//				vector<string> psplit;
	//				boost::split(psplit, p1s, boost::is_any_of("/"));
	//				v1 = stof(psplit[0]);
	//				t1 = stof(psplit[1]);
	//				n1 = stof(psplit[2]);
	//				
	//				boost::split(psplit, p2s, boost::is_any_of("/"));
	//				v2 = stof(psplit[0]);
	//				t2 = stof(psplit[1]);
	//				n2 = stof(psplit[2]);

	//				boost::split(psplit, p3s, boost::is_any_of("/"));
	//				v3 = stof(psplit[0]);
	//				t3 = stof(psplit[1]);
	//				n3 = stof(psplit[2]);
	//				
	//				FaceIndices f = FaceIndices(v1-1, v2-1, v3-1,
	//											t1-1, t2-1, t3-1,
	//											n1-1, n2-1, n3-1);

	//				std::cout << "Face Indices Found: "; f.print();
	//				temp_faces.push_back(f);
	//			}
	//		}

	//		
	//	}
	//	// Now that we have the verts, textures, and norms
	//	// Create triangles and then push them to a mesh
	//	for (unsigned int i = 0; i < temp_faces.size(); i++) {
	//		Triangle tri = Triangle(temp_verts[temp_faces[i].v1],
	//								temp_verts[temp_faces[i].v2],
	//								temp_verts[temp_faces[i].v3],
	//								temp_norms[temp_faces[i].n1],
	//								temp_norms[temp_faces[i].n2],
	//								temp_norms[temp_faces[i].n3],
	//								temp_uvs[temp_faces[i].t1],
	//								temp_uvs[temp_faces[i].t2],
	//								temp_uvs[temp_faces[i].t3]);
	//		triangles->push_back(tri);
	//	}

	//};
	~ObjLoader();
};

#endif