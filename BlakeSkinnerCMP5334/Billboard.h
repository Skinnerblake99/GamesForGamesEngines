#pragma once

#include <glew.h>
#include <glm/glm.hpp>
#include <SDL_opengl.h>
#include  "Texture.h"

class Billboard {
	friend class ModelRenderer;

	Billboard(Texture * texture) {
		this->texture = texture;
		this->scale = glm::vec3(20.0f, 20.0f, 1.0f);
		//this->scale = glm::vec3(1.0f, 1.0f , 1.0f);
		this->position = glm::vec3(0, 0, 0);
	}
	virtual ~Billboard() {

	}

	void init() {
		//Create VBO
		glGenBuffers(1, &vertexBufferObject);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
		glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(GLfloat), vertices, GL_STATIC_DRAW);

		glGenBuffers(1, &uvBufferObject);
		glBindBuffer(GL_ARRAY_BUFFER, uvBufferObject);
		glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(GLfloat), uv, GL_STATIC_DRAW);

		//Create IBO
		glGenBuffers(1, &indexBufferObject);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferObject);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(GLuint), indices, GL_STATIC_DRAW);
	}

	
public:

private:

	Texture * texture;

	glm::vec3 position;
	glm::vec3 scale;
	
	const GLfloat vertices[12] = {
		0.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f
	};

	const GLint indices[6] = {
		0,1,2,
		2,1,3
	};

	const GLfloat uv[8]{
		0.0f, 1.0f,
		1.0f, 1.0f,
		0.0f, 0.0f,
		1.0f, 0.0f
	};

	GLuint vertexBufferObject = -1;
	GLuint uvBufferObject = -1;
	GLuint indexBufferObject = -1;
};