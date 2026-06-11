#include "magnetar/scene/scene.h"

magnetar::Scene::Scene()
    : m_camera(nullptr) {}

void magnetar::Scene::set_camera(Ref<Camera> camera)
{
    m_camera = camera;
}