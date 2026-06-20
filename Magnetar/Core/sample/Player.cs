
namespace Magnetar.Core
{
    public class Player: Entity
    {
        protected void OnStart()
        {
        }

        protected void OnUpdate(float dt)
        {
        }

        public void RunMessage()
        {
            Logger.Info($"Player {ID} got called for a message");
        }
    }
}