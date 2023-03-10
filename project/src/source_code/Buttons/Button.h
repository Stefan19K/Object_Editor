#pragma once

#include <string>
#include <glm/ext/vector_float3.hpp>
#include <glm/ext/vector_float2.hpp>
#include <glm/ext/matrix_float4x4.hpp>
#include <utils/math_utils.h>
#include <glm/ext/matrix_transform.hpp>
#include <core/gpu/mesh.h>
#include <core/gpu/shader.h>
#include <source_code/Camera.h>

using namespace glm;
using namespace implemented;

class Button {
private:
	Mesh *meshID;
	Shader *shader;
	Camera *cam;
	Texture2D *text1;
	Texture2D *text2;
	vec3 translation;
	vec3 rotation;
	vec3 scalation;
	mat4 matrix;
	bool isPressed;

public:
	Button(Mesh *meshID, Shader *shader, Camera *cam, Texture2D *text1, Texture2D *text2, vec3 t = vec3(0.0f), vec3 r = vec3(0.0f), vec3 s = vec3(1.0f)) {
		this->meshID = meshID;
		this->shader = shader;
		this->cam = cam;
		this->text1 = text1;
		this->text2 = text2;
		this->translation = t;
		this->rotation = r;
		this->scalation = s;
		this->isPressed = false;

		UpdateMatrix();
	}

	Button(Mesh* meshID, Shader* shader, Camera* cam, Texture2D* text1, Texture2D* text2, vec2 t = vec2(0.0f), vec2 r = vec2(0.0f), vec2 s = vec2(1.0f)) {
		this->meshID = meshID;
		this->shader = shader;
		this->cam = cam;
		this->text1 = text1;
		this->text2 = text2;
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

	void RenderButton(Texture2D* texture2 = NULL);

	Mesh* GetMeshID();
	Texture2D* GetTextID();
};

void RenderSimpleMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, Camera* cam, Texture2D* texture1, Texture2D* texture2 = NULL);
