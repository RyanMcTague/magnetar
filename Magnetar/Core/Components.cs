
namespace Magnetar.Core
{
    public abstract class Component
    {

    }

    public class TransformComponent : Component
    {
        public Vector3D position;
        public Vector3D rotation;
        public Vector3D scale;
    }
}