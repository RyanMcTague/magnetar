#include "magnetar/renderer/backend/opengl/helpers.h"
#include "magnetar/utils/enum_utils.h"

GLenum magnetar::GLHelpers::gl_check_error_(const char *func, const char *file, int line)
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
        MT_ASSERT(errorCode != GL_NO_ERROR, "\n - source: OpenGL\n - function: {0}\n - code: {1}\n - file: {2}:{3}", func, error, file, line);
    }
    return errorCode;
}

magnetar::RendererDataType magnetar::GLHelpers::convert_renderer_type(GLenum gl_type)
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
    case GL_SAMPLER_2D:
        type = RendererDataType::INT;
        break;
    default:
        MT_ASSERT(false, "Invalid shader data type");
        break;
    }

    return type;
}

GLenum magnetar::GLHelpers::texture_format_type(TextureFormat format)
{

    GLenum f = 0;

    switch (format)
    {
    case TextureFormat::RGB8:
        f = GL_RGB;
        break;
    case TextureFormat::RGBA8:
        f = GL_RGBA;
        break;
    case TextureFormat::RGBA16F:
        f = GL_RGBA16F;
        break;
    case TextureFormat::DEPTH24_STENCIL8:
        f = GL_DEPTH24_STENCIL8;
        break;
    default:
        LOG_ERROR(logger::tags::renderer, "invalid texture format {} for OpenGL", enum_utils::lowercase_name(format));
        f = 0;
        break;
    }
    return f;
}

GLenum magnetar::GLHelpers::texture_filter_type(TextureFilter filter)
{
    GLenum value = 0;
    switch (filter)
    {
    case TextureFilter::LINEAR:
        value = GL_LINEAR;
        break;
    case TextureFilter::NEAREST:
        value = GL_NEAREST;
        break;
    default:
        break;
    }
    return value;
}

GLenum magnetar::GLHelpers::texture_wrap_type(TextureWrap wrap)
{
    GLenum value = 0;
    switch (wrap)
    {
    case TextureWrap::REPEAT:
        value = GL_REPEAT;
        break;
    case TextureWrap::CLAMP_TO_EDGE:
        value = GL_CLAMP_TO_EDGE;
        break;
    default:
        break;
    }
    return value;
}

GLenum magnetar::GLHelpers::draw_mode_type(DrawMode mode)
{
    GLenum value = 0;
    switch (mode)
    {
    case DrawMode::TRIANGLES:
        value = GL_TRIANGLES;
        break;
    case DrawMode::LINES:
        value = GL_LINES;
        break;
    default:
        break;
    }
    return value;
}