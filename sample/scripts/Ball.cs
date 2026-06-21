using Magnetar.Core;

namespace Sample
{
    public class Ball : Entity
    {

        RigidBody2DComponent rb;

        protected void OnStart()
        {
            SpriteRendererComponent sr = AddComponent<SpriteRendererComponent>();
            sr.Size = new Vector2D(2f, 2f);
            sr.Color = Vector4D.FromRGBA(255, 255, 255);

            rb = AddComponent<RigidBody2DComponent>();
        }
    }
}