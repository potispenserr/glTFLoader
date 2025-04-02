#include "GraphicsNode.h"
#include <stdexcept>

GraphicsNode::GraphicsNode()
{
}

GraphicsNode::GraphicsNode(MeshResource newMesh, TextureResource newTexture, ShaderObject newShader, Matrix4D newTransform)
{
	mesh = std::make_shared<MeshResource>(newMesh);
	texture = std::make_shared<TextureResource>(newTexture);
	shader = std::make_shared<ShaderObject>(newShader);
	transform = newTransform;
}

GraphicsNode::GraphicsNode(GraphicsNode& gn)
{
	mesh = gn.mesh;
	texture = gn.texture;
	shader = gn.shader;
	transform = gn.transform;

}


GraphicsNode::~GraphicsNode()
{
}

std::shared_ptr<MeshResource>& GraphicsNode::getMesh()
{
	return mesh;
}

std::shared_ptr<TextureResource>& GraphicsNode::getTexture()
{
	return texture;
}

std::shared_ptr<ShaderObject>& GraphicsNode::getShader()
{
	return shader;
}

void GraphicsNode::setMesh(std::shared_ptr<MeshResource>& newMesh)
{
	mesh = newMesh;
}

void GraphicsNode::setTexture(std::shared_ptr<TextureResource>& newTexture)
{
	texture = newTexture;
}

void GraphicsNode::setShader(std::shared_ptr<ShaderObject>& newShader)
{
	shader = newShader;
}

void GraphicsNode::setTransform(Vector4D newTransform)
{
	transform = transform.translation(newTransform);
}
void GraphicsNode::setTransform(Matrix4D newTransform)
{
	transform = newTransform;
}

void GraphicsNode::updateTransform(Matrix4D transformToAdd)
{
	transform = transform * transformToAdd;
}

Matrix4D& GraphicsNode::getTransform()
{
	return transform;
}

void GraphicsNode::bindGraphics(std::string pathToTextureFile)
{

	texture.get()->loadTex(pathToTextureFile);
	shader.get()->use();

}

void GraphicsNode::draw(Camera cam, Matrix4D projection, Vector4D lightPosition)
{	
	shader.get()->use();
	shader.get()->setMat4(std::string("model"), transform);
	shader.get()->setMat4(std::string("view"), cam.getView());
	shader.get()->setMat4(std::string("projection"), projection);
	shader.get()->setVec3(std::string("light.pos"), lightPosition);
	shader.get()->setVec3(std::string("viewPosition"), cam.camPos);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture.get()->texID);
	if(mesh.get()->isGLTF == true){
		for(auto nodeIt = mesh.get()->glTFModel.nodes.begin();  nodeIt != mesh.get()->glTFModel.nodes.end(); ++nodeIt){
			auto node = *nodeIt;
			
			auto model = mesh.get()->glTFModel;
			auto lol = node.mesh;

			const auto &glTFmesh = model.meshes[node.mesh];
            const auto vaoRange = mesh.get()->meshIndexToVAORange[node.mesh];
            for (size_t primI = 0; primI < glTFmesh.primitives.size(); primI++) {
              const auto vao = mesh.get()->vaos[vaoRange[0] + primI];
              const auto &prim = glTFmesh.primitives[primI];
              glBindVertexArray(vao);

              if (prim.indices >= 0) {
                const auto &accessor = model.accessors[prim.indices];
                const auto &buffView = model.bufferViews[accessor.bufferView];
                const auto byteOffset = accessor.byteOffset + buffView.byteOffset;
                glDrawElements(prim.mode, accessor.count, 
					accessor.componentType, (void *)byteOffset);
              } else {

                const auto accessorI = (*begin(prim.attributes)).second;
                const auto &accessor = model.accessors[accessorI];
                glDrawArrays(prim.mode, 0, accessor.count);
              }
            }
          }

		
	}
	glBindVertexArray(mesh.get()->vertexarray);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.get()->indexbuffer);
	glDrawElements(GL_TRIANGLES, mesh.get()->indices.size(), GL_UNSIGNED_INT, 0);
	//glDrawArrays(GL_TRIANGLES, 0, mesh.get()->verticies.size());

}



void GraphicsNode::clearMemory()
{
	glDeleteVertexArrays(1, &mesh.get()->vertexarray);
	glDeleteBuffers(1, &mesh.get()->vertexbuffer);
	glDeleteBuffers(1, &mesh.get()->indexbuffer);
}
