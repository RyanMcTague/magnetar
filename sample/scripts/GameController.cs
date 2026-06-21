
using Magnetar.Core;

namespace Sample
{
    public class GameController: Entity
    {
        protected void OnStart()
        {
            Logger.SetLevel(LogLevel.Trace);
            CreateEntity<Paddle>();
            CreateEntity<Ball>();
            CreateEntity<Block>();
        }
    }
}