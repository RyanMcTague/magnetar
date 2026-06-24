
using Magnetar.Core;

namespace Sample
{
    class Player: Entity
    {
        private readonly float speed = 50f;

        RigidBody2DComponent rb;

        void OnStart()
        {
            Tag = "player";

            SpriteRendererComponent sr = AddComponent<SpriteRendererComponent>();
            sr.Size = new Vector2D(10f, 10f);
            sr.Color = Vector4D.FromHexRGBA(0xffffffff);
            Position = new Vector3D(Game.ResolutionX / 2f - 5f, 5f, 0);

            rb = AddComponent<RigidBody2DComponent>();
            rb.Velocity = new Vector2D(0f, 0f);
        }

        void OnUpdate(float dt)
        {
            float leftMovement = Input.IsActionDown(Action.Left) ? 1f : 0f;
            float rightMovement = Input.IsActionDown(Action.Right) ? 1f : 0f;
        
            rb.Velocity = new Vector2D((rightMovement - leftMovement) * speed, 0f);

            if(Input.IsActionPressed(Action.Fire))
                CreateEntity<Bullet>();
        }
    }
}