using Microsoft.DirectX.Direct3D;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace GameTool.Class
{
    class CoordinateAxis
    {
        private VertexBuffer m_CoordinateAxis;

        public void SetAxisLine(Device d3dDevice)
        {
            m_CoordinateAxis = new VertexBuffer(typeof(CustomVertex.PositionColored), 6,
               d3dDevice, 0, CustomVertex.PositionColored.Format, Pool.Managed);

            CustomVertex.PositionColored[] posColoredVerts = new CustomVertex.PositionColored[6];

            posColoredVerts[0].Position = new Microsoft.DirectX.Vector3(0, 0, 0);
            posColoredVerts[0].Color = System.Drawing.Color.Red.ToArgb();
            posColoredVerts[1].Position = new Microsoft.DirectX.Vector3(10, 0, 0);
            posColoredVerts[1].Color = System.Drawing.Color.Red.ToArgb();
            posColoredVerts[2].Position = new Microsoft.DirectX.Vector3(0, 0, 0);
            posColoredVerts[2].Color = System.Drawing.Color.Green.ToArgb();
            posColoredVerts[3].Position = new Microsoft.DirectX.Vector3(0, 10, 0);
            posColoredVerts[3].Color = System.Drawing.Color.Green.ToArgb();
            posColoredVerts[4].Position = new Microsoft.DirectX.Vector3(0, 0, 10);
            posColoredVerts[4].Color = System.Drawing.Color.Blue.ToArgb();
            posColoredVerts[5].Position = new Microsoft.DirectX.Vector3(0, 0, 0);
            posColoredVerts[5].Color = System.Drawing.Color.Blue.ToArgb();

            Microsoft.DirectX.GraphicsStream gstm = m_CoordinateAxis.Lock(0, 0, LockFlags.None);
            gstm.Write(posColoredVerts);
            m_CoordinateAxis.Unlock();

        }

        public void RenderAxis(Device d3dDevice)
        {
            d3dDevice.RenderState.Lighting = false;
            d3dDevice.SetStreamSource(0, m_CoordinateAxis, 0);
            d3dDevice.VertexFormat = CustomVertex.PositionColored.Format;
            d3dDevice.DrawPrimitives(PrimitiveType.LineList, 0, 3);
            d3dDevice.RenderState.Lighting = true;
        }

    }
}
