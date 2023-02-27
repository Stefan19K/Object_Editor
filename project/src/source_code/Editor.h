#pragma once

#include "components/simple_scene.h"
#include "source_code/Camera.h"
#include "Macros.h"
#include "Buttons/Button.h"
#include "Buttons/2DButton/2DButton.h"
#include "Buttons/3DButton/3DButton.h"


namespace ed
{
    class Editor : public gfxc::SimpleScene
    {
    public:
        struct ViewportArea
        {
            ViewportArea() : x(0), y(0), width(1), height(1) {}
            ViewportArea(int x, int y, int width, int height)
                : x(x), y(y), width(width), height(height) {}
            int x;
            int y;
            int width;
            int height;
        };

        Editor();
        ~Editor();

        void Init() override;

    private:
        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;

        void RenderMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, implemented::Camera* cam);
        void RenderSimpleMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, implemented::Camera* cam, Texture2D* texture1, Texture2D* texture2 = NULL);
        Texture2D* Editor::CreateTextureColor(unsigned int width, unsigned int height, glm::vec3 color);
        Texture2D* CreateRandomTexture(unsigned int width, unsigned int height);

        void CreateCameras();
        void CreateTextures();
        void CreateObjects();
        void CreateButtons();
        void CreateShaders();

        void RenderMainScene();
        void RenderButtonMenu();

        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
        void OnWindowResize(int width, int height) override;

    protected:
        implemented::Camera* mainCamera;
        implemented::Camera* staticCamera;
        std::unordered_map<std::string, Texture2D*> mapTextures;
        std::vector<Button*> buttons;
        ViewportArea staticViewportArea;
        glm::ivec2 resolution;

        float zNear;
        float zFar;
        float fov;
        float aspect;

        int hovButIndex;
    };
}
