#include <iostream>
#include "GLFW/glfw3.h"

#include "gfx/gfx.hpp"

int main(int ac, const char* argv[]) {
    gfx::window_t window("Project", { 1280, 720 });

    while(window.is_open()) {
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0.0f, 1.0f, 1.0f, 1.0f);

        window.swap_buffers();
        glfwPollEvents();
    }

    window.kill();
}
