
using Magnetar.Core;

namespace Sample
{
    class Bullet : Entity
    {
        void OnStart()
        {
            Player player = GetEntityByName("player").As<Player>();
            Position = new Vector3D(player.Position.x + 5f, player.Position.y + 10f, 0f);

            SpriteRendererComponent sr = AddComponent<SpriteRendererComponent>();
            sr.Size = new Vector2D(2f, 4f);
            sr.Color = Vector4D.FromHexRGBA(0xff0000ff);

            RigidBody2DComponent rb = AddComponent<RigidBody2DComponent>();
            rb.Velocity = new Vector2D(0f, 80f);

            BoxColliderComponent collider = AddComponent<BoxColliderComponent>();
            collider.Size = sr.Size;
        }

        void OnCollision(Entity entity)
        {
            entity.Destroy();
            Destroy();
        }
    }
}