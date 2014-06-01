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

        CustomVertex.TransformedColored[] m_CollisionBox;
        VertexBuffer m_testTriangle;

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
            m_CollisionBox = new CustomVertex.TransformedColored[8];
            m_CollisionBox[0].Position = new Vector4(1000, 150, -150, 1.0f);
            m_CollisionBox[0].Color = System.Drawing.Color.Black.ToArgb();
            m_CollisionBox[1].Position = new Vector4(-1000, 150, -150, 1.0f);
            m_CollisionBox[1].Color = System.Drawing.Color.Black.ToArgb();
            m_CollisionBox[2].Position = new Vector4(-1000, 150, 150, 1.0f);
            m_CollisionBox[2].Color = System.Drawing.Color.Black.ToArgb();
            m_CollisionBox[3].Position = new Vector4(1000, 150, 150, 1.0f);
            m_CollisionBox[3].Color = System.Drawing.Color.Black.ToArgb();
            m_CollisionBox[4].Position = new Vector4(1000, -150, -150, 1.0f);
            m_CollisionBox[4].Color = System.Drawing.Color.Black.ToArgb();
            m_CollisionBox[5].Position = new Vector4(-1000, -150, -150, 1.0f);
            m_CollisionBox[5].Color = System.Drawing.Color.Crimson.ToArgb();
            m_CollisionBox[6].Position = new Vector4(-1000, -150, 150, 1.0f);
            m_CollisionBox[6].Color = System.Drawing.Color.Crimson.ToArgb();
            m_CollisionBox[7].Position = new Vector4(1000, -150, 150, 1.0f);
            m_CollisionBox[7].Color = System.Drawing.Color.Crimson.ToArgb();

            m_testTriangle = new VertexBuffer(typeof(CustomVertex.PositionColored), 3,
                m_device, 0, CustomVertex.PositionColored.Format, Pool.Default);


            CustomVertex.PositionColored[] verts = new CustomVertex.PositionColored[3];

            verts[0].X = 250f;
            verts[0].Y = 0f;
            verts[0].Z = 0f;
            verts[0].Color = System.Drawing.Color.Black.ToArgb();
            verts[1].X = 0f;
            verts[1].Y = 250f;
            verts[1].Z = 0f;
            verts[1].Color = System.Drawing.Color.Black.ToArgb();
            verts[2].X = 0f;
            verts[2].Y = 0f;
            verts[2].Z = 0f;
            verts[2].Color = System.Drawing.Color.Black.ToArgb();

            GraphicsStream stm = m_testTriangle.Lock(0, 0, LockFlags.None);
            stm.Write(verts);
            m_testTriangle.Unlock();
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
            //DrawMesh(GameObjectMesh, GameObjectMaterials, GameObjectTextures);
            DrawBoundingBox();
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
        }

        public void DrawBoundingBox()
        {
            
            m_device.SetStreamSource(0, m_testTriangle, 0);
            m_device.VertexFormat = CustomVertex.PositionColored.Format;
            //m_device.DrawUserPrimitives(PrimitiveType.LineList, 12, m_CollisionBox);
            //m_device.DrawUserPrimitives(PrimitiveType.LineStrip, 8, m_CollisionBox);
            m_device.DrawPrimitives(PrimitiveType.TriangleList, 0, 1);
            //m_device.DrawUserPrimitives(PrimitiveType.TriangleStrip, 1, m_testTriangle);
        }
    }
}
