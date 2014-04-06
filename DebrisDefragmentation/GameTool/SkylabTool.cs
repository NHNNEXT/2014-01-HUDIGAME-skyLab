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

        public skyLabTool()
        {
            InitializeComponent();

           if ( Renderer.Init(this.View.Handle.ToInt32(), this.View.Width, this.View.Height) )
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
                Renderer.Clear();
                Renderer.Begin();

                // 여기서 뭔가 그리게 됩니다

                Renderer.End();

                await Task.Delay(10);
            }
        }
    }
}
