namespace Magnetar.Core
{
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