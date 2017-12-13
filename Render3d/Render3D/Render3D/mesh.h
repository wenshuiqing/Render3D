#pragma once
#include <string>
#include "rmathf.h"
#include <vector>
class Mesh
{
public:
	struct Face
	{
		std::vector<unsigned int> numIndices;
		Face(unsigned int a, unsigned int b, unsigned int c)
		{
			numIndices = { a,b,c,a };
		}
	};

	struct Vertex
	{
		mf::Vector3 vertex;
		mf::Vector3 normal;
		mf::Vector2 texcoord;
	};
public:
	std::vector<Vertex> vertices;
	std::vector<Face> faces;
	Mesh()
	{

	}
	void SetVertices(float* nvertices, int pointCount, int stride)
	{
		int size = pointCount*stride;
		for (int i = 0; i < size; i += stride)
		{
			Vertex v;
			v.vertex = mf::Vector3(nvertices[i], nvertices[i + 1], nvertices[i + 2]);
			if (stride >= 6)
			{
				v.normal = mf::Vector3(nvertices[i + 3], nvertices[i + 4], nvertices[i + 5]);
			}
			if (stride == 8)
			{
				v.texcoord = mf::Vector2(nvertices[i + 6], nvertices[i + 7]);
			}
			vertices.push_back(v);
		}
	}

	~Mesh()
	{

	}
private:

};
