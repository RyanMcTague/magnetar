#pragma once
#include "magnetar/core/base.h"
#include "magnetar/platforms/opengl/glad.h"
#include "magnetar/renderer/enums.h"

#define MT_GL_CHECK(x)                                       \
    do                                                       \
    {                                                        \
        x;                                                   \
        quasar::gl::gl_check_error_(#x, __FILE__, __LINE__); \
    } while (false)

namespace magnetar
{
    class OpenGLHelpers
    {
    public:
        static RendererDataType convert_renderer_type(GLenum gl_type);

        static GLenum gl_check_error_(const char *func, const char *file, int line);

    private:
        OpenGLHelpers() = default;
    };
}