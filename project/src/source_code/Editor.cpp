#include "source_code/Editor.h"

#include <vector>
#include <string>
#include <iostream>

using namespace std;
using namespace ed;

Editor::Editor()
{
}


Editor::~Editor()
{
}


void Editor::Init()
{
    camera = new implemented::Camera();
    camera->Set(glm::vec3(0, 1, 3.5f), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));

    zNear = 0.01f;
    zFar = 200.0f;

    fov = RADIANS(60);
    aspect = window->props.aspectRatio;

    projectionMatrix = glm::perspective(fov, aspect, zNear, zFar);
}


void Editor::FrameStart()
{
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    glViewport(0, 0, resolution.x, resolution.y);
}


void Editor::Update(float deltaTimeSeconds)
{
}


void Editor::FrameEnd()
{
    projectionMatrix = glm::perspective(fov, aspect, zNear, zFar);
    DrawCoordinateSystem(camera->GetViewMatrix(), projectionMatrix);
}


void Editor::RenderMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix)
{
    if (!mesh || !shader || !shader->program)
        return;

    shader->Use();
    glUniformMatrix4fv(shader->loc_view_matrix, 1, GL_FALSE, glm::value_ptr(camera->GetViewMatrix()));
    glUniformMatrix4fv(shader->loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
    glUniformMatrix4fv(shader->loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

    mesh->Render();
}

void Editor::OnInputUpdate(float deltaTime, int mods)
{
    if (window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
    {
        float cameraSpeed = 2.0f;

        if (window->KeyHold(GLFW_KEY_W)) {
            camera->TranslateForward(cameraSpeed * deltaTime);

        }

        if (window->KeyHold(GLFW_KEY_A)) {
            camera->TranslateRight(-cameraSpeed * deltaTime);
        }

        if (window->KeyHold(GLFW_KEY_S)) {
            camera->TranslateForward(-cameraSpeed * deltaTime);
        }

        if (window->KeyHold(GLFW_KEY_D)) {
            camera->TranslateRight(cameraSpeed * deltaTime);
        }

        if (window->KeyHold(GLFW_KEY_Q)) {
            camera->TranslateUpward(-cameraSpeed * deltaTime);
        }

        if (window->KeyHold(GLFW_KEY_E)) {
            camera->TranslateUpward(cameraSpeed * deltaTime);
        }
    }
}


void Editor::OnKeyPress(int key, int mods)
{
}


void Editor::OnKeyRelease(int key, int mods)
{
}


void Editor::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    if (window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
    {
        float sensivityOX = 0.001f;
        float sensivityOY = 0.001f;

        if (window->GetSpecialKeyState() == 0) {
            float angleX = (-deltaX) * sensivityOY;
            float angleY = (-deltaY) * sensivityOX;
            camera->RotateFirstPerson_OY(angleX);
            camera->RotateFirstPerson_OX(angleY);
        }
    }
}


void Editor::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
}


void Editor::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
}


void Editor::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void Editor::OnWindowResize(int width, int height)
{
}
