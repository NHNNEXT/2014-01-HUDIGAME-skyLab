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

        private Mesh m_GameObjectMesh = null;
        Material[] m_GameObjectMaterials;
        Texture[] m_GameObjectTextures;

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

            LoadMesh(Class.Renderer.FOLDER_PATH + m_filename, ref m_GameObjectMesh, ref m_GameObjectMaterials, ref m_GameObjectTextures);
            setCollisionBox();
        }

        // Default 값
        public void setCollisionBox()
        {
            if (null != m_CollisionBox)
            {
                m_CollisionBox.Dispose();
            }

            m_CollisionBox = new VertexBuffer(typeof(CustomVertex.PositionColored), 8,
                m_device, 0, CustomVertex.PositionColored.Format, Pool.Default);

            CustomVertex.PositionColored[] posColoredVerts = new CustomVertex.PositionColored[8];

            for (int i = 0; i < posColoredVerts.Length; ++i )
            {
                posColoredVerts[i].Position = new Vector3(0, 0, 0);
                posColoredVerts[i].Color = System.Drawing.Color.Black.ToArgb();
            }

            GraphicsStream gstm = m_CollisionBox.Lock(0, 0, LockFlags.None);
            gstm.Write(posColoredVerts);
            m_CollisionBox.Unlock();

            // indexedBuffer
            m_IndexBuffer = new IndexBuffer(m_device, 12 * 2 * 2, Usage.WriteOnly, Pool.Managed, true);

            GraphicsStream idstm = m_IndexBuffer.Lock(0, 0, LockFlags.None);
            idstm.Write(m_IndexedBufferOrder);
            m_IndexBuffer.Unlock();
        }

        public void SetScale(float scale)
        {
//             Mesh scaledMesh = m_GameObjectMesh.Clone(m_GameObjectMesh.Options.Value, CustomVertex.PositionNormalTextured.Format, m_device);
//             Array arr = scaledMesh.LockVertexBuffer(typeof(CustomVertex.PositionNormalTextured), LockFlags.Discard, scaledMesh.NumberVertices);
// 
//             for (int i = 0; i < arr.Length; ++i )
//             {
//                 
//             }
// 
//             m_GameObjectMesh = scaledMesh;
            
        }

        // override
        // 자 이 함수가 뭐냐면 오브젝트의 로컬 좌표계 기준으로 오브젝트 중심이 (0, 0, 0)일 때
        // 축 길이를 조절할 수 있는 함수입니다
        public void setCollisionBox(float axisLenX, float axisLenY, float axisLenZ)
        {
            if(null != m_CollisionBox)
            {
                m_CollisionBox.Dispose();
            }
            m_CollisionBox = new VertexBuffer(typeof(CustomVertex.PositionColored), 8,
                m_device, 0, CustomVertex.PositionColored.Format, Pool.Default);

            CustomVertex.PositionColored[] posColoredVerts = new CustomVertex.PositionColored[8];
            posColoredVerts[0].Position = new Vector3(-axisLenX, axisLenY, -axisLenZ);
            posColoredVerts[0].Color = System.Drawing.Color.Black.ToArgb();
            posColoredVerts[1].Position = new Vector3(axisLenX, axisLenY, -axisLenZ);
            posColoredVerts[1].Color = System.Drawing.Color.Black.ToArgb();
            posColoredVerts[2].Position = new Vector3(axisLenX, axisLenY, axisLenZ);
            posColoredVerts[2].Color = System.Drawing.Color.Black.ToArgb();
            posColoredVerts[3].Position = new Vector3(-axisLenX, axisLenY, axisLenZ);
            posColoredVerts[3].Color = System.Drawing.Color.Black.ToArgb();
            posColoredVerts[4].Position = new Vector3(-axisLenX, -axisLenY, -axisLenZ);
            posColoredVerts[4].Color = System.Drawing.Color.Black.ToArgb();
            posColoredVerts[5].Position = new Vector3(axisLenX, -axisLenY, -axisLenZ);
            posColoredVerts[5].Color = System.Drawing.Color.Crimson.ToArgb();
            posColoredVerts[6].Position = new Vector3(axisLenX, -axisLenY, axisLenZ);
            posColoredVerts[6].Color = System.Drawing.Color.Crimson.ToArgb();
            posColoredVerts[7].Position = new Vector3(-axisLenX, -axisLenY, axisLenZ);
            posColoredVerts[7].Color = System.Drawing.Color.Crimson.ToArgb();

            GraphicsStream gstm = m_CollisionBox.Lock(0, 0, LockFlags.None);
            gstm.Write(posColoredVerts);
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
           
           int[] adjacency = new int[mesh.NumberFaces * 3];
            mesh.GenerateAdjacency(0.01F, adjacency);
            mesh.OptimizeInPlace(MeshFlags.OptimizeVertexCache, adjacency);
        }

        public void DrawObject()
        {
            DrawMesh(m_GameObjectMesh, m_GameObjectMaterials, m_GameObjectTextures);
            DrawBoundingBox();
        }

        private void ClearMesh()
        {
            m_GameObjectMaterials = null;
            m_GameObjectMesh = null;
            m_GameObjectTextures = null;
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
            m_device.SetStreamSource(0, m_CollisionBox, 0);
            //m_device.VertexFormat = CustomVertex.PositionColored.Format;
            m_device.Indices = m_IndexBuffer;
            m_device.DrawIndexedPrimitives(PrimitiveType.LineList, 0, 0, 8, 0, 12 );
        }
    }
}
