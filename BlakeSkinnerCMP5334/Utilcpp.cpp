#pragma once
#include "pch.h"
#include <SDL.h>
#include <glew.h>
#include <SDL_opengl.h>
#include <stdio.h>
#include <string>
#include <fstream>

using namespace std;

namespace Util {
	string readFile(string file) {
		string fileString;
		ifstream fStream(file.c_str());
		fileString.assign((std::istreambuf_iterator<char>(fStream)), std::istreambuf_iterator<char>());
		return fileString
	}
}
//completed slide 5