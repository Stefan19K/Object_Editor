#pragma once

#include "source_code/Buttons/Button.h"
#include <source_code/Buttons/menuButton/MenuButton.h>

class TwoDButton : public Button{
private:
	MenuButton* menuBtn;

public:
	TwoDButton(
		string meshID,
		string shaderID,
		string textureID,
		vec3 t,
		vec3 r,
		vec3 s
	) : Button(meshID, shaderID, textureID, t, r, s) {
		this->menuBtn = new MenuButton(
			"quad", 
			"editorShader", 
			"MenuButton", 
			vec2(35.0f, 635.0f), 
			vec2(0.0f), 
			vec2(80.0f)
		);
	}

	TwoDButton(
		string meshID,
		string shaderID,
		string textureID,
		vec2 t = vec2(0.0f), 
		vec2 r = vec2(0.0f), 
		vec2 s = vec2(1.0f)
	) : Button(meshID, shaderID, textureID, t, r, s) {
		this->menuBtn = new MenuButton(
			"quad",
			"editorShader",
			"MenuButton",
			vec2(35.0f, 635.0f),
			vec2(0.0f),
			vec2(80.0f)
		);
	}

	virtual void ButtonPressed() const;

	virtual void RenderButton(Texture2D* texture2 = NULL);
	/*void ShowMenu();
	void HideMenu();*/
};
