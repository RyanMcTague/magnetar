#pragma once
#include <unordered_map>
#include <mono/metadata/class.h>
#include "magnetar/core/base.h"
#include "magnetar/scripting/script_class.h"
#include "magnetar/scene/entity_handle.h"
namespace magnetar
{
    class MAGNETAR_API MonoScriptClass : public ScriptClass
    {
    public:
        MonoScriptClass(MonoDomain* domain, MonoImage *image, const std::string &ns, const std::string &name);
        
        const std::string &name() const override;

        UniqueRef<class ScriptInstance> create_instance() override;

        void* get_native_handle() override;

    protected:
        void invoke_method(void* object, const char *name, void **args, int argc) override;

    private:
        std::string m_name;
        MonoClass *m_class;
        MonoDomain *m_domain;

        std::unordered_map<std::string, MonoMethod*> m_methods;
        
        // void invoke_ctor(MonoObject* object);
        // void invoke_set_handle(MonoObject* object, EntityHandle handle);
        // void invoke_on_start(MonoObject* object);
        // void invoke_on_update(MonoObject* object, float delta_time);

        friend class MonoScriptInstance;

        void register_methods(MonoClass* klass);
    };
}