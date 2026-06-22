using Magnetar.Core;

namespace Sample
{
    public class Block : Entity
    {
        public static int BlocksPerRow { get => 20; }

        public static float Width
        {
            get => Game.ResolutionX / BlocksPerRow;
        }

        protected void OnStart()
        {
            SpriteRendererComponent sr = AddComponent<SpriteRendererComponent>();
            sr.Size = new Vector2D(Width, 5.0f);
            sr.Color = Vector4D.FromRGBA(0, 0, 255);
            Position = new Vector3D(Position.x, 10.0f, Position.z);

            BoxColliderComponent collider = AddComponent<BoxColliderComponent>();
            collider.Position = new Vector2D(0f, 0f);
            collider.Size = sr.Size;
        }

        protected void OnCollision(Entity entity)
        {
            Ball ball = entity.As<Ball>();
            ball.ReverseMovement();
        }
    }
}