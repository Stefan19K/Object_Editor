#pragma once

#include "source_code/Buttons/Button.h"

class ShapeButton : public Button {
public:
	ShapeButton(
		string meshID,
		string shaderID,
		string textureID,
		vec3 t,
		vec3 r,
		vec3 s
	) : Button(meshID, shaderID, textureID, t, r, s) {
	}

	ShapeButton(
		string meshID,
		string shaderID,
		string textureID,
		vec2 t = vec2(0.0f),
		vec2 r = vec2(0.0f),
		vec2 s = vec2(1.0f)
	) : Button(meshID, shaderID, textureID, t, r, s) {
	}

	virtual void ButtonPressed() const;
};