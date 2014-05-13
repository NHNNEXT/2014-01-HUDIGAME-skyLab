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
        Class.Renderer m_Renderer = new Class.Renderer();

        public IndependentGameTool()
        {
            InitializeComponent();
        }

        private void ISSRenderStart(object sender, EventArgs e)
        {
            m_Renderer.ClearRenderDevices();
            m_Renderer.CreateDevice(this.ObjectViewPP);
            m_Renderer.CreateDevice(this.ObjectViewX);
            m_Renderer.CreateDevice(this.ObjectViewY);
            m_Renderer.CreateDevice(this.ObjectViewZ);

            Render();
        }

        private async void Render()
        {
            m_Renderer.Render();
            await Task.Delay(16);
        }
    }
}
