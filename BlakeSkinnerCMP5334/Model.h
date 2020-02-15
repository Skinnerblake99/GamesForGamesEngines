#pragma once
#include "pch.h"
#include <SDL.h>
#include <glew.h>
#include <SDL_opengl.h>
#include <glm/glm.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <vector>
#include <string>

using namespace std;

class Model {
public:
	friend class ModelRenderer;

	Model(string file) {
		position = glm::vec3(0, 0, 0);
		rotation = glm::vec3(0, 45, 0);
		scale = glm::vec3(1.0f, 1.0f, 1.0f);
		this->file = file;
	}

	virtual ~Model() {

	}

	void init() {
		Assimp::Importer importer;
		const aiScene * scene = importer.ReadFile(file,
			aiProcess_CalcTangentSpace |
			aiProcess_Triangulate |
			aiProcess_JoinIdenticalVertices |
			aiProcess_SortByPType
		);
		if (!scene) {
			printf("assimp file failed to load: %s", file);
			return;
		}
		for (int i = 0; i < scene->mNumMeshes; i++) {
			aiMesh *mesh = scene->mMeshes[i];
			vector<GLfloat> vertices;
			vector<GLuint> indices;
			for (int j = 0; j < mesh->mNumVertices; j++) {
				const aiVector3D *pos = &mesh->mVertices[j];
				vertices.push_back(pos->x);
				vertices.push_back(pos->y);
				vertices.push_back(pos->z);
			}
			for (int j = 0; j < mesh->mNumFaces; j++) {
				aiFace * f = &mesh->mFaces[j];
				if (f->mNumIndices != 3) {
					//only load triangluar faces
					continue;
				}
				indices.push_back(f->mIndices[0]);
				indices.push_back(f->mIndices[1]);
				indices.push_back(f->mIndices[2]);
			}

			GLuint vertexBufferObject;
			GLuint indexBufferObject;


			//Create VBO
			glGenBuffers(1, &vertexBufferObject);
			glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
			glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), &vertices[i], GL_STATIC_DRAW);

			//Create IBO
			glGenBuffers(1, &indexBufferObject);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferObject);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices[i], GL_STATIC_DRAW);
			vbos.push_back(vertexBufferObject);
			ibos.push_back(indexBufferObject);
			indexCounts.push_back(indices.size());
		}
	
		
	}
private:
	//Transform of the model
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;

	string file;
	vector<GLuint> vbos;
	vector<GLuint> ibos;
	vector<int> indexCounts;
};