using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Microsoft.DirectX.Direct3D;
using Microsoft.DirectX;
using Microsoft.DirectX.PrivateImplementationDetails;

namespace GameTool.Class
{
    class GameObject
    {
        Device m_device;

        private Mesh GameObjectMesh = null;
        Material[] GameObjectMaterials;
        Texture[] GameObjectTextures;

        string m_filename;

        VertexBuffer m_CollisionBox;

        public GameObject(string fileName)
        {
            m_filename = fileName;

            if (m_filename.Length == 0)
            {
                System.Windows.Forms.MessageBox.Show("Empty Mesh File Name!");
                return;
            }
        }

        public void init(ref Device d3dDevice)
        {
            m_device = d3dDevice;

            LoadMesh(Class.Renderer.FOLDER_PATH + m_filename, ref GameObjectMesh, ref GameObjectMaterials, ref GameObjectTextures);
            setCollisionBox();
        }

        // 조심해!! 하드코딩
        public void setCollisionBox()
        {
            m_CollisionBox = new VertexBuffer(typeof(CustomVertex.TransformedColored), 8, m_device, 0,
                CustomVertex.TransformedColored.Format, Pool.Default);

            GraphicsStream stm = m_CollisionBox.Lock(0, 0, 0);
            CustomVertex.TransformedColored[] verts = new CustomVertex.TransformedColored[8];
            verts[0].X = 150; verts[0].Y = 50; verts[0].Z = -50; verts[0].Rhw = 1;
            verts[0].Color = System.Drawing.Color.Crimson.ToArgb();
            verts[1].X = -150; verts[1].Y = 50; verts[1].Z = -50; verts[1].Rhw = 1;
            verts[1].Color = System.Drawing.Color.Crimson.ToArgb();
            verts[2].X = -150; verts[2].Y = 50; verts[2].Z = 50; verts[2].Rhw = 1;
            verts[2].Color = System.Drawing.Color.Crimson.ToArgb();
            verts[3].X = 150; verts[3].Y = 50; verts[3].Z = 50; verts[3].Rhw = 1;
            verts[3].Color = System.Drawing.Color.Crimson.ToArgb();
            verts[4].X = 150; verts[4].Y = -50; verts[4].Z = -50; verts[4].Rhw = 1;
            verts[4].Color = System.Drawing.Color.Crimson.ToArgb();
            verts[5].X = -150; verts[5].Y = -50; verts[5].Z = -50; verts[5].Rhw = 1;
            verts[5].Color = System.Drawing.Color.Crimson.ToArgb();
            verts[6].X = -150; verts[6].Y = -50; verts[6].Z = 50; verts[6].Rhw = 1;
            verts[6].Color = System.Drawing.Color.Crimson.ToArgb();
            verts[7].X = 150; verts[7].Y = -50; verts[7].Z = 50; verts[7].Rhw = 1;
            verts[7].Color = System.Drawing.Color.Crimson.ToArgb();

            stm.Write(verts);
            m_CollisionBox.Unlock();
        }

        // 메쉬를 불러오는 함수
        private void LoadMesh(string filenameWithPath, ref Mesh mesh, ref Material[] meshmaterials, ref Texture[] meshtextures)
        {
            ExtendedMaterial[] materialarray;
            mesh = Mesh.FromFile(filenameWithPath, MeshFlags.Managed, m_device, out materialarray);

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
                        meshtextures[i] = TextureLoader.FromFile(m_device, Class.Renderer.FOLDER_PATH + materialarray[i].TextureFilename);
                    }
                }
            }

            mesh = mesh.Clone(mesh.Options.Value, CustomVertex.PositionNormalTextured.Format, m_device);
            mesh.ComputeNormals();

            VertexBuffer vertices = mesh.VertexBuffer;
            GraphicsStream stream = vertices.Lock(0, 0, LockFlags.None);
            vertices.Unlock();
        }

        public void DrawObject()
        {
            DrawMesh(GameObjectMesh, GameObjectMaterials, GameObjectTextures);
        }

        private void ClearMesh()
        {
            GameObjectMaterials = null;
            GameObjectMesh = null;
            GameObjectTextures = null;
        }

        private void DrawMesh(Mesh mesh, Material[] meshmaterials, Texture[] meshtextures)
        {
            for (int i = 0; i < meshmaterials.Length; i++)
            {
                m_device.Material = meshmaterials[i];
                m_device.SetTexture(0, meshtextures[i]);
                mesh.DrawSubset(i);
            }

            DrawBoundingBox();
        }

        private void DrawBoundingBox()
        {
            m_device.SetStreamSource(0, m_CollisionBox, 0);
            m_device.VertexFormat = CustomVertex.TransformedColored.Format;
            m_device.DrawPrimitives(PrimitiveType.TriangleList, 0, 2);
        }
    }
}
