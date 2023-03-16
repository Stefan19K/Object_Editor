#include "source_code/Editor.h"

#include <vector>
#include <string>
#include <iostream>
#include "GeometryShapes.h"

using namespace std;
using namespace ed;

Editor::Editor()
{
    hovButIndex = -1;
    presButIndex = -1;
}

Editor::~Editor()
{
}

void Editor::Init()
{
    resolution = window->GetResolution();         // initial 1280 x 720.
    staticViewportArea = ViewportArea(0, 0, resolution.x, resolution.y);

    CreateCameras();
    CreateTextures();
    CreateObjects();
    CreateShaders();
    CreateButtons();

    mainCamera = Globals::GetMainCamera();
}

void Editor::FrameStart()
{
    glClearColor(0.3f, 0.3f, 0.3f, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Editor::Update(float deltaTimeSeconds)
{
    // RenderMainScene();
    RenderButtonMenu();
}

void Editor::FrameEnd()
{    
}

void Editor::RenderMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, implemented::Camera* cam)
{
    if (!mesh || !shader || !shader->program)
        return;

    // Render an object using the specified shader and the specified position
    shader->Use();
    glUniformMatrix4fv(shader->loc_view_matrix, 1, GL_FALSE, glm::value_ptr(cam->GetViewMatrix()));
    glUniformMatrix4fv(shader->loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(cam->projectionMatrix));
    glUniformMatrix4fv(shader->loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

    mesh->Render();
}

//void Editor::RenderSimpleMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, implemented::Camera* cam, Texture2D* texture1, Texture2D* texture2)
//{
//    if (!mesh || !shader || !shader->GetProgramID())
//        return;
//
//    glUseProgram(shader->program);
//
//    GLint loc_model_matrix = glGetUniformLocation(shader->program, "Model");
//    glUniformMatrix4fv(loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));
//
//    glm::mat4 viewMatrix = cam->GetViewMatrix();
//    int loc_view_matrix = glGetUniformLocation(shader->program, "View");
//    glUniformMatrix4fv(loc_view_matrix, 1, GL_FALSE, glm::value_ptr(viewMatrix));
//
//    int loc_projection_matrix = glGetUniformLocation(shader->program, "Projection");
//    glUniformMatrix4fv(loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(cam->projectionMatrix));
//
//    int multipleTextures = 0;
//    if (texture2 != NULL) {
//        multipleTextures = 1;
//    }
//
//    loc_projection_matrix = glGetUniformLocation(shader->program, "multipleTextures");
//    glUniform1i(loc_projection_matrix, multipleTextures);
//
//    if (texture1)
//    {
//        glActiveTexture(GL_TEXTURE0);
//
//        glBindTexture(GL_TEXTURE_2D, texture1->GetTextureID());
//
//        glUniform1i(glGetUniformLocation(shader->program, "texture_1"), 0);
//
//    }
//
//    if (texture2)
//    {
//        glActiveTexture(GL_TEXTURE1);
//
//        glBindTexture(GL_TEXTURE_2D, texture2->GetTextureID());
//
//        glUniform1i(glGetUniformLocation(shader->program, "texture_2"), 1);
//
//    }
//
//    glBindVertexArray(mesh->GetBuffers()->m_VAO);
//    glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_INT, 0);
//}

Texture2D* Editor::CreateTextureColor(unsigned int width, unsigned int height, glm::vec3 color)
{
    GLuint textureID = 0;
    unsigned int channels = 3;
    unsigned int size = width * height * channels;
    unsigned char* data = new unsigned char[size];

    for (int i{}; i < size; i += 3) {
        data[i] = static_cast<int>(color.x * 255);
        data[i + 1] = static_cast<int>(color.y * 255);
        data[i + 2] = static_cast<int>(color.z * 255);
    }

    unsigned int gl_texture_object;

    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    if (GLEW_EXT_texture_filter_anisotropic) {
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 4);
    }

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);

    glPixelStorei(GL_PACK_ALIGNMENT, 1);
    CheckOpenGLError();

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glGenerateMipmap(GL_TEXTURE_2D);

    CheckOpenGLError();

    Texture2D* texture = new Texture2D();
    texture->Init(textureID, width, height, channels);

    SAFE_FREE_ARRAY(data);
    return texture;
}

