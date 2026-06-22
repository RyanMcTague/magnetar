using Magnetar.Core;

namespace Sample
{
    public class Ball : Entity
    {
        RigidBody2DComponent rb;

        protected void OnStart()
        {
            Tag = "Ball";

            Position = new Vector3D(Game.ResolutionX / 2f, Game.ResolutionY / 2f, Position.z);

            SpriteRendererComponent sr = AddComponent<SpriteRendererComponent>();
            sr.Size = new Vector2D(2f, 2f);
            sr.Color = Vector4D.FromRGBA(255, 255, 255);

            rb = AddComponent<RigidBody2DComponent>();
            rb.Velocity = new Vector2D(45f, 80f);

            BoxColliderComponent collider = AddComponent<BoxColliderComponent>();
            collider.Position = new Vector2D(0f, 0f);
            collider.Size = sr.Size;
        }

        public void OnCollision(Entity entity)
        {
            switch (entity.Tag)
            {
                case "BorderTop":
                    rb.Velocity = new Vector2D(rb.Velocity.x, -1f * rb.Velocity.y);
                    break;
                case "BorderBottom":
                    rb.Velocity = new Vector2D(rb.Velocity.x, -1f * rb.Velocity.y);
                    break;
                case "BorderLeft":
                    rb.Velocity = new Vector2D(-1f * rb.Velocity.x, rb.Velocity.y);
                    break;
                case "BorderRight":
                    rb.Velocity = new Vector2D(-1f * rb.Velocity.x, rb.Velocity.y);
                    break;
                case "Paddle":
                    rb.Velocity = new Vector2D(rb.Velocity.x, -1f * rb.Velocity.y);
                    break;
                default:
                    break;
            }
        }
    }
}