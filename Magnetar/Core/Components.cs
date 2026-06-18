
namespace Magnetar.Core
{
    public abstract class Component
    {
        public ScriptableEntity Entity { get; internal set; }
    }

    public class TransformComponent : Component
    {
        public Vector3D Position
        {
            get
            {
                InternalCalls.TransformComponent_GetPosition(Entity.ID, out Vector3D position);
                return position;
            }
            set
            {
                InternalCalls.TransformComponent_SetPosition(Entity.ID, ref value);
            }
        }

        public Vector3D Rotation
        {
            get
            {
                InternalCalls.TransformComponent_GetRotation(Entity.ID, out Vector3D rotation);
                return rotation;
            }
            set
            {
                InternalCalls.TransformComponent_SetRotation(Entity.ID, ref value);
            }
        }

        public Vector3D Scale
        {
            get
            {
                InternalCalls.TransformComponent_GetScale(Entity.ID, out Vector3D scale);
                return scale;
            }
            set
            {
                InternalCalls.TransformComponent_SetScale(Entity.ID, ref value);
            }
        }
    }

    public class SpriteRendererComponent : Component
    {
        public Vector2D Size
        {
            get
            {
                InternalCalls.SpriteRenderer_GetSize(Entity.ID, out Vector2D size);
                return size;
            }
            set
            {
                InternalCalls.SpriteRenderer_SetSize(Entity.ID, ref value);
            }
        }
        public Vector4D Color
        {
            get
            {
                InternalCalls.SpriteRenderer_GetColor(Entity.ID, out Vector4D color);
                return color;
            }
            set
            {
                InternalCalls.SpriteRenderer_SetColor(Entity.ID, ref value);
            }
        }
    }

    public class RigidBody2DComponent : Component
    {
        public Vector2D Velocity
        {
            get
            {
                InternalCalls.RigidBody2D_GetVelocity(Entity.ID, out Vector2D velocity);
                return velocity;
            }
            set
            {
                InternalCalls.RigidBody2D_SetVelocity(Entity.ID, ref value);
            }
        }

        public float AngularVelocity
        {
            get
            {
                InternalCalls.RigidBody2D_GetAngularVelocity(Entity.ID, out float velocity);
                return velocity;
            }
            set
            {
                InternalCalls.RigidBody2D_SetAngularVelocity(Entity.ID, ref value);
            }
        }
    }
}