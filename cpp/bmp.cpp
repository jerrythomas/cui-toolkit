BMP BitMapHeader structure
file contains
  file header ,
  bmp header ,
  bitmap data ,
  and color map unless image uses 24 bit color

File Header
bfType //type of file ; must be ascii "BM" ?? 2B
bfSize  // Size of file                    ?? 2B
bfReserved1  //reserved fiels must be 0    ?? 1B
bfReserved2 // ----------do------------    ?? 1B
bf OffBits  //specifies offset in bytes fo start of bitmap data ?? 1B

BMP bitmap infostructure
biSize           //Size of bitmapinfostructure 40 bytes
biWidth          //Width of bitmap in pixels   ? 2 bytes ?
biHeight         //Height of Bitmap in pixels  ? 2 bytes ?
biPlanes         //image planes( 1)            ?  1 b ?
biBitCount       //BitsPerPixel (1,4,8 or 24)  ? 1 b ?
biCompression    //Compressionused             ?     ?
biSizeImage      // Size of image in bytes     ? 4 bytes ?
biXPelsPerMeter  // Horizontal resolution in pixels per meter   ? 1b?
biYPelsPerMeter  // Vertical resolution in pixels per meter     ? 1 b?
biClrUsed        // Number of color inedxes in the color table  ? 2 b?
biClrImportant   // Number of color indexes considered important for displaying bitmap  ? 2 b?


biCompression specifies type of compression
 BI_RGB   => no compression
 BI_RLE4  => RLE 4 bit color
 BI_RLE8 => RLE 8  bit color
 if biClrUsed is 0
    the bmp uses 24 bit color
 else
    the value is the actual number of colors bmp uses
 if biClrImportant = 0
    all colors are important
 Color data entries in Color map occupy 4 bytes
   1 byte each for blue green & red values 1byte left as 0
