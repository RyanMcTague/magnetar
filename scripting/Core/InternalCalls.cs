using System;
using System.Runtime.CompilerServices;

namespace Magnetar.Core
{
    internal static class InternalCalls
    {
        //==========================================
        // Time
        //==========================================
        [MethodImpl(MethodImplOptions.InternalCall)]
        internal static extern float Time_GetTime();

        //==========================================
        // Logger
        //==========================================
        [MethodImpl(MethodImplOptions.InternalCall)]
        internal static extern int Math_Random(int min, int max);
        
        //==========================================
        // Logger
        //==========================================

        [MethodImpl(MethodImplOptions.InternalCall)]
        internal static extern void Logger_Log(LogLevel level, string message);

        [MethodImpl(MethodImplOptions.InternalCall)]
        internal static extern void Logger_SetLevel(LogLevel level);

        //==========================================
        // Input
        //==========================================

        [MethodImpl(MethodImplOptions.InternalCall)]
        internal static extern ActionState Input_GetActionState(uint code);

        //==========================================
        // Game
        //==========================================

        [MethodImpl(MethodImplOptions.InternalCall)]
        internal static extern int Game_GetResolutionX();

        [MethodImpl(MethodImplOptions.InternalCall)]
        internal static extern int Game_GetResolutionY();

        //==========================================
        // Entity
        //==========================================

        [MethodImpl(MethodImplOptions.InternalCall)]
        internal static extern bool Entity_Destroy(uint id);

        [MethodImpl(MethodImplOptions.InternalCall)]
        internal static extern bool Entity_HasComponent(uint id, Type type);

        [MethodImpl(MethodImplOptions.InternalCall)]
        internal static extern void Entity_AddComponent(uint id, Type type);

        [MethodImpl(MethodImplOptions.InternalCall)]
        internal static extern void Entity_RemoveComponent(uint id, Type type);

        [MethodImpl(MethodImplOptions.InternalCall)]
        internal static extern uint Entity_GetByName(string name, out int found);

        [MethodImpl(MethodImplOptions.InternalCall)]
        internal static extern object Entity_GetScriptInstance(uint id);

        [MethodImpl(MethodImplOptions.InternalCall)]
        internal static extern object Entity_CreateEntity(Type type);

        //==========================================
        // TransformComponent
        //==========================================

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


        //==========================================
        // SpriteRenderer
        //==========================================

        [MethodImpl(MethodImplOptions.InternalCall)]
        internal static extern void SpriteRenderer_GetSize(uint id, out Vector2D size);

        [MethodImpl(MethodImplOptions.InternalCall)]
        internal static extern void SpriteRenderer_SetSize(uint id, ref Vector2D size);

        [MethodImpl(MethodImplOptions.InternalCall)]
        internal static extern void SpriteRenderer_GetColor(uint id, out Vector4D color);

        [MethodImpl(MethodImplOptions.InternalCall)]
        internal static extern void SpriteRenderer_SetColor(uint id, ref Vector4D color);

        [MethodImpl(MethodImplOptions.InternalCall)]
        internal static extern void SpriteRenderer_GetTexture(uint id, out uint color);

        [MethodImpl(MethodImplOptions.InternalCall)]
        internal static extern void SpriteRenderer_SetTexture(uint id, ref uint color);


        //==========================================
        // RigidBody2D
        //==========================================

        [MethodImpl(MethodImplOptions.InternalCall)]
        internal static extern void RigidBody2D_GetVelocity(uint id, out Vector2D velocity);

        [MethodImpl(MethodImplOptions.InternalCall)]
        internal static extern void RigidBody2D_SetVelocity(uint id, ref Vector2D velocity);

        [MethodImpl(MethodImplOptions.InternalCall)]
        internal static extern void RigidBody2D_GetAngularVelocity(uint id, out float velocity);

        [MethodImpl(MethodImplOptions.InternalCall)]
        internal static extern void RigidBody2D_SetAngularVelocity(uint id, ref float velocity);

        //==========================================
        // Tag
        //==========================================

        [MethodImpl(MethodImplOptions.InternalCall)]
        internal static extern void Tag_GetValue(uint id, out string str);

        [MethodImpl(MethodImplOptions.InternalCall)]
        internal static extern void Tag_SetValue(uint id, ref string str);

        //==========================================
        // BoxCollider
        //==========================================

        [MethodImpl(MethodImplOptions.InternalCall)]
        internal static extern void BoxCollider_GetSize(uint id, out Vector2D size);

        [MethodImpl(MethodImplOptions.InternalCall)]
        internal static extern void BoxCollider_SetSize(uint id, ref Vector2D size);

        [MethodImpl(MethodImplOptions.InternalCall)]
        internal static extern void BoxCollider_GetPosition(uint id, out Vector2D size);

        [MethodImpl(MethodImplOptions.InternalCall)]
        internal static extern void BoxCollider_SetPosition(uint id, ref Vector2D size);

        //==========================================
        // TextRenderer
        //==========================================
        [MethodImpl(MethodImplOptions.InternalCall)]
        internal static extern void TextRenderer_GetValue(uint id, out string str);

        [MethodImpl(MethodImplOptions.InternalCall)]
        internal static extern void TextRenderer_SetValue(uint id, ref string str);

        [MethodImpl(MethodImplOptions.InternalCall)]
        internal static extern void TextRenderer_GetColor(uint id, out Vector4D color);

        [MethodImpl(MethodImplOptions.InternalCall)]
        internal static extern void TextRenderer_SetColor(uint id, ref Vector4D color);

        [MethodImpl(MethodImplOptions.InternalCall)]
        internal static extern void TextRenderer_GetFont(uint id, out uint font);

        [MethodImpl(MethodImplOptions.InternalCall)]
        internal static extern void TextRenderer_SetFont(uint id, ref uint font);
    }
}