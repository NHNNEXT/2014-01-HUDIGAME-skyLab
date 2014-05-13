using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Microsoft.DirectX;
using Microsoft.DirectX.Direct3D;

namespace GameTool.Class
{
    public class Renderer
    {
        public Renderer()
        {

        }

        // devices for ISS Renderer
        private List<Device> m_deviceList = new List<Device>();

        // D3D Device를 할당한다
        public void CreateDevice(System.Windows.Forms.Control display)
        {
            try
            {
                PresentParameters presentParams = new PresentParameters();
                presentParams.Windowed = true;
                presentParams.SwapEffect = SwapEffect.Discard;
                Device device = new Device(0, DeviceType.Hardware, display,
                    CreateFlags.SoftwareVertexProcessing, presentParams);

                m_deviceList.Add(device);
            }
            catch (DirectXException)
            {
                System.Windows.Forms.MessageBox.Show("DirectX CreateDevice Error");
                return;
            }
        }

        public void ClearRenderDevices()
        {
            m_deviceList.Clear();
        }

        public void Render()
        {
            foreach (Device dc in m_deviceList)
            {
                dc.Clear(ClearFlags.Target,
                System.Drawing.Color.FromArgb(0, 0, 255).ToArgb(),
                1.0f, 0);

                dc.Present();
            }
        }
    }
}
