#pragma once
#include <mono/jit/jit.h>
#include "magnetar/core/base.h"
#include "magnetar/scripting/script_instance.h"

namespace magnetar
{
    class MonoScriptClass;

    class MAGNETAR_API MonoScriptInstance: public ScriptInstance
    {
    public:
        MonoScriptInstance(MonoScriptClass* klass, MonoObject* object);

        void invoke(const std::string& method, void** args) override;

    private:
        MonoObject* m_object;
        MonoScriptClass *m_class;
    };
}