#include "Button.h"

void Button::ButtonPressed() const
{
}

void Button::UpdateMatrix()
{
	matrix = mat4(1.0f);
	matrix = translate(matrix, translation);
	matrix = rotate(matrix, RADIANS(rotation.x), vec3(1, 0, 0));
	matrix = rotate(matrix, RADIANS(rotation.y), vec3(0, 1, 0));
	matrix = rotate(matrix, RADIANS(rotation.z), vec3(0, 0, 1));
	matrix = scale(matrix, scalation);

	/*Here we place the bottom left corner of the button in the
	bottom left corner of the viewport.*/
	matrix = translate(matrix, vec3(0.5f, 0.5f, 0));
}

mat4 Button::getTransformationMatrix()
{
	return matrix;
}

std::string Button::GetMeshID()
{
	return meshID;
}

std::string Button::GetTextID()
{
	return textID;
}

