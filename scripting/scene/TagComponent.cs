namespace Magnetar.Core
{
    public class TagComponent : Component
    {
        public string Value
        {
            get
            {
                InternalCalls.Tag_GetValue(Entity.ID, out string value);
                return value;
            }
            set
            {
                InternalCalls.Tag_SetValue(Entity.ID, ref value);
            }
        }
    }
}