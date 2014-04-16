using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

// 슬슬 툴에 들어가는 함수도 너무 많아져서 메인에서 여기저기 다른 클래스로 유배보내야 함

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
        private DDWrapper.Renderer m_Renderer = null;
        // Camera
        private DDWrapper.GameCamera m_Camera = null;
        // Physics
        private DDWrapper.GamePhysics m_Physics = new DDWrapper.GamePhysics();
        
        // test Scene
        private DDWrapper.GameObject m_Scene = null;

        // test model
        private DDWrapper.GameModel m_Model = null;
        // test model accelation & velocity
        System.Diagnostics.Stopwatch m_StopWatch = new System.Diagnostics.Stopwatch();
        bool g_IsAccelationInput = false;
        float accelX = 0;
        float accelY = 0;
        float accelZ = 0;
        float velocityX = 0;
        float velocityY = 0;
        float velocityZ = 0;
        float previousTime = 0;
        float currentTime = 0;

        // test light
        private DDWrapper.GameLight m_Light = null;

        // test mouseMovement values
        float m_PrevXPos = 0.0f;
        float m_CurrentXPos = 0.0f;
        float m_PrevYPos = 0.0f;
        float m_CurrentYPos = 0.0f;

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
            
            // Direct3D 창에서 마우스 휠 이벤트 추가
           this.View.MouseWheel += new System.Windows.Forms.MouseEventHandler(CameraZoomInOut);

           
            // Scene 추가
           m_Scene = new DDWrapper.GameObject();
       
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

                await Task.Delay(30);
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
            m_Model = new DDWrapper.GameModel(path);
            m_Scene.AddChild(m_Model);

            // test Debris
            string debrisPath = "debris.x";
            float randX, randY, randZ;
            for (int i = 0; i < 1000; ++i)
            {
                DDWrapper.GameModel debris = new DDWrapper.GameModel(debrisPath);
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
                m_Camera.SetPosition(
                    m_Camera.GetPositionX(),
                    m_Camera.GetPositionY(),
                    m_Camera.GetPositionZ() + 3
                );
            }
            else
            {
                m_Camera.SetPosition(
                   m_Camera.GetPositionX(),
                   m_Camera.GetPositionY(),
                   m_Camera.GetPositionZ() - 3
               );
            }
        }

        private void ResetCamera(object sender, EventArgs e)
        {
            m_Camera.SetPosition(0, 1, -5);
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
            accelX = 0;
            accelY = 0;
            accelZ = 0;
            velocityX = 0;
            velocityY = 0;
            velocityZ = 0;
        }

        private void MovePlayer()
        {
            currentTime = m_StopWatch.ElapsedMilliseconds / 1000.0f;
            float dt = currentTime - previousTime;
            previousTime = currentTime;

            if ( g_IsAccelationInput )
            {
                // 아 여기서 노말벡터 구해줘야함;; 그냥 뷰 디렉션 넣으면 ㄴㄴ해
                accelX = m_Model.GetViewDirectionX() * 50;
                accelY = m_Model.GetViewDirectionY() * 50;
                accelZ = m_Model.GetViewDirectionZ() * 50;
                
                if ( m_Physics.AccelObject(m_Model, velocityX, velocityY, velocityZ, accelX, accelY, accelZ, dt) )
                {
                    velocityX += accelX * dt;
                    velocityY += accelY * dt;
                    velocityZ += accelZ * dt;
                }
                else
                {
                    g_IsAccelationInput = false;
                    accelX = 0;
                    accelY = 0;
                    accelZ = 0;
                }
            }
            else
            {
                m_Physics.MoveObject(m_Model, velocityX, velocityY, velocityZ, dt);
            }
        }

        private double GetAccelation()
        {
            return Math.Pow((accelX * accelX + accelY * accelY + accelZ * accelZ), 0.5);
        }

        private double GetSpeed()
        {
            return Math.Pow((velocityX * velocityX + velocityY * velocityY + velocityZ * velocityZ), 0.5);
        }
        
        private void UpdatePlayerStatus()
        {
            // update position
            this.PlayerPosX.Text = m_Model.GetPositionX().ToString();
            this.PlayerPosY.Text = m_Model.GetPositionY().ToString();
            this.PlayerPosZ.Text = m_Model.GetPositionZ().ToString();

            // update acceleration
            this.IntegratedAccelVal.Text = GetAccelation().ToString();
            this.PlayerAccelX.Text = accelX.ToString();
            this.PlayerAccelY.Text = accelY.ToString();
            this.PlayerAccelZ.Text = accelZ.ToString();

            // update speed
            this.IntegratedVelVal.Text = GetSpeed().ToString();
            this.PlayerVelocityX.Text = velocityX.ToString();
            this.PlayerVelocityY.Text = velocityY.ToString();
            this.PlayerVelocityZ.Text = velocityZ.ToString();
        }
    }
}
