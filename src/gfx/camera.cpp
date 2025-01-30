#include "camera.hpp"

gfx::camera_t::camera_t(u32 width, u32 height, glm::vec3 pos)
{
    this->width = width;
    this->height = height;
    this->pos = pos;
}

void gfx::camera_t::matrix(
    f32 fov,
    f32 near,
    f32 far,
    program_t &program,
    str uniform)
{
    glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 proj = glm::mat4(1.0f);

	view = glm::lookAt(
        this->pos,
        this->pos + this->orientation,
        this->up);

	proj = glm::perspective(
        glm::radians(fov), (f32)(width / height),
        near, far);

	// Exports the camera matrix to the Vertex Shader
	glUniformMatrix4fv(
        glGetUniformLocation(
            program.get_handle(),
            uniform.c_str()),
        1, GL_FALSE, glm::value_ptr(proj * view));
}

#define IF_PRESSED(inp, consequence) \
    if(win.is_pressed(inp)) {        \
        consequence;                 \
    }

#define IF_PRESSED_GO(inp, x) \
    IF_PRESSED(global::get_settings().controls.inp, this->pos += this->speed / 10000.0f * x )

void gfx::camera_t::handle_inputs(gfx::window_t &win) {
    this->speed = 250.0f;
    IF_PRESSED_GO(forward, this->orientation);
    IF_PRESSED_GO(back, -this->orientation);
    IF_PRESSED_GO(left, -glm::normalize(glm::cross(this->orientation, up)));
    IF_PRESSED_GO(right, glm::normalize(glm::cross(this->orientation, up)));

    win.cursor_hide();

    // win.set_cursor_pos(f2({width / 2, height / 2}));

    f2 mouse = win.get_cursor_pos();

    f2 rot;
    rot.x = sensitivity * (f64)(mouse.y - (height / 2)) / height;
    rot.y = sensitivity * (f64)(mouse.x - (width / 2)) / width;

    glm::f64vec3 new_orientation = glm::rotate(this->orientation, glm::radians(-rot.x),glm::normalize(glm::cross(this->orientation, up)));
    
    if(std::abs(glm::angle(new_orientation, this->up)) - glm::radians(90.0f) <= glm::radians(85.0f)) {
        this->orientation = new_orientation;
    }

    this->orientation = glm::rotate(this->orientation, glm::radians(-rot.y), this->up);

    win.set_cursor_pos(f2({width / 2, height / 2}));

    // win.cursor_show();
}
