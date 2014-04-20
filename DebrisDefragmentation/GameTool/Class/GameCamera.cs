using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace GameTool.Class
{
    class GameCamera : GameObject
    {
        // 생성자
        public GameCamera()
        {
            m_Camera = new DDWrapper.GameCamera();
        }

        public override void AttachParent(GameTool.Class.GameObject parent)
        {
            parent.Unwrapping().AddChild(m_Camera);
        }

        public override void AddChild(GameTool.Class.GameObject child)
        { 
            m_Camera.AddChild(child.Unwrapping());
        }

        public override DDWrapper.GameObject Unwrapping()
        {
            return m_Camera;
        }

        public void MoveCamera(float x, float y, float z)
        {
            m_Camera.SetPosition(
                     m_Camera.GetPositionX() + x,
                     m_Camera.GetPositionY() + y,
                     m_Camera.GetPositionZ() + z
                 );
        }

        public void ResetCamera()
        {
            m_Camera.SetPosition(0, 1, -5);
        }

        public float GetPositionX()
        {
            return m_Camera.GetPositionX();
        }

        public float GetPositionY()
        {
            return m_Camera.GetPositionY();
        }

        public float GetPositionZ()
        {
            return m_Camera.GetPositionZ();
        }

        public float GetViewDirectionX()
        {
            return m_Camera.GetViewDirectionX();
        }

        public float GetViewDirectionY()
        {
            return m_Camera.GetViewDirectionY();
        }

        public float GetViewDirectionZ()
        {
            return m_Camera.GetViewDirectionZ();
        }

        // 멤버변수
        private DDWrapper.GameCamera m_Camera = null;
    }
}
