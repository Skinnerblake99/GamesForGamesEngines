#pragma once
#include "pch.h"
#include <SDL.h>
#include <glew.h>
#include <SDL_opengl.h>
#include <stdio.h>
#include <glm/gtc/type_ptr.hpp>

#include "Camera.h"
#include "Model.h"
#include "Utilcpp.cpp"
#include "Model2.h"
#include "Terrain.h"
#include "Skydome.h"
#include "FPSCamera.h"
#include "Billboard.h"
class ModelRenderer {
public:
	ModelRenderer(FPSCamera * camera);
	virtual ~ModelRenderer();

	void init();
	void renderModel(Model * m);
<<<<<<< HEAD
	//Stuff for new models just copy in cpp renderer for each model and add their indivdual OBJ files
	//void renderModel2(Model2 * m);
=======
	void renderModel2(Model2 * m);
>>>>>>> parent of 0abcc9b... Added ability
	void renderTerrain(Terrain * t);
	void renderSkydome(Skydome * s);
private:

	GLuint programId = 0;
	GLint vertexPositionLocation = -1;
	GLint uvLocation = -1;

	GLuint modelMatrixLocation = -1;
	GLuint viewMatrixLocation = -1;
	GLuint projectionMatrixLocation = -1;
	GLuint textureSamplerLocation = -1;
	FPSCamera* camera;
	
};