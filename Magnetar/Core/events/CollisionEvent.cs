
namespace Magnetar.Core
{
    public class CollisionEvent : Event
    {
        public Entity Entity { get; }

        public CollisionEvent(Entity entity) { Entity = entity; }
    }
}