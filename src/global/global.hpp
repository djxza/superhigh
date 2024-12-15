#pragma once

#include <GLFW/glfw3.h>

#include "gfx/glm.hpp"
#include "utils/utils.hpp"

namespace global {
    enum class window_mode_t {
        FULLSCREEN,
        WINDOWED_FULLSCREEN,
        WINDOWED
    };

    struct settings_t {
        glm::u16vec2 window_size;
        int monitor_index;
        int refresh_rate;
        int max_fps;
        bool vsync_enabled;
        window_mode_t window_mode;
    };

    void init_settings();

    /* TODO: add function that load this from a file */
    inline settings_t settings = {
        {1280, 720},            // resolution
        0,                      // monitor_index
        240,                    // refresh_rate
        240,                    // max_fps
        true,                   // vsync_enabled
        window_mode_t::WINDOWED // window_mode
    };
}