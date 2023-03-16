#pragma once

#include <string>
#include <glm/ext/vector_float3.hpp>
#include <glm/ext/vector_float2.hpp>
#include <glm/ext/matrix_float4x4.hpp>
#include <utils/math_utils.h>
#include <glm/ext/matrix_transform.hpp>
#include "source_code/Globals.h"

using namespace glm;
using namespace implemented;

class Button {
private:
	string meshID;
	string shaderID;
	string textureID;
	vec3 translation;
	vec3 rotation;
	vec3 scalation;
	mat4 matrix;
	bool isPressed;

public:
	Button(string meshID, string shaderID, string textureID, vec3 t = vec3(0.0f), vec3 r = vec3(0.0f), vec3 s = vec3(1.0f)) {
		this->meshID = meshID;
		this->shaderID = shaderID;
		this->textureID = textureID;
		this->translation = t;
		this->rotation = r;
		this->scalation = s;
		this->isPressed = false;

		UpdateMatrix();
	}

	Button(string meshID, string shaderID, string textureID, vec2 t = vec2(0.0f), vec2 r = vec2(0.0f), vec2 s = vec2(1.0f)) {
		this->meshID = meshID;
		this->shaderID = shaderID;
		this->textureID = textureID;
		this->translation = vec3(t.x, t.y, 0.0f);
		this->rotation = vec3(r.x, r.y, 0.0f);
		this->scalation = vec3(s.x, s.y, 1.0f);
		this->isPressed = false;

		UpdateMatrix();
	}

	virtual void ButtonPressed() const;

	void Resize(float newX, float newY);
	void UpdateMatrix();
	mat4 getTransformationMatrix();

	bool isHovered(const float x, const float y);

	virtual void RenderButton(Texture2D* texture2 = NULL);

	// Getters.
	string GetMeshID();
	string GetTextID();
	string GetShaderID();
};

void RenderSimpleMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, Camera* cam, Texture2D* texture1, Texture2D* texture2 = NULL);
