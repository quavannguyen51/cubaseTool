using System.Runtime.InteropServices;




namespace AutoCubase
{
    using System;
    using System.Runtime.InteropServices;


    internal static class ImportDLL
    {
        [StructLayout(LayoutKind.Sequential)]
        public struct RECT
        {
            public int Left;
            public int Top;
            public int Right;
            public int Bottom;
        }

        [DllImport("EngineCpp.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr Engine_FindCubaseWindow();

        [DllImport("EngineCpp.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern bool Engine_GetWindowRect(
            IntPtr hwnd,
            out RECT rect
        );
    }
}
