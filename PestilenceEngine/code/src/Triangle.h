#include "Vertex.h"
class Triangle
{
public:
	// Default constructor - initializes to nullptrs
	Triangle();

	Triangle(Vertex x, Vertex y, Vertex z); 

	// Constructor for vertices, normals, and texture coords
	Triangle(Vertex* a, Vertex* b, Vertex* c,
		Vertex* na, Vertex* nb, Vertex* nc,
		Vertex* ta, Vertex* tb, Vertex* tc);
	
	// Get the triangle (static)
	const Triangle& get()
	{
		return *this;
	};
	 
	void print()
	{
		this->a->print(); 
		this->b->print(); 
		this->c->print(); 
		this->n_a->print(); 
		this->n_b->print(); 
		this->n_c->print();
		this->t_a->print();
		this->t_b->print();
		this->t_c->print();
	};
	// Three-point constructor in local coordinates
	~Triangle();

	// Permanent pointers to vertices
	Vertex* a;
	Vertex* b;
	Vertex* c;

	// Normals
	Vertex* n_a;
	Vertex* n_b;
	Vertex* n_c;

	// UVs (Texture coords)
	Vertex* t_a;
	Vertex* t_b;
	Vertex* t_c;

private: 

	float scale = 1; // always 1 to start
};

