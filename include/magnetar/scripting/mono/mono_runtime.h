#pragma once
#include <unordered_map>
#include <unordered_set>
#include <mono/jit/jit.h>
#include "magnetar/core/base.h"
#include "magnetar/scripting/script_runtime.h"
#include "magnetar/scripting/script_instance.h"

namespace magnetar
{
    class MonoRuntime : public ScriptRuntime
    {
    public:
        bool initialize() override;
        bool shutdown() override;

        bool load_assembly(const std::string &path) override;
        bool reload_assembly() override;

        void update(float delta_time) override;

        ScriptInstance *create_entity_instance(const std::string &name, EntityHandle handle) override;

        ScriptInstance *allocate_entity_instance(const std::string &name, EntityHandle handle) override;

        void start_all_entity_instances() override;

        ScriptInstance *get_entity_instance(EntityHandle handle) override;

        void remove_entity_instance(EntityHandle handle) override;

    private:
        MonoDomain *m_domain;
        MonoAssembly *m_client_assembly;
        MonoImage *m_client_image;
        MonoAssembly *m_engine_assembly;
        MonoImage *m_engine_image;
        std::unordered_map<EntityHandle, UniqueRef<ScriptInstance>> m_entity_instances;
        std::unordered_set<EntityHandle> m_started_instances;
    };
}