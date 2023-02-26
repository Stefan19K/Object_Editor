#include <vector>
#include <iostream>

#include "GeometryShapes.h"
#include "Macros.h"
#include "core/engine.h"
#include "utils/gl_utils.h"

Mesh* shapes::CreateSquare(
    const std::string& name,
    glm::vec3 color)
{
    std::vector<VertexFormat> vertices
    {
        VertexFormat(glm::vec3(-0.5f, -0.5f, 0), color),
        VertexFormat(glm::vec3(0.5f, -0.5f, 0), color),
        VertexFormat(glm::vec3(-0.5f, 0.5f, 0), color),
        VertexFormat(glm::vec3(0.5f, 0.5f, 0), color)
    };

    Mesh* square = new Mesh(name);
    std::vector<unsigned int> indices =
    {
        0, 1, 2,    // indices for first triangle
        1, 3, 2,    // indices for second triangle
    };

    square->InitFromData(vertices, indices);
    return square;
}

Mesh* shapes::CreateQuad(
    const std::string& name)
{
    std::vector<glm::vec3> vertices
    {
        glm::vec3(0.5f,   0.5f, 0.0f),    // top right
        glm::vec3(0.5f,  -0.5f, 0.0f),    // bottom right
        glm::vec3(-0.5f, -0.5f, 0.0f),    // bottom left
        glm::vec3(-0.5f,  0.5f, 0.0f),    // top left
    };

    std::vector<glm::vec3> normals
    {
        glm::vec3(0, 0, 1),
        glm::vec3(0, 0, 1),
        glm::vec3(0, 0, 1),
        glm::vec3(0, 0, 1)
    };

    std::vector<glm::vec2> textureCoords
    {
        glm::vec2(1.0f, 0.0f),
        glm::vec2(1.0f, 1.0f),
        glm::vec2(0.0f, 1.0f),
        glm::vec2(0.0f, 0.0f)
    };

    std::vector<unsigned int> indices =
    {
        0, 1, 3,
        1, 2, 3
    };

    Mesh* quad = new Mesh(name);
    quad->InitFromData(vertices, normals, textureCoords, indices);
    return quad;
}

Mesh* shapes::CreateTriangle(
    const std::string& name,
    glm::vec3 color)
{
    std::vector<VertexFormat> vertices
    {
        VertexFormat(glm::vec3(-0.5f, -0.5f, 0), color),
        VertexFormat(glm::vec3(0.5f, -0.5f, 0), color),
        VertexFormat(glm::vec3(-0.5f, 0.5f, 0), color)
    };

    Mesh* triangle = new Mesh(name);
    std::vector<unsigned int> indices =
    {
        0, 1, 2,    // indices for first triangle
    };

    triangle->InitFromData(vertices, indices);
    return triangle;
}

Mesh* shapes::CreateEllipse(
    const std::string& name,
    glm::vec3 leftBottomCorner,
    float width,
    float height,
    int triangles,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 corner = leftBottomCorner;
    std::vector<VertexFormat> vertices;
    float measure{ 0 };
    float step{ (float)FULL_CIRCLE / triangles };

    vertices.push_back(VertexFormat(corner, color));
    for (int i{ }; i < triangles; ++i) {
        float x = corner.x + width * cos(measure * PI / 180);
        float y = corner.y + height * sin(measure * PI / 180);

        vertices.push_back(VertexFormat(corner + glm::vec3(x, y, 0), color));
        measure += step;
    }

    Mesh* ellipse = new Mesh(name);
    std::vector<unsigned int> indices;
    for (int i{ }; i <= triangles; ++i) {
        indices.push_back(i);
    }

    if (!fill) {
        indices.erase(indices.begin());
        ellipse->SetDrawMode(GL_LINE_LOOP);
    }
    else {
        // Draw 2 triangles. Add the remaining 2 indices
        indices.push_back(1);
        ellipse->SetDrawMode(GL_TRIANGLE_FAN);
    }

    ellipse->InitFromData(vertices, indices);
    return ellipse;
}

