#pragma once

#include "source_code/Buttons/Button.h"

class ThreeDButton : public Button {
public:
	ThreeDButton(
		Mesh* meshID, 
		Texture2D* textID,
		vec3 t,
		vec3 r,
		vec3 s
	) : Button(meshID, textID, t, r, s) {
	}

	ThreeDButton(
		Mesh* meshID, 
		Texture2D* textID,
		vec2 t = vec2(0.0f),
		vec2 r = vec2(0.0f),
		vec2 s = vec2(1.0f)
	) : Button(meshID, textID, t, r, s) {
	}

	virtual void ButtonPressed() const;
};
