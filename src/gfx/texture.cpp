#include "texture.hpp"

gfx::texture_t::texture_t(str path, tp type,
    tp slot, tp format, tp pixel_tp)
{
    this->type = type;

    texture_params_t params;

    stbi_set_flip_vertically_on_load(true);

    u8* bytes = stbi_load(
        path.c_str(),
        &params.width,
        &params.height,
        &params.color_channels,
        0);

	glGenTextures(1, &this->handle);
	glActiveTexture(slot);
	glBindTexture(this->type, this->handle);

	glTexParameteri(this->type, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
	glTexParameteri(this->type, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexParameteri(this->type, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(this->type, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// Extra lines in case you choose to use GL_CLAMP_TO_BORDER
	// float flatColor[] = {1.0f, 1.0f, 1.0f, 1.0f};
	// glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, flatColor);

	glTexImage2D(this->type, 0, GL_RGBA,
                 params.width, 
                 params.height,
                 0, format, 
                 pixel_tp, bytes);

	glGenerateMipmap(this->type);

	stbi_image_free(bytes);

	glBindTexture(this->type, 0);
}

void gfx::texture_t::unit(program_t &program, str uniform, GLuint unit)
{
	GLuint texUni = glGetUniformLocation(program.get_handle(), uniform.c_str());
	// Shader needs to be activated before changing the value of a uniform
	glUseProgram(program.get_handle());
	// Sets the value of the uniform
	glUniform1i(texUni, unit);
}

void gfx::texture_t::bind()
{
    glBindTexture(this->type, this->handle);
}

void gfx::texture_t::unbind()
{
    glBindTexture(this->type, this->handle);
}

void gfx::texture_t::kill()
{
    glDeleteTextures(1, &this->handle);
}
