using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.InteropServices;

namespace GameTool
{
    class Renderer
    {
        [DllImport("Renderer.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern bool Init(Int32 hWnd, int WindowWidth, int WindowHeight);

        [DllImport("Renderer.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern bool Release();

        [DllImport("Renderer.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern bool Clear();

        [DllImport("Renderer.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern bool Begin();

        [DllImport("Renderer.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern bool End();
    }
}
