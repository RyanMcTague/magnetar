
namespace Magnetar.Core
{
    public abstract class ScriptableEntity
    {
        public uint ID { get; internal set; }

        public Vector3D Position
        {
            get
            {
                return GetComponent<TransformComponent>().Position;
            }
            set
            {
                GetComponent<TransformComponent>().Position = value;
            }
        }

        public Vector3D Rotation
        {
            get
            {
                return GetComponent<TransformComponent>().Rotation;
            }
            set
            {
                GetComponent<TransformComponent>().Rotation = value;
            }
        }

        public Vector3D Scale
        {
            get
            {
                return GetComponent<TransformComponent>().Scale;
            }
            set
            {
                GetComponent<TransformComponent>().Scale = value;
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

