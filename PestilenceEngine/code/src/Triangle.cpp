#include "Triangle.h"

Triangle::Triangle()
{
	this->a = nullptr; 
	this->b = nullptr; 
	this->c = nullptr;

	this->n_a = nullptr; 
	this->n_b = nullptr; 
	this->n_c = nullptr; 
	
	this->t_a = nullptr; 
	this->t_b = nullptr; 
	this->t_b = nullptr; 
}

// Triangle with no UVs or normals
Triangle::Triangle(Vertex a, Vertex b, Vertex c)
{
	this->a = new Vertex(a);
	this->b = new Vertex(b);
	this->c = new Vertex(c);

	// Give normals and UVs "default" values for now
	this->n_a = new Vertex(.5f, .5f, .5f);
	this->n_b = new Vertex(.5f, .5f, .5f);
	this->n_c = new Vertex(.5f, .5f, .5f);

	this->t_a = new Vertex(.5f, .5f, .5f);
	this->t_b = new Vertex(.5f, .5f, .5f);
	this->t_c = new Vertex(.5f, .5f, .5f);
}

// Triangle with verts, UVs, and normals initialized
// This will be the most commonly used. 
Triangle::Triangle(Vertex a, Vertex b, Vertex c,
	Vertex na, Vertex nb, Vertex nc, 
	Vertex ta, Vertex tb, Vertex tc)
{
	this->a = new Vertex(a); 
	this->b = new Vertex(b); 
	this->c = new Vertex(c);

	this->n_a = new Vertex(na); 
	this->n_b = new Vertex(nb); 
	this->n_c = new Vertex(nc); 

	this->t_a = new Vertex(ta); 
	this->t_b = new Vertex(tb); 
	this->t_b = new Vertex(tc); 
}




Triangle::~Triangle()
{
}
