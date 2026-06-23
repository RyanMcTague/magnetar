
using Magnetar.Core;

namespace Sample
{
    class Alien : Entity
    {
        public static float Width { get => 10f; }
        public static float Height { get => 10f; }

        float counter = 0f;

        void OnStart()
        {
            SpriteRendererComponent sr = AddComponent<SpriteRendererComponent>();
            sr.Size = new Vector2D(10f, 10f);
            sr.Color = Vector4D.FromHexRGBA(0x932aa3ff);
        }

        void OnUpdate(float dt)
        {
            counter += dt;

            if(dt >= 5f)
            {
                counter = 0f;
                Logger.Debug("Step");
            }            
        }
    }
}