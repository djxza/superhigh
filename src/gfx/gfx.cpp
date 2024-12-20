#include "gfx.hpp"

using namespace global;

gfx::window_t::window_t(std::string title, u2 _size) {
    assert(glfwInit() && "GLFW library not initialized!");

    this->size = _size;

    glfwSetErrorCallback([](int error, const char *description)
                         { 
        utils::_throw(
                        "Error",
                        std::string(
                            "glfw error " + error +
                            std::string("; glfw says ") + description)); });
    
    init_settings();

    // Get monitor info
    int num_monitors;
    this->monitors = glfwGetMonitors(&num_monitors);
    if (settings.monitor_index >= num_monitors) {
        utils::_throw("Failure", "Monitor index out of range");
    } else {
        this->monitor = monitors[settings.monitor_index];
    }

    /* some sketchy casting here potential break? */
    this->mode = const_cast<vidmode_t>(glfwGetVideoMode(monitor));
    glm::ivec2 monitor_pos;
    glfwGetMonitorPos(monitor, &monitor_pos.x, &monitor_pos.y);

    glfwDefaultWindowHints(); // Call this first to reset hints

    /* set to max refresh rate. */
    if(settings.refresh_rate == -1) {
        settings.refresh_rate = this->mode->refreshRate;
    }

    glfwWindowHint(GLFW_REFRESH_RATE, settings.refresh_rate);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);

    // CHANGE IF NEEDED
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /*TODO: dodaj fullscreen koj se cita iz json setting fila. */
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);


    this->handle = glfwCreateWindow(
        this->size.x,
        this->size.y,
        title.c_str(),
        nullptr,
        nullptr);

    assert(this->handle && "Window failed to initialize!");

    glfwMakeContextCurrent(this->handle);

	gladLoadGL();

	glViewport(
        0, 0, 
        this->size.x,
        this->size.y);
}

void gfx::window_t::swap_buffers()
{
    glfwSwapBuffers(this->handle);
}

bool gfx::window_t::is_open() const {
    return !glfwWindowShouldClose(this->handle);
}

void gfx::window_t::kill() {
    glfwDestroyWindow(this->handle);
    glfwTerminate();
}