using Magnetar.Core;

namespace Sample
{
    public class Block : Entity
    {
        protected void OnStart()
        {
            Tag = "Ball";

            Position = new Vector3D(Game.ResolutionX / 2f, Game.ResolutionY / 2f, Position.z);

            SpriteRendererComponent sr = AddComponent<SpriteRendererComponent>();
            sr.Size = new Vector2D(10f, 10f);
            sr.Color = Vector4D.FromRGBA(255, 255, 255);

            BoxColliderComponent collider = AddComponent<BoxColliderComponent>();
            collider.Position = new Vector2D(0f, 0f);
            collider.Size = sr.Size;
        }
    }
}