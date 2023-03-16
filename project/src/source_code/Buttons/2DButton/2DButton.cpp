#include "2DButton.h"

void TwoDButton::ButtonPressed() const
{
	this->menuBtn->SetMenuStatus(this->menuBtn->IsHidden() ^ 1);
}

void TwoDButton::RenderButton(Texture2D* texture2) {
    RenderSimpleMesh(
        Globals::GetMeshes(this->GetMeshID()),
        Globals::GetShaders(this->GetShaderID()),
        this->getTransformationMatrix(),
        Globals::GetStaticCamera(),
        Globals::GetTextures(this->GetTextID()),
        texture2
    );

    if (!this->menuBtn->IsHidden())
        RenderSimpleMesh(
            Globals::GetMeshes(this->menuBtn->GetMeshID()),
            Globals::GetShaders(this->menuBtn->GetShaderID()),
            this->menuBtn->getTransformationMatrix(),
            Globals::GetStaticCamera(),
            Globals::GetTextures(this->menuBtn->GetTextID())
        );


}
