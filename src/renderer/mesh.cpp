#include "magnetar/renderer/mesh.h"
#include "magnetar/renderer/renderer.h"

magnetar::Mesh::Mesh(const std::vector<Vertex> &vertices, const std::vector<uint32_t> &indices)
    : m_vao(nullptr), m_vbo(nullptr), m_ibo(nullptr), m_index_count(indices.size())
{
    m_vao = Renderer::create_vertex_array();
    m_vbo = Renderer::create_vertex_buffer(vertices.size() * sizeof(Vertex), vertices.data());
    m_ibo = Renderer::create_index_buffer(indices.size() * sizeof(uint32_t), indices.data());
    m_index_count = indices.size();

    m_vbo->push_layout_element("a_position", RendererDataType::VEC3);
    m_vbo->push_layout_element("a_texcoord", RendererDataType::VEC2);
    m_vbo->push_layout_element("a_normal", RendererDataType::VEC3);
    m_vbo->push_layout_element("a_color", RendererDataType::VEC4);
    m_vao->add_vertex_buffer(m_vbo);
    m_vao->set_index_buffer(m_ibo);
}

void magnetar::Mesh::draw() const
{
    Renderer::draw_indexed(m_vao, m_ibo);
}