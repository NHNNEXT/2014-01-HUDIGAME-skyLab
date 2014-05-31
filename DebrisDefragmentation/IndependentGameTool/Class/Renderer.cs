using System;
using System.Collections.Generic;
using System.IO;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Microsoft.DirectX;
using Microsoft.DirectX.Direct3D;
using D3D = Microsoft.DirectX.Direct3D;
using System.Drawing;

namespace GameTool.Class
{
    public class Renderer
    {
        public const string FOLDER_PATH = ".\\Resources\\3DModel\\";
        List<GameObject> m_GameObjectList = new List<GameObject>();

        // 카메라 확대, 축소에 관여하는 변수
        int m_CameraZoomOutVar = 0;

        // camera variables
        int Width = 760;
        int Height = 680;

        // viewports
        Viewport defaultViewport;
        Viewport AxisXViewport;
        Viewport AxisYViewport;
        Viewport AxisZViewport;

        enum VIEWPORT
        {
            PERSPECTIVE,
            AXIS_X,
            AXIS_Y,
            AXIS_Z
        }

        // devices for ISS Renderer
        private Device m_device = null;

        // 아무것도 안 하는 생성자
        public Renderer()
        {

        }


        public bool IsDeviceReady()
        {
            if (null == m_device)
            {
                return false;
            }
            else
            {
                return true;
            }
        }


        // 4대의 카메라가 자신이 보고 있는 방향으로 앞/ 뒤로 움직인다
        public void ZoomInOutCameraPosition(int delta)
        {
            m_CameraZoomOutVar += delta;
        }
        

        // D3D Device를 할당한다
        public void CreateDevice(System.Windows.Forms.Control display)
        {
            try
            {
                PresentParameters presentParams = new PresentParameters();
                presentParams.Windowed = true;
                presentParams.SwapEffect = SwapEffect.Discard;
                presentParams.EnableAutoDepthStencil = true;
                presentParams.AutoDepthStencilFormat = DepthFormat.D16;
                m_device = new Device(0, DeviceType.Hardware, display,
                    CreateFlags.SoftwareVertexProcessing, presentParams);

                // device options
                m_device.RenderState.ZBufferEnable = true;
                m_device.RenderState.Lighting = true;
                m_device.RenderState.CullMode = Cull.None;

                Init();
            }
            catch (DirectXException)
            {
                System.Windows.Forms.MessageBox.Show("DirectX CreateDevice Error");
                return;
            }
        }

        private void SetUpCamera()
        {
            m_device.Transform.Projection = Matrix.PerspectiveFovLH((float)Math.PI / 4, (float)this.Width / (float)this.Height, 0.3f, 500f);
        }
        
        // 4개의 뷰포트마다 저마다 다른 카메라를 가진다
        private void ChangeCameraAndViewPort(VIEWPORT v)
        {
            Vector3 ISSPos = new Vector3(0, 0, 0);

            switch (v)
            {
                case VIEWPORT.PERSPECTIVE:
                    m_device.Transform.View = Matrix.LookAtLH(new Vector3(30 + m_CameraZoomOutVar, 15 + m_CameraZoomOutVar, 15 + m_CameraZoomOutVar), ISSPos, new Vector3(0, 0, 1));
                    m_device.Viewport = defaultViewport;
                    break;
                case VIEWPORT.AXIS_X:
                    m_device.Transform.View = Matrix.LookAtLH(new Vector3(60 + m_CameraZoomOutVar, 0, 0), ISSPos, new Vector3(0, 0, 1));
                    m_device.Viewport = AxisXViewport;
                    break;
                case VIEWPORT.AXIS_Y:
                    m_device.Transform.View = Matrix.LookAtLH(new Vector3(0, 60 + m_CameraZoomOutVar, 0), ISSPos, new Vector3(0, 0, 1));
                    m_device.Viewport = AxisYViewport;
                    break;
                case VIEWPORT.AXIS_Z:
                    m_device.Transform.View = Matrix.LookAtLH(new Vector3(0, 0, 60 + m_CameraZoomOutVar), ISSPos, new Vector3(0, 1, 0));
                    m_device.Viewport = AxisZViewport;
                    break;
                default:
                    m_device.Transform.View = Matrix.LookAtLH(new Vector3(20, 5, 13), ISSPos, new Vector3(0, 0, 1));
                    break;
            }
        }

        // 4개의 뷰 포트를 할당함
        private void ReallocateViewPort()
        {
            defaultViewport = m_device.Viewport;
            defaultViewport.Width /= 2;
            defaultViewport.Height /= 2;
            AxisXViewport = defaultViewport;
            AxisYViewport = defaultViewport;
            AxisZViewport = defaultViewport;

            AxisYViewport.X = AxisXViewport.Width;
            AxisZViewport.Y = AxisXViewport.Height;
            defaultViewport.X = AxisYViewport.X;
            defaultViewport.Y = AxisZViewport.Y;
        }

        private void SetUpLight()
        {
            m_device.Lights[0].Type = LightType.Directional;
            m_device.Lights[0].Diffuse = Color.White;
            m_device.Lights[0].Direction = new Vector3(5, 5, 5);
            m_device.Lights[0].Enabled = true;

            m_device.Lights[1].Type = LightType.Point;
            m_device.Lights[1].Ambient = Color.White;
            m_device.Lights[1].Direction = new Vector3(10, 10, 10);
            m_device.Lights[1].Enabled = true;
        }

        private void Init()
        {
            SetUpCamera();
            SetUpLight();
            ReallocateViewPort();
        }

        public void CreateAndAddMesh(string name)
        {
            GameObject gObj = new GameObject(name);
            gObj.init(ref m_device);
            m_GameObjectList.Add(gObj);
        }

        public void Render()
        {
            m_device.BeginScene();

            m_device.Transform.World = Matrix.Identity;
            m_device.VertexFormat = CustomVertex.PositionNormalTextured.Format;

            foreach(VIEWPORT v in Enum.GetValues(typeof(VIEWPORT)) )
            {
                ChangeCameraAndViewPort(v);
                // clear를 여기서 호출해야 모든 뷰 포트가 깔끔해진다
                m_device.Clear(ClearFlags.Target | ClearFlags.ZBuffer, System.Drawing.Color.DarkSeaGreen, 1.0f, 0);
                RenderGameObject();
            }

            m_device.EndScene();
            m_device.Present();
        }

        private void RenderGameObject()
        {
            foreach(GameObject gobj in m_GameObjectList)
            {
                gobj.DrawObject();
            }
        }

        private void RenderCollisionBox()
        {
            
        }
    }
}
