#define TINYGLTF_IMPLEMENTATION
#define TINYGLTF_USE_CPP14
#include "mesh.h"
#include "config.h"
#include <fstream>
#include <sstream>
#include "tiny_gltf.h"

/// generate vertex buffer object
void MeshResource::genvertexbuffer() {
	//generate buffer id
	glGenBuffers(1, &vertexbuffer);

	//bind buffer to id
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);

	// copy vertex array to vertex buffer object
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

}

/// set attributes
void MeshResource::setattrib(){
	
	//set vertex attributes
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	//enable the vertex attribute
	glEnableVertexAttribArray(0);

	//set color attribute
	/*glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	//enable color attribute
	glEnableVertexAttribArray(1);*/
	
	//set texture attributes
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoord));
	//enable the texture attribute
	glEnableVertexAttribArray(1);
	
	//set normal attributes
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, meshNorm));
	//enable the normal attribute
	glEnableVertexAttribArray(2);

}

void MeshResource::loadObj(std::string pathToFile)
{
	std::vector<Vector4D> vertices;
	std::vector<Vector4D> normals;
	std::vector<Vector4D> texCoords;
	std::vector<int> vertIndicies;
	std::vector<int> normIndicies;
	std::vector<int> texIndicies;
	std::fstream file;
	file.open(pathToFile, std::ios::in);
	if (file.is_open()) {
		std::string line;
		int lineNumber = 1;

		while (std::getline(file, line)) {
			std::string lineToken = line.substr(0, 2);
			lineToken.erase(std::remove_if(lineToken.begin(), lineToken.end(), isspace), lineToken.end());
			if (lineToken == "v") {

				std::vector<size_t> lineSpaces;
				std::string vertexPosition;
				lineSpaces.push_back(line.find(" "));
				lineSpaces.push_back(line.find(" ", lineSpaces[0] + 1));
				lineSpaces.push_back(line.find(" ", lineSpaces[1] + 1));
				lineSpaces.push_back(line.find(" ", lineSpaces[2] + 1));
				float x = std::stof(line.substr(lineSpaces[0] + 1, lineSpaces[1] - 2));
				float y = std::stof(line.substr(lineSpaces[1] + 1, (lineSpaces[2]) - (lineSpaces[1] + 1)));
				float z = std::stof(line.substr(lineSpaces[2] + 1, line.size()));
				vertices.push_back(Vector4D(x, y, z));

			}
			if (lineToken == "vn") {
				std::vector<size_t> lineSpaces;
				std::string vertexPosition;
				lineSpaces.push_back(line.find(" "));
				lineSpaces.push_back(line.find(" ", lineSpaces[0] + 1));
				lineSpaces.push_back(line.find(" ", lineSpaces[1] + 1));
				lineSpaces.push_back(line.find(" ", lineSpaces[2] + 1));
				float x = std::stof(line.substr(lineSpaces[0] + 1, lineSpaces[1] - 2));
				float y = std::stof(line.substr(lineSpaces[1] + 1, (lineSpaces[2]) - (lineSpaces[1] + 1)));
				float z = std::stof(line.substr(lineSpaces[2] + 1, line.size()));
				normals.push_back(Vector4D(x, y, z));
			}
			if (lineToken == "vt") {
				std::vector<size_t> lineSpaces;
				std::string vertexPosition;
				lineSpaces.push_back(line.find(" "));
				lineSpaces.push_back(line.find(" ", lineSpaces[0] + 1));
				lineSpaces.push_back(line.find(" ", lineSpaces[1] + 1));
				if (lineSpaces[2] == UINT64_MAX) {
					float x = std::stof(line.substr(lineSpaces[0] + 1, (lineSpaces[1]) - (lineSpaces[0] + 1)));
					float y = std::stof(line.substr(lineSpaces[1] + 1, line.size()));
					texCoords.push_back(Vector4D(x, y, 0.0f, 0.0f));
					continue;
				}
				//why even have a third texel AAAHHH
				float x = stof(line.substr(lineSpaces[0] + 1, (lineSpaces[1]) - (lineSpaces[0] + 1)));
				float y = stof(line.substr(lineSpaces[1] + 1, (lineSpaces[2]) - (lineSpaces[1] + 1)));
				texCoords.push_back(Vector4D(x, y, 0.0f, 0.0f));

			}
			if (lineToken == "f") {
				std::vector<size_t> lineSpaces;
				std::vector<size_t> slashPos;
				std::string vertexPosition;
				bool quadFaces = true;
				lineSpaces.push_back(line.find(" "));
				lineSpaces.push_back(line.find(" ", lineSpaces[0] + 1));
				lineSpaces.push_back(line.find(" ", lineSpaces[1] + 1));
				lineSpaces.push_back(line.find(" ", lineSpaces[2] + 1));
				slashPos.push_back(line.find("/"));
				for (int i = 0; i < 7; i++) {
					if (line.find("/", slashPos[i] + 1) == std::string::npos) {
						quadFaces = false;
						break;
					}
					slashPos.push_back(line.find("/", slashPos[i] + 1));
				}

				//first index
				vertIndicies.push_back(std::stof(line.substr(lineSpaces[0] + 1, (slashPos[0]) - (lineSpaces[0] + 1))));
				texIndicies.push_back(std::stof(line.substr(slashPos[0] + 1, (slashPos[1]) - (slashPos[0] + 1))));
				normIndicies.push_back(std::stof(line.substr(slashPos[1] + 1, (lineSpaces[1]) - (slashPos[1] + 1))));

				//second index
				vertIndicies.push_back(std::stof(line.substr(lineSpaces[1] + 1, (slashPos[2]) - (lineSpaces[1] + 1))));
				texIndicies.push_back(std::stof(line.substr(slashPos[2] + 1, (slashPos[3]) - (slashPos[2] + 1))));
				normIndicies.push_back(std::stof(line.substr(slashPos[3] + 1, (lineSpaces[2]) - (slashPos[3] + 1))));




				if (quadFaces == true) {
					//fourth index
					vertIndicies.push_back(std::stof(line.substr(lineSpaces[3] + 1, (slashPos[6]) - (lineSpaces[3] + 1))));
					texIndicies.push_back(std::stof(line.substr(slashPos[6] + 1, (slashPos[7]) - (slashPos[6] + 1))));
					normIndicies.push_back(std::stof(line.substr(slashPos[7] + 1, (line.size()) - (slashPos[7] + 1))));


					//now for the second triangle third index
					vertIndicies.push_back(std::stof(line.substr(lineSpaces[2] + 1, (slashPos[4]) - (lineSpaces[2] + 1))));
					texIndicies.push_back(std::stof(line.substr(slashPos[4] + 1, (slashPos[5]) - (slashPos[4] + 1))));
					normIndicies.push_back(std::stof(line.substr(slashPos[5] + 1, lineSpaces[3] - slashPos[5] + 1)));

					//fourth index
					vertIndicies.push_back(std::stof(line.substr(lineSpaces[3] + 1, (slashPos[6]) - (lineSpaces[3] + 1))));
					texIndicies.push_back(std::stof(line.substr(slashPos[6] + 1, (slashPos[7]) - (slashPos[6] + 1))));
					normIndicies.push_back(std::stof(line.substr(slashPos[7] + 1, (line.size()) - (slashPos[7] + 1))));

					//second index
					vertIndicies.push_back(std::stof(line.substr(lineSpaces[1] + 1, (slashPos[2]) - (lineSpaces[1] + 1))));
					texIndicies.push_back(std::stof(line.substr(slashPos[2] + 1, (slashPos[3]) - (slashPos[2] + 1))));
					normIndicies.push_back(std::stof(line.substr(slashPos[3] + 1, (lineSpaces[2]) - (slashPos[3] + 1))));

					continue;

				}
				// to not screw up quad face compatibility this has to be moved here

				// third index
				vertIndicies.push_back(std::stof(line.substr(lineSpaces[2] + 1, (slashPos[4]) - (lineSpaces[2] + 1))));
				texIndicies.push_back(std::stof(line.substr(slashPos[4] + 1, (slashPos[5]) - (slashPos[4] + 1))));
				normIndicies.push_back(std::stof(line.substr(slashPos[5] + 1, (line.size()) - (slashPos[5] + 1))));


			}
			lineNumber++;
		}
		file.close();

		std::vector<Vertex> finalVerts;
		for (int i = 0; i < vertIndicies.size(); i++) {
			Vector4D vert = vertices[vertIndicies[i] - 1];
			Vector4D norm = normals[normIndicies[i] - 1];
			Vector4D tex = texCoords[texIndicies[i] - 1];
			int vertIndex = vertIndicies[i] - 1;
			int normIndex = normIndicies[i] - 1;
			int texIndex = texIndicies[i] - 1;

			finalVerts.push_back(Vertex(vert, norm, tex));
		}
		std::cout << "finished loading obj" << "\n";
		indexVertices(finalVerts);

	}
	genvertexarray();
	genvertexbuffer();
	setattrib();
}

