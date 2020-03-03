#pragma once
#include<sdl.h>
#include <glm\glm.hpp>
#include "Camera.h"

#define UP 0
#define DOWN 1

class FPSCamera : public Camera {
public:
	FPSCamera(SDL_Window * window) {
		this->window = window;
		SDL_GetMouseState(&oldMouseX, &oldMouseY);
	}
	virtual ~FPSCamera(){}

	void handleInput(SDL_Event &e) {
		if (e.type == SDL_KEYDOWN) {
			switch (e.key.keysym.scancode) {
			case SDL_SCANCODE_UP:
					keyStates[UP] = true;
					break;
				case SDL_SCANCODE_DOWN:
					keyStates[DOWN] = true;
					break;
			}
		}
		if (e.type == SDL_KEYUP) {
			switch (e.key.keysym.scancode) {
			case SDL_SCANCODE_UP:
				keyStates[UP] = false;
				break;
			case SDL_SCANCODE_DOWN:
				keyStates[DOWN] = false;
				break;
			}
		}
	}
	void update() {
		//Camera position is moved forwards and backwards on key press
		//sin and cos are used to move the camera based on its facing direction
		if (keyStates[UP]) {
			position.x += sin(glm::radians(yaw)) * 0.03f;
			position.z -= cos(glm::radians(yaw)) * 0.03f;
		}
		if (keyStates[DOWN]) {
			position.x -= sin(glm::radians(yaw)) * 0.03f;
			position.z += cos(glm::radians(yaw)) * 0.03f;
		}
		//Calculations of how many pixels mouse has moved within the frame
		int x, y;
		SDL_GetMouseState(&x, &y);
		float diffX = (x - oldMouseX) * 1.0f;
		float diffY = (y - oldMouseY) * 1.0f;
		//the camera yaw and pitch are set based on mouse difference
		yaw += diffX;
		pitch += diffY;

		//clamp pitch values
		if (pitch > 20.0f)
			pitch = 20.0f;
		if (pitch < -20.0f)
			pitch = -20.0f;

		glm::mat4 matRoll = glm::mat4(1.0f);//identity matrix
		glm::mat4 matPitch = glm::mat4(1.0f);//identity matrix
		glm::mat4 matYaw = glm::mat4(1.0f);//identity matrix
		//Roll pitch and yaw are used to store our angles in the class
		matRoll = glm::rotate(matRoll, 0.0f, glm::vec3(0.0f, 0.0f, 1.0f));
		matPitch = glm::rotate(matPitch, glm::radians(pitch), glm::vec3(1.0f, 0.0f, 0.0f));
		matYaw = glm::rotate(matYaw, glm::radians(yaw), glm::vec3(0.0f, 1.0f, 0.0f));

		glm::mat4 rotate = matRoll * matPitch * matYaw;

		glm::mat4 translate = glm::mat4(1.0f);
		translate = glm::translate(translate, -position);
		viewMatrix = rotate * translate;
		//move the mouse to the center of the screen
		SDL_WarpMouseInWindow(window, 320, 240);
		oldMouseX = 320;
		oldMouseY = 240;
	}
	float yaw = 0.0f, pitch = 0.0f;
private:
	bool keyStates[2];
	
	int oldMouseX, oldMouseY;
	SDL_Window * window;
};