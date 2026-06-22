
namespace Magnetar.Core
{
    public struct Vector4D
    {
        public float x;
        public float y;
        public float z;
        public float w;

        public Vector4D(float x, float y, float z, float w)
        {
            this.x = x;
            this.y = y;
            this.z = z;
            this.w = w;
        }

        public static Vector4D FromRGBA(byte r, byte g, byte b, byte a = 255)
        {
            return new Vector4D(
                a / 255.0f,
                g / 255.0f,
                b / 255.0f,
                a / 255.0f
            );
        }

        public static Vector4D FromHexRGBA(uint rgba)
        {
            byte r = (byte)((rgba & 0xff000000) >> 24);
            byte g = (byte)((rgba & 0x00ff0000) >> 16);
            byte b = (byte)((rgba & 0x0000ff00) >> 8);
            byte a = (byte)((rgba & 0x000000ff) >> 0);
            return new Vector4D(
                r / 255.0f,
                g / 255.0f,
                b / 255.0f,
                a / 255.0f
            );
        }
    }
}