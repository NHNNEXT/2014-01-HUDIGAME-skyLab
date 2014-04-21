using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace GameTool.Class
{
    class GamePlayer : GameObject
    {
        private DDWrapper.GameModel m_Model = null;
        // 지금이야 툴에서 물리가 하나뿐이지만 나중에는 따로 뺴야 한다
        private GameTool.Class.PlayerPhysics m_PlayerPhysics = new PlayerPhysics();

        float velocityX = 0.0f;
        float velocityY = 0.0f;
        float velocityZ = 0.0f;

        float accelX = 0.0f;
        float accelY = 0.0f;
        float accelZ = 0.0f;

        float m_StartTime = 0.0f;
        float m_TimeStack = 0.0f;

        bool m_IsAccelation = false;

        public GamePlayer()
        {
            m_Model = new DDWrapper.GameModel();
        }

        public GamePlayer(string path)
        {
            m_Model = new DDWrapper.GameModel(path);
        }

        public override void AttachParent(ref GameTool.Class.GameObject parent)
        {
            parent.Unwrapping().AddChild(m_Model);
        }

        public override void AddChild(ref GameTool.Class.GameObject child)
        {
            m_Model.AddChild(child.Unwrapping());
        }

        public override DDWrapper.GameObject Unwrapping()
        {
            return m_Model;
        }

        // return false == 가속 종료
        public bool MovePlayer(float dt, bool IsAccelKeyInput)
        {
            UpdateTimer(dt);

            if (IsAccelKeyInput)
            {
                Acceleration();
                UpdateVelocity(dt);
            }

            if (!m_PlayerPhysics.AccelPlayer(m_Model, velocityX, velocityY, velocityZ, accelX, accelY, accelZ, dt))
            {
                StopAccelPlayer();
                // 가속 종료
                return false;
            }

            return true;
        }

        public void StopPlayer()
        {
            StopAccelPlayer();
            velocityX = 0;
            velocityY = 0;
            velocityZ = 0;
        }

        private void StopAccelPlayer()
        {
            accelX = 0;
            accelY = 0;
            accelZ = 0;
        }

        private void Acceleration()
        {
            accelX = m_Model.GetViewDirectionX() * 50;
            accelY = m_Model.GetViewDirectionY() * 50;
            accelZ = m_Model.GetViewDirectionZ() * 50;
        }

        private void UpdateVelocity(float dt)
        {
            velocityX += accelX * dt;
            velocityY += accelY * dt;
            velocityZ += accelZ * dt;
        }

        public double GetAccelation()
        {
            return Math.Pow((accelX * accelX + accelY * accelY + accelZ * accelZ), 0.5);
        }

        public double GetSpeed()
        {
            return Math.Pow((velocityX * velocityX + velocityY * velocityY + velocityZ * velocityZ), 0.5);
        }

        public float GetAccelX()
        {
            return accelX;
        }

        public float GetAccelY()
        {
            return accelY;
        }

        public float GetAccelZ()
        {
            return accelZ;
        }

        public float GetSpeedX()
        {
            return velocityX;
        }

        public float GetSpeedY()
        {
            return velocityY;
        }

        public float GetSpeedZ()
        {
            return velocityZ;
        }

        public float GetPositionX()
        {
            return m_Model.GetPositionX();
        }

        public float GetPositionY()
        {
            return m_Model.GetPositionY();
        }

        public float GetPositionZ()
        {
            return m_Model.GetPositionZ();
        }

        public void SetPosition(float x, float y, float z)
        {
            m_Model.SetPosition(x, y, z);
        }

        private void UpdateTimer(float dt)
        {
            // 가속 중이라면 타이머에 시간을 누적한다
            if (m_IsAccelation)
            {
                m_TimeStack += dt;
            }
        }

        // 혹시 먼 훗날 연속 가속이 문제가 될 때 방어코드로 쓸 수도 있음
//         private bool IsTimeEnded()
//         {
//             // 0.5초 지나면 가속 끝!
//             if (m_TimeStack > 500.0f)
//             {
//                 m_IsAccelation = false;
//                 m_TimeStack = 0;
//                 return true;
//             }
// 
//             return false;
//         }
    }
}
