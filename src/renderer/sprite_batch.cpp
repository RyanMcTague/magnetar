#include <glm/gtc/matrix_transform.hpp>
#include "magnetar/renderer/sprite_batch.h"
#include "magnetar/renderer/renderer.h"

const char *shader_source = R"""(
#stage vertex

layout (location = 0) in vec4 a_position;
layout (location = 1) in vec4 a_color;

uniform mat4 u_view_projection;

out vec2 o_color;

void main()
{
    o_color = a_color;
    gl_Position = u_view_projection * a_position;
}

#stage fragment

in vec2 o_color;
out vec4 FragColor;

void main()
{
    FragColor = o_color;
}
)""";

magnetar::SpriteBatch::SpriteBatch(uint32_t max_quads)
    : m_num_quads(max_quads)
{
    m_current_quad_count = 0;
    m_vertex_index = 0;
    m_vertex_data_count = VERTICES_PER_QUAD * m_num_quads;
    m_vertex_data = new Vertex[m_vertex_data_count];

    m_vertex_array = Renderer::create_vertex_array();
    m_vertex_buffer = Renderer::create_vertex_buffer(m_vertex_data_count * sizeof(Vertex));
    m_vertex_buffer->push_layout_element("a_position", RendererDataType::VEC4);
    m_vertex_buffer->push_layout_element("a_color", RendererDataType::VEC4);

    uint32_t index_data_count = INDICES_PER_QUAD * m_num_quads;
    auto index_data = new uint32_t[index_data_count];

    uint32_t offset = 0;
    for (size_t i = 0; i < index_data_count; i++)
    {
        index_data[i + 0] = offset + 0;
        index_data[i + 1] = offset + 1;
        index_data[i + 2] = offset + 2;

        index_data[i + 3] = offset + 2;
        index_data[i + 4] = offset + 3;
        index_data[i + 5] = offset + 0;

        offset += 4;
    }
    auto index_buffer = Renderer::create_index_buffer(index_data_count, index_data);

    m_vertex_array->add_vertex_buffer(m_vertex_buffer);
    m_vertex_array->set_index_buffer(index_buffer);

    m_shader = Renderer::create_shader("sprite-batch", shader_source);

    delete[] index_data;
}

magnetar::SpriteBatch::~SpriteBatch()
{
    delete[] m_vertex_data;
}

void magnetar::SpriteBatch::start(const glm::mat4 &view_projection)
{
    m_view_projection = view_projection;
    m_vertex_index = 0;
    m_current_quad_count = 0;
}

void magnetar::SpriteBatch::render()
{
    if (m_vertex_index)
    {
        size_t size = m_vertex_index * sizeof(Vertex);
        m_vertex_buffer->update(m_vertex_data, 0, size);
        m_shader->bind();
        Renderer::draw_indexed(m_vertex_array, m_vertex_array->index_buffer());
        m_shader->unbind();
    }
}

void magnetar::SpriteBatch::draw_quad(const glm::mat4 &transform, const glm::vec4 &color)
{
    static glm::vec4 points[] = {
        glm::vec4(-0.5f, -0.5f, 0.0f, 1.0f),
        glm::vec4(0.5f, -0.5f, 0.0f, 1.0f),
        glm::vec4(0.5f, 0.5f, 0.0f, 1.0f),
        glm::vec4(-0.5f, 0.5f, 0.0f, 1.0f),
    };

    // static glm::vec2 textureCoords[] = {
    //     glm::vec2(0.0f, 0.0f),
    //     glm::vec2(1.0f, 0.0f),
    //     glm::vec2(1.0f, 1.0f),
    //     glm::vec2(0.0f, 1.0f),
    // };

    MT_ASSERT(m_vertex_index + VERTICES_PER_QUAD < m_vertex_data_count, "vertex overflow");

    for (uint32_t i = 0; i < VERTICES_PER_QUAD; i++)
    {
        m_vertex_data[m_vertex_index].position = transform * points[i];
        m_vertex_data[m_vertex_index].color = color;
        m_vertex_index++;
    }

    m_current_quad_count++;
}

void magnetar::SpriteBatch::draw_quad(const glm::vec3 &position, const glm::vec2 &size, const glm::vec4 &color)
{
    auto transform = glm::translate(glm::mat4(1.0f), position) *
                     glm::scale(glm::mat4(1.0f), glm::vec3(size.x, size.y, 1.0f));

    draw_quad(transform, color);
}

void magnetar::SpriteBatch::draw_quad(const glm::vec3 &position, const glm::vec2 &size, float rotation, const glm::vec4 &color)
{
    auto transform = glm::translate(glm::mat4(1.0f), position) *
                     glm::rotate(glm::mat4(1.0f), rotation, glm::vec3(0.0f, 0.0f, 1.0f)) *
                     glm::scale(glm::mat4(1.0f), glm::vec3(size.x, size.y, 1.0f));

    draw_quad(transform, color);
}
