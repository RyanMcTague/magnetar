#include <glm/gtc/matrix_transform.hpp>
#include "magnetar/renderer/renderer2d.h"
#include "magnetar/renderer/vertex_array.h"
#include "magnetar/renderer/vertex_buffer.h"
#include "magnetar/renderer/index_buffer.h"
#include "magnetar/renderer/shader.h"
#include "magnetar/renderer/renderer.h"

#include "magnetar/core/application.h"
#include "magnetar/core/window.h"

static const char *text_shader_source = R"""(
#stage vertex

layout (location = 0) in vec4 a_position;
layout (location = 1) in vec2 a_texcoord;
layout (location = 2) in vec4 a_color;

uniform mat4 u_view_projection;

out vec4 o_color;
out vec2 o_texcoord;

void main()
{
    o_color = a_color;
    o_texcoord = a_texcoord;
    gl_Position = u_view_projection * a_position;
}

#stage fragment

out vec4 FragColor;
in vec4 o_color;
in vec2 o_texcoord;

uniform sampler2D u_texture;

void main()
{
    float alpha = texture(u_texture, o_texcoord).r;
    FragColor = vec4(o_color.rgb, o_color.a * alpha);
}

)""";

static const char *quad_shader_source = R"""(
#stage vertex

layout (location = 0) in vec4 a_position;
layout (location = 1) in vec2 a_texcoord;
layout (location = 2) in vec4 a_color;
layout (location = 3) in float a_texture;

uniform mat4 u_view_projection;
uniform float u_null_texcoord;

out vec4 o_color;
out vec2 o_texcoord;
out float o_texture;
out float o_null_texcoord;

void main()
{
    o_color = a_color;
    o_texcoord = a_texcoord;
    o_texture = int(a_texture);
    o_null_texcoord = u_null_texcoord;
    gl_Position = u_view_projection * a_position;
}

#stage fragment

in vec4 o_color;
in vec2 o_texcoord;
in float o_texture;
in float o_null_texcoord;

int used_texture = int(o_texture);
int null_texcoord = int(o_null_texcoord);

out vec4 FragColor;

uniform sampler2D u_texture0;

void main()
{
    if(used_texture < null_texcoord)
    {
        switch(used_texture)
        {
        case 0:
            FragColor = texture(u_texture0, o_texcoord);
            break;
        default:
            break;
        }
    }
    else
    {
        FragColor = o_color;
    }
}
)""";

namespace magnetar
{
    static constexpr int MAX_TEXTURE_SLOTS = 1;
    static constexpr int NULL_TEXTURE_SLOT = MAX_TEXTURE_SLOTS + 1;

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
        float texture;
    };

    struct TextVertex
    {
        glm::vec4 position;
        glm::vec2 texcoord;
        glm::vec4 color;
    };

    struct QuadBatch
    {
        Ref<Texture2D> textures[MAX_TEXTURE_SLOTS];
        int texture_count;
        QuadVertex vertices[MAX_QUAD_VERTICES];
        QuadVertex *ptr;
        QuadVertex *end;
        uint32_t count;
        Ref<VertexArray> vertex_array;
        Ref<VertexBuffer> vertex_buffer;
        Ref<IndexBuffer> index_buffer;
        Ref<Shader> shader;
    };

    struct TextBatch
    {
        Ref<Texture2D> textures[MAX_TEXTURE_SLOTS];
        int texture_count;
        TextVertex vertices[MAX_QUAD_VERTICES];
        TextVertex *ptr;
        TextVertex *end;
        uint32_t count;
        Ref<VertexArray> vertex_array;
        Ref<VertexBuffer> vertex_buffer;
        Ref<IndexBuffer> index_buffer;
        Ref<Shader> shader;
    };

    struct Renderer2DData
    {
        QuadBatch quads;
        TextBatch text;
        glm::mat4 view_projection = glm::mat4(1.0f);
        glm::mat4 text_view_projection = glm::mat4(1.0f);
    };

    static Renderer2DData s_data;

    inline static glm::vec2 get_indexed_uv(const Rect &rect, int i)
    {
        switch (i)
        {
        case 0:
            return rect.bl;
        case 1:
            return glm::vec2(rect.tr.x, rect.bl.y);
        case 2:
            return rect.tr;
        case 3:
            return glm::vec2(rect.bl.x, rect.tr.y);
        default:
            break;
        }
        return glm::vec2(0.0f);
    }

}

