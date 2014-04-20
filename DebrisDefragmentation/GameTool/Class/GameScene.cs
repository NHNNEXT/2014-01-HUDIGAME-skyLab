using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace GameTool.Class
{
    class GameScene : GameObject
    {
        DDWrapper.GameObject m_Scene = new DDWrapper.GameObject();

        public override void AttachParent(GameTool.Class.GameObject parent)
        {
            parent.Unwrapping().AddChild(m_Scene);
        }

        public override void AddChild(GameTool.Class.GameObject child)
        {
            m_Scene.AddChild(child.Unwrapping());
        }

        public override DDWrapper.GameObject Unwrapping()
        {
            return m_Scene;
        }

        public void Render()
        {
            m_Scene.Render();
        }

        public void IncreaseRotationX(float dx)
        {
            m_Scene.IncreaseRotationX(dx);
        }

        public void IncreaseRotationY(float dy)
        {
            m_Scene.IncreaseRotationY(dy);
        }

        public void IncreaseRotationZ(float dz)
        {
            m_Scene.IncreaseRotationX(dz);
        }
    }
}
