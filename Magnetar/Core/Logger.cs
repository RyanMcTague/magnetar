
namespace Magnetar.Core
{
    public static class Logger
    {
        public static void Fatal(string message)
        {
            InternalCalls.Log(LogLevel.Fatal, message);
        }

        public static void Error(string message)
        {
            InternalCalls.Log(LogLevel.Error, message);
        }

        public static void Warn(string message)
        {
            InternalCalls.Log(LogLevel.Warn, message);
        }

        public static void Info(string message)
        {
            InternalCalls.Log(LogLevel.Info, message);
        }

        public static void Debug(string message)
        {
            InternalCalls.Log(LogLevel.Debug, message);
        }

        public static void Trace(string message)
        {
            InternalCalls.Log(LogLevel.Trace, message);
        }

        public static void Log(LogLevel level, string message)
        {
            InternalCalls.Log(level, message);
        }
    }
}