#pragma once
#include "core/app.h"
#include "render/window.h"
#include "config.h"
class TextureResource {
public:

	TextureResource() {
		width = 0;
		height = 0;
		nChannels = 0;

	}

	TextureResource(std::string pathToFile);

	~TextureResource() {
		glDeleteTextures(1, &texID);
	}

	float borderColor[4] = { 1.0f, 1.0f, 0.0f, 1.0f };

	void setTexParam();
	void loadTex(std::string path);


	int width = 0;
	int height = 0;
	int nChannels = 0;

	unsigned int texID = 0;
	unsigned char* texPictureData = NULL;
	
};
