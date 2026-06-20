
namespace Magnetar.Core
{
    public static class Input
    {
        public static ActionState GetActionState(uint code)
        {
            return InternalCalls.Input_GetActionState(code);
        }

        public static bool IsActionPressed(uint code)
        {
            return GetActionState(code) == ActionState.PRESSED;
        }

        public static bool IsActionDown(uint code)
        {
            return GetActionState(code) == ActionState.DOWN;
        }

        public static bool IsActionReleased(uint code)
        {
            return GetActionState(code) == ActionState.RELEASED;
        }

        public static bool IsActionUp(uint code)
        {
            return GetActionState(code) == ActionState.UP;
        }
    }
}