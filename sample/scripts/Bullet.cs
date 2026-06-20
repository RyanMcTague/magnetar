using Magnetar.Core;

namespace Sample
{
    public class Bullet: Entity
    {
        protected void OnStart()
        {
            Logger.Debug("Created bullet!");
        }
    }
}