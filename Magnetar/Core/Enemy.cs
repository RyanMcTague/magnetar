
namespace Magnetar.Core
{
    public class Enemy: ScriptableEntity
    {
        RigidBody2DComponent rigidBody;

        private float step = 0.0f;

        private float sign = -1.0f;

        protected void OnStart()
        {
            rigidBody = GetComponent<RigidBody2DComponent>();
            rigidBody.AngularVelocity = 45.0f * 3.14159f / 180.0f;
        }

        protected void OnUpdate(float dt)
        {
            step += dt;

            if(step >= 1.0)
            {
                rigidBody.AngularVelocity = sign * 45.0f * 3.14159f / 180.0f;
                step = 0.0f;
                sign *= -1.0f;
            }
        }
    }
}