using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace GameTool.Class
{
    class PlayerPhysics
    {
        private DDWrapper.GamePhysics m_Physics = new DDWrapper.GamePhysics();

        // return false == 가속 끝
        public bool AccelPlayer(DDWrapper.GameModel m_Model, float velocityX, float velocityY, float velocityZ, float accelX, float accelY, float accelZ, float dt)
        {
            return m_Physics.AccelObject(m_Model, velocityX, velocityY, velocityZ, accelX, accelY, accelZ, dt);
        }
    }
}
