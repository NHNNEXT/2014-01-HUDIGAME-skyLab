using System;
using System.IO;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Net.Json;
using System.Text.RegularExpressions;

namespace GameTool
{
    public partial class skyLabTool : Form
    {
        // Json Config 파일을 다루기 위한 변수
        JsonObjectCollection g_JsonCollection = new JsonObjectCollection();

        // render를 할지 말지 결정하는 bool값
        bool g_IsRenderable = true;

        // Random
        Random r = new Random();

        // Timer
        GameTool.Class.GameTimer m_Timer = null;

        // Renderer
         // DDWrapper의 Renderer가 멤버변수로 DDRenderer*를 가지고 있음
        private DDWrapper.Renderer m_Renderer = new DDWrapper.Renderer();
        
        // Camera
        private GameTool.Class.GameCamera m_Camera = new GameTool.Class.GameCamera();

        // Scene
        private GameTool.Class.GameScene m_Scene = null;

        // Player model
        private GameTool.Class.GamePlayer m_Model = null;

        // StopWatch
        System.Diagnostics.Stopwatch m_StopWatch = new System.Diagnostics.Stopwatch();
        
        // acceleration variables
        bool g_IsAccelationInput = false;

        float previousTime = 0;
        float currentTime = 0;

        // light
        private GameTool.Class.GameLight m_Light = null;

        // mouseMovement values
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

               // Stopwatch 가동
               m_StopWatch.Start();

               AddCamera();
               DrawScreen();
           }

            // render가 끝난 다음 타이머를 설정한다
           m_Timer = new GameTool.Class.GameTimer(ref TimePass);
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
                }

                m_Renderer.EndDraw();
                UpdateCameraInformation();
                UpdatePlayerStatus();
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
            m_Model.AddChild(ref m_Camera);
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

                m_Scene.IncreaseRotationX((m_CurrentYPos - m_PrevYPos)/2);
                m_Scene.IncreaseRotationY((m_CurrentXPos - m_PrevXPos)/2);

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
            PlayerPosX.Text = m_Model.GetPositionX().ToString();
            PlayerPosY.Text = m_Model.GetPositionY().ToString();
            PlayerPosZ.Text = m_Model.GetPositionZ().ToString();

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

        private void RenderOnOff(object sender, EventArgs e)
        {
            g_IsRenderable = !g_IsRenderable;
            DrawScreen();
        }

        /////////////////////////////////////////////////////////////////////////////////////////////
        //                                       Second Tab                                        //
        /////////////////////////////////////////////////////////////////////////////////////////////

        private void LoadJsonFile(object sender, EventArgs e)
        {
            if ( this.JsonFileList.SelectedIndices.Count > 0 )
            {
                string file = JsonFileList.SelectedItem.ToString();
                StreamReader sr = new StreamReader(file);

                // 파일에서 다 읽는다
                string jsonText = sr.ReadToEnd();

                // 빈 파일이면?
                if (jsonText.Length == 0)
                {
                    // 파싱 없이 리턴
                    MessageBox.Show("Empty File!");
                    return;
                }

                // 파싱한 다음
                JsonTextParser parser = new JsonTextParser();
                JsonObject obj = parser.Parse(jsonText);

                // JSON 전역 객체로 전달한다
                g_JsonCollection = (JsonObjectCollection)obj;

                MessageBox.Show("Load Json Success!");

                // 스트림 리더를 닫는다.
                sr.Close();
            }
        }

        private void SearchJsonFiles(object sender, EventArgs e)
        {
            // 우선 파일 리스트를 비우고
            JsonFileList.Items.Clear();

            // Tool 이 실행된 폴더를 찾도록 한다
            System.IO.DirectoryInfo di = new System.IO.DirectoryInfo(@".\");

            foreach(System.IO.FileInfo f in di.GetFiles())
            {
                // 설정파일 규약을 좀 정해야겠네요
                if (f.Extension.ToString() == ".json")
                {
                    JsonFileList.Items.Add(f.Name);
                }
            }
        }

        private void SaveJsonFile(object sender, EventArgs e)
        {
            // 파일명이 있어야겠죠?
            if (JSONNameToSave.Text.Length > 0)
            {
                if (IsCorrectFileName(JSONNameToSave.Text))
                {
                    StreamWriter sw = new StreamWriter(JSONNameToSave.Text + ".json");

                    // 파일에 쓴다
                    sw.Write(g_JsonCollection.ToString());

                    MessageBox.Show("Save Json Success!");

                    // 스트림 라이터를 닫는다
                    sw.Close();
                }
                else
                {
                    MessageBox.Show("Invalid File Name!");
                    return;
                }
            }
            else
            {
                MessageBox.Show("Empty File Name!");
                return;
            }
        }

        private bool IsCorrectFileName(string fileName)
        {
            Regex rg = new Regex(@"[!@#$%^&*/\\]");
            if (rg.Matches(fileName).Count > 0)
            {
                return false;
            }
            return true;
        }
    }
}
