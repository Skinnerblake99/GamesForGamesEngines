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
class GameLoop {
public:
	GameLoop();
	virtual ~GameLoop();

	void init();
	bool handleInput();
	void update();
	void draw();
	void clean();

private:
	SDL_Window * window;
	SDL_GLContext glContext;
	TriangleRenderer * triangleRenderer;
	Camera * camera;
	Model* model;
	ModelRenderer* modelRenderer;
};