using Magnetar.Core;

namespace Sample
{
    class GameController : Entity
    {
        public float Spacing { get; internal set; }

        void OnStart()
        {
            int aliensPerRow = 10;
            int alienRowCount = 3;

            float startY = Game.ResolutionY - 3 * aliensPerRow;

            Spacing = (Game.ResolutionX - aliensPerRow * Alien.Width) / (aliensPerRow + 1);

            float y = startY;

            for (int j = 0; j < alienRowCount; j++)
            {
                float x = Spacing;
                for (int i = 0; i < aliensPerRow; i++)
                {
                    Alien alien = CreateEntity<Alien>();
                    alien.Tag = "alien" + i.ToString() + "-" + j.ToString();
                    alien.Position = new Vector3D(x, y, 0f);
                    x += Alien.Width + Spacing;
                }
                y -= Alien.Height + Spacing;
            }

            CreateEntity<Player>();
        }
    }
}