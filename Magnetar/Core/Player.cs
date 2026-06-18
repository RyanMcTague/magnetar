
namespace Magnetar.Core
{
    public class Player: ScriptableEntity
    {
        protected void OnStart()
        {
            Logger.Debug($"Created Entity {Handle}");
        }

        protected void OnUpdate(float dt)
        {
        }
    }
}