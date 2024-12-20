#pragma once

#include "gfx.hpp"

namespace gfx {
    void unbind_vbo();
    void unbind_vao();
    void unbind_ebo();

    class vbo_t {
    private:
        GLuint handle;

    public:
        vbo_t();

        GLuint get_handle() const;

        void bind();
        void buffer_data(std::vector<f32>& v);

        void kill();
    };

    class vao_t {
    private:
        GLuint handle;

    public:
        vao_t();

        GLuint get_handle() const;

        void bind();
        void link_attrib(vbo_t& vbo, GLuint layout,
            GLuint numComponents, GLenum type,
            GLsizeiptr stride, void* offset);

        void kill();
    };
    

    class ebo_t {
    private:
        GLuint handle;

    public:
        ebo_t();

        GLuint get_handle() const;

        void bind();

        void buffer_data(std::vector<GLuint>& v);

        void kill();
    };
}