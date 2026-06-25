
using Magnetar.Core;

namespace Sample
{
    class Score: Entity
    {
        TextRendererComponent textRenderer;

        private int score = 0;

        void OnStart()
        {
            Tag = "score";
            textRenderer = AddComponent<TextRendererComponent>();
            textRenderer.Color = Vector4D.FromHexRGBA(0xffffffff);
            textRenderer.Font = 1009;
            textRenderer.Value = $"Score: {score}";
            Position = new Vector3D(100, 750 , Position.z);
        }

        public void AddScore()
        {
            score += 1;
            textRenderer.Value = $"Score: {score}";
        }
    }
}