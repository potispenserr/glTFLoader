#pragma once
#include "core/app.h"
#include "render/window.h"
#include "config.h"
#include "mesh.h"
#include "TextureResource.h"
#include "ShaderObject.h"
#include "Matrix4D.h"
#include "Camera.h"
#include <memory>
class GraphicsNode
{
public:
	GraphicsNode();
	GraphicsNode(MeshResource newMesh, TextureResource newTexture, ShaderObject newShader, Matrix4D newTransform);
	GraphicsNode(GraphicsNode& gn);



	~GraphicsNode();

	std::shared_ptr<MeshResource>& getMesh();
	std::shared_ptr<TextureResource>& getTexture();
	std::shared_ptr<ShaderObject>& getShader();

	void setMesh(MeshResource newMesh);
	void setTexture(TextureResource newTexture);
	void setShader(ShaderObject newShader);

	void setTransform(Vector4D newTransform);
	void setTransform(Matrix4D newTransform);
	void updateTransform(Matrix4D transformToAdd);
	Matrix4D& getTransform();

	void bindGraphics(std::string pathToTextureFile);

	void draw(Camera cam, Matrix4D projection, Vector4D lightPosition);

	void loadObj(std::string pathToFile);

	void loadGLTF(std::string pathToFile);

	void clearMemory();


	

private:
	std::shared_ptr<MeshResource> mesh;
	std::shared_ptr<TextureResource> texture;
	std::shared_ptr<ShaderObject> shader;
	Matrix4D transform;


};

