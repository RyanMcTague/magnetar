
namespace Magnetar.Core
{
    public class Entity
    {
        public uint ID { get; internal set; }

        public Entity() { ID = 0; }

        internal Entity(uint id) { ID = id; }

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

        public string Tag
        {
            get
            {
                return GetComponent<TagComponent>().Value;
            }
            set
            {
                GetComponent<TagComponent>().Value = value;
            }
        }

        public static Entity GetEntityByName(string name)
        {
            uint id = InternalCalls.Entity_GetByName(name, out int wasFound);
            if (wasFound < 0)
                return null;

            return new Entity(id);
        }

        public bool HasComponent<T>() where T : Component, new()
        {
            return InternalCalls.Entity_HasComponent(ID, typeof(T));
        }

        public T AddComponent<T>() where T : Component, new()
        {
            InternalCalls.Entity_AddComponent(ID, typeof(T));
            return GetComponent<T>();
        }

        public T GetComponent<T>() where T : Component, new()
        {
            if (!HasComponent<T>())
                return null;
            T component = new T() { Entity = this };
            return component;
        }

        public void RemoveComponent<T>() where T : Component
        {
            InternalCalls.Entity_RemoveComponent(ID, typeof(T));
        }

        public T As<T>() where T : Entity, new()
        {
            object instance = InternalCalls.Entity_GetScriptInstance(ID);
            return instance as T;
        }

        public void Destroy()
        {
            InternalCalls.Entity_Destroy(ID);
        }

        public static T CreateEntity<T>() where T : Entity, new()
        {
            object instance = InternalCalls.Entity_CreateEntity(typeof(T));
            return instance as T;
        }
    }
}

