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

            this.ObjectView.MouseWheel += new System.Windows.Forms.MouseEventHandler(ObjectCameraZoomInOut);
        }

        private void ISSRenderStart(object sender, EventArgs e)
        {
            m_Renderer.CreateDevice(this.ObjectView);

            Render();
        }

        private async void Render()
        {
            // 무한 루프
            while(true)
            {
                m_Renderer.Render();
                await Task.Delay(5);
            }
        }

        private void ISSPartRenderClick(object sender, EventArgs e)
        {
            this.Activate();
            this.ObjectView.Focus();
        }

        private void ObjectCameraZoomInOut(object sender, MouseEventArgs e)
        {
            // 아래로 휠
            if ( e.Delta > 0 )
            {
                m_Renderer.ZoomInOutCameraPosition(-1);
            }
            else
            {
                m_Renderer.ZoomInOutCameraPosition(1);
            }
        }
    }
}
