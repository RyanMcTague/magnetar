
#include <magnetar/magnetar.h>
using namespace magnetar;

std::vector<Mesh::Vertex> vertex_data = {
    {
        glm::vec3(0.5f, -0.5f, 0.0f),
        glm::vec2(1.0f, 0.0f),
        glm::vec3(0.0f, 0.0f, -1.0f),
        glm::vec4(0.0f, 1.0f, 1.0f, 1.0f),
    },
    {
        glm::vec3(-0.5f, -0.5f, 0.0f),
        glm::vec2(0.0f, 0.0f),
        glm::vec3(0.0f, 0.0f, -1.0f),
        glm::vec4(0.0f, 1.0f, 1.0f, 1.0f),
    },
    {
        glm::vec3(0.5f, 0.5f, 0.0f),
        glm::vec2(1.0f, 1.0f),
        glm::vec3(0.0f, 0.0f, -1.0f),
        glm::vec4(0.0f, 0.0f, 1.0f, 1.0f),
    },
    {
        glm::vec3(-0.5f, 0.5f, 0.0f),
        glm::vec2(0.0f, 1.0f),
        glm::vec3(0.0f, 0.0f, -1.0f),
        glm::vec4(0.0f, 0.0f, 1.0f, 1.0f),
    },
};

std::vector<uint32_t> indx = {0, 1, 2, 2, 1, 3};

namespace actions
{
    static constexpr int quit = 0;
}

class SandboxApp final : public Application
{
protected:
    void on_initialize() override;
    void on_update(float delta_time) override;

private:
    Ref<Mesh> m_mesh;
    Ref<Material> m_material;
    Ref<Texture> m_texture;
    Ref<Camera> m_camera;
    BufferMask m_mask;
    glm::mat4 m_model;
};

void SandboxApp::on_initialize()
{
    Logger::set_level(LogLevel::trace);
    InputSystem::register_action(actions::quit, KeyboardKey::ESCAPE);

    m_mask.set(BufferMask::COLOR_BUFFER);

    m_model = glm::mat4(1.0f);
    m_model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));

    auto aspect = get_window()->aspect_ratio();
    float y = 2.0f;
    float x = y * aspect;
    m_camera = create_reference<Camera2D>(-x, x, y, -y, -1.0, 1.0);

    auto file = FileSystem::get<NativeFileSystem>()->open("./sample/assets/shaders/GL_sample.glsl", FileMode::READ);
    auto source = file->to_string();
    auto shader = Renderer::create_shader(file->uri(), source);

    TextureImporter texture_importer;
    auto result = texture_importer.import("./sample/assets/images/wall.jpg");

    TextureSpecification spec;
    spec.width = result.data.width;
    spec.height = result.data.height;
    spec.format = result.data.format;
    spec.generate_mipmaps = true;
    m_texture = Renderer::create_texture2D(spec, result.data.buffer.get());

    m_mesh = create_reference<Mesh>(vertex_data, indx);
    m_material = create_reference<Material>(shader);
    m_material->set_texture("u_texture", m_texture);
}

void SandboxApp::on_update(float delta_time)
{
    if (InputSystem::action_pressed(actions::quit))
        close();

    Renderer::clear(m_mask);
    Renderer::begin_scene(m_camera);
    Renderer::submit(m_mesh, m_material, m_model);
    Renderer::end_scene();
}

int main(int argc, char **argv)
{
    SandboxApp app;
    app.initialize();
    app.run();
    return 0;
}