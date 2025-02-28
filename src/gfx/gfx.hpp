#pragma once

#include <string>
#include <cassert>

#include "glad/glad.h"

#include "GLFW/glfw3.h"
#include "utils/utils.hpp"
#include "global/global.hpp"
#include "glm.hpp"

using u2 = glm::u32vec2;
using f2 = glm::f64vec2;

namespace gfx {
    class window_t {
            using handle_t  = GLFWwindow*;
            using monitor_t = GLFWmonitor*;
            using vidmode_t = GLFWvidmode*;

        private:
            handle_t handle = nullptr;
            monitor_t monitor = nullptr, *monitors = nullptr;
            vidmode_t mode = nullptr;
            u2 size;

        public:
            window_t(std::string title, u2 size);

            bool is_open() const;
            void swap_buffers();

            bool is_pressed(int key) const;

            void set_cursor_pos(f2 pos);
            f2 get_cursor_pos() const;

            void cursor_show();
            void cursor_hide();

            void kill();
    };
}