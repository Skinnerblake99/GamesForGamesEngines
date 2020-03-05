#pragma once
#include "pch.h"
#include <SDL.h>
#include <glew.h>
#include <SDL_opengl.h>
#include <stdio.h>
#include "TriangleRenderer.h"
#include "Camera.h"
#include "Model.h"
#include "ModelRenderer.h"
#include "Model2.h"
#include "FPSCamera.h"
#include "Terrain.h"
#include "Billboard.h"
class GameLoop {
public:
	GameLoop();
	virtual ~GameLoop();

	void init();
	bool handleInput();
	void update();
	void draw();
	void clean();
	Texture * brick;
	Texture * ground;
	Texture * TankT;
	Texture * TracksT;
private:
	SDL_Window * window;
	SDL_GLContext glContext;
	TriangleRenderer * triangleRenderer;
	//Camera * camera;
	Model* model;
<<<<<<< HEAD
	Model * model2;
	Model * Tank;
	Model * Tracks;
	//Model2 * model2;
=======
	Model2 * model2;
>>>>>>> parent of 0abcc9b... Added ability
	FPSCamera * camera;
	ModelRenderer* modelRenderer;

	Terrain * terrain;
	Texture * terrainTexture;

	Texture * sky1;
	Skydome * skydome;

	Billboard * billboard;
};