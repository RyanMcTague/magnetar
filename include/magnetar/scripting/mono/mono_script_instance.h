#pragma once
#include <mono/jit/jit.h>
#include "magnetar/core/base.h"
#include "magnetar/scripting/script_instance.h"
#include "magnetar/scene/entity_handle.h"
namespace magnetar
{
    class MonoScriptClass;

    class MAGNETAR_API MonoScriptInstance : public ScriptInstance
    {
    public:
        MonoScriptInstance(MonoScriptClass *klass, MonoObject *object);

        void *get_native_handle() override;

        bool has_method(const std::string &name) const override;
        void invoke_ctor() override;
        void invoke_set_id(EntityHandle handle) override;
        void invoke_on_start() override;
        void invoke_on_update(float delta_time) override;
        void invoke_on_collision(ScriptInstance *entity) override;

    private:
        MonoObject *m_object;
        MonoScriptClass *m_class;
    };
}