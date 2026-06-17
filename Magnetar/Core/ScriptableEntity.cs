
namespace Magnetar.Core
{
    public abstract class ScriptableEntity
    {
        public ulong Handle { get; internal set; }

        // protected T GetComponent<T>()
        // {
        //     return InternalCalls.GetComponent<T>(Handle);
        // }
    }
}

