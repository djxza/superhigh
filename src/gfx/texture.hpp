#pragma once

#include "glad/glad.h"
#include "stb/image.h"
#include "gfx/shader.hpp"

namespace gfx {
    struct texture_params_t {
        int width;
        int height;
        int color_channels;
    };

    class texture_t {

        using tp = GLenum;

    private:
        GLuint handle;
        tp type;

    public:
        texture_t(str path, tp type,
            tp slot, tp format, tp pixel_tp);

        void unit(program_t &program, str uniform, GLuint unit);
        
        void bind();
        void unbind();

        void kill();
    };
};