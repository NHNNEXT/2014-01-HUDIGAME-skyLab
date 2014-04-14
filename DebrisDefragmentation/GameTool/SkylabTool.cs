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
        // render를 할지 말지 결정하는 bool값
        bool g_IsRenderable = true;

        // Random
        Random r = new Random();

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
           // DDWrapper의 Renderer가 멤버변수로 DDRenderer*를 가지고 있음
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
               AddLight();
               testMeshLoad();
               AddCamera();
               DrawScreen();
           }
          
        }

        private async void DrawScreen()
        {
            while(g_IsRenderable)
            {
                m_Renderer.Clear();

                if (m_Renderer.BeginDraw())
                {
                    // 여기서 뭔가 그리게 됩니다
                    RenderScene();
                    UpdateCameraInformation();
                }

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
            // test character
            string path = "tiger.x";
            m_Model = new DDWrapper.GameModel(path, m_Renderer);
            m_Scene.AddChild(m_Model);

            // test Debris
            string debrisPath = "debris.x";
            float randX, randY, randZ;
            for (int i = 0; i < 1000; ++i)
            {
                DDWrapper.GameModel debris = new DDWrapper.GameModel(debrisPath, m_Renderer);
                randX = r.Next(-100, 100);
                randY = r.Next(-100, 100);
                randZ = r.Next(-100, 100);
                debris.SetPosition(randX, randY, randZ);
                m_Scene.AddChild(debris);
            }
        }

        private void RenderScene()
        {
            m_Scene.Render();
        }

        private void AddCamera()
        {
            m_Camera = new DDWrapper.GameCamera();
            m_Model.AddChild(m_Camera);
        }

        private void AddLight()
        {
            m_Light = new DDWrapper.GameLight();
            m_Scene.AddChild(m_Light);
        }

        private void UpdateCameraInformation()
        {
            cameraXpos.Text = m_Camera.GetPositionX().ToString();
            cameraYpos.Text = m_Camera.GetPositionY().ToString();
            cameraZpos.Text = m_Camera.GetPositionZ().ToString();
        }

        private void ViewMouseEnver(object sender, EventArgs e)
        {
            this.View.Focus();
        }

        private void ViewMouseLeave(object sender, EventArgs e)
        {
            this.Focus();
        }

        private void ViewMouseMove(object sender, MouseEventArgs e)
        {
            if (e.Button == System.Windows.Forms.MouseButtons.Left)
            {
                m_Scene.IncreaseRotationX(e.X);
                m_Scene.IncreaseRotationY(e.Y);
            }
        } 
    }
}
