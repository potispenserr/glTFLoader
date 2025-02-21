#pragma once
#include <vector>
#include "Matrix4D.h"
#include "Vector4D.h"
#include "core/app.h"
#include "render/window.h"
#include "config.h"
struct Vertex {
    Vector4D position;
    Vector4D meshNorm;
    Vector4D texCoord;
    Vertex(Vector4D newPos, Vector4D newNorm, Vector4D newTexCoord) :
        position(newPos), meshNorm(newNorm), texCoord(newTexCoord) {}
};

struct Texture {
    unsigned int id;
    std::string type;
};

class MeshResource {
public:
	MeshResource() {
	}

	~MeshResource() {
	}
    

    std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;

	unsigned int vertexarray = 0;
	unsigned int vertexbuffer = 0;
	unsigned int indexbuffer = 0;
    unsigned int textureBuffer = 0;

	void setattrib();

	void loadObj(std::string pathToFile);

	void loadGLTF(std::string pathToFile);

	void genvertexarray();

	void genvertexbuffer();

	void indexVertices(std::vector<Vertex> verts);

    void setVertices(std::vector<Vertex> newVertices);

	bool isVertexEqual(Vertex v1, Vertex v2);

};