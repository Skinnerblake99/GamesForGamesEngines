#include "pch.h"
#include "GameLoop.h"
#undef main

GameLoop::GameLoop()
{
	camera = new FPSCamera(this->window);
	modelRenderer = new ModelRenderer(camera);
	//Call in models
	model = new Model("cube.obj");
<<<<<<< HEAD
	model2 = new Model("cube.obj");
	Tank = new Model("TANK.obj");
	Tracks = new Model("TrainTracks/TrainTracks_3m.obj");
	//Call in textures
	TracksT = new Texture("TrainTracks/TrainTracks_3m/1.png");
	brick = new Texture("brick.png");
=======
	model2 = new Model2 ("cube.obj");
	brick = new Texture("brick.png");
	ground = new Texture("ground.png");
>>>>>>> parent of 0abcc9b... Added ability
	terrainTexture = new Texture("terrain-texture.png");
	sky1 = new Texture("skydome.jpg");
	//Terrain/ sky
	terrain = new Terrain("terrain-heightmap.png", terrainTexture);

	
	skydome = new Skydome(sky1);

	billboard = new Billboard(brick);
}

GameLoop::~GameLoop()
{
	//delete triangleRenderer;
	delete camera;
	delete model;
	delete model2;
<<<<<<< HEAD
	delete Tank;
	delete Tracks;
=======
>>>>>>> parent of 0abcc9b... Added ability
	delete modelRenderer;
	delete terrainTexture;
	delete terrain;
	delete skydome;
	delete billboard;
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
<<<<<<< HEAD
	Tracks->init();
	Tank->init();

	//Initalise the texure
	brick->init();
	//set the texture to relevant model
	model->setTexture(brick);
	model2->setTexture(brick);
	Tracks->setTexture(TracksT);
	Tank->setTexture(TracksT);

	//Where to set positions
	model2->setPosition(10, 1, 10);
	Tracks->setPosition(20, 1, 20);
	Tank->setPosition(40, 2, 10);

	//Initalise the Textures
	TankT->init();
	TracksT->init();
=======
	//Initalise the texure
	brick->init();
	ground->init();
	//set the texture to relevant model
	model->setTexture(brick);
	model2->setTexture(ground);
>>>>>>> parent of 0abcc9b... Added ability
	terrainTexture->init();
	terrain->init();
	sky1->init();
	skydome->init();
	//Billboard
	billboard->init();
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
	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	modelRenderer->renderModel(model);
<<<<<<< HEAD
	modelRenderer->renderModel(model2);
	modelRenderer->renderModel(Tracks);
	modelRenderer->renderModel(Tank);
=======
	modelRenderer->renderModel2(model2);
>>>>>>> parent of 0abcc9b... Added ability
	modelRenderer->renderTerrain(terrain);
	modelRenderer->renderSkydome(skydome);
	modelRenderer->renderBillboard(billboard);
	//triangleRenderer->draw();
	//present the screen
	SDL_GL_SwapWindow(window);
	
	
	
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