namespace Magnetar.Core
{
    public class SpriteRendererComponent : Component
    {
        public Vector2D Size
        {
            get
            {
                InternalCalls.SpriteRenderer_GetSize(Entity.ID, out Vector2D size);
                return size;
            }
            set
            {
                InternalCalls.SpriteRenderer_SetSize(Entity.ID, ref value);
            }
        }
        public Vector4D Color
        {
            get
            {
                InternalCalls.SpriteRenderer_GetColor(Entity.ID, out Vector4D color);
                return color;
            }
            set
            {
                InternalCalls.SpriteRenderer_SetColor(Entity.ID, ref value);
            }
        }

        public uint Texture
        {
            get
            {
                InternalCalls.SpriteRenderer_GetTexture(Entity.ID, out uint color);
                return color;
            }
            set
            {
                InternalCalls.SpriteRenderer_SetTexture(Entity.ID, ref value);
            }
        }
    }
}