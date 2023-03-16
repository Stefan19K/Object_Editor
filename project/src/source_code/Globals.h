#pragma once

#include <unordered_map>
#include <core/gpu/mesh.h>
#include <core/gpu/shader.h>
#include "Camera.h"

class Globals {
private:
	static std::unordered_map<std::string, Mesh*> meshes;
	static std::unordered_map<std::string, Shader*> shaders;
	static std::unordered_map<std::string, Texture2D*> mapTextures;
	static implemented::Camera* mainCamera;
	static implemented::Camera* staticCamera;

public:
	static void AddMesh(Mesh* mesh);
	static void AddShader(Shader* shader);
	static void AddTexture(std::string textName, Texture2D* texture);

	static void AddMeshes(std::unordered_map<std::string, Mesh*> meshes);
	static void AddShaders(std::unordered_map<std::string, Shader*> shaders);
	static void AddTextures(std::unordered_map<std::string, Texture2D*> mapTextures);

	// Setters.
	static void SetMainCamera(implemented::Camera* camera);
	static void SetStaticCamera(implemented::Camera* camera);

	// Getters.
	static Mesh* GetMeshes(std::string meshID);
	static Shader* GetShaders(std::string shaderID);
	static Texture2D* GetTextures(std::string textureID);
	static implemented::Camera* GetMainCamera();
	static implemented::Camera* GetStaticCamera();
};