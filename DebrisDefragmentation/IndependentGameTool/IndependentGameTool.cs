using System;
using System.IO;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Windows.Forms;
using System.Threading.Tasks;

namespace GameTool
{
    public partial class IndependentGameTool : Form
    {
        Class.Renderer m_Renderer = null;

        public IndependentGameTool()
        {
            InitializeComponent();
        }

        private void ISSRenderStart(object sender, EventArgs e)
        {
            m_Renderer = new Class.Renderer();
            m_Renderer.CreateDevice(this.ObjectViewPP);
            Render();
        }

        private async void Render()
        {
            m_Renderer.Render();
            await Task.Delay(16);
        }
    }
}
