
using Magnetar.Core;

namespace Sample
{
    public class GameController: Entity
    {
        protected void OnStart()
        {
            CreateEntity<Paddle>();
            CreateEntity<Ball>();
            CreateEntity<Block>();
        }
    }
}