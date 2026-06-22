
using Magnetar.Core;

namespace Sample
{
    public class GameController: Entity
    {

        public readonly float BorderSize = 2.5f;
        
        protected void OnStart()
        {
            CreateEntity<Paddle>();
            CreateEntity<Block>();
            CreateEntity<Ball>();
            CreateBorders();
        }

        void CreateBorders()
        {

            SpriteRendererComponent sr;
            BoxColliderComponent bc;
            Entity left = CreateEntity<Entity>();
            left.Tag = "BorderLeft";
         
            sr = left.AddComponent<SpriteRendererComponent>();
            sr.Size = new Vector2D(BorderSize, Game.ResolutionY);
            sr.Color = Vector4D.FromRGBA(255, 255, 255);
            
            bc = left.AddComponent<BoxColliderComponent>();
            bc.Position = new Vector2D(0f, 0f);
            bc.Size = sr.Size;

            left.Position = new Vector3D(0, 0, left.Position.z);

            Entity right = CreateEntity<Entity>();
            right.Tag = "BorderRight";
         
            sr = right.AddComponent<SpriteRendererComponent>();
            sr.Size = new Vector2D(BorderSize, Game.ResolutionY);
            sr.Color = Vector4D.FromRGBA(255, 255, 255);

            bc = right.AddComponent<BoxColliderComponent>();
            bc.Position = new Vector2D(0f, 0f);
            bc.Size = sr.Size;

            right.Position = new Vector3D(Game.ResolutionX - BorderSize, 0, right.Position.z);

            Entity bottom = CreateEntity<Entity>();
            bottom.Tag = "BorderBottom";
         
            sr = bottom.AddComponent<SpriteRendererComponent>();
            sr.Size = new Vector2D(Game.ResolutionX, BorderSize);
            sr.Color = Vector4D.FromRGBA(255, 0, 0);

            bc = bottom.AddComponent<BoxColliderComponent>();
            bc.Position = new Vector2D(0f, 0f);
            bc.Size = sr.Size;

            bottom.Position = new Vector3D(0, 0, bottom.Position.z);

            Entity top = CreateEntity<Entity>();
            top.Tag = "BorderTop";
            
            sr = top.AddComponent<SpriteRendererComponent>();
            sr.Size = new Vector2D(Game.ResolutionX, BorderSize);
            sr.Color = Vector4D.FromRGBA(255, 255, 255);

            bc = top.AddComponent<BoxColliderComponent>();
            bc.Position = new Vector2D(0f, 0f);
            bc.Size = sr.Size;

            top.Position = new Vector3D(0, Game.ResolutionY - BorderSize, top.Position.z);
        }
    }
}