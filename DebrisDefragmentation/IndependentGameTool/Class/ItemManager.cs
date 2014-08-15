using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using GameTool.GameEnvironment;

namespace GameTool.Class
{
    class ItemManager
    {
        public void AddItemPropertiesTo(ComboBox box)
        {
            foreach (var properties in Enum.GetValues(typeof(JSONEnvironment.JsonItemProperty)) )
            {
                box.Items.Add(properties);
            }
        }
    }
}
