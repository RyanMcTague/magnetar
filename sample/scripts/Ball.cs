using Magnetar.Core;

namespace Sample
{
    public class Ball : Entity
    {
        RigidBody2DComponent rb;

        protected void OnStart()
        {
            Tag = "Ball";

            SpriteRendererComponent sr = AddComponent<SpriteRendererComponent>();
            sr.Size = new Vector2D(2f, 2f);
            sr.Color = Vector4D.FromRGBA(255, 255, 255);

            rb = AddComponent<RigidBody2DComponent>();
            rb.Velocity = new Vector2D(0f, 80f);

            BoxColliderComponent collider = AddComponent<BoxColliderComponent>();
            collider.Position = new Vector2D(0f, 0f);
            collider.Size = sr.Size;
        }

        public void ReverseMovement()
        {
            rb.Velocity = new Vector2D(0f, -1f * rb.Velocity.y);
        }
    }
}