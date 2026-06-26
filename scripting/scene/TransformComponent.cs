namespace Magnetar.Core
{
    public class TransformComponent : Component
    {
        public Vector3D Position
        {
            get
            {
                InternalCalls.TransformComponent_GetPosition(Entity.ID, out Vector3D position);
                return position;
            }
            set
            {
                InternalCalls.TransformComponent_SetPosition(Entity.ID, ref value);
            }
        }

        public Vector3D Rotation
        {
            get
            {
                InternalCalls.TransformComponent_GetRotation(Entity.ID, out Vector3D rotation);
                return rotation;
            }
            set
            {
                InternalCalls.TransformComponent_SetRotation(Entity.ID, ref value);
            }
        }

        public Vector3D Scale
        {
            get
            {
                InternalCalls.TransformComponent_GetScale(Entity.ID, out Vector3D scale);
                return scale;
            }
            set
            {
                InternalCalls.TransformComponent_SetScale(Entity.ID, ref value);
            }
        }
    }
}