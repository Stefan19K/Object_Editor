#pragma once

#include "source_code/Buttons/Button.h"

class ThreeDButton : public Button {
public:
	ThreeDButton(std::string meshID,
		std::string textID,
		vec3 t = vec3(0.0f),
		vec3 r = vec3(0.0f),
		vec3 s = vec3(1.0f)
	) : Button(meshID, textID, t, r, s) {}

	ThreeDButton(std::string meshID,
		std::string textID,
		vec2 t = vec2(0.0f),
		vec2 r = vec2(0.0f),
		vec2 s = vec2(1.0f)
	) : Button(meshID, textID, t, r, s) {}

	virtual void ButtonPressed() const;
};