void MeshResource::loadGLTF(std::string pathToFile)
{
	tinygltf::Model gltfModel;
	tinygltf::TinyGLTF loader;
	std::string error;
	std::string warning;

	bool result = loader.LoadASCIIFromFile(&gltfModel, &error, &warning, pathToFile);
}

/// generate vertex array object
void MeshResource::genvertexarray() {

	//generate vertex array object id
	glGenVertexArrays(1, &vertexarray);

	//bind vertex array object
	glBindVertexArray(vertexarray);
}

/// generate index buffer
void MeshResource::indexVertices(std::vector<Vertex> verts) {
	std::cout << "indexing mesh" << "\n";
	std::vector<Vertex> indexedVerts;
	std::vector<unsigned int> indices;

	indexedVerts.push_back(verts[0]);
	indices.push_back(0);
	bool matchingVertex = false;
	for (int i = 1; i < verts.size(); i++) {
		for (int j = 0; j < indexedVerts.size(); j++) {
			if (isVertexEqual(verts[i], indexedVerts[j])) {
				indices.push_back(j);
				matchingVertex = true;
				break;
			}

		}
		if (matchingVertex == false) {
			indexedVerts.push_back(verts[i]);
			indices.push_back(indexedVerts.size() - 1);
		}
		matchingVertex = false;

	}

	setVertices(indexedVerts);
	this->indices = indices;

	//generate index buffer id
	glGenBuffers(1, &indexbuffer);
	//bind index buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexbuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indices.size() * sizeof(unsigned int), &this->indices[0], GL_STATIC_DRAW);

	std::cout << "finished indexing mesh" << "\n";
}

void MeshResource::setVertices(std::vector<Vertex> newVertices)
{
	this->vertices = newVertices;
}

bool MeshResource::isVertexEqual(Vertex vert1, Vertex vert2)
{
	if (vert1.position == vert2.position && vert1.meshNorm == vert2.meshNorm && vert1.texCoord == vert2.texCoord) {
		return true;
	}
	return false;
}


