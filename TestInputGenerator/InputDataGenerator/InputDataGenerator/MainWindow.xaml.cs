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
using System.IO;
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
        /*
        Загрузка множества изображений
        вывод координат по точкам
        добавить возможность просто перемешки данных
        ч\б
        добавить возможность шумов из палитры текущего изображения.
        сделать % в шуме не только целыми.
        сделать сохранение изображений
        изменить пропорции. 3 колонка должна быть гораздо меньше.
        стоит ли учитывать alpha при генерации шума? стоит ли её учитывать в выходных данных?
        стоит ли добавлять опцию "генерировать шум для каждого экземпляра"? Вроде нет случаев когда есть шум и он не должен быть разным
         * 
        можно потом добавить сравнение 2х изображений (типо проверять уже восстановленный образ) в % соответствия.
         * 
         * 
         * протестить пнг и т.п.
         * 
         * БАГИ:
         * 1)маленькие изображения могут криво обрабатываться
         * 2)аутпут именно для 16 оттенков именно в  блокноте выглядит крайне странно
         * 3) 2 оттенка плохо работают. мб стоит даже формулу изменить, ато жёлтый цвет к примеру становится белым.
        */
        string text;
        BitmapSource resultImg;
        BitmapImage img;
        string filename;
        private void Button1_Click(object sender, RoutedEventArgs e)
        {
            OpenFileDialog dlg = new OpenFileDialog();
            dlg.DefaultExt = ".jpg";
            dlg.Filter = "Jpg (*.jpg)|*.jpg|Images (*.bmp)|*.bmp| Png (*.png)|*.png";
            Nullable<bool> result = dlg.ShowDialog();
            if (result == true)
            {
                filename = dlg.FileName;
                img = new BitmapImage(new Uri(filename));
                ImgPreview.Source = img;
                ConvertImage();
            }
        }

        private void ConvertImage()
        {
            OutputText.Text = "";
            var separator = SeparatorText.Text;
            Random rand = new Random();
            int noice = Convert.ToInt32(NoiceInput.Text);
            var pix_new = img.CopyPixels();

            var dpiX = 96d;
            var dpiY = 96d;
            var pixelFormat = PixelFormats.Bgr32;
            if (GrayScale.IsChecked == true)
            {
                switch (GrayScaleColorsCountCmb.SelectedIndex)
                {
                    case 0: pixelFormat = PixelFormats.Gray2; break;
                    case 1: pixelFormat = PixelFormats.Gray2; break;
                    case 2: pixelFormat = PixelFormats.Gray4; break;
                    case 3: pixelFormat = PixelFormats.Gray8; break;
                    default:; break;
                }
            }
            var bytesPerPixel = (pixelFormat.BitsPerPixel + 7) / 8;
            //MessageBox.Show(bytesPerPixel + " ");
            

            var relative_result_width = Convert.ToDouble(ResultImageWidth.Text);
            var relative_result_height = Convert.ToDouble(ResultImageHeight.Text);

            Uri uri = new Uri(filename);
            BitmapImage source = new BitmapImage();
            source.BeginInit();
            source.UriSource = uri;
            if (ImageSizeTypeCmb.SelectedIndex == 0)//%
            {
                source.DecodePixelHeight = (int)(relative_result_height * img.PixelHeight / 100);
                source.DecodePixelWidth = (int)(relative_result_width * img.PixelWidth / 100);
            }
            else//px
            {
                source.DecodePixelHeight = (int)(relative_result_height);
                source.DecodePixelWidth = (int)(relative_result_width);
            }
            source.EndInit();
            var pixels = BitmapSourceHelper.CopyPixels(source);


            int result_width = pixels.GetLength(0), result_height = pixels.GetLength(1);
            PreviewImgSize.Content = "Размеры:" + img.PixelWidth + "х" + img.PixelHeight;
            ResultImgSize.Content = "Размеры:" + result_width + "х" + result_height;
            string res = "";
            var pixels_for_result_img = new byte[result_width * result_height *  bytesPerPixel * pixelFormat.BitsPerPixel / 8];
            var stride = bytesPerPixel * result_width;
            int arr_counter = 0;

            if (GrayScale.IsChecked == true)
            {
                switch (GrayScaleColorsCountCmb.SelectedIndex)
                {
                    case 0: stride /= 4; break;
                    case 1: stride /= 4; break;
                    case 2: stride /= 2; break;
                    default: ; break;
                }
            }

            int points_cnt = result_width * result_height;
            int noice_points_cnt = points_cnt * noice / 100;
            bool[,] created_noice_matrix = new bool[result_width, result_height];
            for (int i = 0; i < result_width; i++)
                for (int j = 0; j < result_height; j++)
                    created_noice_matrix[i, j] = false;

            for (int i = 0; i < noice_points_cnt; i++)
            {
                bool created = false;
                while (!created)
                {
                    int w = rand.Next(result_width);
                    int h = rand.Next(result_height);
                    if (!created_noice_matrix[w, h])
                    {
                        created_noice_matrix[w, h] = true;
                        pixels[w, h].Red = (byte)rand.Next(256);
                        pixels[w, h].Blue = (byte)rand.Next(256);
                        pixels[w, h].Green = (byte)rand.Next(256);
                        pixels[w, h].Alpha = (byte)rand.Next(256);
                        created = true;
                    }
                }
            }

            var bit_val = 1;
            string coords_result = "";
            for (var i = 0; i < pixels.GetLength(0); i++)
            {
                for (var j = 0; j < pixels.GetLength(1); j++)
                {
                    byte r = pixels[i, j].Red, g = pixels[i, j].Green, b = pixels[i, j].Blue, a = pixels[i, j].Alpha;
                    string cur_text = "";
                    if (bytesPerPixel == 4)
                    {
                        pixels_for_result_img[arr_counter++] = b;
                        pixels_for_result_img[arr_counter++] = g;
                        pixels_for_result_img[arr_counter++] = r;
                        pixels_for_result_img[arr_counter++] = a;
                        cur_text = ((int)pixels[i, j].Blue + ((int)pixels[i, j].Green + 1) * 256 + ((int)pixels[i, j].Red + 1) * 256 * 256).ToString() + separator;
                    }
                    else
                    {
                        byte val = (byte)((b + g + r) / 3);
                        byte bit_summond = 0;
                        if (bit_val == 1)
                            pixels_for_result_img[arr_counter] = 0;
                        switch (GrayScaleColorsCountCmb.SelectedIndex)
                        {
                            case 0: bit_summond = (byte)(val / 128); break;
                            case 1: bit_summond = (byte)(val / 64); break;
                            case 2: bit_summond = (byte)(val / 16); break;
                            case 3: bit_summond = val; break;
                            default: cur_text = ""; break;
                        }
                        cur_text = "" + bit_summond.ToString() + separator;
                        if (GrayScaleColorsCountCmb.SelectedIndex == 0)
                            bit_summond *= 3;
                        pixels_for_result_img[arr_counter] += (byte)(bit_summond * bit_val);
                        switch (GrayScaleColorsCountCmb.SelectedIndex)
                        {
                            case 0: bit_val *= 4; break;
                            case 1: bit_val *= 4; break;
                            case 2: bit_val *= 16; break;
                            case 3: bit_val *= 256; break;
                            default: cur_text = ""; break;
                        }
                        if (bit_val >= 256)
                        {
                            arr_counter++;
                            bit_val = 1;
                        }
                        /*pixels_for_result_img[arr_counter++] = (byte)((b + g + r) / 3);
                        switch (GrayScaleColorsCountCmb.SelectedIndex) {
                            case 0: cur_text = (byte)(pixels_for_result_img[arr_counter - 1] / 128) + ""; break;
                            case 1: cur_text = (byte)(pixels_for_result_img[arr_counter - 1] / 64) + ""; break;
                            case 2: cur_text = (byte)(pixels_for_result_img[arr_counter - 1] / 16) + ""; break;
                            case 3: cur_text = (byte)(pixels_for_result_img[arr_counter - 1]) + ""; break;
                            default: cur_text =""; break;
                        }*/
                    }
                    if (CoordinatesOutput.IsChecked == true)
                    {
                        if (r > 5 || g > 5 || b > 5)
                        {
                            cur_text = "(" + j + "," + i + ")" + separator;
                        }
                        else cur_text = "";

                    }
                    if (arr_counter < 120 && ShowOutputChb.IsChecked == true && cur_text.Length > 0)
                    {
                        OutputText.Inlines.Add(new Run(cur_text));
                        OutputText.Inlines.Add(new LineBreak());
                    }

                    res += cur_text;

                }
            }
            text = res;
            resultImg = BitmapSource.Create(result_width, result_height, dpiX, dpiY, pixelFormat, null, pixels_for_result_img, stride);
            ImgResult.Source = resultImg;
           



            if (ShowOutputChb.IsChecked == true)
            {
                OutputCaption.Visibility = Visibility.Visible;
            }
            else
            {
                OutputCaption.Visibility = Visibility.Hidden;
                OutputText.Text = "";
            }
            
        }

        private void UpdateImage_Click(object sender, RoutedEventArgs e)
        {
            ConvertImage();
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
                    ConvertImage();
                    // Code to write the stream goes here.
                    var file_name =sfd.FileName;
                    System.IO.StreamWriter sw = new System.IO.StreamWriter(file_name);
                    sw.Write(text);
                    sw.Close();
                }
            }
        }

        private void ImageSizeTypeCmb_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            if (img != null)
            {
                if (ImageSizeTypeCmb.SelectedIndex == 0)
                {
                    ResultImageWidth.Text = "" + (int)(Convert.ToDouble(ResultImageWidth.Text) * 100 / img.PixelWidth);
                    ResultImageHeight.Text = "" + (int)(Convert.ToDouble(ResultImageHeight.Text) * 100 / img.PixelHeight);
                }
                else
                {
                    ResultImageWidth.Text = "" + (int)(Convert.ToDouble(ResultImageWidth.Text) * img.PixelWidth / 100);
                    ResultImageHeight.Text = "" + (int)(Convert.ToDouble(ResultImageHeight.Text) * img.PixelHeight / 100);
                }
            }
        }

        private void GrayScale_Click(object sender, RoutedEventArgs e)
        {
            if (GrayScale.IsChecked == true)
            {
                GrayScaleColorsCount.Visibility = System.Windows.Visibility.Visible;
                GrayScaleColorsCountCmb.Visibility = System.Windows.Visibility.Visible;
            }
            else {
                GrayScaleColorsCount.Visibility = System.Windows.Visibility.Hidden;
                GrayScaleColorsCountCmb.Visibility = System.Windows.Visibility.Hidden;
            }
        }

        private void SaveImage_Click(object sender, RoutedEventArgs e)
        {
            SaveFileDialog sfd = new SaveFileDialog();
            sfd.Filter = "images (*.jpg)|*.jpg";
            Nullable<bool> result = sfd.ShowDialog();
            if (result == true && sfd.FileName != "")
            {
                if (resultImg != null)
                {
                    var encoder = new PngBitmapEncoder();//тут может быть не только пнг ведь...
                    encoder.Frames.Add(BitmapFrame.Create((BitmapSource)ImgResult.Source));
                    using (FileStream stream = new FileStream(sfd.FileName, FileMode.Create))
                        encoder.Save(stream);
                }
            }
        }
    }
}
