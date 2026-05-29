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

GLenum magnetar::OpenGLHelpers::gl_check_error_(const char *func, const char *file, int line)
{
    GLenum errorCode = GL_NO_ERROR;
    while ((errorCode = glGetError()) != GL_NO_ERROR)
    {
        std::string error;
        switch (errorCode)
        {
        case GL_INVALID_ENUM:
            error = "INVALID_ENUM";
            break;
        case GL_INVALID_VALUE:
            error = "INVALID_VALUE";
            break;
        case GL_INVALID_OPERATION:
            error = "INVALID_OPERATION";
            break;
        case GL_STACK_OVERFLOW:
            error = "STACK_OVERFLOW";
            break;
        case GL_STACK_UNDERFLOW:
            error = "STACK_UNDERFLOW";
            break;
        case GL_OUT_OF_MEMORY:
            error = "OUT_OF_MEMORY";
            break;
        case GL_INVALID_FRAMEBUFFER_OPERATION:
            error = "INVALID_FRAMEBUFFER_OPERATION";
            break;
        }
        std::string msg = fmt::format("\n - source: OpenGL\n - function: {0}\n - code: {1}\n - file: {2}:{3}", func, error, file, line);
        MT_ASSERT(errorCode != GL_NO_ERROR, msg);
    }
    return errorCode;
}