#pragma once
#include "magnetar/core/base.h"
#include "magnetar/scene/entity_handle.h"

namespace magnetar
{
    class MAGNETAR_API ScriptClass
    {
    public:
        virtual ~ScriptClass() = default;

        virtual const std::string &name() const = 0;

        virtual UniqueRef<class ScriptInstance> create_instance() = 0;

        virtual void *get_native_handle() = 0;

    protected:
        virtual void invoke_method(void* object, const char *name, void **args, int argc) = 0;

    private:
        template <typename... Args>
        void invoke(void* object, const char *name, Args... args);
    };

    template <typename... Args>
    void ScriptClass::invoke(void* object, const char *name, Args... args)
    {
        if constexpr (sizeof...(Args) == 0)
        {
            invoke_method(object, name, nullptr, 0);
        }
        else
        {
            void *arg_ptrs[] = {(void *)(&args)...};
            invoke_method(object, name, arg_ptrs, static_cast<int>(sizeof...(Args)));
        }
    }
}