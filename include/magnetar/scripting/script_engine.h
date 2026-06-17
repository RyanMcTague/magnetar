#pragma once
#include "magnetar/core/base.h"
#include "magnetar/scripting/script_runtime.h"

namespace magnetar
{
    class MAGNETAR_API ScriptEngine
    {
    public:

        static bool initialize();
        static bool shutdown();

        static bool load_assembly(const std::string &path);
        static bool reload_assembly();

        static void update(float delta_time);

    private:
        ScriptEngine() = default;
        static Ref<ScriptRuntime> s_runtime;
    };
}