#pragma once
#include "magnetar/core/base.h"
#include "magnetar/scene/entity_handle.h"
namespace magnetar
{
    class MAGNETAR_API ScriptInstance
    {
    public:
        virtual ~ScriptInstance() = default;

        virtual void *get_native_handle() = 0;

        virtual bool has_method(const std::string& name) const = 0;

        template <typename... Args>
        void invoke(const char *name, Args... args)
        {
            if constexpr (sizeof...(Args) == 0)
            {
                invoke_method(name, nullptr, 0);
            }
            else
            {
                void *arg_ptrs[] = {(void *)(&args)...};
                invoke_method(name, arg_ptrs, static_cast<int>(sizeof...(Args)));
            }
        }

    protected:
        virtual void invoke_method(const char *name, void **args, int argc) = 0;
    };

    class MAGNETAR_API EntityScriptInstance
    {
    public:
        EntityScriptInstance(ScriptInstance* instance)
            : m_instance(instance) {}

        void constructor() const
        {
            m_instance->invoke(".ctor");
        }

        void set_handle(EntityHandle handle) const
        {
            m_instance->invoke("set_ID", handle);
        }

        void on_start() const
        {
            m_instance->invoke("OnStart");
        }

        void on_update(float dt) const
        {
            m_instance->invoke("OnUpdate", dt);
        }
    private:
        ScriptInstance *m_instance;
    };
}