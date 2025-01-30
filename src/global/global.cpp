#include "global/global.hpp"
#include "global.hpp"

static global::settings_t settings = {
        {1280, 720},                    // resolution
        0,                              // monitor_index
        240,                            // refresh_rate
        240,                            // max_fps
        true,                           // vsync_enabled
        global::window_mode_t::WINDOWED // window_mode
};

global::settings_t global::get_settings() {
    return settings;
}

void global::set_settings(const global::settings_t& update) {
    settings = update;
}

void global::init_settings() {
    if(!settings.vsync_enabled) {
        /* vsync is enabled by default */
        glfwSwapInterval(0);
    }
}