Mesh* shapes::CreateBox(
    const std::string& name,
    glm::vec3 color)
{
    std::vector<VertexFormat> vertices
    {
        VertexFormat(glm::vec3(-0.5f, -0.5f, -0.5f), color),
        VertexFormat(glm::vec3(0.5f, -0.5f, -0.5f), color),
        VertexFormat(glm::vec3(-0.5f, 0.5f, -0.5f), color),
        VertexFormat(glm::vec3(0.5f, 0.5f, -0.5f), color),
        VertexFormat(glm::vec3(-0.5f, -0.5f, 0.5f), color),
        VertexFormat(glm::vec3(0.5f, -0.5f, 0.5f), color),
        VertexFormat(glm::vec3(-0.5f, 0.5f, 0.5f), color),
        VertexFormat(glm::vec3(0.5f, 0.5f, 0.5f), color)
    };

    Mesh* box = new Mesh(name);
    std::vector<unsigned int> indices =
    {
        0, 1, 2,    // indices for first triangle
        1, 3, 2,    // indices for second triangle
        2, 3, 7,
        2, 7, 6,
        1, 7, 3,
        1, 5, 7,
        6, 7, 4,
        7, 5, 4,
        0, 4, 1,
        1, 4, 5,
        2, 6, 4,
        0, 2, 4
    };

    box->InitFromData(vertices, indices);
    return box;
}

Mesh* shapes::CreatePrism(
    const std::string& name,
    glm::vec3 color)
{
    std::vector<VertexFormat> vertices
    {
        VertexFormat(glm::vec3(0.5f, -0.5f, -0.5f), color),
        VertexFormat(glm::vec3(0.5f, 0.5f, -0.5f), color),
        VertexFormat(glm::vec3(-0.5f, 0.5f, -0.5f), color),
        VertexFormat(glm::vec3(0.5f, -0.5f, 0.5f), color),
        VertexFormat(glm::vec3(0.5f, 0.5f, 0.5f), color),
        VertexFormat(glm::vec3(-0.5f, 0.5f, 0.5f), color)
    };

    Mesh* prism = new Mesh(name);
    std::vector<unsigned int> indices =
    {
        0, 1, 2,    // indices for first triangle
        3, 4, 5,    // indices for second triangle
        3, 0, 4,
        4, 0, 1,
        4, 1, 5,
        5, 1, 2,
        5, 2, 3,
        3, 2, 0
    };

    prism->InitFromData(vertices, indices);
    return prism;
}

Mesh* shapes::CreateCyllinder(
    const std::string& name,
    glm::vec3 leftBottomCorner,
    float width, float length, float height,
    int triangles,
    glm::vec3 color)
{
    glm::vec3 corner = leftBottomCorner;
    std::vector<VertexFormat> vertices;
    float measure{ 0 };
    float step{ (float)FULL_CIRCLE / triangles };

    vertices.push_back(VertexFormat(corner, color));
    vertices.push_back(VertexFormat(corner + glm::vec3(0, 0, height), color));
    for (int i{ }; i < triangles; ++i) {
        float x = corner.x + width * cos(measure * PI / 180);
        float y = corner.y + length * sin(measure * PI / 180);

        vertices.push_back(VertexFormat(corner + glm::vec3(x, y, 0), color));
        vertices.push_back(VertexFormat(corner + glm::vec3(x, y, height), color));
        measure += step;
    }

    Mesh* cyllinder = new Mesh(name);
    std::vector<unsigned int> indices;
    int a = 2;
    int b = 4;
    for (int i{ }; i < triangles; ++i) {
        if (i + 1 == triangles) {
            indices.push_back(0);
            indices.push_back(b);
            indices.push_back(2);

            indices.push_back(1);
            indices.push_back(b + 1);
            indices.push_back(3);

            indices.push_back(a);
            indices.push_back(a + 1);
            indices.push_back(2);

            indices.push_back(3);
            indices.push_back(2);
            indices.push_back(a + 1);
        }
        else {
            indices.push_back(0);
            indices.push_back(a);
            indices.push_back(b);

            indices.push_back(1);
            indices.push_back(a + 1);
            indices.push_back(b + 1);

            indices.push_back(a);
            indices.push_back(a + 1);
            indices.push_back(a + 2);

            indices.push_back(a + 3);
            indices.push_back(a + 2);
            indices.push_back(a + 1);
        }

        a += 2;
        b += 2;
    }

    cyllinder->InitFromData(vertices, indices);
    return cyllinder;
}
