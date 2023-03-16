#include "Globals.h"

void Globals::SetMainCamera(implemented::Camera* camera)
{
    mainCamera = camera;
}

void Globals::SetStaticCamera(implemented::Camera* camera)
{
    staticCamera = camera;
}

Mesh* Globals::GetMeshes(std::string meshID)
{
    return meshes[meshID];
}

Shader* Globals::GetShaders(std::string shaderID)
{
    return shaders[shaderID];
}

Texture2D* Globals::GetTextures(std::string textureID)
{
    return mapTextures[textureID];
}

implemented::Camera* Globals::GetMainCamera()
{
    return mainCamera;
}

implemented::Camera* Globals::GetStaticCamera()
{
    return staticCamera;
}

void Globals::AddMesh(Mesh* mesh)
{
    meshes[mesh->GetMeshID()] = mesh;
}

void Globals::AddShader(Shader* shader)
{
    shaders[shader->GetName()] = shader;
}

void Globals::AddTexture(std::string textName, Texture2D* texture)
{
    mapTextures[textName] = texture;
}

std::unordered_map<std::string, Mesh*> Globals::meshes;
std::unordered_map<std::string, Shader*> Globals::shaders;
std::unordered_map<std::string, Texture2D*> Globals::mapTextures;
implemented::Camera* Globals::mainCamera;
implemented::Camera* Globals::staticCamera;
