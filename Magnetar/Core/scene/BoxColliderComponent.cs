namespace Magnetar.Core
{
    public class BoxColliderComponent: Component
    {
        public Vector2D Size
        {
            get
            {
                InternalCalls.BoxCollider_GetSize(Entity.ID, out Vector2D size);
                return size;
            }
            set
            {
                InternalCalls.BoxCollider_SetSize(Entity.ID, ref value);
            }
        }

        public Vector2D Position
        {
            get
            {
                InternalCalls.BoxCollider_GetPosition(Entity.ID, out Vector2D position);
                return position;
            }
            set
            {
                InternalCalls.BoxCollider_SetPosition(Entity.ID, ref value);
            }
        }
    }
}