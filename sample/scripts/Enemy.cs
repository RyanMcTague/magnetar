using Magnetar.Core;

namespace Sample
{
    public class Enemy: Entity
    {
        RigidBody2DComponent rigidBody;

        private float step = 0.0f;

        private float sign = -1.0f;

        protected void OnStart()
        {
            rigidBody = GetComponent<RigidBody2DComponent>();
            rigidBody.AngularVelocity = Magnetar.Core.Math.ToRadians(45.0f);
            GetEntityByName("Player").As<Player>().RunMessage();
            CreateEntity<Bullet>();
        }

        protected void OnUpdate(float dt)
        {
            step += dt;
            if(step >= 1.0)
            {
                rigidBody.AngularVelocity = sign * Magnetar.Core.Math.ToRadians(45.0f);
                step = 0.0f;
                sign *= -1.0f;
            }
        }
    }
}