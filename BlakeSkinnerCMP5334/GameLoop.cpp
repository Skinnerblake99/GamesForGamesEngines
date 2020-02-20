#include "pch.h"
#include "GameLoop.h"
#undef main

GameLoop::GameLoop()
{
	camera = new FPSCamera(this->window);
	//triangleRenderer = new TriangleRenderer(camera);
	modelRenderer = new ModelRenderer(camera);
	//model = new Model("monkey.obj");
	model = new Model("cube.obj");
	model2 = new Model2 ("cube.obj");
	brick = new Texture("brick.png");
	ground = new Texture("ground.png");
	terrainTexture = new Texture("terrain-texture.png");
	terrain = new Terrain("terrain-heightmap.png", terrainTexture);
}

GameLoop::~GameLoop()
{
	//delete triangleRenderer;
	delete camera;
	delete model;
	delete model2;
	delete modelRenderer;
	delete terrainTexture;
	delete terrain;
}

void GameLoop::init()
{
 //Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initalize! SDL ERROR: %s\n", SDL_GetError());
		return;
	}
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	//create window
	window = SDL_CreateWindow("SDL OPENGL", 50, 50, 640, 480, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

	if (window == nullptr) {
		printf("SDL could not create window! SDL Error:%s\n", SDL_GetError());
		return;
	}
	//create GL context
	glContext = SDL_GL_CreateContext(window);

	if (glContext == nullptr) {
		printf("SDL could not create GL context! SDL Error: %s/n", SDL_GetError());
		return;
	}
	
	//Initalize GLEW
	glewExperimental = GL_TRUE;
	GLenum glewError = glewInit();
	if (glewError != GLEW_OK) {
		printf("Error initializing GLEW! %s\n", glewGetErrorString(glewError));
	}
	//Use Vsync
	if (SDL_GL_SetSwapInterval(1) < 0) {
		printf("Warning: Unable to set VSync! SDL Error: %s/n", SDL_GetError());
	}

	//triangleRenderer->init();
	//Spawn mdoels in
	modelRenderer->init();
	model->init();
	model2->init();
	//Initalise the texure
	brick->init();
	ground->init();
	//set the texture to relevant model
	model->setTexture(brick);
	model2->setTexture(ground);
	terrainTexture->init();
	terrain->init();
}

bool GameLoop::handleInput()
{
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			return false;
		}
		camera->handleInput(e);
	}
	return true;
}

void GameLoop::update(){
	camera->update();
}

void GameLoop::draw()
{
	//clear the screen to cornflower blue
	glClearColor(0.392f, 0.584f, 0.929f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glEnable(GL_CULL_FACE);
	modelRenderer->renderModel(model);
	modelRenderer->renderModel2(model2);
	//triangleRenderer->draw();
	//present the screen
	SDL_GL_SwapWindow(window);
	glClear(GL_COLOR_BUFFER_BIT);
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	modelRenderer->renderTerrain(terrain);
}

void GameLoop::clean()
{
	SDL_DestroyWindow(window);
	window = NULL;

	SDL_Quit();
}

int main(void) {
	GameLoop * gameLoop = new GameLoop();
	gameLoop->init();

	while (gameLoop->handleInput()) {
		gameLoop->update();
		gameLoop->draw();
	}

	gameLoop->clean();
	delete gameLoop;
	return 0;
}