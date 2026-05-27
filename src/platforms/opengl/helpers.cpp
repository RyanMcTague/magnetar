#include "magnetar/platforms/opengl/helpers.h"

magnetar::RendererDataType magnetar::OpenGLHelpers::convert_renderer_type(GLenum gl_type)
{
    RendererDataType type;
    switch (gl_type)
    {
    case GL_INT:
        type = RendererDataType::INT;
        break;
    case GL_FLOAT:
        type = RendererDataType::FLOAT;
        break;
    case GL_FLOAT_VEC2:
        type = RendererDataType::VEC2;
        break;
    case GL_FLOAT_VEC3:
        type = RendererDataType::VEC3;
        break;
    case GL_FLOAT_VEC4:
        type = RendererDataType::VEC4;
        break;
    case GL_FLOAT_MAT2:
        type = RendererDataType::MAT2;
        break;
    case GL_FLOAT_MAT3:
        type = RendererDataType::MAT3;
        break;
    case GL_FLOAT_MAT4:
        type = RendererDataType::MAT4;
        break;
    case GL_FLOAT_MAT2x3:
        type = RendererDataType::MAT2X3;
        break;
    case GL_FLOAT_MAT2x4:
        type = RendererDataType::MAT2X4;
        break;
    case GL_FLOAT_MAT3x2:
        type = RendererDataType::MAT3X2;
        break;
    case GL_FLOAT_MAT3x4:
        type = RendererDataType::MAT3X4;
        break;
    case GL_FLOAT_MAT4x2:
        type = RendererDataType::MAT4X2;
        break;
    case GL_FLOAT_MAT4x3:
        type = RendererDataType::MAT4X3;
        break;
    default:
        MT_ASSERT(false, "Invalid shader data type");
        break;
    }

    return type;
}