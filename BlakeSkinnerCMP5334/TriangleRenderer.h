#pragma once
#include "pch.h"
#include <SDL.h>
#include <glew.h>
#include <SDL_opengl.h>
#include <stdio.h>
#include <glm/gtc/type_ptr.hpp>
#include "Camera.h"
class TriangleRenderer {
public:
	TriangleRenderer(Camera * camera);
	virtual ~TriangleRenderer();
	
	void init();
	void update();
	void draw();
	void clean();

private:

	GLuint programId = 0;
	GLint vertexPositionLocation = -1;

	GLuint vertexBufferObject =0;
	GLuint indexBufferObject = 0;
	GLuint modelMatrixLocation = -1;
	GLuint viewMatrixLocation = -1;
	GLuint projectionMatrixLocation = -1;
};