using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace GameTool.Class
{
    abstract class GameObject
    {
        public abstract void AttachParent(ref GameTool.Class.GameObject parent);
        public abstract void AddChild(ref GameTool.Class.GameObject child);
        public abstract DDWrapper.GameObject Unwrapping();
    }
}
