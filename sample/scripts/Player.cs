using Magnetar.Core;

namespace Sample
{
    public class Player : Entity
    {
        RigidBody2DComponent rb;

        protected void OnStart()
        {
            rb = AddComponent<RigidBody2DComponent>();
            rb.Velocity = new Vector2D(0.0f, 10.0f);
        }

        protected void OnUpdate(float dt)
        {
            if (Input.IsActionPressed(Action.Fire))
            {
                RemoveComponent<RigidBody2DComponent>();
            }
        }

        public void RunMessage()
        {
            Logger.Info($"Player {ID} got called for a message");
        }
    }
}