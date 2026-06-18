using System;
using System.Runtime.CompilerServices;

namespace Magnetar.Core
{
    internal static class InternalCalls
    {
          
        [MethodImpl(MethodImplOptions.InternalCall)]
        internal static extern void Logger_Log(LogLevel level, string message);
        
        [MethodImpl(MethodImplOptions.InternalCall)]
        internal static extern bool Entity_HasComponent(uint id, Type type);

        [MethodImpl(MethodImplOptions.InternalCall)]
        internal static extern void TransformComponent_GetPosition(uint id, out Vector3D position);

        [MethodImpl(MethodImplOptions.InternalCall)]
        internal static extern void TransformComponent_SetPosition(uint id, ref Vector3D position);

        [MethodImpl(MethodImplOptions.InternalCall)]
        internal static extern void TransformComponent_GetRotation(uint id, out Vector3D rotation);

        [MethodImpl(MethodImplOptions.InternalCall)]
        internal static extern void TransformComponent_SetRotation(uint id, ref Vector3D rotation);

        [MethodImpl(MethodImplOptions.InternalCall)]
        internal static extern void TransformComponent_GetScale(uint id, out Vector3D scale);

        [MethodImpl(MethodImplOptions.InternalCall)]
        internal static extern void TransformComponent_SetScale(uint id, ref Vector3D scale);

        [MethodImpl(MethodImplOptions.InternalCall)]
        internal static extern void SpriteRenderer_GetSize(uint id, out Vector2D size);

        [MethodImpl(MethodImplOptions.InternalCall)]
        internal static extern void SpriteRenderer_SetSize(uint id, ref Vector2D size);

        [MethodImpl(MethodImplOptions.InternalCall)]
        internal static extern void SpriteRenderer_GetColor(uint id, out Vector4D color);

        [MethodImpl(MethodImplOptions.InternalCall)]
        internal static extern void SpriteRenderer_SetColor(uint id, ref Vector4D color);
    }
}