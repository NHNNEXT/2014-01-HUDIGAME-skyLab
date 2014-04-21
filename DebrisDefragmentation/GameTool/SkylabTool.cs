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

        // Timer
        System.Windows.Forms.Timer m_Timer = new Timer();
        int m_Second = 0;
        int m_Minute = 0;
        int m_Hour = 0;

        // Renderer
         // DDWrapper의 Renderer가 멤버변수로 DDRenderer*를 가지고 있음
        private DDWrapper.Renderer m_Renderer = new DDWrapper.Renderer();
        
        // Camera
        private GameTool.Class.GameCamera m_Camera = new GameTool.Class.GameCamera();

        // test Scene
        private GameTool.Class.GameScene m_Scene = null;

        // test model
        private GameTool.Class.GamePlayer m_Model = null;

        // test model accelation & velocity
        System.Diagnostics.Stopwatch m_StopWatch = new System.Diagnostics.Stopwatch();
        bool g_IsAccelationInput = false;

        float previousTime = 0;
        float currentTime = 0;

        // test light
        private GameTool.Class.GameLight m_Light = null;

        // test mouseMovement values
        float m_PrevXPos = 0.0f;
        float m_CurrentXPos = 0.0f;
        float m_PrevYPos = 0.0f;
        float m_CurrentYPos = 0.0f;

        public skyLabTool()
        {
           InitializeComponent();

            // 방어 코드
           if (null == m_Renderer)
            {
                return;
            }
            
            // Direct3D 창에서 마우스 휠 이벤트 추가
           this.View.MouseWheel += new System.Windows.Forms.MouseEventHandler(CameraZoomInOut);

            // Scene 추가
           m_Scene = new GameTool.Class.GameScene();
       
            // Renderer의 오버라이드된 Init 함수를 사용. 윈도우 크기와 HWND를 직접 넘겨준다
           if ( m_Renderer.Init(this.View.Handle.ToInt32(), this.View.Width, this.View.Height) )
           {
               AddLight();
               testMeshLoad();

               // Timer 가동
               SettingTimer();

               // Stopwatch 가동
               m_StopWatch.Start();

               AddCamera();
               DrawScreen();
           }
        }
        // 화면에 그림 그리는 함수
        private async void DrawScreen()
        {
            while(g_IsRenderable)
            {
                m_Renderer.Clear();

                if (m_Renderer.BeginDraw())
                {
                    // 여기서 뭔가 그리게 됩니다
                    MovePlayer();
                    RenderScene();
                    UpdateCameraInformation();
                    UpdatePlayerStatus();
                }

                m_Renderer.EndDraw();

                await Task.Delay(16);
            }
        }
        // 여기 들어오면 종료된다
        private void exitToolStripMenuItem_Click(object sender, EventArgs e)
        {
            //모든게 끝날 때 D3D도 릴리즈 시켜줘야 합니다
            g_IsRenderable = false;
            m_Renderer.Release();

            Application.Exit();
        }
        // 호랑이 한 마리랑 데브리 2000개쯤 불러오는 함수
        private void testMeshLoad()
        {
            // test character
            string path = "tiger.x";
            m_Model = new GameTool.Class.GamePlayer(path);
            m_Scene.AddChild(ref m_Model);

            // test Debris
            string debrisPath = "debris.x";
            float randX, randY, randZ;
            for (int i = 0; i < 2000; ++i)
            {
                GameTool.Class.GameModel debris = new GameTool.Class.GameModel(debrisPath);
                randX = r.Next(-200, 200);
                randY = r.Next(-200, 200);
                randZ = r.Next(-200, 200);
                debris.SetScale(0.5f);
                debris.SetPosition(randX, randY, randZ);
                m_Scene.AddChild(ref debris);
            }
        }

        private void RenderScene()
        {
            m_Scene.Render();
        }

        private void AddCamera()
        {
            m_Scene.AddChild(ref m_Camera);
        }

        private void AddLight()
        {
            m_Light = new GameTool.Class.GameLight();
            m_Scene.AddChild(ref m_Light);
        }

        private void UpdateCameraInformation()
        {
            cameraXpos.Text = m_Camera.GetPositionX().ToString();
            cameraYpos.Text = m_Camera.GetPositionY().ToString();
            cameraZpos.Text = m_Camera.GetPositionZ().ToString();

            CameraViewVecX.Text = m_Camera.GetViewDirectionX().ToString();
            CameraViewVecY.Text = m_Camera.GetViewDirectionY().ToString();
            CameraViewVecZ.Text = m_Camera.GetViewDirectionZ().ToString();
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
                m_CurrentXPos = e.X;
                m_CurrentYPos = e.Y;

                m_Scene.IncreaseRotationX(m_CurrentYPos - m_PrevYPos);
                m_Scene.IncreaseRotationY(m_CurrentXPos - m_PrevXPos);

                m_PrevXPos = m_CurrentXPos;
                m_PrevYPos = m_CurrentYPos;
            }
            else
            {
                // 안쓰면 초기화
                m_CurrentXPos = 0;
                m_CurrentYPos = 0;
                m_PrevXPos = 0;
                m_PrevYPos = 0;
            }
        }

        private void InputProc(object sender, PreviewKeyDownEventArgs e)
        {
            if (e.KeyCode  == Keys.W)
            {
                g_IsAccelationInput = true;
            }
            if (e.KeyCode == Keys.S)
            {
                StopPlayer();
            }
        } 

        private void CameraZoomInOut(object sender, MouseEventArgs e)
        {
            if (e.Delta > 0)
            {
                m_Camera.MoveCamera(0, 0, 1);
            }
            else
            {
                m_Camera.MoveCamera(0, 0, -1);
            }
        }

        private void ResetCamera(object sender, EventArgs e)
        {
            m_Camera.ResetCamera();
        }

        private void SettingTimer()
        {
            // 1초 주기로
            m_Timer.Interval = 1000;

            m_Timer.Tick += new EventHandler(UpdateClock);
            m_Timer.Start();
        }

        private void UpdateClock(object sender, EventArgs e)
        {
            ++m_Second;

            if (m_Second > 59)
            {
                ++m_Minute;
                m_Second = 0;
            }

            if (m_Minute > 59)
            {
                ++m_Hour;
                m_Minute = 0;
            }

            string result = m_Hour.ToString() + " 시  " + m_Minute.ToString() + " 분  " + m_Second.ToString() + " 초";
            TimePass.Text = result;
        }

        private void StopPlayer()
        {
            m_Model.StopPlayer();
        }

        private void MovePlayer()
        {
            currentTime = m_StopWatch.ElapsedMilliseconds / 1000.0f;
            float dt = currentTime - previousTime;
            previousTime = currentTime;

            if ( !m_Model.MovePlayer(dt, g_IsAccelationInput) )
            {
                g_IsAccelationInput = false;
            }
        }

        private void UpdatePlayerStatus()
        {
            // update position
            this.PlayerPosX.Text = m_Model.GetPositionX().ToString();
            this.PlayerPosY.Text = m_Model.GetPositionY().ToString();
            this.PlayerPosZ.Text = m_Model.GetPositionZ().ToString();

            // update acceleration
            this.IntegratedAccelVal.Text = m_Model.GetAccelation().ToString();
            this.PlayerAccelX.Text = m_Model.GetAccelX().ToString();
            this.PlayerAccelY.Text = m_Model.GetAccelY().ToString();
            this.PlayerAccelZ.Text = m_Model.GetAccelZ().ToString();

            // update speed
            this.IntegratedVelVal.Text = m_Model.GetSpeed().ToString();
            this.PlayerVelocityX.Text = m_Model.GetSpeedX().ToString();
            this.PlayerVelocityY.Text = m_Model.GetSpeedY().ToString();
            this.PlayerVelocityZ.Text = m_Model.GetSpeedZ().ToString();
        }

        private void ResetPlayerStatus(object sender, EventArgs e)
        {
            m_Model.SetPosition(0, 0, 0);
            StopPlayer();
        }
    }
}
