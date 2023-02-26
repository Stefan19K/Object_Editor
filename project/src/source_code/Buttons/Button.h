#pragma once

#include <string>
#include <glm/ext/vector_float3.hpp>
#include <glm/ext/vector_float2.hpp>
#include <glm/ext/matrix_float4x4.hpp>
#include <utils/math_utils.h>
#include <glm/ext/matrix_transform.hpp>

using namespace glm;

class Button {
private:
	std::string meshID;
	std::string textID;
	vec3 translation;
	vec3 rotation;
	vec3 scalation;
	mat4 matrix;

public:
	Button(std::string meshID, std::string textID, vec3 t = vec3(0.0f), vec3 r = vec3(0.0f), vec3 s = vec3(1.0f)) {
		this->meshID = meshID;
		this->textID = textID;
		this->translation = t;
		this->rotation = r;
		this->scalation = s;

		UpdateMatrix();
	}

	Button(std::string meshID, std::string textID, vec2 t = vec2(0.0f), vec2 r = vec2(0.0f), vec2 s = vec2(1.0f)) {
		this->meshID = meshID;
		this->textID = textID;
		this->translation = vec3(t.x, t.y, 0.0f);
		this->rotation = vec3(r.x, r.y, 0.0f);
		this->scalation = vec3(s.x, s.y, 1.0f);

		UpdateMatrix();
	}

	virtual void ButtonPressed() const;

	void UpdateMatrix();
	mat4 getTransformationMatrix();
	std::string GetMeshID();
	std::string GetTextID();
};
