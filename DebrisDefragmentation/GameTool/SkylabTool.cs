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
        // Renderer
        private DDWrapper.Renderer m_Renderer = null;
        // Camera
        private DDWrapper.GameCamera m_Camera = null;
        
        // test Scene
        private DDWrapper.GameObject m_Scene = null;

        // test model
        private DDWrapper.GameModel m_Model = null;

        // test light
        private DDWrapper.GameLight m_Light = null;

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

           m_Scene = new DDWrapper.GameObject();
       
            // Renderer의 오버라이드된 Init 함수를 사용. 윈도우 크기와 HWND를 직접 넘겨준다
           if ( m_Renderer.Init(this.View.Handle.ToInt32(), this.View.Width, this.View.Height) )
           {
               AddCamera();
               AddLight();
               testMeshLoad();
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
                RenderScene();

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

        private void testMeshLoad()
        {
            string path = "tiger.x";
            m_Model = new DDWrapper.GameModel(path, m_Renderer);
            m_Scene.AddChild(m_Model);
        }

        private void RenderScene()
        {
            m_Scene.Render();
        }

        private void AddCamera()
        {
            m_Camera = new DDWrapper.GameCamera();
            m_Scene.AddChild(m_Camera);
        }

        private void AddLight()
        {
            m_Light = new DDWrapper.GameLight();
            m_Scene.AddChild(m_Light);
        }
    }
}
