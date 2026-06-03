#include <glm/gtc/matrix_transform.hpp>
#include "magnetar/renderer/camera.h"

magnetar::Camera2D::Camera2D(float left, float right, float top, float bottom, float near, float far)
    : m_matrix(glm::mat4(1.0f)), m_left(left), m_right(right), m_top(top), m_bottom(bottom), m_near(near), m_far(far)
{
    calculate();
}

void magnetar::Camera2D::calculate()
{
    m_matrix = glm::ortho(m_left, m_right, m_bottom, m_top, m_near, m_far);
}

void magnetar::Camera2D::set_y_plane(float bottom, float top)
{
    m_bottom = bottom;
    m_top = top;
    calculate();
}
void magnetar::Camera2D::set_x_plane(float left, float right)
{
    m_left = left;
    m_right = right;
    calculate();
}
void magnetar::Camera2D::set_z_plane(float near, float far)
{
    m_near = near;
    m_far = far;
    calculate();
}

void magnetar::Camera2D::move(const glm::vec2 &amount)
{
    m_left += amount.x;
    m_right += amount.x;

    m_top += amount.y;
    m_bottom += amount.y;
    calculate();
}

magnetar::Camera3D::Camera3D(float fov, float aspect_ratio, float near, float far, const glm::mat4 &model)
    : m_model(model), m_matrix(glm::mat4(1.0f)), m_field_of_view(fov), m_apsect_ratio(aspect_ratio), m_near(near), m_far(far)

{
    calculate();
}

void magnetar::Camera3D::calculate()
{
    auto projection = glm::perspective(m_field_of_view, m_apsect_ratio, m_near, m_far);
    auto view = glm::inverse(m_model);
    m_matrix = projection * view;
}

void magnetar::Camera3D::set_field_of_view(float field_of_view)
{
    m_field_of_view = field_of_view;
    calculate();
}

void magnetar::Camera3D::set_aspect_ratio(float aspect_ratio)
{
    m_apsect_ratio = aspect_ratio;
    calculate();
}

void magnetar::Camera3D::set_near(float near)
{
    m_near = near;
    calculate();
}

void magnetar::Camera3D::set_far(float far)
{
    m_far = far;
    calculate();
}

void magnetar::Camera3D::set_model(const glm::mat4 &model)
{
    m_model = model;
    calculate();
}
