using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace GameTool.Class
{
    class GameModel : GameObject
    {
        private DDWrapper.GameModel m_Model = null;

        public GameModel(string path)
        {
            m_Model = new DDWrapper.GameModel(path);
        }

        public override void AttachParent(ref GameTool.Class.GameObject parent)
        {
            throw new NotImplementedException();
        }

        public override void AddChild(ref GameTool.Class.GameObject child)
        {
            throw new NotImplementedException();
        }

        public override DDWrapper.GameObject Unwrapping()
        {
            return m_Model;
        }

        public void SetScale(float scale)
        {
            m_Model.SetScale(scale);
        }

        public void SetPosition( float x, float y, float z )
        {
            m_Model.SetPosition(x, y, z);
        }
    }
}
