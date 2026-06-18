
namespace Magnetar.Core
{
    public abstract class ScriptableEntity
    {
        public uint Handle { get; internal set; }

        // protected T GetComponent<T>()
        // {
        //     return InternalCalls.GetComponent<T>(Handle);
        // }

        protected bool HasComponent<T>()
        {
            return InternalCalls.HasComponent(Handle, typeof(T));
        }
    }
}

