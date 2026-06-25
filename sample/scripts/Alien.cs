
using Magnetar.Core;

namespace Sample
{
    class Alien : Entity
    {
        private static float direction = 1.0f;
        private static float countTarget = 1f;
        public static float Width { get => 10f; }
        public static float Height { get => 10f; }

        float count =0;

        void OnStart()
        {
            Tag = "alien";

            SpriteRendererComponent sr = AddComponent<SpriteRendererComponent>();
            sr.Size = new Vector2D(10f, 10f);
            sr.Color = Vector4D.FromHexRGBA(0x932aa3ff);

            BoxColliderComponent collider = AddComponent<BoxColliderComponent>();
            collider.Size = sr.Size;
        }

        void OnUpdate(float dt)
        {
            count += dt;
            if(count > countTarget)
            {
                count = 0f;
                float x = Position.x;
                float xMovement = 4f;
                float newX = x + direction * xMovement;
                float y = Position.y;
                if((newX + Width) > Game.ResolutionX)
                {
                    direction *= -1f;
                    newX = x + direction * xMovement;
                    countTarget -= 0.1f;
                    y -= Height;
                }
                else if((newX - 5f) < 0f)
                {
                    direction *= -1f;
                    newX = x + direction * xMovement;
                    countTarget -= 0.1f;
                    y -= Height;
                }
               
                Position = new Vector3D(newX, y, Position.z);
            }
        }
    }
}