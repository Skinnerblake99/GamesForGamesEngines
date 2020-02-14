#include "ModelRenderer.h"


ModelRenderer::ModelRenderer::ModelRenderer(Camera * camera)
{
	this->camera = camera;
}

ModelRenderer::~ModelRenderer()
{

}

void ModelRenderer::init()
{
	Util util;
	//A program is a combination of a vertex and fragment shader.
	programId = glCreateProgram();

	//First the vertex shader source code needs to be loaded, compiled and then attached to the program
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

	string fileText = util.readFile("vertexshader.shader");
	const GLchar * shaderSource = fileText.c_str();

	glShaderSource(vertexShader, 1, (const GLchar**)&shaderSource, NULL);
	//sglShaderSource(vertexShader, 1, vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	GLint vShaderCompiled = GL_FALSE;
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &vShaderCompiled);

	if (vShaderCompiled != GL_TRUE)
	{
		printf("Unable to compile vertex shader %d!\n", vertexShader);
		util.printShaderLog(vertexShader);
		return;
	}

	glAttachShader(programId, vertexShader);

	//Next, the fragment shader source code needs to be loaded, compiled and then attached to the program
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	fileText = util.readFile("fragmentshader.shader");
	shaderSource = fileText.c_str();

	//Set fragment source
	glShaderSource(fragmentShader, 1, (const GLchar**)&shaderSource, NULL);

	//Compile fragment source
	glCompileShader(fragmentShader);

	//Check fragment shader for errors
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

	vertexPositionLocation = glGetAttribLocation(programId, "vertexPosition");

	if (vertexPositionLocation == -1)
	{
		printf("vertexPos2D is not a valid glsl program variable!\n");
		return;
	}

	modelMatrixLocation = glGetUniformLocation(programId, "modelMatrix");
	viewMatrixLocation = glGetUniformLocation(programId, "viewMatrix");
	projectionMatrixLocation = glGetUniformLocation(programId, "projectionMatrix");
}

void ModelRenderer::renderModel(Model * m)
{
	//Bind program (the shader)
	glUseProgram(programId);

	glm::vec3 translation = m->position;
	glm::vec3 rotation = m->rotation;
	glm::vec3 scale = m->scale;

	glm::mat4 modelMatrix = glm::mat4(1.0f);
	modelMatrix = glm::rotate(modelMatrix, rotation.x * 180.0f / 3.14159265f, glm::vec3(1.0f, 0.0f, 0.0f));
	modelMatrix = glm::rotate(modelMatrix, rotation.y * 180.0f / 3.14159265f, glm::vec3(0.0f, 1.0f, 0.0f));
	modelMatrix = glm::rotate(modelMatrix, rotation.z * 180.0f / 3.14159265f, glm::vec3(0.0f, 0.0f, 1.0f));
	modelMatrix = glm::translate(modelMatrix, translation);
	modelMatrix = glm::scale(modelMatrix, scale);

	camera->updateViewMatrix();


	glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, glm::value_ptr(modelMatrix));
	glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, glm::value_ptr(camera->getViewMatrix()));
	glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, glm::value_ptr(camera->getprojectionMatrix()));

	//Enable vertex position
	glEnableVertexAttribArray(vertexPositionLocation);

	//Set vertex data
	glBindBuffer(GL_ARRAY_BUFFER, m->vbos[0]);
	glVertexAttribPointer(vertexPositionLocation, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), NULL);

	//Set index data and render
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m->ibos[0]);

	glDrawElements(GL_TRIANGLES, m->indexCounts[0], GL_UNSIGNED_INT, NULL);

	//Disable vertex position
	glDisableVertexAttribArray(vertexPositionLocation);

	//Unbind program
	glUseProgram(NULL);
}
