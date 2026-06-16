using System.Runtime.CompilerServices;

namespace Magnetar.Core
{
    internal static class InternalCalls
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        internal static extern void Log(string message);

    }
}