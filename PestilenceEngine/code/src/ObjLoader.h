#include "Triangle.h" 
#include <iostream> 
#include <fstream> 
#include <string>
#include <vector>

using namespace std; 

// OBJ Loader: Can read in files and generate game meshes with it. 
class ObjLoader
{
public:
	ObjLoader()
	{
		std::cout << "Obj loader created." << std::endl;
		readFile("models/cube.obj");
	};

	void readFile(string filename)
	{
		// Crete temporary vars for verts, uvs and normals
		vector<Vertex> temp_verts; 
		vector<Vertex> temp_uvs; 
		vector<Vertex> temp_norms;
		const char* path = filename.c_str();
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
					fscanf(*file, "%f %f \n", &a, &b);
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
			}
		}
		// Now that we have the verts, textures, and norms
		// Create triangles and then push them to a mesh


	};
	~ObjLoader();
};

