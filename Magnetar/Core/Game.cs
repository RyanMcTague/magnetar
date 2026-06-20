namespace Magnetar.Core
{
    public static class Game
    {
        public static int ResolutionX
        {
            get => InternalCalls.Game_GetResolutionX();
        }

        public static int ResolutionY
        {
            get => InternalCalls.Game_GetResolutionY();
        }
    }
}