Texture2D* Editor::CreateRandomTexture(unsigned int width, unsigned int height)
{
    GLuint textureID = 0;
    unsigned int channels = 3;
    unsigned int size = width * height * channels;
    unsigned char* data = new unsigned char[size];

    glm::vec3 color = glm::vec3((rand() % 256), (rand() % 256), (rand() % 256));
    for (int i{}; i < size; ++i) {
        data[i] = (float)(rand() % 256);
    }

    unsigned int gl_texture_object;

    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    if (GLEW_EXT_texture_filter_anisotropic) {
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 4);
    }

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);

    glPixelStorei(GL_PACK_ALIGNMENT, 1);
    CheckOpenGLError();

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glGenerateMipmap(GL_TEXTURE_2D);

    CheckOpenGLError();

    Texture2D* texture = new Texture2D();
    texture->Init(textureID, width, height, channels);

    SAFE_FREE_ARRAY(data);
    return texture;
}

void ed::Editor::CreateCameras()
{
    // Main camera.
    implemented::Camera* mainCamera;
    mainCamera = new implemented::Camera();
    mainCamera->Set(glm::vec3(0, 1, 3.5f), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
    zNear = 0.01f;
    zFar = 200.0f;
    fov = RADIANS(60);
    aspect = window->props.aspectRatio;
    mainCamera->projectionMatrix = glm::perspective(fov, aspect, zNear, zFar);
    Globals::SetMainCamera(mainCamera);

    // Static camera.
    implemented::Camera* staticCamera;
    staticCamera = new implemented::Camera();
    staticCamera->Set(glm::vec3(5, 5, 1), glm::vec3(5, 5, 0), glm::vec3(0, 1, 0));
    zNear = 0.01f;
    zFar = 100.0f;
    float left = 0.0f;
    float right = resolution.x;
    float bottom = 0.0f;
    float top = resolution.y;
    staticCamera->projectionMatrix = glm::ortho(left, right, bottom, top, zNear, zFar);
    Globals::SetStaticCamera(staticCamera);
    /*float left = -5.0f;
    float right =5.0f;
    float bottom = -50.0f;
    float top = 50.0f;
    staticCamera->projectionMatrix = glm::ortho(left, right, bottom, top, zNear, zFar);*/
}

void ed::Editor::CreateTextures()
{
    Texture2D* texture;
    /*Texture2D* texture = new Texture2D();
    texture->Load2D(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::TEXTURES, "crate.jpg").c_str(), GL_REPEAT);
    mapTextures["crate"] = texture;*/

    Globals::AddTexture("red", CreateTextureColor(256, 256, RED));

    Globals::AddTexture("cyan", CreateTextureColor(256, 256, CYAN));

    Globals::AddTexture("white", CreateTextureColor(256, 256, WHITE));

    Globals::AddTexture("background", CreateTextureColor(256, 256, vec3(0.2f)));

    texture = new Texture2D();
    texture->Load2D(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::TEXTURES, "2D Button.png").c_str(), GL_REPEAT);
    Globals::AddTexture("2DButton", texture);

    texture = new Texture2D();
    texture->Load2D(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::TEXTURES, "3D Button.png").c_str(), GL_REPEAT);
    Globals::AddTexture("3DButton", texture);

    texture = new Texture2D();
    texture->Load2D(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::TEXTURES, "Arrow Button.png").c_str(), GL_REPEAT);
    Globals::AddTexture("ArrowButton", texture);

    texture = new Texture2D();
    texture->Load2D(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::TEXTURES, "Menu Button.png").c_str(), GL_REPEAT);
    Globals::AddTexture("MenuButton", texture);
}

void ed::Editor::CreateObjects()
{
    Mesh* mesh;

    mesh = new Mesh("box");
    mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "box.obj");
    Globals::AddMesh(mesh);

    mesh = shapes::CreateQuad("quad");
    Globals::AddMesh(mesh);

    /*mesh = new Mesh("2DButton");
    mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "buttons", "2DButton"), "2DButton.fbx");
    meshes[mesh->GetMeshID()] = mesh;

    mesh = new Mesh("3DButton");
    mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "buttons", "3DButton"), "3DButton.fbx");
    meshes[mesh->GetMeshID()] = mesh;*/
}

void ed::Editor::CreateButtons()
{   
    {
        TwoDButton* button = new TwoDButton("quad", "editorShader", "2DButton", vec2(35.0f, 695.0f), vec2(0.0f), vec2(50.0f));
        buttons.push_back(button);
    }
    
    {
        ThreeDButton* button = new ThreeDButton("quad", "editorShader", "3DButton", vec2(95.0f, 695.0f), vec2(0.0f), vec2(50.0f));
        buttons.push_back(button);
    }
}

