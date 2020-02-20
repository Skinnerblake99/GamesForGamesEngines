#include "pch.h"
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

	uvLocation = glGetAttribLocation(programId, "uv");

	if (uvLocation == -1)
	{
		printf("uv is not a valid glsl program variable!\n");
		return;
	}

	modelMatrixLocation = glGetUniformLocation(programId, "modelMatrix");
	viewMatrixLocation = glGetUniformLocation(programId, "viewMatrix");
	projectionMatrixLocation = glGetUniformLocation(programId, "projectionMatrix");
	textureSamplerLocation = glGetUniformLocation(programId, "textureSampler");
}


void ModelRenderer::renderModel(Model *  m)
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

	//camera->updateViewMatrix();


	glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, glm::value_ptr(modelMatrix));
	glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, glm::value_ptr(camera->getViewMatrix()));
	glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, glm::value_ptr(camera->getprojectionMatrix()));

	//Enable vertex position
	glEnableVertexAttribArray(vertexPositionLocation);

	//Set vertex data
	glBindBuffer(GL_ARRAY_BUFFER, m->vbos[0]);
	glVertexAttribPointer(vertexPositionLocation, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), NULL);
	glEnableVertexAttribArray(uvLocation);
	glBindBuffer(GL_ARRAY_BUFFER, m->uvbos[0]);
	glVertexAttribPointer(uvLocation, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), NULL);
	//Set the texture
	glActiveTexture(GL_TEXTURE0);
	glUniform1i(textureSamplerLocation, 0);
	glBindTexture(GL_TEXTURE_2D, m->texture->textureId);

	//Set index data and render
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m->ibos[0]);
	
	glDrawElements(GL_TRIANGLES, m->indexCounts[0], GL_UNSIGNED_INT, NULL);

	//Disable vertex position
	glDisableVertexAttribArray(vertexPositionLocation);

	//Unbind program
	glUseProgram(NULL);
}
//Second model
void ModelRenderer::renderModel2(Model2 * a)
{
	//Bind program (the shader)
	glUseProgram(programId);

	glm::vec3 translation = a->position;
	glm::vec3 rotation = a->rotation;
	glm::vec3 scale = a->scale;

	glm::mat4 modelMatrix = glm::mat4(1.0f);
	modelMatrix = glm::rotate(modelMatrix, rotation.x * 180.0f / 3.14159265f, glm::vec3(1.0f, 0.0f, 0.0f));
	modelMatrix = glm::rotate(modelMatrix, rotation.y * 180.0f / 3.14159265f, glm::vec3(0.0f, 1.0f, 0.0f));
	modelMatrix = glm::rotate(modelMatrix, rotation.z * 180.0f / 3.14159265f, glm::vec3(0.0f, 0.0f, 1.0f));
	modelMatrix = glm::translate(modelMatrix, translation);
	modelMatrix = glm::scale(modelMatrix, scale);

	//camera->updateViewMatrix();


	glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, glm::value_ptr(modelMatrix));
	glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, glm::value_ptr(camera->getViewMatrix()));
	glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, glm::value_ptr(camera->getprojectionMatrix()));

	//Enable vertex position
	glEnableVertexAttribArray(vertexPositionLocation);

	//Set vertex data
	glBindBuffer(GL_ARRAY_BUFFER, a->vbos[0]);
	glVertexAttribPointer(vertexPositionLocation, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), NULL);
	glEnableVertexAttribArray(uvLocation);
	glBindBuffer(GL_ARRAY_BUFFER, a->uvbos[0]);
	glVertexAttribPointer(uvLocation, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), NULL);
	//Set the texture
	glActiveTexture(GL_TEXTURE0);
	glUniform1i(textureSamplerLocation, 0);
	glBindTexture(GL_TEXTURE_2D, a->texture->textureId);

	//Set index data and render
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, a->ibos[0]);

	glDrawElements(GL_TRIANGLES, a->indexCounts[0], GL_UNSIGNED_INT, NULL);

	//Disable vertex position
	glDisableVertexAttribArray(vertexPositionLocation);

	//Unbind program
	glUseProgram(NULL);
}

void ModelRenderer::renderTerrain(Terrain * t)
{
	//Bind program (the shader)
	glUseProgram(programId);

	glm::vec3 translation = glm::vec3(0, -50, 0);
	glm::vec3 rotation = glm::vec3(0, 0, 0);
	glm::vec3 scale = glm::vec3(1, 1, 1);

	glm::mat4 modelMatrix = glm::mat4(1.0f);
	modelMatrix = glm::rotate(modelMatrix, rotation.x * 180.0f / 3.14159265f, glm::vec3(1.0f, 0.0f, 0.0f));
	modelMatrix = glm::rotate(modelMatrix, rotation.y * 180.0f / 3.14159265f, glm::vec3(0.0f, 1.0f, 0.0f));
	modelMatrix = glm::rotate(modelMatrix, rotation.z * 180.0f / 3.14159265f, glm::vec3(0.0f, 0.0f, 1.0f));
	modelMatrix = glm::translate(modelMatrix, translation);
	modelMatrix = glm::scale(modelMatrix, scale);

	glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, glm::value_ptr(modelMatrix));
	glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, glm::value_ptr(camera->getViewMatrix()));
	glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, glm::value_ptr(camera->getprojectionMatrix()));

	//Enable vertex position
	glEnableVertexAttribArray(vertexPositionLocation);

	//Set vertex data
	glBindBuffer(GL_ARRAY_BUFFER, t->vertexBufferObject);
	glVertexAttribPointer(vertexPositionLocation, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), NULL);

	glEnableVertexAttribArray(uvLocation);
	glBindBuffer(GL_ARRAY_BUFFER, t->uvBufferObject);
	glVertexAttribPointer(uvLocation, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), NULL);

	//set the texture
	glActiveTexture(GL_TEXTURE0);
	glUniform1i(textureSamplerLocation, 0);
	glBindTexture(GL_TEXTURE_2D, t->texture->textureId);

	//Set index data and render
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, t->indexBufferObject);

	glDrawElements(GL_TRIANGLES, t->indexCount, GL_UNSIGNED_INT, NULL);

	//Disable vertex position
	glDisableVertexAttribArray(vertexPositionLocation);

	//Unbind program
	glUseProgram(NULL);
}

