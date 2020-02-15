#pragma once
#include <SDL.h>
#include <glew.h>
#include <SDL_opengl.h>
#include <stdio.h>
#include <glm/gtc/type_ptr.hpp>

#include "Camera.h"
#include "Model.h"
#include "Utilcpp.cpp"
class ModelRenderer {
public:
	ModelRenderer(Camera * camera);
	virtual ~ModelRenderer();

	void init();
	void renderModel(Model * m);
private:

	GLuint programId = 0;
	GLint vertexPositionLocation = -1;

	GLuint modelMatrixLocation = -1;
	GLuint viewMatrixLocation = -1;
	GLuint projectionMatrixLocation = -1;

	Camera* camera;
	
};