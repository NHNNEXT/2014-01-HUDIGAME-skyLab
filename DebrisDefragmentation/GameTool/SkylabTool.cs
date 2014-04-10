using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace GameTool
{
    public partial class skyLabTool : Form
    {
        bool g_IsRenderable = true;
        private DDWrapper.Renderer m_Renderer = null;

        public skyLabTool()
        {
           InitializeComponent();
           // new 하면 멤버변수가 싱글톤으로 할당됨
           m_Renderer = new DDWrapper.Renderer();

            // 방어 코드
           if (null == m_Renderer)
            {
                return;
            }

            // Renderer의 오버라이드된 Init 함수를 사용. 윈도우 크기와 HWND를 직접 넘겨준다
           if ( m_Renderer.Init(this.View.Handle.ToInt32(), this.View.Width, this.View.Height) )
           {
               DrawScreen();
           }
          
        }

        private async void DrawScreen()
        {
            while(g_IsRenderable)
            {
                m_Renderer.Clear();
                m_Renderer.BeginDraw();

                // 여기서 뭔가 그리게 됩니다

                m_Renderer.EndDraw();

                await Task.Delay(10);
            }
        }

        private void exitToolStripMenuItem_Click(object sender, EventArgs e)
        {
            //모든게 끝날 때 D3D도 릴리즈 시켜줘야 합니다
            g_IsRenderable = false;
            m_Renderer.Release();

            Application.Exit();
        }
    }
}
