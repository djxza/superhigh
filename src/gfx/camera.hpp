#pragma once

#include "glm.hpp"
#include "shader.hpp"
#include "utils/utils.hpp"

namespace gfx {
    class camera_t {
    private:
        glm::f64vec3 pos;
        glm::f64vec3 orientation = glm::vec3(0.0f, 0.0f, -1.0f);
        glm::f64vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);

        u32 width;
        u32 height;

        f64 speed;
        f64 sensitivity = 100.0f;

    public:
        camera_t(
            u32 width,
            u32 height,
            glm::vec3 pos);

        void matrix(
            f32 fov,
            f32 near,
            f32 far,
            program_t& program,
            str uniform);

        void handle_inputs(
            gfx::window_t& window);
    };
};