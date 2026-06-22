namespace Magnetar.Core
{
    public static class Math
    {
        public const float PI = 3.1415926535898f;

        private const float RADIANS_CONVERSION = PI / 180.0f;
        private const float DEGRESS_CONVERSION = 180.0f / PI;

        public static float ToRadians(float degrees)
        {
            return degrees * RADIANS_CONVERSION;
        }

        public static float ToDegrees(float degrees)
        {
            return degrees * DEGRESS_CONVERSION;
        }

        public static int Random(int min, int max)
        {
            return InternalCalls.Math_Random(min, max);
        }
    }    
}