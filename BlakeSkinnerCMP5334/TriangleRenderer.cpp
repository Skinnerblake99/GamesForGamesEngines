#include "pch.h"
#include "TriangleRenderer.h"
#include "Utilcpp.cpp"
//Got to slide 12 - 11/02/2020
//vertices
//test push
GLfloat vertexData[] =
{
	-0.5f, -0.5f, -1.0f,
	0.5f, -0.5f, -1.0f,
	0.0f, 0.5f, -1.0f
};

//indices 
GLuint indexData[] = { 0,1,2 };

TriangleRenderer::TriangleRenderer(Camera* camera) {
	this->camera = camera;
}

TriangleRenderer::~TriangleRenderer() {

}

void TriangleRenderer::init() {
	Util util;
	//A program is a combination of a vertext and a fragment shader.
	programId = glCreateProgram();
	//First the vertex shader source code needs to be loaded, compiled and then attached to the program
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	//This is the vertex shader program source code.This can be modified to load a file
	//later turotials will look at loading shaders from a file.
	//const GLchar* vertexShaderSource[] = {
	//	"#version 140\nin vec2 vertexPos2D;"
	//	"void main() { gl_Position = vec4( vertexPos2D.x, vertexPos2D.y, 0, 1);}"
	//11/02/2020

	string fileText = util.readFile("vertexshader.shader");
	const GLchar * shaderSource = fileText.c_str();

	glShaderSource(vertexShader, 1, (const GLchar**)&shaderSource, NULL);
	//sglShaderSource(vertexShader, 1, vertexShaderSource, Null);
	glCompileShader(vertexShader);
	};

	glShaderSource(vertexShader, 1, vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	GLint vShaderCompiled = GL_FALSE;
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &vShaderCompiled);

	if (vShaderCompiled != GL_TRUE)
	{
		printf("Unable to compile vertex shader %d!\n", vertexShader);
		return;
	}

	glAttachShader(programId, vertexShader);

	//Next, the fragment shader source code needs to be loaded, compiled and then attached to the program
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	//This is the fragment shader program source cide, This can be modified to be loaded from a file
	const GLchar* fragmentShaderSource[] = 
	{
		"#version 140\nout vec4 fragmentColor;"
		"void main() { fragmentColor = vec4(1.0,1.0,1.0,1.0);}"
	};

    //Set fragment source
	glShaderSource(fragmentShader, 1, fragmentShaderSource, NULL);
    //Compile fragment source
	glCompileShader(fragmentShader);
	//Check fragment shader for Errors
	GLint fShaderCompiled = GL_FALSE;
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &fShaderCompiled);
	if (fShaderCompiled != GL_TRUE)
	{
		printf("Unable to compile fragment shader %d!\n", fragmentShader);
		return;
	}
	//Attach fragment shader to program
	glAttachShader(programId, fragmentShader);

	//Link program
	glLinkProgram(programId);

	//Check for errors
	GLint programSuccess = GL_TRUE;
	glGetProgramiv(programId, GL_LINK_STATUS, &programSuccess);
	if (programSuccess != GL_TRUE)
	{
		printf("Error linking program %d!\n", programId);
		return;
	}

	vertexPos2DLocation = glGetAttribLocation(programId, "vertexPos2D");
	
	if (vertexPos2DLocation == -1)
	{
		printf("vertexPos2D is not a valid glsl program variable!\n");
		return;
	}

	//Create VBO
	glGenBuffers(1, &vertexBufferObject);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
	glBufferData(GL_ARRAY_BUFFER, 2 * 4 * sizeof(GLfloat), vertexData, GL_STATIC_DRAW);

	//Create IBO
	glGenBuffers(1, &indexBufferObject);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferObject);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 4 * sizeof(GLuint), indexData, GL_STATIC_DRAW);

}

void TriangleRenderer::update()
{

}

void TriangleRenderer::draw()
{
   //Bind program (the shader)
   glUseProgram(programId);

   //Enable vertex position
   glEnableVertexAttribArray(vertexPos2DLocation);

   //Set vertex data
   glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
   glVertexAttribPointer(vertexPos2DLocation, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), NULL);

   //Set index data and render
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferObject);
   glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_INT, NULL);

   //Disable vertex positions
   glDisableVertexAttribArray(vertexPos2DLocation);

   //Unbind program
   glUseProgram(NULL);
}

void TriangleRenderer::clean()
{
   glDeleteProgram(programId);
}