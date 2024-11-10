#include "TextureResource.h"
#include "stb_image.h"
#include <iostream>

TextureResource::TextureResource(std::string pathToFile)
{
	loadTex(pathToFile);
}

// sets all texture parameters
void TextureResource::setTexParam() {
	//texture wrapping
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}


///loads texture data from stbi and generates mipmaps
void TextureResource::loadTex(std::string path) {
	stbi_set_flip_vertically_on_load(true);
	glGenTextures(1, &texID);

	texPictureData = stbi_load(path.c_str(), &width, &height, &nChannels, 0);
	if (texPictureData) {
		if (this->nChannels == 3) {
			glBindTexture(GL_TEXTURE_2D, texID);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, texPictureData);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else if (this->nChannels == 4) {
			glBindTexture(GL_TEXTURE_2D, texID);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texPictureData);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		this->setTexParam();

		std::cout << "Hey you actually hit something" << "\n";
	}
	else {
		std::cout << stbi_failure_reason() << "\n";
		std::cout << "Nice shootin' Tex" << "\n";
	}
	stbi_image_free(texPictureData);
	
}

