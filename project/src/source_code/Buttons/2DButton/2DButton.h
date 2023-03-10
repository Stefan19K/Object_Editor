#pragma once

#include "source_code/Buttons/Button.h"
#include <source_code/Buttons/menuButton/MenuButton.h>

class TwoDButton : public Button{
public:
	TwoDButton(
		Mesh* meshID,
		Shader* shader,
		Camera* cam,
		Texture2D* text1,
		Texture2D* text2,
		vec3 t,
		vec3 r,
		vec3 s
	) : Button(meshID, shader, cam, text1, text2, t, r, s) {
	}

	TwoDButton(
		Mesh* meshID,
		Shader* shader,
		Camera* cam,
		Texture2D* text1,
		Texture2D* text2,
		vec2 t = vec2(0.0f), 
		vec2 r = vec2(0.0f), 
		vec2 s = vec2(1.0f)
	) : Button(meshID, shader, cam, text1, text2, t, r, s) {
	}

	virtual void ButtonPressed() const;

	/*void ShowMenu();
	void HideMenu();*/
};
