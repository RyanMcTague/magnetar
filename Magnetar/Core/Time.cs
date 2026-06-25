
namespace Magnetar.Core
{
    public class Time
    {
        public static float Now
        {
            get
            {
                return InternalCalls.Time_GetTime();
            }
        }
    }
}