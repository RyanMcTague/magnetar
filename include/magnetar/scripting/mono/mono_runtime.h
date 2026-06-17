#pragma once
#include <mono/jit/jit.h>
#include "magnetar/core/base.h"
#include "magnetar/scripting/script_runtime.h"

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

    private:
        MonoDomain *m_domain;
        MonoAssembly *m_assembly;
        MonoImage* m_image;
    };
}