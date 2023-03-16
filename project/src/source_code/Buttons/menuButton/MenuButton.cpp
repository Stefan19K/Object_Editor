#include "MenuButton.h"

void MenuButton::ButtonPressed() const
{
}

bool MenuButton::IsHidden()
{
	return this->hidden;
}

void MenuButton::SetMenuStatus(bool status)
{
	this->hidden = status;
}
