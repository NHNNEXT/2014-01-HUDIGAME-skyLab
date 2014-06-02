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
        IndexBuffer m_IndexBuffer;

        private Int16[] m_IndexedBufferOrder = {0, 1, 1, 2, 2, 3, 3, 0, 0, 4, 1, 5, 2, 6, 3, 7, 4, 5, 5, 6, 6, 7, 7, 4 };

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
            m_CollisionBox = new VertexBuffer(typeof(CustomVertex.PositionColored), 8,
                m_device, 0, CustomVertex.PositionColored.Format, Pool.Default);

            CustomVertex.PositionColored[] posColoredVerts = new CustomVertex.PositionColored[8];
            posColoredVerts[0].Position = new Vector3(-100, 150, -150);
            posColoredVerts[0].Color = System.Drawing.Color.Black.ToArgb();
            posColoredVerts[1].Position = new Vector3(100, 150, -150);
            posColoredVerts[1].Color = System.Drawing.Color.Black.ToArgb();
            posColoredVerts[2].Position = new Vector3(100, 150, 150);
            posColoredVerts[2].Color = System.Drawing.Color.Black.ToArgb();
            posColoredVerts[3].Position = new Vector3(-100, 150, 150);
            posColoredVerts[3].Color = System.Drawing.Color.Black.ToArgb();
            posColoredVerts[4].Position = new Vector3(-100, -150, -150);
            posColoredVerts[4].Color = System.Drawing.Color.Black.ToArgb();
            posColoredVerts[5].Position = new Vector3(100, -150, -150);
            posColoredVerts[5].Color = System.Drawing.Color.Crimson.ToArgb();
            posColoredVerts[6].Position = new Vector3(100, -150, 150);
            posColoredVerts[6].Color = System.Drawing.Color.Crimson.ToArgb();
            posColoredVerts[7].Position = new Vector3(-100, -150, 150);
            posColoredVerts[7].Color = System.Drawing.Color.Crimson.ToArgb();

            GraphicsStream gstm = m_CollisionBox.Lock(0, 0, LockFlags.None);
            gstm.Write(posColoredVerts);
            m_CollisionBox.Unlock();

            // indexedBuffer
            m_IndexBuffer = new IndexBuffer(m_device, 12 * 2 * 2, Usage.WriteOnly, Pool.Managed, true);

            GraphicsStream idstm = m_IndexBuffer.Lock(0, 0, LockFlags.None);
            idstm.Write(m_IndexedBufferOrder);
            m_IndexBuffer.Unlock();

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
            
            //m_device.DrawUserPrimitives(PrimitiveType.TriangleStrip, 1, m_testTriangle);

            m_device.SetStreamSource(0, m_CollisionBox, 0);
            //m_device.VertexFormat = CustomVertex.PositionColored.Format;
            m_device.Indices = m_IndexBuffer;
            m_device.DrawIndexedPrimitives(PrimitiveType.LineList, 0, 0, 8, 0, 12 );
        }
    }
}
