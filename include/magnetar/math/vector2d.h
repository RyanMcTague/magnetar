#pragma once
#include "magnetar/core/base.h"

namespace magnetar
{
    struct MAGNETAR_API Vector2D
    {
        double x;
        double y;

        Vector2D()
            : x(0), y(0) {}
        
        Vector2D(double s)
            : x(s), y(s) {}
        
        Vector2D(double x, double y)
            : x(x), y(y) {}
    };
}