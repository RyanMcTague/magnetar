#pragma once
#include "magnetar/core/base.h"
#include "magnetar/renderer/backend/opengl/glad.h"
#include "magnetar/renderer/enums.h"

#define MT_GL_CHECK(x)                                                    \
    do                                                                    \
    {                                                                     \
        x;                                                                \
        magnetar::GLHelpers::gl_check_error_(#x, __FILE__, __LINE__); \
    } while (false)

namespace magnetar
{
    class GLHelpers
    {
    public:
        static GLenum gl_check_error_(const char *func, const char *file, int line);
        static RendererDataType convert_renderer_type(GLenum gl_type);
        static GLenum texture_format_type(TextureFormat format);
        static GLenum texture_filter_type(TextureFilter filter);
        static GLenum texture_wrap_type(TextureWrap wrap);
        static GLenum draw_mode_type(DrawMode mode);
    private:
        GLHelpers() = default;
    };
}