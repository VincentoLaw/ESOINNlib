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
        BitmapSource resultImg;
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
                //var pixels = BitmapSourceHelper.CopyPixels(img);
                

                var separator = SeparatorText.Text;
                Random rand = new Random();
                int noice = Convert.ToInt32(NoiceInput.Text);
                var pix_new = img_new.CopyPixels();

                var dpiX = 96d;
                var dpiY = 96d;
                var pixelFormat = PixelFormats.Bgr32;
                var bytesPerPixel = (pixelFormat.BitsPerPixel + 7) / 8;

                

                Uri uri = new Uri(filename);
                BitmapImage source = new BitmapImage();
                source.BeginInit();
                source.UriSource = uri;
                source.DecodePixelHeight = (int)(Convert.ToDouble(ResultImageHeight.Text) * img.Height / 100);
                source.DecodePixelWidth = (int)(Convert.ToDouble(ResultImageWidth.Text) * img.Width / 100);
                source.EndInit();
                var pixels = BitmapSourceHelper.CopyPixels(source);
                //ImgPreview.Source = source;
                PreviewImgSize.Content = "Размеры:" + img.Width + "х" + img.Height;
                ResultImgSize.Content = "Размеры:" + pixels.GetLength(0) + "х" + pixels.GetLength(1);

                string res = "";
                double stepWidth = 100 / Convert.ToDouble(ResultImageWidth.Text);//новые размеры итк есть в соурсе
                double stepHeight = 100 / Convert.ToDouble(ResultImageHeight.Text);
                int width_size = (int)(img.Width / stepWidth), height_size = (int)(img.Height / stepHeight);
                var pixels_for_result_img = new byte[height_size * width_size * 4];
                var stride = bytesPerPixel * width_size;//1st number bytes per pixel
                //1st dimention is width, second height, i_step width, i width, new_i width
                int arr_counter = 0;
                for (var i = 0; i < pixels.GetLength(0); i++)
                {
                    for (var j = 0; j < pixels.GetLength(1); j++)
                    {
                        {
                            byte r = pixels[i, j].Red, g = pixels[i, j].Green, b = pixels[i, j].Blue, a = pixels[i, j].Alpha;
                            if (rand.Next(100) < noice)
                            {
                                r = (byte)rand.Next(256);
                                g = (byte)rand.Next(256);
                                b = (byte)rand.Next(256);
                                a = (byte)rand.Next(256);
                                res += b + r * 256 + g * 256 * 256;
                            }
                            else
                            {
                                res += ((int)pixels[i, j].Blue + ((int)pixels[i, j].Green + 1) * 256 + ((int)pixels[i, j].Red + 1) * 256 * 256).ToString() + separator;
                            }
                            pixels_for_result_img[arr_counter++] = b;
                            pixels_for_result_img[arr_counter++] = g;
                            pixels_for_result_img[arr_counter++] = r;
                            pixels_for_result_img[arr_counter++] = a;
                        }
                    }
                }
                if (ShowOutputChb.IsChecked == true)
                {
                    OutputCaption.Visibility = Visibility.Visible;
                    OutputText.Text = res;
                }
                else
                {
                    OutputCaption.Visibility = Visibility.Hidden;
                    OutputText.Text = "";
                }
                text = res;
                resultImg = BitmapSource.Create(width_size, height_size, dpiX, dpiY, pixelFormat, null, pixels_for_result_img, stride);
                ImgResult.Source = resultImg;
            }
        }

        private void UpdateImage_Click(object sender, RoutedEventArgs e)
        {

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

        private void ComboBox_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            if (text != null && text.Length > 0)
            {
                if (ImageSizeTypeCmb.SelectedIndex == 0)
                {

                }
                else
                {

                }
            }
        }
    }
}
