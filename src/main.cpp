#include <iostream>

#include "gfx/gfx.hpp"
#include "gfx/shader.hpp"
#include "gfx/vertex_object.hpp"
#include "gfx/texture.hpp"

int main(int ac, const char* argv[]) {
    gfx::window_t window("Project", { 800, 800 });
    
    	// Create Vertex Shader Object and get its reference
	gfx::shader_t<gfx::shader_enum::VERTEX>   vertex_shader(utils::str("./res/shader/vert.glsl"));
    gfx::shader_t<gfx::shader_enum::FRAGMENT> fragment_shader(utils::str("./res/shader/frag.glsl"));
    gfx::program_t program(vertex_shader, fragment_shader);

	// Vertices coordinates
	// Vertices coordinates
	std::vector<f32> vertices = {
		-0.5f, -0.5f, 0.0f,     1.0f, 0.0f, 0.0f,	0.0f, 0.0f, // Lower left corner
		-0.5f,  0.5f, 0.0f,     0.0f, 1.0f, 0.0f,	0.0f, 1.0f, // Upper left corner
		0.5f,  0.5f, 0.0f,     0.0f, 0.0f, 1.0f,	1.0f, 1.0f, // Upper right corner
		0.5f, -0.5f, 0.0f,     1.0f, 1.0f, 1.0f,	1.0f, 0.0f  // Lower right corner
	};

	std::vector<GLuint> indices = {
		0, 2, 1, // Upper triangle
		0, 3, 2 // Lower triangle
	};

	gfx::vao_t vao;
	gfx::vbo_t vbo;
	gfx::ebo_t ebo;

	// Make the VAO the current Vertex Array Object by binding it
	vao.bind();

	// Bind the VBO specifying it's a GL_ARRAY_BUFFER
	vbo.bind();
	vbo.buffer_data(vertices);

	ebo.bind();
	ebo.buffer_data(indices);

	vao.link_attrib(vbo, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	vao.link_attrib(vbo, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	vao.link_attrib(vbo, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));

	gfx::unbind_vbo();
	gfx::unbind_vao();
	gfx::unbind_ebo();

	auto uniid = glGetUniformLocation(program.get_handle(), "scale");

	gfx::texture_t pop_cat("res/gfx/2d/pop_cat.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	pop_cat.unit(program, "tex0", 0);

    while(window.is_open())
	{
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		/*TODO: dodaj ovo u program.use*/
		glUseProgram(program.get_handle());
		glUniform1f(uniid, 0.5f);

		pop_cat.bind();

		vao.bind();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		window.swap_buffers();
		glfwPollEvents();
	}

    GLenum err;
    while ((err = glGetError()) != GL_NO_ERROR) {
        std::cerr << "OpenGL error: " << err << std::endl;
    }

	// Delete all the objects we've created
	vao.kill();
	vbo.kill();
	ebo.kill();

	pop_cat.kill();

	glDeleteProgram(program.get_handle());
	// Delete window before ending the program

    window.kill();
}
