#pragma once
#include <unordered_map>
#include <mono/metadata/class.h>
#include "magnetar/core/base.h"
#include "magnetar/scripting/enums.h"
#include "magnetar/scripting/script_class.h"
namespace magnetar
{
    class MAGNETAR_API MonoScriptClass : public ScriptClass
    {
    public:
        MonoScriptClass(MonoDomain* domain, MonoImage *image, const std::string &ns, const std::string &name);
        
        const std::string &name() const override;

        UniqueRef<class ScriptInstance> create_instance() override;

    private:
        struct MethodEntry
        {
            MonoMethod* method;
            ScriptVisibility visibility;
        };
        std::string m_name;
        MonoClass *m_class;
        MonoDomain *m_domain;
        std::unordered_map<std::string, MethodEntry> m_methods;
        
        void parse_method(MonoMethod* method);

        void invoke(MonoObject* object, const std::string& method, void** args);

        friend class MonoScriptInstance;
    };
}