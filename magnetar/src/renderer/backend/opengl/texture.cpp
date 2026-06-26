#include "magnetar/renderer/backend/opengl/texture.h"
#include "magnetar/renderer/backend/opengl/helpers.h"

magnetar::GLTexture2D::GLTexture2D(const TextureSpecification &spec, const void *data)
    : m_spec(spec), m_handle(0)
{
    glGenTextures(1, &m_handle);
    glBindTexture(GL_TEXTURE_2D, m_handle);

    glTexImage2D(
        GL_TEXTURE_2D,
        0,
        GLHelpers::texture_format_type(spec.format),
        m_spec.width,
        m_spec.height,
        0,
        GLHelpers::texture_format_type(spec.format),
        GL_UNSIGNED_BYTE,
        data);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GLHelpers::texture_filter_type(m_spec.min_filter));
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GLHelpers::texture_filter_type(m_spec.mag_filter));

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GLHelpers::texture_wrap_type(m_spec.wrap));
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GLHelpers::texture_wrap_type(m_spec.wrap));

    if (m_spec.generate_mipmaps && data)
        glGenerateMipmap(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);
    LOG_TRACE(logger::tags::renderer, "created OpenGL texture2D {}", m_handle);
}

magnetar::GLTexture2D::~GLTexture2D()
{
    if (m_handle)
        glDeleteTextures(1, &m_handle);
}
void magnetar::GLTexture2D::bind(uint32_t slot) const
{
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, m_handle);
}
void magnetar::GLTexture2D::unbind() const
{
    glBindTexture(GL_TEXTURE_2D, 0);
}

void magnetar::GLTexture2D::set_data(const void *data, uint32_t)
{
    glBindTexture(GL_TEXTURE_2D, m_handle);
    glTexSubImage2D(
        GL_TEXTURE_2D,
        0,
        0,
        0,
        m_spec.width,
        m_spec.height,
        GLHelpers::texture_format_type(m_spec.format),
        GL_UNSIGNED_BYTE,
        data);

    if (m_spec.generate_mipmaps && data)
        glGenerateMipmap(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, 0);
}
