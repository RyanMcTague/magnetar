using System;
using System.Runtime.CompilerServices;

namespace Magnetar.Core
{
    internal static class InternalCalls
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern T GetComponent<T>(uint id);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern bool HasComponent(uint id, Type type);
        
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Log(LogLevel level, string message);
    }
}