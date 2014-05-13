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

namespace GameTool.Class
{
    public class Renderer
    {
        // 조심해!! 이걸 Renderer가 갖고 있는 구조는 좋지 않다 (확장 X)
        // 어디까지나 임시방편임!
        // ISS variables
        private Mesh ISSMesh = null;
        D3D.Material[] ISSMaterials;
        D3D.Texture[] ISSTextures;
        const string filename = "ISS.x";

        // devices for ISS Renderer
        private Device m_device = null;

        public Renderer()
        {

        }

        private void LoadMesh(string filename, ref Mesh mesh, ref Material[] meshmaterials, ref Texture[] meshtextures, Device device)
        {
            ExtendedMaterial[] materialarray;
            mesh = Mesh.FromFile(filename, MeshFlags.Managed, device, out materialarray);

            if ((materialarray != null) && (materialarray.Length > 0))
            {
                meshmaterials = new Material[materialarray.Length];
                meshtextures = new Texture[materialarray.Length];

                for (int i = 0; i < materialarray.Length; i++)
                {
                    meshmaterials[i] = materialarray[i].Material3D;
                    meshmaterials[i].Ambient = meshmaterials[i].Diffuse;

                    if ((materialarray[i].TextureFilename != null) && (materialarray[i].TextureFilename != string.Empty))
                    {
                        meshtextures[i] = TextureLoader.FromFile(device, materialarray[i].TextureFilename);
                    }
                }
            }

            mesh = mesh.Clone(mesh.Options.Value, CustomVertex.PositionNormalTextured.Format, device);
            mesh.ComputeNormals();

            VertexBuffer vertices = mesh.VertexBuffer;
            GraphicsStream stream = vertices.Lock(0, 0, LockFlags.None);
            vertices.Unlock();
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
                m_device.RenderState.Lighting = false;
                m_device.RenderState.CullMode = Cull.Clockwise;
            }
            catch (DirectXException)
            {
                System.Windows.Forms.MessageBox.Show("DirectX CreateDevice Error");
                return;
            }
        }

        public void Render()
        {
            m_device.Clear(ClearFlags.Target,
                System.Drawing.Color.FromArgb(0, 0, 0).ToArgb(),
                1.0f, 0);
            m_device.Present();
        }
    }
}
