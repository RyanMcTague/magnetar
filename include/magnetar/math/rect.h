#pragma once
#include <glm/glm.hpp>
#include <cmath>
#include "magnetar/core/base.h"

namespace magnetar
{
    struct MAGNETAR_API Rect
    {
        glm::vec2 bl;
        glm::vec2 tr;

        Rect()
            : bl(glm::vec2(0.0f)), tr(glm::vec2(0.0f)) {}

        Rect(float s)
            : bl(glm::vec2(0.0f, 0.0f)), tr(glm::vec2(s, s)) {}

        Rect(const glm::vec2 &bl, const glm::vec2 &tr)
            : bl(bl), tr(tr) {}

        float horizontal() const
        {
            return fabsf(tr.x - bl.x);
        }

        float vertical() const
        {
            return fabsf(tr.y - bl.y);
        }

        bool is_inside(const Rect& o) const
        {
            return bl.x >= o.bl.x && tr.x <= o.tr.x &&
                bl.y >= o.bl.y && tr.y <= o.tr.y;
        }

        bool is_overlapping(const Rect& o) const
        {
            float minX = glm::min(bl.x, tr.x), maxX = glm::max(bl.x, tr.x);
            float minY = glm::min(bl.y, tr.y), maxY = glm::max(bl.y, tr.y);
            float oMinX = glm::min(o.bl.x, o.tr.x), oMaxX = glm::max(o.bl.x, o.tr.x);
            float oMinY = glm::min(o.bl.y, o.tr.y), oMaxY = glm::max(o.bl.y, o.tr.y);
            return minX < oMaxX && maxX > oMinX &&
                   minY < oMaxY && maxY > oMinY;
        }

        bool is_no_overlap(const Rect& o) const
        {
            return !is_overlapping(o);
        }
    };
}