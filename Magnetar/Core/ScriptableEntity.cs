
namespace Magnetar.Core
{
    public abstract class ScriptableEntity
    {
        public uint Handle { get; internal set; }

        protected bool HasComponent<T>()
        {
            return InternalCalls.HasComponent(Handle, typeof(T));
        }

        protected T GetComponent<T>() where T : new()
        {
            return InternalCalls.GetComponent<T>(Handle);
        }
    }
}

