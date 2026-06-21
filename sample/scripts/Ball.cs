using Magnetar.Core;

namespace Sample
{
    public class Ball : Entity
    {
        protected void OnStart()
        {
            SpriteRendererComponent sr = AddComponent<SpriteRendererComponent>();
            sr.Size = new Vector2D(2f, 2f);
            sr.Color = Vector4D.FromRGBA(255, 255, 255);

            RigidBody2DComponent rb = AddComponent<RigidBody2DComponent>();
            rb.Velocity = new Vector2D(0f, 10f);

            BoxColliderComponent collider = AddComponent<BoxColliderComponent>();
            collider.Position = new Vector2D(0f, 0f);
            collider.Size = sr.Size;
        }
    }
}