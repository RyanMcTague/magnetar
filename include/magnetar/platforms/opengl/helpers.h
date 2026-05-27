#pragma once
#include "magnetar/core/base.h"
#include "magnetar/platforms/opengl/glad.h"
#include "magnetar/renderer/enums.h"

namespace magnetar
{
    class OpenGLHelpers
    {
    public:
        static RendererDataType convert_renderer_type(GLenum gl_type);
    private:
        OpenGLHelpers() = default;
    };
}