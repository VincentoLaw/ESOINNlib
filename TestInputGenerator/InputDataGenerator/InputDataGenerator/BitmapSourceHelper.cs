using System;
using System.Runtime.InteropServices;
using System.Windows;
using System.Windows.Media;
using System.Windows.Media.Imaging;

namespace InputDataGenerator
{
    [StructLayout(LayoutKind.Sequential)]
    public struct PixelColor
    {
        public byte Blue;
        public byte Green;
        public byte Red;
        public byte Alpha;
    }
    public static class BitmapSourceHelper
    {
#if UNSAFE
        public unsafe static void CopyPixels(this BitmapSource source, PixelColor[,] pixels, int stride, int offset)
        {
            fixed(PixelColor* buffer = &pixels[0, 0])
            source.CopyPixels(
            new Int32Rect(0, 0, source.PixelWidth, source.PixelHeight),
            (IntPtr)(buffer + offset),
            pixels.GetLength(0) * pixels.GetLength(1) * sizeof(PixelColor),
            stride);
        }
#else
        public static void CopyPixels(this BitmapSource source, PixelColor[,] pixels, int stride, int offset)
        {
            var height = source.PixelHeight;
            var width = source.PixelWidth;
            var pixelBytes = new byte[height*width*4];
            source.CopyPixels(pixelBytes, stride, 0);
            int y0 = offset/width;
            int x0 = offset - width*y0;
            for (int y = 0; y < height; y++)
                for (int x = 0; x < width; x++)
                    pixels[x + x0, y + y0] = new PixelColor
                                                 {
                                                     Blue = pixelBytes[(y*width + x)*4 + 0],
                                                     Green = pixelBytes[(y*width + x)*4 + 1],
                                                     Red = pixelBytes[(y*width + x)*4 + 2],
                                                     Alpha = pixelBytes[(y*width + x)*4 + 3],
                                                 };
        }
#endif
        public static PixelColor[,] CopyPixels(this BitmapSource source)
        {
            if (source.Format != PixelFormats.Bgra32)
                source = new FormatConvertedBitmap(source, PixelFormats.Bgra32, null, 0);
            PixelColor[,] pixels = new PixelColor[source.PixelWidth, source.PixelHeight];
            int stride = source.PixelWidth * ((source.Format.BitsPerPixel + 7) / 8);
            GCHandle pinnedPixels = GCHandle.Alloc(pixels, GCHandleType.Pinned);
            source.CopyPixels(
              new Int32Rect(0, 0, source.PixelWidth, source.PixelHeight),
              pinnedPixels.AddrOfPinnedObject(),
              pixels.GetLength(0) * pixels.GetLength(1) * 4,
                  stride);
            pinnedPixels.Free();
            return pixels;
        }

        //[DllImport("gdi32")]
        //static extern int DeleteObject(IntPtr o);

        /*public static BitmapSource LoadBitmap(System.Drawing.Bitmap source)
        {
            IntPtr ip = source.GetHbitmap();
            BitmapSource bs = null;
            try
            {
                bs = System.Windows.Interop.Imaging.CreateBitmapSourceFromHBitmap(ip,
                   IntPtr.Zero, Int32Rect.Empty,
                   System.Windows.Media.Imaging.BitmapSizeOptions.FromEmptyOptions());
            }
            finally
            {
                DeleteObject(ip);
            }

            return bs;
        }*/
    }
}