#include "vertex_object.hpp"

void gfx::unbind_vbo() {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void gfx::unbind_vao() {
    glBindVertexArray(0);
}

void gfx::unbind_ebo() {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

gfx::vao_t::vao_t() {
    glGenVertexArrays(1, &this->handle);
}

GLuint gfx::vao_t::get_handle() const {
    return this->handle;
}

void gfx::vao_t::bind() {
    glBindVertexArray(this->handle);
}

void gfx::vao_t::link_attrib(vbo_t &vbo, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void *offset)
{
    vbo.bind();
	glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);
	glEnableVertexAttribArray(layout);
    gfx::unbind_vbo();
}

void gfx::vao_t::kill() {
    glDeleteVertexArrays(1, &this->handle);
}

gfx::vbo_t::vbo_t() {
    glGenBuffers(1, &this->handle);
}

GLuint gfx::vbo_t::get_handle() const {
    return this->handle;
}

void gfx::vbo_t::bind() {
    glBindBuffer(GL_ARRAY_BUFFER, this->handle);
}

void gfx::vbo_t::buffer_data(std::vector<f32>& v) {
    glBufferData(GL_ARRAY_BUFFER, v.size() * sizeof(f32),
        v.data(), GL_STATIC_DRAW);
}

void gfx::vbo_t::kill() {
    glDeleteBuffers(1, &this->handle);
}


gfx::ebo_t::ebo_t() {
    glGenBuffers(1, &this->handle);
}

void gfx::ebo_t::bind() {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->handle);
}

void gfx::ebo_t::buffer_data(std::vector<GLuint>& v) {
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, v.size() * sizeof(GLuint),
        v.data(), GL_STATIC_DRAW);
}

void gfx::ebo_t::kill() {
    glDeleteBuffers(1, &this->handle);
}
