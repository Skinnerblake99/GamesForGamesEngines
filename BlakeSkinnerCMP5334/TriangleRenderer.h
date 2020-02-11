#pragma once
#include "pch.h"
#include <SDL.h>
#include <glew.h>
#include <SDL_opengl.h>
#include <stdio.h>

class TriangleRenderer {
public:
	TriangleRenderer();
	virtual ~TriangleRenderer();
	
	void init();
	void update();
	void draw();
	void clean();

private:

	GLuint programId = 0;
	GLint vertexPos2DLocation = -1;

	GLuint vertexBufferObject =0;
	GLuint indexBufferObject = 0;

};