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
}

mat4 Button::getTransformationMatrix()
{
	return matrix;
}

bool Button::isHovered(const float x, const float y)
{
	float x1{this->translation.x - this->scalation.x / 2.0f};
	float x2{ this->translation.x + this->scalation.x / 2.0f };
	float y1{ this->translation.y - this->scalation.y / 2.0f };
	float y2{ this->translation.y + this->scalation.y / 2.0f };

	if (x >= x1 && x <= x2 && y >= y1 && y <= y2)
		return true;

	return false;
}

std::string Button::GetMeshID()
{
	return meshID;
}

std::string Button::GetTextID()
{
	return textID;
}