void magnetar::Renderer2D::initialize()
{
    Renderer::set_blend_enabled(true);
    Renderer::set_blend_func(BlendFactor::SRC_ALPHA, BlendFactor::ONE_MINUS_SRC_ALPHA);

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
    s_data.quads.texture_count = 0;

    s_data.quads.shader = Renderer::create_shader("quad-batch-shader", quad_shader_source);
    s_data.quads.vertex_array = Renderer::create_vertex_array();
    s_data.quads.index_buffer = Renderer::create_index_buffer(QUAD_INDICES_COUNT, index_data);
    s_data.quads.vertex_buffer = Renderer::create_vertex_buffer(sizeof(QuadVertex) * MAX_QUADS, nullptr);

    s_data.quads.vertex_buffer->push_layout_element("a_position", RendererDataType::VEC4);
    s_data.quads.vertex_buffer->push_layout_element("a_texcoord", RendererDataType::VEC2);
    s_data.quads.vertex_buffer->push_layout_element("a_color", RendererDataType::VEC4);
    s_data.quads.vertex_buffer->push_layout_element("a_texture", RendererDataType::FLOAT);
    s_data.quads.vertex_array->add_vertex_buffer(s_data.quads.vertex_buffer);
    s_data.quads.vertex_array->set_index_buffer(s_data.quads.index_buffer);

    //==== Text Batch =========================
    s_data.text.ptr = s_data.text.vertices;
    s_data.text.end = &s_data.text.vertices[MAX_QUAD_VERTICES - 1] + 1;
    s_data.text.count = 0;
    s_data.text.texture_count = 0;

    s_data.text.shader = Renderer::create_shader("text-batch-shader", text_shader_source);
    s_data.text.vertex_array = Renderer::create_vertex_array();
    s_data.text.index_buffer = Renderer::create_index_buffer(QUAD_INDICES_COUNT, index_data);
    s_data.text.vertex_buffer = Renderer::create_vertex_buffer(sizeof(TextVertex) * MAX_QUADS, nullptr);

    s_data.text.vertex_buffer->push_layout_element("a_position", RendererDataType::VEC4);
    s_data.text.vertex_buffer->push_layout_element("a_texcoord", RendererDataType::VEC2);
    s_data.text.vertex_buffer->push_layout_element("a_color", RendererDataType::VEC4);
    s_data.text.vertex_array->add_vertex_buffer(s_data.text.vertex_buffer);
    s_data.text.vertex_array->set_index_buffer(s_data.text.index_buffer);
}

void magnetar::Renderer2D::shutdown()
{
    s_data.quads = QuadBatch();
    s_data.text = TextBatch();
}

void magnetar::Renderer2D::start(const glm::mat4 &view_projection)
{
    float width = Application::get()->get_window()->width();
    float height = Application::get()->get_window()->height();
    
    s_data.text_view_projection = glm::ortho(0.0f, width, 0.0f, height, -1.0f, 1.0f);
    s_data.view_projection = view_projection;

    s_data.quads.ptr = s_data.quads.vertices;
    s_data.quads.count = 0;
    s_data.quads.texture_count = 0;

    s_data.text.ptr = s_data.text.vertices;
    s_data.text.count = 0;
    s_data.text.texture_count = 0;
}

void magnetar::Renderer2D::submit()
{
    if (s_data.quads.count)
    {
        QuadBatch *batch = &s_data.quads;
        size_t size = sizeof(QuadVertex) * batch->count * VERTICES_PER_QUAD;
        batch->vertex_buffer->update(batch->vertices, 0, size);

        batch->shader->bind();
        for (int i = 0; i < batch->texture_count; i++)
        {
            s_data.quads.textures[i]->bind(i);
            std::string uniform_name = "u_texture" + std::to_string(i);
            batch->shader->set_int(uniform_name, i);
        }

        batch->shader->set_mat4("u_view_projection", s_data.view_projection);
        batch->shader->set_float("u_null_texcoord", NULL_TEXTURE_SLOT);
        Renderer::draw_indexed(DrawMode::TRIANGLES, batch->vertex_array, batch->index_buffer);
        batch->shader->unbind();
    }

    if (s_data.text.count)
    {
        TextBatch *batch = &s_data.text;
        size_t size = sizeof(TextVertex) * batch->count * VERTICES_PER_QUAD;
        batch->vertex_buffer->update(batch->vertices, 0, size);

        batch->shader->bind();
        if (batch->textures[0])
        {
            batch->textures[0]->bind(0);
            batch->shader->set_int("u_texture", 0);
        }

        batch->shader->set_mat4("u_view_projection", s_data.text_view_projection);
        Renderer::draw_indexed(DrawMode::TRIANGLES, batch->vertex_array, batch->index_buffer);
        batch->shader->unbind();
    }

    for (uint32_t i = 0; i < MAX_TEXTURE_SLOTS; i++)
    {
        s_data.quads.textures[i] = nullptr;
        s_data.text.textures[i] = nullptr;
    }
}

