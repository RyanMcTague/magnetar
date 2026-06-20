using Magnetar.Core;

namespace Sample
{
    public class Bullet: Entity
    {
        protected void OnStart()
        {
            Tag = "Bullet-" + ID.ToString();
            Logger.Debug($"Created bullet {Tag}");
        }
    }
}