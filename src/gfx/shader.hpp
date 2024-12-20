#pragma once

#include <fstream>
#include "gfx.hpp"

namespace gfx {

    enum class shader_enum : bool {
        VERTEX = 0,
        FRAGMENT = 1
    };

    template<shader_enum type>
    class shader_t {
    private:
        u32 handle;
        const char* shader_contents;

    public:
        shader_t(utils::str shader_path) {
            this->handle = glCreateShader(
                static_cast<bool>(type) ?
                    GL_FRAGMENT_SHADER : GL_VERTEX_SHADER);

            str read = utils::read_file_newline(shader_path);
            this->shader_contents = read.c_str();
                        //std::cout << shader_contents << std::endl;

            glShaderSource(this->handle, 1, &this->shader_contents, NULL);
            glCompileShader(this->handle);

                        i32 success;
            char infoLog[512];
            glGetShaderiv(this->handle, GL_COMPILE_STATUS, &success);

            if (!success) {
                glGetProgramInfoLog(this->handle, 512, NULL, infoLog);
                std::cerr << "ERROR: Program linking failed\n" << infoLog << std::endl;
            }
        }

        u32 get_handle() const {
            return this->handle;
        }
    };

    class program_t {
        using vertex_shader_t = shader_t<shader_enum::VERTEX>;
        using fragment_shader_t = shader_t<shader_enum::FRAGMENT>;

    private:
        u32 handle;

    public:
        program_t(vertex_shader_t& vertex, fragment_shader_t& fragment) {
            this->handle = glCreateProgram();
            glAttachShader(this->handle, vertex.get_handle());
            glAttachShader(this->handle, fragment.get_handle());
            glLinkProgram(this->handle);

            // Delete the now useless shader objects
            glDeleteShader(vertex.get_handle());
            glDeleteShader(fragment.get_handle());

            i32 success;
            char infoLog[512];
            glGetProgramiv(this->handle, GL_LINK_STATUS, &success);

            if (!success) {
                glGetProgramInfoLog(this->handle, 512, NULL, infoLog);
                std::cerr << "PROGRAM ERROR: Program linking failed\n" << infoLog << std::endl;
            }
    }

        u32 get_handle() const {
            return this->handle;
        }
    };
}
