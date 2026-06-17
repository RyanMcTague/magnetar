
namespace Magnetar.Core
{
    public class Player: ScriptableEntity
    {
        void OnStart()
        {
            Logger.Debug($"Created Entity {Handle}");
        }

        void OnUpdate(float dt)
        {
        }
    }
}