void magnetar::Renderer2D::draw_quad(const glm::mat4 &transform, const glm::vec4 &color, const Ref<Texture2D> &texture, const Rect &rect)
{
    static glm::vec4 points[] = {
        glm::vec4(0.0f, 0.0f, 0.0f, 1.0f),
        glm::vec4(1.0f, 0.0f, 0.0f, 1.0f),
        glm::vec4(1.0f, 1.0f, 0.0f, 1.0f),
        glm::vec4(0.0f, 1.0f, 0.0f, 1.0f),
    };

    // static glm::vec2 texture_coords[] = {
    //     glm::vec2(0.0f, 0.0f), // bl
    //     glm::vec2(1.0f, 0.0f), // tl
    //     glm::vec2(1.0f, 1.0f), // tr
    //     glm::vec2(0.0f, 1.0f), // br
    // };

    QuadBatch *batch = &s_data.quads;

    float texture_slot = (float)NULL_TEXTURE_SLOT;

    if (texture)
    {
        bool found = false;
        for (uint32_t i = 0; i < MAX_TEXTURE_SLOTS; i++)
        {
            if (s_data.quads.textures[i] == texture)
            {
                found = true;
                texture_slot = (float)i;
                break;
            }
        }

        if (!found)
        {
            MT_ASSERT(batch->texture_count < MAX_TEXTURE_SLOTS, "quad texture overflow");
            s_data.quads.textures[batch->texture_count] = texture;
            texture_slot = (float)batch->texture_count;
            s_data.quads.texture_count++;
        }
    }

    MT_ASSERT(batch->count < MAX_QUAD_VERTICES, "quad vertex overflow");
    batch->count++;

    for (uint32_t i = 0; i < VERTICES_PER_QUAD; i++)
    {
        batch->ptr->position = transform * points[i];
        batch->ptr->texcoord = get_indexed_uv(rect, i);
        batch->ptr->color = color;
        batch->ptr->texture = texture_slot;
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

void magnetar::Renderer2D::draw_quad(const glm::vec3 &position, const glm::vec2 &size, const Ref<Texture2D> &texture, const Rect &rect)
{
    auto transform = glm::translate(glm::mat4(1.0f), position) *
                     glm::scale(glm::mat4(1.0f), glm::vec3(size.x, size.y, 1.0f));

    draw_quad(transform, glm::vec4(0.0f), texture, rect);
}

void magnetar::Renderer2D::draw_quad(const glm::vec3 &position, const glm::vec2 &size, float rotation, const Ref<Texture2D> &texture, const Rect &rect)
{
    auto transform = glm::translate(glm::mat4(1.0f), position) *
                     glm::rotate(glm::mat4(1.0f), rotation, glm::vec3(0.0f, 0.0f, 1.0f)) *
                     glm::scale(glm::mat4(1.0f), glm::vec3(size.x, size.y, 1.0f));

    draw_quad(transform, glm::vec4(0.0f), texture, rect);
}

void magnetar::Renderer2D::draw_text(const std::string &text, Ref<Font> font, const glm::vec3 &position, const glm::vec4 &color)
{
    static glm::vec4 points[] = {
        glm::vec4(0.0f, 0.0f, 0.0f, 1.0f),
        glm::vec4(1.0f, 0.0f, 0.0f, 1.0f),
        glm::vec4(1.0f, 1.0f, 0.0f, 1.0f),
        glm::vec4(0.0f, 1.0f, 0.0f, 1.0f),
    };

    TextBatch *batch = &s_data.text;

    Ref<Texture2D> texture = font->texture();
    if (texture && !s_data.text.textures[0])
    {
        MT_ASSERT(batch->texture_count < MAX_TEXTURE_SLOTS, "text texture overflow");
        s_data.text.textures[batch->texture_count] = texture;
        batch->texture_count++;
    }

    float x = position.x;
    float y = position.y;

    for (auto ch : text)
    {
        if(ch == '\n')
        {
            x = position.x;
            y -= font->size();
            continue;
        }

        Font::Glyph glyph = font->get(ch);

        float gx = x + glyph.bearing.x;
        float gy = y - (glyph.size.y - glyph.bearing.y);

        auto transform = glm::translate(glm::mat4(1.0f), glm::vec3(gx, gy, position.z)) *
                         glm::scale(glm::mat4(1.0f), glm::vec3(glyph.size.x, glyph.size.y, 1.0f));

        MT_ASSERT(batch->count < MAX_QUAD_VERTICES, "text vertex overflow");
        batch->count++;

        Rect rect;
        rect.bl = glyph.uv0;
        rect.tr = glyph.uv1;

        for (uint32_t i = 0; i < VERTICES_PER_QUAD; i++)
        {
            batch->ptr->position = transform * points[i];
            batch->ptr->texcoord = get_indexed_uv(rect, i);
            batch->ptr->color = color;
            batch->ptr++;
        }
        x += glyph.advance.x / 64.0f;
    }
}