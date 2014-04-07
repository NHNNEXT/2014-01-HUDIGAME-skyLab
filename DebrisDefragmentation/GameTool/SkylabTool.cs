using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace GameTool
{
    public partial class skyLabTool : Form
    {
        bool g_IsRenderable = true;
        private DDWrapper.Renderer m_Renderer = null;

        public skyLabTool()
        {
           InitializeComponent();
           // new 하면 멤버변수가 싱글톤으로 할당됨
           m_Renderer = new DDWrapper.Renderer();

           if ( m_Renderer.Init(this.View.Handle.ToInt32(), this.View.Width, this.View.Height) )
           {
               DrawScreen();
           }
            //모든게 끝날 때 D3D도 릴리즈 시켜줘야 합니다
            //그러니까 이 함수는 이 자리 말고 Exit 버튼 콜백에 이식해줌 됩니다
            //Renderer.Release();
        }

        private async void DrawScreen()
        {
            while(g_IsRenderable)
            {
                m_Renderer.Clear();
                m_Renderer.BeginDraw();

                // 여기서 뭔가 그리게 됩니다

                m_Renderer.EndDraw();

                await Task.Delay(10);
            }
        }
    }
}
