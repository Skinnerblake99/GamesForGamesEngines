#pragma once
#include "pch.h"
#include <SDL.h>
#include <glew.h>
#include <SDL_opengl.h>
#include <stdio.h>
#include <string>
#include <fstream>

using namespace std;

struct Util {
	string readFile(string file) {
		string fileString;
		ifstream fStream(file.c_str());
		fileString.assign((std::istreambuf_iterator<char>(fStream)), std::istreambuf_iterator<char>());
		return fileString;
	}

	void printShaderLog(GLuint shader)
	{
		//Shader log length
		int infoLogLength = 0;
		int maxLength = 0;

		//get length of error then allocate to string
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);
		char* infoLog = new char[maxLength];
		glGetShaderInfoLog(shader, maxLength, &infoLogLength, infoLog);

		if (infoLogLength > 0)
		{
			printf("%s\n", infoLog);
		}
		delete[] infoLog;
	}
};