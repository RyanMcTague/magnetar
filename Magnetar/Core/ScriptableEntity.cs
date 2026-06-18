
namespace Magnetar.Core
{
    public abstract class ScriptableEntity
    {
        public uint ID { get; internal set; }

        public TransformComponent Transform
        {
            get
            {
                return GetComponent<TransformComponent>();
            }
        }

        protected bool HasComponent<T>() where T : Component, new()
        {
            return InternalCalls.Entity_HasComponent(ID, typeof(T));
        }

        protected T GetComponent<T>() where T : Component, new()
        {
            if(!HasComponent<T>())
                return null;
            T component = new T() { Entity = this };
            return component;
        }
    }
}

