using System.Runtime.CompilerServices;

namespace Magnetar
{
    class ScriptableEntity
    {
        // [MethodImpl(MethodImplOptions.InternalCall)]
        // extern static int update();

        static string GetMessage()
        {
            update();
            return "Hello World";
        }
    }
}