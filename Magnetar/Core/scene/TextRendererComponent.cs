namespace Magnetar.Core
{
    public class TextRendererComponent: Component
    {
        public string Value
        {
            get
            {
                InternalCalls.TextRenderer_GetValue(Entity.ID, out string str);
                return str;
            }
            set
            {
                InternalCalls.TextRenderer_SetValue(Entity.ID, ref value);
            }
        }

        public Vector4D Color
        {
            get
            {
                InternalCalls.TextRenderer_GetColor(Entity.ID, out Vector4D color);
                return color;
            }
            set
            {
                InternalCalls.TextRenderer_SetColor(Entity.ID, ref value);
            }
        }

        public uint Font
        {
            get
            {
                InternalCalls.TextRenderer_GetFont(Entity.ID, out uint color);
                return color;
            }
            set
            {
                InternalCalls.TextRenderer_SetFont(Entity.ID, ref value);
            }
        }
    }
}