#include "Triangle.h" 
#include <iostream> 
#include <fstream> 
#include <string>
#include <vector>

#include "dataStructures/modelStructures.h"

using namespace std; 

// OBJ Loader: Can read in files and generate game meshes with it. 
class ObjLoader
{
public:
	ObjLoader()
	{
		std::cout << "Obj loader created." << std::endl;
		//readFile("models/cube.obj");
	};

	void readFile(char* filename)
	{
		// Crete temporary vars for verts, uvs and normals
		vector<Vertex> temp_verts; 
		vector<Vertex> temp_uvs; 
		vector<Vertex> temp_norms;
		vector<FaceIndices> temp_faces;
		const char* path = filename;
		//FILE* file = fopen_s(path, "r"); 
		FILE** file = new FILE*();
		fopen_s(file, path, "r");
		if (file == NULL)
		{
			std::cout << "Unable to open file " << filename << "." << std::endl;
			return;
		}
		while (1)
		{
			char lineHeader[128];
			// First word of the line
			int res = fscanf(*file, "%s", lineHeader); 
			if (res == EOF)
				break;
			else // parse lineHeader
			{
				if (strcmp(lineHeader, "v") == 0)
				{
					float a; float b; float c; 
					fscanf(*file, "%f %f %f\n", &a, &b, &c);
					Vertex v = Vertex(a, b, c);
					std::cout << "Vertex found: ";  v.print();
					temp_verts.push_back(v);
				}
				else if (strcmp(lineHeader, "vt") == 0)
				{
					float a; float b; 
					fscanf(*file, "%f %f\n", &a, &b);
					Vertex v = Vertex(a, b); 
					std::cout << "UV found: ";  v.print();
					temp_uvs.push_back(v); 
				}
				else if (strcmp(lineHeader, "vn") == 0)
				{ 
					float x; float y; float z;
					fscanf(*file, "%f %f %f\n", &x, &y, &z);
					Vertex n = Vertex(x, y, z); 
					std::cout << "Normal found: ";  n.print();
					temp_norms.push_back(n);
				}
				else if (strcmp(lineHeader, "f") == 0)
				{
					float v1, v2, v3;
					float t1, t2, t3;
					float n1, n2, n3;
					char p1[10];
					char p2[10];
					char p3[10];
					fscanf(*file, "%s %s %s\n", &p1, &p2, &p3);
					
					string p1s = string(p1);
					string p2s = string(p2);
					string p3s = string(p3);
					v1 = stof(p1s.substr(0, p1s.find('/')));
					t1 = stof(p1s.substr(2, p1s.find('/')));
					n1 = stof(p1s.substr(4, p1s.find('/')));
					
					v2 = stof(p2s.substr(0, p2s.find('/')));
					t2 = stof(p2s.substr(2, p2s.find('/')));
					n2 = stof(p2s.substr(4, p2s.find('/')));

					v3 = stof(p3s.substr(0, p3s.find('/')));
					t3 = stof(p3s.substr(2, p3s.find('/')));
					n3 = stof(p3s.substr(4, p3s.find('/')));
					
					FaceIndices f = FaceIndices(v1-1, v2-1, v3-1,
												t1-1, t2-1, t3-1,
												n1-1, n2-1, n3-1);

					std::cout << "Face Indices Found: "; f.print();
					temp_faces.push_back(f);
				}
			}

			vector<Triangle> faces;
			for (unsigned int i = 0; i < temp_faces.size(); i++) {
				Triangle tri = Triangle(temp_verts[temp_faces[i].v1],
										temp_verts[temp_faces[i].v2],
										temp_verts[temp_faces[i].v3],
										temp_norms[temp_faces[i].n1],
										temp_norms[temp_faces[i].n2],
										temp_norms[temp_faces[i].n3],
										temp_uvs[temp_faces[i].t1],
										temp_uvs[temp_faces[i].t2],
										temp_uvs[temp_faces[i].t3]);
				faces.push_back(tri);
			}
		}
		// Now that we have the verts, textures, and norms
		// Create triangles and then push them to a mesh


	};
	~ObjLoader();
};

