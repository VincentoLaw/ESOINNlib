using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using Microsoft.Win32;

namespace InputDataGenerator
{
    /// <summary>
    /// Логика взаимодействия для MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();
        }
        string text;
        private void Button1_Click(object sender, RoutedEventArgs e)
        {
            OpenFileDialog dlg = new OpenFileDialog();
            dlg.DefaultExt = ".jpg";
            dlg.Filter = "Jpg (*.jpg)|*.jpg|Images (*.bmp)|*.bmp| Png (*.png)|*.png";
            Nullable<bool> result = dlg.ShowDialog();
            if (result == true)
            {
                string filename = dlg.FileName;
                var img = new BitmapImage(new Uri(filename));
                var img_new = new BitmapImage(new Uri(filename));
                ImgPreview.Source = img;
                var pixels = BitmapSourceHelper.CopyPixels(img);
                var separator = SeparatorText.Text;
                Random rand = new Random();
                int noice = Convert.ToInt32(NoiceInput.Text);
                var pix_new = img_new.CopyPixels();
                string res = "";
                for (var i = 0; i < pixels.GetLength(0); i++)
                    for (var j = 0; j < pixels.GetLength(1); j++)
                    {
                        if (rand.Next(100) < noice)
                        {
                            byte r = (byte)rand.Next(256);
                            byte g = (byte)rand.Next(256);
                            byte b = (byte)rand.Next(256);
                            res += b + r * 256 + g * 256 * 256;
                            /*var px_col = new PixelColor();
                            px_col.Red = r;
                            px_col.Green = g;
                            px_col.Blue = b;
                            pix_new[i, j] = px_col;*/
                        }
                        else
                        {
                            res += ((int)pixels[i, j].Blue + ((int)pixels[i, j].Green + 1) * 256 + ((int)pixels[i, j].Red + 1) * 256 * 256).ToString() + separator;
                        }
                    }
                if (ShowOutputChb.IsChecked == true)
                {
                    OutputText.Text = res;
                }
                text = res;
            }
        }

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            SaveFileDialog sfd = new SaveFileDialog();
            sfd.Filter = "txt files (*.txt)|*.txt";
            Nullable<bool> result = sfd.ShowDialog();
            
            if (result == true)
            {
                if (sfd.FileName != "")
                {
                    // Code to write the stream goes here.
                    var file_name =sfd.FileName;
                    System.IO.StreamWriter sw = new System.IO.StreamWriter(file_name);
                    sw.Write(text);
                }
            }
        }
    }
}
