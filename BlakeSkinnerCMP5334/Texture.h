#pragma once
#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>
#include <string>

using namespace std;

class Texture {
public:
	friend class ModelRenderer;
	Texture(string file) {
		this->file = file;
	}
	void init() {
		SDL_Surface * surface = IMG_Load(this->file.c_str());

		int mode = GL_RGB;

		if (surface->format->BytesPerPixel == 4) {
			mode = GL_RGBA;
		}
		glGenTextures(1, &textureId);
		glBindTexture(GL_TEXTURE_2D, textureId);
		glTexImage2D(GL_TEXTURE_2D, 0, mode, surface->w, surface->h, 0, mode, GL_UNSIGNED_BYTE, surface->pixels);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		SDL_FreeSurface(surface);
	}

private:
	string file;
	GLuint textureId;
};