void ed::Editor::CreateShaders()
{
    Shader* shader = new Shader("editorShader");
    shader->AddShader(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::SHADERS, "Editor_Shader", "Editor.Shader.VS.glsl"), GL_VERTEX_SHADER);
    shader->AddShader(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::SHADERS, "Editor_Shader", "Editor.Shader.FS.glsl"), GL_FRAGMENT_SHADER);
    shader->CreateAndLink();
    Globals::AddShader(shader);
}

void ed::Editor::RenderMainScene()
{
    glViewport(0, 0, resolution.x, resolution.y);

    {
        glm::mat4 modelMatrix = glm::mat4(1);
        RenderSimpleMesh(Globals::GetMeshes("quad"), Globals::GetShaders("editorShader"), modelMatrix, mainCamera, Globals::GetTextures("2DButton"));
    }

    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(2, 0.5f, 0));
        modelMatrix = glm::rotate(modelMatrix, RADIANS(60.0f), glm::vec3(1, 0, 0));
        modelMatrix = glm::scale(modelMatrix, glm::vec3(0.75f));
        RenderSimpleMesh(Globals::GetMeshes("box"), Globals::GetShaders("editorShader"), modelMatrix, mainCamera, Globals::GetTextures("cyan"));
    }

    /*{
        glm::mat4 modelMatrix = glm::mat4(1);
        RenderMesh(meshes["2DButton"], shaders["Simple"], modelMatrix, mainCamera);
    }*/

    DrawCoordinateSystem(mainCamera->GetViewMatrix(), mainCamera->projectionMatrix);
}

void ed::Editor::RenderButtonMenu()
{
    glClear(GL_DEPTH_BUFFER_BIT);
    glViewport(staticViewportArea.x, staticViewportArea.y, staticViewportArea.width, staticViewportArea.height);

    // Render buttons.
    for (int i {}; i < buttons.size(); ++i) {
        // RenderMesh(meshes[button->GetTextID()], shaders["Simple"], button->getTransformationMatrix(), staticCamera);
        if (i != hovButIndex) {
            buttons[i]->RenderButton();
        }
        else {
            buttons[i]->RenderButton(Globals::GetTextures("white"));
        }
    }
}

void Editor::OnInputUpdate(float deltaTime, int mods)
{
    if (window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
    {
        float cameraSpeed = 2.0f;

        if (window->KeyHold(GLFW_KEY_W)) {
            mainCamera->TranslateForward(cameraSpeed * deltaTime);

        }

        if (window->KeyHold(GLFW_KEY_A)) {
            mainCamera->TranslateRight(-cameraSpeed * deltaTime);
        }

        if (window->KeyHold(GLFW_KEY_S)) {
            mainCamera->TranslateForward(-cameraSpeed * deltaTime);
        }

        if (window->KeyHold(GLFW_KEY_D)) {
            mainCamera->TranslateRight(cameraSpeed * deltaTime);
        }

        if (window->KeyHold(GLFW_KEY_Q)) {
            mainCamera->TranslateUpward(-cameraSpeed * deltaTime);
        }

        if (window->KeyHold(GLFW_KEY_E)) {
            mainCamera->TranslateUpward(cameraSpeed * deltaTime);
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
            mainCamera->RotateFirstPerson_OY(angleX);
            mainCamera->RotateFirstPerson_OX(angleY);
        }
    }

    // Check if the mouse is hovering over a button.
    bool hovered{ false };
    for (int i{}; i < buttons.size(); ++i) {
        if (buttons[i]->isHovered(mouseX, resolution.y - mouseY)) {
            hovButIndex = i;
            hovered = true;
        }
    }

    if (!hovered)
        hovButIndex = -1;
}

void Editor::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    if (hovButIndex != -1) {
        presButIndex = hovButIndex;
        buttons[presButIndex]->ButtonPressed();
    }
}

void Editor::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
}

void Editor::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}

void Editor::OnWindowResize(int width, int height)
{
    float newX {width / (float)resolution.x};
    float newY {height / (float)resolution.y};
    resolution.x = width;
    resolution.y = height;
    staticViewportArea.width = width;
    staticViewportArea.height = height;

    for (const auto button : buttons) {
        button->Resize(newX, newY);
    }
}
