using Magnetar.Core;

namespace Sample
{
    public class Paddle : Entity
    {
        readonly float movementSpeed = 100.0f;

        RigidBody2DComponent rb;

        protected void OnStart()
        {
            SpriteRendererComponent sr = AddComponent<SpriteRendererComponent>();
            sr.Size = new Vector2D(25.0f, 5.0f);
            sr.Color = Vector4D.FromRGBA(255, 255, 255);

            float bottom = -1.0f * Game.ResolutionY / 2.0f;
            bottom += sr.Size.y;
            Position = new Vector3D(Position.x, bottom, Position.z);

            rb = AddComponent<RigidBody2DComponent>();

            BoxColliderComponent collider = AddComponent<BoxColliderComponent>();
            collider.Size = sr.Size;
            collider.Position = new Vector2D(0f, 0f);
        }

        protected void OnUpdate(float dt)
        {
            float left = Input.IsActionDown(Action.Left) ? 1f : 0;
            float right = Input.IsActionDown(Action.Right) ? 1f : 0;
            float speed = (right - left) * movementSpeed;
            rb.Velocity = new Vector2D(speed, 0.0f);
        }

        protected void OnCollision(Entity entity)
        {
            Ball ball = entity.As<Ball>();
            ball.ReverseMovement();
        }
    }
}