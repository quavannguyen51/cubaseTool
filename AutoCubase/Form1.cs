namespace AutoCubase
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();


        }

        private void button1_Click(object sender, EventArgs e)
        {
            var hwnd = ImportDLL.Engine_FindCubaseWindow();
            if (hwnd == IntPtr.Zero)
            {
                MessageBox.Show("Không tìm thấy Cubase");
                return;
            }

           ImportDLL.Engine_GetWindowRect(hwnd, out var r);

            MessageBox.Show(
                $"Cubase: {r.Left},{r.Top} - {r.Right},{r.Bottom}"
            );
        }
    }
    
}
