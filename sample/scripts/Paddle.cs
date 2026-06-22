using Magnetar.Core;

namespace Sample
{
    public class Paddle : Entity
    {
        readonly float movementSpeed = 100.0f;

        RigidBody2DComponent rb;
        SpriteRendererComponent sr;

        public bool IsMovingLeft { get => rb.Velocity.x < 0f; }
        public bool IsMovingRight { get => rb.Velocity.x > 0f; }

        protected void OnStart()
        {
            Tag = "Paddle";

            sr = AddComponent<SpriteRendererComponent>();
            sr.Size = new Vector2D(25.0f, 5.0f);
            sr.Color = Vector4D.FromRGBA(255, 255, 255);

            Position = new Vector3D(Game.ResolutionX / 2f, sr.Size.y, Position.z);

            rb = AddComponent<RigidBody2DComponent>();

            BoxColliderComponent collider = AddComponent<BoxColliderComponent>();
            collider.Position = new Vector2D(0f, 0f);
            collider.Size = sr.Size;
        }

        protected void OnUpdate(float dt)
        {
            float left = Input.IsActionDown(Action.Left) ? 1f : 0;
            float right = Input.IsActionDown(Action.Right) ? 1f : 0;
            float speed = (right - left) * movementSpeed;
            rb.Velocity = new Vector2D(speed, 0.0f);
        }
    }
}