#pragma once
#include "magnetar/core/base.h"

namespace magnetar
{
    class MAGNETAR_API ScriptInstance
    {
    public:
        virtual ~ScriptInstance() = default;    
        
        virtual void invoke(const std::string& method, void** args) = 0;
    };
}