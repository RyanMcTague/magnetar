#pragma once
#include <glm/glm.hpp>
#include "magnetar/core/base.h"

namespace magnetar
{
    class MAGNETAR_API Camera
    {
    public:
        virtual ~Camera() = default;
        virtual const glm::mat4 &matrix() const = 0;
    };

    class MAGNETAR_API Camera2D : public Camera
    {
    public:
        Camera2D(float left, float right, float top, float bottom, float near, float far);

        const glm::mat4 &matrix() const override { return m_matrix; }

        float left() const { return m_left; }
        float right() const { return m_right; }
        float top() const { return m_top; }
        float bottom() const { return m_bottom; }
        float near() const { return m_near; }
        float far() const { return m_far; }

        void set_y_plane(float bottom, float top);
        void set_x_plane(float left, float right);
        void set_z_plane(float near, float far);

        void set_position(const glm::vec2 &amount);

    private:
        glm::mat4 m_matrix;
        float m_left;
        float m_right;
        float m_top;
        float m_bottom;
        float m_near;
        float m_far;

        void calculate();
    };

    class MAGNETAR_API Camera3D : public Camera
    {
    public:
        Camera3D(float fov, float aspect_ratio, float near, float far, const glm::mat4 &model);

        const glm::mat4 &matrix() const override { return m_matrix; }

        float field_of_view() const { return m_field_of_view; }
        float aspect_ratio() const { return m_apsect_ratio; }
        float near() const { return m_near; }
        float far() const { return m_far; }
        const glm::mat4 &model() { return m_model; }

        void set_field_of_view(float field_of_view);
        void set_aspect_ratio(float aspect_ratio);
        void set_near(float near);
        void set_far(float far);
        void set_model(const glm::mat4 &model);

    private:
        void calculate();
        glm::mat4 m_model;
        glm::mat4 m_matrix;
        float m_field_of_view;
        float m_apsect_ratio;
        float m_near;
        float m_far;
    };
}