#include <glm/gtc/matrix_transform.hpp>
#include "magnetar/renderer/renderer2d.h"
#include "magnetar/renderer/vertex_array.h"
#include "magnetar/renderer/vertex_buffer.h"
#include "magnetar/renderer/index_buffer.h"
#include "magnetar/renderer/shader.h"
#include "magnetar/renderer/renderer.h"

static const char *quad_shader_source = R"""(
#stage vertex

layout (location = 0) in vec4 a_position;
layout (location = 1) in vec2 a_texcoord;
layout (location = 2) in vec4 a_color;

uniform mat4 u_view_projection;

out vec4 o_color;

void main()
{
    o_color = a_color;
    gl_Position = u_view_projection * a_position;
}

#stage fragment

in vec4 o_color;
out vec4 FragColor;

void main()
{
    FragColor = o_color;
}
)""";

namespace magnetar
{
    static constexpr uint32_t MAX_QUADS = 1000;
    static constexpr uint32_t VERTICES_PER_QUAD = 4;
    static constexpr uint32_t INDICES_PER_QUAD = 6;

    static constexpr uint32_t MAX_QUAD_VERTICES = MAX_QUADS * VERTICES_PER_QUAD;
    static constexpr uint32_t QUAD_INDICES_COUNT = MAX_QUADS * INDICES_PER_QUAD;

    struct QuadVertex
    {
        glm::vec4 position;
        glm::vec2 texcoord;
        glm::vec4 color;
    };

    struct QuadBatch
    {
        QuadVertex vertices[MAX_QUAD_VERTICES];
        QuadVertex *ptr;
        QuadVertex *end;
        uint32_t count;
        Ref<VertexArray> vertex_array;
        Ref<VertexBuffer> vertex_buffer;
        Ref<IndexBuffer> index_buffer;
        Ref<Shader> shader;
    };

    struct Renderer2DData
    {
        QuadBatch quads;
        glm::mat4 view_projection = glm::mat4(1.0f);
    };

    static Renderer2DData s_data;
}

void magnetar::Renderer2D::initialize()
{
    //==== Quad Batch =========================
    uint32_t index_data[QUAD_INDICES_COUNT];

    uint32_t offset = 0;
    for (size_t i = 0; i < QUAD_INDICES_COUNT; i += INDICES_PER_QUAD)
    {
        index_data[i + 0] = offset + 0;
        index_data[i + 1] = offset + 1;
        index_data[i + 2] = offset + 2;

        index_data[i + 3] = offset + 2;
        index_data[i + 4] = offset + 3;
        index_data[i + 5] = offset + 0;

        offset += 4;
    }

    s_data.quads.ptr = s_data.quads.vertices;
    s_data.quads.end = &s_data.quads.vertices[MAX_QUAD_VERTICES - 1] + 1;
    s_data.quads.count = 0;

    s_data.quads.shader = Renderer::create_shader("quad-batch-shader", quad_shader_source);
    s_data.quads.vertex_array = Renderer::create_vertex_array();
    s_data.quads.index_buffer = Renderer::create_index_buffer(QUAD_INDICES_COUNT, index_data);
    s_data.quads.vertex_buffer = Renderer::create_vertex_buffer(sizeof(QuadVertex) * MAX_QUADS, nullptr);

    s_data.quads.vertex_buffer->push_layout_element("a_position", RendererDataType::VEC4);
    s_data.quads.vertex_buffer->push_layout_element("a_texcoord", RendererDataType::VEC2);
    s_data.quads.vertex_buffer->push_layout_element("a_color", RendererDataType::VEC4);
    s_data.quads.vertex_array->add_vertex_buffer(s_data.quads.vertex_buffer);
    s_data.quads.vertex_array->set_index_buffer(s_data.quads.index_buffer);
}

void magnetar::Renderer2D::shutdown()
{
    s_data.quads = QuadBatch();
}

void magnetar::Renderer2D::start(const glm::mat4 &view_projection)
{
    s_data.view_projection = view_projection;
    s_data.quads.ptr = s_data.quads.vertices;
    s_data.quads.count = 0;
}

void magnetar::Renderer2D::submit()
{
    if (s_data.quads.count)
    {
        QuadBatch *batch = &s_data.quads;
        size_t size = sizeof(QuadVertex) * batch->count * VERTICES_PER_QUAD;
        batch->vertex_buffer->update(batch->vertices, 0, size);
        batch->shader->bind();
        batch->shader->set_mat4("u_view_projection", s_data.view_projection);
        Renderer::draw_indexed(batch->vertex_array, batch->index_buffer);
        batch->shader->unbind();
    }
}

void magnetar::Renderer2D::draw_quad(const glm::mat4 &transform, const glm::vec4 &color)
{
    // static glm::vec4 points[] = {
    //     glm::vec4(-0.5f, -0.5f, 0.0f, 1.0f),
    //     glm::vec4(0.5f, -0.5f, 0.0f, 1.0f),
    //     glm::vec4(0.5f, 0.5f, 0.0f, 1.0f),
    //     glm::vec4(-0.5f, 0.5f, 0.0f, 1.0f),
    // };

    static glm::vec4 points[] = {
        glm::vec4(0.0f, 0.0f, 0.0f, 1.0f),
        glm::vec4(1.0f, 0.0f, 0.0f, 1.0f),
        glm::vec4(1.0f, 1.0f, 0.0f, 1.0f),
        glm::vec4(0.0f, 1.0f, 0.0f, 1.0f),
    };

    static glm::vec2 texture_coords[] = {
        glm::vec2(0.0f, 0.0f),
        glm::vec2(1.0f, 0.0f),
        glm::vec2(1.0f, 1.0f),
        glm::vec2(0.0f, 1.0f),
    };

    QuadBatch *batch = &s_data.quads;
    MT_ASSERT(batch->count < MAX_QUAD_VERTICES, "quad vertex overflow");
    batch->count++;

    for (uint32_t i = 0; i < VERTICES_PER_QUAD; i++)
    {
        batch->ptr->position = transform * points[i];
        batch->ptr->texcoord = texture_coords[i];
        batch->ptr->color = color;
        batch->ptr++;
    }
}

void magnetar::Renderer2D::draw_quad(const glm::vec3 &position, const glm::vec2 &size, const glm::vec4 &color)
{
    auto transform = glm::translate(glm::mat4(1.0f), position) *
                     glm::scale(glm::mat4(1.0f), glm::vec3(size.x, size.y, 1.0f));

    draw_quad(transform, color);
}

void magnetar::Renderer2D::draw_quad(const glm::vec3 &position, const glm::vec2 &size, float rotation, const glm::vec4 &color)
{
    auto transform = glm::translate(glm::mat4(1.0f), position) *
                     glm::rotate(glm::mat4(1.0f), rotation, glm::vec3(0.0f, 0.0f, 1.0f)) *
                     glm::scale(glm::mat4(1.0f), glm::vec3(size.x, size.y, 1.0f));

    draw_quad(transform, color);
}