using System.Runtime.CompilerServices;

namespace Magnetar.Core
{
    public abstract class ScriptableEntity
    {
        // [MethodImpl(MethodImplOptions.InternalCall)]
        // extern static int update();

        public ulong ID { get; internal set; }

        protected T GetComponent<T>()
        {
        }
    }
}