#include "Button.h"

void Button::ButtonPressed() const
{
}

void Button::Resize(float newX, float newY)
{
	translation = vec3(translation.x * newX, translation.y * newY, 0.0f);
	scalation = vec3(scalation.x * newX, scalation.y * newY, 1.0f);
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

void Button::RenderButton(Texture2D* texture2)
{
    RenderSimpleMesh(this->meshID, this->shader, this->matrix, this->cam, this->text1, texture2);
}

Mesh* Button::GetMeshID()
{
	return meshID;
}

Texture2D* Button::GetTextID()
{
	return text1;
}

void RenderSimpleMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, implemented::Camera* cam, Texture2D* texture1, Texture2D* texture2)
{
    if (!mesh || !shader || !shader->GetProgramID())
        return;

    glUseProgram(shader->program);

    GLint loc_model_matrix = glGetUniformLocation(shader->program, "Model");
    glUniformMatrix4fv(loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

    glm::mat4 viewMatrix = cam->GetViewMatrix();
    int loc_view_matrix = glGetUniformLocation(shader->program, "View");
    glUniformMatrix4fv(loc_view_matrix, 1, GL_FALSE, glm::value_ptr(viewMatrix));

    int loc_projection_matrix = glGetUniformLocation(shader->program, "Projection");
    glUniformMatrix4fv(loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(cam->projectionMatrix));

    int multipleTextures = 0;
    if (texture2 != NULL) {
        multipleTextures = 1;
    }

    loc_projection_matrix = glGetUniformLocation(shader->program, "multipleTextures");
    glUniform1i(loc_projection_matrix, multipleTextures);

    if (texture1)
    {
        glActiveTexture(GL_TEXTURE0);

        glBindTexture(GL_TEXTURE_2D, texture1->GetTextureID());

        glUniform1i(glGetUniformLocation(shader->program, "texture_1"), 0);

    }

    if (texture2)
    {
        glActiveTexture(GL_TEXTURE1);

        glBindTexture(GL_TEXTURE_2D, texture2->GetTextureID());

        glUniform1i(glGetUniformLocation(shader->program, "texture_2"), 1);

    }

    glBindVertexArray(mesh->GetBuffers()->m_VAO);
    glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_INT, 0);
}
