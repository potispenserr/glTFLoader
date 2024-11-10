#include "LightNode.h"
#include <stb_image.h>
LightNode::LightNode(ShaderObject& lighting)
{
	lightShader = lighting;

}

LightNode::~LightNode()
{

}


void LightNode::setupLighting()
{
	
	//lightCube.updateTransform(lightCube.getTransform().translation(lightPos));
	//glGenVertexArrays(1, &lightVAO);
	//glBindVertexArray(lightVAO);

	//glBindBuffer(GL_ARRAY_BUFFER, lightCube.getMesh().get()->vertexbuffer);

	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	//glEnableVertexAttribArray(0);

	//
	////enable the normal attribute
	//glEnableVertexAttribArray(1);

	////set normal attributes
	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, meshNorm));
	//

	//
	////set texture attributes
	//glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoord));

	////enable the texture attribute
	//glEnableVertexAttribArray(2);

	//diffuseTex.loadTex("./resources/container2fixed.png");
	//specularTex.loadTex("./resources/container2_specularfixed.png");
	

	lightShader.use();
	lightShader.setVec3(std::string("lightColor"), lightColor);
	lightShader.setFloat(std::string("ambientIntensity"), 0.1f);

	lightShader.setInt(std::string("material.textureDiffuse"), 0);
	lightShader.setVec3(std::string("material.textureSpecular"), Vector4D(0.5f, 0.5f, 0.5f));
	lightShader.setFloat(std::string("material.shininess"), 64.0f);

	lightShader.setVec3(std::string("light.ambient"), Vector4D(0.2f, 0.2f, 0.2f));
	lightShader.setVec3(std::string("light.diffuse"), Vector4D(0.5f, 0.5f, 0.5f));
	lightShader.setVec3(std::string("light.specular"), Vector4D(1.0f, 1.0f, 1.0f));

	


}

void LightNode::updateLighting(Camera cam, Matrix4D projection, GraphicsNode& lightCube)
{
	lightCube.setTransform(Matrix4D::translation(lightPos));
	lightCube.updateTransform(Matrix4D::scale(Vector4D(0.2f, 0.2f, 0.2f)));

	
}


