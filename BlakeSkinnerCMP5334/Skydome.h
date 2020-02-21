#pragma once
#include <SDL.h>
#include <glew.h>
#include <SDL_opengl.h>

#include "Texture.h"

class Skydome {
	friend class ModelRenderer;
public:
	Skydome(Texture * texture) {
		this->texture = texture;
	}
	virtual ~Skydome(){}

	void init() 
	{
		float azimuth;
		int k;

		vector<glm::vec3>
	}

private:

	GLuint vertextBufferObject;
	GLuint uvBufferObject;
	GLuint indexBufferObject;

	Texture * texture;

	__int32 indexCount;
};